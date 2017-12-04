#include "testalg.h"

Feature::Feature(QVector<float> input){

}

Silence::Silence(QVector<float> input){
    type = 0;
    data = input;
}

SquareWave::SquareWave(QVector<float> input){
    type = 1;
    data = input;
}

SawWave::SawWave(QVector<float> input){
    type = 2;
    data = input;
}

SineWave::SineWave(QVector<float> input){
    type = 3;
    data = input;
}

DefaultWave::DefaultWave(QVector<float> input){
    type = 4;
    data = input;
}

FeatureDetection::FeatureDetection(AlgoSettings* settings){
    Param* p;
    foreach(p, settings->getParams()){
        if(p->getName() == "silenceThreshold")
            silenceThreshold = p->getValue();
        else if(p->getName() == "sameThreshold")
            sameThreshold = p->getValue();
        else if(p->getName() == "sineishErrorMax")
            sineishErrorMax = (int)p->getValue();
    }
}

float FeatureDetection::slope(float Y1, float Y2, float X1, float X2){
    return (Y2 - Y1) / (X2 - X1);
}


void FeatureDetection::detect(QVector<float> input){

    short trend = 0;
    short lastTrend = 0;
    bool sineish = true;
    bool isSilence = false;
    int sineishError = 0;
    int silences = 0;
    int bigChanges = 0;

// dont worry about these
    int cooldown = 0;
    int cooldownSet = 40;
// ......................


    QVector<float> slopes;
    int beginWave =0;
    int zeroedCount = 0;
    int countWaves = 0;
    for(int i = 0; i < input.size(); ++i){
        if(input[i] >= 0 - silenceThreshold &&
           input[i] <= 0 + silenceThreshold){
            silences++;
        }
        if((input[i] < 0 && input[i+1] > 0) ||
           (input[i] > 0 && input[i+1] < 0)){
            cooldown = cooldownSet;
            zeroedCount++;
        }
        cooldown--;
        if (silences > 100){
            zeroedCount = 3;
            isSilence = true;
        }
        if (i == input.size()-1){
            zeroedCount = 3;
        }
        if(zeroedCount == 3){
            zeroedCount = 0;
            //qDebug() << "WaveEnd" << countWaves;
            //qDebug() << beginWave << i;
            countWaves++;
            if(bigChanges >= 2){
                //qDebug() << "Square?";
                features.append(new SquareWave(input.mid(beginWave-1,(i-beginWave))));
            }
            else if (bigChanges >= 1){
                //qDebug() << "Saw?";
                features.append(new SawWave(input.mid(beginWave-1,(i-beginWave))));
            }
            else if (isSilence) {
                //qDebug() << "Silence?";
                features.append(new Silence(input.mid(beginWave-1,(i-beginWave))));
            }
            else if (sineish){
                //qDebug() << "Sine?";
                features.append(new SineWave(input.mid(beginWave-1,(i-beginWave))));
            }
            else{
                //qDebug() << "default";
                features.append(new DefaultWave(input.mid(beginWave-1,(i-beginWave))));
            }

            beginWave = i+1;
            sineish = true;
            isSilence = false;
            sineishError = 0;
            bigChanges = 0;

        }
        cooldown = qMax(cooldown,0);
        if (qAbs(slope(input[i],input[i+1])) > .25){
            bigChanges++;
        }
        if(i+1 <= input.size()){
            if (qAbs(input[i]-input[i+1])< sameThreshold){
                trend = 0;
            }
            else if(input[i] < input[i+1]){
                trend = 1;
            }
            else if (input[i] > input[i+1]){
                trend = -1;
            }
            if(lastTrend == 1 && trend == 0||
               lastTrend == -1 && trend == 0||
               lastTrend == 0 && trend == 1 ||
               lastTrend == 0 && trend == 1 ||
               lastTrend == 0 && trend == 0 ||
               lastTrend == 1 && trend == 1 ||
               lastTrend == -1 && trend == -1){
                cooldown = 1;
            }
            else {
                if(sineishError >= sineishErrorMax)
                    sineish = false;
                sineishError++;
            }
            if (0){
                if (lastTrend < trend)
                    qDebug() << i << "inc" << slope(input[i],input[i+1])<< input[i]<<input[i+1];
                else if(lastTrend > trend)
                    qDebug() << i << "dec"<< slope(input[i],input[i+1])<< input[i]<<input[i+1];
                else
                    qDebug() << i << "same"<< slope(input[i],input[i+1])<< input[i]<<input[i+1];
            }
            slopes.append(slope(input[i],input[i+1]));
            lastTrend = trend;
        }
    }

    qDebug() << input.size();
    qDebug() << slopes.size();


}

void TestAlg::setOutputLength(double len) {
    outputLength = len;
}

TestAlg::TestAlg(AlgoSettings* settings)
{
    this->settings = settings;
}

QVector<float> TestAlg::run(QVector<QVector<float> > input){
    QList<FeatureDetection*> analyzedSounds;
    for(int i = 0; i < input.size(); ++i){
        if(i == 0) qDebug() << "Input " << i;
        FeatureDetection* in = new FeatureDetection(settings);
        in->detect(input[i]);
        analyzedSounds.append(in);
        qDebug() << in->getFeatures().size();
    }

    QVector<Feature*> silence;
    QVector<Feature*> square;
    QVector<Feature*> sine;
    QVector<Feature*> saw;
    QVector<Feature*> defaultWave;
    FeatureDetection* analyzed;
    foreach (analyzed, analyzedSounds) {
        QVector<Feature*> features = analyzed->getFeatures();
        Feature* A;
        foreach(A, features){
            if (A->ty() == 0)
                silence.append(A);
            else if(A->ty() == 1)
                square.append(A);
            else if(A->ty() == 2)
                saw.append(A);
            else if(A->ty() == 3)
                sine.append(A);
            else
                defaultWave.append(A);
        }
    }



    unsigned long len = 44100 * outputLength;
    unsigned int totalFeatures = silence.size() +
                                 square.size() +
                                 saw.size() +
                                 sine.size() +
                                 defaultWave.size();

    qDebug() << totalFeatures;

    double chanceSine = (double)sine.size() / totalFeatures;
    double chanceSquare = (double)square.size() / totalFeatures + chanceSine;
    double chanceSaw = (double)saw.size() / totalFeatures + chanceSquare;
    double chanceDefault = (double)defaultWave.size() / totalFeatures + chanceSaw;
    double chanceSilence = (double)silence.size() / totalFeatures + chanceDefault;
    QVector<float> output;

    qDebug() << chanceSine;
    qDebug() << chanceSquare;
    qDebug() << chanceSaw;
    qDebug() << chanceDefault;
    qDebug() << chanceSilence;

    while(output.size() < len){
        float test = qrand() / RAND_MAX;
        if (test < chanceSine){
            float randint = qrand() % sine.size();
            output.append(sine[randint]->getData());
        }
        else if (test < chanceSquare){
            float randint = qrand() % square.size();
            output.append(square[randint]->getData());
        }
        else if (test < chanceSaw){
            float randint = qrand() % saw.size();
            output.append(saw[randint]->getData());
        }
        else if (test < chanceDefault){
            float randint = qrand() % defaultWave.size();
            output.append(defaultWave[randint]->getData());
        }
        else if (test < chanceSilence){
            float randint = qrand() % silence.size();
            output.append(silence[randint]->getData());
        }

    }


    return(output);
}
