#include "model.h"
#include "Runge_Kutta.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime> 
#include <omp.h>
#include <random>

using namespace std;

#define TIME 100        //����� �������������

#define NUMAVE 50000    //���������� �������� ��� ����������
double FREQ = 140;        //������� ��������������� �������
double SIGNAL = -4;        //������� ������� (0 - ��� �������; <0 - �����; >0 - DC, ������ ��������);
double STEP = 0.01;     //��� �� �������. 0.001 = 1 ������������
int METHOD = 1;            // ����� ��������������. 1 = ����. 2 = �����. 3 = �����-�����

inline void nul(double *V){    // ��������� ���������� �������
    V[0] = -1.1;
    V[1] = -0.656;
}



inline double newnoise(){    //��������� �������� ����
    double q, t1, t2, s;
    do{
        t1 = rand() / (double)RAND_MAX * 2 - 1;
        t2 = rand() / (double)RAND_MAX * 2 - 1;
        s = t1 * t1 + t2 * t2;
    } while ((s) > 1);
    q = t1 * sqrt(-2 * log(s) / s);


    return q;
}


void escape_time_parallel_launch(ofstream *fout){

    double EscTime = 0.0;
    double EscTime2 = 0.0;
    double dispercy = 0.005;

    while (dispercy < 50) {
        EscTime = 0.0;
        EscTime2 = 0.0;
        system("cls");
        std::cout << FREQ << ":  " << dispercy;
        //unsigned int start_time = clock();
        setParams(STEP, FREQ);
        double noiseParam = sqrt(2 * dispercy * STEP);
        double noise = 0.0;

#pragma omp parallel reduction(+:EscTime,EscTime2) num_threads(5) private(noise)
        {
            //            std::cout << omp_get_thread_num() << " ";
#pragma omp for
            
            for (int k = 0; k < NUMAVE; k++){
                double *Y = new double[2];
                nul(Y);
                
                //double oldnoise = 0.0;


                for (double i = 0; i < TIME; i += STEP){

                    noise = newnoise();


                    Model_next_Step(Y, i, STEP, FREQ, SIGNAL, noise * noiseParam, METHOD);


                    if (Y[0] > 1) {
                        EscTime += i;
                        EscTime2 += i*i;
                        break;
                    }
                }
                delete []Y;
            }
        }
        EscTime /= NUMAVE;
        EscTime2 /= NUMAVE;
        //unsigned int end_time = clock(); // �������� �����
        //unsigned int search_time = end_time - start_time; // ������� �����
        double tmp = sqrt(EscTime2 - EscTime*EscTime);
        *fout << dispercy << " " << EscTime << " " << tmp << " " << tmp / EscTime << "\n";
        dispercy *= 1.04;
    }
}

void simplelaunch(ofstream *fout){

    double dispercy = 0.001;
    double noise;
    double *V = new double[N];
    setParams(STEP, 0);
    nul(V);
                for (double i = 0; i < TIME; i += STEP){

                    noise = newnoise();

                    //Model_next_Step(V, i, STEP, FREQ, SIGNAL, (noise * sqrt(2 * dispercy * STEP)), METHOD);
                    Model_next_Step(V, i, STEP, 0, 0, 0, METHOD);

                    *fout << i << " " << *V << " " << V[1] << "\n";
                }
    delete []V;
            
}

inline double generatingTime() {
    double *Y = new double[2];
    nul(Y);
    for (double i = 0; i < TIME; i += STEP) {

        Model_next_Step(Y, i, STEP, FREQ, SIGNAL, 0, METHOD);

        if (Y[0] > 1) {
            return i;
        }
    }

    delete []Y;
    return -1;
}

void getAllGeneratingTime(ofstream *fout) {
    double tmp;
    for (SIGNAL = 0.1; SIGNAL < 1; SIGNAL += 0.1)
    {
        for (FREQ = 0.01; FREQ < 2; FREQ *= 1.1)
        {
            setParams(STEP, FREQ);
            tmp = generatingTime();
            cout << SIGNAL << " " << FREQ << " " << tmp << "\n";
            *fout << SIGNAL << " " << FREQ << " " << tmp << "\n";
        }
    }
}



int main(){
    ofstream fout("output.txt");
    //simplelaunch(&fout);

    //    ifstream fin("input.txt");

    //srand(time(NULL));


    //    somelaunch(&fout);
    //    escape_time_parallel_launch(&fout);
    //    qq123(&fout);

    /*    ofstream fout6("6.txt");
    ofstream fout7("7.txt");
    ofstream fout9("9.txt");

    SIGNAL = 6;
    escape_time_parallel_launch(&fout6);
    fout6.close();
    SIGNAL = 7;
    escape_time_parallel_launch(&fout7);
    fout7.close();
    SIGNAL = 9;
    escape_time_parallel_launch(&fout9);
    fout9.close();*/


    /*for (METHOD = 1; METHOD <= 1; METHOD += 1){
        std::cout << "METHOD = " << METHOD << "\n";
        std::ostringstream strs;
        strs << METHOD;
        std::string str = strs.str();
        str += ".txt";
        ofstream fout(str);
        escape_time_parallel_launch(&fout);

        fout.close();
    }*/



    /*
    for (FREQ = 131; FREQ <= 133; FREQ += 1){
        std::cout << "FREQ = " << FREQ << "\n";
        std::ostringstream strs;
        strs << FREQ;
        std::string str = strs.str();
        str += ".txt";
        ofstream fout(str);
        escape_time_parallel_launch(&fout);

        fout.close();
    }*/

    getAllGeneratingTime(&fout);

    /*FREQ = 20;
    SIGNAL = -4;
    simplelaunch(&fout);
    fout.close();*/


    system("pause");
    return 0;
}