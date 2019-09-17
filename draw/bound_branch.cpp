// bound_branch.cpp : 定义控制台应用程序的入口点。
//

#include "stdio.h"
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
#include "low_bound_first.h"
#include "graphics.h" 
#include <math.h>
using namespace std;

int main()
{
	
	printf("About to start graphics.\n");
	init_graphics("Some Example Graphics", WHITE);

	/* still picture drawing allows user to zoom, etc. */
	// Set-up coordinates from (xl,ytop) = (0,0) to 
	// (xr,ybot) = (1000,1000)
	init_world(0., 0., 1000., 1000.);
	update_message("Interactive graphics example.");
	file_extract x;
	map<int, vector<int>>cost;
	
	cost = x.get_connection();
	cout << cost.size() << endl;
	for (int i = 0; i < cost.size(); i++){
		vector<int>y = cost[i];
		for (int c = 0; c < y.size(); c++){
			if (c == y.size()-1){
				cout << y[c] << endl;
			}
			else{
				cout << y[c];
			}
		}
	}
	branching a;
	vector<int>q = a.initial_partition();
	final_val ivan = a.branch_result();
	for (int x = 0; x < q.size(); x++){
		cout << q[x] << endl;
	}
	
	/*low_bound_first l;
	l.lbf();*/
	//vector<int>sample = {1,1,2,2,3,0};
	//calculator C;
	//int c = C.cost_increase(sample, 4);
	//cout << "increase is " << c << endl;
	//final_val d = a.branch_result();
	//cout << "best is" << d.best << endl;
	/*map<int, vector<int>>xtest;
	cout << xtest.size() << endl;
	vector<int>y = { 1, 2, 3, 4 };
	xtest[1] = y;
	xtest[0] = y;
	cout << xtest.size();
	xtest.erase(1);
	cout << xtest.size();
	xtest[1] = y;
	cout << xtest.size();*/
	/*map<int, map<int, vector<int>>>x;
	map<int, vector<int>>y;
	map<int, vector<int>>ytest;
	vector<int>z;
	vector<int>x_test = { 1 };
	x[0] = ytest;
	x[1] = y;
	y[0] = x_test;
	cout << "x size before erase"<<x.size() << endl;
	y.erase(0);
	cout << "x size after erase" << x.size() << endl;*/
	/*vector<int>x(20, 40);
	cout << "x size before swap " << x.size() << endl;
	vector<int>().swap(x);
	cout << "x size after swap " << x.size() << endl;*/
	/*map<int, map<int, vector<int>>>*x;
	map<int, map<int, vector<int>>>y;
	map<int, vector<int>>z;
	y[0] = z;
	x = &y;
	
	cout << (*x).size() << endl;
	cout << (x[0]).size() << endl;
	//cout << x.size() << endl;*/
	//system("pause");
	return 0;
}

