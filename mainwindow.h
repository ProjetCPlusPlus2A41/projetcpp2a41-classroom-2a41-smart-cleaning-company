#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h" // Inclure le fichier d'en-tête de Service

namespace Ui {
class MainWindow; // Déclaration de la classe Ui::MainWindow
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTableModel(QSqlQueryModel *model);

private:
    Ui::MainWindow *ui;
    employe employeTemp; // Déclaration de serviceTemp pour stocker les données temporaires de Service

private slots:
    void on_pushButton_ajouter_clicked(); // Slot pour le bouton Ajouter
    void on_pushButton_modifier_clicked();
    void setupValidation();
    void on_pushButton_supprimer_clicked(); // Slot pour le bouton Supprimer
};

#endif // MAINWINDOW_H
