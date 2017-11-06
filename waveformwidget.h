#ifndef WAVEFORMWIDGET_H
#define WAVEFORMWIDGET_H

#include <QWidget>
#include <QList>
#include <sndfile.hh>
#include "audioutil.h"

class WaveformWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WaveformWidget(QWidget *parent, QString filePath);
    ~WaveformWidget();

    void resetFile(QString fileName);
    void setColor(QColor color) { waveformColor = color; }

    enum FileHandlingMode {FULL_CACHE, DISK_MODE};
    void setFileHandlingMode(FileHandlingMode mode);
    FileHandlingMode getFileHandlingMode() { return currentFileHandlingMode; }

protected:
    virtual void resizeEvent(QResizeEvent*) {}
    virtual void paintEvent(QPaintEvent* evt);

private:
    AudioUtil* srcAudioFile;

    enum DrawingMode {OVERVIEW, MACRO, NO_MODE};
    DrawingMode currentDrawingMode;
    FileHandlingMode currentFileHandlingMode;

    QList< QList<double> >  peakList;
    QVector<double> dataVector;
    double maxPeak;
    double padding;
    double scaleFactor;

    QString audioFilePath;
    QColor waveformColor;
    QSize lastSize;

    void recalculatePeaks();
    void establishDrawingMode();
    void macroDraw(QPaintEvent* evt);
    void overviewDraw(QPaintEvent* evt);

};

#endif // WAVEFORMWIDGET_H
