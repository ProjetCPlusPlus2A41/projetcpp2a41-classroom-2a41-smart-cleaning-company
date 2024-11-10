#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>

employe::employe()
    : id(0), nom(""), prenom(""), poste(""),email("") {
    // Constructeur par défaut avec initialisation
}

int employe::getId() const {
    return id;
}

employe::employe(int id, QString nom, QString prenom, QString poste, QString email)
    : id(id), nom(nom), prenom(prenom), poste(poste), email(email) {
    // Constructeur avec paramètres
}

bool employe::ajouter() {
    QSqlQuery query;

    query.prepare("INSERT INTO EMPLOYES (ID_EMPLOYE, NOM_EMPLOYE, PRENOM_EMPLOYE, POSTE_EMPLOYE, EMAIL_EMPLOYE) "
                  "VALUES (:id, :nom, :prenom, :poste, :email)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":email", email);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout du service :" << query.lastError().text();
        return false;
    }
}

bool employe::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlTableModel* employe::afficher() {
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("EMPLOYES");
    model->select();  // Charge les données de la table
    return model;
}

bool employe::modifier(int id, const QString& nom, const QString& prenom, const QString& poste, const QString& email)
{
    // Créez une requête SQL pour vérifier si l'id existe
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche de l'id:" << query.lastError();
        return false;
    }

    // Si l'id existe, effectuez la mise à jour
    if (query.next()) {
        query.prepare("UPDATE EMPLOYES SET NOM_EMPLOYE = :nom, PRENOM_EMPLOYE = :prenom, POSTE_EMPLOYE = :poste, EMAIL_EMPLOYE = :email WHERE ID_EMPLOYE = :id");
        query.bindValue(":id", id);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":poste", poste);
        query.bindValue(":email", email);

        if (!query.exec()) {
            qDebug() << "Erreur lors de la mise à jour:" << query.lastError();
            return false;
        }

        return true;  // Mise à jour réussie
    }

    return false;  // L'id n'a pas été trouvé
}
