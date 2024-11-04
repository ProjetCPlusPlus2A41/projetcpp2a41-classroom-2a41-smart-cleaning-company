#ifndef LIVRAISON_H
#define LIVRAISON_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlTableModel> // Ensure this is included
#include <QDate>

class Livraison {
private:
    int id;
    QDateTime date;
    QString adresse;
    QString etat;
    float montant;

public:
    Livraison(); // Default constructor
    Livraison(int id, const QDateTime& date, const QString& adresse, const QString& etat, float montant); // Parameterized constructor

    // Getters
    int getId();
    QDateTime getDate() const;
    //QDate getDate();
    QString getAdresse();
    QString getEtat();
    //float getMontant();

    // Setters
    void setId(int id);
    void setDate(const QDateTime& date);
    void setAdresse(const QString& adresse);
    void setEtat(const QString& etat);
    void setMontant(float montant);


    float getMontant() const; // Déclarez la méthode comme 'const'

    // Database interaction methods
    bool ajouter();
    bool supprimer(int id);
    QSqlTableModel* afficher();

};

#endif // LIVRAISON_H
