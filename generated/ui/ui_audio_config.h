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
    QGroupBox *groupBox;
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
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelAudioEncoder_2;
    QComboBox *comboBoxAudioEncoder_2;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_6;
    QLabel *labelAudioEncoder_3;
    QComboBox *comboBoxAudioEncoder_3;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_5;
    QWidget *page_fdkaac;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_8;
    QLabel *labelAudioEncoder_4;
    QComboBox *comboBoxAudioEncoder_9;
    QSpacerItem *horizontalSpacer_7;
    QSlider *horizontalSlider_2;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_9;
    QLabel *labelAudioEncoder_8;
    QComboBox *comboBoxAudioEncoder_10;
    QSpacerItem *horizontalSpacer_10;
    QWidget *page_neroaac;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_8;
    QSlider *horizontalSlider_3;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_11;
    QLabel *labelAudioEncoder_5;
    QComboBox *comboBoxAudioEncoder_6;
    QSpacerItem *horizontalSpacer_12;
    QWidget *page_alac;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_5;
    QWidget *page_flac;
    QVBoxLayout *verticalLayout_10;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_11;
    QSlider *horizontalSlider_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_2;
    QWidget *page_opus;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_14;
    QLabel *labelAudioEncoder_6;
    QComboBox *comboBoxAudioEncoder_7;
    QSpacerItem *horizontalSpacer_15;
    QSlider *horizontalSlider_5;
    QWidget *page_vorbis;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_16;
    QSlider *horizontalSlider_6;
    QWidget *page_mp3;
    QVBoxLayout *verticalLayout_18;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_17;
    QLabel *labelAudioEncoder_7;
    QComboBox *comboBoxAudioEncoder_8;
    QSpacerItem *horizontalSpacer_18;
    QSlider *horizontalSlider_7;
    QWidget *page_ac3;
    QVBoxLayout *verticalLayout_19;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_17;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_19;
    QSlider *horizontalSlider_8;
    QWidget *page_wav;
    QVBoxLayout *verticalLayout_20;
    QGroupBox *groupBox_11;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonAccept;
    QPushButton *buttonCancel;

    void setupUi(QWidget *AudioConfig)
    {
        if (AudioConfig->objectName().isEmpty())
            AudioConfig->setObjectName(QStringLiteral("AudioConfig"));
        AudioConfig->resize(548, 322);
        verticalLayout_2 = new QVBoxLayout(AudioConfig);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(AudioConfig);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayoutTemplate = new QHBoxLayout();
        horizontalLayoutTemplate->setSpacing(8);
        horizontalLayoutTemplate->setObjectName(QStringLiteral("horizontalLayoutTemplate"));
        labelTemplate = new QLabel(groupBox);
        labelTemplate->setObjectName(QStringLiteral("labelTemplate"));
        labelTemplate->setMinimumSize(QSize(80, 0));
        labelTemplate->setMaximumSize(QSize(80, 16777215));

        horizontalLayoutTemplate->addWidget(labelTemplate);

        comboBoxTemplate = new QComboBox(groupBox);
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

        buttonSaveTemplate = new QPushButton(groupBox);
        buttonSaveTemplate->setObjectName(QStringLiteral("buttonSaveTemplate"));
        buttonSaveTemplate->setMinimumSize(QSize(90, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSaveTemplate->setIcon(icon);

        horizontalLayoutTemplate->addWidget(buttonSaveTemplate);

        buttonDeleteTemplate = new QPushButton(groupBox);
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
        labelAudioEncoder = new QLabel(groupBox);
        labelAudioEncoder->setObjectName(QStringLiteral("labelAudioEncoder"));
        labelAudioEncoder->setMinimumSize(QSize(80, 0));
        labelAudioEncoder->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(labelAudioEncoder);

        comboBoxAudioEncoder = new QComboBox(groupBox);
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


        verticalLayout_2->addWidget(groupBox);

        stackedWidgetMode = new QStackedWidget(AudioConfig);
        stackedWidgetMode->setObjectName(QStringLiteral("stackedWidgetMode"));
        page_qaac = new QWidget();
        page_qaac->setObjectName(QStringLiteral("page_qaac"));
        verticalLayout_3 = new QVBoxLayout(page_qaac);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(page_qaac);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        labelAudioEncoder_2 = new QLabel(groupBox_2);
        labelAudioEncoder_2->setObjectName(QStringLiteral("labelAudioEncoder_2"));
        labelAudioEncoder_2->setMinimumSize(QSize(80, 0));
        labelAudioEncoder_2->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(labelAudioEncoder_2);

        comboBoxAudioEncoder_2 = new QComboBox(groupBox_2);
        comboBoxAudioEncoder_2->setObjectName(QStringLiteral("comboBoxAudioEncoder_2"));
        comboBoxAudioEncoder_2->setMinimumSize(QSize(130, 22));
        comboBoxAudioEncoder_2->setMaximumSize(QSize(90, 22));
        comboBoxAudioEncoder_2->setEditable(true);

        horizontalLayout_4->addWidget(comboBoxAudioEncoder_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSlider = new QSlider(groupBox_2);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedAppearance(false);
        horizontalSlider->setInvertedControls(false);
        horizontalSlider->setTickPosition(QSlider::TicksAbove);
        horizontalSlider->setTickInterval(10);

        horizontalLayout_5->addWidget(horizontalSlider);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        labelAudioEncoder_3 = new QLabel(groupBox_2);
        labelAudioEncoder_3->setObjectName(QStringLiteral("labelAudioEncoder_3"));
        labelAudioEncoder_3->setMinimumSize(QSize(80, 0));
        labelAudioEncoder_3->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(labelAudioEncoder_3);

        comboBoxAudioEncoder_3 = new QComboBox(groupBox_2);
        comboBoxAudioEncoder_3->addItem(QString());
        comboBoxAudioEncoder_3->addItem(QString());
        comboBoxAudioEncoder_3->setObjectName(QStringLiteral("comboBoxAudioEncoder_3"));
        comboBoxAudioEncoder_3->setMinimumSize(QSize(130, 22));
        comboBoxAudioEncoder_3->setMaximumSize(QSize(90, 22));
        comboBoxAudioEncoder_3->setEditable(true);

        horizontalLayout_3->addWidget(comboBoxAudioEncoder_3);

        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_3->addWidget(checkBox);

        horizontalSpacer_5 = new QSpacerItem(40, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(groupBox_2);

        stackedWidgetMode->addWidget(page_qaac);
        page_fdkaac = new QWidget();
        page_fdkaac->setObjectName(QStringLiteral("page_fdkaac"));
        verticalLayout_5 = new QVBoxLayout(page_fdkaac);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(page_fdkaac);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_6 = new QVBoxLayout(groupBox_3);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);

        labelAudioEncoder_4 = new QLabel(groupBox_3);
        labelAudioEncoder_4->setObjectName(QStringLiteral("labelAudioEncoder_4"));
        labelAudioEncoder_4->setMinimumSize(QSize(80, 0));
        labelAudioEncoder_4->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_6->addWidget(labelAudioEncoder_4);

        comboBoxAudioEncoder_9 = new QComboBox(groupBox_3);
        comboBoxAudioEncoder_9->addItem(QString());
        comboBoxAudioEncoder_9->addItem(QString());
        comboBoxAudioEncoder_9->setObjectName(QStringLiteral("comboBoxAudioEncoder_9"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBoxAudioEncoder_9->sizePolicy().hasHeightForWidth());
        comboBoxAudioEncoder_9->setSizePolicy(sizePolicy1);
        comboBoxAudioEncoder_9->setMinimumSize(QSize(180, 22));
        comboBoxAudioEncoder_9->setMaximumSize(QSize(180, 22));
        comboBoxAudioEncoder_9->setEditable(true);

        horizontalLayout_6->addWidget(comboBoxAudioEncoder_9);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        verticalLayout_6->addLayout(horizontalLayout_6);

        horizontalSlider_2 = new QSlider(groupBox_3);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_2->setInvertedAppearance(false);
        horizontalSlider_2->setInvertedControls(false);
        horizontalSlider_2->setTickPosition(QSlider::TicksAbove);
        horizontalSlider_2->setTickInterval(10);

        verticalLayout_6->addWidget(horizontalSlider_2);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_9);

        labelAudioEncoder_8 = new QLabel(groupBox_3);
        labelAudioEncoder_8->setObjectName(QStringLiteral("labelAudioEncoder_8"));
        labelAudioEncoder_8->setMinimumSize(QSize(80, 0));
        labelAudioEncoder_8->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_13->addWidget(labelAudioEncoder_8);

        comboBoxAudioEncoder_10 = new QComboBox(groupBox_3);
        comboBoxAudioEncoder_10->addItem(QString());
        comboBoxAudioEncoder_10->addItem(QString());
        comboBoxAudioEncoder_10->addItem(QString());
        comboBoxAudioEncoder_10->addItem(QString());
        comboBoxAudioEncoder_10->addItem(QString());
        comboBoxAudioEncoder_10->addItem(QString());
        comboBoxAudioEncoder_10->addItem(QString());
        comboBoxAudioEncoder_10->addItem(QString());
        comboBoxAudioEncoder_10->setObjectName(QStringLiteral("comboBoxAudioEncoder_10"));
        sizePolicy1.setHeightForWidth(comboBoxAudioEncoder_10->sizePolicy().hasHeightForWidth());
        comboBoxAudioEncoder_10->setSizePolicy(sizePolicy1);
        comboBoxAudioEncoder_10->setMinimumSize(QSize(180, 22));
        comboBoxAudioEncoder_10->setMaximumSize(QSize(180, 22));
        comboBoxAudioEncoder_10->setEditable(true);

        horizontalLayout_13->addWidget(comboBoxAudioEncoder_10);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_10);


        verticalLayout_6->addLayout(horizontalLayout_13);


        verticalLayout_5->addWidget(groupBox_3);

        stackedWidgetMode->addWidget(page_fdkaac);
        page_neroaac = new QWidget();
        page_neroaac->setObjectName(QStringLiteral("page_neroaac"));
        verticalLayout_7 = new QVBoxLayout(page_neroaac);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(page_neroaac);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_8 = new QVBoxLayout(groupBox_4);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalSlider_3 = new QSlider(groupBox_4);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        horizontalSlider_3->setInvertedAppearance(false);
        horizontalSlider_3->setInvertedControls(false);
        horizontalSlider_3->setTickPosition(QSlider::TicksAbove);
        horizontalSlider_3->setTickInterval(10);

        verticalLayout_8->addWidget(horizontalSlider_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);

        labelAudioEncoder_5 = new QLabel(groupBox_4);
        labelAudioEncoder_5->setObjectName(QStringLiteral("labelAudioEncoder_5"));
        labelAudioEncoder_5->setMinimumSize(QSize(80, 0));
        labelAudioEncoder_5->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_7->addWidget(labelAudioEncoder_5);

        comboBoxAudioEncoder_6 = new QComboBox(groupBox_4);
        comboBoxAudioEncoder_6->addItem(QString());
        comboBoxAudioEncoder_6->addItem(QString());
        comboBoxAudioEncoder_6->addItem(QString());
        comboBoxAudioEncoder_6->setObjectName(QStringLiteral("comboBoxAudioEncoder_6"));
        comboBoxAudioEncoder_6->setMinimumSize(QSize(130, 22));
        comboBoxAudioEncoder_6->setMaximumSize(QSize(90, 22));
        comboBoxAudioEncoder_6->setEditable(true);

        horizontalLayout_7->addWidget(comboBoxAudioEncoder_6);

        horizontalSpacer_12 = new QSpacerItem(40, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_12);


        verticalLayout_8->addLayout(horizontalLayout_7);


        verticalLayout_7->addWidget(groupBox_4);

        stackedWidgetMode->addWidget(page_neroaac);
        page_alac = new QWidget();
        page_alac->setObjectName(QStringLiteral("page_alac"));
        verticalLayout_9 = new QVBoxLayout(page_alac);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        groupBox_5 = new QGroupBox(page_alac);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));

        verticalLayout_9->addWidget(groupBox_5);

        stackedWidgetMode->addWidget(page_alac);
        page_flac = new QWidget();
        page_flac->setObjectName(QStringLiteral("page_flac"));
        verticalLayout_10 = new QVBoxLayout(page_flac);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        groupBox_6 = new QGroupBox(page_flac);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        verticalLayout_11 = new QVBoxLayout(groupBox_6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalSlider_4 = new QSlider(groupBox_6);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        horizontalSlider_4->setInvertedAppearance(false);
        horizontalSlider_4->setInvertedControls(false);
        horizontalSlider_4->setTickPosition(QSlider::TicksAbove);
        horizontalSlider_4->setTickInterval(10);

        verticalLayout_11->addWidget(horizontalSlider_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label = new QLabel(groupBox_6);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(label);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);

        label_2 = new QLabel(groupBox_6);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(label_2);


        verticalLayout_11->addLayout(horizontalLayout_8);


        verticalLayout_10->addWidget(groupBox_6);

        stackedWidgetMode->addWidget(page_flac);
        page_opus = new QWidget();
        page_opus->setObjectName(QStringLiteral("page_opus"));
        verticalLayout_12 = new QVBoxLayout(page_opus);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        groupBox_7 = new QGroupBox(page_opus);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        verticalLayout_13 = new QVBoxLayout(groupBox_7);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_14);

        labelAudioEncoder_6 = new QLabel(groupBox_7);
        labelAudioEncoder_6->setObjectName(QStringLiteral("labelAudioEncoder_6"));
        labelAudioEncoder_6->setMinimumSize(QSize(80, 0));
        labelAudioEncoder_6->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_9->addWidget(labelAudioEncoder_6);

        comboBoxAudioEncoder_7 = new QComboBox(groupBox_7);
        comboBoxAudioEncoder_7->addItem(QString());
        comboBoxAudioEncoder_7->addItem(QString());
        comboBoxAudioEncoder_7->addItem(QString());
        comboBoxAudioEncoder_7->setObjectName(QStringLiteral("comboBoxAudioEncoder_7"));
        comboBoxAudioEncoder_7->setMinimumSize(QSize(130, 22));
        comboBoxAudioEncoder_7->setMaximumSize(QSize(90, 22));
        comboBoxAudioEncoder_7->setEditable(true);

        horizontalLayout_9->addWidget(comboBoxAudioEncoder_7);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_15);


        verticalLayout_13->addLayout(horizontalLayout_9);

        horizontalSlider_5 = new QSlider(groupBox_7);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setOrientation(Qt::Horizontal);
        horizontalSlider_5->setInvertedAppearance(false);
        horizontalSlider_5->setInvertedControls(false);
        horizontalSlider_5->setTickPosition(QSlider::TicksAbove);
        horizontalSlider_5->setTickInterval(10);

        verticalLayout_13->addWidget(horizontalSlider_5);


        verticalLayout_12->addWidget(groupBox_7);

        stackedWidgetMode->addWidget(page_opus);
        page_vorbis = new QWidget();
        page_vorbis->setObjectName(QStringLiteral("page_vorbis"));
        verticalLayout_14 = new QVBoxLayout(page_vorbis);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        groupBox_8 = new QGroupBox(page_vorbis);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        verticalLayout_15 = new QVBoxLayout(groupBox_8);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_3 = new QLabel(groupBox_8);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        horizontalLayout_10->addWidget(label_3);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_16);


        verticalLayout_15->addLayout(horizontalLayout_10);

        horizontalSlider_6 = new QSlider(groupBox_8);
        horizontalSlider_6->setObjectName(QStringLiteral("horizontalSlider_6"));
        horizontalSlider_6->setOrientation(Qt::Horizontal);
        horizontalSlider_6->setInvertedAppearance(false);
        horizontalSlider_6->setInvertedControls(false);
        horizontalSlider_6->setTickPosition(QSlider::TicksAbove);
        horizontalSlider_6->setTickInterval(10);

        verticalLayout_15->addWidget(horizontalSlider_6);


        verticalLayout_14->addWidget(groupBox_8);

        stackedWidgetMode->addWidget(page_vorbis);
        page_mp3 = new QWidget();
        page_mp3->setObjectName(QStringLiteral("page_mp3"));
        verticalLayout_18 = new QVBoxLayout(page_mp3);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        groupBox_9 = new QGroupBox(page_mp3);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        verticalLayout_16 = new QVBoxLayout(groupBox_9);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_17);

        labelAudioEncoder_7 = new QLabel(groupBox_9);
        labelAudioEncoder_7->setObjectName(QStringLiteral("labelAudioEncoder_7"));
        labelAudioEncoder_7->setMinimumSize(QSize(80, 0));
        labelAudioEncoder_7->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_11->addWidget(labelAudioEncoder_7);

        comboBoxAudioEncoder_8 = new QComboBox(groupBox_9);
        comboBoxAudioEncoder_8->addItem(QString());
        comboBoxAudioEncoder_8->addItem(QString());
        comboBoxAudioEncoder_8->addItem(QString());
        comboBoxAudioEncoder_8->setObjectName(QStringLiteral("comboBoxAudioEncoder_8"));
        comboBoxAudioEncoder_8->setMinimumSize(QSize(130, 22));
        comboBoxAudioEncoder_8->setMaximumSize(QSize(90, 22));
        comboBoxAudioEncoder_8->setEditable(true);

        horizontalLayout_11->addWidget(comboBoxAudioEncoder_8);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_18);


        verticalLayout_16->addLayout(horizontalLayout_11);

        horizontalSlider_7 = new QSlider(groupBox_9);
        horizontalSlider_7->setObjectName(QStringLiteral("horizontalSlider_7"));
        horizontalSlider_7->setOrientation(Qt::Horizontal);
        horizontalSlider_7->setInvertedAppearance(false);
        horizontalSlider_7->setInvertedControls(false);
        horizontalSlider_7->setTickPosition(QSlider::TicksAbove);
        horizontalSlider_7->setTickInterval(10);

        verticalLayout_16->addWidget(horizontalSlider_7);


        verticalLayout_18->addWidget(groupBox_9);

        stackedWidgetMode->addWidget(page_mp3);
        page_ac3 = new QWidget();
        page_ac3->setObjectName(QStringLiteral("page_ac3"));
        verticalLayout_19 = new QVBoxLayout(page_ac3);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        groupBox_10 = new QGroupBox(page_ac3);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        verticalLayout_17 = new QVBoxLayout(groupBox_10);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_5 = new QLabel(groupBox_10);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

        horizontalLayout_12->addWidget(label_5);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_19);


        verticalLayout_17->addLayout(horizontalLayout_12);

        horizontalSlider_8 = new QSlider(groupBox_10);
        horizontalSlider_8->setObjectName(QStringLiteral("horizontalSlider_8"));
        horizontalSlider_8->setOrientation(Qt::Horizontal);
        horizontalSlider_8->setInvertedAppearance(false);
        horizontalSlider_8->setInvertedControls(false);
        horizontalSlider_8->setTickPosition(QSlider::TicksAbove);
        horizontalSlider_8->setTickInterval(10);

        verticalLayout_17->addWidget(horizontalSlider_8);


        verticalLayout_19->addWidget(groupBox_10);

        stackedWidgetMode->addWidget(page_ac3);
        page_wav = new QWidget();
        page_wav->setObjectName(QStringLiteral("page_wav"));
        verticalLayout_20 = new QVBoxLayout(page_wav);
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        verticalLayout_20->setContentsMargins(0, 0, 0, 0);
        groupBox_11 = new QGroupBox(page_wav);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));

        verticalLayout_20->addWidget(groupBox_11);

        stackedWidgetMode->addWidget(page_wav);

        verticalLayout_2->addWidget(stackedWidgetMode);

        frame = new QFrame(AudioConfig);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
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
        comboBoxAudioEncoder_2->setCurrentIndex(-1);
        comboBoxAudioEncoder_3->setCurrentIndex(0);
        comboBoxAudioEncoder_9->setCurrentIndex(0);
        comboBoxAudioEncoder_10->setCurrentIndex(0);
        comboBoxAudioEncoder_6->setCurrentIndex(0);
        comboBoxAudioEncoder_7->setCurrentIndex(0);
        comboBoxAudioEncoder_8->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AudioConfig);
    } // setupUi

    void retranslateUi(QWidget *AudioConfig)
    {
        AudioConfig->setWindowTitle(QApplication::translate("AudioConfig", "Audio Config", nullptr));
        groupBox->setTitle(QApplication::translate("AudioConfig", " Configuration ", nullptr));
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

        groupBox_2->setTitle(QApplication::translate("AudioConfig", "QAAC", nullptr));
        labelAudioEncoder_2->setText(QApplication::translate("AudioConfig", "Mode", nullptr));
        labelAudioEncoder_3->setText(QApplication::translate("AudioConfig", "Profile", nullptr));
        comboBoxAudioEncoder_3->setItemText(0, QApplication::translate("AudioConfig", "LC-AAC", nullptr));
        comboBoxAudioEncoder_3->setItemText(1, QApplication::translate("AudioConfig", "HE-AAC", nullptr));

        checkBox->setText(QApplication::translate("AudioConfig", "No Delay", nullptr));
        groupBox_3->setTitle(QApplication::translate("AudioConfig", "FDKAAC", nullptr));
        labelAudioEncoder_4->setText(QApplication::translate("AudioConfig", "Mode", nullptr));
        comboBoxAudioEncoder_9->setItemText(0, QApplication::translate("AudioConfig", "CBR", nullptr));
        comboBoxAudioEncoder_9->setItemText(1, QApplication::translate("AudioConfig", "VBR", nullptr));

        labelAudioEncoder_8->setText(QApplication::translate("AudioConfig", "Profile", nullptr));
        comboBoxAudioEncoder_10->setItemText(0, QApplication::translate("AudioConfig", "MPEG-4 LC-AAC", nullptr));
        comboBoxAudioEncoder_10->setItemText(1, QApplication::translate("AudioConfig", "MPEG-4 HE-AAC", nullptr));
        comboBoxAudioEncoder_10->setItemText(2, QApplication::translate("AudioConfig", "MPEG-4 HE-AAC v2", nullptr));
        comboBoxAudioEncoder_10->setItemText(3, QApplication::translate("AudioConfig", "MPEG-4 AAC LD", nullptr));
        comboBoxAudioEncoder_10->setItemText(4, QApplication::translate("AudioConfig", "MPEG-4 AAC ELD", nullptr));
        comboBoxAudioEncoder_10->setItemText(5, QApplication::translate("AudioConfig", "MPEG-2 LC-AAC", nullptr));
        comboBoxAudioEncoder_10->setItemText(6, QApplication::translate("AudioConfig", "MPEG-2 HE-AAC", nullptr));
        comboBoxAudioEncoder_10->setItemText(7, QApplication::translate("AudioConfig", "MPEG-2 HE-AAC v2", nullptr));

        groupBox_4->setTitle(QApplication::translate("AudioConfig", "NeroAAC", nullptr));
        labelAudioEncoder_5->setText(QApplication::translate("AudioConfig", "Profile", nullptr));
        comboBoxAudioEncoder_6->setItemText(0, QApplication::translate("AudioConfig", "Adaptive Bitrate", nullptr));
        comboBoxAudioEncoder_6->setItemText(1, QApplication::translate("AudioConfig", "Constant Bitrate", nullptr));
        comboBoxAudioEncoder_6->setItemText(2, QApplication::translate("AudioConfig", "Variable Bitrate", nullptr));

        groupBox_5->setTitle(QApplication::translate("AudioConfig", "ALAC", nullptr));
        groupBox_6->setTitle(QApplication::translate("AudioConfig", "FLAC", nullptr));
        label->setText(QApplication::translate("AudioConfig", "Biggest file ,fast encode", nullptr));
        label_2->setText(QApplication::translate("AudioConfig", "Smallest file, slow encode", nullptr));
        groupBox_7->setTitle(QApplication::translate("AudioConfig", "OPUS", nullptr));
        labelAudioEncoder_6->setText(QApplication::translate("AudioConfig", "Mode", nullptr));
        comboBoxAudioEncoder_7->setItemText(0, QApplication::translate("AudioConfig", "VBR", nullptr));
        comboBoxAudioEncoder_7->setItemText(1, QApplication::translate("AudioConfig", "Constrained VBR", nullptr));
        comboBoxAudioEncoder_7->setItemText(2, QApplication::translate("AudioConfig", "Hard CBR", nullptr));

        groupBox_8->setTitle(QApplication::translate("AudioConfig", "Ogg Vorbis", nullptr));
        label_3->setText(QApplication::translate("AudioConfig", "Variable Bitrate", nullptr));
        groupBox_9->setTitle(QApplication::translate("AudioConfig", "MP3", nullptr));
        labelAudioEncoder_7->setText(QApplication::translate("AudioConfig", "Mode", nullptr));
        comboBoxAudioEncoder_8->setItemText(0, QApplication::translate("AudioConfig", "CBR", nullptr));
        comboBoxAudioEncoder_8->setItemText(1, QApplication::translate("AudioConfig", "ABR", nullptr));
        comboBoxAudioEncoder_8->setItemText(2, QApplication::translate("AudioConfig", "VBR", nullptr));

        groupBox_10->setTitle(QApplication::translate("AudioConfig", "AC3", nullptr));
        label_5->setText(QApplication::translate("AudioConfig", "Bitrate", nullptr));
        groupBox_11->setTitle(QApplication::translate("AudioConfig", "WAV", nullptr));
        buttonAccept->setText(QApplication::translate("AudioConfig", "Accept", nullptr));
        buttonCancel->setText(QApplication::translate("AudioConfig", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioConfig: public Ui_AudioConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIO_CONFIG_H
