#ifndef MYMODELFIRMS_H
#define MYMODELFIRMS_H

#include <QSqlTableModel>
#include <QObject>

class MyModelFirms : public QSqlTableModel
{
    Q_OBJECT
public:
    MyModelFirms();

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // MYMODELFIRMS_H
