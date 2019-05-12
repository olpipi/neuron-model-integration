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

#define TIME 4000

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
#if 0
void simplelaunch(ofstream *fout) {

    double dispercy = 0.001;
    double noise;
    double *V = new double[N];
    setParams(STEP, FREQ);
    nul(V);
    for (double i = 0; i < TIME; i += STEP) {

        noise = newnoise();


        //Model_next_Step(V, i, STEP, FREQ, SIGNAL, (noise * sqrt(2 * dispercy * STEP)), METHOD);
        Model_next_Step(V, i, STEP, FREQ, SIGNAL, 0, METHOD);

        *fout << i << " " << *V << " " << V[1] << "\n";
    }
    delete[]V;

}

inline double generatingTime() {
    double *Y = new double[2];
    nul(Y);
    for (double i = 0; i < TIME; i += STEP) {

        Model_next_Step(Y, i, 0, 0, SIGNAL, 0, 0);

        if (Y[0] > 1) {
            return i;
        }
    }

    delete[]Y;
    return -1;
}

void getAllGeneratingTime(ofstream *fout) {
    double tmp;
    for (SIGNAL = 0.1; SIGNAL <= 1; SIGNAL += 0.02)
    {
        for (FREQ = 0.001; FREQ < 2; FREQ *= 1.05)
        {
            setParams(STEP, FREQ);
            tmp = generatingTime();
            if (-1 == tmp) continue;
            cout << SIGNAL << " " << FREQ << " " << tmp << "\n";
            *fout << SIGNAL << " " << FREQ << " " << tmp << "\n";
            break;
        }
    }
}
#endif


int main() {

    //FREQ = 0.1;
    //SIGNAL = 0.5;

    //ofstream fout("out.txt");
    //
    //simplelaunch(&fout);

    //fout.close();

    FREQ = FREQ_START;

    while (FREQ <= FREQ_FINISH)
    {
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



    return 0;
}

//
//
//int main() {
//    ofstream fout("output.txt");
//    simplelaunch(&fout);
//
//    ifstream fin("input.txt");
//
//    srand(time(NULL));
//
//
//        somelaunch(&fout);
//        escape_time_parallel_launch(&fout);
//        qq123(&fout);
//
//    /*    ofstream fout6("6.txt");
//    ofstream fout7("7.txt");
//    ofstream fout9("9.txt");
//
//    SIGNAL = 6;
//    escape_time_parallel_launch(&fout6);
//    fout6.close();
//    SIGNAL = 7;
//    escape_time_parallel_launch(&fout7);
//    fout7.close();
//    SIGNAL = 9;
//    escape_time_parallel_launch(&fout9);
//    fout9.close();*/
//
//
//    /*for (METHOD = 1; METHOD <= 1; METHOD += 1){
//        std::cout << "METHOD = " << METHOD << "\n";
//        std::ostringstream strs;
//        strs << METHOD;
//        std::string str = strs.str();
//        str += ".txt";
//        ofstream fout(str);
//        escape_time_parallel_launch(&fout);
//
//        fout.close();
//    }*/
//
//
//    clock_t t1, t2;
//    t1 = clock();
//
//
//
//    /*for (FREQ = 131; FREQ <= 131; FREQ += 1) {
//        std::cout << "FREQ = " << FREQ << "\n";
//        std::ostringstream strs;
//        strs << FREQ;
//        std::string str = strs.str();
//        str += ".txt";
//        ofstream fout(str);
//        escape_time_parallel_launch(&fout);
//
//        fout.close();
//    }*/
//
//    double dummy;
//    while (!fin.eof()) {
//
//        fin >> SIGNAL >> FREQ >> dummy;
//
//        FREQ += 1.0;
//        for (int i = 0; i < 5; i++) {
//            FREQ *= 1.02;
//            std::cout << "FREQ = " << FREQ << "\n";
//            std::ostringstream strs;
//            strs << SIGNAL << "_" << FREQ;
//            std::string str = strs.str();
//            str += ".txt";
//            ofstream fout(str);
//            escape_time_parallel_launch(&fout);
//            fout.close();
//
//        }
//
//
//    }
//
//    t2 = clock();
//    float diff((float)t2 - (float)t1);
//    cout << "\n" << diff << "\n";
//
//
//    /*FREQ = 20;
//    SIGNAL = -4;
//    simplelaunch(&fout);
//    fout.close();*/
//
//
//    system("pause");
//    return 0;
//}
