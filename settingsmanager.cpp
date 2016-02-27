#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QDataStream>

#include "settingsmanager.h"

const static QString SCALES_INTERVALS = "ScalesIntervals";
const static QString TUNES_INTERVALS = "TunesIntervals";

const QString settingsFileName = "skalator_user_data";

void SettingsManager::addCustomScale(Scale &scale)
{
    customScales.push_back(scale);
    saveAssets();
}

void SettingsManager::removeCustomScale(const QString &name)
{
    int customScalesSize = customScales.size();
    for(int i = 0 ; i < customScalesSize ; ++i) {
        if(customScales[i].getName() == name) {
            customScales.remove(i);
            break;
        }
    }
    saveAssets();
}

void SettingsManager::addCustomTune(Tune &tune)
{
    customTunes.push_back(tune);
    saveAssets();
}

void SettingsManager::removeCustomTune(const QString &name)
{
    int customTunesSize = customTunes.size();
    for(int i = 0 ; i < customTunesSize ; ++i) {
        if(customTunes[i].getName() == name) {
            customTunes.remove(i);
            break;
        }
    }
    saveAssets();
}

void SettingsManager::setRootNote(int rootNote) {
    this->rootNote = rootNote; saveAssets();
}

void SettingsManager::setZeroFretStandardName(int zeroFretStandardName){
    this->zeroFretStandardName = zeroFretStandardName; saveAssets();
}

void SettingsManager::setShowNumbersInsteadStandardNotation(bool numbersOn){
    showNumberInsteadOfStandardNotation = numbersOn; saveAssets();
}

void SettingsManager::setCurrentScale(Scale scale){
    currentScale = scale; saveAssets();
}

Tune SettingsManager::getCurrentTune(){
    return currentTune;
}

void SettingsManager::setCurrentTune(Tune tune){
    currentTune = tune; saveAssets();
}

void SettingsManager::loadAssets()
{
    QFile file(settingsFileName);
    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            qint32 scaleSize;
            qint32 tunesSize;
            QString scalesNumberString;
            QString tunesNumberString;

            in >> scalesNumberString >> scaleSize >> tunesNumberString >> tunesSize;
            if(scalesNumberString == SCALES_INTERVALS) {
                for(int i = 0 ; i < scaleSize ; ++i) {
                    Scale scale;
                    in >> scale;
                    customScales.push_back(scale);
                }
            }
            if(tunesNumberString == TUNES_INTERVALS) {
                for(int i = 0 ; i < tunesSize ; ++i) {
                    Tune tune;
                    in >> tune;
                    customTunes.push_back(tune);
                }
            }
            in >> rootNote;
            in >> zeroFretStandardName;
            in >> showNumberInsteadOfStandardNotation;
            in >> currentScale;
            in >> currentTune;
        }
        file.close();
    } else {
        rootNote = 0;
        zeroFretStandardName = 7; // E
        showNumberInsteadOfStandardNotation = true;
        saveAssets();
    }
}

void SettingsManager::saveAssets()
{
    QFile file(settingsFileName);
    if(file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        quint32 nb = 0;
        int scalesSize = customScales.size();
        int tuneSize = customTunes.size();
        out << SCALES_INTERVALS << (quint32) scalesSize << TUNES_INTERVALS << (quint32) tuneSize;
        if(scalesSize > 0) {
            for(int i = 0 ; i < scalesSize ; ++i)
                out << customScales[i];
        }
        if(tuneSize > 0) {
            for(int i = 0 ; i < tuneSize ; ++i)
                out << customTunes[i];
        }
        out << (quint32) rootNote;
        out << (quint32) zeroFretStandardName;
        out << showNumberInsteadOfStandardNotation;
        out << currentScale;
        out << currentTune;
    }
    file.close();
}

