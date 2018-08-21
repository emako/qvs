/********************************************************************************
** Form generated from reading UI file 'audio_config.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIO_CONFIG_H
#define UI_AUDIO_CONFIG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioConfig
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBoxConfig;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutTemplate;
    QLabel *labelTemplate;
    QComboBox *comboBoxTemplate;
    QSpacerItem *horizontalSpacerTemplate;
    QPushButton *buttonSaveTemplate;
    QPushButton *buttonDeleteTemplate;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelAudioEncoder;
    QComboBox *comboBoxAudioEncoder;
    QSpacerItem *horizontalSpacerEncoder;
    QStackedWidget *stackedWidgetMode;
    QWidget *page_qaac;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBoxAacApple;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelAacAppleMode;
    QComboBox *comboBoxAacAppleMode;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QSlider *horizontalSliderAacApple;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_6;
    QLabel *labelAacAppleProfile;
    QComboBox *comboBoxAacAppleProfile;
    QCheckBox *checkBoxAacAppleNoDelay;
    QSpacerItem *horizontalSpacer_5;
    QWidget *page_fdkaac;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBoxAacFdk;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_8;
    QLabel *labelAacFdkMode;
    QComboBox *comboBoxAacFdkMode;
    QSpacerItem *horizontalSpacer_7;
    QSlider *horizontalSliderAacFdk;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_9;
    QLabel *labelAacFdkProfile;
    QComboBox *comboBoxAacFdkProfile;
    QSpacerItem *horizontalSpacer_10;
    QWidget *page_neroaac;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBoxAacNero;
    QVBoxLayout *verticalLayout_8;
    QSlider *horizontalSliderAacNero;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_11;
    QLabel *labelAacNeroProfile;
    QComboBox *comboBoxAacNeroProfile;
    QSpacerItem *horizontalSpacer_12;
    QWidget *page_alac;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBoxAlac;
    QWidget *page_flac;
    QVBoxLayout *verticalLayout_10;
    QGroupBox *groupBoxFlac;
    QVBoxLayout *verticalLayout_11;
    QSlider *horizontalSliderFlac;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelFlacFast;
    QSpacerItem *horizontalSpacer_13;
    QLabel *labelFlacSlow;
    QWidget *page_opus;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *groupBoxOpus;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_14;
    QLabel *labelOpusMode;
    QComboBox *comboBoxOpusMode;
    QSpacerItem *horizontalSpacer_15;
    QSlider *horizontalSliderOpus;
    QWidget *page_vorbis;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *groupBoxOggVorbis;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelOggVorbisVariableBitrate;
    QSpacerItem *horizontalSpacer_16;
    QSlider *horizontalSliderOggVorbis;
    QWidget *page_mp3;
    QVBoxLayout *verticalLayout_18;
    QGroupBox *groupBoxMp3;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_17;
    QLabel *labelMp3Mode;
    QComboBox *comboBoxMp3Mode;
    QSpacerItem *horizontalSpacer_18;
    QSlider *horizontalSliderMp3;
    QWidget *page_ac3;
    QVBoxLayout *verticalLayout_19;
    QGroupBox *groupBoxAc3;
    QVBoxLayout *verticalLayout_17;
    QHBoxLayout *horizontalLayout_12;
    QLabel *labelAc3Bitrate;
    QSpacerItem *horizontalSpacer_19;
    QSlider *horizontalSliderAc3;
    QWidget *page_wav;
    QVBoxLayout *verticalLayout_20;
    QGroupBox *groupBoxWav;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxAdvancedOption;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonAccept;
    QPushButton *buttonCancel;

    void setupUi(QWidget *AudioConfig)
    {
        if (AudioConfig->objectName().isEmpty())
            AudioConfig->setObjectName(QStringLiteral("AudioConfig"));
        AudioConfig->resize(548, 324);
        verticalLayout_2 = new QVBoxLayout(AudioConfig);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBoxConfig = new QGroupBox(AudioConfig);
        groupBoxConfig->setObjectName(QStringLiteral("groupBoxConfig"));
        verticalLayout = new QVBoxLayout(groupBoxConfig);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayoutTemplate = new QHBoxLayout();
        horizontalLayoutTemplate->setSpacing(8);
        horizontalLayoutTemplate->setObjectName(QStringLiteral("horizontalLayoutTemplate"));
        labelTemplate = new QLabel(groupBoxConfig);
        labelTemplate->setObjectName(QStringLiteral("labelTemplate"));
        labelTemplate->setMinimumSize(QSize(80, 0));
        labelTemplate->setMaximumSize(QSize(80, 16777215));

        horizontalLayoutTemplate->addWidget(labelTemplate);

        comboBoxTemplate = new QComboBox(groupBoxConfig);
        comboBoxTemplate->setObjectName(QStringLiteral("comboBoxTemplate"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxTemplate->sizePolicy().hasHeightForWidth());
        comboBoxTemplate->setSizePolicy(sizePolicy);
        comboBoxTemplate->setMinimumSize(QSize(200, 23));
        comboBoxTemplate->setMaximumSize(QSize(16777215, 16777215));
        comboBoxTemplate->setEditable(true);

        horizontalLayoutTemplate->addWidget(comboBoxTemplate);

        horizontalSpacerTemplate = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayoutTemplate->addItem(horizontalSpacerTemplate);

        buttonSaveTemplate = new QPushButton(groupBoxConfig);
        buttonSaveTemplate->setObjectName(QStringLiteral("buttonSaveTemplate"));
        buttonSaveTemplate->setMinimumSize(QSize(90, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSaveTemplate->setIcon(icon);

        horizontalLayoutTemplate->addWidget(buttonSaveTemplate);

        buttonDeleteTemplate = new QPushButton(groupBoxConfig);
        buttonDeleteTemplate->setObjectName(QStringLiteral("buttonDeleteTemplate"));
        buttonDeleteTemplate->setMinimumSize(QSize(90, 0));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/cross.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDeleteTemplate->setIcon(icon1);

        horizontalLayoutTemplate->addWidget(buttonDeleteTemplate);


        verticalLayout->addLayout(horizontalLayoutTemplate);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(8);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelAudioEncoder = new QLabel(groupBoxConfig);
        labelAudioEncoder->setObjectName(QStringLiteral("labelAudioEncoder"));
        labelAudioEncoder->setMinimumSize(QSize(80, 0));
        labelAudioEncoder->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(labelAudioEncoder);

        comboBoxAudioEncoder = new QComboBox(groupBoxConfig);
        comboBoxAudioEncoder->addItem(QString());
        comboBoxAudioEncoder->addItem(QString());
        comboBoxAudioEncoder->addItem(QString());
        comboBoxAudioEncoder->addItem(QString());
        comboBoxAudioEncoder->addItem(QString());
        comboBoxAudioEncoder->addItem(QString());
        comboBoxAudioEncoder->addItem(QString());
        comboBoxAudioEncoder->addItem(QString());
        comboBoxAudioEncoder->addItem(QString());
        comboBoxAudioEncoder->addItem(QString());
        comboBoxAudioEncoder->setObjectName(QStringLiteral("comboBoxAudioEncoder"));
        sizePolicy.setHeightForWidth(comboBoxAudioEncoder->sizePolicy().hasHeightForWidth());
        comboBoxAudioEncoder->setSizePolicy(sizePolicy);
        comboBoxAudioEncoder->setMinimumSize(QSize(200, 23));
        comboBoxAudioEncoder->setMaximumSize(QSize(16777215, 16777215));
        comboBoxAudioEncoder->setEditable(true);

        horizontalLayout_2->addWidget(comboBoxAudioEncoder);

        horizontalSpacerEncoder = new QSpacerItem(40, 29, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacerEncoder);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(groupBoxConfig);

        stackedWidgetMode = new QStackedWidget(AudioConfig);
        stackedWidgetMode->setObjectName(QStringLiteral("stackedWidgetMode"));
        page_qaac = new QWidget();
        page_qaac->setObjectName(QStringLiteral("page_qaac"));
        verticalLayout_3 = new QVBoxLayout(page_qaac);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBoxAacApple = new QGroupBox(page_qaac);
        groupBoxAacApple->setObjectName(QStringLiteral("groupBoxAacApple"));
        verticalLayout_4 = new QVBoxLayout(groupBoxAacApple);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        labelAacAppleMode = new QLabel(groupBoxAacApple);
        labelAacAppleMode->setObjectName(QStringLiteral("labelAacAppleMode"));
        labelAacAppleMode->setMinimumSize(QSize(80, 0));
        labelAacAppleMode->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(labelAacAppleMode);

        comboBoxAacAppleMode = new QComboBox(groupBoxAacApple);
        comboBoxAacAppleMode->setObjectName(QStringLiteral("comboBoxAacAppleMode"));
        sizePolicy.setHeightForWidth(comboBoxAacAppleMode->sizePolicy().hasHeightForWidth());
        comboBoxAacAppleMode->setSizePolicy(sizePolicy);
        comboBoxAacAppleMode->setMinimumSize(QSize(180, 23));
        comboBoxAacAppleMode->setMaximumSize(QSize(16777215, 16777215));
        comboBoxAacAppleMode->setEditable(true);

        horizontalLayout_4->addWidget(comboBoxAacAppleMode);

        horizontalSpacer_4 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSliderAacApple = new QSlider(groupBoxAacApple);
        horizontalSliderAacApple->setObjectName(QStringLiteral("horizontalSliderAacApple"));
        horizontalSliderAacApple->setOrientation(Qt::Horizontal);
        horizontalSliderAacApple->setInvertedAppearance(false);
        horizontalSliderAacApple->setInvertedControls(false);
        horizontalSliderAacApple->setTickPosition(QSlider::TicksAbove);
        horizontalSliderAacApple->setTickInterval(10);

        horizontalLayout_5->addWidget(horizontalSliderAacApple);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        labelAacAppleProfile = new QLabel(groupBoxAacApple);
        labelAacAppleProfile->setObjectName(QStringLiteral("labelAacAppleProfile"));
        labelAacAppleProfile->setMinimumSize(QSize(80, 0));
        labelAacAppleProfile->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(labelAacAppleProfile);

        comboBoxAacAppleProfile = new QComboBox(groupBoxAacApple);
        comboBoxAacAppleProfile->addItem(QString());
        comboBoxAacAppleProfile->addItem(QString());
        comboBoxAacAppleProfile->setObjectName(QStringLiteral("comboBoxAacAppleProfile"));
        sizePolicy.setHeightForWidth(comboBoxAacAppleProfile->sizePolicy().hasHeightForWidth());
        comboBoxAacAppleProfile->setSizePolicy(sizePolicy);
        comboBoxAacAppleProfile->setMinimumSize(QSize(180, 23));
        comboBoxAacAppleProfile->setMaximumSize(QSize(16777215, 16777215));
        comboBoxAacAppleProfile->setEditable(true);

        horizontalLayout_3->addWidget(comboBoxAacAppleProfile);

        checkBoxAacAppleNoDelay = new QCheckBox(groupBoxAacApple);
        checkBoxAacAppleNoDelay->setObjectName(QStringLiteral("checkBoxAacAppleNoDelay"));

        horizontalLayout_3->addWidget(checkBoxAacAppleNoDelay);

        horizontalSpacer_5 = new QSpacerItem(40, 17, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(groupBoxAacApple);

        stackedWidgetMode->addWidget(page_qaac);
        page_fdkaac = new QWidget();
        page_fdkaac->setObjectName(QStringLiteral("page_fdkaac"));
        verticalLayout_5 = new QVBoxLayout(page_fdkaac);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        groupBoxAacFdk = new QGroupBox(page_fdkaac);
        groupBoxAacFdk->setObjectName(QStringLiteral("groupBoxAacFdk"));
        verticalLayout_6 = new QVBoxLayout(groupBoxAacFdk);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);

        labelAacFdkMode = new QLabel(groupBoxAacFdk);
        labelAacFdkMode->setObjectName(QStringLiteral("labelAacFdkMode"));
        labelAacFdkMode->setMinimumSize(QSize(80, 0));
        labelAacFdkMode->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_6->addWidget(labelAacFdkMode);

        comboBoxAacFdkMode = new QComboBox(groupBoxAacFdk);
        comboBoxAacFdkMode->addItem(QString());
        comboBoxAacFdkMode->addItem(QString());
        comboBoxAacFdkMode->setObjectName(QStringLiteral("comboBoxAacFdkMode"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBoxAacFdkMode->sizePolicy().hasHeightForWidth());
        comboBoxAacFdkMode->setSizePolicy(sizePolicy1);
        comboBoxAacFdkMode->setMinimumSize(QSize(180, 23));
        comboBoxAacFdkMode->setMaximumSize(QSize(16777215, 16777215));
        comboBoxAacFdkMode->setEditable(true);

        horizontalLayout_6->addWidget(comboBoxAacFdkMode);

        horizontalSpacer_7 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        verticalLayout_6->addLayout(horizontalLayout_6);

        horizontalSliderAacFdk = new QSlider(groupBoxAacFdk);
        horizontalSliderAacFdk->setObjectName(QStringLiteral("horizontalSliderAacFdk"));
        horizontalSliderAacFdk->setOrientation(Qt::Horizontal);
        horizontalSliderAacFdk->setInvertedAppearance(false);
        horizontalSliderAacFdk->setInvertedControls(false);
        horizontalSliderAacFdk->setTickPosition(QSlider::TicksAbove);
        horizontalSliderAacFdk->setTickInterval(10);

        verticalLayout_6->addWidget(horizontalSliderAacFdk);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_9);

        labelAacFdkProfile = new QLabel(groupBoxAacFdk);
        labelAacFdkProfile->setObjectName(QStringLiteral("labelAacFdkProfile"));
        labelAacFdkProfile->setMinimumSize(QSize(80, 0));
        labelAacFdkProfile->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_13->addWidget(labelAacFdkProfile);

        comboBoxAacFdkProfile = new QComboBox(groupBoxAacFdk);
        comboBoxAacFdkProfile->addItem(QString());
        comboBoxAacFdkProfile->addItem(QString());
        comboBoxAacFdkProfile->addItem(QString());
        comboBoxAacFdkProfile->addItem(QString());
        comboBoxAacFdkProfile->addItem(QString());
        comboBoxAacFdkProfile->addItem(QString());
        comboBoxAacFdkProfile->addItem(QString());
        comboBoxAacFdkProfile->addItem(QString());
        comboBoxAacFdkProfile->setObjectName(QStringLiteral("comboBoxAacFdkProfile"));
        sizePolicy1.setHeightForWidth(comboBoxAacFdkProfile->sizePolicy().hasHeightForWidth());
        comboBoxAacFdkProfile->setSizePolicy(sizePolicy1);
        comboBoxAacFdkProfile->setMinimumSize(QSize(180, 23));
        comboBoxAacFdkProfile->setMaximumSize(QSize(16777215, 16777215));
        comboBoxAacFdkProfile->setEditable(true);

        horizontalLayout_13->addWidget(comboBoxAacFdkProfile);

        horizontalSpacer_10 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_10);


        verticalLayout_6->addLayout(horizontalLayout_13);


        verticalLayout_5->addWidget(groupBoxAacFdk);

        stackedWidgetMode->addWidget(page_fdkaac);
        page_neroaac = new QWidget();
        page_neroaac->setObjectName(QStringLiteral("page_neroaac"));
        verticalLayout_7 = new QVBoxLayout(page_neroaac);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        groupBoxAacNero = new QGroupBox(page_neroaac);
        groupBoxAacNero->setObjectName(QStringLiteral("groupBoxAacNero"));
        verticalLayout_8 = new QVBoxLayout(groupBoxAacNero);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalSliderAacNero = new QSlider(groupBoxAacNero);
        horizontalSliderAacNero->setObjectName(QStringLiteral("horizontalSliderAacNero"));
        horizontalSliderAacNero->setOrientation(Qt::Horizontal);
        horizontalSliderAacNero->setInvertedAppearance(false);
        horizontalSliderAacNero->setInvertedControls(false);
        horizontalSliderAacNero->setTickPosition(QSlider::TicksAbove);
        horizontalSliderAacNero->setTickInterval(10);

        verticalLayout_8->addWidget(horizontalSliderAacNero);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);

        labelAacNeroProfile = new QLabel(groupBoxAacNero);
        labelAacNeroProfile->setObjectName(QStringLiteral("labelAacNeroProfile"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelAacNeroProfile->sizePolicy().hasHeightForWidth());
        labelAacNeroProfile->setSizePolicy(sizePolicy2);
        labelAacNeroProfile->setMinimumSize(QSize(80, 0));
        labelAacNeroProfile->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_7->addWidget(labelAacNeroProfile);

        comboBoxAacNeroProfile = new QComboBox(groupBoxAacNero);
        comboBoxAacNeroProfile->addItem(QString());
        comboBoxAacNeroProfile->addItem(QString());
        comboBoxAacNeroProfile->addItem(QString());
        comboBoxAacNeroProfile->setObjectName(QStringLiteral("comboBoxAacNeroProfile"));
        sizePolicy.setHeightForWidth(comboBoxAacNeroProfile->sizePolicy().hasHeightForWidth());
        comboBoxAacNeroProfile->setSizePolicy(sizePolicy);
        comboBoxAacNeroProfile->setMinimumSize(QSize(180, 23));
        comboBoxAacNeroProfile->setMaximumSize(QSize(16777215, 16777215));
        comboBoxAacNeroProfile->setEditable(true);

        horizontalLayout_7->addWidget(comboBoxAacNeroProfile);

        horizontalSpacer_12 = new QSpacerItem(100, 17, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_12);


        verticalLayout_8->addLayout(horizontalLayout_7);


        verticalLayout_7->addWidget(groupBoxAacNero);

        stackedWidgetMode->addWidget(page_neroaac);
        page_alac = new QWidget();
        page_alac->setObjectName(QStringLiteral("page_alac"));
        verticalLayout_9 = new QVBoxLayout(page_alac);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        groupBoxAlac = new QGroupBox(page_alac);
        groupBoxAlac->setObjectName(QStringLiteral("groupBoxAlac"));

        verticalLayout_9->addWidget(groupBoxAlac);

        stackedWidgetMode->addWidget(page_alac);
        page_flac = new QWidget();
        page_flac->setObjectName(QStringLiteral("page_flac"));
        verticalLayout_10 = new QVBoxLayout(page_flac);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        groupBoxFlac = new QGroupBox(page_flac);
        groupBoxFlac->setObjectName(QStringLiteral("groupBoxFlac"));
        verticalLayout_11 = new QVBoxLayout(groupBoxFlac);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalSliderFlac = new QSlider(groupBoxFlac);
        horizontalSliderFlac->setObjectName(QStringLiteral("horizontalSliderFlac"));
        horizontalSliderFlac->setOrientation(Qt::Horizontal);
        horizontalSliderFlac->setInvertedAppearance(false);
        horizontalSliderFlac->setInvertedControls(false);
        horizontalSliderFlac->setTickPosition(QSlider::TicksAbove);
        horizontalSliderFlac->setTickInterval(10);

        verticalLayout_11->addWidget(horizontalSliderFlac);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        labelFlacFast = new QLabel(groupBoxFlac);
        labelFlacFast->setObjectName(QStringLiteral("labelFlacFast"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelFlacFast->sizePolicy().hasHeightForWidth());
        labelFlacFast->setSizePolicy(sizePolicy3);

        horizontalLayout_8->addWidget(labelFlacFast);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);

        labelFlacSlow = new QLabel(groupBoxFlac);
        labelFlacSlow->setObjectName(QStringLiteral("labelFlacSlow"));
        sizePolicy3.setHeightForWidth(labelFlacSlow->sizePolicy().hasHeightForWidth());
        labelFlacSlow->setSizePolicy(sizePolicy3);

        horizontalLayout_8->addWidget(labelFlacSlow);


        verticalLayout_11->addLayout(horizontalLayout_8);


        verticalLayout_10->addWidget(groupBoxFlac);

        stackedWidgetMode->addWidget(page_flac);
        page_opus = new QWidget();
        page_opus->setObjectName(QStringLiteral("page_opus"));
        verticalLayout_12 = new QVBoxLayout(page_opus);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        groupBoxOpus = new QGroupBox(page_opus);
        groupBoxOpus->setObjectName(QStringLiteral("groupBoxOpus"));
        verticalLayout_13 = new QVBoxLayout(groupBoxOpus);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_14);

        labelOpusMode = new QLabel(groupBoxOpus);
        labelOpusMode->setObjectName(QStringLiteral("labelOpusMode"));
        sizePolicy3.setHeightForWidth(labelOpusMode->sizePolicy().hasHeightForWidth());
        labelOpusMode->setSizePolicy(sizePolicy3);
        labelOpusMode->setMinimumSize(QSize(80, 0));
        labelOpusMode->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_9->addWidget(labelOpusMode);

        comboBoxOpusMode = new QComboBox(groupBoxOpus);
        comboBoxOpusMode->addItem(QString());
        comboBoxOpusMode->addItem(QString());
        comboBoxOpusMode->addItem(QString());
        comboBoxOpusMode->setObjectName(QStringLiteral("comboBoxOpusMode"));
        sizePolicy.setHeightForWidth(comboBoxOpusMode->sizePolicy().hasHeightForWidth());
        comboBoxOpusMode->setSizePolicy(sizePolicy);
        comboBoxOpusMode->setMinimumSize(QSize(180, 23));
        comboBoxOpusMode->setMaximumSize(QSize(16777215, 16777215));
        comboBoxOpusMode->setEditable(true);

        horizontalLayout_9->addWidget(comboBoxOpusMode);

        horizontalSpacer_15 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_15);


        verticalLayout_13->addLayout(horizontalLayout_9);

        horizontalSliderOpus = new QSlider(groupBoxOpus);
        horizontalSliderOpus->setObjectName(QStringLiteral("horizontalSliderOpus"));
        horizontalSliderOpus->setOrientation(Qt::Horizontal);
        horizontalSliderOpus->setInvertedAppearance(false);
        horizontalSliderOpus->setInvertedControls(false);
        horizontalSliderOpus->setTickPosition(QSlider::TicksAbove);
        horizontalSliderOpus->setTickInterval(10);

        verticalLayout_13->addWidget(horizontalSliderOpus);


        verticalLayout_12->addWidget(groupBoxOpus);

        stackedWidgetMode->addWidget(page_opus);
        page_vorbis = new QWidget();
        page_vorbis->setObjectName(QStringLiteral("page_vorbis"));
        verticalLayout_14 = new QVBoxLayout(page_vorbis);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        groupBoxOggVorbis = new QGroupBox(page_vorbis);
        groupBoxOggVorbis->setObjectName(QStringLiteral("groupBoxOggVorbis"));
        verticalLayout_15 = new QVBoxLayout(groupBoxOggVorbis);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        labelOggVorbisVariableBitrate = new QLabel(groupBoxOggVorbis);
        labelOggVorbisVariableBitrate->setObjectName(QStringLiteral("labelOggVorbisVariableBitrate"));
        sizePolicy3.setHeightForWidth(labelOggVorbisVariableBitrate->sizePolicy().hasHeightForWidth());
        labelOggVorbisVariableBitrate->setSizePolicy(sizePolicy3);

        horizontalLayout_10->addWidget(labelOggVorbisVariableBitrate);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_16);


        verticalLayout_15->addLayout(horizontalLayout_10);

        horizontalSliderOggVorbis = new QSlider(groupBoxOggVorbis);
        horizontalSliderOggVorbis->setObjectName(QStringLiteral("horizontalSliderOggVorbis"));
        horizontalSliderOggVorbis->setOrientation(Qt::Horizontal);
        horizontalSliderOggVorbis->setInvertedAppearance(false);
        horizontalSliderOggVorbis->setInvertedControls(false);
        horizontalSliderOggVorbis->setTickPosition(QSlider::TicksAbove);
        horizontalSliderOggVorbis->setTickInterval(10);

        verticalLayout_15->addWidget(horizontalSliderOggVorbis);


        verticalLayout_14->addWidget(groupBoxOggVorbis);

        stackedWidgetMode->addWidget(page_vorbis);
        page_mp3 = new QWidget();
        page_mp3->setObjectName(QStringLiteral("page_mp3"));
        verticalLayout_18 = new QVBoxLayout(page_mp3);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        groupBoxMp3 = new QGroupBox(page_mp3);
        groupBoxMp3->setObjectName(QStringLiteral("groupBoxMp3"));
        verticalLayout_16 = new QVBoxLayout(groupBoxMp3);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_17);

        labelMp3Mode = new QLabel(groupBoxMp3);
        labelMp3Mode->setObjectName(QStringLiteral("labelMp3Mode"));
        sizePolicy3.setHeightForWidth(labelMp3Mode->sizePolicy().hasHeightForWidth());
        labelMp3Mode->setSizePolicy(sizePolicy3);
        labelMp3Mode->setMinimumSize(QSize(80, 0));
        labelMp3Mode->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_11->addWidget(labelMp3Mode);

        comboBoxMp3Mode = new QComboBox(groupBoxMp3);
        comboBoxMp3Mode->addItem(QString());
        comboBoxMp3Mode->addItem(QString());
        comboBoxMp3Mode->addItem(QString());
        comboBoxMp3Mode->setObjectName(QStringLiteral("comboBoxMp3Mode"));
        sizePolicy.setHeightForWidth(comboBoxMp3Mode->sizePolicy().hasHeightForWidth());
        comboBoxMp3Mode->setSizePolicy(sizePolicy);
        comboBoxMp3Mode->setMinimumSize(QSize(180, 23));
        comboBoxMp3Mode->setMaximumSize(QSize(16777215, 16777215));
        comboBoxMp3Mode->setEditable(true);

        horizontalLayout_11->addWidget(comboBoxMp3Mode);

        horizontalSpacer_18 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_18);


        verticalLayout_16->addLayout(horizontalLayout_11);

        horizontalSliderMp3 = new QSlider(groupBoxMp3);
        horizontalSliderMp3->setObjectName(QStringLiteral("horizontalSliderMp3"));
        horizontalSliderMp3->setOrientation(Qt::Horizontal);
        horizontalSliderMp3->setInvertedAppearance(false);
        horizontalSliderMp3->setInvertedControls(false);
        horizontalSliderMp3->setTickPosition(QSlider::TicksAbove);
        horizontalSliderMp3->setTickInterval(10);

        verticalLayout_16->addWidget(horizontalSliderMp3);


        verticalLayout_18->addWidget(groupBoxMp3);

        stackedWidgetMode->addWidget(page_mp3);
        page_ac3 = new QWidget();
        page_ac3->setObjectName(QStringLiteral("page_ac3"));
        verticalLayout_19 = new QVBoxLayout(page_ac3);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        groupBoxAc3 = new QGroupBox(page_ac3);
        groupBoxAc3->setObjectName(QStringLiteral("groupBoxAc3"));
        verticalLayout_17 = new QVBoxLayout(groupBoxAc3);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        labelAc3Bitrate = new QLabel(groupBoxAc3);
        labelAc3Bitrate->setObjectName(QStringLiteral("labelAc3Bitrate"));
        sizePolicy3.setHeightForWidth(labelAc3Bitrate->sizePolicy().hasHeightForWidth());
        labelAc3Bitrate->setSizePolicy(sizePolicy3);

        horizontalLayout_12->addWidget(labelAc3Bitrate);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_19);


        verticalLayout_17->addLayout(horizontalLayout_12);

        horizontalSliderAc3 = new QSlider(groupBoxAc3);
        horizontalSliderAc3->setObjectName(QStringLiteral("horizontalSliderAc3"));
        horizontalSliderAc3->setOrientation(Qt::Horizontal);
        horizontalSliderAc3->setInvertedAppearance(false);
        horizontalSliderAc3->setInvertedControls(false);
        horizontalSliderAc3->setTickPosition(QSlider::TicksAbove);
        horizontalSliderAc3->setTickInterval(10);

        verticalLayout_17->addWidget(horizontalSliderAc3);


        verticalLayout_19->addWidget(groupBoxAc3);

        stackedWidgetMode->addWidget(page_ac3);
        page_wav = new QWidget();
        page_wav->setObjectName(QStringLiteral("page_wav"));
        verticalLayout_20 = new QVBoxLayout(page_wav);
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        verticalLayout_20->setContentsMargins(0, 0, 0, 0);
        groupBoxWav = new QGroupBox(page_wav);
        groupBoxWav->setObjectName(QStringLiteral("groupBoxWav"));

        verticalLayout_20->addWidget(groupBoxWav);

        stackedWidgetMode->addWidget(page_wav);

        verticalLayout_2->addWidget(stackedWidgetMode);

        frame = new QFrame(AudioConfig);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBoxAdvancedOption = new QCheckBox(AudioConfig);
        checkBoxAdvancedOption->setObjectName(QStringLiteral("checkBoxAdvancedOption"));

        horizontalLayout->addWidget(checkBoxAdvancedOption);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonAccept = new QPushButton(AudioConfig);
        buttonAccept->setObjectName(QStringLiteral("buttonAccept"));
        buttonAccept->setMinimumSize(QSize(112, 0));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/buttons/accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAccept->setIcon(icon2);

        horizontalLayout->addWidget(buttonAccept);

        buttonCancel = new QPushButton(AudioConfig);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setMinimumSize(QSize(112, 0));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/buttons/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon3);

        horizontalLayout->addWidget(buttonCancel);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(AudioConfig);

        comboBoxTemplate->setCurrentIndex(-1);
        comboBoxAudioEncoder->setCurrentIndex(0);
        stackedWidgetMode->setCurrentIndex(0);
        comboBoxAacAppleMode->setCurrentIndex(-1);
        comboBoxAacAppleProfile->setCurrentIndex(0);
        comboBoxAacFdkMode->setCurrentIndex(0);
        comboBoxAacFdkProfile->setCurrentIndex(0);
        comboBoxAacNeroProfile->setCurrentIndex(0);
        comboBoxOpusMode->setCurrentIndex(0);
        comboBoxMp3Mode->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AudioConfig);
    } // setupUi

    void retranslateUi(QWidget *AudioConfig)
    {
        AudioConfig->setWindowTitle(QApplication::translate("AudioConfig", "Audio Config", nullptr));
        groupBoxConfig->setTitle(QApplication::translate("AudioConfig", " Configuration ", nullptr));
#ifndef QT_NO_TOOLTIP
        labelTemplate->setToolTip(QApplication::translate("AudioConfig", "Here you can load a user-defined template that you have saved before. Use the \"Save As\" button to save your current configuration to a new template.", nullptr));
#endif // QT_NO_TOOLTIP
        labelTemplate->setText(QApplication::translate("AudioConfig", "Template:", nullptr));
#ifndef QT_NO_TOOLTIP
        comboBoxTemplate->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        buttonSaveTemplate->setText(QApplication::translate("AudioConfig", "Save", nullptr));
        buttonDeleteTemplate->setText(QApplication::translate("AudioConfig", "Delete", nullptr));
        labelAudioEncoder->setText(QApplication::translate("AudioConfig", "Encoder:", nullptr));
        comboBoxAudioEncoder->setItemText(0, QApplication::translate("AudioConfig", "AAC (Apple)", nullptr));
        comboBoxAudioEncoder->setItemText(1, QApplication::translate("AudioConfig", "AAC (FDK)", nullptr));
        comboBoxAudioEncoder->setItemText(2, QApplication::translate("AudioConfig", "AAC (Nero)", nullptr));
        comboBoxAudioEncoder->setItemText(3, QApplication::translate("AudioConfig", "ALAC", nullptr));
        comboBoxAudioEncoder->setItemText(4, QApplication::translate("AudioConfig", "FLAC", nullptr));
        comboBoxAudioEncoder->setItemText(5, QApplication::translate("AudioConfig", "OPUS", nullptr));
        comboBoxAudioEncoder->setItemText(6, QApplication::translate("AudioConfig", "OGG Vorbis", nullptr));
        comboBoxAudioEncoder->setItemText(7, QApplication::translate("AudioConfig", "MP3", nullptr));
        comboBoxAudioEncoder->setItemText(8, QApplication::translate("AudioConfig", "AC3", nullptr));
        comboBoxAudioEncoder->setItemText(9, QApplication::translate("AudioConfig", "WAV", nullptr));

        groupBoxAacApple->setTitle(QApplication::translate("AudioConfig", "QAAC", nullptr));
        labelAacAppleMode->setText(QApplication::translate("AudioConfig", "Mode", nullptr));
        labelAacAppleProfile->setText(QApplication::translate("AudioConfig", "Profile", nullptr));
        comboBoxAacAppleProfile->setItemText(0, QApplication::translate("AudioConfig", "LC-AAC", nullptr));
        comboBoxAacAppleProfile->setItemText(1, QApplication::translate("AudioConfig", "HE-AAC", nullptr));

        checkBoxAacAppleNoDelay->setText(QApplication::translate("AudioConfig", "No Delay", nullptr));
        groupBoxAacFdk->setTitle(QApplication::translate("AudioConfig", "FDKAAC", nullptr));
        labelAacFdkMode->setText(QApplication::translate("AudioConfig", "Mode", nullptr));
        comboBoxAacFdkMode->setItemText(0, QApplication::translate("AudioConfig", "CBR", nullptr));
        comboBoxAacFdkMode->setItemText(1, QApplication::translate("AudioConfig", "VBR", nullptr));

        labelAacFdkProfile->setText(QApplication::translate("AudioConfig", "Profile", nullptr));
        comboBoxAacFdkProfile->setItemText(0, QApplication::translate("AudioConfig", "MPEG-4 LC-AAC", nullptr));
        comboBoxAacFdkProfile->setItemText(1, QApplication::translate("AudioConfig", "MPEG-4 HE-AAC", nullptr));
        comboBoxAacFdkProfile->setItemText(2, QApplication::translate("AudioConfig", "MPEG-4 HE-AAC v2", nullptr));
        comboBoxAacFdkProfile->setItemText(3, QApplication::translate("AudioConfig", "MPEG-4 AAC LD", nullptr));
        comboBoxAacFdkProfile->setItemText(4, QApplication::translate("AudioConfig", "MPEG-4 AAC ELD", nullptr));
        comboBoxAacFdkProfile->setItemText(5, QApplication::translate("AudioConfig", "MPEG-2 LC-AAC", nullptr));
        comboBoxAacFdkProfile->setItemText(6, QApplication::translate("AudioConfig", "MPEG-2 HE-AAC", nullptr));
        comboBoxAacFdkProfile->setItemText(7, QApplication::translate("AudioConfig", "MPEG-2 HE-AAC v2", nullptr));

        groupBoxAacNero->setTitle(QApplication::translate("AudioConfig", "NeroAAC", nullptr));
        labelAacNeroProfile->setText(QApplication::translate("AudioConfig", "Profile", nullptr));
        comboBoxAacNeroProfile->setItemText(0, QApplication::translate("AudioConfig", "Adaptive Bitrate", nullptr));
        comboBoxAacNeroProfile->setItemText(1, QApplication::translate("AudioConfig", "Constant Bitrate", nullptr));
        comboBoxAacNeroProfile->setItemText(2, QApplication::translate("AudioConfig", "Variable Bitrate", nullptr));

        groupBoxAlac->setTitle(QApplication::translate("AudioConfig", "ALAC", nullptr));
        groupBoxFlac->setTitle(QApplication::translate("AudioConfig", "FLAC", nullptr));
        labelFlacFast->setText(QApplication::translate("AudioConfig", "Biggest file ,fast encode", nullptr));
        labelFlacSlow->setText(QApplication::translate("AudioConfig", "Smallest file, slow encode", nullptr));
        groupBoxOpus->setTitle(QApplication::translate("AudioConfig", "OPUS", nullptr));
        labelOpusMode->setText(QApplication::translate("AudioConfig", "Mode", nullptr));
        comboBoxOpusMode->setItemText(0, QApplication::translate("AudioConfig", "VBR", nullptr));
        comboBoxOpusMode->setItemText(1, QApplication::translate("AudioConfig", "Constrained VBR", nullptr));
        comboBoxOpusMode->setItemText(2, QApplication::translate("AudioConfig", "Hard CBR", nullptr));

        groupBoxOggVorbis->setTitle(QApplication::translate("AudioConfig", "Ogg Vorbis", nullptr));
        labelOggVorbisVariableBitrate->setText(QApplication::translate("AudioConfig", "Variable Bitrate", nullptr));
        groupBoxMp3->setTitle(QApplication::translate("AudioConfig", "MP3", nullptr));
        labelMp3Mode->setText(QApplication::translate("AudioConfig", "Mode", nullptr));
        comboBoxMp3Mode->setItemText(0, QApplication::translate("AudioConfig", "CBR", nullptr));
        comboBoxMp3Mode->setItemText(1, QApplication::translate("AudioConfig", "ABR", nullptr));
        comboBoxMp3Mode->setItemText(2, QApplication::translate("AudioConfig", "VBR", nullptr));

        groupBoxAc3->setTitle(QApplication::translate("AudioConfig", "AC3", nullptr));
        labelAc3Bitrate->setText(QApplication::translate("AudioConfig", "Bitrate", nullptr));
        groupBoxWav->setTitle(QApplication::translate("AudioConfig", "WAV", nullptr));
        checkBoxAdvancedOption->setText(QApplication::translate("AudioConfig", "Advanced Option", nullptr));
        buttonAccept->setText(QApplication::translate("AudioConfig", "Accept", nullptr));
        buttonCancel->setText(QApplication::translate("AudioConfig", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioConfig: public Ui_AudioConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIO_CONFIG_H
