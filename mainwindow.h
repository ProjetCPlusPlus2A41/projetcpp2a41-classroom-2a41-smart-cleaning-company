#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QString>
#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QSqlQuery>      // Pour exécuter des requêtes SQL
#include <QSqlError>      // Pour gérer les erreurs de requête SQL
#include <QMessageBox>    // Pour afficher des messages d'information ou d'erreur
#include <QDebug>
#include "gestionemployes.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void on_pushButton_login_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
