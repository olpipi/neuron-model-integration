#include "model.h"
#include "Runge_Kutta.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime> 
#include <omp.h>
#include <random>

using namespace std;

#define TIME 120		//����� �������������

#define NUMAVE 50000	//���������� �������� ��� ����������
double FREQ = 140;		//������� ��������������� �������
double SIGNAL = -4;		//������� ������� (0 - ��� �������; <0 - �����; >0 - DC, ������ ��������);
double STEP = 0.01; 	//��� �� �������. 0.001 = 1 ������������
int METHOD = 1;			// ����� ��������������. 1 = ����. 2 = �����. 3 = �����-�����

void nul(double *V){	// ��������� ���������� �������
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



double newnoise(){	//��������� �������� ����
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
				double *Y = new double[4];
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
		//unsigned int end_time = clock(); // �������� �����
		//unsigned int search_time = end_time - start_time; // ������� �����

		*fout << dispercy << " " << EscTime << " " << sqrt(EscTime2 - EscTime*EscTime) << " " << sqrt(EscTime2 - EscTime*EscTime) / EscTime << "\n";
		dispercy *= 1.1;
	}
}


int main(){
	ofstream fout("output.txt");

	double noise;

	//	ifstream fin("input.txt");

	srand(time(NULL));

	//	simplelaunch(&fout);
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

	for (FREQ = 120; FREQ <= 140; FREQ += 20){
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