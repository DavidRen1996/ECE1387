// w.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include  <vector>
#include <fstream>
using namespace std;
int length();
int main()
{
	int m=0;
	double num[3000];
	ifstream file;
	file.open("C:\\Users\\ThinkPad\\Desktop\\circuit.txt");
	while (!file.eof())
	{
		file >> num[m++];
	}
	int n = num[1];
	cout << num[1] << endl;
	int *cont = new int[n];
	for (int i = 0; i < n; i++){
		cont[i] = 0;
	}
	int line_num = length();
	cout << line_num<< endl;
	int mini_w=0;
	for (int f = 0; f < line_num-5; f++){
		int mark = 0;
		for (int k = 0; k < n; k++){
			if (cont[k] == num[7 + 6 * f]){
				//cont[k] = num[7 + 6 * f];
				//cout << num[7 + 6 * f] << endl;
				mark = 0;
				//cout << mark << endl;
				
			}
			else{
				mark = mark+1;
				//cout << mark << endl;
				
			}
		}
		
		if (mark == n){
			cont[mini_w] = num[7 + 6 * f];
			cout << "w="<<cont[mini_w] << endl;
			mini_w = mini_w + 1;
			//cout << mini_w << endl;
		}
		
	}
	cout << mini_w << endl;
	system("pause");
	return 0;
}

int length(){
	char buffer[256];
	int i;
	ifstream infile;
	infile.open("C:\\Users\\ThinkPad\\Desktop\\circuit.txt");
	if (!infile.is_open())
	{
		cout << "cannot open";
	}
	//infile.getline(buffer, 100);
	//cout << buffer[0] << endl;
	while (!infile.eof()){
		for (i = 1; buffer[0] != '-'; i++)
			infile.getline(buffer, 20);

	}
	return i;
	infile.close();
}

//cout << num[7 + 6 * f] << endl;

//cout << mini_w << endl;
//continue;