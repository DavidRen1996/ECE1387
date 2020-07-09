#pragma once
#include <vector>
#include "recurs.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "extract.h"
#include "net.h"
#include "block.h"

using namespace std;
struct linear_parameter{
	int m;
	int n;
	vector<int>Ap;
	vector<int>Ai;
	vector<double>Ax;
	//vector<double>b;
};
class spread;
class create_matrix
{
	
	extract c;
	net ba;
	block bbc;
	spread *sm;
public:
	create_matrix();
	~create_matrix();
	void get_file();
	vector<vector<double>> matrix_calculation();
	vector<double> get_q(int i);//i=0,1
	vector<int>get_connections(int i, vector<int>neti);//i=0,1..
	double gsum(int x, int y);//x=row ,6,7,8... y=column 6,7,8...
	vector<double> get_b(int x_y);
	linear_parameter create_matrix::mat(vector<vector<double>>Atest, vector<double>B_test);
};

