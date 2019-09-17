// test.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int length(){
	char buffer[256];
	int i;
	ifstream infile;
	infile.open("circuit.txt");
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
