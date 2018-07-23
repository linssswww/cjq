#pragma once
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class LightControl:QObject
{
	Q_OBJECT
public:
	LightControl();
	~LightControl();

	int open(const char* port,int baudrate,int databits,int stopbits,int parity);
	int close();
	void setDeviceID(int devID) { mDevId = devID; }
	int setBright(int channel,int bright);
	int getBright(int channel);
	
protected:
	QSerialPort mSP;
	int mDevId = 1;

private slots:
void onRecv();
};