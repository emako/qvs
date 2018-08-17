/********************************************************************************
** Form generated from reading UI file 'job_view_cmd.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOB_VIEW_CMD_H
#define UI_JOB_VIEW_CMD_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JobViewCmd
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelLogo;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxShowDetail;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonSave;
    QPushButton *buttonCopy;
    QPushButton *buttonClose;

    void setupUi(QWidget *JobViewCmd)
    {
        if (JobViewCmd->objectName().isEmpty())
            JobViewCmd->setObjectName(QStringLiteral("JobViewCmd"));
        JobViewCmd->resize(725, 523);
        verticalLayout = new QVBoxLayout(JobViewCmd);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        labelLogo = new QLabel(JobViewCmd);
        labelLogo->setObjectName(QStringLiteral("labelLogo"));
        labelLogo->setMinimumSize(QSize(48, 48));
        labelLogo->setMaximumSize(QSize(48, 48));
        labelLogo->setCursor(QCursor(Qt::OpenHandCursor));
        labelLogo->setPixmap(QPixmap(QString::fromUtf8(":/images/console.png")));
        labelLogo->setScaledContents(true);
        labelLogo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_2->addWidget(labelLogo);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_2);

        plainTextEdit = new QPlainTextEdit(JobViewCmd);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(9);
        plainTextEdit->setFont(font);
        plainTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        plainTextEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(plainTextEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(50, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        frame = new QFrame(JobViewCmd);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(frame);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(55, -1, -1, -1);
        checkBoxShowDetail = new QCheckBox(JobViewCmd);
        checkBoxShowDetail->setObjectName(QStringLiteral("checkBoxShowDetail"));
        checkBoxShowDetail->setLayoutDirection(Qt::LeftToRight);
        checkBoxShowDetail->setAutoFillBackground(false);

        horizontalLayout->addWidget(checkBoxShowDetail);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonSave = new QPushButton(JobViewCmd);
        buttonSave->setObjectName(QStringLiteral("buttonSave"));
        buttonSave->setMinimumSize(QSize(100, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSave->setIcon(icon);
        buttonSave->setFlat(false);

        horizontalLayout->addWidget(buttonSave);

        buttonCopy = new QPushButton(JobViewCmd);
        buttonCopy->setObjectName(QStringLiteral("buttonCopy"));
        buttonCopy->setMinimumSize(QSize(100, 0));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/page_paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCopy->setIcon(icon1);
        buttonCopy->setFlat(false);

        horizontalLayout->addWidget(buttonCopy);

        buttonClose = new QPushButton(JobViewCmd);
        buttonClose->setObjectName(QStringLiteral("buttonClose"));
        buttonClose->setMinimumSize(QSize(100, 0));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/buttons/cross_grey.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonClose->setIcon(icon2);
        buttonClose->setFlat(false);

        horizontalLayout->addWidget(buttonClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(JobViewCmd);
        QObject::connect(buttonClose, SIGNAL(clicked()), JobViewCmd, SLOT(close()));

        QMetaObject::connectSlotsByName(JobViewCmd);
    } // setupUi

    void retranslateUi(QWidget *JobViewCmd)
    {
        JobViewCmd->setWindowTitle(QApplication::translate("JobViewCmd", "Command View", nullptr));
        labelLogo->setText(QString());
        checkBoxShowDetail->setText(QApplication::translate("JobViewCmd", "Detail", nullptr));
        buttonSave->setText(QApplication::translate("JobViewCmd", "Save", nullptr));
        buttonCopy->setText(QApplication::translate("JobViewCmd", "Copy", nullptr));
        buttonClose->setText(QApplication::translate("JobViewCmd", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JobViewCmd: public Ui_JobViewCmd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOB_VIEW_CMD_H
