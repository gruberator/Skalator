#ifndef SKALATOR_FRETBOARD_H
#define SKALATOR_FRETBOARD_H

#include <QWidget>
#include <QVector>
#include <QColor>
#include <QPixmap>
#include "tune.h"
#include "scale.h"
#include "scaleslistmodel.h"

class Fretboard : public QWidget
{
    Q_OBJECT
public:
    explicit Fretboard(QWidget *parent = 0);
    void setScale(const Scale &scale);
    void setTune(Tune &tune);
    void setRootNote(int rootNote);
    void setNotesAsTab(bool tab = true, int rootValue = 0);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *);

private:
    void scaleVector(int width, int height);
    void paintFretboard(QPainter &painter, int width);
    void paintScaleStep(QPainter &painter, QColor color, int idx, int width, int height, QString name);
    void paintScale(QPainter &painter, int width, int height);
    void paintMarkers(QPainter &painter, int width, int height);
    QColor pickColorForScaleStep(int scaleStep);
    QString getStandardNoteName(int index);

    QVector<QPointF> fretCoords;
    QVector<QString> standardNotationVals;
    QPixmap currentPixmap;
    QPixmap previousPixmap;

    int numberOfFrets;
    int numberOfString;
    int rootValueClassicalNotation;
    bool displayNotesAsTab;

    Scale scale;
    Tune  tune;
};

#endif // SKALATOR_FRETBOARD_H
