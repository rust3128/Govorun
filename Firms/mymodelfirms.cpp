#include "mymodelfirms.h"

MyModelFirms::MyModelFirms()
{

}


QVariant MyModelFirms::data(const QModelIndex &idx, int role) const
{
    if(role == Qt::DisplayRole){
        if(idx.column()==4){
            if(QSqlTableModel::data(this->index(idx.row(),4)).toBool()){
                return "Да";
            } else {
                return "Нет";
            }
        }
    }

    if(role == Qt::TextAlignmentRole){
        if(idx.column() == 4)
            return Qt::AlignCenter;
    }


    return QSqlTableModel::data(idx,role);
}
