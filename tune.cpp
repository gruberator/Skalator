#include <QFont>
#include <QDataStream>

#include "tune.h"

Tune::Tune(const QString& name, QVector<int> intervals, int numberOfFrets):
    rootNote(0)
{
    this->intervals = intervals;
    this->fretCount = numberOfFrets;
    this->name = name;
}

int Tune::getFretCount() const
{
    return fretCount;
}

void Tune::setFretCount(int fretCount)
{
    this->fretCount = fretCount;
}

int Tune::getStringNumber()
{
    return intervals.size();
}

QString Tune::getName() const
{
    return name;
}

void Tune::setName(const QString &value)
{
    name = value;
}

int Tune::getRootNote() const
{
    return rootNote;
}

void Tune::setRootNote(int value)
{
    rootNote = value;
}

QVector<int> Tune::getIntervals() const
{
    return intervals;
}

void Tune::setIntervals(const QVector<int> &value)
{
    intervals = value;
}

QDataStream &operator<<(QDataStream &out, const Tune &tune)
{
    out << tune.getName()
        << tune.getIntervals()
        << (quint32)tune.getRootNote()
        << tune.getFretCount();
    return out;
}

QDataStream &operator>>(QDataStream &in, Tune &tune)
{
    QString name;
    QVector<int> intervals;
    quint32 rootNote;
    quint32 fretCount;
    in >> name
            >> intervals
            >> rootNote
            >> fretCount;
    tune = Tune(name, intervals, fretCount);
    return in;
}

