/********************************************************************************
** Form generated from reading UI file 'script_creator.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCRIPT_CREATOR_H
#define UI_SCRIPT_CREATOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "./script/script_editor.h"

QT_BEGIN_NAMESPACE

class Ui_ScriptCreator
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_source;
    QVBoxLayout *verticalLayout_20;
    QGroupBox *groupBoxSource;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_31;
    QLabel *labelSource;
    QSpacerItem *horizontalSpacer_17;
    QLabel *labelSourcePreview;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *editSource;
    QPushButton *buttonBrowseSource;
    QVBoxLayout *verticalLayout_6;
    QLabel *labelOutput;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *editOutput;
    QPushButton *buttonBrowseOutput;
    QGroupBox *groupBoxSourceFilter;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelSourceFilter;
    QComboBox *comboBoxSourceFilter;
    QSpacerItem *horizontalSpacer_3;
    QStackedWidget *stackedWidgetSourceFilter;
    QWidget *page_lwl;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_17;
    QVBoxLayout *verticalLayout_17;
    QLabel *labelSourceFilterLWLFormat;
    QComboBox *comboBoxSourceFilterLWLFormat;
    QVBoxLayout *verticalLayout_18;
    QLabel *labelSourceFilterLWLDecoder;
    QComboBox *comboBoxSourceFilterLWLDecoder;
    QHBoxLayout *horizontalLayout_16;
    QCheckBox *checkBoxSourceFilterLWLFPS;
    QSpinBox *spinBoxSourceFilterLWLFpsnum;
    QLabel *labelSourceFilterLWLFPS2;
    QSpinBox *spinBoxSourceFilterLWLFpsden;
    QSpacerItem *horizontalSpacer_13;
    QCheckBox *checkBoxSourceFilterLSMASH;
    QWidget *page_ffms2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *checkBoxSourceFilterFFmpegFPS;
    QSpinBox *spinBoxSourceFilterFFmpegFpsnum;
    QLabel *labelSourceFilterFFmpegFPS2;
    QSpinBox *spinBoxSourceFilterFFmpegFpsden;
    QSpacerItem *horizontalSpacer_14;
    QLabel *dotGridFFMS2;
    QWidget *page_dgnv;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_20;
    QCheckBox *checkBoxSourceFilterDGNVDeinterlacer;
    QComboBox *comboBoxSourceFilterDGNVDeinterlacer;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_21;
    QCheckBox *checkBoxSourceFilterDGNVResizer;
    QSpinBox *spinBoxSourceFilterDGNVResizeW;
    QSpinBox *spinBoxSourceFilterDGNVResizeH;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_24;
    QCheckBox *checkBoxSourceFilterDGNVDeinterlacer_2;
    QComboBox *comboBoxSourceFilterDGNVFieldOperation;
    QSpacerItem *horizontalSpacer_15;
    QWidget *page_dg;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_19;
    QVBoxLayout *verticalLayout_21;
    QLabel *labelSourceFilterDGFieldOperation;
    QComboBox *comboBoxSourceFilterDGFieldOperation;
    QCheckBox *checkBoxD2VWitch;
    QLabel *labelSourceFilterDGFieldOperation_2;
    QSpacerItem *horizontalSpacer_9;
    QLabel *dotGridDGNV;
    QWidget *page_dss;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_22;
    QCheckBox *checkBoxSourceFilterDSSConvertFPS;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_23;
    QCheckBox *checkBoxSourceFilterDSSFPS;
    QDoubleSpinBox *doubleSpinBoxSourceFilterDSSFPS;
    QSpacerItem *horizontalSpacer_12;
    QLabel *dotGridDSS;
    QGroupBox *groupBoxCropResize;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *checkBoxCrop;
    QSpinBox *spinBoxCropLeft;
    QSpinBox *spinBoxCropTop;
    QSpinBox *spinBoxCropRight;
    QSpinBox *spinBoxCropButtom;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *checkBoxFillMargins;
    QSpinBox *spinBoxFillMarginsLeft;
    QSpinBox *spinBoxFillMarginsTop;
    QSpinBox *spinBoxFillMarginsRight;
    QSpinBox *spinBoxFillMarginsButtom;
    QHBoxLayout *horizontalLayout_13;
    QCheckBox *checkBoxResize;
    QComboBox *comboBoxResizeFilter;
    QSpinBox *spinBoxResizeW;
    QSpinBox *spinBoxResizeH;
    QGroupBox *groupBoxFPS;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBoxFPS;
    QComboBox *comboBoxFPSFilter;
    QSpinBox *spinBoxFPSFilterFpsnum;
    QLabel *labelFPSFilterFPS2;
    QSpinBox *spinBoxFPSFilterFpsden;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_18;
    QLineEdit *editTimeCodeFile;
    QPushButton *buttonBrowseTimeCodeFile;
    QWidget *tab_filters;
    QVBoxLayout *verticalLayout_28;
    QGroupBox *groupBoxDeinterlacingInverseTelecine;
    QVBoxLayout *verticalLayout_27;
    QHBoxLayout *horizontalLayout_29;
    QVBoxLayout *verticalLayout_22;
    QLabel *labelDeinterlacingSourceType;
    QComboBox *comboBoxDeinterlacingSourceType;
    QVBoxLayout *verticalLayout_23;
    QLabel *labelDeinterlacingFieldOrder;
    QComboBox *comboBoxDeinterlacingFieldOrder;
    QVBoxLayout *verticalLayout_25;
    QLabel *labelDeinterlacingFrameRate;
    QComboBox *comboBoxDeinterlacingFrameRate;
    QHBoxLayout *horizontalLayout_30;
    QVBoxLayout *verticalLayout_24;
    QLabel *labelDeinterlacingFilter;
    QComboBox *comboBoxDeinterlacingFilter;
    QVBoxLayout *verticalLayout_26;
    QLabel *labelDeinterlacingPreset;
    QComboBox *comboBoxDeinterlacingPreset;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *groupBoxLogo;
    QVBoxLayout *verticalLayout_15;
    QVBoxLayout *verticalLayout_11;
    QCheckBox *checkBoxDeleteLogoDataInput;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *editDeleteLogoDataInput;
    QPushButton *buttonBrowseDeleteLogoDataInput;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelDelogoAlignment;
    QSpinBox *spinBoxDelogoAlignment;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_13;
    QCheckBox *checkBoxAddLogoDataInput;
    QHBoxLayout *horizontalLayout_14;
    QLineEdit *editAddLogoDataInput;
    QPushButton *buttonBrowseAddLogoDataInput;
    QHBoxLayout *horizontalLayout_15;
    QLabel *labelAddLogoAlignment;
    QSpinBox *spinBoxAddLogoAlignment;
    QSpacerItem *horizontalSpacer_7;
    QGroupBox *groupBoxDenoise;
    QHBoxLayout *horizontalLayout_28;
    QCheckBox *checkBoxDenoise;
    QComboBox *comboBoxDenoise;
    QSpacerItem *horizontalSpacer_16;
    QGroupBox *groupBoxSubtitle;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBoxSubtitle;
    QComboBox *comboBoxSubtitle;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *editSubtitle;
    QPushButton *buttonBrowseSubtitle;
    QWidget *tab_script;
    QVBoxLayout *verticalLayout_2;
    ScriptEditor *scriptEditor;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxNotAddJobOnSaved;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonPreview;
    QPushButton *buttonSave;

    void setupUi(QWidget *ScriptCreator)
    {
        if (ScriptCreator->objectName().isEmpty())
            ScriptCreator->setObjectName(QStringLiteral("ScriptCreator"));
        ScriptCreator->resize(630, 650);
        ScriptCreator->setAcceptDrops(true);
        verticalLayout = new QVBoxLayout(ScriptCreator);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(ScriptCreator);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setAutoFillBackground(false);
        tab_source = new QWidget();
        tab_source->setObjectName(QStringLiteral("tab_source"));
        verticalLayout_20 = new QVBoxLayout(tab_source);
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        verticalLayout_20->setContentsMargins(-1, 3, -1, -1);
        groupBoxSource = new QGroupBox(tab_source);
        groupBoxSource->setObjectName(QStringLiteral("groupBoxSource"));
        groupBoxSource->setCheckable(false);
        verticalLayout_5 = new QVBoxLayout(groupBoxSource);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setObjectName(QStringLiteral("horizontalLayout_31"));
        labelSource = new QLabel(groupBoxSource);
        labelSource->setObjectName(QStringLiteral("labelSource"));

        horizontalLayout_31->addWidget(labelSource);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_31->addItem(horizontalSpacer_17);

        labelSourcePreview = new QLabel(groupBoxSource);
        labelSourcePreview->setObjectName(QStringLiteral("labelSourcePreview"));
        QFont font;
        font.setUnderline(true);
        labelSourcePreview->setFont(font);
        labelSourcePreview->setCursor(QCursor(Qt::PointingHandCursor));
        labelSourcePreview->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));

        horizontalLayout_31->addWidget(labelSourcePreview);


        verticalLayout_5->addLayout(horizontalLayout_31);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        editSource = new QLineEdit(groupBoxSource);
        editSource->setObjectName(QStringLiteral("editSource"));
        editSource->setMinimumSize(QSize(0, 25));
        editSource->setStyleSheet(QStringLiteral(""));
        editSource->setReadOnly(true);

        horizontalLayout_5->addWidget(editSource);

        buttonBrowseSource = new QPushButton(groupBoxSource);
        buttonBrowseSource->setObjectName(QStringLiteral("buttonBrowseSource"));
        buttonBrowseSource->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_5->addWidget(buttonBrowseSource);


        verticalLayout_5->addLayout(horizontalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        labelOutput = new QLabel(groupBoxSource);
        labelOutput->setObjectName(QStringLiteral("labelOutput"));

        verticalLayout_6->addWidget(labelOutput);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(3);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        editOutput = new QLineEdit(groupBoxSource);
        editOutput->setObjectName(QStringLiteral("editOutput"));
        editOutput->setMinimumSize(QSize(0, 25));
        editOutput->setStyleSheet(QStringLiteral(""));
        editOutput->setReadOnly(true);

        horizontalLayout_6->addWidget(editOutput);

        buttonBrowseOutput = new QPushButton(groupBoxSource);
        buttonBrowseOutput->setObjectName(QStringLiteral("buttonBrowseOutput"));
        buttonBrowseOutput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_6->addWidget(buttonBrowseOutput);


        verticalLayout_6->addLayout(horizontalLayout_6);


        verticalLayout_5->addLayout(verticalLayout_6);

        groupBoxSourceFilter = new QGroupBox(groupBoxSource);
        groupBoxSourceFilter->setObjectName(QStringLiteral("groupBoxSourceFilter"));
        groupBoxSourceFilter->setMinimumSize(QSize(0, 0));
        groupBoxSourceFilter->setFlat(false);
        verticalLayout_3 = new QVBoxLayout(groupBoxSourceFilter);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        labelSourceFilter = new QLabel(groupBoxSourceFilter);
        labelSourceFilter->setObjectName(QStringLiteral("labelSourceFilter"));
        labelSourceFilter->setMinimumSize(QSize(50, 0));

        horizontalLayout_4->addWidget(labelSourceFilter);

        comboBoxSourceFilter = new QComboBox(groupBoxSourceFilter);
        comboBoxSourceFilter->addItem(QString());
        comboBoxSourceFilter->addItem(QString());
        comboBoxSourceFilter->addItem(QString());
        comboBoxSourceFilter->addItem(QString());
        comboBoxSourceFilter->addItem(QString());
        comboBoxSourceFilter->setObjectName(QStringLiteral("comboBoxSourceFilter"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxSourceFilter->sizePolicy().hasHeightForWidth());
        comboBoxSourceFilter->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(comboBoxSourceFilter);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_4);

        stackedWidgetSourceFilter = new QStackedWidget(groupBoxSourceFilter);
        stackedWidgetSourceFilter->setObjectName(QStringLiteral("stackedWidgetSourceFilter"));
        page_lwl = new QWidget();
        page_lwl->setObjectName(QStringLiteral("page_lwl"));
        verticalLayout_14 = new QVBoxLayout(page_lwl);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 5, 0, 0);
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(15);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(3);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        labelSourceFilterLWLFormat = new QLabel(page_lwl);
        labelSourceFilterLWLFormat->setObjectName(QStringLiteral("labelSourceFilterLWLFormat"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelSourceFilterLWLFormat->sizePolicy().hasHeightForWidth());
        labelSourceFilterLWLFormat->setSizePolicy(sizePolicy1);
        labelSourceFilterLWLFormat->setMinimumSize(QSize(50, 0));

        verticalLayout_17->addWidget(labelSourceFilterLWLFormat);

        comboBoxSourceFilterLWLFormat = new QComboBox(page_lwl);
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->addItem(QString());
        comboBoxSourceFilterLWLFormat->setObjectName(QStringLiteral("comboBoxSourceFilterLWLFormat"));
        sizePolicy.setHeightForWidth(comboBoxSourceFilterLWLFormat->sizePolicy().hasHeightForWidth());
        comboBoxSourceFilterLWLFormat->setSizePolicy(sizePolicy);

        verticalLayout_17->addWidget(comboBoxSourceFilterLWLFormat);


        horizontalLayout_17->addLayout(verticalLayout_17);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(3);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        labelSourceFilterLWLDecoder = new QLabel(page_lwl);
        labelSourceFilterLWLDecoder->setObjectName(QStringLiteral("labelSourceFilterLWLDecoder"));
        sizePolicy1.setHeightForWidth(labelSourceFilterLWLDecoder->sizePolicy().hasHeightForWidth());
        labelSourceFilterLWLDecoder->setSizePolicy(sizePolicy1);
        labelSourceFilterLWLDecoder->setMinimumSize(QSize(50, 0));

        verticalLayout_18->addWidget(labelSourceFilterLWLDecoder);

        comboBoxSourceFilterLWLDecoder = new QComboBox(page_lwl);
        comboBoxSourceFilterLWLDecoder->addItem(QString());
        comboBoxSourceFilterLWLDecoder->addItem(QString());
        comboBoxSourceFilterLWLDecoder->addItem(QString());
        comboBoxSourceFilterLWLDecoder->addItem(QString());
        comboBoxSourceFilterLWLDecoder->addItem(QString());
        comboBoxSourceFilterLWLDecoder->addItem(QString());
        comboBoxSourceFilterLWLDecoder->addItem(QString());
        comboBoxSourceFilterLWLDecoder->addItem(QString());
        comboBoxSourceFilterLWLDecoder->addItem(QString());
        comboBoxSourceFilterLWLDecoder->setObjectName(QStringLiteral("comboBoxSourceFilterLWLDecoder"));
        sizePolicy.setHeightForWidth(comboBoxSourceFilterLWLDecoder->sizePolicy().hasHeightForWidth());
        comboBoxSourceFilterLWLDecoder->setSizePolicy(sizePolicy);

        verticalLayout_18->addWidget(comboBoxSourceFilterLWLDecoder);


        horizontalLayout_17->addLayout(verticalLayout_18);


        verticalLayout_14->addLayout(horizontalLayout_17);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        checkBoxSourceFilterLWLFPS = new QCheckBox(page_lwl);
        checkBoxSourceFilterLWLFPS->setObjectName(QStringLiteral("checkBoxSourceFilterLWLFPS"));

        horizontalLayout_16->addWidget(checkBoxSourceFilterLWLFPS);

        spinBoxSourceFilterLWLFpsnum = new QSpinBox(page_lwl);
        spinBoxSourceFilterLWLFpsnum->setObjectName(QStringLiteral("spinBoxSourceFilterLWLFpsnum"));
        spinBoxSourceFilterLWLFpsnum->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinBoxSourceFilterLWLFpsnum->sizePolicy().hasHeightForWidth());
        spinBoxSourceFilterLWLFpsnum->setSizePolicy(sizePolicy2);
        spinBoxSourceFilterLWLFpsnum->setMaximum(999999999);
        spinBoxSourceFilterLWLFpsnum->setValue(24000);

        horizontalLayout_16->addWidget(spinBoxSourceFilterLWLFpsnum);

        labelSourceFilterLWLFPS2 = new QLabel(page_lwl);
        labelSourceFilterLWLFPS2->setObjectName(QStringLiteral("labelSourceFilterLWLFPS2"));
        labelSourceFilterLWLFPS2->setEnabled(false);
        sizePolicy1.setHeightForWidth(labelSourceFilterLWLFPS2->sizePolicy().hasHeightForWidth());
        labelSourceFilterLWLFPS2->setSizePolicy(sizePolicy1);
        labelSourceFilterLWLFPS2->setMinimumSize(QSize(0, 0));
        labelSourceFilterLWLFPS2->setMaximumSize(QSize(16777215, 16777215));
        labelSourceFilterLWLFPS2->setTextFormat(Qt::AutoText);
        labelSourceFilterLWLFPS2->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(labelSourceFilterLWLFPS2);

        spinBoxSourceFilterLWLFpsden = new QSpinBox(page_lwl);
        spinBoxSourceFilterLWLFpsden->setObjectName(QStringLiteral("spinBoxSourceFilterLWLFpsden"));
        spinBoxSourceFilterLWLFpsden->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinBoxSourceFilterLWLFpsden->sizePolicy().hasHeightForWidth());
        spinBoxSourceFilterLWLFpsden->setSizePolicy(sizePolicy2);
        spinBoxSourceFilterLWLFpsden->setMaximum(999999999);
        spinBoxSourceFilterLWLFpsden->setValue(1000);

        horizontalLayout_16->addWidget(spinBoxSourceFilterLWLFpsden);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_13);

        checkBoxSourceFilterLSMASH = new QCheckBox(page_lwl);
        checkBoxSourceFilterLSMASH->setObjectName(QStringLiteral("checkBoxSourceFilterLSMASH"));

        horizontalLayout_16->addWidget(checkBoxSourceFilterLSMASH);


        verticalLayout_14->addLayout(horizontalLayout_16);

        stackedWidgetSourceFilter->addWidget(page_lwl);
        page_ffms2 = new QWidget();
        page_ffms2->setObjectName(QStringLiteral("page_ffms2"));
        verticalLayout_7 = new QVBoxLayout(page_ffms2);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        checkBoxSourceFilterFFmpegFPS = new QCheckBox(page_ffms2);
        checkBoxSourceFilterFFmpegFPS->setObjectName(QStringLiteral("checkBoxSourceFilterFFmpegFPS"));

        horizontalLayout_8->addWidget(checkBoxSourceFilterFFmpegFPS);

        spinBoxSourceFilterFFmpegFpsnum = new QSpinBox(page_ffms2);
        spinBoxSourceFilterFFmpegFpsnum->setObjectName(QStringLiteral("spinBoxSourceFilterFFmpegFpsnum"));
        spinBoxSourceFilterFFmpegFpsnum->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinBoxSourceFilterFFmpegFpsnum->sizePolicy().hasHeightForWidth());
        spinBoxSourceFilterFFmpegFpsnum->setSizePolicy(sizePolicy2);
        spinBoxSourceFilterFFmpegFpsnum->setMinimum(0);
        spinBoxSourceFilterFFmpegFpsnum->setMaximum(999999999);

        horizontalLayout_8->addWidget(spinBoxSourceFilterFFmpegFpsnum);

        labelSourceFilterFFmpegFPS2 = new QLabel(page_ffms2);
        labelSourceFilterFFmpegFPS2->setObjectName(QStringLiteral("labelSourceFilterFFmpegFPS2"));
        labelSourceFilterFFmpegFPS2->setEnabled(false);
        sizePolicy1.setHeightForWidth(labelSourceFilterFFmpegFPS2->sizePolicy().hasHeightForWidth());
        labelSourceFilterFFmpegFPS2->setSizePolicy(sizePolicy1);
        labelSourceFilterFFmpegFPS2->setMinimumSize(QSize(0, 0));
        labelSourceFilterFFmpegFPS2->setMaximumSize(QSize(16777215, 16777215));
        labelSourceFilterFFmpegFPS2->setTextFormat(Qt::AutoText);
        labelSourceFilterFFmpegFPS2->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(labelSourceFilterFFmpegFPS2);

        spinBoxSourceFilterFFmpegFpsden = new QSpinBox(page_ffms2);
        spinBoxSourceFilterFFmpegFpsden->setObjectName(QStringLiteral("spinBoxSourceFilterFFmpegFpsden"));
        spinBoxSourceFilterFFmpegFpsden->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinBoxSourceFilterFFmpegFpsden->sizePolicy().hasHeightForWidth());
        spinBoxSourceFilterFFmpegFpsden->setSizePolicy(sizePolicy2);
        spinBoxSourceFilterFFmpegFpsden->setMinimum(0);
        spinBoxSourceFilterFFmpegFpsden->setMaximum(999999999);
        spinBoxSourceFilterFFmpegFpsden->setSingleStep(1);

        horizontalLayout_8->addWidget(spinBoxSourceFilterFFmpegFpsden);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_14);


        verticalLayout_7->addLayout(horizontalLayout_8);

        dotGridFFMS2 = new QLabel(page_ffms2);
        dotGridFFMS2->setObjectName(QStringLiteral("dotGridFFMS2"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dotGridFFMS2->sizePolicy().hasHeightForWidth());
        dotGridFFMS2->setSizePolicy(sizePolicy3);

        verticalLayout_7->addWidget(dotGridFFMS2);

        stackedWidgetSourceFilter->addWidget(page_ffms2);
        page_dgnv = new QWidget();
        page_dgnv->setObjectName(QStringLiteral("page_dgnv"));
        verticalLayout_9 = new QVBoxLayout(page_dgnv);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        checkBoxSourceFilterDGNVDeinterlacer = new QCheckBox(page_dgnv);
        checkBoxSourceFilterDGNVDeinterlacer->setObjectName(QStringLiteral("checkBoxSourceFilterDGNVDeinterlacer"));
        checkBoxSourceFilterDGNVDeinterlacer->setEnabled(true);
        checkBoxSourceFilterDGNVDeinterlacer->setCheckable(false);

        horizontalLayout_20->addWidget(checkBoxSourceFilterDGNVDeinterlacer);

        comboBoxSourceFilterDGNVDeinterlacer = new QComboBox(page_dgnv);
        comboBoxSourceFilterDGNVDeinterlacer->addItem(QString());
        comboBoxSourceFilterDGNVDeinterlacer->addItem(QString());
        comboBoxSourceFilterDGNVDeinterlacer->addItem(QString());
        comboBoxSourceFilterDGNVDeinterlacer->setObjectName(QStringLiteral("comboBoxSourceFilterDGNVDeinterlacer"));
        sizePolicy.setHeightForWidth(comboBoxSourceFilterDGNVDeinterlacer->sizePolicy().hasHeightForWidth());
        comboBoxSourceFilterDGNVDeinterlacer->setSizePolicy(sizePolicy);

        horizontalLayout_20->addWidget(comboBoxSourceFilterDGNVDeinterlacer);

        horizontalSpacer_8 = new QSpacerItem(241, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_8);


        verticalLayout_9->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        checkBoxSourceFilterDGNVResizer = new QCheckBox(page_dgnv);
        checkBoxSourceFilterDGNVResizer->setObjectName(QStringLiteral("checkBoxSourceFilterDGNVResizer"));

        horizontalLayout_21->addWidget(checkBoxSourceFilterDGNVResizer);

        spinBoxSourceFilterDGNVResizeW = new QSpinBox(page_dgnv);
        spinBoxSourceFilterDGNVResizeW->setObjectName(QStringLiteral("spinBoxSourceFilterDGNVResizeW"));
        spinBoxSourceFilterDGNVResizeW->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinBoxSourceFilterDGNVResizeW->sizePolicy().hasHeightForWidth());
        spinBoxSourceFilterDGNVResizeW->setSizePolicy(sizePolicy2);
        spinBoxSourceFilterDGNVResizeW->setMinimum(0);
        spinBoxSourceFilterDGNVResizeW->setMaximum(999999999);

        horizontalLayout_21->addWidget(spinBoxSourceFilterDGNVResizeW);

        spinBoxSourceFilterDGNVResizeH = new QSpinBox(page_dgnv);
        spinBoxSourceFilterDGNVResizeH->setObjectName(QStringLiteral("spinBoxSourceFilterDGNVResizeH"));
        spinBoxSourceFilterDGNVResizeH->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinBoxSourceFilterDGNVResizeH->sizePolicy().hasHeightForWidth());
        spinBoxSourceFilterDGNVResizeH->setSizePolicy(sizePolicy2);
        spinBoxSourceFilterDGNVResizeH->setMinimum(0);
        spinBoxSourceFilterDGNVResizeH->setMaximum(999999999);

        horizontalLayout_21->addWidget(spinBoxSourceFilterDGNVResizeH);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_10);


        verticalLayout_9->addLayout(horizontalLayout_21);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        checkBoxSourceFilterDGNVDeinterlacer_2 = new QCheckBox(page_dgnv);
        checkBoxSourceFilterDGNVDeinterlacer_2->setObjectName(QStringLiteral("checkBoxSourceFilterDGNVDeinterlacer_2"));
        checkBoxSourceFilterDGNVDeinterlacer_2->setCheckable(false);

        horizontalLayout_24->addWidget(checkBoxSourceFilterDGNVDeinterlacer_2);

        comboBoxSourceFilterDGNVFieldOperation = new QComboBox(page_dgnv);
        comboBoxSourceFilterDGNVFieldOperation->addItem(QString());
        comboBoxSourceFilterDGNVFieldOperation->addItem(QString());
        comboBoxSourceFilterDGNVFieldOperation->addItem(QString());
        comboBoxSourceFilterDGNVFieldOperation->setObjectName(QStringLiteral("comboBoxSourceFilterDGNVFieldOperation"));
        sizePolicy.setHeightForWidth(comboBoxSourceFilterDGNVFieldOperation->sizePolicy().hasHeightForWidth());
        comboBoxSourceFilterDGNVFieldOperation->setSizePolicy(sizePolicy);

        horizontalLayout_24->addWidget(comboBoxSourceFilterDGNVFieldOperation);

        horizontalSpacer_15 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_15);


        verticalLayout_9->addLayout(horizontalLayout_24);

        stackedWidgetSourceFilter->addWidget(page_dgnv);
        page_dg = new QWidget();
        page_dg->setObjectName(QStringLiteral("page_dg"));
        verticalLayout_8 = new QVBoxLayout(page_dg);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        labelSourceFilterDGFieldOperation = new QLabel(page_dg);
        labelSourceFilterDGFieldOperation->setObjectName(QStringLiteral("labelSourceFilterDGFieldOperation"));

        verticalLayout_21->addWidget(labelSourceFilterDGFieldOperation);

        comboBoxSourceFilterDGFieldOperation = new QComboBox(page_dg);
        comboBoxSourceFilterDGFieldOperation->addItem(QString());
        comboBoxSourceFilterDGFieldOperation->addItem(QString());
        comboBoxSourceFilterDGFieldOperation->addItem(QString());
        comboBoxSourceFilterDGFieldOperation->setObjectName(QStringLiteral("comboBoxSourceFilterDGFieldOperation"));
        sizePolicy.setHeightForWidth(comboBoxSourceFilterDGFieldOperation->sizePolicy().hasHeightForWidth());
        comboBoxSourceFilterDGFieldOperation->setSizePolicy(sizePolicy);

        verticalLayout_21->addWidget(comboBoxSourceFilterDGFieldOperation);


        horizontalLayout_19->addLayout(verticalLayout_21);

        checkBoxD2VWitch = new QCheckBox(page_dg);
        checkBoxD2VWitch->setObjectName(QStringLiteral("checkBoxD2VWitch"));

        horizontalLayout_19->addWidget(checkBoxD2VWitch);

        labelSourceFilterDGFieldOperation_2 = new QLabel(page_dg);
        labelSourceFilterDGFieldOperation_2->setObjectName(QStringLiteral("labelSourceFilterDGFieldOperation_2"));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setItalic(true);
        font1.setUnderline(false);
        font1.setWeight(50);
        labelSourceFilterDGFieldOperation_2->setFont(font1);

        horizontalLayout_19->addWidget(labelSourceFilterDGFieldOperation_2);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_9);


        verticalLayout_8->addLayout(horizontalLayout_19);

        dotGridDGNV = new QLabel(page_dg);
        dotGridDGNV->setObjectName(QStringLiteral("dotGridDGNV"));
        sizePolicy3.setHeightForWidth(dotGridDGNV->sizePolicy().hasHeightForWidth());
        dotGridDGNV->setSizePolicy(sizePolicy3);

        verticalLayout_8->addWidget(dotGridDGNV);

        stackedWidgetSourceFilter->addWidget(page_dg);
        page_dss = new QWidget();
        page_dss->setObjectName(QStringLiteral("page_dss"));
        verticalLayout_10 = new QVBoxLayout(page_dss);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        checkBoxSourceFilterDSSConvertFPS = new QCheckBox(page_dss);
        checkBoxSourceFilterDSSConvertFPS->setObjectName(QStringLiteral("checkBoxSourceFilterDSSConvertFPS"));
        checkBoxSourceFilterDSSConvertFPS->setChecked(true);

        horizontalLayout_22->addWidget(checkBoxSourceFilterDSSConvertFPS);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_11);


        verticalLayout_10->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        checkBoxSourceFilterDSSFPS = new QCheckBox(page_dss);
        checkBoxSourceFilterDSSFPS->setObjectName(QStringLiteral("checkBoxSourceFilterDSSFPS"));
        checkBoxSourceFilterDSSFPS->setChecked(true);

        horizontalLayout_23->addWidget(checkBoxSourceFilterDSSFPS);

        doubleSpinBoxSourceFilterDSSFPS = new QDoubleSpinBox(page_dss);
        doubleSpinBoxSourceFilterDSSFPS->setObjectName(QStringLiteral("doubleSpinBoxSourceFilterDSSFPS"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(doubleSpinBoxSourceFilterDSSFPS->sizePolicy().hasHeightForWidth());
        doubleSpinBoxSourceFilterDSSFPS->setSizePolicy(sizePolicy4);
        doubleSpinBoxSourceFilterDSSFPS->setDecimals(3);
        doubleSpinBoxSourceFilterDSSFPS->setMaximum(1e+45);
        doubleSpinBoxSourceFilterDSSFPS->setSingleStep(1);
        doubleSpinBoxSourceFilterDSSFPS->setValue(24);

        horizontalLayout_23->addWidget(doubleSpinBoxSourceFilterDSSFPS);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_12);


        verticalLayout_10->addLayout(horizontalLayout_23);

        dotGridDSS = new QLabel(page_dss);
        dotGridDSS->setObjectName(QStringLiteral("dotGridDSS"));
        sizePolicy3.setHeightForWidth(dotGridDSS->sizePolicy().hasHeightForWidth());
        dotGridDSS->setSizePolicy(sizePolicy3);

        verticalLayout_10->addWidget(dotGridDSS);

        stackedWidgetSourceFilter->addWidget(page_dss);

        verticalLayout_3->addWidget(stackedWidgetSourceFilter);


        verticalLayout_5->addWidget(groupBoxSourceFilter);


        verticalLayout_20->addWidget(groupBoxSource);

        groupBoxCropResize = new QGroupBox(tab_source);
        groupBoxCropResize->setObjectName(QStringLiteral("groupBoxCropResize"));
        verticalLayout_12 = new QVBoxLayout(groupBoxCropResize);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        checkBoxCrop = new QCheckBox(groupBoxCropResize);
        checkBoxCrop->setObjectName(QStringLiteral("checkBoxCrop"));
        checkBoxCrop->setMinimumSize(QSize(100, 0));

        horizontalLayout_11->addWidget(checkBoxCrop);

        spinBoxCropLeft = new QSpinBox(groupBoxCropResize);
        spinBoxCropLeft->setObjectName(QStringLiteral("spinBoxCropLeft"));
        spinBoxCropLeft->setEnabled(false);
        spinBoxCropLeft->setMaximum(999999999);

        horizontalLayout_11->addWidget(spinBoxCropLeft);

        spinBoxCropTop = new QSpinBox(groupBoxCropResize);
        spinBoxCropTop->setObjectName(QStringLiteral("spinBoxCropTop"));
        spinBoxCropTop->setEnabled(false);
        spinBoxCropTop->setMaximum(999999999);

        horizontalLayout_11->addWidget(spinBoxCropTop);

        spinBoxCropRight = new QSpinBox(groupBoxCropResize);
        spinBoxCropRight->setObjectName(QStringLiteral("spinBoxCropRight"));
        spinBoxCropRight->setEnabled(false);
        spinBoxCropRight->setMaximum(999999999);

        horizontalLayout_11->addWidget(spinBoxCropRight);

        spinBoxCropButtom = new QSpinBox(groupBoxCropResize);
        spinBoxCropButtom->setObjectName(QStringLiteral("spinBoxCropButtom"));
        spinBoxCropButtom->setEnabled(false);
        spinBoxCropButtom->setMaximum(999999999);

        horizontalLayout_11->addWidget(spinBoxCropButtom);


        verticalLayout_12->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        checkBoxFillMargins = new QCheckBox(groupBoxCropResize);
        checkBoxFillMargins->setObjectName(QStringLiteral("checkBoxFillMargins"));
        checkBoxFillMargins->setMinimumSize(QSize(100, 0));

        horizontalLayout_12->addWidget(checkBoxFillMargins);

        spinBoxFillMarginsLeft = new QSpinBox(groupBoxCropResize);
        spinBoxFillMarginsLeft->setObjectName(QStringLiteral("spinBoxFillMarginsLeft"));
        spinBoxFillMarginsLeft->setEnabled(false);
        spinBoxFillMarginsLeft->setMaximum(999999999);

        horizontalLayout_12->addWidget(spinBoxFillMarginsLeft);

        spinBoxFillMarginsTop = new QSpinBox(groupBoxCropResize);
        spinBoxFillMarginsTop->setObjectName(QStringLiteral("spinBoxFillMarginsTop"));
        spinBoxFillMarginsTop->setEnabled(false);
        spinBoxFillMarginsTop->setMaximum(999999999);

        horizontalLayout_12->addWidget(spinBoxFillMarginsTop);

        spinBoxFillMarginsRight = new QSpinBox(groupBoxCropResize);
        spinBoxFillMarginsRight->setObjectName(QStringLiteral("spinBoxFillMarginsRight"));
        spinBoxFillMarginsRight->setEnabled(false);
        spinBoxFillMarginsRight->setMaximum(999999999);

        horizontalLayout_12->addWidget(spinBoxFillMarginsRight);

        spinBoxFillMarginsButtom = new QSpinBox(groupBoxCropResize);
        spinBoxFillMarginsButtom->setObjectName(QStringLiteral("spinBoxFillMarginsButtom"));
        spinBoxFillMarginsButtom->setEnabled(false);
        spinBoxFillMarginsButtom->setMaximum(999999999);

        horizontalLayout_12->addWidget(spinBoxFillMarginsButtom);


        verticalLayout_12->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        checkBoxResize = new QCheckBox(groupBoxCropResize);
        checkBoxResize->setObjectName(QStringLiteral("checkBoxResize"));
        checkBoxResize->setMinimumSize(QSize(100, 0));

        horizontalLayout_13->addWidget(checkBoxResize);

        comboBoxResizeFilter = new QComboBox(groupBoxCropResize);
        comboBoxResizeFilter->setObjectName(QStringLiteral("comboBoxResizeFilter"));
        comboBoxResizeFilter->setEnabled(false);
        sizePolicy.setHeightForWidth(comboBoxResizeFilter->sizePolicy().hasHeightForWidth());
        comboBoxResizeFilter->setSizePolicy(sizePolicy);

        horizontalLayout_13->addWidget(comboBoxResizeFilter);

        spinBoxResizeW = new QSpinBox(groupBoxCropResize);
        spinBoxResizeW->setObjectName(QStringLiteral("spinBoxResizeW"));
        spinBoxResizeW->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinBoxResizeW->sizePolicy().hasHeightForWidth());
        spinBoxResizeW->setSizePolicy(sizePolicy2);
        spinBoxResizeW->setMinimum(0);
        spinBoxResizeW->setMaximum(999999999);
        spinBoxResizeW->setValue(1280);

        horizontalLayout_13->addWidget(spinBoxResizeW);

        spinBoxResizeH = new QSpinBox(groupBoxCropResize);
        spinBoxResizeH->setObjectName(QStringLiteral("spinBoxResizeH"));
        spinBoxResizeH->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinBoxResizeH->sizePolicy().hasHeightForWidth());
        spinBoxResizeH->setSizePolicy(sizePolicy2);
        spinBoxResizeH->setMinimum(0);
        spinBoxResizeH->setMaximum(999999999);
        spinBoxResizeH->setValue(720);

        horizontalLayout_13->addWidget(spinBoxResizeH);


        verticalLayout_12->addLayout(horizontalLayout_13);


        verticalLayout_20->addWidget(groupBoxCropResize);

        groupBoxFPS = new QGroupBox(tab_source);
        groupBoxFPS->setObjectName(QStringLiteral("groupBoxFPS"));
        verticalLayout_16 = new QVBoxLayout(groupBoxFPS);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        checkBoxFPS = new QCheckBox(groupBoxFPS);
        checkBoxFPS->setObjectName(QStringLiteral("checkBoxFPS"));

        horizontalLayout_7->addWidget(checkBoxFPS);

        comboBoxFPSFilter = new QComboBox(groupBoxFPS);
        comboBoxFPSFilter->addItem(QString());
        comboBoxFPSFilter->addItem(QString());
        comboBoxFPSFilter->addItem(QString());
        comboBoxFPSFilter->setObjectName(QStringLiteral("comboBoxFPSFilter"));
        comboBoxFPSFilter->setEnabled(false);
        sizePolicy2.setHeightForWidth(comboBoxFPSFilter->sizePolicy().hasHeightForWidth());
        comboBoxFPSFilter->setSizePolicy(sizePolicy2);

        horizontalLayout_7->addWidget(comboBoxFPSFilter);

        spinBoxFPSFilterFpsnum = new QSpinBox(groupBoxFPS);
        spinBoxFPSFilterFpsnum->setObjectName(QStringLiteral("spinBoxFPSFilterFpsnum"));
        spinBoxFPSFilterFpsnum->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinBoxFPSFilterFpsnum->sizePolicy().hasHeightForWidth());
        spinBoxFPSFilterFpsnum->setSizePolicy(sizePolicy2);
        spinBoxFPSFilterFpsnum->setMinimum(0);
        spinBoxFPSFilterFpsnum->setMaximum(999999999);

        horizontalLayout_7->addWidget(spinBoxFPSFilterFpsnum);

        labelFPSFilterFPS2 = new QLabel(groupBoxFPS);
        labelFPSFilterFPS2->setObjectName(QStringLiteral("labelFPSFilterFPS2"));
        labelFPSFilterFPS2->setEnabled(false);
        sizePolicy1.setHeightForWidth(labelFPSFilterFPS2->sizePolicy().hasHeightForWidth());
        labelFPSFilterFPS2->setSizePolicy(sizePolicy1);
        labelFPSFilterFPS2->setMinimumSize(QSize(0, 0));
        labelFPSFilterFPS2->setMaximumSize(QSize(16777215, 16777215));
        labelFPSFilterFPS2->setTextFormat(Qt::AutoText);
        labelFPSFilterFPS2->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(labelFPSFilterFPS2);

        spinBoxFPSFilterFpsden = new QSpinBox(groupBoxFPS);
        spinBoxFPSFilterFpsden->setObjectName(QStringLiteral("spinBoxFPSFilterFpsden"));
        spinBoxFPSFilterFpsden->setEnabled(false);
        sizePolicy2.setHeightForWidth(spinBoxFPSFilterFpsden->sizePolicy().hasHeightForWidth());
        spinBoxFPSFilterFpsden->setSizePolicy(sizePolicy2);
        spinBoxFPSFilterFpsden->setMinimum(0);
        spinBoxFPSFilterFpsden->setMaximum(999999999);
        spinBoxFPSFilterFpsden->setSingleStep(1);

        horizontalLayout_7->addWidget(spinBoxFPSFilterFpsden);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);


        verticalLayout_16->addLayout(horizontalLayout_7);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(3);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        editTimeCodeFile = new QLineEdit(groupBoxFPS);
        editTimeCodeFile->setObjectName(QStringLiteral("editTimeCodeFile"));
        editTimeCodeFile->setEnabled(false);
        editTimeCodeFile->setMinimumSize(QSize(0, 25));
        editTimeCodeFile->setStyleSheet(QStringLiteral(""));
        editTimeCodeFile->setReadOnly(true);

        horizontalLayout_18->addWidget(editTimeCodeFile);

        buttonBrowseTimeCodeFile = new QPushButton(groupBoxFPS);
        buttonBrowseTimeCodeFile->setObjectName(QStringLiteral("buttonBrowseTimeCodeFile"));
        buttonBrowseTimeCodeFile->setEnabled(false);
        buttonBrowseTimeCodeFile->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_18->addWidget(buttonBrowseTimeCodeFile);


        verticalLayout_16->addLayout(horizontalLayout_18);


        verticalLayout_20->addWidget(groupBoxFPS);

        tabWidget->addTab(tab_source, QString());
        tab_filters = new QWidget();
        tab_filters->setObjectName(QStringLiteral("tab_filters"));
        verticalLayout_28 = new QVBoxLayout(tab_filters);
        verticalLayout_28->setObjectName(QStringLiteral("verticalLayout_28"));
        verticalLayout_28->setContentsMargins(-1, 3, -1, -1);
        groupBoxDeinterlacingInverseTelecine = new QGroupBox(tab_filters);
        groupBoxDeinterlacingInverseTelecine->setObjectName(QStringLiteral("groupBoxDeinterlacingInverseTelecine"));
        verticalLayout_27 = new QVBoxLayout(groupBoxDeinterlacingInverseTelecine);
        verticalLayout_27->setObjectName(QStringLiteral("verticalLayout_27"));
        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setSpacing(3);
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        labelDeinterlacingSourceType = new QLabel(groupBoxDeinterlacingInverseTelecine);
        labelDeinterlacingSourceType->setObjectName(QStringLiteral("labelDeinterlacingSourceType"));

        verticalLayout_22->addWidget(labelDeinterlacingSourceType);

        comboBoxDeinterlacingSourceType = new QComboBox(groupBoxDeinterlacingInverseTelecine);
        comboBoxDeinterlacingSourceType->addItem(QString());
        comboBoxDeinterlacingSourceType->addItem(QString());
        comboBoxDeinterlacingSourceType->addItem(QString());
        comboBoxDeinterlacingSourceType->setObjectName(QStringLiteral("comboBoxDeinterlacingSourceType"));
        sizePolicy.setHeightForWidth(comboBoxDeinterlacingSourceType->sizePolicy().hasHeightForWidth());
        comboBoxDeinterlacingSourceType->setSizePolicy(sizePolicy);

        verticalLayout_22->addWidget(comboBoxDeinterlacingSourceType);


        horizontalLayout_29->addLayout(verticalLayout_22);

        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setSpacing(3);
        verticalLayout_23->setObjectName(QStringLiteral("verticalLayout_23"));
        labelDeinterlacingFieldOrder = new QLabel(groupBoxDeinterlacingInverseTelecine);
        labelDeinterlacingFieldOrder->setObjectName(QStringLiteral("labelDeinterlacingFieldOrder"));
        labelDeinterlacingFieldOrder->setEnabled(false);

        verticalLayout_23->addWidget(labelDeinterlacingFieldOrder);

        comboBoxDeinterlacingFieldOrder = new QComboBox(groupBoxDeinterlacingInverseTelecine);
        comboBoxDeinterlacingFieldOrder->addItem(QString());
        comboBoxDeinterlacingFieldOrder->addItem(QString());
        comboBoxDeinterlacingFieldOrder->setObjectName(QStringLiteral("comboBoxDeinterlacingFieldOrder"));
        comboBoxDeinterlacingFieldOrder->setEnabled(false);
        sizePolicy.setHeightForWidth(comboBoxDeinterlacingFieldOrder->sizePolicy().hasHeightForWidth());
        comboBoxDeinterlacingFieldOrder->setSizePolicy(sizePolicy);

        verticalLayout_23->addWidget(comboBoxDeinterlacingFieldOrder);


        horizontalLayout_29->addLayout(verticalLayout_23);

        verticalLayout_25 = new QVBoxLayout();
        verticalLayout_25->setSpacing(3);
        verticalLayout_25->setObjectName(QStringLiteral("verticalLayout_25"));
        labelDeinterlacingFrameRate = new QLabel(groupBoxDeinterlacingInverseTelecine);
        labelDeinterlacingFrameRate->setObjectName(QStringLiteral("labelDeinterlacingFrameRate"));
        labelDeinterlacingFrameRate->setEnabled(false);

        verticalLayout_25->addWidget(labelDeinterlacingFrameRate);

        comboBoxDeinterlacingFrameRate = new QComboBox(groupBoxDeinterlacingInverseTelecine);
        comboBoxDeinterlacingFrameRate->addItem(QString());
        comboBoxDeinterlacingFrameRate->addItem(QString());
        comboBoxDeinterlacingFrameRate->setObjectName(QStringLiteral("comboBoxDeinterlacingFrameRate"));
        comboBoxDeinterlacingFrameRate->setEnabled(false);
        sizePolicy.setHeightForWidth(comboBoxDeinterlacingFrameRate->sizePolicy().hasHeightForWidth());
        comboBoxDeinterlacingFrameRate->setSizePolicy(sizePolicy);

        verticalLayout_25->addWidget(comboBoxDeinterlacingFrameRate);


        horizontalLayout_29->addLayout(verticalLayout_25);


        verticalLayout_27->addLayout(horizontalLayout_29);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setSpacing(3);
        verticalLayout_24->setObjectName(QStringLiteral("verticalLayout_24"));
        labelDeinterlacingFilter = new QLabel(groupBoxDeinterlacingInverseTelecine);
        labelDeinterlacingFilter->setObjectName(QStringLiteral("labelDeinterlacingFilter"));
        labelDeinterlacingFilter->setEnabled(false);

        verticalLayout_24->addWidget(labelDeinterlacingFilter);

        comboBoxDeinterlacingFilter = new QComboBox(groupBoxDeinterlacingInverseTelecine);
        comboBoxDeinterlacingFilter->setObjectName(QStringLiteral("comboBoxDeinterlacingFilter"));
        comboBoxDeinterlacingFilter->setEnabled(false);
        sizePolicy.setHeightForWidth(comboBoxDeinterlacingFilter->sizePolicy().hasHeightForWidth());
        comboBoxDeinterlacingFilter->setSizePolicy(sizePolicy);

        verticalLayout_24->addWidget(comboBoxDeinterlacingFilter);


        horizontalLayout_30->addLayout(verticalLayout_24);

        verticalLayout_26 = new QVBoxLayout();
        verticalLayout_26->setSpacing(3);
        verticalLayout_26->setObjectName(QStringLiteral("verticalLayout_26"));
        labelDeinterlacingPreset = new QLabel(groupBoxDeinterlacingInverseTelecine);
        labelDeinterlacingPreset->setObjectName(QStringLiteral("labelDeinterlacingPreset"));
        labelDeinterlacingPreset->setEnabled(false);

        verticalLayout_26->addWidget(labelDeinterlacingPreset);

        comboBoxDeinterlacingPreset = new QComboBox(groupBoxDeinterlacingInverseTelecine);
        comboBoxDeinterlacingPreset->addItem(QString());
        comboBoxDeinterlacingPreset->addItem(QString());
        comboBoxDeinterlacingPreset->addItem(QString());
        comboBoxDeinterlacingPreset->addItem(QString());
        comboBoxDeinterlacingPreset->addItem(QString());
        comboBoxDeinterlacingPreset->addItem(QString());
        comboBoxDeinterlacingPreset->addItem(QString());
        comboBoxDeinterlacingPreset->addItem(QString());
        comboBoxDeinterlacingPreset->addItem(QString());
        comboBoxDeinterlacingPreset->addItem(QString());
        comboBoxDeinterlacingPreset->setObjectName(QStringLiteral("comboBoxDeinterlacingPreset"));
        comboBoxDeinterlacingPreset->setEnabled(false);
        sizePolicy.setHeightForWidth(comboBoxDeinterlacingPreset->sizePolicy().hasHeightForWidth());
        comboBoxDeinterlacingPreset->setSizePolicy(sizePolicy);

        verticalLayout_26->addWidget(comboBoxDeinterlacingPreset);


        horizontalLayout_30->addLayout(verticalLayout_26);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_30->addItem(horizontalSpacer_6);


        verticalLayout_27->addLayout(horizontalLayout_30);


        verticalLayout_28->addWidget(groupBoxDeinterlacingInverseTelecine);

        groupBoxLogo = new QGroupBox(tab_filters);
        groupBoxLogo->setObjectName(QStringLiteral("groupBoxLogo"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBoxLogo->sizePolicy().hasHeightForWidth());
        groupBoxLogo->setSizePolicy(sizePolicy5);
        groupBoxLogo->setCheckable(false);
        groupBoxLogo->setChecked(false);
        verticalLayout_15 = new QVBoxLayout(groupBoxLogo);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        checkBoxDeleteLogoDataInput = new QCheckBox(groupBoxLogo);
        checkBoxDeleteLogoDataInput->setObjectName(QStringLiteral("checkBoxDeleteLogoDataInput"));

        verticalLayout_11->addWidget(checkBoxDeleteLogoDataInput);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(3);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        editDeleteLogoDataInput = new QLineEdit(groupBoxLogo);
        editDeleteLogoDataInput->setObjectName(QStringLiteral("editDeleteLogoDataInput"));
        editDeleteLogoDataInput->setEnabled(false);
        editDeleteLogoDataInput->setMinimumSize(QSize(0, 25));
        editDeleteLogoDataInput->setStyleSheet(QStringLiteral(""));
        editDeleteLogoDataInput->setReadOnly(true);

        horizontalLayout_10->addWidget(editDeleteLogoDataInput);

        buttonBrowseDeleteLogoDataInput = new QPushButton(groupBoxLogo);
        buttonBrowseDeleteLogoDataInput->setObjectName(QStringLiteral("buttonBrowseDeleteLogoDataInput"));
        buttonBrowseDeleteLogoDataInput->setEnabled(false);
        buttonBrowseDeleteLogoDataInput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_10->addWidget(buttonBrowseDeleteLogoDataInput);


        verticalLayout_11->addLayout(horizontalLayout_10);


        verticalLayout_15->addLayout(verticalLayout_11);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        labelDelogoAlignment = new QLabel(groupBoxLogo);
        labelDelogoAlignment->setObjectName(QStringLiteral("labelDelogoAlignment"));
        labelDelogoAlignment->setEnabled(false);

        horizontalLayout_9->addWidget(labelDelogoAlignment);

        spinBoxDelogoAlignment = new QSpinBox(groupBoxLogo);
        spinBoxDelogoAlignment->setObjectName(QStringLiteral("spinBoxDelogoAlignment"));
        spinBoxDelogoAlignment->setEnabled(false);
        spinBoxDelogoAlignment->setMinimumSize(QSize(130, 0));
        spinBoxDelogoAlignment->setMaximum(9);

        horizontalLayout_9->addWidget(spinBoxDelogoAlignment);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);


        verticalLayout_15->addLayout(horizontalLayout_9);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        checkBoxAddLogoDataInput = new QCheckBox(groupBoxLogo);
        checkBoxAddLogoDataInput->setObjectName(QStringLiteral("checkBoxAddLogoDataInput"));

        verticalLayout_13->addWidget(checkBoxAddLogoDataInput);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(3);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        editAddLogoDataInput = new QLineEdit(groupBoxLogo);
        editAddLogoDataInput->setObjectName(QStringLiteral("editAddLogoDataInput"));
        editAddLogoDataInput->setEnabled(false);
        editAddLogoDataInput->setMinimumSize(QSize(0, 25));
        editAddLogoDataInput->setStyleSheet(QStringLiteral(""));
        editAddLogoDataInput->setReadOnly(true);

        horizontalLayout_14->addWidget(editAddLogoDataInput);

        buttonBrowseAddLogoDataInput = new QPushButton(groupBoxLogo);
        buttonBrowseAddLogoDataInput->setObjectName(QStringLiteral("buttonBrowseAddLogoDataInput"));
        buttonBrowseAddLogoDataInput->setEnabled(false);
        buttonBrowseAddLogoDataInput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_14->addWidget(buttonBrowseAddLogoDataInput);


        verticalLayout_13->addLayout(horizontalLayout_14);


        verticalLayout_15->addLayout(verticalLayout_13);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        labelAddLogoAlignment = new QLabel(groupBoxLogo);
        labelAddLogoAlignment->setObjectName(QStringLiteral("labelAddLogoAlignment"));
        labelAddLogoAlignment->setEnabled(false);

        horizontalLayout_15->addWidget(labelAddLogoAlignment);

        spinBoxAddLogoAlignment = new QSpinBox(groupBoxLogo);
        spinBoxAddLogoAlignment->setObjectName(QStringLiteral("spinBoxAddLogoAlignment"));
        spinBoxAddLogoAlignment->setEnabled(false);
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(spinBoxAddLogoAlignment->sizePolicy().hasHeightForWidth());
        spinBoxAddLogoAlignment->setSizePolicy(sizePolicy6);
        spinBoxAddLogoAlignment->setMinimumSize(QSize(130, 0));
        spinBoxAddLogoAlignment->setMaximum(9);
        spinBoxAddLogoAlignment->setValue(0);

        horizontalLayout_15->addWidget(spinBoxAddLogoAlignment);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_7);


        verticalLayout_15->addLayout(horizontalLayout_15);


        verticalLayout_28->addWidget(groupBoxLogo);

        groupBoxDenoise = new QGroupBox(tab_filters);
        groupBoxDenoise->setObjectName(QStringLiteral("groupBoxDenoise"));
        horizontalLayout_28 = new QHBoxLayout(groupBoxDenoise);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        checkBoxDenoise = new QCheckBox(groupBoxDenoise);
        checkBoxDenoise->setObjectName(QStringLiteral("checkBoxDenoise"));

        horizontalLayout_28->addWidget(checkBoxDenoise);

        comboBoxDenoise = new QComboBox(groupBoxDenoise);
        comboBoxDenoise->setObjectName(QStringLiteral("comboBoxDenoise"));
        comboBoxDenoise->setEnabled(false);
        sizePolicy.setHeightForWidth(comboBoxDenoise->sizePolicy().hasHeightForWidth());
        comboBoxDenoise->setSizePolicy(sizePolicy);
        comboBoxDenoise->setMinimumSize(QSize(0, 0));

        horizontalLayout_28->addWidget(comboBoxDenoise);

        horizontalSpacer_16 = new QSpacerItem(0, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_16);


        verticalLayout_28->addWidget(groupBoxDenoise);

        groupBoxSubtitle = new QGroupBox(tab_filters);
        groupBoxSubtitle->setObjectName(QStringLiteral("groupBoxSubtitle"));
        sizePolicy5.setHeightForWidth(groupBoxSubtitle->sizePolicy().hasHeightForWidth());
        groupBoxSubtitle->setSizePolicy(sizePolicy5);
        groupBoxSubtitle->setCheckable(false);
        groupBoxSubtitle->setChecked(false);
        verticalLayout_4 = new QVBoxLayout(groupBoxSubtitle);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBoxSubtitle = new QCheckBox(groupBoxSubtitle);
        checkBoxSubtitle->setObjectName(QStringLiteral("checkBoxSubtitle"));

        horizontalLayout_2->addWidget(checkBoxSubtitle);

        comboBoxSubtitle = new QComboBox(groupBoxSubtitle);
        comboBoxSubtitle->setObjectName(QStringLiteral("comboBoxSubtitle"));
        comboBoxSubtitle->setEnabled(false);
        sizePolicy.setHeightForWidth(comboBoxSubtitle->sizePolicy().hasHeightForWidth());
        comboBoxSubtitle->setSizePolicy(sizePolicy);
        comboBoxSubtitle->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(comboBoxSubtitle);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        editSubtitle = new QLineEdit(groupBoxSubtitle);
        editSubtitle->setObjectName(QStringLiteral("editSubtitle"));
        editSubtitle->setEnabled(false);
        editSubtitle->setMinimumSize(QSize(0, 25));
        editSubtitle->setStyleSheet(QStringLiteral(""));
        editSubtitle->setReadOnly(true);

        horizontalLayout_3->addWidget(editSubtitle);

        buttonBrowseSubtitle = new QPushButton(groupBoxSubtitle);
        buttonBrowseSubtitle->setObjectName(QStringLiteral("buttonBrowseSubtitle"));
        buttonBrowseSubtitle->setEnabled(false);
        buttonBrowseSubtitle->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_3->addWidget(buttonBrowseSubtitle);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_28->addWidget(groupBoxSubtitle);

        tabWidget->addTab(tab_filters, QString());
        tab_script = new QWidget();
        tab_script->setObjectName(QStringLiteral("tab_script"));
        verticalLayout_2 = new QVBoxLayout(tab_script);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        scriptEditor = new ScriptEditor(tab_script);
        scriptEditor->setObjectName(QStringLiteral("scriptEditor"));
        scriptEditor->setAcceptDrops(false);

        verticalLayout_2->addWidget(scriptEditor);

        tabWidget->addTab(tab_script, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, -1, 5, 5);
        checkBoxNotAddJobOnSaved = new QCheckBox(ScriptCreator);
        checkBoxNotAddJobOnSaved->setObjectName(QStringLiteral("checkBoxNotAddJobOnSaved"));
        checkBoxNotAddJobOnSaved->setChecked(false);

        horizontalLayout->addWidget(checkBoxNotAddJobOnSaved);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonPreview = new QPushButton(ScriptCreator);
        buttonPreview->setObjectName(QStringLiteral("buttonPreview"));
        buttonPreview->setEnabled(true);
        buttonPreview->setMinimumSize(QSize(104, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/film.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonPreview->setIcon(icon);
        buttonPreview->setCheckable(false);

        horizontalLayout->addWidget(buttonPreview);

        buttonSave = new QPushButton(ScriptCreator);
        buttonSave->setObjectName(QStringLiteral("buttonSave"));
        buttonSave->setEnabled(true);
        buttonSave->setMinimumSize(QSize(104, 0));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSave->setIcon(icon1);

        horizontalLayout->addWidget(buttonSave);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ScriptCreator);

        tabWidget->setCurrentIndex(0);
        stackedWidgetSourceFilter->setCurrentIndex(0);
        comboBoxDeinterlacingPreset->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(ScriptCreator);
    } // setupUi

    void retranslateUi(QWidget *ScriptCreator)
    {
        ScriptCreator->setWindowTitle(QApplication::translate("ScriptCreator", "Script Creator", nullptr));
        groupBoxSource->setTitle(QApplication::translate("ScriptCreator", "Input/Output", nullptr));
#ifndef QT_NO_TOOLTIP
        labelSource->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelSource->setText(QApplication::translate("ScriptCreator", "Source Media/Project File:", nullptr));
        labelSourcePreview->setText(QApplication::translate("ScriptCreator", "Preview Source", nullptr));
#ifndef QT_NO_TOOLTIP
        editSource->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editSource->setPlaceholderText(QApplication::translate("ScriptCreator", "Enable Drag and drop Event ...", nullptr));
        buttonBrowseSource->setText(QApplication::translate("ScriptCreator", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        labelOutput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelOutput->setText(QApplication::translate("ScriptCreator", "Output VapourSynth Script File:", nullptr));
#ifndef QT_NO_TOOLTIP
        editOutput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editOutput->setPlaceholderText(QApplication::translate("ScriptCreator", "Enable Drag and drop Event ...", nullptr));
        buttonBrowseOutput->setText(QApplication::translate("ScriptCreator", "...", nullptr));
        groupBoxSourceFilter->setTitle(QApplication::translate("ScriptCreator", "Filter", nullptr));
#ifndef QT_NO_TOOLTIP
        labelSourceFilter->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelSourceFilter->setText(QApplication::translate("ScriptCreator", "Filter:", nullptr));
        comboBoxSourceFilter->setItemText(0, QApplication::translate("ScriptCreator", "LWLibavSource", nullptr));
        comboBoxSourceFilter->setItemText(1, QApplication::translate("ScriptCreator", "FFmpegSouce", nullptr));
        comboBoxSourceFilter->setItemText(2, QApplication::translate("ScriptCreator", "DGSourceNV", nullptr));
        comboBoxSourceFilter->setItemText(3, QApplication::translate("ScriptCreator", "DGSource", nullptr));
        comboBoxSourceFilter->setItemText(4, QApplication::translate("ScriptCreator", "DirectShowSource", nullptr));

#ifndef QT_NO_TOOLTIP
        labelSourceFilterLWLFormat->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelSourceFilterLWLFormat->setText(QApplication::translate("ScriptCreator", "Format:", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(0, QApplication::translate("ScriptCreator", "<None>", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(1, QApplication::translate("ScriptCreator", "YUV420P8", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(2, QApplication::translate("ScriptCreator", "YUV422P8", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(3, QApplication::translate("ScriptCreator", "YUV444P8", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(4, QApplication::translate("ScriptCreator", "YUV410P8", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(5, QApplication::translate("ScriptCreator", "YUV411P8", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(6, QApplication::translate("ScriptCreator", "YUV440P8", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(7, QApplication::translate("ScriptCreator", "YUV420P9", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(8, QApplication::translate("ScriptCreator", "YUV422P9", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(9, QApplication::translate("ScriptCreator", "YUV444P9", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(10, QApplication::translate("ScriptCreator", "YUV420P10", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(11, QApplication::translate("ScriptCreator", "YUV422P10", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(12, QApplication::translate("ScriptCreator", "YUV444P10", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(13, QApplication::translate("ScriptCreator", "YUV420P16", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(14, QApplication::translate("ScriptCreator", "YUV422P16", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(15, QApplication::translate("ScriptCreator", "YUV444P16", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(16, QApplication::translate("ScriptCreator", "RGB24", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(17, QApplication::translate("ScriptCreator", "RGB27", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(18, QApplication::translate("ScriptCreator", "RGB30", nullptr));
        comboBoxSourceFilterLWLFormat->setItemText(19, QApplication::translate("ScriptCreator", "RGB48", nullptr));

#ifndef QT_NO_TOOLTIP
        labelSourceFilterLWLDecoder->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelSourceFilterLWLDecoder->setText(QApplication::translate("ScriptCreator", "Decoder:", nullptr));
        comboBoxSourceFilterLWLDecoder->setItemText(0, QApplication::translate("ScriptCreator", "<None>", nullptr));
        comboBoxSourceFilterLWLDecoder->setItemText(1, QApplication::translate("ScriptCreator", "h264_qsv", nullptr));
        comboBoxSourceFilterLWLDecoder->setItemText(2, QApplication::translate("ScriptCreator", "h264_cuvid", nullptr));
        comboBoxSourceFilterLWLDecoder->setItemText(3, QApplication::translate("ScriptCreator", "hevc_qsv", nullptr));
        comboBoxSourceFilterLWLDecoder->setItemText(4, QApplication::translate("ScriptCreator", "hevc_cuvid", nullptr));
        comboBoxSourceFilterLWLDecoder->setItemText(5, QApplication::translate("ScriptCreator", "mpeg2_qsv", nullptr));
        comboBoxSourceFilterLWLDecoder->setItemText(6, QApplication::translate("ScriptCreator", "mpeg2_cuvid", nullptr));
        comboBoxSourceFilterLWLDecoder->setItemText(7, QApplication::translate("ScriptCreator", "mpeg4_cuvid", nullptr));
        comboBoxSourceFilterLWLDecoder->setItemText(8, QApplication::translate("ScriptCreator", "vp9_cuvid", nullptr));

        checkBoxSourceFilterLWLFPS->setText(QApplication::translate("ScriptCreator", "FPS:", nullptr));
        spinBoxSourceFilterLWLFpsnum->setPrefix(QApplication::translate("ScriptCreator", "fpsnum=", nullptr));
#ifndef QT_NO_TOOLTIP
        labelSourceFilterLWLFPS2->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelSourceFilterLWLFPS2->setText(QApplication::translate("ScriptCreator", "/", nullptr));
        spinBoxSourceFilterLWLFpsden->setPrefix(QApplication::translate("ScriptCreator", "fpsden=", nullptr));
        checkBoxSourceFilterLSMASH->setText(QApplication::translate("ScriptCreator", "L-SMASH", nullptr));
        checkBoxSourceFilterFFmpegFPS->setText(QApplication::translate("ScriptCreator", "FPS:", nullptr));
        spinBoxSourceFilterFFmpegFpsnum->setPrefix(QApplication::translate("ScriptCreator", "fpsnum=", nullptr));
#ifndef QT_NO_TOOLTIP
        labelSourceFilterFFmpegFPS2->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelSourceFilterFFmpegFPS2->setText(QApplication::translate("ScriptCreator", "/", nullptr));
        spinBoxSourceFilterFFmpegFpsden->setPrefix(QApplication::translate("ScriptCreator", "fpsden=", nullptr));
        dotGridFFMS2->setText(QString());
        checkBoxSourceFilterDGNVDeinterlacer->setText(QApplication::translate("ScriptCreator", "Nvcuvid Deinterlacer", nullptr));
        comboBoxSourceFilterDGNVDeinterlacer->setItemText(0, QApplication::translate("ScriptCreator", "No Deinterlacing", nullptr));
        comboBoxSourceFilterDGNVDeinterlacer->setItemText(1, QApplication::translate("ScriptCreator", "Single Rate Deinterlacing", nullptr));
        comboBoxSourceFilterDGNVDeinterlacer->setItemText(2, QApplication::translate("ScriptCreator", "Double Rate Deinterlacing", nullptr));

        checkBoxSourceFilterDGNVResizer->setText(QApplication::translate("ScriptCreator", "Nvcuvid Resizer", nullptr));
        spinBoxSourceFilterDGNVResizeW->setPrefix(QApplication::translate("ScriptCreator", "w=", nullptr));
        spinBoxSourceFilterDGNVResizeH->setPrefix(QApplication::translate("ScriptCreator", "h=", nullptr));
        checkBoxSourceFilterDGNVDeinterlacer_2->setText(QApplication::translate("ScriptCreator", "Field Operation", nullptr));
        comboBoxSourceFilterDGNVFieldOperation->setItemText(0, QApplication::translate("ScriptCreator", "Honor Pulldown Flags", nullptr));
        comboBoxSourceFilterDGNVFieldOperation->setItemText(1, QApplication::translate("ScriptCreator", "Force Film", nullptr));
        comboBoxSourceFilterDGNVFieldOperation->setItemText(2, QApplication::translate("ScriptCreator", "Ignore Pulldown Flags", nullptr));

        labelSourceFilterDGFieldOperation->setText(QApplication::translate("ScriptCreator", "Field Operation:", nullptr));
        comboBoxSourceFilterDGFieldOperation->setItemText(0, QApplication::translate("ScriptCreator", "Honor Pulldown Flags", nullptr));
        comboBoxSourceFilterDGFieldOperation->setItemText(1, QApplication::translate("ScriptCreator", "Force Film", nullptr));
        comboBoxSourceFilterDGFieldOperation->setItemText(2, QApplication::translate("ScriptCreator", "Ignore Pulldown Flags", nullptr));

        checkBoxD2VWitch->setText(QApplication::translate("ScriptCreator", "D2VWitch", nullptr));
        labelSourceFilterDGFieldOperation_2->setText(QApplication::translate("ScriptCreator", "(Effect before indexed.)", nullptr));
        dotGridDGNV->setText(QString());
        checkBoxSourceFilterDSSConvertFPS->setText(QApplication::translate("ScriptCreator", "ConvertFPS", nullptr));
        checkBoxSourceFilterDSSFPS->setText(QApplication::translate("ScriptCreator", "FPS:", nullptr));
        dotGridDSS->setText(QString());
        groupBoxCropResize->setTitle(QApplication::translate("ScriptCreator", "Crop/Resize", nullptr));
        checkBoxCrop->setText(QApplication::translate("ScriptCreator", "Crop", nullptr));
        spinBoxCropLeft->setPrefix(QApplication::translate("ScriptCreator", "l=", nullptr));
        spinBoxCropTop->setPrefix(QApplication::translate("ScriptCreator", "t=", nullptr));
        spinBoxCropRight->setPrefix(QApplication::translate("ScriptCreator", "r=", nullptr));
        spinBoxCropButtom->setPrefix(QApplication::translate("ScriptCreator", "b=", nullptr));
        checkBoxFillMargins->setText(QApplication::translate("ScriptCreator", "FillMargins", nullptr));
        spinBoxFillMarginsLeft->setPrefix(QApplication::translate("ScriptCreator", "l=", nullptr));
        spinBoxFillMarginsTop->setPrefix(QApplication::translate("ScriptCreator", "t=", nullptr));
        spinBoxFillMarginsRight->setPrefix(QApplication::translate("ScriptCreator", "r=", nullptr));
        spinBoxFillMarginsButtom->setPrefix(QApplication::translate("ScriptCreator", "b=", nullptr));
        checkBoxResize->setText(QApplication::translate("ScriptCreator", "Resize", nullptr));
        spinBoxResizeW->setPrefix(QApplication::translate("ScriptCreator", "w=", nullptr));
        spinBoxResizeH->setPrefix(QApplication::translate("ScriptCreator", "h=", nullptr));
        groupBoxFPS->setTitle(QApplication::translate("ScriptCreator", "Frames Per Second", nullptr));
        checkBoxFPS->setText(QApplication::translate("ScriptCreator", "FPS:", nullptr));
        comboBoxFPSFilter->setItemText(0, QApplication::translate("ScriptCreator", "ChangeFPS", nullptr));
        comboBoxFPSFilter->setItemText(1, QApplication::translate("ScriptCreator", "AssumeFPS", nullptr));
        comboBoxFPSFilter->setItemText(2, QApplication::translate("ScriptCreator", "VFRtoCFR", nullptr));

        spinBoxFPSFilterFpsnum->setPrefix(QApplication::translate("ScriptCreator", "fpsnum=", nullptr));
#ifndef QT_NO_TOOLTIP
        labelFPSFilterFPS2->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelFPSFilterFPS2->setText(QApplication::translate("ScriptCreator", "/", nullptr));
        spinBoxFPSFilterFpsden->setPrefix(QApplication::translate("ScriptCreator", "fpsden=", nullptr));
#ifndef QT_NO_TOOLTIP
        editTimeCodeFile->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editTimeCodeFile->setPlaceholderText(QApplication::translate("ScriptCreator", "Enable Drag and drop Event ...", nullptr));
        buttonBrowseTimeCodeFile->setText(QApplication::translate("ScriptCreator", "...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_source), QApplication::translate("ScriptCreator", "Source", nullptr));
        groupBoxDeinterlacingInverseTelecine->setTitle(QApplication::translate("ScriptCreator", "Deinterlacing/Inverse telecine", nullptr));
        labelDeinterlacingSourceType->setText(QApplication::translate("ScriptCreator", "Source Type:", nullptr));
        comboBoxDeinterlacingSourceType->setItemText(0, QApplication::translate("ScriptCreator", "Progressive", nullptr));
        comboBoxDeinterlacingSourceType->setItemText(1, QApplication::translate("ScriptCreator", "Interlaced", nullptr));
        comboBoxDeinterlacingSourceType->setItemText(2, QApplication::translate("ScriptCreator", "Telecine", nullptr));

        labelDeinterlacingFieldOrder->setText(QApplication::translate("ScriptCreator", "Field Order:", nullptr));
        comboBoxDeinterlacingFieldOrder->setItemText(0, QApplication::translate("ScriptCreator", "Top Field First", nullptr));
        comboBoxDeinterlacingFieldOrder->setItemText(1, QApplication::translate("ScriptCreator", "Buttom Field First", nullptr));

        labelDeinterlacingFrameRate->setText(QApplication::translate("ScriptCreator", "Frame Rate:", nullptr));
        comboBoxDeinterlacingFrameRate->setItemText(0, QApplication::translate("ScriptCreator", "Single Rate", nullptr));
        comboBoxDeinterlacingFrameRate->setItemText(1, QApplication::translate("ScriptCreator", "Double Rate", nullptr));

        labelDeinterlacingFilter->setText(QApplication::translate("ScriptCreator", "Filter:", nullptr));
        labelDeinterlacingPreset->setText(QApplication::translate("ScriptCreator", "Preset:", nullptr));
        comboBoxDeinterlacingPreset->setItemText(0, QApplication::translate("ScriptCreator", "Placebo", nullptr));
        comboBoxDeinterlacingPreset->setItemText(1, QApplication::translate("ScriptCreator", "Very Slow", nullptr));
        comboBoxDeinterlacingPreset->setItemText(2, QApplication::translate("ScriptCreator", "Slower", nullptr));
        comboBoxDeinterlacingPreset->setItemText(3, QApplication::translate("ScriptCreator", "Slow", nullptr));
        comboBoxDeinterlacingPreset->setItemText(4, QApplication::translate("ScriptCreator", "Medium", nullptr));
        comboBoxDeinterlacingPreset->setItemText(5, QApplication::translate("ScriptCreator", "Fast", nullptr));
        comboBoxDeinterlacingPreset->setItemText(6, QApplication::translate("ScriptCreator", "Faster", nullptr));
        comboBoxDeinterlacingPreset->setItemText(7, QApplication::translate("ScriptCreator", "Very Fast", nullptr));
        comboBoxDeinterlacingPreset->setItemText(8, QApplication::translate("ScriptCreator", "Super Fast", nullptr));
        comboBoxDeinterlacingPreset->setItemText(9, QApplication::translate("ScriptCreator", "Ultra Fast", nullptr));

        comboBoxDeinterlacingPreset->setCurrentText(QApplication::translate("ScriptCreator", "Slow", nullptr));
        groupBoxLogo->setTitle(QApplication::translate("ScriptCreator", "Delogo/Add Logo", nullptr));
        checkBoxDeleteLogoDataInput->setText(QApplication::translate("ScriptCreator", "Delete logo Data File:", nullptr));
#ifndef QT_NO_TOOLTIP
        editDeleteLogoDataInput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editDeleteLogoDataInput->setPlaceholderText(QApplication::translate("ScriptCreator", "Enable Drag and drop Event ...", nullptr));
        buttonBrowseDeleteLogoDataInput->setText(QApplication::translate("ScriptCreator", "...", nullptr));
        labelDelogoAlignment->setText(QApplication::translate("ScriptCreator", "Alignment:", nullptr));
        spinBoxDelogoAlignment->setPrefix(QApplication::translate("ScriptCreator", "an=", nullptr));
        checkBoxAddLogoDataInput->setText(QApplication::translate("ScriptCreator", "Add logo Image/Data File:", nullptr));
#ifndef QT_NO_TOOLTIP
        editAddLogoDataInput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editAddLogoDataInput->setPlaceholderText(QApplication::translate("ScriptCreator", "Enable Drag and drop Event ...", nullptr));
        buttonBrowseAddLogoDataInput->setText(QApplication::translate("ScriptCreator", "...", nullptr));
        labelAddLogoAlignment->setText(QApplication::translate("ScriptCreator", "Alignment:", nullptr));
        spinBoxAddLogoAlignment->setPrefix(QApplication::translate("ScriptCreator", "an=", nullptr));
        groupBoxDenoise->setTitle(QApplication::translate("ScriptCreator", "Denoise", nullptr));
        checkBoxDenoise->setText(QApplication::translate("ScriptCreator", "Filter:", nullptr));
        groupBoxSubtitle->setTitle(QApplication::translate("ScriptCreator", "Subtitle", nullptr));
        checkBoxSubtitle->setText(QApplication::translate("ScriptCreator", "Filter:", nullptr));
#ifndef QT_NO_TOOLTIP
        editSubtitle->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editSubtitle->setPlaceholderText(QApplication::translate("ScriptCreator", "Enable Drag and drop Event ...", nullptr));
        buttonBrowseSubtitle->setText(QApplication::translate("ScriptCreator", "...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_filters), QApplication::translate("ScriptCreator", "Filters", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_script), QApplication::translate("ScriptCreator", "Script", nullptr));
        checkBoxNotAddJobOnSaved->setText(QApplication::translate("ScriptCreator", "Not add job on saved", nullptr));
        buttonPreview->setText(QApplication::translate("ScriptCreator", "Preview", nullptr));
        buttonSave->setText(QApplication::translate("ScriptCreator", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScriptCreator: public Ui_ScriptCreator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCRIPT_CREATOR_H
