// class_recursive.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "recurs.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "extract.h"
#include"net.h"
#include "block.h"
#include "create_matrix.h"
using namespace std;


int main()
{
	/*extern vec_rec rec_val;
	cout << rec_val.total_numbers << endl;*/
	create_matrix vans;
	//vector<double>x = vans.get_q(38);
	/*for (int i = 16; i < 50; i++){
		vector<double>x = vans.get_q(i);
		cout << "i=" << i << endl;
	}*/
	//vector<double>line_t=vans.get_q(22);
	//extern vector<vector<int>>ad;
	//cout << ad[99][6];
	//double w = vans.gsum(23, 4);
	//cout << w;
	vans.get_file();
	/*extract van;
	vector<vector<int>>i=van.advanced_return();
	cout << i[99][10];*/
	/*block van;
	vector<int>o = van.j_connection(1);
	cout << o[5];*/
	system("pause");
	return 0;
}

