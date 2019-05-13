// neuron-model-integration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "model.h"
#include "integration.h"
#include "noise-generator.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime> 
#include <omp.h>
#include <random>

using namespace std;

#define INTEL_RANDOM_GENERATOR

#define TIME 400

#define NUMAVE 10000

#define FREQ_START 0.017
#define FREQ_FINISH 0.017
#define FREQ_STEP 1.05

#define NOISE_START 0.0001
#define NOISE_FINISH 10
#define NOISE_STEP 1.1

double SIGNAL = 0.5;


//#define OUT_FREQ


double FREQ = 1.1;
double STEP = 0.01;
int METHOD = 1;

inline double newnoise() {    //Генерация Гауссого шума
    double q, t1, t2, s;
    do {
        t1 = rand() / (double)RAND_MAX * 2 - 1;
        t2 = rand() / (double)RAND_MAX * 2 - 1;
        s = t1 * t1 + t2 * t2;
    } while ((s) > 1);
    q = t1 * sqrt(-2 * log(s) / s);


    return q;
}

void escape_time_parallel_launch(ofstream *fout) {

    double EscTime = 0.0;
    double EscTime2 = 0.0;
    double dispercy = NOISE_START;

    while (dispercy <= NOISE_FINISH) {
        EscTime = 0.0;
        EscTime2 = 0.0;
        system("cls");
        std::cout << FREQ << ":  " << dispercy;
        //unsigned int start_time = clock();
        setParams(STEP, FREQ, SIGNAL);
        double noiseParam = sqrt(2 * dispercy * STEP);
        double noise = 0.0;

#pragma omp parallel reduction(+:EscTime,EscTime2) private(noise)
        {
            //            std::cout << omp_get_thread_num() << " ";
            neuron_model::vector Y;
#pragma omp for

            for (int k = 0; k < NUMAVE; k++) {
                
                setDefaultPoint(Y);

                int steps = (int)TIME / STEP;
#ifdef INTEL_RANDOM_GENERATOR
                double* noiseArray = new double[steps + 10];

                getNoiseArray(0, noiseParam, steps + 10, noiseArray);
#endif
                double currentTime = 0;
                //for (int i = 0, double currentTime = 0; currentTime < TIME; i++, currentTime += STEP) {
                for (int i = 0; i < steps; i++) {

#ifdef INTEL_RANDOM_GENERATOR
                    noise = noiseArray[i + 10];
#else
                    noise = newnoise() * noiseParam;
#endif

                    Model_next_Step(Y, currentTime, noise);


                    if (Y[0] > 1) {
                        break;
                    }

                    currentTime += STEP;
                }

                EscTime += currentTime;
                EscTime2 += currentTime * currentTime;


#ifdef INTEL_RANDOM_GENERATOR
                delete[] noiseArray;
#endif
            }
            delete[]Y;
        }
        EscTime /= NUMAVE;
        EscTime2 /= NUMAVE;
        //unsigned int end_time = clock(); 
        //unsigned int search_time = end_time - start_time; 
        double deviation = sqrt(EscTime2 - EscTime * EscTime);

#ifdef OUT_FREQ
        *fout << FREQ << " ";
#else
        *fout << dispercy << " ";
#endif
        if (EscTime > 0.0000001) 
            *fout << EscTime << " " << deviation << " " << deviation / EscTime << "\n";
        else 
            *fout <<"0 0 0\n";
        dispercy *= NOISE_STEP;
    }
}

void simplelaunch(ofstream *fout) {

    double dispercy = 0.01;
    double noise;
    FREQ = 1.5;
    SIGNAL = 0.5;
    double *V = new double[N];
    setParams(STEP, FREQ, SIGNAL);
    setDefaultPoint(V);

    for (double i = 0; i < TIME; i += STEP) {

        noise = newnoise();

        //Model_next_Step(V, i, (noise * sqrt(2 * dispercy * STEP)));
        Model_next_Step(V, i, 0);
        *fout << i << " " << *V << " " << V[1] << "\n";
    }
    delete[]V;

}

inline double generatingTime() {
    double *Y = new double[2];
    setDefaultPoint(Y);
    for (double i = 0; i <= TIME; i += STEP) {

        Model_next_Step(Y, i, 0 /*noise*/);

        if (Y[0] > 0) {
            delete[]Y;
            return i;
        }
    }

    delete[]Y;
    return -1;
}

void getAllGeneratingTime(ofstream *fout) {
    double tmp;
    for (SIGNAL = 0.1; SIGNAL <= 1.0; SIGNAL += 0.1)
    {
        for (FREQ = 0.001; FREQ < 0.2; FREQ *= 1.05)
        {
            setParams(STEP, FREQ, SIGNAL);
            tmp = generatingTime();
            if (-1 == tmp) continue;
            cout << SIGNAL << " " << FREQ << " " << tmp << "\n";
            *fout << SIGNAL << " " << FREQ << " " << tmp << "\n";
            break;
        }
    }
}


int main() {

#if 1
    ofstream fout("out1.txt");
    
    getAllGeneratingTime(&fout);
    //simplelaunch(&fout);
    fout.close();

#else
    ifstream fin("input.txt");

    double dummy;
    fin >> SIGNAL >> FREQ >> dummy;
    FREQ = FREQ_START;

    while (!fin.eof())
    {

        double dummy;
        fin >> SIGNAL >> FREQ >> dummy;

        std::cout << "FREQ = " << FREQ << "\n";
        std::ostringstream strs;
        strs << SIGNAL << "_" << FREQ;
        std::string str = strs.str();
        str += ".txt";
        ofstream fout(str);

        escape_time_parallel_launch(&fout);
        FREQ *= FREQ_STEP;
        fout.close();

    }
    fin.close();


#endif

    return 0;
}

