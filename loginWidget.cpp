#include "loginWidget.h"

loginWidget::loginWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

loginWidget::~loginWidget()
{

}
void loginWidget::editText(QString usr)
{
	this->usr = usr;
}
void loginWidget::logined() {
	this->hide();
	mw = new MainWindow(usr);
	mw->show();
}

