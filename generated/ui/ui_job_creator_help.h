/********************************************************************************
** Form generated from reading UI file 'job_creator_help.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOB_CREATOR_HELP_H
#define UI_JOB_CREATOR_HELP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_JobCreatorHelp
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelLogo;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *plainTextEdit;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonClose;

    void setupUi(QDialog *JobCreatorHelp)
    {
        if (JobCreatorHelp->objectName().isEmpty())
            JobCreatorHelp->setObjectName(QStringLiteral("JobCreatorHelp"));
        JobCreatorHelp->resize(899, 549);
        JobCreatorHelp->setSizeGripEnabled(true);
        JobCreatorHelp->setModal(true);
        verticalLayout = new QVBoxLayout(JobCreatorHelp);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(7, -1, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(7);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        labelLogo = new QLabel(JobCreatorHelp);
        labelLogo->setObjectName(QStringLiteral("labelLogo"));
        labelLogo->setMinimumSize(QSize(48, 48));
        labelLogo->setMaximumSize(QSize(48, 48));
        labelLogo->setPixmap(QPixmap(QString::fromUtf8(":/images/help.png")));
        labelLogo->setScaledContents(true);
        labelLogo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_2->addWidget(labelLogo);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_2);

        plainTextEdit = new QPlainTextEdit(JobCreatorHelp);
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

        frame = new QFrame(JobCreatorHelp);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonClose = new QPushButton(JobCreatorHelp);
        buttonClose->setObjectName(QStringLiteral("buttonClose"));
        buttonClose->setMinimumSize(QSize(100, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/cross_grey.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonClose->setIcon(icon);
        buttonClose->setFlat(false);

        horizontalLayout->addWidget(buttonClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(JobCreatorHelp);
        QObject::connect(buttonClose, SIGNAL(clicked()), JobCreatorHelp, SLOT(accept()));

        QMetaObject::connectSlotsByName(JobCreatorHelp);
    } // setupUi

    void retranslateUi(QDialog *JobCreatorHelp)
    {
        JobCreatorHelp->setWindowTitle(QApplication::translate("JobCreatorHelp", "Help Screen", nullptr));
        labelLogo->setText(QString());
        buttonClose->setText(QApplication::translate("JobCreatorHelp", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JobCreatorHelp: public Ui_JobCreatorHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOB_CREATOR_HELP_H
