#include <QDataStream>

#include "scale.h"

Scale::Scale(const QString &scaleName, const QVector<int> &intervalsFromRoot, const QColor &color)
{
    this->name = scaleName;
    this->color = color;
    if(&intervalsFromRoot != NULL) {
        intervalsFromRootInSemitones = intervalsFromRoot;
    }
}

Scale::Scale()
{
    // create single note scale
    intervalsFromRootInSemitones.push_back(0);
    name = "Octave";
    color = Qt::white;
}

QString Scale::getName() const
{
    return name;
}

QString Scale::getNameWithIntervals() const
{
    QString str = name;
    for(int i = 0 ; i < intervalsFromRootInSemitones.size() ; ++i){
        str += " " + QString::number(intervalsFromRootInSemitones[i]);
    }
    return str;
}

void Scale::setName(const QString &value)
{
    name = value;
}

QColor Scale::getColor() const
{
    return color;
}

void Scale::setColor(const QColor &value)
{
    color = value;
}

QVector<int> Scale::getIntervalsFromRootInSemitones() const
{
    return intervalsFromRootInSemitones;
}

void Scale::setIntervalsFromRootInSemitones(const QVector<int> &value)
{
    intervalsFromRootInSemitones = value;
}


QDataStream &operator<<(QDataStream &out, const Scale &scale)
{
    out << scale.getName()
        << scale.getIntervalsFromRootInSemitones()
        << scale.getColor();
    return out;
}


QDataStream &operator>>(QDataStream &in, Scale &scale)
{
    QString name;
    QVector<int> intervals;
    QColor color;
    in >> name
            >> intervals
            >> color;
    scale = Scale(name, intervals, color);
    return in;
}
