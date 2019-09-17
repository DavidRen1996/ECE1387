//#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "extract.h"
using namespace std;

extract::extract()
{


};


extract::~extract()
{
}

vec_rec extract::recv(){//get all contents
	vector<double> a;//creat vector to reveive data
	vector<double> fixed;
	ifstream file;
	file.open("c1.txt");//open file
	while (!file.eof())
	{
		double n;//varaible to receive data
		file >> n;
		//cout << n;
		a.push_back(n);
	}
	int v_size = a.size();//size of the whole file
	int n = 0;
	int f_start = 0;
	for (n = 0; n < v_size; n++){//locate the start of fix pins
		if (a[n] == -1){
			if (a[n + 1] == -1){
				f_start = n + 2;
				break;
			}
		}
	}
	for (n = f_start; n < v_size - 1; n++){//put fixed pins data into fixed vector
		double i = a[n];
		fixed.push_back(i);
	}
	int f_size = fixed.size();
	vector<int>nodes;
	for (int m = 0; m < f_size; m = m + 3){//get the nodes that are fixed
		nodes.push_back(fixed[m]);
	}
	//calculate the number of total nets
	int net_num = 0;//number of nets
	for (int i = 2; i < f_start - 2; i++){//count stop at the beginning of fixed blocks
		if (a[i] == -1){//end of a line
			i = i + 2;
			//cout << "next line begins" << a[i+1] << endl;
			continue;
		}
		else{
			if (a[i] >= net_num){
				net_num = a[i];
			}
		}
	}
	vec_rec van;
	van.a = a;
	van.fixed = fixed;
	van.totoal_nets = net_num;
	van.total_numbers = v_size;
	van.fixed_numbers = f_size;
	van.start = f_start;
	//cout << "net number is" << net_num << endl;
	//cout << fixed[1] << endl;
	//cout << f_size << "van" << endl;
	//cout << v_size << "van" << endl;
	return van;
}
vector<int> extract::get_net(){//get  all moveable blocks in the circuit
	extern vec_rec rec_val;
	vec_rec vans = rec_val;

	vector<int>connection;
	//vector<int>j_connection;
	vector<double>f = fixed();
	int fix_size = f.size();
	//cout << fix_size << endl;
	int count = 0;
	for (int x = 0; x <vans.total_numbers; x++){

		if (vans.a[x] == -1){
			if (vans.a[x + 1] == -1){//end of moveable
				break;
			}
			else{
				count = count + 1;//line + 1
				if (count >= fix_size){
					connection.push_back(vans.a[x + 1]);//store moveable block
					/*int i = x + 3;
					while (vans.a[i]!=-1){
					j_connection.push_back(vans.a[i]);
					i++;
					}*/
				}
			}
		}
	}
	/*for (int f = 0; f < connection.size(); f++){
	cout << connection[f];
	}
	cout << "total finish"<<endl;
	/*for (int y = 0; y < j_connection.size(); y++){
	cout << j_connection[y];
	}*/

	return connection;
}
vector<double> extract::fixed(){//return a vector with only fixed block number
	extern vec_rec rec_val;
	vec_rec vans = rec_val;
	vector<double>fix;
	int n = vans.fixed.size();
	for (int i = 0; i < n; i = i + 3){
		fix.push_back(vans.fixed[i]);
	}
	//cout << "content fix" << fix[0] << fix[1] << fix.back() << endl;
	return fix;
}
xy extract::get_cfile(){
	vector<double>x_co;
	vector<double>y_co;
	int c0 = 0;
	ifstream inputfile;
	inputfile.open("coordinate.txt");
	while (!inputfile.eof()){
		double n = 0;
		inputfile >> n;
		if (c0 < 15){
			x_co.push_back(n);
		}
		else {
			y_co.push_back(n);
		}
		c0 = c0 + 1;
	}
	xy vans;
    vans.x=x_co;
	vans.y=y_co;
	return vans;
}
vector<vector<int>>extract::advanced_return(){
	extern vec_rec rec_val;
	vector<vector<int>>ar;
	//int alength = rec_val.a.size();
	int v_row;//row number of vector
	for (int i = rec_val.start-3; i > 0; i--){
		if (rec_val.a[i] == -1){
			v_row = rec_val.a[i + 1];
			break;
		}
	}
	ar.resize(v_row);//v_row rows
	//cout << v_row;
	int count = 0;
	for (int c = 0; c < v_row; c++){//store data to each line in vector
		
			for (int x = 0; x < 30; x++){
				if (rec_val.a[count] == -1){
					count = count + 1;
					break;
				}
				else{
					ar[c].push_back(rec_val.a[count]);
					count = count + 1;
				}
				
			}
	}
	return ar;
}
	
	
