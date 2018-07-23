#include "UsbCamera.h"
#include <Strmif.h>
#include <uuids.h>
#include <comutil.h>
#include <map>
#define __IDxtCompositor_INTERFACE_DEFINED__  
#define __IDxtAlphaSetter_INTERFACE_DEFINED__  
#define __IDxtJpeg_INTERFACE_DEFINED__  
#define __IDxtKey_INTERFACE_DEFINED__  
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swscale.lib")
#include <thread>
#include <chrono>

AVInputFormat* UsbCamera::iformat = nullptr;
template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

UsbCameraManager::UsbCameraManager()
{
	avcodec_register_all();
	avdevice_register_all();
}

UsbCameraManager::~UsbCameraManager()
{
	uninit();
	for (auto camera : mCameras)
	{
		delete camera;
	}
	mCameras.clear();
}

int UsbCameraManager::initialize()
{
	ICreateDevEnum *pSysDevEnum;  //创建设备枚举器
									 //创建设备枚举管理器
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum,
		//要创建的Filter的Class ID
		NULL,       //表示Filter不被聚合
		CLSCTX_INPROC_SERVER,  //创建进程内COM对象
		IID_ICreateDevEnum,   //获得的接口ID
		(void**)&pSysDevEnum); //创建的接口对象的指针
	if (hr != NOERROR)  return -1;
	IEnumMoniker *pEnumCat = NULL;
	hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumCat, 0);

	std::map<std::string, int> name2count;
	if (S_OK == hr)
	{
		pEnumCat->Reset();
		ULONG cFetched;
		IMoniker *pM;

		while (hr = pEnumCat->Next(1, &pM, &cFetched), hr == S_OK)
		{
			IPropertyBag *pBag = 0;

			hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
			if (SUCCEEDED(hr))
			{
				VARIANT var;
				var.vt = VT_BSTR;
				hr = pBag->Read(L"FriendlyName", &var, NULL);
				if (hr == NOERROR)
				{
					UsbCamera* camera = new UsbCamera();
					camera->mName = _com_util::ConvertBSTRToString(var.bstrVal);
					//camera->mMoniker = pM;
					//pM->BindToObject(0, 0,
					//	IID_IBaseFilter, (void**)&camera->mFilter);
					if (name2count.find(camera->mName) == name2count.end())
					{
						name2count[camera->mName] = 1;
						camera->mIndex = 0;
					}
					else
					{
						int count = name2count[camera->mName];
						camera->mIndex = count;
						name2count[camera->mName] = count + 1;
					}
					mCameras.push_back(camera);
					SysFreeString(var.bstrVal);
					pM->AddRef();
				}
				pBag->Release();
			}

			pM->Release();
		}
		pEnumCat->Release();
	}
	pSysDevEnum->Release();

	return mCameras.size();
}

void UsbCameraManager::uninit()
{
	for (auto camera : mCameras)
	{
		camera->close();
	}
}

UsbCamera* UsbCameraManager::getCameraByIndex(int index)
{
	if (mCameras.size() > index)
	{
		return mCameras[index];
	}
	return nullptr;
}

UsbCamera::UsbCamera()
{
	mBuffer = new unsigned char[MAX_BUFFER_SIZE];
}

UsbCamera::~UsbCamera()
{
	if (mImage) {
		delete[] mImage;
	}
	if (mCloneImage)
	{
		delete[] mCloneImage;
	}
}

