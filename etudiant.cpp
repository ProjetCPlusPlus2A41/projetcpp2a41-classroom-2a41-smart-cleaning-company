#include "etudiant.h"

Etudiant::Etudiant(int id, QString nom, QString prenom)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
}

/*bool Etudiant::ajouter()
{
    QSqlQuery query;
    QString id_str = QString::number(id);
    query.prepare("INSERT INTO etudiants (id, nom, prenom) "
                  "VALUES (:id, :nom, :prenom)");
    query.bindValue(":id", id_str);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);

    if(!query.exec())
    {
        qDebug() << "Échec de l'ajout :" << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}*/
/*bool Etudiant::ajouter()
{
    QSqlQuery query;

    QString res = QString::number(id);

    query.prepare("INSERT INTO etudiants (id, nom, prenom) "
                  "VALUES (:id, :nom, :prenom)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);


    return query.exec(); // Retourne true si l'ajout a réussi
}*/
bool Etudiant::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO etudiants (id, nom, prenom) VALUES (:id, :nom, :prenom)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de l'étudiant : " << query.lastError().text();
        return false;
    }
    return true;
}

bool Etudiant::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("DELETE FROM etudiants WHERE id = :id");
    query.bindValue(":id", res);


        return query.exec();
}

QSqlQueryModel* Etudiant::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM etudiants");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));

    return model;
}
