#include <stdio.h>
#include <QModelIndex>
#include <QColorDialog>
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include "settingsmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->editScale, SIGNAL(textChanged(QString)), this, SLOT(parseScaleFromEditText(QString)));
    connect(ui->editTuneIntervals, SIGNAL(textChanged(QString)), this, SLOT(parseTuneIntervalsFromEditText(QString)));

    ui->scaleView->setModel(&scalesModel);
    connect(ui->scaleView, SIGNAL(clicked(QModelIndex)), this, SLOT(setScalePickedFromList(QModelIndex)));

    ui->tuneView->setModel(&tuneModel);
    connect(ui->tuneView, SIGNAL(clicked(QModelIndex)), this, SLOT(setTunePickedFromList(QModelIndex)));

    ui->editTuneRoot->setText(QString::number(0));
    connect(ui->buttonRaiseTune, SIGNAL(clicked()), this, SLOT(raiseTune()));
    connect(ui->buttonDropTune, SIGNAL(clicked()), this, SLOT(dropTune()));

    connect(ui->buttonAddScale, SIGNAL(clicked()), this, SLOT(addScale()));
    connect(ui->buttonRemoveScale, SIGNAL(clicked()), this, SLOT(removeScale()));
    connect(ui->buttonAddTune, SIGNAL(clicked()), this, SLOT(addTune()));
    connect(ui->buttonRemoveTune, SIGNAL(clicked()), this, SLOT(removeTune()));

    connect(ui->buttonDropRootTone, SIGNAL(clicked()), this, SLOT(dropTuneStandardNotation()));
    connect(ui->buttonRiseRootTone, SIGNAL(clicked()), this, SLOT(raiseTuneStandardNotation()));

    connect(ui->checkBoxTabulature, SIGNAL(clicked()), this, SLOT(pickDisplayNotesType()));

    // perseverance
    SettingsManager &settingsManager = SettingsManager::getInstance();

    standardNotationTune = settingsManager.getZeroFretStandardName();
    rootNote = settingsManager.getRootNote();
    ui->checkBoxTabulature->setChecked(settingsManager.getShowNumbersInsteadStandardNotation());

    initStandardNotation(true);

    ui->editTuneRootStandardName->setText(standardNotationVals[standardNotationTune]);
    ui->myFretboard->setNotesAsTab(ui->checkBoxTabulature->isChecked(), standardNotationTune);

    //workaround the fact that rootNote is loaded but it is not refreshed, nasty but will work
    dropTune();
    raiseTune();
    newScaleColor = Qt::white;
    currentScale = settingsManager.getCurrentScale();
    currentTune = settingsManager.getCurrentTune();

    if(currentTune.getIntervals().size() == 0){
        if(tuneModel.getTunings().size()>0){
            // get first tune from tune model
            currentTune = tuneModel.getTunings()[0];
        }
    }
    ui->editScale->setText(currentScale.getNameWithIntervals());
    ui->myFretboard->setScale(currentScale);
    ui->myFretboard->setTune(currentTune);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::parseFirstStringTillFirstNumber(QString someString)
{
    int size = someString.size();
    QString name;
    for(int i = 0 ; i < size ; ++i ) {
        QChar c = someString.at(i);
        if(c < '0' || c > '9') {
            name.push_back(c);
        } else {
            break;
        }
    }
    return name.trimmed();
}

QVector<int> MainWindow::parseNumbersFromString(QString someString)
{
    QVector<int> parsedIntervals;
    QString number;
    number.clear();
    for(int i = 0 ; i < someString.size() ; ++i ) {

        QChar c = someString.at(i);
        if(c <= '9' && c >= '0') {
            //add digit to string
            number.push_back(c);
        } else {
            //no digit so try to parse digit from number string
            if(number.size()>0) {
                bool ok;
                int interval = number.toInt(&ok);
                if(ok) {
                    parsedIntervals.push_back(interval);
                    number.clear();
                }
            }
        }
        // if this is a last character of the text, then parse what we have in acumulator
        if(i+1 == someString.size()) {
            if(number.size()>0) {
                bool ok;
                int interval = number.toInt(&ok);
                if(ok) {
                    parsedIntervals.push_back(interval);
                }
            }
        }
    }
    return parsedIntervals;
}

void MainWindow::initStandardNotation(bool usingIncrements)
{
    if(usingIncrements) {
        standardNotationVals.push_back("A");
        standardNotationVals.push_back("A#");
        standardNotationVals.push_back("B");
        standardNotationVals.push_back("C");
        standardNotationVals.push_back("C#");
        standardNotationVals.push_back("D");
        standardNotationVals.push_back("D#");
        standardNotationVals.push_back("E");
        standardNotationVals.push_back("F");
        standardNotationVals.push_back("F#");
        standardNotationVals.push_back("G");
        standardNotationVals.push_back("G#");
    } else {
        standardNotationVals.push_back("A");
        standardNotationVals.push_back("Bb");
        standardNotationVals.push_back("B");
        standardNotationVals.push_back("C");
        standardNotationVals.push_back("Db");
        standardNotationVals.push_back("D");
        standardNotationVals.push_back("Eb");
        standardNotationVals.push_back("E");
        standardNotationVals.push_back("F");
        standardNotationVals.push_back("Gb");
        standardNotationVals.push_back("G");
        standardNotationVals.push_back("Ab");
    }
}

