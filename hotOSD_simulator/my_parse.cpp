#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;
#define N 10250
int osdNum = -1;
int visitObject[N] = {0};
int primaryOSD[N] = {0};
double hotOSDList[N] = {0};
char tmp[100];
int main(int argc, char* argv[])
{
	if(argc < 2){
		cout<<"no enough args! argv[1] is the [osd num]"<<endl;
		return -1;
	}
	if(atoi(argv[1]) <= 0){
		cout << "argv[1] is the osd num, should be > 0!"<<endl;
		return -1;
	}
	ifstream hotspot("hotspot.txt", ios::in);
	vector<string> hotspots;
	string textline0;
	int i = 0;
	if(hotspot.good())
	{
		while(!hotspot.fail()&&!hotspot.eof())
		{
			getline(hotspot, textline0);
			//split(textline0, delim0, hotspots);
			strcpy(tmp,textline0.c_str());
			//strncpy(tmp,textline0.c_str(),textline0.length());
			visitObject[i] = atoi(tmp);
			//visitObject[i] = abs(atoi(tmp));
			//cout << visitObject[i] << endl;
			i++;
		}
	}
	visitObject[i--] = 0;
	//cout << "i: "<< i <<endl;
	hotspot.close();
/*
	vector<string>::iterator iter0 = hotspots.begin();
	while(iter0 != hotspots.end())
	{
		cout<<*iter0++<<endl;
	}
*/	
	ifstream infile("data-placement_information.csv", ios::in);
	vector<string> results;
	string word;
	string delim(",");
	string textline;
	string priOSD;
	string::size_type start = 0,index;
	i = 0;
	if(infile.good())
	{
		while(!infile.fail())
		{
			getline(infile, textline);
			//split(textline, delim, results);
			index = textline.find_first_of(delim,0);
			if(index != string::npos){
				start = textline.find_first_not_of(delim, index);
				index = textline.find_first_of(delim,start);

				priOSD = textline.substr(start, index-start);
				//cout << primaryOSD << endl;
				strcpy(tmp,priOSD.c_str());// why strncpy is wrong?
				//cout << tmp<<endl;
				primaryOSD[i++]= atoi(tmp)%atoi(argv[1]);
				//cout << primaryOSD[i] << endl;
			}
		}
	}
	i--;
	cout << "i: "<<i--<<endl;
	infile.close();
	//debug	
	ofstream outf2;
	outf2.open("visitObject.csv");
	double count[N] = {0};
	int hotNum = 0;
	for (int j = 0; j < i; j++){
		if (visitObject[j]%11 == 0)
			count[visitObject[j]] = abs(visitObject[j]*rand());
	}
	outf2<<"obj,pv"<<endl;
	for (int j = 0; j < i; j++){
		outf2<<j<<","<<count[j]<<endl;
		if (count[j] != 0){
			hotNum ++;
		}
	}
	outf2<<"total object: "<<i<<" "<<" hot object: "<<hotNum<<" "<<((double)hotNum/i)<<"%"<<endl;
	outf2.close();
	hotNum = 0;
	for (int j = 0; j < i; j++){
//		cout << visitObject[j] << endl;
		cout << "obj " << visitObject[j] << endl; 
		hotOSDList[primaryOSD[visitObject[j]]] += count[visitObject[j]];
		//hotOSDList[primaryOSD[visitObject[j]]] += visitObject[j]*visitObject[j];
		cout << " put in primary OSD: " << primaryOSD[visitObject[j]]<<endl;
	}
	
	ofstream outf;
	outf.open("hotOSD.csv");
	outf<< "OSD,pv"<<endl;
	for (int j = 0; j < atoi(argv[1]); j++){
		outf <<j<<","<<hotOSDList[j]<<endl;
		if (hotOSDList[j] != 0){
			hotNum ++;
		}
	}
	outf<<"total OSD: "<<atoi(argv[1])<<" "<<"hot OSD: "<<hotNum<<endl;
	outf.close();


/*
	vector<string>::iterator iter = results.begin();
	while(iter != results.end())
	{
		cout<<*iter++<<endl;
	}
*/
	return 0;
}
