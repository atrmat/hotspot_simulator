#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
using namespace std;
const double PI=3.141592654;
double Normal(double x, double miu, double sigma)
{
	return 1.0/sqrt(2*PI*sigma)*exp(-1*(x-miu)*(x-miu)/(2*sigma*sigma));
}
int DoubleToInt(double dValue)
{
  if(dValue < 0.0)
     return static_cast<int>(dValue - 0.5);
  else
     return static_cast<int>(dValue + 0.5);
 
  return 0;
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
	for (int i =1 ;i <= atoi(argv[1]); i++){
		//outf << (int)(Normal(i,avg,1)*10240)<<"," << endl;
		outf << Normal(i,avg,1) << endl;
	}
	outf.close();
	return 0;
}
