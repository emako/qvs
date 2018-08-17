/********************************************************************************
** Form generated from reading UI file 'muxer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUXER_H
#define UI_MUXER_H

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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Muxer
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxMuxer;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_VideoInput;
    QLineEdit *editMuxerVideoInput;
    QPushButton *buttonMuxerVideoInput;
    QHBoxLayout *horizontalLayout_AudioInput;
    QLineEdit *editMuxerAudioInput;
    QPushButton *buttonMuxerAudioInput;
    QHBoxLayout *horizontalLayout_Output;
    QLineEdit *editMuxerOutput;
    QPushButton *buttonMuxerOutput;
    QHBoxLayout *horizontalLayout_Start;
    QLabel *labelMuxerFormat;
    QComboBox *comboBoxMuxerFormat;
    QSpacerItem *horizontalSpacer_6;
    QLabel *labelMuxerDelay;
    QSpinBox *spinBoxMuxerDelay;
    QLabel *labelMuxerDelayUnit;
    QPushButton *buttonMuxerStart;

    void setupUi(QWidget *Muxer)
    {
        if (Muxer->objectName().isEmpty())
            Muxer->setObjectName(QStringLiteral("Muxer"));
        Muxer->resize(740, 175);
        verticalLayout = new QVBoxLayout(Muxer);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBoxMuxer = new QGroupBox(Muxer);
        groupBoxMuxer->setObjectName(QStringLiteral("groupBoxMuxer"));
        verticalLayout_9 = new QVBoxLayout(groupBoxMuxer);
        verticalLayout_9->setSpacing(5);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(11, 11, -1, -1);
        horizontalLayout_VideoInput = new QHBoxLayout();
        horizontalLayout_VideoInput->setObjectName(QStringLiteral("horizontalLayout_VideoInput"));
        editMuxerVideoInput = new QLineEdit(groupBoxMuxer);
        editMuxerVideoInput->setObjectName(QStringLiteral("editMuxerVideoInput"));
        editMuxerVideoInput->setMinimumSize(QSize(0, 25));
        editMuxerVideoInput->setStyleSheet(QStringLiteral("background-color: rgb(243, 243, 243);"));
        editMuxerVideoInput->setReadOnly(true);

        horizontalLayout_VideoInput->addWidget(editMuxerVideoInput);

        buttonMuxerVideoInput = new QPushButton(groupBoxMuxer);
        buttonMuxerVideoInput->setObjectName(QStringLiteral("buttonMuxerVideoInput"));
        buttonMuxerVideoInput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_VideoInput->addWidget(buttonMuxerVideoInput);


        verticalLayout_9->addLayout(horizontalLayout_VideoInput);

        horizontalLayout_AudioInput = new QHBoxLayout();
        horizontalLayout_AudioInput->setObjectName(QStringLiteral("horizontalLayout_AudioInput"));
        editMuxerAudioInput = new QLineEdit(groupBoxMuxer);
        editMuxerAudioInput->setObjectName(QStringLiteral("editMuxerAudioInput"));
        editMuxerAudioInput->setMinimumSize(QSize(0, 25));
        editMuxerAudioInput->setStyleSheet(QStringLiteral("background-color: rgb(243, 243, 243);"));
        editMuxerAudioInput->setReadOnly(true);

        horizontalLayout_AudioInput->addWidget(editMuxerAudioInput);

        buttonMuxerAudioInput = new QPushButton(groupBoxMuxer);
        buttonMuxerAudioInput->setObjectName(QStringLiteral("buttonMuxerAudioInput"));
        buttonMuxerAudioInput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_AudioInput->addWidget(buttonMuxerAudioInput);


        verticalLayout_9->addLayout(horizontalLayout_AudioInput);

        horizontalLayout_Output = new QHBoxLayout();
        horizontalLayout_Output->setObjectName(QStringLiteral("horizontalLayout_Output"));
        editMuxerOutput = new QLineEdit(groupBoxMuxer);
        editMuxerOutput->setObjectName(QStringLiteral("editMuxerOutput"));
        editMuxerOutput->setMinimumSize(QSize(0, 25));
        editMuxerOutput->setReadOnly(false);

        horizontalLayout_Output->addWidget(editMuxerOutput);

        buttonMuxerOutput = new QPushButton(groupBoxMuxer);
        buttonMuxerOutput->setObjectName(QStringLiteral("buttonMuxerOutput"));
        buttonMuxerOutput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_Output->addWidget(buttonMuxerOutput);


        verticalLayout_9->addLayout(horizontalLayout_Output);

        horizontalLayout_Start = new QHBoxLayout();
        horizontalLayout_Start->setObjectName(QStringLiteral("horizontalLayout_Start"));
        labelMuxerFormat = new QLabel(groupBoxMuxer);
        labelMuxerFormat->setObjectName(QStringLiteral("labelMuxerFormat"));

        horizontalLayout_Start->addWidget(labelMuxerFormat);

        comboBoxMuxerFormat = new QComboBox(groupBoxMuxer);
        comboBoxMuxerFormat->addItem(QString());
        comboBoxMuxerFormat->addItem(QString());
        comboBoxMuxerFormat->addItem(QString());
        comboBoxMuxerFormat->addItem(QString());
        comboBoxMuxerFormat->setObjectName(QStringLiteral("comboBoxMuxerFormat"));
        comboBoxMuxerFormat->setMinimumSize(QSize(120, 25));

        horizontalLayout_Start->addWidget(comboBoxMuxerFormat);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_Start->addItem(horizontalSpacer_6);

        labelMuxerDelay = new QLabel(groupBoxMuxer);
        labelMuxerDelay->setObjectName(QStringLiteral("labelMuxerDelay"));

        horizontalLayout_Start->addWidget(labelMuxerDelay);

        spinBoxMuxerDelay = new QSpinBox(groupBoxMuxer);
        spinBoxMuxerDelay->setObjectName(QStringLiteral("spinBoxMuxerDelay"));
        spinBoxMuxerDelay->setMinimumSize(QSize(65, 25));
        spinBoxMuxerDelay->setStyleSheet(QStringLiteral(""));
        spinBoxMuxerDelay->setWrapping(false);
        spinBoxMuxerDelay->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBoxMuxerDelay->setCorrectionMode(QAbstractSpinBox::CorrectToPreviousValue);
        spinBoxMuxerDelay->setProperty("showGroupSeparator", QVariant(false));
        spinBoxMuxerDelay->setMinimum(-999999999);
        spinBoxMuxerDelay->setMaximum(999999999);
        spinBoxMuxerDelay->setValue(0);

        horizontalLayout_Start->addWidget(spinBoxMuxerDelay);

        labelMuxerDelayUnit = new QLabel(groupBoxMuxer);
        labelMuxerDelayUnit->setObjectName(QStringLiteral("labelMuxerDelayUnit"));

        horizontalLayout_Start->addWidget(labelMuxerDelayUnit);

        buttonMuxerStart = new QPushButton(groupBoxMuxer);
        buttonMuxerStart->setObjectName(QStringLiteral("buttonMuxerStart"));
        buttonMuxerStart->setEnabled(true);
        buttonMuxerStart->setMinimumSize(QSize(104, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonMuxerStart->setIcon(icon);

        horizontalLayout_Start->addWidget(buttonMuxerStart);


        verticalLayout_9->addLayout(horizontalLayout_Start);


        verticalLayout->addWidget(groupBoxMuxer);


        retranslateUi(Muxer);

        QMetaObject::connectSlotsByName(Muxer);
    } // setupUi

    void retranslateUi(QWidget *Muxer)
    {
        Muxer->setWindowTitle(QApplication::translate("Muxer", "Form", nullptr));
        groupBoxMuxer->setTitle(QApplication::translate("Muxer", "Muxer", nullptr));
#ifndef QT_NO_TOOLTIP
        editMuxerVideoInput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editMuxerVideoInput->setPlaceholderText(QApplication::translate("Muxer", "Video File Input Path", nullptr));
        buttonMuxerVideoInput->setText(QApplication::translate("Muxer", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        editMuxerAudioInput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editMuxerAudioInput->setPlaceholderText(QApplication::translate("Muxer", "Audio File Input Path", nullptr));
        buttonMuxerAudioInput->setText(QApplication::translate("Muxer", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        editMuxerOutput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editMuxerOutput->setPlaceholderText(QApplication::translate("Muxer", "Muxed File Output Path", nullptr));
        buttonMuxerOutput->setText(QApplication::translate("Muxer", "...", nullptr));
        labelMuxerFormat->setText(QApplication::translate("Muxer", "Format:", nullptr));
        comboBoxMuxerFormat->setItemText(0, QApplication::translate("Muxer", "mp4box", nullptr));
        comboBoxMuxerFormat->setItemText(1, QApplication::translate("Muxer", "l-smash", nullptr));
        comboBoxMuxerFormat->setItemText(2, QApplication::translate("Muxer", "mkvmerge", nullptr));
        comboBoxMuxerFormat->setItemText(3, QApplication::translate("Muxer", "ffmpeg", nullptr));

        labelMuxerDelay->setText(QApplication::translate("Muxer", "Delay:", nullptr));
        spinBoxMuxerDelay->setSpecialValueText(QString());
        labelMuxerDelayUnit->setText(QApplication::translate("Muxer", "ms", nullptr));
        buttonMuxerStart->setText(QApplication::translate("Muxer", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Muxer: public Ui_Muxer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUXER_H
