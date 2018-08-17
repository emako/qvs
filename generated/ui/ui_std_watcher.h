/********************************************************************************
** Form generated from reading UI file 'std_watcher.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STD_WATCHER_H
#define UI_STD_WATCHER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StdWatcher
{
public:
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBoxExitCompleted;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnPause;
    QPushButton *btnClose;

    void setupUi(QWidget *StdWatcher)
    {
        if (StdWatcher->objectName().isEmpty())
            StdWatcher->setObjectName(QStringLiteral("StdWatcher"));
        StdWatcher->resize(631, 551);
        verticalLayout = new QVBoxLayout(StdWatcher);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        plainTextEdit = new QPlainTextEdit(StdWatcher);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        plainTextEdit->setFont(font);

        verticalLayout->addWidget(plainTextEdit);

        frame = new QFrame(StdWatcher);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(frame);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBoxExitCompleted = new QCheckBox(StdWatcher);
        checkBoxExitCompleted->setObjectName(QStringLiteral("checkBoxExitCompleted"));
        checkBoxExitCompleted->setChecked(true);

        horizontalLayout_2->addWidget(checkBoxExitCompleted);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnPause = new QPushButton(StdWatcher);
        btnPause->setObjectName(QStringLiteral("btnPause"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/pause_green.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPause->setIcon(icon);
        btnPause->setCheckable(true);

        horizontalLayout_2->addWidget(btnPause);

        btnClose = new QPushButton(StdWatcher);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/cross_grey.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon1);

        horizontalLayout_2->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(StdWatcher);

        QMetaObject::connectSlotsByName(StdWatcher);
    } // setupUi

    void retranslateUi(QWidget *StdWatcher)
    {
        StdWatcher->setWindowTitle(QApplication::translate("StdWatcher", "StdWatcher", nullptr));
        checkBoxExitCompleted->setText(QApplication::translate("StdWatcher", "Close on completed", nullptr));
        btnPause->setText(QApplication::translate("StdWatcher", "Pause", nullptr));
        btnClose->setText(QApplication::translate("StdWatcher", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StdWatcher: public Ui_StdWatcher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STD_WATCHER_H
