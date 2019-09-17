#include "stdafx.h"
#include "block.h"


block::block()
{

}


block::~block()
{
}
vector<int> block::get_net(){//get  all moveable blocks in the circuit
	extern vec_rec rec_val;
	vec_rec vans = rec_val;
	vector<int>connection;
	//vector<int>j_connection;
	extern vector<double>fget;
	vector<double>f = fget;
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
vector<int>block::get_connections(int i){// get connection between block i and the rest of the circuit, i=0,1....
	//vec_rec g_recv = b.recv();// get circuit info
	vector<int>g_connection;//return
	extern vector<int> nget;
	vector<int>netl = nget;//get  all moveable blocks in the circuit
	vector<int>neti = j_connection(netl[i]);//get all net that connects to block i
	int i_size = neti.size();
	int n = netl.size();
	for (int k = 0; k < n; k++){
		if (netl[k] == netl[i]){//find itself
			continue;
		}
		else{
			vector<int>g = j_connection(netl[k]);//get all net that connects to block j
			int g_size = g.size();
			int set = 0;
			for (int b = 0; b < g_size; b++){
				for (int c = 0; c < i_size; c++){
					if (g[b] == neti[c]){//match connection
						g_connection.push_back(netl[k]);

						set = 1;
						break;
					}
				}
				if (set == 1){
					break;
				}
			}
		}
	}
	/*//get fixed connection
	vector<double>f = fixed();
	cout << f[4] << endl;
	int f_size = f.size();
	cout << "size = " << f_size << endl;
	for (int x = 0; x < f_size; x++){
	cout << "x=" << x << endl;
	vector<int>f_rec = j_connection(f[x]);//get all net that connects to block j
	int F = f_rec.size();
	cout << F;
	cout << "start" << endl;
	for (int d = 0; d < F; d++){
	cout << f_rec[d] << endl;
	}

	int set = 0;
	for (int b = 0; b < F; b++){
	for (int c = 0; c < i_size; c++){
	if (f_rec[b] == neti[c]){//match connection
	g_connection.push_back(f[x]);

	set = 1;
	break;
	}
	}

	if (set == 1){
	break;
	}
	}
	}*/
	//int con_size = g_connection.size();
	return g_connection;
}

vector<int> block::j_connection(int j){//get all net that connects to block j
	extern vec_rec rec_val;
	extern vector<vector<int>>ad;
	vec_rec v = rec_val;
	vector<int>j1;//return 
	int cont = 0;
	int v_length = ad[j - 1].size();
	for (int k = 2; k < v_length; k++){
		j1.push_back(ad[j - 1][k]);
	}
	/*for (int x = 0; x < v.total_numbers; x++){
		if (j == 1){
			for (int i = x + 2; v.a[i] != -1; i++){
				j1.push_back(v.a[i]);
				//cout << v.a[i];
			}
			break;
		}
		if (v.a[x] == -1){
			if (v.a[x + 1] == j){
				//cout << v.a[x+1];
				//cout << "net start" << endl;
				for (int i = x + 3; v.a[i] != -1; i++){
					j1.push_back(v.a[i]);
					//cout << v.a[i];
				}
				break;
			}
		}
		else{
			continue;
		}
	}*/

	return j1;
}
bound block::get_boundary(){
	extern vec_rec rec_val;
	vec_rec g_r = rec_val;
	double X_max = 0;
	double X_min = 10;
	double Y_min = 0;
	double Y_max =10;

	for (int i = 0; i < g_r.fixed_numbers; i = i + 3){
		if (g_r.fixed[i + 1]>X_max){
			X_max = g_r.fixed[i + 1];
		}
		if (g_r.fixed[i + 1] < X_min){
			X_min = g_r.fixed[i + 1];
		}
		if (g_r.fixed[i + 2]>Y_max){
			Y_max = g_r.fixed[i + 2];
		}
		if (g_r.fixed[i + 2]<Y_min){
			Y_min = g_r.fixed[i + 2];
		}
	}
	bound vans;
	vans.x_max = X_max;
	vans.x_min = X_min;
	vans.y_max = Y_max;
	vans.y_min = Y_min;
	return vans;
}