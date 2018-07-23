/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_11;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView4;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView2;
    QGraphicsView *graphicsView3;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labCurPos;
    QPushButton *pbRotation;
    QLineEdit *leStep;
    QPushButton *pbRotation2;
    QLineEdit *leAbsPos;
    QPushButton *pbGo;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QComboBox *cmbCameras;
    QPushButton *pbSnap;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_2;
    QSlider *slideLight1;
    QSlider *slideLight2;
    QSlider *slideLight5;
    QSlider *slideLight4;
    QSlider *slideLight8;
    QSlider *slideLight7;
    QSlider *slideLight6;
    QSlider *slideLight3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QSpinBox *spinExposure;
    QPushButton *pbExposure;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QSpinBox *spinGain;
    QPushButton *pbGain;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QComboBox *cmbDPI;
    QPushButton *pbParamSet;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *leAutoStep;
    QPushButton *pbStart;
    QSpacerItem *horizontalSpacer_14;
    QLabel *genPathLabel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *checkBox_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_12;
    QComboBox *cmbClassify;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_11;
    QTableWidget *tableWidget;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1386, 1075);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_11 = new QHBoxLayout(centralWidget);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView4 = new QGraphicsView(frame_2);
        graphicsView4->setObjectName(QStringLiteral("graphicsView4"));

        gridLayout->addWidget(graphicsView4, 1, 1, 1, 1);

        graphicsView = new QGraphicsView(frame_2);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        graphicsView2 = new QGraphicsView(frame_2);
        graphicsView2->setObjectName(QStringLiteral("graphicsView2"));

        gridLayout->addWidget(graphicsView2, 0, 1, 1, 1);

        graphicsView3 = new QGraphicsView(frame_2);
        graphicsView3->setObjectName(QStringLiteral("graphicsView3"));

        gridLayout->addWidget(graphicsView3, 1, 0, 1, 1);


        horizontalLayout_11->addWidget(frame_2);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(800, 500));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labCurPos = new QLabel(frame);
        labCurPos->setObjectName(QStringLiteral("labCurPos"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labCurPos->sizePolicy().hasHeightForWidth());
        labCurPos->setSizePolicy(sizePolicy2);
        labCurPos->setMinimumSize(QSize(100, 0));
        labCurPos->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(labCurPos);

        pbRotation = new QPushButton(frame);
        pbRotation->setObjectName(QStringLiteral("pbRotation"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pbRotation->sizePolicy().hasHeightForWidth());
        pbRotation->setSizePolicy(sizePolicy3);
        pbRotation->setMinimumSize(QSize(32, 32));
        pbRotation->setMaximumSize(QSize(32, 32));
        pbRotation->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Trainer/Resource/rotation2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbRotation->setIcon(icon);
        pbRotation->setIconSize(QSize(32, 32));

        horizontalLayout_5->addWidget(pbRotation);

        leStep = new QLineEdit(frame);
        leStep->setObjectName(QStringLiteral("leStep"));
        sizePolicy3.setHeightForWidth(leStep->sizePolicy().hasHeightForWidth());
        leStep->setSizePolicy(sizePolicy3);
        leStep->setMinimumSize(QSize(50, 0));
        leStep->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_5->addWidget(leStep);

        pbRotation2 = new QPushButton(frame);
        pbRotation2->setObjectName(QStringLiteral("pbRotation2"));
        sizePolicy3.setHeightForWidth(pbRotation2->sizePolicy().hasHeightForWidth());
        pbRotation2->setSizePolicy(sizePolicy3);
        pbRotation2->setMinimumSize(QSize(32, 32));
        pbRotation2->setMaximumSize(QSize(32, 32));
        pbRotation2->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Trainer/Resource/rotation1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbRotation2->setIcon(icon1);
        pbRotation2->setIconSize(QSize(32, 32));

        horizontalLayout_5->addWidget(pbRotation2);

        leAbsPos = new QLineEdit(frame);
        leAbsPos->setObjectName(QStringLiteral("leAbsPos"));
        sizePolicy3.setHeightForWidth(leAbsPos->sizePolicy().hasHeightForWidth());
        leAbsPos->setSizePolicy(sizePolicy3);
        leAbsPos->setMinimumSize(QSize(50, 0));
        leAbsPos->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_5->addWidget(leAbsPos);

        pbGo = new QPushButton(frame);
        pbGo->setObjectName(QStringLiteral("pbGo"));
        sizePolicy3.setHeightForWidth(pbGo->sizePolicy().hasHeightForWidth());
        pbGo->setSizePolicy(sizePolicy3);
        pbGo->setMinimumSize(QSize(32, 32));
        pbGo->setMaximumSize(QSize(32, 32));

        horizontalLayout_5->addWidget(pbGo);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_6->addWidget(label_2);

        cmbCameras = new QComboBox(frame);
        cmbCameras->setObjectName(QStringLiteral("cmbCameras"));
        sizePolicy3.setHeightForWidth(cmbCameras->sizePolicy().hasHeightForWidth());
        cmbCameras->setSizePolicy(sizePolicy3);
        cmbCameras->setMinimumSize(QSize(200, 0));

        horizontalLayout_6->addWidget(cmbCameras);

        pbSnap = new QPushButton(frame);
        pbSnap->setObjectName(QStringLiteral("pbSnap"));

        horizontalLayout_6->addWidget(pbSnap);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_6);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        slideLight1 = new QSlider(frame);
        slideLight1->setObjectName(QStringLiteral("slideLight1"));
        slideLight1->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slideLight1, 0, 0, 1, 1);

        slideLight2 = new QSlider(frame);
        slideLight2->setObjectName(QStringLiteral("slideLight2"));
        slideLight2->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slideLight2, 0, 1, 1, 1);

        slideLight5 = new QSlider(frame);
        slideLight5->setObjectName(QStringLiteral("slideLight5"));
        slideLight5->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slideLight5, 2, 0, 1, 1);

        slideLight4 = new QSlider(frame);
        slideLight4->setObjectName(QStringLiteral("slideLight4"));
        slideLight4->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slideLight4, 1, 1, 1, 1);

        slideLight8 = new QSlider(frame);
        slideLight8->setObjectName(QStringLiteral("slideLight8"));
        slideLight8->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slideLight8, 3, 1, 1, 1);

        slideLight7 = new QSlider(frame);
        slideLight7->setObjectName(QStringLiteral("slideLight7"));
        slideLight7->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slideLight7, 3, 0, 1, 1);

        slideLight6 = new QSlider(frame);
        slideLight6->setObjectName(QStringLiteral("slideLight6"));
        slideLight6->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slideLight6, 2, 1, 1, 1);

        slideLight3 = new QSlider(frame);
        slideLight3->setObjectName(QStringLiteral("slideLight3"));
        slideLight3->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slideLight3, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_7->addWidget(label_3);

        spinExposure = new QSpinBox(frame);
        spinExposure->setObjectName(QStringLiteral("spinExposure"));
        sizePolicy3.setHeightForWidth(spinExposure->sizePolicy().hasHeightForWidth());
        spinExposure->setSizePolicy(sizePolicy3);
        spinExposure->setMinimumSize(QSize(80, 0));
        spinExposure->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_7->addWidget(spinExposure);

        pbExposure = new QPushButton(frame);
        pbExposure->setObjectName(QStringLiteral("pbExposure"));

        horizontalLayout_7->addWidget(pbExposure);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_8->addWidget(label_4);

        spinGain = new QSpinBox(frame);
        spinGain->setObjectName(QStringLiteral("spinGain"));
        sizePolicy3.setHeightForWidth(spinGain->sizePolicy().hasHeightForWidth());
        spinGain->setSizePolicy(sizePolicy3);
        spinGain->setMinimumSize(QSize(80, 0));
        spinGain->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_8->addWidget(spinGain);

        pbGain = new QPushButton(frame);
        pbGain->setObjectName(QStringLiteral("pbGain"));

        horizontalLayout_8->addWidget(pbGain);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_10->addWidget(label_6);

        cmbDPI = new QComboBox(frame);
        cmbDPI->setObjectName(QStringLiteral("cmbDPI"));
        sizePolicy3.setHeightForWidth(cmbDPI->sizePolicy().hasHeightForWidth());
        cmbDPI->setSizePolicy(sizePolicy3);
        cmbDPI->setMinimumSize(QSize(200, 0));
        cmbDPI->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_10->addWidget(cmbDPI);

        pbParamSet = new QPushButton(frame);
        pbParamSet->setObjectName(QStringLiteral("pbParamSet"));

        horizontalLayout_10->addWidget(pbParamSet);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        leAutoStep = new QLineEdit(frame);
        leAutoStep->setObjectName(QStringLiteral("leAutoStep"));
        sizePolicy3.setHeightForWidth(leAutoStep->sizePolicy().hasHeightForWidth());
        leAutoStep->setSizePolicy(sizePolicy3);
        leAutoStep->setMinimumSize(QSize(50, 0));
        leAutoStep->setMaximumSize(QSize(100, 16777215));
        leAutoStep->setCursor(QCursor(Qt::IBeamCursor));
        leAutoStep->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_3->addWidget(leAutoStep);

        pbStart = new QPushButton(frame);
        pbStart->setObjectName(QStringLiteral("pbStart"));

        horizontalLayout_3->addWidget(pbStart);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_14);

        genPathLabel = new QLabel(frame);
        genPathLabel->setObjectName(QStringLiteral("genPathLabel"));

        horizontalLayout_3->addWidget(genPathLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        checkBox = new QCheckBox(frame);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_4->addWidget(checkBox);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_4->addWidget(pushButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        checkBox_2 = new QCheckBox(frame);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout_4->addWidget(checkBox_2);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(frame);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_9->addWidget(label_8);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_12);

        cmbClassify = new QComboBox(frame);
        cmbClassify->setObjectName(QStringLiteral("cmbClassify"));
        sizePolicy3.setHeightForWidth(cmbClassify->sizePolicy().hasHeightForWidth());
        cmbClassify->setSizePolicy(sizePolicy3);
        cmbClassify->setMinimumSize(QSize(200, 0));

        horizontalLayout_9->addWidget(cmbClassify);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_10);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_9->addWidget(pushButton_2);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_7);

        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_9->addWidget(pushButton_3);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_13);

        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_9->addWidget(pushButton_4);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_11);


        verticalLayout->addLayout(horizontalLayout_9);

        tableWidget = new QTableWidget(frame);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_11->addWidget(frame);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1386, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(checkBox, SIGNAL(stateChanged(int)), MainWindow, SLOT(isOpenAWB(int)));
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(setGainValue()));
        QObject::connect(checkBox_2, SIGNAL(clicked(bool)), MainWindow, SLOT(OpenOrCloseAWB(bool)));
        QObject::connect(pushButton_2, SIGNAL(clicked()), MainWindow, SLOT(addElement()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), MainWindow, SLOT(addItem()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), MainWindow, SLOT(clearItem()));
        QObject::connect(tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), MainWindow, SLOT(currentItem(QTableWidgetItem*)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        labCurPos->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\350\247\222\345\272\246:0\302\260", Q_NULLPTR));
        pbRotation->setText(QString());
        leStep->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        pbRotation2->setText(QString());
        leAbsPos->setText(QApplication::translate("MainWindow", "10", Q_NULLPTR));
        pbGo->setText(QApplication::translate("MainWindow", "Go", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\347\233\270\346\234\272:", Q_NULLPTR));
        pbSnap->setText(QApplication::translate("MainWindow", "\346\212\223\346\213\215", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\346\233\235\345\205\211:", Q_NULLPTR));
        pbExposure->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\345\242\236\347\233\212:", Q_NULLPTR));
        pbGain->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\345\210\206\350\276\250\347\216\207:", Q_NULLPTR));
        pbParamSet->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\346\227\213\350\275\254\346\255\245\351\225\277", Q_NULLPTR));
        leAutoStep->setText(QApplication::translate("MainWindow", "120", Q_NULLPTR));
        pbStart->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", Q_NULLPTR));
        genPathLabel->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\350\267\257\345\276\204:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\347\231\275\345\271\263\350\241\241:", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\350\207\252\345\212\250\350\256\241\347\256\227\347\231\275\345\271\263\350\241\241\345\217\202\346\225\260", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\233\272\345\256\232\346\240\207\345\256\232\345\217\202\346\225\260", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\347\231\275\345\271\263\350\241\241", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "\347\261\273\345\210\253:", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "\345\212\240\345\205\245", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
