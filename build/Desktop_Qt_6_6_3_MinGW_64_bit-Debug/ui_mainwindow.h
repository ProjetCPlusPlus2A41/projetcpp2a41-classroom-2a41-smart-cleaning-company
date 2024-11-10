/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_ID;
    QLineEdit *lineEdit_nom;
    QLineEdit *lineEdit_prenom;
    QPushButton *pushButton_ajouter;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *comboBox_poste;
    QLineEdit *lineEdit_email;
    QWidget *tab_2;
    QGroupBox *groupBox_2;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_ID_2;
    QLineEdit *lineEdit_nom_2;
    QLineEdit *lineEdit_prenom_2;
    QPushButton *pushButton_modifier;
    QLabel *label_9;
    QLabel *label_10;
    QComboBox *comboBox_poste_2;
    QLineEdit *lineEdit_email_2;
    QWidget *tab_3;
    QGroupBox *groupBox_3;
    QTableView *tableView;
    QWidget *tab_4;
    QGroupBox *groupBox_4;
    QLineEdit *lineEditIDS;
    QLabel *label_11;
    QPushButton *pushButton_supprimer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(850, 540);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(30, 20, 791, 441));
        tab = new QWidget();
        tab->setObjectName("tab");
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(200, 20, 351, 361));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 40, 47, 13));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 47, 13));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 120, 47, 16));
        lineEdit_ID = new QLineEdit(groupBox);
        lineEdit_ID->setObjectName("lineEdit_ID");
        lineEdit_ID->setGeometry(QRect(140, 40, 113, 20));
        lineEdit_nom = new QLineEdit(groupBox);
        lineEdit_nom->setObjectName("lineEdit_nom");
        lineEdit_nom->setGeometry(QRect(140, 80, 113, 20));
        lineEdit_prenom = new QLineEdit(groupBox);
        lineEdit_prenom->setObjectName("lineEdit_prenom");
        lineEdit_prenom->setGeometry(QRect(140, 120, 113, 20));
        pushButton_ajouter = new QPushButton(groupBox);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setGeometry(QRect(130, 310, 75, 23));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 170, 47, 16));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 220, 47, 16));
        comboBox_poste = new QComboBox(groupBox);
        comboBox_poste->addItem(QString());
        comboBox_poste->addItem(QString());
        comboBox_poste->addItem(QString());
        comboBox_poste->setObjectName("comboBox_poste");
        comboBox_poste->setGeometry(QRect(140, 170, 121, 22));
        lineEdit_email = new QLineEdit(groupBox);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setGeometry(QRect(140, 220, 113, 20));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(230, 20, 351, 361));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 40, 47, 13));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 80, 47, 13));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 120, 47, 16));
        lineEdit_ID_2 = new QLineEdit(groupBox_2);
        lineEdit_ID_2->setObjectName("lineEdit_ID_2");
        lineEdit_ID_2->setGeometry(QRect(140, 40, 113, 20));
        lineEdit_nom_2 = new QLineEdit(groupBox_2);
        lineEdit_nom_2->setObjectName("lineEdit_nom_2");
        lineEdit_nom_2->setGeometry(QRect(140, 80, 113, 20));
        lineEdit_prenom_2 = new QLineEdit(groupBox_2);
        lineEdit_prenom_2->setObjectName("lineEdit_prenom_2");
        lineEdit_prenom_2->setGeometry(QRect(140, 120, 113, 20));
        pushButton_modifier = new QPushButton(groupBox_2);
        pushButton_modifier->setObjectName("pushButton_modifier");
        pushButton_modifier->setGeometry(QRect(130, 310, 75, 23));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 170, 47, 16));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 220, 47, 16));
        comboBox_poste_2 = new QComboBox(groupBox_2);
        comboBox_poste_2->addItem(QString());
        comboBox_poste_2->addItem(QString());
        comboBox_poste_2->addItem(QString());
        comboBox_poste_2->setObjectName("comboBox_poste_2");
        comboBox_poste_2->setGeometry(QRect(140, 170, 121, 22));
        lineEdit_email_2 = new QLineEdit(groupBox_2);
        lineEdit_email_2->setObjectName("lineEdit_email_2");
        lineEdit_email_2->setGeometry(QRect(140, 220, 113, 20));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(19, 9, 751, 391));
        tableView = new QTableView(groupBox_3);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(30, 20, 711, 361));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        groupBox_4 = new QGroupBox(tab_4);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(230, 50, 321, 241));
        lineEditIDS = new QLineEdit(groupBox_4);
        lineEditIDS->setObjectName("lineEditIDS");
        lineEditIDS->setGeometry(QRect(140, 40, 113, 22));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 40, 49, 16));
        pushButton_supprimer = new QPushButton(groupBox_4);
        pushButton_supprimer->setObjectName("pushButton_supprimer");
        pushButton_supprimer->setGeometry(QRect(120, 130, 75, 24));
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 850, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Ajouter Employe", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "id", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "nom", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "prenom", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "poste", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        comboBox_poste->setItemText(0, QCoreApplication::translate("MainWindow", "poste 1", nullptr));
        comboBox_poste->setItemText(1, QCoreApplication::translate("MainWindow", "poste 2", nullptr));
        comboBox_poste->setItemText(2, QCoreApplication::translate("MainWindow", "poste 3", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "modifier Employe", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "id", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "nom", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "prenom", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "poste", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        comboBox_poste_2->setItemText(0, QCoreApplication::translate("MainWindow", "poste 1", nullptr));
        comboBox_poste_2->setItemText(1, QCoreApplication::translate("MainWindow", "poste 2", nullptr));
        comboBox_poste_2->setItemText(2, QCoreApplication::translate("MainWindow", "poste 3", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "afficher employe", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Page", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "supprimer employe", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "id", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
