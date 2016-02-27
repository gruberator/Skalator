#ifndef SKALATOR_SETTINGSMANAGER_H
#define SKALATOR_SETTINGSMANAGER_H

#include "scale.h"
#include "tune.h"

/**
 * @brief The SettingsManager class
 * SettingsManager is perserverance class to save state of scales, tunes and settings of the ui interface.
 *
 */
class SettingsManager
{
public:
    static SettingsManager& getInstance() {
        static SettingsManager instance;
        return instance;
    }

    void addCustomScale(Scale &scale);
    void removeCustomScale(const QString &name);

    void addCustomTune(Tune &tune);
    void removeCustomTune(const QString &name);

    QVector<Tune>& getTunes(void) { return customTunes; }
    QVector<Scale>& getScales(void) {return customScales; }

    void setRootNote(int rootNote);
    int getRootNote() { return rootNote; }

    void setZeroFretStandardName(int zeroFretStandardName);
    int getZeroFretStandardName() { return zeroFretStandardName; }

    bool getShowNumbersInsteadStandardNotation() { return showNumberInsteadOfStandardNotation; }
    void setShowNumbersInsteadStandardNotation(bool numbersOn);

    Scale getCurrentScale(){ return currentScale; }
    void setCurrentScale(Scale scale);
    Scale currentScale;

    Tune getCurrentTune();
    void setCurrentTune(Tune tune);
    Tune currentTune;

    void loadAssets();
private:
    SettingsManager() { loadAssets(); }
    SettingsManager(SettingsManager const&);
    void operator=(SettingsManager const&);

    static SettingsManager instace;

    void saveAssets();

    QVector<Tune> customTunes;
    QVector<Scale> customScales;

    int rootNote;
    int zeroFretStandardName; // A - 0 Bb - 1 etc
    bool showNumberInsteadOfStandardNotation;

};

#endif // SKALATOR_SETTINGSMANAGER_H
