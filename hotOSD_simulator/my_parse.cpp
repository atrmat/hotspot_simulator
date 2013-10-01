#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;

/*
@in, src: 待分割的字符串
@in, delim: 分隔符字符串
@in_out, dest: 保存分割后的每个字符串
*/
int osdNum = -1;
int objectID = 0;
int visitObject[10250] = {0};
int primaryOSD[10250] = {0};
int hotOSDList[10250] = {0};
char tmp[100];
/*
void split(const string& src, const string& delim, vector<string>& dest)
{
	string str = src;
	string::size_type start = 0, index;
	string substr;
	osdNum = -1;
	index = str.find_first_of(delim, start);	//在str中查找(起始：start) delim的任意字符的第一次出现的位置
	while(index != string::npos)
	{
		substr = str.substr(start, index-start);
		dest.push_back(substr);
		if(++osdNum == 1 ){// the first osd is visited
			char temp[20];
			strncpy(temp,substr.c_str(),substr.length());
			cout<< atoi(temp) <<" "<< substr << endl;	
		}
		start = str.find_first_not_of(delim, index);	//在str中查找(起始：index) 第一个不属于delim的字符出现的位置
		if(start == string::npos) {
			return;
		}
		index = str.find_first_of(delim, start);
	}
	index = str.find_first_of("\n", start);
	substr = str.substr(start, index-start);
	dest.push_back(substr);
}
*/
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
			strncpy(tmp,textline0.c_str(),textline0.length());
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
				primaryOSD[i++]= atoi(tmp);
				//cout << primaryOSD[i] << endl;
			}
		}
	}
	cout << "i: "<<--i<<endl;
	infile.close();
	for (int j = 0; j < i; j++){
//		cout << visitObject[j] << endl;
		hotOSDList[primaryOSD[j]] += visitObject[j];
		//cout << "obj " << j << " put in primary OSD: " << primaryOSD[j]<<endl;
	}
	
	ofstream outf;
	outf.open("hotOSD.result.csv");
	for (int j = 0; j < atoi(argv[1]); j++){
		outf << hotOSDList[j]<<endl;
	}
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
