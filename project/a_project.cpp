//#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include  <vector>
#include <fstream>
#include"router.h"
using namespace std;
//static int t_con = 0;
struct van{
	int *grid;
	int **fifo;
	int n, l, con_num, pl, n_con, w_con, t_con;
};


van path(van f_in, int n){// z has not been used, add later
	van slv;
	slv = f_in;
	slv.t_con = f_in.t_con;
	//cout << "slv.l=" << slv.l << endl;
	//cout << slv.con_num;
	//cout << slv.fifo[0][1];
	int l_con = 0;
	//cout << "l_con=" << l_con << endl;
	//int n_con = 0;
	//int w_con = 0;
	int mark = 0;
	int loop = 1;
	int length = 1;//path number
	//int num = slv.n_con;//length of fifo
	//cout << num << endl;
	//int *arr = new int[num];//initialize the fifo
	//arr[0] = 2 * p + 2;
	//arr[1] = 2 * q;
	//for (int m = 0; m<5; m++){//m for the number of loops

	int pd = 0;
	for (int i = 0; i < slv.n_con; i = i + 2){
		if (slv.grid[slv.con_num] - 2 == slv.grid[i] && slv.grid[slv.con_num + 1] == slv.grid[i + 1]){
			pd = 1;
		}
	}
	cout << slv.grid[slv.con_num] - 2 << slv.grid[slv.con_num + 1] << endl;
	cout << "pd=" << pd << endl;
	if (slv.grid[slv.con_num] - 2 >= 0&&pd==0){//source has a swtich block on the left
			cout << "source has a swtich block on the left" << endl;

			if (slv.fifo[slv.grid[slv.con_num] - 2][slv.grid[slv.con_num + 1]] == 116){
				//cout << "con=" << slv.con_num << endl;
				//cout << slv.grid[slv.con_num];
				//cout << slv.fifo[slv.grid[slv.con_num] - 2][slv.grid[slv.con_num + 1]];
				mark = 1;
				cout << "find target left" << endl;
				slv.n = 1;
				slv.fifo[slv.grid[slv.con_num] - 1][slv.grid[slv.con_num + 1]] = slv.l;
				slv.pl = slv.fifo[slv.grid[slv.con_num] - 1][slv.grid[slv.con_num + 1]];
				return slv;
			}
			else {//not the target
				
				
			
						l_con = l_con + 1;
						slv.n_con = slv.n_con + 2;
						cout << slv.n_con << endl;
						int *fifo = new int[slv.n_con];//make one more room in the expansion list
						::memcpy(fifo, slv.grid, 4 * slv.n_con);//copy the original expansion list into fifo
						int n = sizeof(slv.grid);
						//cout << "length=" << n << endl;
						fifo[slv.n_con - 2] = slv.grid[slv.con_num] - 2;//store the new coordinate into expansion list
						fifo[slv.n_con - 1] = slv.grid[slv.con_num + 1];
						//cout << fifo[0] << endl;
						//cout << fifo[1] << endl;
						//cout << fifo[2] << endl;
						//cout << fifo[3]<<endl;
						slv.grid = fifo;
						//num = num + 2;
						//cout << num << endl;
						//cout << slv.fifo[0][1];
						if (slv.fifo[slv.grid[slv.con_num] - 1][slv.grid[slv.con_num + 1]] == 1){
							slv.fifo[slv.grid[slv.con_num] - 1][slv.grid[slv.con_num + 1]] = slv.l;//mark the path between two swtich blocks

						}
				

			}

		}

	//cout << slv.grid[slv.con_num];
	int pr = 0;
	for (int i = 0; i < slv.n_con; i = i + 2){
		if (slv.grid[slv.con_num] + 2 == slv.grid[i] && slv.grid[slv.con_num + 1] == slv.grid[i + 1]){
			pr = 1;
		}
	}
	//cout << "pr=" << pr << endl;
	if (slv.grid[slv.con_num] + 2 <= 2 * n + 1&&pr==0){//source has a swtich block on the right
			cout << "source has a swtich block on the right" << endl;
			//cout << "slv.con_num=" << slv.con_num;
			//cout << slv.fifo[slv.grid[slv.con_num] + 2][slv.grid[slv.con_num + 1]] << endl;
			if (slv.fifo[slv.grid[slv.con_num] + 2][slv.grid[slv.con_num + 1]] == 116){
				mark = 1;
				//cout << "find target right" << endl;
				slv.n = 1;
				slv.fifo[slv.grid[slv.con_num] + 1][slv.grid[slv.con_num + 1]] = slv.l;
				slv.pl = slv.fifo[slv.grid[slv.con_num] + 1][slv.grid[slv.con_num + 1]];
				return slv;//should be replaced by return
			}

			else {
				l_con = l_con + 1;
				slv.n_con = slv.n_con + 2;
				cout << slv.n_con << endl;
				int *fifo = new int[slv.n_con];
				::memcpy(fifo, slv.grid, 4 * slv.n_con);
				fifo[slv.n_con - 2] = slv.grid[slv.con_num] + 2;//store the new coordinate into expansion list
				fifo[slv.n_con - 1] = slv.grid[slv.con_num + 1];
				cout << fifo[5];
				//cout << fifo[4];
				slv.grid = fifo;
				//num = num + 2;
				//cout << num << endl;
				//cout << slv.fifo[slv.grid[slv.con_num] + 1][slv.grid[slv.con_num + 1]];
				if (slv.fifo[slv.grid[slv.con_num] + 1][slv.grid[slv.con_num + 1]] == 1){
					slv.fifo[slv.grid[slv.con_num] + 1][slv.grid[slv.con_num + 1]] = slv.l;
					//cout << slv.fifo[slv.grid[slv.con_num] + 1][slv.grid[slv.con_num + 1]] << endl;
				}
			}
		}

	int pc = 0;
	for (int i = 0; i < slv.n_con; i = i + 2){
		if (slv.grid[slv.con_num] == slv.grid[i] && slv.grid[slv.con_num + 1] + 2 == slv.grid[i + 1]){
			pc = 1;
		}
	}
	//cout << "pc=" << pc << endl;

	if (slv.grid[slv.con_num + 1] + 2 <= 2 * n + 1&&pc==0){//source has a swtich block on the above
			cout << "source has a swtich block on the above" << endl;
			//cout << slv.con_num << endl;
			//cout << slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] + 2];
			if (slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] + 2] == 116){
				//cout << slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] + 2];
				mark = 1;
				cout << "find target above" << endl;
				slv.n = 1;
				slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] + 1] = slv.l;
				slv.pl = slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] + 1];
				return slv;
			}
			else {
				l_con = l_con + 1;
				slv.n_con = slv.n_con + 2;
				//cout << slv.n_con << endl;
				int *fifo = new int[slv.n_con];
				::memcpy(fifo, slv.grid, 4 * slv.n_con);
				fifo[slv.n_con - 2] = slv.grid[slv.con_num];//store the new coordinate into expansion list
				//cout << "above x=" << fifo[num]<< endl;
				fifo[slv.n_con - 1] = slv.grid[slv.con_num + 1] + 2;
				slv.grid = fifo;
				//num = num + 2;
				//cout << num << endl;
				if (slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] + 1] == 1){
					slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] + 1] = slv.l;
					//cout <<"path coordinate="<< slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] + 1] << endl;
				}
			}
		}

	int pa = 0;
	for (int i = 0; i < slv.n_con; i = i + 2){
		if (slv.grid[slv.con_num] == slv.grid[i] && slv.grid[slv.con_num + 1] - 2 == slv.grid[i + 1]){
			pa = 1;
		}
	}
	//cout << slv.grid[slv.con_num + 1];
	if (slv.grid[slv.con_num + 1] - 2 >= 0&&pa==0){//source has a swtich block on the below
			cout << "source has a swtich block on the below" << endl;
			
			l_con = l_con + 1;
			cout << "l_con=" << l_con << endl;
			if (slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] - 2] == 116){
				mark = 1;
				cout << "find target below" << endl;
				slv.n = 1;
				slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] - 1] = slv.l;
				slv.pl = slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] - 1];//return the value of the path between slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] - 2] and source
				return slv;
			}
			else {
				slv.n_con = slv.n_con + 2;
				cout << slv.n_con << endl;
				if (slv.l == 2){
					slv.l = slv.l + 1;
					//cout << slv.l;
					//slv.n_con = l_con + 1;
					slv.w_con = l_con + 1;
					cout << "next=" << slv.w_con << endl;
					cout << "total=" << slv.t_con << endl;
				}
				else{
					//cout << num << endl;
					if (slv.con_num/2+1== slv.w_con){
						slv.t_con = l_con + slv.t_con;
						slv.w_con = slv.w_con + slv.t_con;
						cout << "next="<<slv.w_con << endl;
						//cout << t_con << endl;
						slv.t_con = 0;
						slv.l = slv.l + 1;
						cout << "length=" << slv.l << endl;
					}
					else{
						slv.t_con = l_con + slv.t_con;
						cout << "total=" << slv.t_con << endl;
					}

				}
				
				int *fifo = new int[slv.n_con];//creat new array to store the expansion numbers
				::memcpy(fifo, slv.grid, 4 * slv.n_con);
				fifo[slv.n_con - 2] = slv.grid[slv.con_num];//store the new coordinate into expansion list
				fifo[slv.n_con - 1] = slv.grid[slv.con_num + 1] - 2;
				slv.grid = fifo;
				//num = num + 2;

				if (slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] - 1] == 1){
					slv.fifo[slv.grid[slv.con_num]][slv.grid[slv.con_num + 1] - 1] = slv.l;//first surronding has no target

				}
				//slv.fifo[slv.grid[con]][slv.grid[con + 1] - 1] = length + 1;//first surronding has no target
				van r_value;
				r_value.n_con = slv.n_con;
				r_value.w_con = slv.w_con;
				r_value.con_num = slv.con_num;
				r_value.t_con = slv.t_con;
				//cout << "excute" << endl;
				r_value.l = slv.l;
				//cout << r_value.l;
				r_value.n = mark;
				r_value.fifo = slv.fifo;
				//cout << slv.fifo[0][1];
				//cout << r_value.fifo[0][1];
				r_value.grid = fifo;
				return r_value;
			}
		}
	else {
		if (slv.l == 2){
			slv.l = slv.l + 1;
			
			//slv.n_con = l_con + 1;
			slv.w_con = l_con + 1;
			//cout << slv.w_con << endl;
		}
		else{
			//cout << num << endl;
			if (slv.con_num/2+1== slv.w_con){
				slv.w_con = slv.w_con + slv.t_con;
				cout << "next=" << slv.w_con << endl;
				//cout << slv.w_con << endl;
				slv.t_con = 0;
				slv.l = slv.l + 1;
				cout << "length=" << slv.l << endl;
			}
			else{
				slv.t_con = l_con + slv.t_con;
				cout << "total=" << slv.t_con << endl;
			}

		}





		int *fifo = new int[slv.n_con];//creat new array to store the expansion numbers
		::memcpy(fifo, slv.grid, 4 * slv.n_con);
		        van r_value;
				r_value.con_num = slv.con_num;
				r_value.t_con = slv.t_con;
				r_value.n_con = slv.n_con;
				r_value.w_con = slv.w_con;
				//cout << "excute" << endl;
				r_value.l = slv.l;
				//cout << r_value.l;
				r_value.n = mark;
				r_value.fifo = slv.fifo;
				//cout << slv.fifo[0][1];
				//cout << r_value.fifo[0][1];
				r_value.grid = slv.grid;
				return r_value;
	}




	//	}



}