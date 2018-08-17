/********************************************************************************
** Form generated from reading UI file 'preferences.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCES_H
#define UI_PREFERENCES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Preferences
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkNotRunNextJob;
    QLabel *labelNotRunNextJob;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkNotShowSplashScreen;
    QLabel *labelNotShowSplashScreen;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBoxDummy1;
    QLabel *labelJobCount;
    QSpinBox *spinBoxJobCount;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkUse32BitAVS;
    QLabel *labelUse64BitAVS;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_14;
    QCheckBox *checkBoxDG;
    QLabel *labelProcessPriority_4;
    QLineEdit *editDG;
    QToolButton *buttonDG;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *checkBoxDGNV;
    QLabel *labelDGNV;
    QLineEdit *editDGNV;
    QToolButton *buttonDGNV;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBoxDummy3;
    QLabel *labelStyleFactory;
    QComboBox *comboBoxStyleFactory;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *checkBoxDummy2;
    QLabel *labelProcessPriority;
    QComboBox *comboBoxPriority;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *resetButton;
    QPushButton *closeButton;

    void setupUi(QDialog *Preferences)
    {
        if (Preferences->objectName().isEmpty())
            Preferences->setObjectName(QStringLiteral("Preferences"));
        Preferences->setWindowModality(Qt::ApplicationModal);
        Preferences->resize(573, 331);
        Preferences->setModal(true);
        verticalLayout_2 = new QVBoxLayout(Preferences);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_2 = new QGroupBox(Preferences);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkNotRunNextJob = new QCheckBox(groupBox_2);
        checkNotRunNextJob->setObjectName(QStringLiteral("checkNotRunNextJob"));
        checkNotRunNextJob->setText(QStringLiteral(""));

        horizontalLayout_2->addWidget(checkNotRunNextJob);

        labelNotRunNextJob = new QLabel(groupBox_2);
        labelNotRunNextJob->setObjectName(QStringLiteral("labelNotRunNextJob"));

        horizontalLayout_2->addWidget(labelNotRunNextJob);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        checkNotShowSplashScreen = new QCheckBox(groupBox_2);
        checkNotShowSplashScreen->setObjectName(QStringLiteral("checkNotShowSplashScreen"));
        checkNotShowSplashScreen->setText(QStringLiteral(""));

        horizontalLayout_5->addWidget(checkNotShowSplashScreen);

        labelNotShowSplashScreen = new QLabel(groupBox_2);
        labelNotShowSplashScreen->setObjectName(QStringLiteral("labelNotShowSplashScreen"));

        horizontalLayout_5->addWidget(labelNotShowSplashScreen);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBoxDummy1 = new QCheckBox(groupBox_2);
        checkBoxDummy1->setObjectName(QStringLiteral("checkBoxDummy1"));
        checkBoxDummy1->setEnabled(false);

        horizontalLayout_3->addWidget(checkBoxDummy1);

        labelJobCount = new QLabel(groupBox_2);
        labelJobCount->setObjectName(QStringLiteral("labelJobCount"));
        labelJobCount->setEnabled(false);

        horizontalLayout_3->addWidget(labelJobCount);

        spinBoxJobCount = new QSpinBox(groupBox_2);
        spinBoxJobCount->setObjectName(QStringLiteral("spinBoxJobCount"));
        spinBoxJobCount->setEnabled(false);
        spinBoxJobCount->setMinimumSize(QSize(80, 0));
        spinBoxJobCount->setMinimum(1);
        spinBoxJobCount->setMaximum(16);

        horizontalLayout_3->addWidget(spinBoxJobCount);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        checkUse32BitAVS = new QCheckBox(groupBox_2);
        checkUse32BitAVS->setObjectName(QStringLiteral("checkUse32BitAVS"));
        checkUse32BitAVS->setText(QStringLiteral(""));

        horizontalLayout_7->addWidget(checkUse32BitAVS);

        labelUse64BitAVS = new QLabel(groupBox_2);
        labelUse64BitAVS->setObjectName(QStringLiteral("labelUse64BitAVS"));

        horizontalLayout_7->addWidget(labelUse64BitAVS);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(3);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        checkBoxDG = new QCheckBox(groupBox_2);
        checkBoxDG->setObjectName(QStringLiteral("checkBoxDG"));
        checkBoxDG->setEnabled(false);

        horizontalLayout_14->addWidget(checkBoxDG);

        labelProcessPriority_4 = new QLabel(groupBox_2);
        labelProcessPriority_4->setObjectName(QStringLiteral("labelProcessPriority_4"));
        labelProcessPriority_4->setMinimumSize(QSize(75, 0));

        horizontalLayout_14->addWidget(labelProcessPriority_4);

        editDG = new QLineEdit(groupBox_2);
        editDG->setObjectName(QStringLiteral("editDG"));

        horizontalLayout_14->addWidget(editDG);

        buttonDG = new QToolButton(groupBox_2);
        buttonDG->setObjectName(QStringLiteral("buttonDG"));

        horizontalLayout_14->addWidget(buttonDG);


        verticalLayout_3->addLayout(horizontalLayout_14);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(3);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        checkBoxDGNV = new QCheckBox(groupBox_2);
        checkBoxDGNV->setObjectName(QStringLiteral("checkBoxDGNV"));
        checkBoxDGNV->setEnabled(false);

        horizontalLayout_12->addWidget(checkBoxDGNV);

        labelDGNV = new QLabel(groupBox_2);
        labelDGNV->setObjectName(QStringLiteral("labelDGNV"));
        labelDGNV->setMinimumSize(QSize(75, 0));

        horizontalLayout_12->addWidget(labelDGNV);

        editDGNV = new QLineEdit(groupBox_2);
        editDGNV->setObjectName(QStringLiteral("editDGNV"));

        horizontalLayout_12->addWidget(editDGNV);

        buttonDGNV = new QToolButton(groupBox_2);
        buttonDGNV->setObjectName(QStringLiteral("buttonDGNV"));

        horizontalLayout_12->addWidget(buttonDGNV);


        verticalLayout_3->addLayout(horizontalLayout_12);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        checkBoxDummy3 = new QCheckBox(groupBox_2);
        checkBoxDummy3->setObjectName(QStringLiteral("checkBoxDummy3"));
        checkBoxDummy3->setEnabled(false);

        horizontalLayout_4->addWidget(checkBoxDummy3);

        labelStyleFactory = new QLabel(groupBox_2);
        labelStyleFactory->setObjectName(QStringLiteral("labelStyleFactory"));

        horizontalLayout_4->addWidget(labelStyleFactory);

        comboBoxStyleFactory = new QComboBox(groupBox_2);
        comboBoxStyleFactory->setObjectName(QStringLiteral("comboBoxStyleFactory"));
        comboBoxStyleFactory->setEditable(false);
        comboBoxStyleFactory->setFrame(true);

        horizontalLayout_4->addWidget(comboBoxStyleFactory);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        checkBoxDummy2 = new QCheckBox(groupBox_2);
        checkBoxDummy2->setObjectName(QStringLiteral("checkBoxDummy2"));
        checkBoxDummy2->setEnabled(false);

        horizontalLayout_11->addWidget(checkBoxDummy2);

        labelProcessPriority = new QLabel(groupBox_2);
        labelProcessPriority->setObjectName(QStringLiteral("labelProcessPriority"));

        horizontalLayout_11->addWidget(labelProcessPriority);

        comboBoxPriority = new QComboBox(groupBox_2);
        comboBoxPriority->addItem(QString());
        comboBoxPriority->addItem(QString());
        comboBoxPriority->addItem(QString());
        comboBoxPriority->addItem(QString());
        comboBoxPriority->addItem(QString());
        comboBoxPriority->addItem(QString());
        comboBoxPriority->setObjectName(QStringLiteral("comboBoxPriority"));
        comboBoxPriority->setEditable(false);
        comboBoxPriority->setFrame(true);

        horizontalLayout_11->addWidget(comboBoxPriority);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_9);


        verticalLayout_3->addLayout(horizontalLayout_11);


        verticalLayout->addLayout(verticalLayout_3);


        verticalLayout_2->addWidget(groupBox_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        resetButton = new QPushButton(Preferences);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setMinimumSize(QSize(100, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/restart.png"), QSize(), QIcon::Normal, QIcon::Off);
        resetButton->setIcon(icon);

        horizontalLayout->addWidget(resetButton);

        closeButton = new QPushButton(Preferences);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setMinimumSize(QSize(100, 0));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/accept.png"), QSize(), QIcon::Normal, QIcon::Off);
        closeButton->setIcon(icon1);

        horizontalLayout->addWidget(closeButton);


        verticalLayout_2->addLayout(horizontalLayout);

        QWidget::setTabOrder(closeButton, resetButton);

        retranslateUi(Preferences);
        QObject::connect(closeButton, SIGNAL(clicked()), Preferences, SLOT(accept()));

        comboBoxPriority->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Preferences);
    } // setupUi

    void retranslateUi(QDialog *Preferences)
    {
        Preferences->setWindowTitle(QApplication::translate("Preferences", "Preferences", nullptr));
        groupBox_2->setTitle(QApplication::translate("Preferences", " Preferences ", nullptr));
        labelNotRunNextJob->setText(QApplication::translate("Preferences", "Not automatically launch next job when a running job completes", nullptr));
#ifndef QT_NO_TOOLTIP
        labelNotShowSplashScreen->setToolTip(QApplication::translate("Preferences", "If this option is checked, then splash screen wil not be showed.", nullptr));
#endif // QT_NO_TOOLTIP
        labelNotShowSplashScreen->setText(QApplication::translate("Preferences", "Not show splash screen", nullptr));
        checkBoxDummy1->setText(QString());
#ifndef QT_NO_TOOLTIP
        labelJobCount->setToolTip(QApplication::translate("Preferences", "If the specified number of jobs (or even more) is already running, the next one will NOT be launched yet.", nullptr));
#endif // QT_NO_TOOLTIP
        labelJobCount->setText(QApplication::translate("Preferences", "Maximum number of running jobs:", nullptr));
#ifndef QT_NO_TOOLTIP
        spinBoxJobCount->setToolTip(QApplication::translate("Preferences", "If the specified number of jobs (or even more) is already running, the next one will NOT be launched yet.", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        checkUse32BitAVS->setToolTip(QApplication::translate("Preferences", "If this option is un-checked (default), then 32-Bit Avisynth will be used - even when using 64-Bit x264.\n"
"Please be aware that this option does NOT have any effect on 32-Bit systems.", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        labelUse64BitAVS->setToolTip(QApplication::translate("Preferences", "If this option is checked, then 32-Bit Avisynth will be used firstly.", nullptr));
#endif // QT_NO_TOOLTIP
        labelUse64BitAVS->setText(QApplication::translate("Preferences", "Prefer 32-Bit source (Avisynth) on 64-Bit systems", nullptr));
        checkBoxDG->setText(QString());
        labelProcessPriority_4->setText(QApplication::translate("Preferences", "DGIndex", nullptr));
        editDG->setPlaceholderText(QApplication::translate("Preferences", "DGIndex Folder Setting ...", nullptr));
        buttonDG->setText(QApplication::translate("Preferences", "...", nullptr));
        checkBoxDGNV->setText(QString());
        labelDGNV->setText(QApplication::translate("Preferences", "DGIndexNV", nullptr));
        editDGNV->setPlaceholderText(QApplication::translate("Preferences", "DGIndexNV Folder Setting ...", nullptr));
        buttonDGNV->setText(QApplication::translate("Preferences", "...", nullptr));
        checkBoxDummy3->setText(QString());
        labelStyleFactory->setText(QApplication::translate("Preferences", "Set style factory", nullptr));
        checkBoxDummy2->setText(QString());
        labelProcessPriority->setText(QApplication::translate("Preferences", "Priority for encoder processes:", nullptr));
        comboBoxPriority->setItemText(0, QApplication::translate("Preferences", "Idle", nullptr));
        comboBoxPriority->setItemText(1, QApplication::translate("Preferences", "Below Normal", nullptr));
        comboBoxPriority->setItemText(2, QApplication::translate("Preferences", "Normal", nullptr));
        comboBoxPriority->setItemText(3, QApplication::translate("Preferences", "Above Normal", nullptr));
        comboBoxPriority->setItemText(4, QApplication::translate("Preferences", "High", nullptr));
        comboBoxPriority->setItemText(5, QApplication::translate("Preferences", "Realtime", nullptr));

        resetButton->setText(QApplication::translate("Preferences", "Reset", nullptr));
        closeButton->setText(QApplication::translate("Preferences", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Preferences: public Ui_Preferences {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCES_H
