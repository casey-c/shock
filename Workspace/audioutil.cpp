#include "audioutil.h"
#include <QDebug>

AudioUtil::AudioUtil(QString filePath) :
    fileHandlingMode(FULL_CACHE),
    sfInfo(new SF_INFO),
    sndFileNotEmpty(false)
{
    setFile(filePath);
    setFileHandlingMode(FULL_CACHE);
}

AudioUtil::~AudioUtil() {
    if (sndFileNotEmpty)
        sf_close(sndFile);
    delete sfInfo;
}

void AudioUtil::setFileHandlingMode(FileHandlingMode mode) {
    fileHandlingMode = mode;
    if (mode == FULL_CACHE)
        populateCache();
}

bool AudioUtil::setFile(QString filePath) {
    if (sndFileNotEmpty)
        sf_close(sndFile);
    sfInfo->format = 0;

    // Attempt to open the file
    sndFile = sf_open(filePath.toStdString().c_str(), SFM_READ, sfInfo);
    if (!sndFile) {
        qWarning() << "ERROR: Failed to open input file";
        sf_perror(NULL);
        return false;
    }

    // Normalization
    sf_command(sndFile, SFC_SET_NORM_DOUBLE, NULL, SF_TRUE);


    //conversion to mono

    if (sfInfo->channels > 1) {
        convertMono();
        sndFile = sf_open(filePath.toStdString().c_str(), SFM_READ, sfInfo);
    }
    if (fileHandlingMode == FULL_CACHE)
    {
        //fileCache.clear();
        //fileCache = getAllFrames();
    }

    sndFileNotEmpty = true;
    return true;
}

void AudioUtil::convertMono() {
    float *audioIn = new float[sfInfo->channels * sfInfo->frames];
    sf_read_float(sndFile, audioIn, sfInfo->channels * sfInfo->frames);
   // mixdown
    float *audioOut = new float[sfInfo->frames];
    for(int i = 0; i < sfInfo->frames; i++)
    {
        audioOut[i] = 0;
        for(int j = 0; j < sfInfo->channels; j++)
            audioOut[i] += audioIn[i*sfInfo->channels + j];
        audioOut[i] /= sfInfo->channels;
    }
    sf_close(sndFile);
    // write output
    int frames = sfInfo->frames;
    sfInfo->format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfInfo->channels = 1;
    sndFile = sf_open((filePath).toStdString().c_str(), SFM_WRITE, sfInfo);
    sf_write_float(sndFile, audioOut, frames);
    sf_close(sndFile);
}

QVector<double> AudioUtil::calculateNormalizedPeaks() {
    peaks.clear();

    // Not sure if what was originally intended?
    double* peaksPtr = (double*)malloc(getNumChannels() * sizeof(double));

    sf_command(sndFile, SFC_CALC_NORM_MAX_ALL_CHANNELS,
               peaksPtr, sizeof(double)*getNumChannels());

    double avg = 0;
    for (int i = 0; i < getNumChannels(); ++i)
        avg += peaksPtr[i];

    peaks.push_back(avg/getNumChannels());

    free(peaksPtr);
    return peaks;
    for (int i = 0; i < getNumChannels(); ++i)
        peaks.push_back(peaksPtr[i]);

    free(peaksPtr);
    return peaks;
}

int AudioUtil::getNumChannels() {
    return sfInfo != NULL ? sfInfo->channels : NULL;
}

int AudioUtil::getSampleRate() {
    return sfInfo != NULL ? sfInfo->samplerate : NULL;
}

int AudioUtil::getTotalFrames() {
    return sfInfo != NULL ? sfInfo->frames : NULL;
}

