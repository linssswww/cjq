/********************************************************************************
** Form generated from reading UI file 'SetPathWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPATHWIDGET_H
#define UI_SETPATHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetPathWidget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *taskLineEdit;
    QLineEdit *zuheLineEdit;
    QLineEdit *usrLineEdit;
    QLabel *label_3;
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *SetPathWidget)
    {
        if (SetPathWidget->objectName().isEmpty())
            SetPathWidget->setObjectName(QStringLiteral("SetPathWidget"));
        SetPathWidget->resize(400, 284);
        gridLayoutWidget = new QWidget(SetPathWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 371, 201));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        taskLineEdit = new QLineEdit(gridLayoutWidget);
        taskLineEdit->setObjectName(QStringLiteral("taskLineEdit"));

        gridLayout->addWidget(taskLineEdit, 0, 1, 1, 1);

        zuheLineEdit = new QLineEdit(gridLayoutWidget);
        zuheLineEdit->setObjectName(QStringLiteral("zuheLineEdit"));

        gridLayout->addWidget(zuheLineEdit, 2, 1, 1, 1);

        usrLineEdit = new QLineEdit(gridLayoutWidget);
        usrLineEdit->setObjectName(QStringLiteral("usrLineEdit"));

        gridLayout->addWidget(usrLineEdit, 1, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        horizontalLayoutWidget = new QWidget(SetPathWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 220, 371, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        retranslateUi(SetPathWidget);
        QObject::connect(pushButton, SIGNAL(clicked()), SetPathWidget, SLOT(hide()));

        QMetaObject::connectSlotsByName(SetPathWidget);
    } // setupUi

    void retranslateUi(QWidget *SetPathWidget)
    {
        SetPathWidget->setWindowTitle(QApplication::translate("SetPathWidget", "\346\226\207\344\273\266\345\244\271\350\256\276\347\275\256", Q_NULLPTR));
        label_2->setText(QApplication::translate("SetPathWidget", "\344\273\273\345\212\241\345\220\215:", Q_NULLPTR));
        label_3->setText(QApplication::translate("SetPathWidget", "\345\225\206\345\223\201\347\273\204:", Q_NULLPTR));
        label->setText(QApplication::translate("SetPathWidget", "\347\224\250\346\210\267\345\220\215:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SetPathWidget", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SetPathWidget: public Ui_SetPathWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPATHWIDGET_H
