#include "LightControl.h"

LightControl::LightControl()
{

}

LightControl::~LightControl()
{

}

void LightControl::onRecv()
{

}

int LightControl::open(const char* port, int baudrate, int databits, int stopbits, int parity)
{
	mSP.setPortName(port);
	mSP.setBaudRate(baudrate);
	mSP.setDataBits((QSerialPort::DataBits)databits);
	mSP.setStopBits((QSerialPort::StopBits)stopbits);
	mSP.setParity((QSerialPort::Parity)parity);
	if (mSP.open(QIODevice::ReadWrite)) {
		return 0;
	}
	connect(&mSP, SIGNAL(readyRead()), this, SLOT(onRecv()));
	return -1;
}

int LightControl::close()
{
	mSP.close();
	return 0;
}

int LightControl::setBright(int channel, int bright)
{
	unsigned char data[] = { 0xAA,mDevId,0x33,2,channel,bright ,0,0};
	unsigned short sum = 2;
	sum += channel;
	sum += bright;
	data[6] = sum >> 8;
	data[7] = (sum & 0xFF);
	mSP.write((char*)data,8);
	return 0;
}

int LightControl::getBright(int channel)
{
	return 0;
}