QVector<double> AudioUtil::grabFrame(int frameIndex) {
    QVector<double> frameData;

    // TODO: refactor!
    if (fileHandlingMode == FULL_CACHE) {
        if (getNumChannels() == 1) {
            if (frameIndex >=  fileCache.size()) {
                qWarning() << "ERROR: grabFrame() - attempt to access out of range frame";
                return frameData;
            }
            else {
                frameData.append(fileCache.at(frameIndex));
            }
        }
        else if (getNumChannels() == 2) {
            if (2 * frameIndex + 1 >= fileCache.size()) {
                qWarning() << "ERROR: grabFrame() - attempt to access out of range frame";
                return frameData;
            }
            else {
                frameData.append(fileCache.at(2 * frameIndex));
                frameData.append(fileCache.at(2 * frameIndex + 1));
            }
        }
    }
    else if (fileHandlingMode == DISK_MODE) {
        qErrnoWarning("DISKMODE NOT IMPLEMENTED");
    }
    return frameData;
}

QVector<double> AudioUtil::peakForRegion(int start, int end) {
    if (end > fileCache.size()) {
        end = fileCache.size();
    }
    if (fileHandlingMode == FULL_CACHE) {
        // TODO: refactor!
        if (getNumChannels() == 2) {
            regionPeak.clear();

            double max0 = 0.0;
            double max1 = 0.0;

            //qDebug() << "fileCache size is" << fileCache.size();
            //qDebug() << "start is " << 2*start;
            //qDebug() << "end is " << 2*end;

            for (int i = 2*start; i < 2*end && i < fileCache.size(); i+=2) {
                if (qAbs(fileCache[i]) > qAbs(max0))
                    max0 = fileCache[i];
                if (qAbs(fileCache[i+1]) > qAbs(max1))
                    max1 = fileCache[i+1];
            }

            regionPeak.append(max0);
            regionPeak.append(max1);
        }
        else if (getNumChannels() == 1) {

            regionPeak.clear();

            double max0 = 0.0;

            for (int i = start; i < end; i++) {
                if (qAbs(fileCache[i]) > qAbs(max0))
                    max0 = fileCache[i];
            }

            regionPeak.append(max0);
        }
    }
    else if (fileHandlingMode == DISK_MODE) {
        qWarning() << "ERROR: DISKMODE NOT HANDLED";
    }

    return regionPeak;
}

void AudioUtil::populateCache() {
    fileCache.clear();
    int readSize = 1024;

    if (sf_seek(sndFile, 0, SEEK_SET) == -1)
        qWarning() << "Seek failed in populateCache";

    double* chunk = new double[readSize];
    int itemsRead = sf_read_double(sndFile, chunk, readSize);

    int numChannels = getNumChannels();
    int totalRead = 0;
    double mono = 0;


    while (itemsRead == readSize) {
        for (int i = 0; i < readSize; ++i) {
            if (totalRead%numChannels == 0) {// only appends a single channel from a multi-channel sound
                mono += chunk[i];
                fileCache.append(mono/numChannels);
                mono = 0;
            }
            else
                mono += chunk[i];

            totalRead++;
        }


        itemsRead = sf_read_double(sndFile, chunk, readSize);
    }

    for (int i = 0; i < itemsRead; ++i) {
        if (totalRead%numChannels == 0) {// only appends a single channel from a multi-channel sound
            mono += chunk[i];
            fileCache.append(mono/numChannels);
            mono = 0;
        }
        else
            mono += chunk[i];

        totalRead++;
    }


    sfInfo->channels = 1;

    //qDebug() << "in populate: fileCache size is" << fileCache.size();
}

QVector<double> AudioUtil::getAllFrames() {
   if(this->fileHandlingMode == FULL_CACHE)
   {
      return this->fileCache;
   }
   else
   {
       this->dataVector.clear();
       int readSize = 1024;

       //seek to file start
      if (sf_seek(sndFile, 0, SEEK_SET) == -1)
      {
          fprintf(stderr, "seek failed in AudioUtil::getAllFrames() function\n");
      }
       double *chunk = new double[readSize];
       int itemsRead = sf_read_double(this->sndFile, chunk, readSize);

       while(itemsRead == readSize)
       {

           for(int i = 0; i < readSize; i++)
           {
                this->dataVector.push_back(chunk[i]);
           }

           itemsRead = sf_read_double(this->sndFile, chunk, readSize);
       }

       //add the last items to the vector
       for(int i = 0; i < itemsRead; i++)
       {
            this->dataVector.push_back(chunk[i]);
       }

       delete[] chunk;

       return this->dataVector;
   }
}













