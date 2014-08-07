/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created: Sun May 4 16:49:09 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_Save;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_4;
    QFrame *operationFrame;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *operationLabel;
    QListWidget *operationListBox;
    QGroupBox *parameterGroupBox;
    QGridLayout *parametersLayout;
    QVBoxLayout *verticalLayout_4;
    QWidget *rightSideFrame;
    QVBoxLayout *verticalLayout_3;
    QFrame *imageFrame;
    QHBoxLayout *horizontalLayout_2;
    QFrame *imagePositionAndValueFrame;
    QHBoxLayout *horizontalLayout;
    QSlider *threeDFramePositionSlider;
    QLabel *threeDFramePositionLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *positionLabel;
    QLabel *rowPositionLabel;
    QLabel *columnPositionLabel;
    QLabel *label;
    QLabel *imageValueLabel;
    QFrame *buttonFrame;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *swapButton;
    QPushButton *applyButton;
    QMenuBar *menubar;
    QMenu *menuEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(732, 567);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_4 = new QHBoxLayout(centralwidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        operationFrame = new QFrame(centralwidget);
        operationFrame->setObjectName(QString::fromUtf8("operationFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(operationFrame->sizePolicy().hasHeightForWidth());
        operationFrame->setSizePolicy(sizePolicy);
        operationFrame->setFrameShape(QFrame::NoFrame);
        operationFrame->setFrameShadow(QFrame::Raised);
        operationFrame->setLineWidth(1);
        verticalLayout_2 = new QVBoxLayout(operationFrame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        operationLabel = new QLabel(operationFrame);
        operationLabel->setObjectName(QString::fromUtf8("operationLabel"));

        verticalLayout->addWidget(operationLabel);

        operationListBox = new QListWidget(operationFrame);
        operationListBox->setObjectName(QString::fromUtf8("operationListBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(operationListBox->sizePolicy().hasHeightForWidth());
        operationListBox->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(operationListBox);

        parameterGroupBox = new QGroupBox(operationFrame);
        parameterGroupBox->setObjectName(QString::fromUtf8("parameterGroupBox"));
        parametersLayout = new QGridLayout(parameterGroupBox);
        parametersLayout->setObjectName(QString::fromUtf8("parametersLayout"));

        verticalLayout->addWidget(parameterGroupBox);


        verticalLayout_2->addLayout(verticalLayout);


        horizontalLayout_4->addWidget(operationFrame);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, -1, -1, 0);
        rightSideFrame = new QWidget(centralwidget);
        rightSideFrame->setObjectName(QString::fromUtf8("rightSideFrame"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(rightSideFrame->sizePolicy().hasHeightForWidth());
        rightSideFrame->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(rightSideFrame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        imageFrame = new QFrame(rightSideFrame);
        imageFrame->setObjectName(QString::fromUtf8("imageFrame"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(imageFrame->sizePolicy().hasHeightForWidth());
        imageFrame->setSizePolicy(sizePolicy3);
        imageFrame->setFrameShape(QFrame::NoFrame);
        imageFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(imageFrame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout_3->addWidget(imageFrame);

        imagePositionAndValueFrame = new QFrame(rightSideFrame);
        imagePositionAndValueFrame->setObjectName(QString::fromUtf8("imagePositionAndValueFrame"));
        imagePositionAndValueFrame->setFrameShape(QFrame::NoFrame);
        imagePositionAndValueFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(imagePositionAndValueFrame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        threeDFramePositionSlider = new QSlider(imagePositionAndValueFrame);
        threeDFramePositionSlider->setObjectName(QString::fromUtf8("threeDFramePositionSlider"));
        threeDFramePositionSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(threeDFramePositionSlider);

        threeDFramePositionLabel = new QLabel(imagePositionAndValueFrame);
        threeDFramePositionLabel->setObjectName(QString::fromUtf8("threeDFramePositionLabel"));

        horizontalLayout->addWidget(threeDFramePositionLabel);

        horizontalSpacer = new QSpacerItem(19, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        positionLabel = new QLabel(imagePositionAndValueFrame);
        positionLabel->setObjectName(QString::fromUtf8("positionLabel"));

        horizontalLayout->addWidget(positionLabel);

        rowPositionLabel = new QLabel(imagePositionAndValueFrame);
        rowPositionLabel->setObjectName(QString::fromUtf8("rowPositionLabel"));
        rowPositionLabel->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(rowPositionLabel);

        columnPositionLabel = new QLabel(imagePositionAndValueFrame);
        columnPositionLabel->setObjectName(QString::fromUtf8("columnPositionLabel"));
        columnPositionLabel->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(columnPositionLabel);

        label = new QLabel(imagePositionAndValueFrame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        imageValueLabel = new QLabel(imagePositionAndValueFrame);
        imageValueLabel->setObjectName(QString::fromUtf8("imageValueLabel"));
        imageValueLabel->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(imageValueLabel);


        verticalLayout_3->addWidget(imagePositionAndValueFrame);

        buttonFrame = new QFrame(rightSideFrame);
        buttonFrame->setObjectName(QString::fromUtf8("buttonFrame"));
        buttonFrame->setFrameShape(QFrame::NoFrame);
        buttonFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(buttonFrame);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        swapButton = new QPushButton(buttonFrame);
        swapButton->setObjectName(QString::fromUtf8("swapButton"));
        swapButton->setMinimumSize(QSize(130, 60));

        horizontalLayout_3->addWidget(swapButton);

        applyButton = new QPushButton(buttonFrame);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));
        applyButton->setMinimumSize(QSize(130, 60));

        horizontalLayout_3->addWidget(applyButton);


        verticalLayout_3->addWidget(buttonFrame);


        verticalLayout_4->addWidget(rightSideFrame);


        horizontalLayout_4->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 732, 25));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuEdit->menuAction());
        menuEdit->addAction(action_Open);
        menuEdit->addAction(action_Save);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "IFS Operations Viewer", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "&Open IFS Image", 0, QApplication::UnicodeUTF8));
        action_Save->setText(QApplication::translate("MainWindow", " &Save IFS Image", 0, QApplication::UnicodeUTF8));
        operationLabel->setText(QApplication::translate("MainWindow", "Operation:", 0, QApplication::UnicodeUTF8));
        parameterGroupBox->setTitle(QApplication::translate("MainWindow", "Parameters", 0, QApplication::UnicodeUTF8));
        threeDFramePositionLabel->setText(QApplication::translate("MainWindow", "frameValue", 0, QApplication::UnicodeUTF8));
        positionLabel->setText(QApplication::translate("MainWindow", "Position:", 0, QApplication::UnicodeUTF8));
        rowPositionLabel->setText(QString());
        columnPositionLabel->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Value:", 0, QApplication::UnicodeUTF8));
        imageValueLabel->setText(QString());
        swapButton->setText(QApplication::translate("MainWindow", "Swap", 0, QApplication::UnicodeUTF8));
        applyButton->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
