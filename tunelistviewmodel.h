#ifndef SKALATOR_TUNELISTVIEWMODEL_H
#define SKALATOR_TUNELISTVIEWMODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "tune.h"

class tuneListViewModel : public QAbstractListModel
{
public:
    tuneListViewModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void refresh() {emit dataChanged(index(0,0), index(0, tunings.size()));}
    QVector<Tune> getTunings() const;
    void setTunings(const QVector<Tune> &value);

private:
    QVector<Tune> tunings;
    void loadDefaultTunings();

};

#endif // SKALATOR_TUNELISTVIEWMODEL_H
