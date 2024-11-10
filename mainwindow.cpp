#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "service.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serviceTemp()
{
    ui->setupUi(this);
    setupValidation();
    setupDateValidation();

    // Initialize table view to display services
    ui->tableView->setModel(serviceTemp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setTableModel(QSqlQueryModel *model)
{
    ui->tableView->setModel(model);  // Cette ligne lie le modèle au QTableView
}


void MainWindow::on_pushButton_ajouter_clicked()
{
    // Retrieve input values from UI elements
    int id = ui->lineEdit_ID->text().toInt();
    QString type = ui->comboBox_type->currentText();
    QDate date = ui->dateEdit_date->date();
    QString etat = ui->comboBox_etat->currentText();
    QString description = ui->textEdit_description->toPlainText();

    // Create a Service object with retrieved values
    Service newService(id, type, date, etat, description);

    // Add the service to the database
    bool success = newService.ajouter();

    if (success) // If addition was successful
    {
        ui->tableView->setModel(serviceTemp.afficher());

        QMessageBox::information(this, tr("Success"),
                                 tr("Service added successfully."),
                                 QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to add service."),
                              QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEditIDS->text().toInt();

    bool success = serviceTemp.supprimer(id); // delete service by ID

    if (success)
    {
        ui->tableView->setModel(serviceTemp.afficher());

        QMessageBox::information(this, tr("Success"),
                                 tr("Service deleted successfully."),
                                 QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to delete service."),
                              QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_modifier_clicked()
{
    int id = ui->lineEdit_ID_2->text().toInt();
    QString type = ui->comboBox_type_2->currentText();
    QDateTime date = ui->dateEdit_date_2->dateTime();
    QString etat = ui->comboBox_etat_2->currentText();
    QString description = ui->textEdit_description_2->toPlainText();

    Service service;  // Créer un objet Service
    bool result = service.modifier(id, type, date, etat, description);  // Appeler la méthode de modification

    if (result) {
        QMessageBox::information(this, "Success", "Service updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "ID not found. Update failed.");
    }

    // Rafraîchir l'affichage du QTableView
    QSqlQueryModel *model = service.afficher();  // Afficher les données mises à jour
    ui->tableView->setModel(model);  // Mettre à jour le modèle du tableView
}

void MainWindow::setupValidation()
{
    // Crée un validateur pour accepter uniquement des entiers entre 0 et 99999999 (8 chiffres maximum)
    QIntValidator *validator = new QIntValidator(0, 99999999, this);

    // Applique le validateur au QLineEdit
    ui->lineEdit_ID->setValidator(validator);

    // Applique le validateur au QLineEdit
    ui->lineEdit_ID_2->setValidator(validator);

    // Applique le validateur au QLineEdit
    ui->lineEditIDS->setValidator(validator);
}

void MainWindow::setupDateValidation()
{
    // Plage de dates : Min = aujourd'hui, Max = 1 an dans le futur
    ui->dateEdit_date->setMinimumDate(QDate::currentDate()); // Date minimale = aujourd'hui
    ui->dateEdit_date_2->setMinimumDate(QDate::currentDate()); // Date minimale = aujourd'hui pour le 2ème champ

    // Facultatif : Définir le format de la date pour une saisie claire
    ui->dateEdit_date->setDisplayFormat("yyyy-MM-dd");
    ui->dateEdit_date_2->setDisplayFormat("yyyy-MM-dd"); // Format de la date pour le 2ème champ
}

// Fonction de validation pour les deux champs (QDateEdit)
void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    // Vérifiez si la date saisie est antérieure à la date actuelle
    if (date < QDate::currentDate()) {
        QMessageBox::warning(this, "Date invalide", "La date ne peut pas être antérieure à la date actuelle.");
        // Réinitialiser le QDateEdit ou sélectionner la date actuelle
        ui->dateEdit_date->setDate(QDate::currentDate());
    }
}

// Fonction de validation pour le champ dateEdit_date_2
void MainWindow::on_dateEdit_date_2Changed(const QDate &date)
{
    // Vérifiez si la date saisie est antérieure à la date actuelle
    if (date < QDate::currentDate()) {
        QMessageBox::warning(this, "Date invalide", "La date ne peut pas être antérieure à la date actuelle.");
        // Réinitialiser le QDateEdit ou sélectionner la date actuelle
        ui->dateEdit_date_2->setDate(QDate::currentDate());
    }
}
