/********************************************************************************
** Form generated from reading UI file 'mediainfo_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIAINFO_DIALOG_H
#define UI_MEDIAINFO_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MediaInfoDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *editMediaInfo;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBoxMediaInfoFull;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *buttonMediaInfoPreview;
    QPushButton *buttonMediaInfoCopy;
    QPushButton *buttonMediaInfoSave;

    void setupUi(QWidget *MediaInfoDialog)
    {
        if (MediaInfoDialog->objectName().isEmpty())
            MediaInfoDialog->setObjectName(QStringLiteral("MediaInfoDialog"));
        MediaInfoDialog->resize(503, 520);
        MediaInfoDialog->setAcceptDrops(true);
        verticalLayout = new QVBoxLayout(MediaInfoDialog);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        editMediaInfo = new QTextEdit(MediaInfoDialog);
        editMediaInfo->setObjectName(QStringLiteral("editMediaInfo"));
        QFont font;
        font.setFamily(QStringLiteral("Source Code Pro"));
        font.setPointSize(9);
        editMediaInfo->setFont(font);
        editMediaInfo->setAcceptDrops(false);
        editMediaInfo->setReadOnly(true);

        verticalLayout->addWidget(editMediaInfo);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(5, -1, -1, -1);
        checkBoxMediaInfoFull = new QCheckBox(MediaInfoDialog);
        checkBoxMediaInfoFull->setObjectName(QStringLiteral("checkBoxMediaInfoFull"));

        horizontalLayout_4->addWidget(checkBoxMediaInfoFull);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        buttonMediaInfoPreview = new QPushButton(MediaInfoDialog);
        buttonMediaInfoPreview->setObjectName(QStringLiteral("buttonMediaInfoPreview"));
        buttonMediaInfoPreview->setMinimumSize(QSize(90, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/film.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonMediaInfoPreview->setIcon(icon);

        horizontalLayout_4->addWidget(buttonMediaInfoPreview);

        buttonMediaInfoCopy = new QPushButton(MediaInfoDialog);
        buttonMediaInfoCopy->setObjectName(QStringLiteral("buttonMediaInfoCopy"));
        buttonMediaInfoCopy->setMinimumSize(QSize(90, 0));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/page_paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonMediaInfoCopy->setIcon(icon1);

        horizontalLayout_4->addWidget(buttonMediaInfoCopy);

        buttonMediaInfoSave = new QPushButton(MediaInfoDialog);
        buttonMediaInfoSave->setObjectName(QStringLiteral("buttonMediaInfoSave"));
        buttonMediaInfoSave->setMinimumSize(QSize(90, 0));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/buttons/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonMediaInfoSave->setIcon(icon2);

        horizontalLayout_4->addWidget(buttonMediaInfoSave);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(MediaInfoDialog);

        QMetaObject::connectSlotsByName(MediaInfoDialog);
    } // setupUi

    void retranslateUi(QWidget *MediaInfoDialog)
    {
        MediaInfoDialog->setWindowTitle(QApplication::translate("MediaInfoDialog", "MediaInfo", nullptr));
        editMediaInfo->setHtml(QApplication::translate("MediaInfoDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Source Code Pro'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'\357\274\255\357\274\263 \343\202\264\343\202\267\343\203\203\343\202\257';\"><br /></p></body></html>", nullptr));
        editMediaInfo->setPlaceholderText(QApplication::translate("MediaInfoDialog", "Please drag and drop a media file here ...", nullptr));
        checkBoxMediaInfoFull->setText(QApplication::translate("MediaInfoDialog", "Full Info", nullptr));
        buttonMediaInfoPreview->setText(QApplication::translate("MediaInfoDialog", "Preview", nullptr));
        buttonMediaInfoCopy->setText(QApplication::translate("MediaInfoDialog", "Copy", nullptr));
        buttonMediaInfoSave->setText(QApplication::translate("MediaInfoDialog", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MediaInfoDialog: public Ui_MediaInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIAINFO_DIALOG_H
