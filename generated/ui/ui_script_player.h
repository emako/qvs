/********************************************************************************
** Form generated from reading UI file 'script_player.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCRIPT_PLAYER_H
#define UI_SCRIPT_PLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScriptPlayer
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *editInput;
    QToolButton *buttonInput;
    QTextEdit *editMountMessage;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelArch;
    QComboBox *comboBoxArch;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelPlayer;
    QComboBox *comboBoxPlayer;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelMessage;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonMount;
    QPushButton *buttonPlay;

    void setupUi(QWidget *ScriptPlayer)
    {
        if (ScriptPlayer->objectName().isEmpty())
            ScriptPlayer->setObjectName(QStringLiteral("ScriptPlayer"));
        ScriptPlayer->resize(418, 403);
        ScriptPlayer->setAcceptDrops(true);
        verticalLayout_2 = new QVBoxLayout(ScriptPlayer);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        editInput = new QLineEdit(ScriptPlayer);
        editInput->setObjectName(QStringLiteral("editInput"));
        editInput->setMinimumSize(QSize(0, 25));
        editInput->setAcceptDrops(true);

        horizontalLayout->addWidget(editInput);

        buttonInput = new QToolButton(ScriptPlayer);
        buttonInput->setObjectName(QStringLiteral("buttonInput"));
        buttonInput->setMinimumSize(QSize(40, 26));
        buttonInput->setMaximumSize(QSize(45, 16777215));

        horizontalLayout->addWidget(buttonInput);


        verticalLayout_2->addLayout(horizontalLayout);

        editMountMessage = new QTextEdit(ScriptPlayer);
        editMountMessage->setObjectName(QStringLiteral("editMountMessage"));
        editMountMessage->setContextMenuPolicy(Qt::CustomContextMenu);
        editMountMessage->setAcceptDrops(false);
        editMountMessage->setReadOnly(true);

        verticalLayout_2->addWidget(editMountMessage);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelArch = new QLabel(ScriptPlayer);
        labelArch->setObjectName(QStringLiteral("labelArch"));
        labelArch->setMinimumSize(QSize(60, 0));

        horizontalLayout_2->addWidget(labelArch);

        comboBoxArch = new QComboBox(ScriptPlayer);
        comboBoxArch->addItem(QString());
        comboBoxArch->addItem(QString());
        comboBoxArch->setObjectName(QStringLiteral("comboBoxArch"));
        comboBoxArch->setMinimumSize(QSize(130, 0));

        horizontalLayout_2->addWidget(comboBoxArch);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelPlayer = new QLabel(ScriptPlayer);
        labelPlayer->setObjectName(QStringLiteral("labelPlayer"));
        labelPlayer->setMinimumSize(QSize(60, 0));

        horizontalLayout_3->addWidget(labelPlayer);

        comboBoxPlayer = new QComboBox(ScriptPlayer);
        comboBoxPlayer->addItem(QString());
        comboBoxPlayer->addItem(QString());
        comboBoxPlayer->addItem(QString());
        comboBoxPlayer->setObjectName(QStringLiteral("comboBoxPlayer"));
        comboBoxPlayer->setMinimumSize(QSize(130, 0));

        horizontalLayout_3->addWidget(comboBoxPlayer);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelMessage = new QLabel(ScriptPlayer);
        labelMessage->setObjectName(QStringLiteral("labelMessage"));

        horizontalLayout_4->addWidget(labelMessage);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        buttonMount = new QPushButton(ScriptPlayer);
        buttonMount->setObjectName(QStringLiteral("buttonMount"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/pismo.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonMount->setIcon(icon);
        buttonMount->setCheckable(true);

        horizontalLayout_4->addWidget(buttonMount);

        buttonPlay = new QPushButton(ScriptPlayer);
        buttonPlay->setObjectName(QStringLiteral("buttonPlay"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonPlay->setIcon(icon1);

        horizontalLayout_4->addWidget(buttonPlay);


        verticalLayout_2->addLayout(horizontalLayout_4);


        retranslateUi(ScriptPlayer);

        comboBoxArch->setCurrentIndex(0);
        comboBoxPlayer->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ScriptPlayer);
    } // setupUi

    void retranslateUi(QWidget *ScriptPlayer)
    {
        ScriptPlayer->setWindowTitle(QApplication::translate("ScriptPlayer", "Script Player", nullptr));
        editInput->setPlaceholderText(QApplication::translate("ScriptPlayer", "Enable VapourSynth/Avisynth Script", nullptr));
        buttonInput->setText(QApplication::translate("ScriptPlayer", "...", nullptr));
        editMountMessage->setPlainText(QString());
        editMountMessage->setPlaceholderText(QApplication::translate("ScriptPlayer", "Enable Drag and drop Event ...", nullptr));
        labelArch->setText(QApplication::translate("ScriptPlayer", "Arch:", nullptr));
        comboBoxArch->setItemText(0, QApplication::translate("ScriptPlayer", "64-Bit (x64)", nullptr));
        comboBoxArch->setItemText(1, QApplication::translate("ScriptPlayer", "32-Bit (x86)", nullptr));

        labelPlayer->setText(QApplication::translate("ScriptPlayer", "Player:", nullptr));
        comboBoxPlayer->setItemText(0, QApplication::translate("ScriptPlayer", "<System>", nullptr));
        comboBoxPlayer->setItemText(1, QApplication::translate("ScriptPlayer", "Preview", nullptr));
        comboBoxPlayer->setItemText(2, QApplication::translate("ScriptPlayer", "VirtualDub", nullptr));

        labelMessage->setText(QApplication::translate("ScriptPlayer", "Message", nullptr));
        buttonMount->setText(QApplication::translate("ScriptPlayer", "Mount", nullptr));
        buttonPlay->setText(QApplication::translate("ScriptPlayer", "Play", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScriptPlayer: public Ui_ScriptPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCRIPT_PLAYER_H
