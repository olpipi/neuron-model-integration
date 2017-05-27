#include "model.h"
#include "Runge_Kutta.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime> 
#include <omp.h>
#include <random>

using namespace std;

//#define time_measurement

#define TIME 120		//Время моделирования

#define NUMAVE 40000	//Количество прогонов для усреднения
double FREQ = 140;		//Частота синусоидального сигнала
double SIGNAL = 4;		//
double STEP = 0.01; 	//Шаг по времени. 0.001 = 1 микросекунда


void nul(double *V){	// Обнуление переменных системы
	V[0] = 0.000277;
	V[1] = 0.0529;
	V[2] = 0.5961;
	V[3] = 0.3177;

	/*	V[0] = 3.75891;
	V[1] = 0.6;
	V[2] = 0.22;
	V[3] = 0.6;*/


	/*7	V[0] = 4.21668;
	V[1] = 0.0858722;
	V[2] = 0.445565;
	V[3] = 0.383789;*/

	/*9	V[0] = 5.04772;
	V[1] = 0.094134;
	V[2] = 0.416498;
	V[3] = 0.397029;*/


}



double newnoise(){	//Генерация Гауссого шума
	double q, t1, t2, s;
	do{
		t1 = rand() * 0.00006103 - 1;
		t2 = rand() * 0.00006103 - 1;
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
		std::cout << FREQ << ":  " << dispercy << "\n";
#if defined(time_measurement)
		unsigned int start_time = clock();
#endif
		setParams(SIGNAL, STEP, FREQ);

#pragma omp parallel reduction(+:EscTime,EscTime2) num_threads(4)
		{
			//			std::cout << omp_get_thread_num() << " ";
			double *Y = new double[4];
#pragma omp for
			for (int k = 0; k < NUMAVE; k++){				
				nul(Y);
				double noise = 0.0;
				//double oldnoise = 0.0;


				for (double i = 0; i < TIME; i += STEP){

					noise = newnoise();

					//oldnoise = noise;
					//noise = newnoise();


					Model_next_Step(Y, i, STEP, FREQ, SIGNAL, (noise * sqrt(2 * dispercy * STEP)));


					if (Y[0] > 30) {
						EscTime += i;
						EscTime2 += i*i;
						break;
					}
					//*fout << i << " " << *Y << " " << 4 * sin(2 * 3.14 * FREQ * i * 0.001) - 40 << "\n";
				}
			}
			delete[]Y;
		}
		EscTime /= NUMAVE;
		EscTime2 /= NUMAVE;
#if defined(time_measurement)
		unsigned int end_time = clock(); // конечное время
		unsigned int search_time = end_time - start_time; // искомое время
		cout << "Measured time: " << search_time << "\n";
#endif

		*fout << dispercy << " " << EscTime << " " << sqrt(EscTime2 - EscTime*EscTime) << " " << sqrt(EscTime2 - EscTime*EscTime) / EscTime << "\n";
		dispercy *= 1.1;
	}
}

void simplelaunch(std::ofstream *fout){

	double dispercy = 0.000;
	double noise;
	double *Y = new double[4];
	FREQ = 15.5;
	SIGNAL = 4;
	setParams(SIGNAL, STEP, FREQ);
	nul(Y);
	for (double i = 0; i < TIME; i += STEP){

		//noise = newnoise();


		//Model_next_Step(V, i, STEP, FREQ, SIGNAL, (noise * sqrt(2 * dispercy * STEP)), METHOD);
		Model_next_Step(Y, i, STEP, FREQ, 0, 0);

		*fout << i << " " << *Y << "\n";
	}
	delete[]Y;

}

bool isGenerating(){

	double *Y = new double[4];
	setParams(SIGNAL, STEP, FREQ);
	nul(Y);
	for (double i = 0; i < TIME; i += STEP){

		Model_next_Step(Y, i, STEP, FREQ, 0, 0);
		if (Y[0] > 30) return true;

	}
	delete[]Y;

	return false;
}


int main(){
	ofstream fout("output.txt");

	double noise;

	ifstream fin("input.txt");

	srand(time(NULL));

	//simplelaunch(&fout);

	
	/*for (double i = 1.5; i <= 5; i += 0.1)
	{
		SIGNAL = i;
		for (double j = 5; j < 60; j += 0.5){
			FREQ = j;
			if (isGenerating()) {
				fout << i << " " << j << "\n";
				cout << i << " " << j << "\n";
				break;
			}

		}
	}*/

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

	/*for (FREQ = 20; FREQ <= 22; FREQ += 0.5){
		std::cout << "FREQ = " << FREQ << "\n";
		std::ostringstream strs;
		strs << FREQ;
		std::string str = strs.str();
		str += ".txt";
		ofstream fout(str);
		escape_time_parallel_launch(&fout);

		
	}*/


	/*FREQ = 20;
	SIGNAL = -4;
	simplelaunch(&fout);
	fout.close();*/

	while (true)  {

		fin >> SIGNAL >> FREQ;
		
		if (fin.eof()) break;

		//FREQ += 1.0;
		for (int i = 0; i < 5; i++) {
			FREQ += 0.5;
			std::cout << "FREQ = " << FREQ << "\n";
			std::ostringstream strs;
			strs << SIGNAL << "_" << FREQ;
			std::string str = strs.str();
			str += ".txt";
			ofstream fout(str);
			escape_time_parallel_launch(&fout);
		}

	}


	fout.close();
	fin.close();
	system("pause");
	return 0;
}