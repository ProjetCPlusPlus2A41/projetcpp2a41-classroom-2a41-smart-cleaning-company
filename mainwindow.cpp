#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    employeTemp()  // Initialize serviceTemp for Service operations
{
    ui->setupUi(this);
    setupValidation();

    // Initialize table view to display services
    ui->tableView->setModel(employeTemp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

// mainwindow.cpp
void MainWindow::setTableModel(QSqlQueryModel *model)
{
    ui->tableView->setModel(model);  // Cette ligne lie le modèle au QTableView
}


void MainWindow::on_pushButton_ajouter_clicked()
{
    // Retrieve input values from UI elements
    int id = ui->lineEdit_ID->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString poste = ui->comboBox_poste->currentText();
    QString email = ui->lineEdit_email->text();

    // Validate email format
    QRegularExpression regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!regex.match(email).hasMatch()) {
        QMessageBox::warning(this, tr("Invalid Email"),
                             tr("Please enter a valid email address."),
                             QMessageBox::Ok);
        return; // Stop further processing if email is invalid
    }

    if (prenom.contains(QRegularExpression("[0-9]"))) {
        QMessageBox::warning(this, tr("Invalid First Name"),
                             tr("The first name must not contain numbers."),
                             QMessageBox::Ok);
        return; // Stop further processing if first name is invalid
    }

    if (nom.contains(QRegularExpression("[0-9]"))) {
        QMessageBox::warning(this, tr("Invalid First Name"),
                             tr("The first name must not contain numbers."),
                             QMessageBox::Ok);
        return; // Stop further processing if first name is invalid
    }

    // Create a Service object with retrieved values
    employe newemploye(id, nom, prenom, poste, email);

    // Add the service to the database
    bool success = newemploye.ajouter();

    if (success) // If addition was successful
    {
        ui->tableView->setModel(employeTemp.afficher()); // Refresh table view

        QMessageBox::information(this, tr("Success"),
                                 tr("Service added successfully."),
                                 QMessageBox::Ok);
    }
    else // If addition failed
    {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to add service."),
                              QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEditIDS->text().toInt(); // Retrieve ID from lineEditIDS

    bool success = employeTemp.supprimer(id); // Attempt to delete service by ID

    if (success) // If deletion was successful
    {
        ui->tableView->setModel(employeTemp.afficher()); // Refresh table view

        QMessageBox::information(this, tr("Success"),
                                 tr("Service deleted successfully."),
                                 QMessageBox::Ok);
    }
    else // If deletion failed
    {
        QMessageBox::critical(this, tr("Failure"),
                              tr("Failed to delete service."),
                              QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_modifier_clicked()
{
    int id = ui->lineEdit_ID_2->text().toInt();  // Récupérer l'ID
    QString nom = ui->lineEdit_nom_2->text();  // Récupérer le type
    QString prenom = ui->lineEdit_prenom_2->text();  // Récupérer la date
    QString poste = ui->comboBox_poste_2->currentText();  // Récupérer l'état
    QString email = ui->lineEdit_email_2->text();

    if (prenom.contains(QRegularExpression("[0-9]"))) {
        QMessageBox::warning(this, tr("Invalid First Name"),
                             tr("The first name must not contain numbers."),
                             QMessageBox::Ok);
        return; // Stop further processing if first name is invalid
    }

    if (nom.contains(QRegularExpression("[0-9]"))) {
        QMessageBox::warning(this, tr("Invalid First Name"),
                             tr("The first name must not contain numbers."),
                             QMessageBox::Ok);
        return; // Stop further processing if first name is invalid
    }

    // Validate email format
    QRegularExpression regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!regex.match(email).hasMatch()) {
        QMessageBox::warning(this, tr("Invalid Email"),
                             tr("Please enter a valid email address."),
                             QMessageBox::Ok);
        return; // Stop further processing if email is invalid
    }

    employe employe;  // Créer un objet Service
    bool result = employe.modifier(id, nom, prenom, poste, email);  // Appeler la méthode de modification

    if (result) {
        QMessageBox::information(this, "Success", "Service updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "ID not found. Update failed.");
    }

    // Rafraîchir l'affichage du QTableView
    QSqlQueryModel *model = employe.afficher();  // Afficher les données mises à jour
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
