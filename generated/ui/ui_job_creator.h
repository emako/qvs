/********************************************************************************
** Form generated from reading UI file 'job_creator.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOB_CREATOR_H
#define UI_JOB_CREATOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_JobCreator
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxIO;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_14;
    QLabel *labelSource;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *editSource;
    QPushButton *buttonBrowseSource;
    QVBoxLayout *verticalLayout_5;
    QLabel *labelOutput;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *editOutput;
    QPushButton *buttonBrowseOutput;
    QGroupBox *groupBoxConfig;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelTemplate;
    QComboBox *cbxTemplate;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *buttonSaveTemplate;
    QPushButton *buttonDeleteTemplate;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_16;
    QLabel *labelEncoderType;
    QComboBox *cbxEncoderType;
    QSpacerItem *horizontalSpacer_15;
    QVBoxLayout *verticalLayout_18;
    QLabel *labelEncoderArch;
    QComboBox *cbxEncoderArch;
    QSpacerItem *horizontalSpacer_16;
    QVBoxLayout *verticalLayout_17;
    QLabel *labelEncoderVariant;
    QComboBox *cbxEncoderVariant;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelRCMode;
    QComboBox *cbxRateControlMode;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *labelQuantizer;
    QDoubleSpinBox *spinQuantizer;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_6;
    QLabel *labelBitrate;
    QSpinBox *spinBitrate;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_11;
    QLabel *labelPreset;
    QComboBox *cbxPreset;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_10;
    QLabel *labelTuning;
    QComboBox *cbxTuning;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_9;
    QLabel *labelProfile;
    QComboBox *cbxProfile;
    QSpacerItem *verticalSpacer_7;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_13;
    QSpacerItem *verticalSpacer_8;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelCustomEncoderParams;
    QSpacerItem *horizontalSpacer_7;
    QLabel *labelHelpScreenEncoder;
    QLineEdit *editCustomEncoderParams;
    QSpacerItem *verticalSpacer_11;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelCustomPiperParams;
    QSpacerItem *horizontalSpacer_12;
    QLabel *labelHelpScreenCustomPiperParams;
    QLineEdit *editCustomPiperParams;
    QSpacerItem *verticalSpacer_9;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxStartJobImmediately;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonAccept;
    QPushButton *buttonCancel;

    void setupUi(QDialog *JobCreator)
    {
        if (JobCreator->objectName().isEmpty())
            JobCreator->setObjectName(QStringLiteral("JobCreator"));
        JobCreator->resize(595, 679);
        JobCreator->setMaximumSize(QSize(16777215, 16777215));
        JobCreator->setModal(true);
        verticalLayout = new QVBoxLayout(JobCreator);
        verticalLayout->setSpacing(11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        groupBoxIO = new QGroupBox(JobCreator);
        groupBoxIO->setObjectName(QStringLiteral("groupBoxIO"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBoxIO->sizePolicy().hasHeightForWidth());
        groupBoxIO->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBoxIO);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 3, -1, -1);
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(1);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        labelSource = new QLabel(groupBoxIO);
        labelSource->setObjectName(QStringLiteral("labelSource"));

        verticalLayout_14->addWidget(labelSource);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        editSource = new QLineEdit(groupBoxIO);
        editSource->setObjectName(QStringLiteral("editSource"));
        editSource->setMinimumSize(QSize(0, 25));
        editSource->setStyleSheet(QStringLiteral(""));
        editSource->setReadOnly(true);

        horizontalLayout_5->addWidget(editSource);

        buttonBrowseSource = new QPushButton(groupBoxIO);
        buttonBrowseSource->setObjectName(QStringLiteral("buttonBrowseSource"));
        buttonBrowseSource->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_5->addWidget(buttonBrowseSource);


        verticalLayout_14->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(verticalLayout_14);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(1);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        labelOutput = new QLabel(groupBoxIO);
        labelOutput->setObjectName(QStringLiteral("labelOutput"));

        verticalLayout_5->addWidget(labelOutput);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(3);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        editOutput = new QLineEdit(groupBoxIO);
        editOutput->setObjectName(QStringLiteral("editOutput"));
        editOutput->setMinimumSize(QSize(0, 25));
        editOutput->setStyleSheet(QStringLiteral(""));
        editOutput->setReadOnly(true);

        horizontalLayout_6->addWidget(editOutput);

        buttonBrowseOutput = new QPushButton(groupBoxIO);
        buttonBrowseOutput->setObjectName(QStringLiteral("buttonBrowseOutput"));
        buttonBrowseOutput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_6->addWidget(buttonBrowseOutput);


        verticalLayout_5->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(verticalLayout_5);


        verticalLayout->addWidget(groupBoxIO);

        groupBoxConfig = new QGroupBox(JobCreator);
        groupBoxConfig->setObjectName(QStringLiteral("groupBoxConfig"));
        verticalLayout_15 = new QVBoxLayout(groupBoxConfig);
        verticalLayout_15->setSpacing(3);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(-1, 3, -1, -1);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(8);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        labelTemplate = new QLabel(groupBoxConfig);
        labelTemplate->setObjectName(QStringLiteral("labelTemplate"));

        horizontalLayout_7->addWidget(labelTemplate);

        cbxTemplate = new QComboBox(groupBoxConfig);
        cbxTemplate->setObjectName(QStringLiteral("cbxTemplate"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cbxTemplate->sizePolicy().hasHeightForWidth());
        cbxTemplate->setSizePolicy(sizePolicy1);
        cbxTemplate->setMinimumSize(QSize(256, 23));
        cbxTemplate->setEditable(true);

        horizontalLayout_7->addWidget(cbxTemplate);

        horizontalSpacer_9 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        buttonSaveTemplate = new QPushButton(groupBoxConfig);
        buttonSaveTemplate->setObjectName(QStringLiteral("buttonSaveTemplate"));
        buttonSaveTemplate->setMinimumSize(QSize(90, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSaveTemplate->setIcon(icon);

        horizontalLayout_7->addWidget(buttonSaveTemplate);

        buttonDeleteTemplate = new QPushButton(groupBoxConfig);
        buttonDeleteTemplate->setObjectName(QStringLiteral("buttonDeleteTemplate"));
        buttonDeleteTemplate->setMinimumSize(QSize(90, 0));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/cross.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDeleteTemplate->setIcon(icon1);

        horizontalLayout_7->addWidget(buttonDeleteTemplate);


        verticalLayout_15->addLayout(horizontalLayout_7);

        groupBox_6 = new QGroupBox(groupBoxConfig);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        horizontalLayout_10 = new QHBoxLayout(groupBox_6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(-1, 3, -1, 11);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(2);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        labelEncoderType = new QLabel(groupBox_6);
        labelEncoderType->setObjectName(QStringLiteral("labelEncoderType"));

        verticalLayout_16->addWidget(labelEncoderType);

        cbxEncoderType = new QComboBox(groupBox_6);
        cbxEncoderType->setObjectName(QStringLiteral("cbxEncoderType"));

        verticalLayout_16->addWidget(cbxEncoderType);


        horizontalLayout_9->addLayout(verticalLayout_16);

        horizontalSpacer_15 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_15);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(2);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        labelEncoderArch = new QLabel(groupBox_6);
        labelEncoderArch->setObjectName(QStringLiteral("labelEncoderArch"));

        verticalLayout_18->addWidget(labelEncoderArch);

        cbxEncoderArch = new QComboBox(groupBox_6);
        cbxEncoderArch->setObjectName(QStringLiteral("cbxEncoderArch"));

        verticalLayout_18->addWidget(cbxEncoderArch);


        horizontalLayout_9->addLayout(verticalLayout_18);

        horizontalSpacer_16 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_16);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(2);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        labelEncoderVariant = new QLabel(groupBox_6);
        labelEncoderVariant->setObjectName(QStringLiteral("labelEncoderVariant"));

        verticalLayout_17->addWidget(labelEncoderVariant);

        cbxEncoderVariant = new QComboBox(groupBox_6);
        cbxEncoderVariant->setObjectName(QStringLiteral("cbxEncoderVariant"));

        verticalLayout_17->addWidget(cbxEncoderVariant);


        horizontalLayout_9->addLayout(verticalLayout_17);


        horizontalLayout_10->addLayout(horizontalLayout_9);


        verticalLayout_15->addWidget(groupBox_6);

        groupBox_2 = new QGroupBox(groupBoxConfig);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 3, -1, 11);
        verticalSpacer_4 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        labelRCMode = new QLabel(groupBox_2);
        labelRCMode->setObjectName(QStringLiteral("labelRCMode"));

        verticalLayout_4->addWidget(labelRCMode);

        cbxRateControlMode = new QComboBox(groupBox_2);
        cbxRateControlMode->setObjectName(QStringLiteral("cbxRateControlMode"));

        verticalLayout_4->addWidget(cbxRateControlMode);


        horizontalLayout_2->addLayout(verticalLayout_4);

        horizontalSpacer_2 = new QSpacerItem(16, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(2);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        labelQuantizer = new QLabel(groupBox_2);
        labelQuantizer->setObjectName(QStringLiteral("labelQuantizer"));

        verticalLayout_7->addWidget(labelQuantizer);

        spinQuantizer = new QDoubleSpinBox(groupBox_2);
        spinQuantizer->setObjectName(QStringLiteral("spinQuantizer"));
        spinQuantizer->setDecimals(1);
        spinQuantizer->setMaximum(52);
        spinQuantizer->setValue(22);

        verticalLayout_7->addWidget(spinQuantizer);


        horizontalLayout_2->addLayout(verticalLayout_7);

        horizontalSpacer_3 = new QSpacerItem(16, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        labelBitrate = new QLabel(groupBox_2);
        labelBitrate->setObjectName(QStringLiteral("labelBitrate"));

        verticalLayout_6->addWidget(labelBitrate);

        spinBitrate = new QSpinBox(groupBox_2);
        spinBitrate->setObjectName(QStringLiteral("spinBitrate"));
        spinBitrate->setMinimum(10);
        spinBitrate->setMaximum(800000);
        spinBitrate->setValue(2000);

        verticalLayout_6->addWidget(spinBitrate);


        horizontalLayout_2->addLayout(verticalLayout_6);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer_5 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);


        verticalLayout_15->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(groupBoxConfig);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        verticalLayout_8 = new QVBoxLayout(groupBox_3);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(-1, 3, -1, 11);
        verticalSpacer_6 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(2);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        labelPreset = new QLabel(groupBox_3);
        labelPreset->setObjectName(QStringLiteral("labelPreset"));

        verticalLayout_11->addWidget(labelPreset);

        cbxPreset = new QComboBox(groupBox_3);
        cbxPreset->setObjectName(QStringLiteral("cbxPreset"));

        verticalLayout_11->addWidget(cbxPreset);


        horizontalLayout_3->addLayout(verticalLayout_11);

        horizontalSpacer_4 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(2);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        labelTuning = new QLabel(groupBox_3);
        labelTuning->setObjectName(QStringLiteral("labelTuning"));

        verticalLayout_10->addWidget(labelTuning);

        cbxTuning = new QComboBox(groupBox_3);
        cbxTuning->setObjectName(QStringLiteral("cbxTuning"));

        verticalLayout_10->addWidget(cbxTuning);


        horizontalLayout_3->addLayout(verticalLayout_10);

        horizontalSpacer_5 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(2);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        labelProfile = new QLabel(groupBox_3);
        labelProfile->setObjectName(QStringLiteral("labelProfile"));

        verticalLayout_9->addWidget(labelProfile);

        cbxProfile = new QComboBox(groupBox_3);
        cbxProfile->setObjectName(QStringLiteral("cbxProfile"));

        verticalLayout_9->addWidget(cbxProfile);


        horizontalLayout_3->addLayout(verticalLayout_9);


        verticalLayout_8->addLayout(horizontalLayout_3);

        verticalSpacer_7 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_7);


        verticalLayout_15->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(groupBoxConfig);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        verticalLayout_13 = new QVBoxLayout(groupBox_4);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(-1, 3, -1, 7);
        verticalSpacer_8 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_8);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(0);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelCustomEncoderParams = new QLabel(groupBox_4);
        labelCustomEncoderParams->setObjectName(QStringLiteral("labelCustomEncoderParams"));
        labelCustomEncoderParams->setMinimumSize(QSize(150, 0));

        horizontalLayout_4->addWidget(labelCustomEncoderParams);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        labelHelpScreenEncoder = new QLabel(groupBox_4);
        labelHelpScreenEncoder->setObjectName(QStringLiteral("labelHelpScreenEncoder"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        labelHelpScreenEncoder->setPalette(palette);
        QFont font;
        font.setUnderline(true);
        labelHelpScreenEncoder->setFont(font);
        labelHelpScreenEncoder->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_4->addWidget(labelHelpScreenEncoder);


        verticalLayout_12->addLayout(horizontalLayout_4);

        editCustomEncoderParams = new QLineEdit(groupBox_4);
        editCustomEncoderParams->setObjectName(QStringLiteral("editCustomEncoderParams"));
        editCustomEncoderParams->setContextMenuPolicy(Qt::ActionsContextMenu);

        verticalLayout_12->addWidget(editCustomEncoderParams);

        verticalSpacer_11 = new QSpacerItem(20, 3, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_12->addItem(verticalSpacer_11);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        labelCustomPiperParams = new QLabel(groupBox_4);
        labelCustomPiperParams->setObjectName(QStringLiteral("labelCustomPiperParams"));
        labelCustomPiperParams->setMinimumSize(QSize(150, 0));

        horizontalLayout_8->addWidget(labelCustomPiperParams);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_12);

        labelHelpScreenCustomPiperParams = new QLabel(groupBox_4);
        labelHelpScreenCustomPiperParams->setObjectName(QStringLiteral("labelHelpScreenCustomPiperParams"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        labelHelpScreenCustomPiperParams->setPalette(palette1);
        labelHelpScreenCustomPiperParams->setFont(font);
        labelHelpScreenCustomPiperParams->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_8->addWidget(labelHelpScreenCustomPiperParams);


        verticalLayout_12->addLayout(horizontalLayout_8);

        editCustomPiperParams = new QLineEdit(groupBox_4);
        editCustomPiperParams->setObjectName(QStringLiteral("editCustomPiperParams"));
        editCustomPiperParams->setContextMenuPolicy(Qt::ActionsContextMenu);

        verticalLayout_12->addWidget(editCustomPiperParams);


        verticalLayout_13->addLayout(verticalLayout_12);

        verticalSpacer_9 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_9);


        verticalLayout_15->addWidget(groupBox_4);


        verticalLayout->addWidget(groupBoxConfig);

        frame = new QFrame(JobCreator);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBoxStartJobImmediately = new QCheckBox(JobCreator);
        checkBoxStartJobImmediately->setObjectName(QStringLiteral("checkBoxStartJobImmediately"));
        checkBoxStartJobImmediately->setEnabled(true);
        checkBoxStartJobImmediately->setChecked(false);

        horizontalLayout->addWidget(checkBoxStartJobImmediately);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonAccept = new QPushButton(JobCreator);
        buttonAccept->setObjectName(QStringLiteral("buttonAccept"));
        buttonAccept->setMinimumSize(QSize(112, 0));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/buttons/accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAccept->setIcon(icon2);

        horizontalLayout->addWidget(buttonAccept);

        buttonCancel = new QPushButton(JobCreator);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setMinimumSize(QSize(112, 0));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/buttons/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon3);

        horizontalLayout->addWidget(buttonCancel);


        verticalLayout->addLayout(horizontalLayout);

        QWidget::setTabOrder(editSource, buttonBrowseSource);
        QWidget::setTabOrder(buttonBrowseSource, editOutput);
        QWidget::setTabOrder(editOutput, buttonBrowseOutput);
        QWidget::setTabOrder(buttonBrowseOutput, cbxTemplate);
        QWidget::setTabOrder(cbxTemplate, buttonSaveTemplate);
        QWidget::setTabOrder(buttonSaveTemplate, buttonDeleteTemplate);
        QWidget::setTabOrder(buttonDeleteTemplate, cbxRateControlMode);
        QWidget::setTabOrder(cbxRateControlMode, spinBitrate);
        QWidget::setTabOrder(spinBitrate, cbxPreset);
        QWidget::setTabOrder(cbxPreset, cbxTuning);
        QWidget::setTabOrder(cbxTuning, cbxProfile);
        QWidget::setTabOrder(cbxProfile, editCustomEncoderParams);
        QWidget::setTabOrder(editCustomEncoderParams, checkBoxStartJobImmediately);
        QWidget::setTabOrder(checkBoxStartJobImmediately, buttonAccept);
        QWidget::setTabOrder(buttonAccept, buttonCancel);

        retranslateUi(JobCreator);

        cbxTemplate->setCurrentIndex(-1);
        cbxEncoderType->setCurrentIndex(-1);
        cbxEncoderArch->setCurrentIndex(-1);
        cbxEncoderVariant->setCurrentIndex(-1);
        cbxRateControlMode->setCurrentIndex(-1);
        cbxPreset->setCurrentIndex(-1);
        cbxTuning->setCurrentIndex(-1);
        cbxProfile->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(JobCreator);
    } // setupUi

    void retranslateUi(QDialog *JobCreator)
    {
        JobCreator->setWindowTitle(QApplication::translate("JobCreator", "Add Job", nullptr));
        groupBoxIO->setTitle(QApplication::translate("JobCreator", " Input / Output ", nullptr));
#ifndef QT_NO_TOOLTIP
        labelSource->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelSource->setText(QApplication::translate("JobCreator", "Source Media/Avisynth/VapourSynth File:", nullptr));
#ifndef QT_NO_TOOLTIP
        editSource->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editSource->setPlaceholderText(QApplication::translate("JobCreator", "Enable Drag and drop Event ...", nullptr));
        buttonBrowseSource->setText(QApplication::translate("JobCreator", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        labelOutput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelOutput->setText(QApplication::translate("JobCreator", "Output H.264/HEVC/MP4/MKV File:", nullptr));
#ifndef QT_NO_TOOLTIP
        editOutput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editOutput->setPlaceholderText(QApplication::translate("JobCreator", "Enable Drag and drop Event ...", nullptr));
        buttonBrowseOutput->setText(QApplication::translate("JobCreator", "...", nullptr));
        groupBoxConfig->setTitle(QApplication::translate("JobCreator", " Configuration ", nullptr));
#ifndef QT_NO_TOOLTIP
        labelTemplate->setToolTip(QApplication::translate("JobCreator", "Here you can load a user-defined template that you have saved before. Use the \"Save As\" button to save your current configuration to a new template.", nullptr));
#endif // QT_NO_TOOLTIP
        labelTemplate->setText(QApplication::translate("JobCreator", "Template:", nullptr));
#ifndef QT_NO_TOOLTIP
        cbxTemplate->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        buttonSaveTemplate->setText(QApplication::translate("JobCreator", "Save", nullptr));
        buttonDeleteTemplate->setText(QApplication::translate("JobCreator", "Delete", nullptr));
        groupBox_6->setTitle(QApplication::translate("JobCreator", " Encoder Selection ", nullptr));
        labelEncoderType->setText(QApplication::translate("JobCreator", "Encoder:", nullptr));
#ifndef QT_NO_TOOLTIP
        cbxEncoderType->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelEncoderArch->setText(QApplication::translate("JobCreator", "Architecture:", nullptr));
#ifndef QT_NO_TOOLTIP
        cbxEncoderArch->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelEncoderVariant->setText(QApplication::translate("JobCreator", "Variant:", nullptr));
#ifndef QT_NO_TOOLTIP
        cbxEncoderVariant->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupBox_2->setTitle(QApplication::translate("JobCreator", " Rate Control ", nullptr));
#ifndef QT_NO_TOOLTIP
        labelRCMode->setToolTip(QApplication::translate("JobCreator", "Select the x264 rate-control mode. Use 'CRF' mode to hit a specific level of quality or use '2-Pass' mode to hit a specific file size.", nullptr));
#endif // QT_NO_TOOLTIP
        labelRCMode->setText(QApplication::translate("JobCreator", "Mode:", nullptr));
#ifndef QT_NO_TOOLTIP
        cbxRateControlMode->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        labelQuantizer->setToolTip(QApplication::translate("JobCreator", "Select the quantizer or CRF value. Smaller value means better quality, but bigger file. Higher value means smaller file, but lower quality. A value of '0' triggers lossless mode.", nullptr));
#endif // QT_NO_TOOLTIP
        labelQuantizer->setText(QApplication::translate("JobCreator", "Quantizer/CRF:", nullptr));
#ifndef QT_NO_TOOLTIP
        spinQuantizer->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        labelBitrate->setToolTip(QApplication::translate("JobCreator", "Select the target average(!) bitrate, in kilobit/sec. Higher value means better quality, but bigger file. Lower value means smaller file, but lower quality.", nullptr));
#endif // QT_NO_TOOLTIP
        labelBitrate->setText(QApplication::translate("JobCreator", "Target Bitrate (kbps):", nullptr));
#ifndef QT_NO_TOOLTIP
        spinBitrate->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupBox_3->setTitle(QApplication::translate("JobCreator", " Basic Encoder Options ", nullptr));
#ifndef QT_NO_TOOLTIP
        labelPreset->setToolTip(QApplication::translate("JobCreator", "This option controls the \"Speed -vs- Quality\" trade-off. Use a slower preset to improve the quality at the same bitrate (file size). Use a faster preset to save encoding time, at the cost of reduced quality.", nullptr));
#endif // QT_NO_TOOLTIP
        labelPreset->setText(QApplication::translate("JobCreator", "Preset:", nullptr));
#ifndef QT_NO_TOOLTIP
        cbxPreset->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        labelTuning->setToolTip(QApplication::translate("JobCreator", "This option tweaks x264 for a specific type of source/content. For real-life footage, CGI and most other stuff, use the \"Film\" option. For anime/cartoon use the \"Animation\" option.", nullptr));
#endif // QT_NO_TOOLTIP
        labelTuning->setText(QApplication::translate("JobCreator", "Tuning:", nullptr));
#ifndef QT_NO_TOOLTIP
        cbxTuning->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        labelProfile->setToolTip(QApplication::translate("JobCreator", "This option can be used to enforce the restrictions of a specific H.264/AVC Proifle, though it won't force a higher profile than needed. Use \"Auto\" for an unrestricted encode.", nullptr));
#endif // QT_NO_TOOLTIP
        labelProfile->setText(QApplication::translate("JobCreator", "Profile:", nullptr));
#ifndef QT_NO_TOOLTIP
        cbxProfile->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupBox_4->setTitle(QApplication::translate("JobCreator", "Advanced Encoder Options ", nullptr));
#ifndef QT_NO_TOOLTIP
        labelCustomEncoderParams->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelCustomEncoderParams->setText(QApplication::translate("JobCreator", "Custom Encoder Parameters:", nullptr));
#ifndef QT_NO_TOOLTIP
        labelHelpScreenEncoder->setToolTip(QApplication::translate("JobCreator", "Click here to show a detailed list of all command-line options available in your build of x264!", nullptr));
#endif // QT_NO_TOOLTIP
        labelHelpScreenEncoder->setText(QApplication::translate("JobCreator", "Show Help Screen", nullptr));
#ifndef QT_NO_TOOLTIP
        editCustomEncoderParams->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editCustomEncoderParams->setPlaceholderText(QApplication::translate("JobCreator", "You can enter custom command-line options here...", nullptr));
        labelCustomPiperParams->setText(QApplication::translate("JobCreator", "Custom Piper Parameters:", nullptr));
#ifndef QT_NO_TOOLTIP
        labelHelpScreenCustomPiperParams->setToolTip(QApplication::translate("JobCreator", "Click here to show a detailed list of all command-line options available in your build of Avs2YUV!", nullptr));
#endif // QT_NO_TOOLTIP
        labelHelpScreenCustomPiperParams->setText(QApplication::translate("JobCreator", "Show Help Screen", nullptr));
#ifndef QT_NO_TOOLTIP
        editCustomPiperParams->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editCustomPiperParams->setPlaceholderText(QApplication::translate("JobCreator", "You can enter custom command-line options here...", nullptr));
        checkBoxStartJobImmediately->setText(QApplication::translate("JobCreator", "Start Job Immediately", nullptr));
        buttonAccept->setText(QApplication::translate("JobCreator", "Add Job", nullptr));
        buttonCancel->setText(QApplication::translate("JobCreator", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JobCreator: public Ui_JobCreator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOB_CREATOR_H
