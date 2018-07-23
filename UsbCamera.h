#pragma once
#include <vector>
#include <string>

extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}
#include <mutex>

#define MAX_BUFFER_SIZE (2048*1536*4)

enum UsbCameraErr
{
	UCE_OPEN_CODEC_ERR = -100,
	UCE_WRONG_STREAM = -3,
	UCE_CODEC_ALLOC_ERR,
	UCE_FINDE_DECODER_ERR,
	UCE_OK = 0,

};

class UsbCamera;
class UsbCameraManager
{
protected:
	UsbCameraManager();
public:
	~UsbCameraManager();
	static UsbCameraManager* instance()
	{
		static UsbCameraManager ucm;
		return &ucm;
	}
	int initialize();
	void uninit();
	UsbCamera* getCameraByIndex(int index);

protected:
	std::vector<UsbCamera*> mCameras;
};

struct bmImage
{
	int w;
	int h;
	unsigned char* data;
};

class UsbCamera
{
	friend UsbCameraManager;
protected:
	UsbCamera();

public:
	virtual ~UsbCamera();
	const char* name() { return mName.c_str(); }
	int open();
	int close();
	int grabOne(bmImage* image);

protected:
	void grabFoo();

	std::string mName;
	int mIndex; //同名称的列表中编号
	unsigned char* mBuffer;

	AVFormatContext *formatCtx = nullptr;
	AVDictionary* options = nullptr;
	static AVInputFormat *iformat;
	int video_stream = 0;
	int width;
	int height;
	AVCodecContext *codecctx = nullptr;
	AVCodec * decodec = nullptr;
	AVFrame * frame = nullptr;
	AVPacket packet;
	unsigned char* mImage = nullptr;
	unsigned char* mCloneImage = nullptr;
	int mLastSize = 0;
	int mCloneSize = 0;
	int mChannel = 3;

	bool mThreadCond = false;
	bool mIsNew = false;
	std::mutex mMutex;
};
