//#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include  <vector>
#include <fstream>
#include"router.h"
using namespace std;
//static int t_con = 0;
struct path{
	int *grid;
	int **fifo;
	int n, l, con_num, pl, n_con, w_con, t_con;
};


path pathRender(path f_in, int n){// z has not been used, add later
	path tempPath;
	tempPath = f_in;
	tempPath.t_con = f_in.t_con;
	int l_con = 0;
	int mark = 0;
	int loop = 1;
	int length = 1;//path number

	int pd = 0;
	for (int i = 0; i < tempPath.n_con; i = i + 2){
		if (tempPath.grid[tempPath.con_num] - 2 == tempPath.grid[i] && tempPath.grid[tempPath.con_num + 1] == tempPath.grid[i + 1]){
			pd = 1;
		}
	}
	if (tempPath.grid[tempPath.con_num] - 2 >= 0&&pd==0){//source has a swtich block on the left
			cout << "source has a swtich block on the left" << endl;
			if (tempPath.fifo[tempPath.grid[tempPath.con_num] - 2][tempPath.grid[tempPath.con_num + 1]] == 116){
				mark = 1;
				cout << "find target left" << endl;
				tempPath.n = 1;
				tempPath.fifo[tempPath.grid[tempPath.con_num] - 1][tempPath.grid[tempPath.con_num + 1]] = tempPath.l;
				tempPath.pl = tempPath.fifo[tempPath.grid[tempPath.con_num] - 1][tempPath.grid[tempPath.con_num + 1]];
				return tempPath;
			}
			else {//not the target
						l_con = l_con + 1;
						tempPath.n_con = tempPath.n_con + 2;
						cout << tempPath.n_con << endl;
						int *fifo = new int[tempPath.n_con];//make one more room in the expansion list
						::memcpy(fifo, tempPath.grid, 4 * tempPath.n_con);//copy the original expansion list into fifo
						int n = sizeof(tempPath.grid);
						//cout << "length=" << n << endl;
						fifo[tempPath.n_con - 2] = tempPath.grid[tempPath.con_num] - 2;//store the new coordinate into expansion list
						fifo[tempPath.n_con - 1] = tempPath.grid[tempPath.con_num + 1];
					
						tempPath.grid = fifo;
						if (tempPath.fifo[tempPath.grid[tempPath.con_num] - 1][tempPath.grid[tempPath.con_num + 1]] == 1){
							tempPath.fifo[tempPath.grid[tempPath.con_num] - 1][tempPath.grid[tempPath.con_num + 1]] = tempPath.l;//mark the path between two swtich blocks
						}
			}

		}
	int pr = 0;
	for (int i = 0; i < tempPath.n_con; i = i + 2){
		if (tempPath.grid[tempPath.con_num] + 2 == tempPath.grid[i] && tempPath.grid[tempPath.con_num + 1] == tempPath.grid[i + 1]){
			pr = 1;
		}
	}
	if (tempPath.grid[tempPath.con_num] + 2 <= 2 * n + 1&&pr==0){//source has a swtich block on the right
			cout << "source has a swtich block on the right" << endl;
			if (tempPath.fifo[tempPath.grid[tempPath.con_num] + 2][tempPath.grid[tempPath.con_num + 1]] == 116){
				mark = 1;
				tempPath.n = 1;
				tempPath.fifo[tempPath.grid[tempPath.con_num] + 1][tempPath.grid[tempPath.con_num + 1]] = tempPath.l;
				tempPath.pl = tempPath.fifo[tempPath.grid[tempPath.con_num] + 1][tempPath.grid[tempPath.con_num + 1]];
				return tempPath;//should be replaced by return
			}

			else {
				l_con = l_con + 1;
				tempPath.n_con = tempPath.n_con + 2;
				cout << tempPath.n_con << endl;
				int *fifo = new int[tempPath.n_con];
				::memcpy(fifo, tempPath.grid, 4 * tempPath.n_con);
				fifo[tempPath.n_con - 2] = tempPath.grid[tempPath.con_num] + 2;//store the new coordinate into expansion list
				fifo[tempPath.n_con - 1] = tempPath.grid[tempPath.con_num + 1];
				tempPath.grid = fifo;
				if (tempPath.fifo[tempPath.grid[tempPath.con_num] + 1][tempPath.grid[tempPath.con_num + 1]] == 1){
					tempPath.fifo[tempPath.grid[tempPath.con_num] + 1][tempPath.grid[tempPath.con_num + 1]] = tempPath.l;
				}
			}
		}

	int pc = 0;
	for (int i = 0; i < tempPath.n_con; i = i + 2){
		if (tempPath.grid[tempPath.con_num] == tempPath.grid[i] && tempPath.grid[tempPath.con_num + 1] + 2 == tempPath.grid[i + 1]){
			pc = 1;
		}
	}

	if (tempPath.grid[tempPath.con_num + 1] + 2 <= 2 * n + 1&&pc==0){//source has a swtich block on the above
			cout << "source has a swtich block on the above" << endl;
			if (tempPath.fifo[tempPath.grid[tempPath.con_num]][tempPath.grid[tempPath.con_num + 1] + 2] == 116){
				//cout << slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] + 2];
				mark = 1;
				cout << "find target above" << endl;
				tempPath.n = 1;
				tempPath.fifo[tempPath.grid[tempPath.con_num]][tempPath.grid[tempPath.con_num + 1] + 1] = tempPath.l;
				tempPath.pl = tempPath.fifo[tempPath.grid[tempPath.con_num]][tempPath.grid[tempPath.con_num + 1] + 1];
				return tempPath;
			}
			else {
				l_con = l_con + 1;
				tempPath.n_con = tempPath.n_con + 2;
				//cout << slv.n_con << endl;
				int *fifo = new int[tempPath.n_con];
				::memcpy(fifo, tempPath.grid, 4 * tempPath.n_con);
				fifo[tempPath.n_con - 2] = tempPath.grid[tempPath.con_num];//store the new coordinate into expansion list
				fifo[tempPath.n_con - 1] = tempPath.grid[tempPath.con_num + 1] + 2;
				tempPath.grid = fifo;
				if (tempPath.fifo[tempPath.grid[tempPath.con_num]][tempPath.grid[tempPath.con_num + 1] + 1] == 1){
					tempPath.fifo[tempPath.grid[tempPath.con_num]][tempPath.grid[tempPath.con_num + 1] + 1] = tempPath.l;
				}
			}
		}

	int pa = 0;
	for (int i = 0; i < tempPath.n_con; i = i + 2){
		if (tempPath.grid[tempPath.con_num] == tempPath.grid[i] && tempPath.grid[tempPath.con_num + 1] - 2 == tempPath.grid[i + 1]){
			pa = 1;
		}
	}
	//cout << slv.grid[slv.con_num + 1];
	if (tempPath.grid[tempPath.con_num + 1] - 2 >= 0&&pa==0){//source has a swtich block on the below
			cout << "source has a swtich block on the below" << endl;
			
			l_con = l_con + 1;
			cout << "l_con=" << l_con << endl;
			if (tempPath.fifo[tempPath.grid[tempPath.con_num]][tempPath.grid[tempPath.con_num + 1] - 2] == 116){
				mark = 1;
				cout << "find target below" << endl;
				tempPath.n = 1;
				tempPath.fifo[tempPath.grid[tempPath.con_num]][tempPath.grid[tempPath.con_num + 1] - 1] = tempPath.l;
				tempPath.pl = tempPath.fifo[tempPath.grid[tempPath.con_num]][tempPath.grid[tempPath.con_num + 1] - 1];//return the value of the path between slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] - 2] and source
				return tempPath;
			}
			else {
				tempPath.n_con = tempPath.n_con + 2;
				cout << tempPath.n_con << endl;
				if (tempPath.l == 2){
					tempPath.l = tempPath.l + 1;
					tempPath.w_con = l_con + 1;
					cout << "next=" << tempPath.w_con << endl;
					cout << "total=" << tempPath.t_con << endl;
				}
				else{
					//cout << num << endl;
					if (tempPath.con_num/2+1== tempPath.w_con){
						tempPath.t_con = l_con + tempPath.t_con;
						tempPath.w_con = tempPath.w_con + tempPath.t_con;
						cout << "next="<<tempPath.w_con << endl;
						tempPath.t_con = 0;
						tempPath.l = tempPath.l + 1;
						cout << "length=" << tempPath.l << endl;
					}
					else{
						tempPath.t_con = l_con + tempPath.t_con;
						cout << "total=" << tempPath.t_con << endl;
					}

				}
				
				int *fifo = new int[tempPath.n_con];//creat new array to store the expansion numbers
				::memcpy(fifo, tempPath.grid, 4 * tempPath.n_con);
				fifo[tempPath.n_con - 2] = tempPath.grid[tempPath.con_num];//store the new coordinate into expansion list
				fifo[tempPath.n_con - 1] = tempPath.grid[tempPath.con_num + 1] - 2;
				tempPath.grid = fifo;
				//num = num + 2;

				if (tempPath.fifo[tempPath.grid[tempPath.con_num]][tempPath.grid[tempPath.con_num + 1] - 1] == 1){
					tempPath.fifo[tempPath.grid[tempPath.con_num]][tempPath.grid[tempPath.con_num + 1] - 1] = tempPath.l;//first surronding has no target

				}
				path r_value;
				r_value.n_con = tempPath.n_con;
				r_value.w_con = tempPath.w_con;
				r_value.con_num = tempPath.con_num;
				r_value.t_con = tempPath.t_con;

				r_value.l = tempPath.l;
				r_value.n = mark;
				r_value.fifo = tempPath.fifo;
				r_value.grid = fifo;
				return r_value;
			}
		}
	else {
		if (tempPath.l == 2){
			tempPath.l = tempPath.l + 1;
			tempPath.w_con = l_con + 1;
		}
		else{
			if (tempPath.con_num/2+1== tempPath.w_con){
				tempPath.w_con = tempPath.w_con + tempPath.t_con;
				cout << "next=" << tempPath.w_con << endl;
				tempPath.t_con = 0;
				tempPath.l = tempPath.l + 1;
				cout << "length=" << tempPath.l << endl;
			}
			else{
				tempPath.t_con = l_con + tempPath.t_con;
				cout << "total=" << tempPath.t_con << endl;
			}

		}

		int *fifo = new int[tempPath.n_con];//creat new array to store the expansion numbers
		::memcpy(fifo, tempPath.grid, 4 * tempPath.n_con);
		        path r_value;
				r_value.con_num = tempPath.con_num;
				r_value.t_con = tempPath.t_con;
				r_value.n_con = tempPath.n_con;
				r_value.w_con = tempPath.w_con;

				r_value.l = tempPath.l;
				r_value.n = mark;
				r_value.fifo = tempPath.fifo;
				r_value.grid = tempPath.grid;
				return r_value;
	}


}