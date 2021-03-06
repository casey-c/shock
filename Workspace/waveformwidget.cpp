/*
 * Note that we did not create this file, but adapted it for our use
 * As such, it does not fully conform to our commenting standards
 *
 */


#include "waveformwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

#define MACRO_MODE_TOGGLE_CONSTANT 100.0

// Helper (used to be in MathUtil.h)
double getVMax(QVector<double> vec) { // get max value within a range
    if (vec.empty()) {
        qWarning() << "ERROR: empty vector";
        return -1;
    }

    double max = vec.at(0);
    for (int i = 1; i < vec.size(); ++i)
        if (vec[i] > max)
            max = vec[i];

    return max;
}

WaveformWidget::WaveformWidget(QWidget*, QString filePath) : // create a new waveform widget
   srcAudioFile(new AudioUtil(filePath)),
   currentDrawingMode(NO_MODE),
   currentFileHandlingMode(FULL_CACHE),
   scaleFactor(-1.0)
{
   setFileHandlingMode(currentFileHandlingMode);

   resetFile(filePath);
}

WaveformWidget::~WaveformWidget() {
    delete srcAudioFile;
}

void WaveformWidget::resetFile(QString fileName) { // set internal variables to loaded sound
    audioFilePath = fileName;
    srcAudioFile->setFile(audioFilePath);

    peakList.clear();
    dataVector.clear();

    currentDrawingMode = NO_MODE;
    establishDrawingMode();
    repaint();
}

void WaveformWidget::setFileHandlingMode(FileHandlingMode mode) {
    currentFileHandlingMode = mode;
    if (currentFileHandlingMode == FULL_CACHE)
        srcAudioFile->setFileHandlingMode(AudioUtil::FULL_CACHE);
    else if (currentFileHandlingMode == DISK_MODE)
        srcAudioFile->setFileHandlingMode(AudioUtil::DISK_MODE);
}

void WaveformWidget::recalculatePeaks() { // calculate peaks for user display

    QVector<double> normPeak = srcAudioFile->calculateNormalizedPeaks();

    //double peak = MathUtil::getVMax(normPeak);
    double peak = getVMax(normPeak);
    scaleFactor = 1.0/peak;
    scaleFactor -= scaleFactor * padding;

    int totalFrames = srcAudioFile->getTotalFrames();
    int frameIncrement = totalFrames / width();

    // Disallowing for now (TODO: figure out why)
    if (currentDrawingMode == MACRO)
        return;

    peakList.clear();
    QVector<double> regionMax;


    // Note:
    // Peak list is a list of doubles. The list contains data for a single channel

    for (int i = 0; i < totalFrames; i += frameIncrement) {
        regionMax = srcAudioFile->peakForRegion(i, i + frameIncrement);

        for (int j=0; j < regionMax.size(); ++j)
            peakList.append(regionMax[j]);
    }
}

void WaveformWidget::paintEvent(QPaintEvent* evt) {
    establishDrawingMode();

    if (currentDrawingMode == OVERVIEW)
        overviewDraw(evt);
    else
        qWarning() << "DRAWING MODE NOT SUPPORTED";
}

void WaveformWidget::overviewDraw(QPaintEvent* evt) { // draw the sound file
    //qDebug() << "drawing overview";
    QPainter painter(this);
    painter.setPen(QPen(waveformColor, 1, Qt::SolidLine, Qt::RoundCap));

    int minX = evt->region().boundingRect().x();
    int maxX = evt->region().boundingRect().bottomRight().x();

    int minY = evt->region().boundingRect().y();
    int maxY = evt->region().boundingRect().bottomRight().y();

    //qDebug() << "minX" << minX << "maxX" << maxX;

    //qDebug() << "minY" << minY << "maxY" << maxY;


    int numChannels = 1;

    int totalHeight = maxY-minY;
    int channelHeight = totalHeight/numChannels;

    for (int i = 0 ; i < numChannels; ++i) {
        int mid = totalHeight*(1+2*(i))/(numChannels*2);

        QList<double> channelPeaks = peakList;

        QList<double>::iterator itr2 = channelPeaks.begin();
        for ( int x = minX; itr2 != channelPeaks.end() && x < maxX; ++itr2, ++x ) {
            double peak = (*itr2);
            double y1 = mid + peak * scaleFactor * channelHeight/2;
            double y2 = mid - peak * scaleFactor * channelHeight/2;

            //qDebug() << "drawingLine" << x << y1 << x << y2 << numChannels;

            painter.drawLine(x, y1, x, y2);
        }

    }

}

// TODO: refactor
void WaveformWidget::establishDrawingMode() {
    int audioFileSize = srcAudioFile->getTotalFrames();

    this->currentDrawingMode = OVERVIEW;

    if(this->currentDrawingMode == NO_MODE)
    {
        if(this->width() < audioFileSize/MACRO_MODE_TOGGLE_CONSTANT)
        {
            this->currentDrawingMode = OVERVIEW;

            this->recalculatePeaks();
        }else
        {
            this->currentDrawingMode = MACRO;
            this->dataVector = this->srcAudioFile->getAllFrames();
        }
    }

    /*if(this->currentDrawingMode != MACRO && this->width() >= audioFileSize/MACRO_MODE_TOGGLE_CONSTANT)
    {
        this->currentDrawingMode = MACRO;
        this->dataVector = this->srcAudioFile->getAllFrames();
    }*/

    if(this->currentDrawingMode == MACRO && this->width() < audioFileSize/MACRO_MODE_TOGGLE_CONSTANT)
    {
        this->currentDrawingMode = OVERVIEW;
    }

    if(this->size()!=this->lastSize && this->currentDrawingMode != MACRO)
    {
        this->recalculatePeaks();
    }

    this->lastSize = this->size();
}















