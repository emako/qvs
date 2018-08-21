/********************************************************************************
** Form generated from reading UI file 'audio_enc.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIO_ENC_H
#define UI_AUDIO_ENC_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioEnc
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBoxAudio;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *editAudioInput;
    QPushButton *buttonAudioInput;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *editAudioOutput;
    QPushButton *buttonAudioOutput;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelAudioEncoder;
    QComboBox *comboBoxAudioEncoder;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelAudioBitrate;
    QComboBox *comboBoxAudioBitrate;
    QLabel *labelAudioKbps;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *buttonAudioConfig;
    QPushButton *buttonAudioStart;

    void setupUi(QWidget *AudioEnc)
    {
        if (AudioEnc->objectName().isEmpty())
            AudioEnc->setObjectName(QStringLiteral("AudioEnc"));
        AudioEnc->resize(795, 175);
        AudioEnc->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_2 = new QVBoxLayout(AudioEnc);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBoxAudio = new QGroupBox(AudioEnc);
        groupBoxAudio->setObjectName(QStringLiteral("groupBoxAudio"));
        verticalLayout = new QVBoxLayout(groupBoxAudio);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        editAudioInput = new QLineEdit(groupBoxAudio);
        editAudioInput->setObjectName(QStringLiteral("editAudioInput"));
        editAudioInput->setMinimumSize(QSize(0, 25));
        editAudioInput->setStyleSheet(QStringLiteral("background-color: rgb(243, 243, 243);"));
        editAudioInput->setReadOnly(true);

        horizontalLayout_5->addWidget(editAudioInput);

        buttonAudioInput = new QPushButton(groupBoxAudio);
        buttonAudioInput->setObjectName(QStringLiteral("buttonAudioInput"));
        buttonAudioInput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_5->addWidget(buttonAudioInput);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        editAudioOutput = new QLineEdit(groupBoxAudio);
        editAudioOutput->setObjectName(QStringLiteral("editAudioOutput"));
        editAudioOutput->setMinimumSize(QSize(0, 25));
        editAudioOutput->setReadOnly(true);

        horizontalLayout_6->addWidget(editAudioOutput);

        buttonAudioOutput = new QPushButton(groupBoxAudio);
        buttonAudioOutput->setObjectName(QStringLiteral("buttonAudioOutput"));
        buttonAudioOutput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_6->addWidget(buttonAudioOutput);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelAudioEncoder = new QLabel(groupBoxAudio);
        labelAudioEncoder->setObjectName(QStringLiteral("labelAudioEncoder"));
        labelAudioEncoder->setMinimumSize(QSize(80, 0));
        labelAudioEncoder->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(labelAudioEncoder);

        comboBoxAudioEncoder = new QComboBox(groupBoxAudio);
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
        comboBoxAudioEncoder->setMinimumSize(QSize(130, 22));
        comboBoxAudioEncoder->setMaximumSize(QSize(90, 22));
        comboBoxAudioEncoder->setEditable(true);

        horizontalLayout_2->addWidget(comboBoxAudioEncoder);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelAudioBitrate = new QLabel(groupBoxAudio);
        labelAudioBitrate->setObjectName(QStringLiteral("labelAudioBitrate"));
        labelAudioBitrate->setMinimumSize(QSize(80, 0));
        labelAudioBitrate->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(labelAudioBitrate);

        comboBoxAudioBitrate = new QComboBox(groupBoxAudio);
        comboBoxAudioBitrate->addItem(QString());
        comboBoxAudioBitrate->addItem(QString());
        comboBoxAudioBitrate->addItem(QString());
        comboBoxAudioBitrate->addItem(QString());
        comboBoxAudioBitrate->addItem(QString());
        comboBoxAudioBitrate->addItem(QString());
        comboBoxAudioBitrate->addItem(QString());
        comboBoxAudioBitrate->addItem(QString());
        comboBoxAudioBitrate->setObjectName(QStringLiteral("comboBoxAudioBitrate"));
        comboBoxAudioBitrate->setMinimumSize(QSize(130, 22));
        comboBoxAudioBitrate->setMaximumSize(QSize(120, 22));
        comboBoxAudioBitrate->setAcceptDrops(false);
        comboBoxAudioBitrate->setEditable(true);

        horizontalLayout_3->addWidget(comboBoxAudioBitrate);

        labelAudioKbps = new QLabel(groupBoxAudio);
        labelAudioKbps->setObjectName(QStringLiteral("labelAudioKbps"));

        horizontalLayout_3->addWidget(labelAudioKbps);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        buttonAudioConfig = new QPushButton(groupBoxAudio);
        buttonAudioConfig->setObjectName(QStringLiteral("buttonAudioConfig"));
        buttonAudioConfig->setEnabled(true);
        buttonAudioConfig->setMinimumSize(QSize(104, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/cog.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAudioConfig->setIcon(icon);

        horizontalLayout_3->addWidget(buttonAudioConfig);

        buttonAudioStart = new QPushButton(groupBoxAudio);
        buttonAudioStart->setObjectName(QStringLiteral("buttonAudioStart"));
        buttonAudioStart->setEnabled(true);
        buttonAudioStart->setMinimumSize(QSize(104, 0));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAudioStart->setIcon(icon1);

        horizontalLayout_3->addWidget(buttonAudioStart);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(groupBoxAudio);


        retranslateUi(AudioEnc);

        comboBoxAudioEncoder->setCurrentIndex(0);
        comboBoxAudioBitrate->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(AudioEnc);
    } // setupUi

    void retranslateUi(QWidget *AudioEnc)
    {
        AudioEnc->setWindowTitle(QApplication::translate("AudioEnc", "Form", nullptr));
        groupBoxAudio->setTitle(QApplication::translate("AudioEnc", "Audio", nullptr));
#ifndef QT_NO_TOOLTIP
        editAudioInput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editAudioInput->setPlaceholderText(QApplication::translate("AudioEnc", "Audio File Input Path", nullptr));
        buttonAudioInput->setText(QApplication::translate("AudioEnc", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        editAudioOutput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editAudioOutput->setPlaceholderText(QApplication::translate("AudioEnc", "Audio File Output Path", nullptr));
        buttonAudioOutput->setText(QApplication::translate("AudioEnc", "...", nullptr));
        labelAudioEncoder->setText(QApplication::translate("AudioEnc", "Encoder:", nullptr));
        comboBoxAudioEncoder->setItemText(0, QApplication::translate("AudioEnc", "AAC (Apple)", nullptr));
        comboBoxAudioEncoder->setItemText(1, QApplication::translate("AudioEnc", "AAC (FDK)", nullptr));
        comboBoxAudioEncoder->setItemText(2, QApplication::translate("AudioEnc", "AAC (Nero)", nullptr));
        comboBoxAudioEncoder->setItemText(3, QApplication::translate("AudioEnc", "ALAC", nullptr));
        comboBoxAudioEncoder->setItemText(4, QApplication::translate("AudioEnc", "FLAC", nullptr));
        comboBoxAudioEncoder->setItemText(5, QApplication::translate("AudioEnc", "OPUS", nullptr));
        comboBoxAudioEncoder->setItemText(6, QApplication::translate("AudioEnc", "OGG Vorbis", nullptr));
        comboBoxAudioEncoder->setItemText(7, QApplication::translate("AudioEnc", "MP3", nullptr));
        comboBoxAudioEncoder->setItemText(8, QApplication::translate("AudioEnc", "AC3", nullptr));
        comboBoxAudioEncoder->setItemText(9, QApplication::translate("AudioEnc", "WAV", nullptr));

        labelAudioBitrate->setText(QApplication::translate("AudioEnc", "Bitrate:", nullptr));
        comboBoxAudioBitrate->setItemText(0, QApplication::translate("AudioEnc", "64", nullptr));
        comboBoxAudioBitrate->setItemText(1, QApplication::translate("AudioEnc", "96", nullptr));
        comboBoxAudioBitrate->setItemText(2, QApplication::translate("AudioEnc", "128", nullptr));
        comboBoxAudioBitrate->setItemText(3, QApplication::translate("AudioEnc", "160", nullptr));
        comboBoxAudioBitrate->setItemText(4, QApplication::translate("AudioEnc", "192", nullptr));
        comboBoxAudioBitrate->setItemText(5, QApplication::translate("AudioEnc", "256", nullptr));
        comboBoxAudioBitrate->setItemText(6, QApplication::translate("AudioEnc", "320", nullptr));
        comboBoxAudioBitrate->setItemText(7, QApplication::translate("AudioEnc", "480", nullptr));

        comboBoxAudioBitrate->setCurrentText(QApplication::translate("AudioEnc", "160", nullptr));
        labelAudioKbps->setText(QApplication::translate("AudioEnc", "Kbps", nullptr));
        buttonAudioConfig->setText(QApplication::translate("AudioEnc", "Config", nullptr));
        buttonAudioStart->setText(QApplication::translate("AudioEnc", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioEnc: public Ui_AudioEnc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIO_ENC_H
