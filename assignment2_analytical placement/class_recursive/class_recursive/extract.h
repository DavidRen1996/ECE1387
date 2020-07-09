#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
struct vec_rec{
	vector<double>a;//total data
	vector<double> fixed;//fixed blocks' data
	int totoal_nets;//otal nets
	int total_numbers;//total file length
	int fixed_numbers;//number of fixed blocks data c1=15
	int start;
};
struct xy{
	vector<double>x;
	vector<double>y;
};
class extract
{
private:

public:
	//int f_size;
	extract();
	~extract();
	vector<int> get_net();//get  all moveable blocks in the circuit
	vec_rec recv();//get all contents
	vector<double> fixed();//return a vector with only fixed block number
	xy get_cfile();
	vector<vector<int>>advanced_return();
};

