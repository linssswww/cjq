#include "mainwindow.h"
#include "ui_Widget.h"
#include "loginwidget.h"
#include "ui_Dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
	loginWidget lw;
	lw.show();
	
	//QWidget QW;
	//Ui_Form ui;
	//ui.setupUi(&QW);
	//QW.show();
    return a.exec();
}
