#pragma once

#include <QWidget>
#include "ui_SetPathWidget.h"

class SetPathWidget : public QWidget
{
	Q_OBJECT

public:
	SetPathWidget(QWidget *parent = Q_NULLPTR);
	~SetPathWidget();

private:
	Ui::SetPathWidget ui;
};
