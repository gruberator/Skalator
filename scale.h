#ifndef SKALATOR_SCALE_H
#define SKALATOR_SCALE_H
#include <QVector>
#include <QString>
#include <QColor>

class QDataStream;

/**
 * @brief The Scale class
 *  Describes music scale as collection of intervals in single octave.
 *  All intervals included in scale are described by number of half tones from 0.
 *  It has a name and a color that will be used to display this scale.
 *
 */
class Scale
{
public:
    Scale(const QString &scaleName, const QVector<int> &intervalsFromRoot, const QColor &color);
    Scale();

    QVector<int> getIntervalsFromRootInSemitones() const;
    void setIntervalsFromRootInSemitones(const QVector<int> &value);
    QColor getColor() const;
    void setColor(const QColor &value);
    QString getNameWithIntervals() const;
    QString getName() const;
    void setName(const QString &value);

private:
    QString name;
    QColor color;
    QVector<int> intervalsFromRootInSemitones;
};

QDataStream &operator<<(QDataStream &out, const Scale &scale);
QDataStream &operator>>(QDataStream &in, Scale &scale);


#endif // SKALATOR_SCALE_H
