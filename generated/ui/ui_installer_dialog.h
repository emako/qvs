/********************************************************************************
** Form generated from reading UI file 'installer_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALLER_DIALOG_H
#define UI_INSTALLER_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InstallerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QTreeWidget *treeWidgetModule;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *buttonDefault;
    QPushButton *buttonSecletAll;
    QPushButton *buttonSelectNone;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBoxUninstall;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *buttonInstall;
    QPushButton *buttonCancel;

    void setupUi(QDialog *InstallerDialog)
    {
        if (InstallerDialog->objectName().isEmpty())
            InstallerDialog->setObjectName(QStringLiteral("InstallerDialog"));
        InstallerDialog->resize(413, 370);
        verticalLayout = new QVBoxLayout(InstallerDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelTitle = new QLabel(InstallerDialog);
        labelTitle->setObjectName(QStringLiteral("labelTitle"));

        verticalLayout->addWidget(labelTitle);

        treeWidgetModule = new QTreeWidget(InstallerDialog);
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/python_module.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setIcon(0, icon);
        treeWidgetModule->setHeaderItem(__qtreewidgetitem);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/pismo.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font;
        font.setStyleStrategy(QFont::PreferDefault);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/buttons/ffmpeg.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/buttons/page_menu.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidgetModule);
        __qtreewidgetitem1->setCheckState(0, Qt::Unchecked);
        __qtreewidgetitem1->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidgetModule);
        __qtreewidgetitem2->setCheckState(0, Qt::Unchecked);
        __qtreewidgetitem2->setFont(0, font);
        __qtreewidgetitem2->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(treeWidgetModule);
        __qtreewidgetitem3->setCheckState(0, Qt::Unchecked);
        __qtreewidgetitem3->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(treeWidgetModule);
        __qtreewidgetitem4->setCheckState(0, Qt::Unchecked);
        __qtreewidgetitem4->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(treeWidgetModule);
        __qtreewidgetitem5->setCheckState(0, Qt::Unchecked);
        __qtreewidgetitem5->setIcon(0, icon3);
        treeWidgetModule->setObjectName(QStringLiteral("treeWidgetModule"));
        treeWidgetModule->header()->setVisible(true);
        treeWidgetModule->header()->setCascadingSectionResizes(false);
        treeWidgetModule->header()->setHighlightSections(false);

        verticalLayout->addWidget(treeWidgetModule);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        buttonDefault = new QPushButton(InstallerDialog);
        buttonDefault->setObjectName(QStringLiteral("buttonDefault"));
        buttonDefault->setMinimumSize(QSize(95, 0));

        horizontalLayout_4->addWidget(buttonDefault);

        buttonSecletAll = new QPushButton(InstallerDialog);
        buttonSecletAll->setObjectName(QStringLiteral("buttonSecletAll"));
        buttonSecletAll->setMinimumSize(QSize(95, 0));

        horizontalLayout_4->addWidget(buttonSecletAll);

        buttonSelectNone = new QPushButton(InstallerDialog);
        buttonSelectNone->setObjectName(QStringLiteral("buttonSelectNone"));
        buttonSelectNone->setMinimumSize(QSize(95, 0));

        horizontalLayout_4->addWidget(buttonSelectNone);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBoxUninstall = new QCheckBox(InstallerDialog);
        checkBoxUninstall->setObjectName(QStringLiteral("checkBoxUninstall"));

        horizontalLayout_2->addWidget(checkBoxUninstall);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        buttonInstall = new QPushButton(InstallerDialog);
        buttonInstall->setObjectName(QStringLiteral("buttonInstall"));
        buttonInstall->setMinimumSize(QSize(100, 0));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/buttons/shield_admin.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonInstall->setIcon(icon4);

        horizontalLayout->addWidget(buttonInstall);

        buttonCancel = new QPushButton(InstallerDialog);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setMinimumSize(QSize(100, 0));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/buttons/cross.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon5);

        horizontalLayout->addWidget(buttonCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(InstallerDialog);
        QObject::connect(buttonCancel, SIGNAL(clicked()), InstallerDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(InstallerDialog);
    } // setupUi

    void retranslateUi(QDialog *InstallerDialog)
    {
        InstallerDialog->setWindowTitle(QApplication::translate("InstallerDialog", "Qvs Installer", nullptr));
        labelTitle->setText(QApplication::translate("InstallerDialog", "Choose a module", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidgetModule->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("InstallerDialog", "Module", nullptr));

        const bool __sortingEnabled = treeWidgetModule->isSortingEnabled();
        treeWidgetModule->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidgetModule->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("InstallerDialog", "Pismo File Mount 32-bit", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidgetModule->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("InstallerDialog", "VapourSynth 64-bit", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = treeWidgetModule->topLevelItem(2);
        ___qtreewidgetitem3->setText(0, QApplication::translate("InstallerDialog", "Avisynth 32-bit", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidgetModule->topLevelItem(3);
        ___qtreewidgetitem4->setText(0, QApplication::translate("InstallerDialog", "LAV Filters 64-bit and 32-bit", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = treeWidgetModule->topLevelItem(4);
        ___qtreewidgetitem5->setText(0, QApplication::translate("InstallerDialog", "Mediainfo/CopyPath menu", nullptr));
        treeWidgetModule->setSortingEnabled(__sortingEnabled);

        buttonDefault->setText(QApplication::translate("InstallerDialog", "Default", nullptr));
        buttonSecletAll->setText(QApplication::translate("InstallerDialog", "Select All", nullptr));
        buttonSelectNone->setText(QApplication::translate("InstallerDialog", "Select None", nullptr));
        checkBoxUninstall->setText(QApplication::translate("InstallerDialog", "Uninstall only", nullptr));
        buttonInstall->setText(QApplication::translate("InstallerDialog", "Install", nullptr));
        buttonCancel->setText(QApplication::translate("InstallerDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InstallerDialog: public Ui_InstallerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALLER_DIALOG_H
