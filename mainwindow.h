#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "motioncard.h"
#include "UsbCamera.h"
#include "LightControl.h"
#include "dwb.h"
#include <string>
#include <map>
#include "widget.h"
#include <QtWidgets/QTableWidget>
#include "SetPathWidget.h";
namespace Ui {
class MainWindow;
}
struct productinfo 
{
	string eng;
	string chn;
	int sideNum;
	int proNum;
	vector<QString> statistic;
	string seqcode;
};
#define DISPLAY_CAMERA_COUNT (3)
#define DEFAULT_VEL (50000)
#define PULSE_PER_ANGLE (1000)
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString usr,QWidget *parent = 0);
    ~MainWindow();
	void setRgain(int param);
	void setGgain(int param);
	void setBgain(int param);
private slots:
    void on_cmbCameras_currentIndexChanged(int index);

    void on_cmbDPI_currentIndexChanged(int index);

    void on_pbExposure_clicked();

    void on_pbGain_clicked();

    void on_pbBalance_clicked();

    void on_pbStart_clicked();

    void on_pbBrowse_clicked();

    void on_pbSnap_clicked();

    void on_pbRotation_clicked();

    void on_pbRotation2_clicked();

    void on_pbGo_clicked();
    void onDisplay(QImage img,int index);
    void on_pbParamSet_clicked();
	void on_slideLight1_valueChanged(int value);
	void on_slideLight2_valueChanged(int value);
	void on_slideLight3_valueChanged(int value);
	void on_slideLight4_valueChanged(int value);
	void on_slideLight5_valueChanged(int value);
	void on_slideLight6_valueChanged(int value);
	void on_slideLight7_valueChanged(int value);
	void on_slideLight8_valueChanged(int value);

	void isOpenAWB(int param);
	void setGainValue();
	void OpenOrCloseAWB(bool);

	void addElement();

	void ensure();

	void SelectionChanged();

	void addItem();
	
	void clearItem();

	void currentItem(QTableWidgetItem *item);
	void alsetPath();
signals:
    void displaySig(QImage img,int index);

private:


    bool initCameras();
    void startThread();
	bool loadConfig();
    static void displayFoo(MainWindow* mw,int index);
    void onDisplayFoo(int index);
	void showMessage(QString msg);
	int getImage(int index,QImage& qimg);
	int awb(QImage &qImg, int index);
	int QImage2Mat(QImage &qImg, cv::Mat &img);
	int Mat2QImage(cv::Mat &img, QImage &qImg);
	QString getTime(QString format);
	QString genFile();
	QString mkMutiDir(const QString path);
	QString getPath();
	QString getName(int index);


	QGraphicsScene* mScenes[DISPLAY_CAMERA_COUNT];
	QGraphicsView* mGraphicsViews[DISPLAY_CAMERA_COUNT];
    int mCameraCount;
	unsigned char* mImages[DISPLAY_CAMERA_COUNT];

	Ui::MainWindow *ui;
	Ui::Form uiFrom;
	Ui::SetPathWidget pathUi;
	QWidget qwPath;
	QWidget qw;
	vector<productinfo> products;
	QString mfile;
	QString musrName;

    QString mStartup;
    bool mThreadCond;
    bool mDisplayCond;
    bool mFirstCameraChange=true;

    MotionCard mMotionCard;
	UsbCameraManager* mUcm;
	LightControl mLightCtrl;

	std::string mLightPort;
	int mBaudRate;
	int mDataBits;
	int mStopBits;
	int mParity;
	int mMotionVel = DEFAULT_VEL;
	int mPulsePerAngle = PULSE_PER_ANGLE;

	std::mutex mMutex[3];
	std::map<std::string, std::string> mClassify;
	std::map<std::string, std::string> mEn2Cn;
	std::map<std::string, std::string> mEn2Seq;

	bool isOpenAWBmode = false;
	bool startAWB = false;
	DWB dwb;
	DWB dwb1;
	DWB dwb2;

};

#endif // MAINWINDOW_H
