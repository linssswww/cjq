#pragma once
#include "ui_Widget.h"
namespace Ui {
	class Form;
}
class Form :public Ui_Form {
public:
	Form();
	void test();
private slots :
		  void finsh();
};