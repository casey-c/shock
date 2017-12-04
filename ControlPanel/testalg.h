#ifndef TESTALG_H
#define TESTALG_H

#include "ialgorithm.h"

class Feature
{
public:
    Feature() {;}
    Feature(QVector<float> input);
    short ty() {return type;}

protected:
    QVector<float> data;
    short type;
};


class Silence : public Feature
{
public:
    Silence(QVector<float> input);
};

class SineWave : public Feature{
public:
    SineWave(QVector<float> input);
};

class SquareWave : public Feature{
public:
    SquareWave(QVector<float> input);
};

class SawWave : public Feature
{
public:
    SawWave(QVector<float> input);
};

class DefaultWave : public Feature{
public:
    DefaultWave(QVector<float> input);
};

class FeatureDetection
{
public:
    FeatureDetection() {}
    FeatureDetection(AlgoSettings* settings);
    void detect(QVector<float> input);
    QVector<Feature*> getFeatures() {return features;}
private:
    float slope(float Y1, float Y2, float X1 = 0, float X2 = 1);
    QVector<Feature*> features;
    double sameThreshold = .001;
    double silenceThreshold = .0001;
    int sineishErrorMax = 10;
};

class TestAlg : public IAlgorithm
{
public:
    TestAlg();
    TestAlg(AlgoSettings* settings);
    QVector<float> run(QVector<QVector<float>> input) override;

private:
    AlgoSettings* settings;
};

#endif // TESTALG_H