int UsbCamera::open()
{
	mThreadCond = true;
	formatCtx = avformat_alloc_context();
	char index[3] = { 0 };
	itoa(mIndex, index, 10);
	//av_dict_set(&options, "show_video_device_dialog", "true", 0);
	av_dict_set(&options, "video_device_number", index, 0);
	if (!iformat)
	{
		iformat = av_find_input_format("dshow");
	}
	char iParam[100] = { 0 };
	sprintf(iParam, "video=%s", mName.c_str());
	int ret = avformat_open_input(&formatCtx, iParam, iformat, &options);
	if (0 == ret)
	{
		video_stream = av_find_best_stream(formatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
		if (video_stream < 0)
		{
			avformat_close_input(&formatCtx);
			return UCE_WRONG_STREAM;
		}
		width = formatCtx->streams[video_stream]->codecpar->width;
		height = formatCtx->streams[video_stream]->codecpar->height;
		codecctx = avcodec_alloc_context3(NULL);
		if (!codecctx) {
			return UCE_CODEC_ALLOC_ERR;
		}
		avcodec_parameters_to_context(codecctx, formatCtx->streams[video_stream]->codecpar);
		decodec = avcodec_find_decoder(codecctx->codec_id);
		if(!decodec){
			return UCE_FINDE_DECODER_ERR;
		}
		if (avcodec_open2(codecctx, decodec, NULL) < 0) {
			return UCE_OPEN_CODEC_ERR;
		}
		av_init_packet(&packet);
		frame = av_frame_alloc();
		std::thread t([=]() {
			grabFoo();
		});
		t.detach();
	}
	return ret;
}

#include <QThread>
void UsbCamera::grabFoo()
{
	while (mThreadCond)
	{
		if (0 <= av_read_frame(formatCtx, &packet))
		{
			if (packet.stream_index == video_stream)
			{
				if (avcodec_send_packet(codecctx, &packet) != 0) {
					break;
				}
				while (0 == avcodec_receive_frame(codecctx, frame))
				{
					char * buffer = NULL;
					size_t buffer_size = 0;
					struct SwsContext *pSwsCtx = NULL;
					AVFrame * rgb_frame = av_frame_alloc();
					buffer_size = avpicture_get_size(AV_PIX_FMT_RGB24, width, height);
					buffer = (char *)av_malloc(buffer_size);
					avpicture_fill((AVPicture*)rgb_frame, (uint8_t *)buffer, AV_PIX_FMT_RGB24, width, height);
					//get swscale ctx  
					pSwsCtx = sws_getContext(
						formatCtx->streams[video_stream]->codecpar->width,
						formatCtx->streams[video_stream]->codecpar->height,
						(AVPixelFormat)frame->format,
						width,
						height,
						AV_PIX_FMT_RGB24,
						SWS_BILINEAR,
						NULL,
						NULL,
						NULL);
					if (pSwsCtx)
					{
						FILE *fp = NULL;
						SYSTEMTIME dt = { 0 };
						//图像格式转换  
						sws_scale(
							pSwsCtx,
							frame->data,
							frame->linesize,
							0,
							formatCtx->streams[video_stream]->codecpar->height,
							rgb_frame->data,
							rgb_frame->linesize);
						int size = rgb_frame->linesize[0] * height;
						mChannel = rgb_frame->linesize[0] / width;
						mMutex.lock();
						if (!mImage) {
							mImage = new unsigned char[size];
							mLastSize = size;
						}
						else
						{
							if (mLastSize != size) {
								delete[] mImage;
								mImage = new unsigned char[size];
								mLastSize = size;
							}
						}
						memcpy(mImage, rgb_frame->data[0], size);
						mIsNew = true;
						mMutex.unlock();
						sws_freeContext(pSwsCtx);
					}
					//free buffer  
					av_free(rgb_frame);
					av_free(buffer);
				}
			}
			av_packet_unref(&packet);
		}
		QThread::msleep(30);
	}
	av_free(frame);
	av_free(decodec);
	av_free(codecctx);
	av_free(iformat);
	av_free(options);
	av_free(formatCtx);
}

int UsbCamera::close()
{
	mThreadCond = false;
	std::chrono::milliseconds dura(2000);
	std::this_thread::sleep_for(dura);
	return 0;
}

int UsbCamera::grabOne(bmImage* image)
{
	mMutex.lock();
	if (mIsNew)
	{
		image->w = width;
		image->h = height;
		if (!mCloneImage || mCloneSize != mLastSize) {
			if (mCloneImage) { delete[] mCloneImage; }
			mCloneImage = new unsigned char[mLastSize];
			mCloneSize = mLastSize;
		}
		memcpy(mCloneImage, mImage, mLastSize);
		image->data = mCloneImage;
		mMutex.unlock();
		return 0;
	}
	mMutex.unlock();
	return -1;
}