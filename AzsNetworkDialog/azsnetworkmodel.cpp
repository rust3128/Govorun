#include "azsnetworkmodel.h"

#include <QPixmap>
#include <QSqlRecord>

AzsNetworkModel::AzsNetworkModel(QObject *parrent) : QSqlTableModel(parrent)
{

}


QVariant AzsNetworkModel::data(const QModelIndex &idx, int role) const
{


//    if (role==Qt::DecorationRole && idx.column() == 2) //12 - QByteArray [вне зависимости от нумерации столбца]
//    {
//        QPixmap pixmap;
//        pixmap.loadFromData(data(idx,Qt::DisplayRole).toByteArray());
//        return pixmap;
//    }



    return QSqlQueryModel::data(idx,role);
}
