#include "tunelistviewmodel.h"
#include "settingsmanager.h"

void tuneListViewModel::loadDefaultTunings()
{
    int fretCount = 25; // with 0 fret
    {
        QVector<int> intervals;
        QString name = "Standard E six strings";
        intervals.push_back(0);
        intervals.push_back(5);
        intervals.push_back(5);
        intervals.push_back(5);
        intervals.push_back(4);
        intervals.push_back(5);
        Tune tune(name, intervals, fretCount);
        tunings.push_back(tune);
    }
    {
        QVector<int> intervals;
        QString name = "Dropped D six strings";
        fretCount = 25;
        intervals.push_back(0);
        intervals.push_back(7);
        intervals.push_back(5);
        intervals.push_back(5);
        intervals.push_back(4);
        intervals.push_back(5);
        Tune tune(name, intervals, fretCount);
        tunings.push_back(tune);
    }
    {
        QVector<int> intervals;
        QString name = "Standard E seven strings";
        intervals.push_back(0);
        intervals.push_back(5);
        intervals.push_back(5);
        intervals.push_back(5);
        intervals.push_back(5);
        intervals.push_back(4);
        intervals.push_back(5);
        Tune tune(name, intervals, fretCount);
        tunings.push_back(tune);
    }
    {
        QVector<int> intervals;
        QString name = "Dropped D seven strings";
        fretCount = 25;
        intervals.push_back(0);
        intervals.push_back(7);
        intervals.push_back(5);
        intervals.push_back(5);
        intervals.push_back(5);
        intervals.push_back(4);
        intervals.push_back(5);
        Tune tune(name, intervals, fretCount);
        tunings.push_back(tune);
    }

    {
        //        c g d a e g
        //          0 7 7 7 7 3
        //          a 2 b 1 c 2 d 2 e 1 f 2 g 2 a...
        QVector<int> intervals;
        QString name = "New Standard Tuning six strings";
        fretCount = 25;
        intervals.push_back(0);
        intervals.push_back(7);
        intervals.push_back(7);
        intervals.push_back(7);
        intervals.push_back(7);
        intervals.push_back(3);
        Tune tune(name, intervals, fretCount);
        tunings.push_back(tune);
    }
    {
        QVector<int> intervals;
        QString name = "Banjo five strings"; // G D G B D
        fretCount = 25;
        intervals.push_back(0);
        intervals.push_back(7);
        intervals.push_back(5);
        intervals.push_back(4);
        intervals.push_back(3);
        Tune tune(name, intervals, fretCount);
        tunings.push_back(tune);
    }
}

tuneListViewModel::tuneListViewModel()
{
    // add custom tunes
    SettingsManager &am = SettingsManager::getInstance();
    loadDefaultTunings();
    QVector<Tune> customTunes = am.getTunes();
    for(int i = 0 ; i < customTunes.size() ; ++i) {
        tunings.push_back(customTunes[i]);
    }
}

int tuneListViewModel::rowCount(const QModelIndex &parent) const
{
    return tunings.size();
}

QVariant tuneListViewModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(role == Qt::DisplayRole) {
        if(row < tunings.size()) {
            QString value = tunings[row].getName() + "  ";
            QVector<int> tuningIntervals = tunings[row].getIntervals();
            int stringNumber = tuningIntervals.size();
            for(int i = 0 ; i < stringNumber ; ++i) {
                int intervalValue = tuningIntervals[i];
                value += QString::number(intervalValue) + ",";
            }
            return value;
        }
    }
    return QVariant();
}

QVector<Tune> tuneListViewModel::getTunings() const
{
    return tunings;
}

void tuneListViewModel::setTunings(const QVector<Tune> &value)
{
    tunings = value;
}
