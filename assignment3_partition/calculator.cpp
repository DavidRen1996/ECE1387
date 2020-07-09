//#include "stdafx.h"
#include "calculator.h"


calculator::calculator()
{
}


calculator::~calculator()
{
}
int calculator::getc_cost(int b1, int b2){//b1, b2 are blocks to calculate
	extern map<int, vector<int>>order;
	vector<int>b = order[b1];
	int r_value = b[b2];
	return r_value;
}
int calculator::cost_increase(vector<int>x,int n){//n is the location of newly added value in vector
	extern content file_reclaim;
	extern map<int, vector<int>>order;
	extern vector<int>branching_o;
	int cost_increase = 0;
	for (int i = 0; i < n; i++){
		int new_cost = 0;
		if (x[i] == x[n]){
			new_cost = 0;
			//cout << "match" << endl;
		}
		else{
			new_cost = getc_cost(branching_o[n], branching_o[i]);
			cost_increase = cost_increase + new_cost;
		}
		
	}
	return cost_increase;
}