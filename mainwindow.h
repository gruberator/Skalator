#ifndef SKALATOR_MAINWINDOW_H
#define SKALATOR_MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "scale.h"
#include "tune.h"
#include "scaleslistmodel.h"
#include "tunelistviewmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString extractIntervalsString(QVector<int> intervals);
private:

    QString parseFirstStringTillFirstNumber(QString someString);
    QVector<int> parseNumbersFromString(QString someString);
    Ui::MainWindow *ui;

    ScalesListModel scalesModel;
    tuneListViewModel tuneModel;

    Scale currentScale;
    Tune currentTune;

    int rootNote;

    int standardNotationTune;
    QVector<QString> standardNotationVals;
    /**
     * @brief initStandardNotation
     * @param usingIncrements, whether note is displayed like x#, if false then C# is Db
     */
    void initStandardNotation(bool usingIncrements = true);

    QColor newScaleColor;

protected slots:
    void parseScaleFromEditText(QString someString);
    void parseTuneIntervalsFromEditText(QString someString);
    void setScalePickedFromList(QModelIndex modelIndex);
    void setTunePickedFromList(QModelIndex modelIndex);

    void raiseTune();
    void dropTune();

    void addScale();
    void removeScale();

    void addTune();
    void removeTune();

    void raiseTuneStandardNotation();
    void dropTuneStandardNotation();

    void pickDisplayNotesType();

};

#endif // SKALATOR_MAINWINDOW_H
