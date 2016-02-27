#include <QBrush>
#include <QModelIndex>

#include "scaleslistmodel.h"
#include "settingsmanager.h"

ScalesListModel::ScalesListModel()
{
    loadScales();
}

int ScalesListModel::rowCount(const QModelIndex &parent) const
{
    return scales.size();
}

QVariant ScalesListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < scales.size()) {
        if(role == Qt::DisplayRole) {
            QString value = scales[index.row()].getName()+ "  ";
            int intervalsCount = scales[index.row()].getIntervalsFromRootInSemitones().size();
            for(int i = 0 ; i < intervalsCount ; ++i) {
                int intervalValue = scales[index.row()].getIntervalsFromRootInSemitones()[i];
                value += QString::number(intervalValue) + ",";
            }
            return value;
        } else if(role == Qt::BackgroundRole) {
            QBrush background_brush(QColor(scales[index.row()].getColor()));
            return background_brush;
        }
    }
    return QVariant();
}

void ScalesListModel::loadScales()
{
    scales.clear();
    loadDefaultScales();
    // add custom scales
    SettingsManager &am = SettingsManager::getInstance();
    QVector<Scale> customScales = am.getScales();
    for(int i = 0 ; i < customScales.size() ; ++i) {
        scales.push_back(customScales[i]);
    }
}

QVector<Scale> ScalesListModel::getScales() const
{
    return scales;
}

void ScalesListModel::loadDefaultScales()
{
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(2);
        intervals.push_back(3);
        intervals.push_back(5);
        intervals.push_back(7);
        intervals.push_back(8);
        intervals.push_back(10);
        Scale scale("Aeolian", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(2);
        intervals.push_back(3);
        intervals.push_back(5);
        intervals.push_back(7);
        intervals.push_back(8);
        intervals.push_back(11);
        Scale scale("Harmonic minor", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(1);
        intervals.push_back(3);
        intervals.push_back(5);
        intervals.push_back(6);
        intervals.push_back(8);
        intervals.push_back(10);
        Scale scale("Locrian", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(2);
        intervals.push_back(4);
        intervals.push_back(5);
        intervals.push_back(7);
        intervals.push_back(9);
        intervals.push_back(11);
        Scale scale("Ionian", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(2);
        intervals.push_back(3);
        intervals.push_back(5);
        intervals.push_back(7);
        intervals.push_back(9);
        intervals.push_back(10);
        Scale scale("Dorian", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(1);
        intervals.push_back(3);
        intervals.push_back(5);
        intervals.push_back(7);
        intervals.push_back(8);
        intervals.push_back(10);
        Scale scale("Phrygian", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(1);
        intervals.push_back(4);
        intervals.push_back(5);
        intervals.push_back(7);
        intervals.push_back(8);
        intervals.push_back(10);
        Scale scale("Phrygian harmonic", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(2);
        intervals.push_back(4);
        intervals.push_back(6);
        intervals.push_back(7);
        intervals.push_back(9);
        intervals.push_back(11);
        Scale scale("Lydian", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(2);
        intervals.push_back(4);
        intervals.push_back(5);
        intervals.push_back(7);
        intervals.push_back(9);
        intervals.push_back(10);
        Scale scale("Mixolydian", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(2);
        intervals.push_back(4);
        intervals.push_back(6);
        intervals.push_back(8);
        intervals.push_back(10);
        Scale scale("Whole Tone", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(3);
        intervals.push_back(6);
        intervals.push_back(9);
        Scale scale("Half Diminished", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(1);
        intervals.push_back(3);
        intervals.push_back(4);
        intervals.push_back(6);
        intervals.push_back(7);
        intervals.push_back(9);
        intervals.push_back(10);
        Scale scale("Full Diminished", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(3);
        intervals.push_back(4);
        intervals.push_back(7);
        intervals.push_back(8);
        intervals.push_back(11);
        Scale scale("Augumented scale", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(3);
        intervals.push_back(5);
        intervals.push_back(7);
        intervals.push_back(10);
        Scale scale("minor pentatonic", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(2);
        intervals.push_back(4);
        intervals.push_back(7);
        intervals.push_back(9);
        Scale scale("MAJOR Pentatonic", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(3);
        intervals.push_back(7);
        Scale scale("mol Arpeggio", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
    {
        QVector<int> intervals;
        intervals.push_back(0);
        intervals.push_back(4);
        intervals.push_back(7);
        Scale scale("MAJor Arpeggio", intervals, DEFAULT_SCALE_COLOR);
        scales.push_back(scale);
    }
}
