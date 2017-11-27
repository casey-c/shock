#ifndef AUDIOUTIL_H
#define AUDIOUTIL_H

#include <QVector>
#include <sndfile.hh>

class AudioUtil {
public:
    AudioUtil() : fileHandlingMode(DISK_MODE),
                  sfInfo(new SF_INFO),
                  sndFileNotEmpty(false) {}
    AudioUtil(QString filePath);
    ~AudioUtil();

    bool setFile(QString filePath);
    int getNumChannels();
    int getSampleRate();
    int getTotalFrames();

    QVector<double> calculateNormalizedPeaks();
    QVector<double> grabFrame(int frameIndex);
    QVector<double> peakForRegion(int start, int end);
    QVector<double> getAllFrames();

    enum FileHandlingMode{FULL_CACHE, DISK_MODE};
    FileHandlingMode getFileHandlingMode() { return fileHandlingMode; }
    void setFileHandlingMode(FileHandlingMode mode);

private:
    void convertMono();

    QVector<double> data;
    FileHandlingMode fileHandlingMode;
    QString filePath;

    SNDFILE* sndFile;
    SF_INFO* sfInfo;
    bool sndFileNotEmpty;
    int readCount;

    QVector<double> peaks;
    QVector<double> regionPeak;
    QVector<double> fileCache;
    QVector<double> dataVector;

    void populateCache();
};


#endif // AUDIOUTIL_H
