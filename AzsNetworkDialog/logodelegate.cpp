#include "logodelegate.h"

#include <QApplication>

LogoDelegate::LogoDelegate(QObject *parent) :QStyledItemDelegate (parent)
{

}


void LogoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &idx) const
{
       QPixmap pixmap;
       pixmap.loadFromData(idx.model()->data(idx,Qt::DisplayRole).toByteArray());

       painter->drawPixmap(option.rect, pixmap);

}
