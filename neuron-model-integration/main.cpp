#include "model.h"
#include "Runge_Kutta.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime> 
#include <omp.h>
#include <random>

using namespace std;

#define TIME 120		//Время моделирования

#define NUMAVE 10000	//Количество прогонов для усреднения
double FREQ = 140;		//Частота синусоидального сигнала
double SIGNAL = -4;		//Наличие сигнала (0 - без сигнала; <0 - синус; >0 - DC, равный значению);
double STEP = 0.01; 	//Шаг по времени. 0.001 = 1 микросекунда
int METHOD = 1;			// Метод интегрирования. 1 = Хьюн. 2 = Эйлер. 3 = Рунге-кутты

void nul(double *V){	// Обнуление переменных системы
	V[0] = -1.1;
	V[1] = -0.656;
}



double newnoise(){	//Генерация Гауссого шума
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
	double dispercy = 0.001;

	while (dispercy < 100) {
		EscTime = 0.0;
		EscTime2 = 0.0;
		system("cls");
		std::cout << FREQ << ":  " << dispercy;
		//unsigned int start_time = clock();
		setParams(STEP, FREQ);

#pragma omp parallel reduction(+:EscTime,EscTime2) num_threads(4)
		{
			//			std::cout << omp_get_thread_num() << " ";
#pragma omp for
			
			for (int k = 0; k < NUMAVE; k++){
				double *Y = new double[2];
				nul(Y);
				double noise = 0.0;
				//double oldnoise = 0.0;


				for (double i = 0; i < TIME; i += STEP){

					noise = newnoise();

					//oldnoise = noise;
					//noise = newnoise();


					Model_next_Step(Y, i, STEP, FREQ, SIGNAL, (noise * sqrt(2 * dispercy * STEP)), METHOD);


					if (Y[0] > 30) {
						EscTime += i;
						EscTime2 += i*i;
						break;
					}
					//*fout << i << " " << *Y << " " << 4 * sin(2 * 3.14 * FREQ * i * 0.001) - 40 << "\n";
				}
				delete Y;
			}
		}
		EscTime /= NUMAVE;
		EscTime2 /= NUMAVE;
		//unsigned int end_time = clock(); // конечное время
		//unsigned int search_time = end_time - start_time; // искомое время

		*fout << dispercy << " " << EscTime << " " << sqrt(EscTime2 - EscTime*EscTime) << " " << sqrt(EscTime2 - EscTime*EscTime) / EscTime << "\n";
		dispercy *= 1.1;
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
	delete V;
			
}


int main(){
	ofstream fout("output.txt");
	//simplelaunch(&fout);

	//	ifstream fin("input.txt");

	srand(time(NULL));


	//	somelaunch(&fout);
	//	escape_time_parallel_launch(&fout);
	//	qq123(&fout);

	/*	ofstream fout6("6.txt");
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




	for (FREQ = 140; FREQ <= 140; FREQ += 5){
		std::cout << "FREQ = " << FREQ << "\n";
		std::ostringstream strs;
		strs << FREQ;
		std::string str = strs.str();
		str += ".txt";
		ofstream fout(str);
		escape_time_parallel_launch(&fout);

		fout.close();
	}


	/*FREQ = 20;
	SIGNAL = -4;
	simplelaunch(&fout);
	fout.close();*/


	system("pause");
	return 0;
}