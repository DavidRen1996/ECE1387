#pragma once
//#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "file_extract.h"
#include "extern.h"
#include "branching.h"
#include "calculator.h"
#include "draw_graph.h"
using namespace std;
struct r{
	map<int, map<int, vector<int>>>*x1; 
	map<int, vector<int>>*x2; 
	map<int, vector<int>>*results;
	int n;
	int b; 
	int signal;
	int set;
	int count;
};
class low_bound_first
{
	calculator c_sample;
	draw_graph DG;
public:
	low_bound_first();
	~low_bound_first();
	void lbf();
	r lbf_recur(map<int, map<int, vector<int>>>*x1, map<int, vector<int>>*x2, map<int, vector<int>>*results, int n, int b,int signal,int count,int set);
};

