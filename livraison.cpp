#include "livraison.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>  // Include QSqlError for error handling
#include <QDebug>
#include <QSqlTableModel>

// Constructors
Livraison::Livraison() {}

Livraison::Livraison(int id, const QDateTime& date, const QString& adresse, const QString& etat, float montant)
    : id(id), date(date), adresse(adresse), etat(etat), montant(montant) {}

// Getters
int Livraison::getId() { return id; }

//QDate Livraison::getDate() { return date; }
QDateTime Livraison::getDate() const {
    return date;
}

QString Livraison::getAdresse() { return adresse; }

QString Livraison::getEtat() { return etat; }

float Livraison::getMontant() const { return montant; }

// Setters
void Livraison::setId(int id) { this->id = id; }

void Livraison::setDate(const QDateTime& date) { this->date = date; }

void Livraison::setAdresse(const QString& adresse) { this->adresse = adresse; }

void Livraison::setEtat(const QString& etat) { this->etat = etat; }

void Livraison::setMontant(float montant) { this->montant = montant; }

bool Livraison::ajouter() {
    QSqlQuery query;

    query.prepare("INSERT INTO LIVRAISON (ID_LIVRAISON, DATE_LIVRAISON, ADRESSE_LIVRAISON, ETAT_LIVRAISON, MONTANT_LIVRAISON) "
                  "VALUES (:id, :date, :adresse, :etat, :montant)");
    query.bindValue(":id", id);
    query.bindValue(":date", date);
    query.bindValue(":adresse", adresse);
    query.bindValue(":etat", etat);
    query.bindValue(":montant", montant);

    if (!query.exec()) {
        qDebug() << "Insertion failed: " << query.lastError().text();
        return false;
    }

    return true;
}

bool Livraison::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM LIVRAISON WHERE ID_LIVRAISON = :id");
    query.bindValue(":id", id);

    return query.exec();
}

// Method to display records in a table model
QSqlTableModel* Livraison::afficher() {
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("LIVRAISON");

    // Execute the query to load data
    if (!model->select()) {
        qDebug() << "Erreur lors de la sélection des données :" << model->lastError().text();
        return nullptr; // Return nullptr on error
    }

    // Check for empty data
    if (model->rowCount() == 0) {
        qDebug() << "Aucune donnée trouvée dans la table LIVRAISON.";
    }

    return model;
}
