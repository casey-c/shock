#include "waveformwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

#define MACRO_MODE_TOGGLE_CONSTANT 100.0

// Helper (used to be in MathUtil.h)
double getVMax(QVector<double> vec) {
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

WaveformWidget::WaveformWidget(QWidget*, QString filePath) :
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

void WaveformWidget::resetFile(QString fileName) {
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

void WaveformWidget::recalculatePeaks() {

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
    // Peak list is a list of lists: outer list contains channels, inner list
    // contains data for a single channel

    for (int i = 0; i < srcAudioFile->getNumChannels(); ++i)
        peakList.append(QList<double>());


    for (int i = 0; i < totalFrames; i += frameIncrement) {
        regionMax = srcAudioFile->peakForRegion(i, i + frameIncrement);

        QList< QList<double> >::iterator it = peakList.begin();
        for ( int j = 0; it != peakList.end() && j < regionMax.size(); ++it, ++j)
            (*it).append(qAbs(regionMax[j]));
    }
}

void WaveformWidget::paintEvent(QPaintEvent* evt) {
    establishDrawingMode();

    if (currentDrawingMode == OVERVIEW)
        overviewDraw(evt);
    else
        qWarning() << "DRAWING MODE NOT SUPPORTED";
}

void WaveformWidget::overviewDraw(QPaintEvent* evt) {
    //qDebug() << "drawing overview";
    QPainter painter(this);
    painter.setPen(QPen(waveformColor, 1, Qt::SolidLine, Qt::RoundCap));

    int minX = evt->region().boundingRect().x();
    int maxX = evt->region().boundingRect().bottomRight().x();

    int minY = evt->region().boundingRect().y();
    int maxY = evt->region().boundingRect().bottomRight().y();

    qDebug() << "min" << minX << "max" << maxX;

    qDebug() << "min" << minY << "max" << maxY;


    int numChannels = peakList.size();
    //int channelHeight = height() / numChannels;


    int totalHeight = maxY-minY;
    int channelHeight = totalHeight/numChannels;


    QList< QList<double> >::iterator itr = peakList.begin();
    for (int i = 0 ; i < numChannels; ++i, ++itr) {
        int mid = totalHeight*(1+2*(i))/(numChannels*2);
        //int top = mid + channelHeight / 2;
        //int bot = mid - channelHeight / 2;

        QList<double> channelPeaks = (*itr);

        QList<double>::iterator itr2 = channelPeaks.begin();
        for ( int x = minX; itr2 != channelPeaks.end() && x < maxX; ++itr2, ++x ) {
            double peak = (*itr2);
            double y1 = mid + peak * scaleFactor * channelHeight/2;
            double y2 = mid - peak * scaleFactor * channelHeight/2; // TODO: scale these by height/4 to make big

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















