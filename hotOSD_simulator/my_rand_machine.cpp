#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
using namespace std;
const double PI=3.141592654;
double AverageRandom(double min,double max)
{
	int minInteger = (int)(min*10000);
	int maxInteger = (int)(max*10000);
	int randInteger = rand()*rand();
	int diffInteger = abs(maxInteger - minInteger);
	int resultInteger = 0;
	if (0 != diffInteger){
		int resultInteger = randInteger % diffInteger + minInteger;
		return abs(resultInteger/10000.0);
	}
	return minInteger;
}
double Normal(double x, double miu, double sigma)
{
	return 1.0/sqrt(2*PI*sigma)*exp(-1*(x-miu)*(x-miu)/(2*sigma*sigma));
}
double NormalRandom(double miu, double sigma, double min, double max)
{
	double x;
	double y;
	double dScore = 0.0;
	do{
		x = AverageRandom(min, max); 
		y = Normal(x, miu, sigma);
		dScore = AverageRandom(0, Normal(miu, miu, sigma));
	}while(dScore > y);
	return x;
}
int main(int argc, char * argv[])
{
	time_t t;
	int tmp = 0;
	srand((unsigned) time(&t));
	if(argc < 3){
		cout << "no enough args! argv[1] is the [num],range from argv[2] to argv[3], argv[4] is the [output file name]" << endl;
		return -1;
	}
	ofstream outf;
	outf.open(argv[4]);
	int min = 0, max = 0;
	min = atoi(argv[2]);
	max = atoi(argv[3]);
	int avg = (max+min)/2;
	//outf.open("hotspot.txt");
	for (int i =1 ;i <= atoi(argv[1]); i++){
		//tmp = NormalRandom(-(i-avg)*(i-avg)+max*max,1,min,avg);
		tmp = NormalRandom(abs(max + min)/2,1,min,max);
		cout << tmp << endl;
		outf << tmp << endl;
		//outf << tmp << "," << endl;
	}
	outf.close();
	return 0;
}
