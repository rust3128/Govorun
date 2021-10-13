#ifndef AZSNETWORKMODEL_H
#define AZSNETWORKMODEL_H

#include <QSqlTableModel>
#include <QObject>

class AzsNetworkModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit AzsNetworkModel(QObject *parrent = nullptr);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // AZSNETWORKMODEL_H
