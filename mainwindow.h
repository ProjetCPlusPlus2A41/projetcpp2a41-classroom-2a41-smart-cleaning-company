#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "service.h" // Inclure le fichier d'en-tête de Service

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
    Service serviceTemp; // Déclaration de serviceTemp pour stocker les données temporaires de Service

private slots:
    void on_pushButton_ajouter_clicked(); // Slot pour le bouton Ajouter
    void on_pushButton_modifier_clicked();
    void setupValidation();
    void setupDateValidation();
    void on_dateEdit_dateChanged(const QDate &date);
    void on_dateEdit_date_2Changed(const QDate &date);
    void on_pushButton_supprimer_clicked(); // Slot pour le bouton Supprimer
};

#endif // MAINWINDOW_H
