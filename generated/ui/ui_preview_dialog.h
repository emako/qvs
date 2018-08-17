/********************************************************************************
** Form generated from reading UI file 'preview_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEW_DIALOG_H
#define UI_PREVIEW_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "./preview/timeline_slider.h"

QT_BEGIN_NAMESPACE

class Ui_PreviewDialog
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *previewArea;
    QHBoxLayout *horizontalLayout;
    QToolButton *timeLineCheckButton;
    QSpinBox *frameNumberSpinBox;
    TimeLineSlider *frameNumberSlider;
    QToolButton *frameToClipboardButton;
    QToolButton *saveSnapshotButton;
    QToolButton *zoomCheckButton;
    QComboBox *zoomModeComboBox;
    QDoubleSpinBox *zoomRatioSpinBox;
    QComboBox *scaleModeComboBox;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *playButton;
    QLabel *labelFpsLimitMode;
    QComboBox *playFpsLimitModeComboBox;
    QDoubleSpinBox *playFpsLimitSpinBox;
    QSpacerItem *horizontalSpacer;
    QLabel *timeLineModeLabel;
    QComboBox *timeLineModeComboBox;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PreviewDialog)
    {
        if (PreviewDialog->objectName().isEmpty())
            PreviewDialog->setObjectName(QStringLiteral("PreviewDialog"));
        PreviewDialog->resize(1007, 682);
        PreviewDialog->setAcceptDrops(true);
        centralWidget = new QWidget(PreviewDialog);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFocusPolicy(Qt::NoFocus);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1005, 569));
        scrollAreaWidgetContents->setFocusPolicy(Qt::NoFocus);
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        previewArea = new QLabel(scrollAreaWidgetContents);
        previewArea->setObjectName(QStringLiteral("previewArea"));
        previewArea->setFocusPolicy(Qt::NoFocus);
        previewArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(previewArea);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, -1, 2, -1);
        timeLineCheckButton = new QToolButton(centralWidget);
        timeLineCheckButton->setObjectName(QStringLiteral("timeLineCheckButton"));
        timeLineCheckButton->setFocusPolicy(Qt::ClickFocus);
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/timeline_frames.png"), QSize(), QIcon::Normal, QIcon::Off);
        timeLineCheckButton->setIcon(icon);
        timeLineCheckButton->setCheckable(true);

        horizontalLayout->addWidget(timeLineCheckButton);

        frameNumberSpinBox = new QSpinBox(centralWidget);
        frameNumberSpinBox->setObjectName(QStringLiteral("frameNumberSpinBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frameNumberSpinBox->sizePolicy().hasHeightForWidth());
        frameNumberSpinBox->setSizePolicy(sizePolicy);
        frameNumberSpinBox->setFocusPolicy(Qt::ClickFocus);
        frameNumberSpinBox->setKeyboardTracking(false);
        frameNumberSpinBox->setMaximum(999999999);

        horizontalLayout->addWidget(frameNumberSpinBox);

        frameNumberSlider = new TimeLineSlider(centralWidget);
        frameNumberSlider->setObjectName(QStringLiteral("frameNumberSlider"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frameNumberSlider->sizePolicy().hasHeightForWidth());
        frameNumberSlider->setSizePolicy(sizePolicy1);
        frameNumberSlider->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout->addWidget(frameNumberSlider);

        frameToClipboardButton = new QToolButton(centralWidget);
        frameToClipboardButton->setObjectName(QStringLiteral("frameToClipboardButton"));
        frameToClipboardButton->setFocusPolicy(Qt::ClickFocus);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/image_to_clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        frameToClipboardButton->setIcon(icon1);

        horizontalLayout->addWidget(frameToClipboardButton);

        saveSnapshotButton = new QToolButton(centralWidget);
        saveSnapshotButton->setObjectName(QStringLiteral("saveSnapshotButton"));
        saveSnapshotButton->setFocusPolicy(Qt::ClickFocus);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/buttons/picture_save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveSnapshotButton->setIcon(icon2);

        horizontalLayout->addWidget(saveSnapshotButton);

        zoomCheckButton = new QToolButton(centralWidget);
        zoomCheckButton->setObjectName(QStringLiteral("zoomCheckButton"));
        zoomCheckButton->setFocusPolicy(Qt::ClickFocus);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/buttons/zoom.png"), QSize(), QIcon::Normal, QIcon::Off);
        zoomCheckButton->setIcon(icon3);
        zoomCheckButton->setCheckable(true);
        zoomCheckButton->setChecked(true);

        horizontalLayout->addWidget(zoomCheckButton);

        zoomModeComboBox = new QComboBox(centralWidget);
        zoomModeComboBox->setObjectName(QStringLiteral("zoomModeComboBox"));
        sizePolicy.setHeightForWidth(zoomModeComboBox->sizePolicy().hasHeightForWidth());
        zoomModeComboBox->setSizePolicy(sizePolicy);
        zoomModeComboBox->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout->addWidget(zoomModeComboBox);

        zoomRatioSpinBox = new QDoubleSpinBox(centralWidget);
        zoomRatioSpinBox->setObjectName(QStringLiteral("zoomRatioSpinBox"));
        zoomRatioSpinBox->setFocusPolicy(Qt::ClickFocus);
        zoomRatioSpinBox->setKeyboardTracking(false);
        zoomRatioSpinBox->setMinimum(0.01);
        zoomRatioSpinBox->setMaximum(1024);
        zoomRatioSpinBox->setSingleStep(0.1);
        zoomRatioSpinBox->setValue(2);

        horizontalLayout->addWidget(zoomRatioSpinBox);

        scaleModeComboBox = new QComboBox(centralWidget);
        scaleModeComboBox->setObjectName(QStringLiteral("scaleModeComboBox"));
        scaleModeComboBox->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout->addWidget(scaleModeComboBox);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, -1, 2, -1);
        playButton = new QToolButton(centralWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setFocusPolicy(Qt::ClickFocus);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/buttons/play_green.png"), QSize(), QIcon::Normal, QIcon::Off);
        playButton->setIcon(icon4);
        playButton->setCheckable(true);

        horizontalLayout_2->addWidget(playButton);

        labelFpsLimitMode = new QLabel(centralWidget);
        labelFpsLimitMode->setObjectName(QStringLiteral("labelFpsLimitMode"));
        labelFpsLimitMode->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_2->addWidget(labelFpsLimitMode);

        playFpsLimitModeComboBox = new QComboBox(centralWidget);
        playFpsLimitModeComboBox->setObjectName(QStringLiteral("playFpsLimitModeComboBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(playFpsLimitModeComboBox->sizePolicy().hasHeightForWidth());
        playFpsLimitModeComboBox->setSizePolicy(sizePolicy2);
        playFpsLimitModeComboBox->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_2->addWidget(playFpsLimitModeComboBox);

        playFpsLimitSpinBox = new QDoubleSpinBox(centralWidget);
        playFpsLimitSpinBox->setObjectName(QStringLiteral("playFpsLimitSpinBox"));
        playFpsLimitSpinBox->setFocusPolicy(Qt::ClickFocus);
        playFpsLimitSpinBox->setDecimals(5);
        playFpsLimitSpinBox->setMaximum(100000);
        playFpsLimitSpinBox->setValue(24);

        horizontalLayout_2->addWidget(playFpsLimitSpinBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        timeLineModeLabel = new QLabel(centralWidget);
        timeLineModeLabel->setObjectName(QStringLiteral("timeLineModeLabel"));
        timeLineModeLabel->setFocusPolicy(Qt::ClickFocus);
        timeLineModeLabel->setMargin(2);

        horizontalLayout_2->addWidget(timeLineModeLabel);

        timeLineModeComboBox = new QComboBox(centralWidget);
        timeLineModeComboBox->setObjectName(QStringLiteral("timeLineModeComboBox"));
        sizePolicy.setHeightForWidth(timeLineModeComboBox->sizePolicy().hasHeightForWidth());
        timeLineModeComboBox->setSizePolicy(sizePolicy);
        timeLineModeComboBox->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_2->addWidget(timeLineModeComboBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        PreviewDialog->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PreviewDialog);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1007, 26));
        PreviewDialog->setMenuBar(menuBar);
        statusBar = new QStatusBar(PreviewDialog);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PreviewDialog->setStatusBar(statusBar);

        retranslateUi(PreviewDialog);

        QMetaObject::connectSlotsByName(PreviewDialog);
    } // setupUi

    void retranslateUi(QMainWindow *PreviewDialog)
    {
        PreviewDialog->setWindowTitle(QApplication::translate("PreviewDialog", "Preview", nullptr));
        previewArea->setText(QString());
#ifndef QT_NO_TOOLTIP
        timeLineCheckButton->setToolTip(QApplication::translate("PreviewDialog", "Timeline", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        frameToClipboardButton->setToolTip(QApplication::translate("PreviewDialog", "Copy frame to clipboard", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        saveSnapshotButton->setToolTip(QApplication::translate("PreviewDialog", "Save snapshot", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        zoomCheckButton->setToolTip(QApplication::translate("PreviewDialog", "Zoom", nullptr));
#endif // QT_NO_TOOLTIP
        zoomRatioSpinBox->setPrefix(QApplication::translate("PreviewDialog", "x", nullptr));
        playButton->setText(QString());
        labelFpsLimitMode->setText(QApplication::translate("PreviewDialog", "FPS limit mode:", nullptr));
        timeLineModeLabel->setText(QApplication::translate("PreviewDialog", "Timeline display mode:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PreviewDialog: public Ui_PreviewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEW_DIALOG_H
