#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QMessageBox>
#include "livraison.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QComboBox> // Inclure QComboBox
#include <QtCore>
#include <QtGui>
#include <QtCharts>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

        //void afficherStatistiques();


private slots:
    void setupTableView();
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_modifier_clicked();
    void trierParDate();
    void filtrerLivraison(const QString &text);
    void filtrerParEtat(const QString &etat);
    void exporterVersExcel();
    void exporterVersPdf();
    void trierParMontant();

    void afficherStatistiques();
    void afficherStatistiques1();
    void afficherStatistiques2();
    void afficherStatistiques3();
    void afficherStatistiques4();
    void afficherStatistiques5();
private:
    Ui::MainWindow *ui;
    Livraison l;
    Livraison* livraison; // Instance de la classe Livraison
    QSqlTableModel *model;

    QLabel *imageLabel; // QLabel pour afficher l'image
    void loadImage(const QString &imagePath);

    QComboBox *etatComboBox;
    void setupUI();

protected:
    void paintEvent(QPaintEvent *event) override; // Pour le dessin personnalisé
};

#endif // MAINWINDOW_H
