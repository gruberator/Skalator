#include <QPainter>
#include <QPointF>
#include <QBrush>
#include <QPen>
#include <QSize>
#include <QDebug>
#include <QFont>

#include "fretboard.h"

Fretboard::Fretboard(QWidget *parent) :
    QWidget(parent),
    numberOfFrets(25),
    numberOfString(6),
    displayNotesAsTab(true)
{
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
}

void Fretboard::setScale(const Scale &scale)
{
    this->scale = scale;
    repaint();
}

void Fretboard::setNotesAsTab(bool tab, int rootValue)
{
    displayNotesAsTab = tab;
    rootValueClassicalNotation = rootValue;
    repaint();
}

void Fretboard::setTune(Tune &tune)
{
    numberOfFrets = tune.getFretCount();
    numberOfString = tune.getStringNumber();
    this->tune = tune;
    repaint();
}

void Fretboard::setRootNote(int rootNote)
{
    tune.setRootNote(rootNote);
    repaint();
}

void Fretboard::paintScale(QPainter &painter, int width, int height)
{
    if(scale.getIntervalsFromRootInSemitones().size() > 0
            && tune.getIntervals().size() > 0) {
        int intervalCount = scale.getIntervalsFromRootInSemitones().size();

        for(int intervalNumber = 0 ; intervalNumber < intervalCount ; ++intervalNumber) {

            // step value is the value on the thickest string, in tabulature way
            int noteValue = scale.getIntervalsFromRootInSemitones()[intervalNumber] + tune.getRootNote();

            // Intervals between strings, e.g. standard tuning on 6th strings would be: 0 5 5 5 4 5
            QVector<int> tuneIntervals = tune.getIntervals();
            // stringInvervalAcumulator gives total interval from 0 on thickest (eg 0 E6)
            int stringIntervalAcumulator = 0;

            QColor color = pickColorForScaleStep(intervalNumber);
            for(int stringNb = 0 ; stringNb < numberOfString ; ++stringNb) {
                stringIntervalAcumulator += tuneIntervals[stringNb];
                // in order to find same sound on different string substract acumulator from 12 and add noteValue, this will be note on the current string

                int noteOnStringValue = (noteValue + (12000 - stringIntervalAcumulator))%12;

                while(noteOnStringValue < numberOfFrets) {
                    int addressOfTheFret = stringNb * numberOfFrets + noteOnStringValue;
                    noteOnStringValue += 12;
                    paintScaleStep(painter, color, addressOfTheFret, width, height, getStandardNoteName(noteValue));
                }
            }
        }
    }
}

QColor Fretboard::pickColorForScaleStep(int scaleStep) {
    switch(scaleStep) {
    case 0:
        return QColor(Qt::red);
        break;
    case 1:
        return QColor(Qt::darkYellow);
        break;
    case 2:
        return QColor(Qt::yellow);
        break;
    case 3:
        return QColor(Qt::green);
        break;
    case 4:
        return QColor(Qt::darkGreen);
        break;
    case 5:
        return QColor(Qt::blue);
        break;
    case 6:
        return QColor(Qt::gray);
        break;
    case 7:
        return QColor(Qt::darkMagenta);
        break;
    case 8:
        return QColor(Qt::darkGray);
        break;
    case 9:
        return QColor(Qt::cyan);
        break;
    case 10:
        return QColor(Qt::darkCyan);
        break;
    case 11:
        return QColor(Qt::white);
        break;
    }
    return QColor(Qt::white);
}

QString Fretboard::getStandardNoteName(int index)
{
    int i = (index + rootValueClassicalNotation) % 12;
    while(i<0) i+=12;
    return standardNotationVals[i];
}

void Fretboard::paintEvent(QPaintEvent *event)
{
    QPainter painterToScreen(this);
    currentPixmap = previousPixmap;
    QPainter painter(&currentPixmap);
    QBrush brush(QColor(255,255,0, 255));
    QPen pen(brush, 2.0);
    painter.setBrush(brush);
    painter.setPen(pen);

    QBrush backgroundBrush(QColor(0,0,0,255));
    painter.setBackground(backgroundBrush);
    int fretboardWidth = width();
    int fretboardHeight = 145 + width()/8;
    scaleVector(fretboardWidth, fretboardHeight);

    paintFretboard(painter, fretboardWidth);
    paintMarkers(painter, fretboardWidth, fretboardHeight);
    paintScale(painter, fretboardWidth, fretboardHeight);

    // draw framebuffer
    painterToScreen.drawPixmap( 0, 0, currentPixmap);
}

void Fretboard::resizeEvent(QResizeEvent *)
{
    previousPixmap = QPixmap(size());
}