void MainWindow::parseScaleFromEditText(QString someString)
{
    QString name = parseFirstStringTillFirstNumber(someString);
    QVector<int> ret = parseNumbersFromString(someString);
    QSet<int> added;
    QVector<int> scaleIntervals;
    for(int i = 0 ; i < ret.size() ; ++i) {
        int interval = ret[i] % 12;
        if(!added.contains(interval)){
            scaleIntervals.push_back(interval);
            added.insert(interval);
        }
    }
    if(scaleIntervals.size()>0) {
        currentScale.setIntervalsFromRootInSemitones(scaleIntervals);
        currentScale.setName(name);
        currentScale.setColor(newScaleColor);
        SettingsManager &am = SettingsManager::getInstance();
        am.setCurrentScale(currentScale);
        ui->myFretboard->setScale(currentScale);
    }

}

void MainWindow::parseTuneIntervalsFromEditText(QString someString)
{
    QString name = parseFirstStringTillFirstNumber(someString);
    QVector<int> tuneIntervals = parseNumbersFromString(someString);
    for(int i = 0 ; i < tuneIntervals.size() ; ++i) {
        tuneIntervals[i] = tuneIntervals[i] % 12;
    }
    if(tuneIntervals.size()>0) {
        currentTune.setIntervals(tuneIntervals);
        currentTune.setName(name);
        ui->myFretboard->setTune(currentTune);
    }
}

void MainWindow::setScalePickedFromList(QModelIndex modelIndex)
{
    int scaleNumber = modelIndex.row();
    if(scaleNumber < scalesModel.getScales().size()) {
        SettingsManager &am = SettingsManager::getInstance();
        am.setCurrentScale(scalesModel.getScales()[scaleNumber]);
        ui->myFretboard->setScale(scalesModel.getScales()[scaleNumber]);
        QVector<int> intervals = scalesModel.getScales()[scaleNumber].getIntervalsFromRootInSemitones();
        ui->editScale->setText(scalesModel.getScales()[scaleNumber].getName() + " " + extractIntervalsString(intervals));
    }
}

QString MainWindow::extractIntervalsString(QVector<int> intervals)
{
    QString numbers;
    for(int i = 0 ; i < intervals.size() ; ++i) {
        int n = intervals[i];
        QString interval = QString::number(n);
        numbers.push_back(interval + " ");
    }
    return numbers;
}



void MainWindow::setTunePickedFromList(QModelIndex modelIndex)
{
    int tuneNumber = modelIndex.row();
    if(tuneNumber < tuneModel.getTunings().size()) {
        SettingsManager &am = SettingsManager::getInstance();
        am.setCurrentTune(tuneModel.getTunings()[tuneNumber]);
        ui->myFretboard->setTune(tuneModel.getTunings()[tuneNumber]);
        QVector<int> intervals = tuneModel.getTunings()[tuneNumber].getIntervals();
        ui->editTuneIntervals->setText( tuneModel.getTunings()[tuneNumber].getName() + " " + extractIntervalsString(intervals));
    }
}

void MainWindow::raiseTune()
{
    ++rootNote;
    rootNote %= 12;
    SettingsManager &am = SettingsManager::getInstance();
    am.setRootNote(rootNote);
    ui->editTuneRoot->setText(QString::number(rootNote));
    ui->myFretboard->setRootNote(rootNote);

}

void MainWindow::dropTune()
{
    --rootNote;
    while(rootNote<0) rootNote += 12;
    rootNote %= 12;
    SettingsManager &am = SettingsManager::getInstance();
    am.setRootNote(rootNote);
    ui->editTuneRoot->setText(QString::number(rootNote));
    ui->myFretboard->setRootNote(rootNote);
}

void MainWindow::addScale()
{
    SettingsManager &am = SettingsManager::getInstance();
    currentScale.setColor(newScaleColor);
    am.addCustomScale(currentScale);
    scalesModel.getScales().push_back(currentScale);
    scalesModel.refresh();
}

void MainWindow::removeScale()
{
    SettingsManager &am = SettingsManager::getInstance();
    am.removeCustomScale(currentScale.getName());
    scalesModel.loadScales(); // method is invoking assets manager to assist load
}

void MainWindow::addTune()
{
    SettingsManager &am = SettingsManager::getInstance();
    am.addCustomTune(currentTune);
    tuneModel.getTunings().push_back(currentTune);
    tuneModel.refresh();
}

void MainWindow::removeTune()
{
    SettingsManager &am = SettingsManager::getInstance();
    am.removeCustomTune(currentTune.getName());
    for(int i = 0 ; i < tuneModel.getTunings().size() ; ++i) {
        if(tuneModel.getTunings()[i].getName() == currentTune.getName()){
            tuneModel.getTunings().remove(i);
            tuneModel.refresh();
            break;
        }
    }
}

void MainWindow::raiseTuneStandardNotation()
{
    ++standardNotationTune;
    standardNotationTune %= 12;
    ui->editTuneRootStandardName->setText(standardNotationVals[standardNotationTune]);
    SettingsManager &am = SettingsManager::getInstance();
    am.setZeroFretStandardName(standardNotationTune);
    pickDisplayNotesType();
}

void MainWindow::dropTuneStandardNotation()
{
    if(standardNotationTune <= 0) {
        standardNotationTune = 11;
    } else {
        --standardNotationTune;
    }
    ui->editTuneRootStandardName->setText(standardNotationVals[standardNotationTune]);
    SettingsManager &am = SettingsManager::getInstance();
    am.setZeroFretStandardName(standardNotationTune);
    pickDisplayNotesType();
}

void MainWindow::pickDisplayNotesType()
{
    SettingsManager &am = SettingsManager::getInstance();
    am.setShowNumbersInsteadStandardNotation(ui->checkBoxTabulature->isChecked());
    if(ui->checkBoxTabulature->isChecked()) {
        ui->myFretboard->setNotesAsTab(true, standardNotationTune);
    } else {
        ui->myFretboard->setNotesAsTab(false, standardNotationTune);
    }
}

