#pragma once
//#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "extern.h"

struct final_val{
	vector<int>partition_result;
	int best;
};
class calculator;
class draw_graph;
class branching
{
	draw_graph *DDG;
	calculator *C;
public:
	branching();
	~branching();
	vector<int>fanout_calculation();//calculate fanout of each block
	vector<int>initial_partition();//get initial best 
	//int getc_cost(int b1, int b2);//calculate cut size for a solution or partial solution
	final_val branch_result();
	final_val branching_recursion(map<int, map<int, vector<int>>>x1,int n,int b,vector<int>v1);


};

