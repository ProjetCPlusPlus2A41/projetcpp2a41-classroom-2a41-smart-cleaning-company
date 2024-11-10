#ifndef SERVICE_H
#define SERVICE_H

#include <QString>
#include <QDate>
#include <QSqlTableModel>

class employe {
public:
    employe();
    employe(int id, QString nom, QString prenom, QString poste, QString email);

    bool ajouter();
    bool supprimer(int id);
    QSqlTableModel* afficher();
    bool modifier(int id, const QString& nom, const QString& prenom, const QString& poste, const QString& email);
    int getId() const; // Ajout de la méthode d'accès

private:
    int id;
    QString nom;
    QString prenom;
    QString poste;
    QString email;
};

#endif // SERVICE_H
