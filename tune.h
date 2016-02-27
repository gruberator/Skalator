#ifndef SKALATOR_TUNE_H
#define SKALATOR_TUNE_H

#include <QVector>
#include <QString>

class QDataStream;

/**
 * @brief The Tune class
 *        Keeps tuning and fret count of given instrument.
 *        Each string tuning representation is sotred as intervals between each strings.
 *        First string interval is to root sound 0
 */
class Tune
{
public:
    Tune(){}
    Tune(const QString& name, QVector<int> intervals, int numberOfFrets = 25);

    int getFretCount() const;
    void setFretCount(int fretCount);
    int getStringNumber();
    void setStringNumber(int stringCount);
    QString getName() const;
    void setName(const QString &value);
    int getRootNote() const;
    void setRootNote(int value);
    QVector<int> getIntervals() const;
    void setIntervals(const QVector<int> &value);

private:
    QVector<int> intervals;
    int rootNote;
    int fretCount;
    QString name;
};

QDataStream &operator<<(QDataStream &out, const Tune &tune);
QDataStream &operator>>(QDataStream &in, Tune &tune);

#endif // SKALATOR_TUNE_H
