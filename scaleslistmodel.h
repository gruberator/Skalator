#ifndef SKALATOR_SCALESLISTMODEL_H
#define SKALATOR_SCALESLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "scale.h"

const static QColor DEFAULT_SCALE_COLOR(Qt::lightGray);
class ScalesListModel : public QAbstractListModel
{
public:
    ScalesListModel();
    void refresh() {emit dataChanged(index(0,0), index(0, scales.size()));}
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void loadScales();
    QVector<Scale> getScales() const;
private:
    QVector<Scale> scales;
    void loadDefaultScales();
};

#endif // SKALATOR_SCALESLISTMODEL_H
