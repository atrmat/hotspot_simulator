#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
double gaussrand()
{
	static double V1, V2, S;
	static int phase = 0;
	double X;

	if ( phase == 0 ) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while(S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	} else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return X;
}
int main(int argc, char* argv[])
{
/*
	if(argc < 3){
		cout << "no enough args! argv[1] is the [num],range from argv[2] to argv[3], argv[4] is the [output file name]" << endl;
		return -1;
	}
*/	cout <<	gaussrand()<<endl;
	return 0;
}