void Fretboard::scaleVector(int width, int height)
{
    const float FRETWIDTH = (float) width / (float) numberOfFrets;
    const float FRETHEIGHT = (float) height / (float) numberOfString;

    fretCoords.clear();
    for (int i = 0; i < numberOfString; ++i)
    {
        for (int j = 0; j < numberOfFrets; ++j)
        {
            float cordX = j * FRETWIDTH;
            float cordY = height - i * FRETHEIGHT;
            fretCoords.push_back(QPointF(cordX,cordY));
        }
    }
    
}

void Fretboard::paintFretboard(QPainter &painter, int width)
{
    QBrush brush(QColor(255,255,0, 255));
    QPen pen(brush, 2.0);
    painter.setPen(pen);

    for (int i = 0; i < numberOfFrets; ++i)
        painter.drawLine(fretCoords[i],
                         QPointF(fretCoords[i].x(),0));
    for (int i = 0; i < numberOfString; ++i)
        painter.drawLine(QPointF(0,fretCoords[i * numberOfFrets].y()),
                QPointF(width, fretCoords[i * numberOfFrets].y()) );

}

void Fretboard::paintMarkers(QPainter &painter, int width, int height)
{
    const float fretWidth = (float) width / (float) numberOfFrets;
    int ellipseY = 8;
    int ellipseX = 5;
    QBrush brush(QColor(255,255,255,255));
    painter.setBrush(brush);
    painter.drawEllipse(QPointF(fretCoords[3].x() + fretWidth/2, (float) height / 2.0),ellipseX,ellipseY);
    painter.drawEllipse(QPointF(fretCoords[5].x() + fretWidth/2, (float) height / 2.0),ellipseX,ellipseY);
    painter.drawEllipse(QPointF(fretCoords[7].x() + fretWidth/2, (float) height / 2.0),ellipseX,ellipseY);
    painter.drawEllipse(QPointF(fretCoords[9].x() + fretWidth/2, (float) height / 2.0),ellipseX,ellipseY);
    painter.drawEllipse(QPointF(fretCoords[15].x() + fretWidth/2, (float) height / 2.0),ellipseX,ellipseY);
    painter.drawEllipse(QPointF(fretCoords[17].x() + fretWidth/2, (float) height / 2.0),ellipseX,ellipseY);
    painter.drawEllipse(QPointF(fretCoords[19].x() + fretWidth/2, (float) height / 2.0),ellipseX,ellipseY);
    painter.drawEllipse(QPointF(fretCoords[21].x() + fretWidth/2, (float) height / 2.0),ellipseX,ellipseY);

    painter.drawEllipse(QPointF(fretCoords[12].x() + fretWidth/2, (float) height / 3.0),ellipseX,ellipseY);
    painter.drawEllipse(QPointF(fretCoords[12].x() + fretWidth/2, 2 * (float) height / 3.0),ellipseX,ellipseY);
    painter.drawEllipse(QPointF(fretCoords[24].x() + fretWidth/2, (float) height / 3.0),ellipseX,ellipseY);
    painter.drawEllipse(QPointF(fretCoords[24].x() + fretWidth/2, 2 * (float) height / 3.0),ellipseX,ellipseY);
}

void Fretboard::paintScaleStep(QPainter &painter, QColor color, int idx, int width, int height, QString name)
{
    const float fretWidth = (float) width / (float) numberOfFrets;
    const float fretHeight = (float) height / (float) numberOfString;
    const int rx = fretWidth / 3 + fretWidth/10;
    const int ry = fretHeight / 3;
    QBrush brush(color);
    painter.setBrush(brush);
    painter.drawEllipse(QPointF(fretCoords[idx].x() + fretWidth / 2, fretCoords[idx].y() - fretHeight / 2), rx, ry);

    QString s = QString::number(idx % numberOfFrets);

    int shift = 2;
    while(rx < shift * 3) {
        --shift;
    }
    QRect rect(QPoint(fretCoords[idx].x(),fretCoords[idx].y() - fretHeight),
               QPoint(fretCoords[idx].x() + fretWidth, fretCoords[idx].y()));

    QPen pen;
    pen.setColor(Qt::green);
    painter.setPen(pen);
    QFont font;
    font.setPointSize(rx/2 + ry/2);
    font.setBold(true);
    painter.setFont(font);

    // apply font color change if contrast of marker is bad for black font
    if(color == Qt::blue) {
        pen.setColor(Qt::yellow);
    } else {
        pen.setColor(Qt::black);
    }
    painter.setPen(pen);
    if(!displayNotesAsTab) {
        s = name;
    }
    painter.drawText(rect, Qt::AlignCenter, s);
    pen.setColor(Qt::black);
    painter.setPen(pen);
}
