/********************************************************************************
** Form generated from reading UI file 'demuxer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMUXER_H
#define UI_DEMUXER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Demuxer
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxDemuxer;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_13;
    QLineEdit *editDemuxerVideoInput;
    QPushButton *buttonDemuxerVideoInput;
    QHBoxLayout *horizontalLayout_11;
    QLineEdit *editDemuxerOutput;
    QPushButton *buttonDemuxerOutput;
    QListWidget *listWidgetTrack;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelDemuxerFormat;
    QComboBox *comboBoxDemuxerFormat;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelDemuxerParam;
    QComboBox *comboBoxDemuxerParam;
    QPushButton *buttonDemuxerStart;

    void setupUi(QWidget *Demuxer)
    {
        if (Demuxer->objectName().isEmpty())
            Demuxer->setObjectName(QStringLiteral("Demuxer"));
        Demuxer->resize(672, 457);
        verticalLayout = new QVBoxLayout(Demuxer);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBoxDemuxer = new QGroupBox(Demuxer);
        groupBoxDemuxer->setObjectName(QStringLiteral("groupBoxDemuxer"));
        verticalLayout_8 = new QVBoxLayout(groupBoxDemuxer);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        editDemuxerVideoInput = new QLineEdit(groupBoxDemuxer);
        editDemuxerVideoInput->setObjectName(QStringLiteral("editDemuxerVideoInput"));
        editDemuxerVideoInput->setMinimumSize(QSize(0, 25));
        editDemuxerVideoInput->setStyleSheet(QStringLiteral("background-color: rgb(243, 243, 243);"));
        editDemuxerVideoInput->setReadOnly(true);

        horizontalLayout_13->addWidget(editDemuxerVideoInput);

        buttonDemuxerVideoInput = new QPushButton(groupBoxDemuxer);
        buttonDemuxerVideoInput->setObjectName(QStringLiteral("buttonDemuxerVideoInput"));
        buttonDemuxerVideoInput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_13->addWidget(buttonDemuxerVideoInput);


        verticalLayout_8->addLayout(horizontalLayout_13);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        editDemuxerOutput = new QLineEdit(groupBoxDemuxer);
        editDemuxerOutput->setObjectName(QStringLiteral("editDemuxerOutput"));
        editDemuxerOutput->setMinimumSize(QSize(0, 25));
        editDemuxerOutput->setReadOnly(false);

        horizontalLayout_11->addWidget(editDemuxerOutput);

        buttonDemuxerOutput = new QPushButton(groupBoxDemuxer);
        buttonDemuxerOutput->setObjectName(QStringLiteral("buttonDemuxerOutput"));
        buttonDemuxerOutput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_11->addWidget(buttonDemuxerOutput);


        verticalLayout_8->addLayout(horizontalLayout_11);

        listWidgetTrack = new QListWidget(groupBoxDemuxer);
        listWidgetTrack->setObjectName(QStringLiteral("listWidgetTrack"));
        listWidgetTrack->setMinimumSize(QSize(0, 250));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        listWidgetTrack->setFont(font);
        listWidgetTrack->setMovement(QListView::Static);
        listWidgetTrack->setResizeMode(QListView::Adjust);

        verticalLayout_8->addWidget(listWidgetTrack);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        labelDemuxerFormat = new QLabel(groupBoxDemuxer);
        labelDemuxerFormat->setObjectName(QStringLiteral("labelDemuxerFormat"));

        horizontalLayout_8->addWidget(labelDemuxerFormat);

        comboBoxDemuxerFormat = new QComboBox(groupBoxDemuxer);
        comboBoxDemuxerFormat->addItem(QString());
        comboBoxDemuxerFormat->addItem(QString());
        comboBoxDemuxerFormat->addItem(QString());
        comboBoxDemuxerFormat->addItem(QString());
        comboBoxDemuxerFormat->addItem(QString());
        comboBoxDemuxerFormat->setObjectName(QStringLiteral("comboBoxDemuxerFormat"));
        comboBoxDemuxerFormat->setMinimumSize(QSize(120, 25));

        horizontalLayout_8->addWidget(comboBoxDemuxerFormat);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);

        labelDemuxerParam = new QLabel(groupBoxDemuxer);
        labelDemuxerParam->setObjectName(QStringLiteral("labelDemuxerParam"));

        horizontalLayout_8->addWidget(labelDemuxerParam);

        comboBoxDemuxerParam = new QComboBox(groupBoxDemuxer);
        comboBoxDemuxerParam->setObjectName(QStringLiteral("comboBoxDemuxerParam"));
        comboBoxDemuxerParam->setMinimumSize(QSize(140, 25));

        horizontalLayout_8->addWidget(comboBoxDemuxerParam);

        buttonDemuxerStart = new QPushButton(groupBoxDemuxer);
        buttonDemuxerStart->setObjectName(QStringLiteral("buttonDemuxerStart"));
        buttonDemuxerStart->setEnabled(true);
        buttonDemuxerStart->setMinimumSize(QSize(104, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDemuxerStart->setIcon(icon);

        horizontalLayout_8->addWidget(buttonDemuxerStart);


        verticalLayout_8->addLayout(horizontalLayout_8);


        verticalLayout->addWidget(groupBoxDemuxer);


        retranslateUi(Demuxer);

        QMetaObject::connectSlotsByName(Demuxer);
    } // setupUi

    void retranslateUi(QWidget *Demuxer)
    {
        Demuxer->setWindowTitle(QApplication::translate("Demuxer", "Form", nullptr));
        groupBoxDemuxer->setTitle(QApplication::translate("Demuxer", "Demuxer", nullptr));
#ifndef QT_NO_TOOLTIP
        editDemuxerVideoInput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editDemuxerVideoInput->setPlaceholderText(QApplication::translate("Demuxer", "Video File Input Path", nullptr));
        buttonDemuxerVideoInput->setText(QApplication::translate("Demuxer", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        editDemuxerOutput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        editDemuxerOutput->setPlaceholderText(QApplication::translate("Demuxer", "Demuxed File Output Path", nullptr));
        buttonDemuxerOutput->setText(QApplication::translate("Demuxer", "...", nullptr));
        labelDemuxerFormat->setText(QApplication::translate("Demuxer", "Format:", nullptr));
        comboBoxDemuxerFormat->setItemText(0, QApplication::translate("Demuxer", "ffmpeg", nullptr));
        comboBoxDemuxerFormat->setItemText(1, QApplication::translate("Demuxer", "eac3to", nullptr));
        comboBoxDemuxerFormat->setItemText(2, QApplication::translate("Demuxer", "mkvextract", nullptr));
        comboBoxDemuxerFormat->setItemText(3, QApplication::translate("Demuxer", "tsdemux", nullptr));
        comboBoxDemuxerFormat->setItemText(4, QApplication::translate("Demuxer", "caption2ass", nullptr));

        labelDemuxerParam->setText(QApplication::translate("Demuxer", "Parameter:", nullptr));
        buttonDemuxerStart->setText(QApplication::translate("Demuxer", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Demuxer: public Ui_Demuxer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMUXER_H
