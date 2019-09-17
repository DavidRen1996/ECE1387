#pragma once
#include <vector>
#include "extract.h"
#include "net.h"
#include "recurs.h"
using namespace std;
struct bound{
	double x_min;
	double x_max;
	double y_min;
	double y_max;
};
class block
{
	//int k;
	extract b;
	net nb;
public:
	vector<int> get_net();
	vector<int>get_connections(int i);
	vector<int>j_connection(int j);//get all net that connects to block j
	bound get_boundary();
	block();
	~block();
};

