#ifndef SERVICE_H
#define SERVICE_H

#include <QString>
#include <QDate>
#include <QSqlTableModel>

class Service {
public:
    Service();
    Service(int id, QString type, QDate date, QString etat, QString description);

    bool ajouter();
    bool supprimer(int id);
    QSqlTableModel* afficher();
    bool modifier(int id, const QString& type, const QDateTime& date, const QString& etat, const QString& description);
    int getId() const;

private:
    int id;
    QString type;
    QDate date;
    QString etat;
    QString description;
};

#endif // SERVICE_H
