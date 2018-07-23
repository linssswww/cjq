#pragma once

#include <QWidget>
#include "ui_loginWidget.h"
#include "mainwindow.h"
class loginWidget : public QWidget
{
	Q_OBJECT

public:
	loginWidget(QWidget *parent = Q_NULLPTR);
	~loginWidget();

private:
	Ui::loginWidget ui;
	MainWindow *mw;
	QWidget *qw;
	QString usr;
private slots:
	void logined();
	void editText(QString usr);

};
