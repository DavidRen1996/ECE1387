#include "stdafx.h"
#include "create_matrix.h"
#include "spread.h"

using namespace std;

create_matrix::create_matrix()
{
}


create_matrix::~create_matrix()
{
}
void create_matrix::get_file()
{
	int coordinate = 0;
	cout << "X coordinate input 1, Y coordinate input 0" << endl;
	cin >> coordinate;
	vector<vector<double>>r_q = matrix_calculation();
	vector<double>r_b = get_b(coordinate);
	linear_parameter matl = mat(r_q, r_b);
	int row = matl.m;
	cout << "row number=" << row << endl;
	int column = matl.n;
	int x = matl.Ap.size();
	int *AP = new int[x];
	int y = matl.Ai.size();
	int *AI = new int[y];
	int z = matl.Ax.size();
	double *AX = new double[z];
	//int b_length = 15;
	vector<double>B;
	cout << "below is the matlab form" << endl;
	cout << "row = " << matl.m << endl;
	cout << "column is =" << matl.n << endl;
	cout << "Ap = " << endl;
	for (int p = 0; p < matl.Ap.size(); p++){
		AP[p] = matl.Ap[p];
		cout << AP[p] << endl;
	}
	cout << "Ai = " << endl;
	for (int p = 0; p < matl.Ai.size(); p++){
		AI[p] = matl.Ai[p];
		cout << AI[p] << endl;
	}
	cout << "Ax = " << endl;
	for (int p = 0; p < matl.Ax.size(); p++){
		AX[p] = matl.Ax[p];
		cout << AX[p] << endl;
	}
	spread dd;
	sm = &dd;
	cout << "B=" << endl;
	/*for (int p = 0; p < 15; p++){
		B[p] = sm.get_nb[p];
		cout << B[p] << endl;
	}*/
	//B = sm->get_nb(coordinate);//new b values after introducing new fixed blocks in the quarter
	B = r_b;//get b values without adding new fixed blocks
	ofstream outfile_b;
	if (coordinate == 1){
		outfile_b.open("C:\\Users\\ThinkPad\\Desktop\\b_x.txt");
	}
	else {
		outfile_b.open("C:\\Users\\ThinkPad\\Desktop\\b_y.txt");
	}
	//outfile_b.open("C:\\Users\\ThinkPad\\Desktop\\b.txt");
	for (int p = 0; p < r_b.size(); p++){
		outfile_b << B[p] << " ";
	}
	outfile_b.close();
	ofstream outfile_Ap;
	outfile_Ap.open("C:\\Users\\ThinkPad\\Desktop\\Ap.txt");
	for (int p = 0; p <matl.Ap.size(); p++){
		outfile_Ap << matl.Ap[p] << " ";
	}
	outfile_Ap.close();
	ofstream outfile_Ai;
	outfile_Ai.open("C:\\Users\\ThinkPad\\Desktop\\Ai.txt");
	for (int p = 0; p <matl.Ai.size(); p++){
		outfile_Ai << matl.Ai[p] << " ";
	}
	outfile_Ai.close();
	ofstream outfile_Ax;
	outfile_Ax.open("C:\\Users\\ThinkPad\\Desktop\\Ax.txt");
	for (int p = 0; p <matl.Ax.size(); p++){
		outfile_Ax << matl.Ax[p] << " ";
	}
	outfile_Ax.close();
}
vector<vector<double>> create_matrix::matrix_calculation(){//return Q 
	vector<vector<double>>q;
	//q.resize(15, vector<double>(15));
	//vec_rec n_recv = c.recv();// get circuit info
	extern vector<int> nget;
	vector<int>netlist = nget;//get  all moveable blocks in the circuit
	int n_size = netlist.size();
	for (int i = 0; i < n_size; i++){//loop all blocks
		vector<double>line_t = get_q(netlist[i]);//a line prepare to add to Q
		q.push_back(line_t);
	}

	return q;
}
vector<double> create_matrix::get_q(int i){//i=0,1,.....
	//vec_rec n_recv = c.recv();// get circuit info
	extern vec_rec rec_val;
	vec_rec n_recv = rec_val;
	extern vector<int> nget;
	vector<int>netlist = nget;;//get  all moveable blocks in the circuit
	int n_size = netlist.size();
	vector<double>line(n_size);//a line prepare to add to Q
	cout << n_recv.fixed_numbers;
	int nx = n_recv.fixed_numbers / 3;
	vector<int>j_connect = bbc.j_connection(netlist[i - nx - 1]);//get all net that connects to block j
	int j_size = j_connect.size();
	double q_sum = 0;
	for (int x = 0; x < j_size; x++){//loop all net that connects to j
		double w = ba.get_weight(j_connect[x]);//get weight for a net
		//cout << "get net's weight" << j_connect[x] << endl;
		vector<int>p = ba.get_num(j_connect[x]);//j_connect[x]is the net number
		int num = p.size() - 1;
		q_sum = q_sum + w*num;
	}
	line[i - nx - 1] = q_sum;//
	// get off diag
	cout << n_size << endl;
	for (int z = 0; z < n_size; z++){
		if (netlist[z] == netlist[i - nx - 1]){
			continue;
		}
		else{
			double sum = 0;
			vector<int>off_diag = get_connections(i - nx - 1, j_connect);

			int o_diag = off_diag.size();
			for (int y = 0; y < o_diag; y++){
				double w2 = gsum(i, off_diag[y]);
				line[off_diag[y] - nx - 1] = -w2;
				//cout << "finish a point" << endl;
			
			}

		}
	}


	return line;
}
vector<int>create_matrix::get_connections(int i, vector<int>neti){// get connection between block i and the rest of the circuit, i=0,1....
	//vec_rec g_recv = c.recv();// get circuit info
	vector<int>g_connection;//return
	extern vector<int> nget;
	vector<int>netl = nget;//get  all moveable blocks in the circuit
	//vector<int>neti = bbc.j_connection(netl[i]);//get all net that connects to block i
	int i_size = neti.size();
	int n = netl.size();
	for (int k = 0; k < n; k++){
		if (netl[k] == netl[i]){//find itself
			continue;
		}
		else{
			vector<int>g = bbc.j_connection(netl[k]);//get all net that connects to block j
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
	
	return g_connection;
}
double create_matrix::gsum(int x, int y){//get sum of off diag value for a block,x is the row , y is the column
	
	double s = 0;
	extern vec_rec rec_val;
	vec_rec s_recv = rec_val;
	int ss = s_recv.fixed_numbers / 3;
	extern vector<int> nget;
	extern vector<vector<int>>ad;
	for (int i = 2; i < ad[x-1].size(); i++){
		for (int k = 2; k < ad[y-1].size(); k++){
			if (ad[x-1][i] == ad[y-1][k]){
				double w1 = ba.get_weight(ad[x-1][i]);
				s = s + w1;
			}
		}
	}
	
	return s;
}
vector<double> create_matrix::get_b(int x_y){
	vector<double>b;
	extern vec_rec rec_val;
	vec_rec b_recv = rec_val;
	extern vector<int> nget;
	vector<int>b_mov = nget;
	extern vector<double>fget;
	vector<double>b_fix = fget;
	int b_fsize = b_fix.size();
	for (int i = 0; i < b_mov.size(); i++){//loop through each moveable block
		vector<int>b_connect = bbc.j_connection(b_mov[i]);//get all net that connects to block j
		double b_sum = 0;
		int b_size = b_connect.size();
		for (int k = 0; k < b_size; k++){//the code below is to find if there is a fixed block in that net
			vector<int>b_content = ba.get_num(b_connect[k]);//net b_connect[k]'s content
			mov b_r = ba.moveable(b_connect[k]);
			//cout << "fixed block number in net" << b_connect[k] << "is" << b_r.m_num << endl;
			if (b_r.m_num == 0){//that net has no connection to fix blocks
				continue;
			}
			else{
				for (int h = 0; h < b_r.mv.size(); h++){//fix

					double W = ba.get_weight(b_connect[k]);//weight for net 
					//cout << "weight is =" << W << endl;
					if (x_y == 1){
						for (int c = 0; c < b_recv.fixed.size(); c = c + 3){//get x coordinate
							if (b_recv.fixed[c] == b_r.mv[h]){
								b_sum = b_sum + W*b_recv.fixed[c + 1];
								break;
							}
						}
					}
					else{
						for (int c = 0; c < b_recv.fixed.size(); c = c + 3){//get y coordinate
							if (b_recv.fixed[c] == b_r.mv[h]){
								b_sum = b_sum + W*b_recv.fixed[c + 2];
								break;
							}
						}
					}

				}
			}
		}


		b.push_back(b_sum);
	}
	return b;
}

linear_parameter create_matrix::mat(vector<vector<double>>Atest, vector<double>B_test){
	vector<int>Ap_re(1);//make one room for the first zero
	vector<int>Ai_re;
	vector<double>Ax_re;
	vector<double>b_re;
	int nz = 0;//number of non-zero item in a column
	int m = Atest.size();//get m for a m*n matrix
	//cout << m;
	int n = Atest[0].size();//get n for a m*n matrix
	cout << n;
	for (int i = 0; i < n; i++){//loop each column search for non-zero
		//nz = 0;
		for (int x = 0; x < m; x++){
			if (Atest[x][i] != 0){
				nz = nz + 1;//find a nz
				//cout << nz << endl;
				Ai_re.push_back(x);//add nz's row coordinate to a vector
				Ax_re.push_back(Atest[x][i]);//store nz's value
			}

		}
		Ap_re.push_back(nz);//add the number of nz in a column
	}
	linear_parameter para_return;
	para_return.Ai = Ai_re;
	para_return.Ap = Ap_re;
	para_return.Ax = Ax_re;
	para_return.m = m;
	para_return.n = n;
	return para_return;
}