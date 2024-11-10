#include "service.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>

Service::Service()
    : id(0), type(""), date(QDate::currentDate()), etat(""), description("") {
    // Constructeur par défaut avec initialisation
}

int Service::getId() const {
    return id;
}

Service::Service(int id, QString type, QDate date, QString etat, QString description)
    : id(id), type(type), date(date), etat(etat), description(description) {
    // Constructeur avec paramètres
}

bool Service::ajouter() {
    QSqlQuery query;

    query.prepare("INSERT INTO SERVICES (ID_SERVICE, TYPE_SERVICE, DATE_SERVICE, ETAT_SERVICE, DESCRIPTION_SERVICE) "
                  "VALUES (:id, :type, :date, :etat, :description)");

    query.bindValue(":id", id);
    query.bindValue(":type", type);
    query.bindValue(":date", date);
    query.bindValue(":etat", etat);
    query.bindValue(":description", description);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout du service :" << query.lastError().text();
        return false;
    }
}

bool Service::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM SERVICES WHERE ID_SERVICE = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlTableModel* Service::afficher() {
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("SERVICES");  // Remplacez "services" par le nom de votre table
    model->select();  // Charge les données de la table
    return model;
}

bool Service::modifier(int id, const QString& type, const QDateTime& date, const QString& etat, const QString& description)
{
    // Créez une requête SQL pour vérifier si l'id existe
    QSqlQuery query;
    query.prepare("SELECT * FROM SERVICES WHERE ID_SERVICE = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche de l'id:" << query.lastError();
        return false;
    }

    // Si l'id existe, effectuez la mise à jour
    if (query.next()) {
        query.prepare("UPDATE SERVICES SET TYPE_SERVICE = :type, DATE_SERVICE = :date, ETAT_SERVICE = :etat, DESCRIPTION_SERVICE = :description WHERE ID_SERVICE = :id");
        query.bindValue(":id", id);
        query.bindValue(":type", type);
        query.bindValue(":date", date);
        query.bindValue(":etat", etat);
        query.bindValue(":description", description);

        if (!query.exec()) {
            qDebug() << "Erreur lors de la mise à jour:" << query.lastError();
            return false;
        }

        return true;  // Mise à jour réussie
    }

    return false;  // L'id n'a pas été trouvé
}

