
#include "branching.h"
#include "calculator.h"
#include "draw_graph.h"
branching::branching()
{
}


branching::~branching()
{
}
vector<int>branching::fanout_calculation(){
	extern map<int, vector<int>>order;
	vector<int>fanout;
	
	int o_size = order.size();
	for (int i = 0; i < o_size; i++){
		int number = 0;
		vector<int>temp = order[i];
		for (int k = 0; k < temp.size();k++){
			number = number + temp[k];
		}
		fanout.push_back(number);
	}
	return fanout;
}
vector<int>branching::initial_partition(){
	extern map<int, vector<int>>order;
	vector<int>f_result = fanout_calculation();
	vector<int>block;
	for (int i = 0; i < f_result.size(); i++){
		block.push_back(i);
	}
	for (int i = 0; i < f_result.size(); i++){
		int temp = 0;
		for (int x = i + 1; x < f_result.size(); x++){
			if (f_result[i] < f_result[x]){
				temp = f_result[i];
				f_result[i] = f_result[x];
				f_result[x] = temp;
				temp = block[i];
				block[i] = block[x];
				block[x] = temp;
			}
			//cout<<"van";
		}
	}
	return block;
}

final_val branching::branch_result(){
	extern content file_reclaim;
	extern map<int, vector<int>>order;
	extern vector<int>branching_o;
	vector<int>initial_fanout = initial_partition();//get first partition
	
	map<int, vector<int>>p0;
	vector<int>pl;
	vector<int>pm;
	vector<int>pr;
	/*each vector represents a partial solution last member of vector is partial solution's cost*/
	for (int k = 0; k < file_reclaim.total_blocks + 4; k++){
		if (k == 0){
			pl.push_back(1);
			pm.push_back(2);
			pr.push_back(3);
		}
		else{
			pl.push_back(0);
			pm.push_back(0);
			pr.push_back(0);
		}
	}
	/*count number of l,m,r;12number of location+3numbers of count and 1bit of lb*/
	pl[file_reclaim.total_blocks] = 1;
	pm[file_reclaim.total_blocks + 1] = 1;
	pr[file_reclaim.total_blocks + 2] = 1;
	map < int, map<int, vector<int>>>p1;
	p0[0] = pl;
	p0[1] = pm;
	p0[2] = pr;
	p1[0] = p0;
	/*get initial best*/
	calculator ccc;
	C = &ccc;
	int best = 0;
	
	for (int x = 0; x < file_reclaim.total_blocks / 3; x++){
		for (int i = 0; i < file_reclaim.total_blocks / 3; i++){
			int n = 0;
			n = C->getc_cost(branching_o[x], branching_o[i + file_reclaim.total_blocks / 3]);
			best = best + n;
			cout << "first is " << branching_o[x] << endl;
			cout << "second is " << branching_o[i + file_reclaim.total_blocks / 3] << endl;
			cout << best;
			n = C->getc_cost(branching_o[x], branching_o[i + file_reclaim.total_blocks * 2 / 3]);
			best = best + n;
			
		}
	}
	for (int x = 0; x < file_reclaim.total_blocks / 3; x++){
		for (int i = 0; i < file_reclaim.total_blocks / 3; i++){
			int n = 0;
			n = C->getc_cost(branching_o[x + file_reclaim.total_blocks / 3], branching_o[i + file_reclaim.total_blocks*2 / 3]);
			best = best + n;
		}
	}
	cout << best << endl;
	final_val xx = branching_recursion(&p1, 0, best, initial_fanout);
	return xx;
}

final_val branching::branching_recursion(map<int, map<int, vector<int>>>*x1, int n, int b, vector<int>v1){
	calculator ccc;
	C = &ccc;
	extern content file_reclaim;
	extern map<int, vector<int>>order;
	if (n == file_reclaim.total_blocks-1){
		final_val x;
		map<int, vector<int>>new_primier;
		new_primier = (*x1)[file_reclaim.total_blocks - 1];
		int psize = new_primier.size();
		int best = b;
		cout << "first best is" << best << endl;
		cout << "vector length" << file_reclaim.total_blocks;
		cout << "i=" << psize << endl;
		for (int i = 0; i < psize; i++){
			vector<int>temp;
			temp = new_primier[i];
			cout << "cost " << temp[file_reclaim.total_blocks + 3] << endl;
			if (temp[file_reclaim.total_blocks + 3] < best){
				best = temp[file_reclaim.total_blocks + 3];
				x.partition_result = temp;
			}
		}
		x.best = best;
		for (int y = 0; y < x.partition_result.size(); y++){
			cout << x.partition_result[y];
		}
		cout << "best should be" << best << endl;
		draw_graph xxx;
		DDG = &xxx;
		for (int i = 0; i < (*x1).size(); i++){
			DDG->draw_depth((*x1)[i]);
		}
		return x;
	}
	else {
		/* get */
		map<int, vector<int>>size_c;
		map<int, vector<int>>new_primier;
		size_c = (*x1)[n];
		int nsize = size_c.size();
		int primier = 3 * nsize;
		int new_count = 0;
		for (int k = 0; k < nsize; k++){
			
			//for (int i = 0; i < nsize; i++){
				vector<int>old_partial_l = size_c[k];
				vector<int>old_partial_m = size_c[k];
				vector<int>old_partial_r = size_c[k];
				old_partial_l[n + 1] = 1;
				old_partial_l[file_reclaim.total_blocks] = old_partial_l[file_reclaim.total_blocks] + 1;
				/*cout << "old";
				for (int m = 0; m < old_partial_l.size(); m++){
					cout << old_partial_l[m];
				}
				cout << ""<<endl;*/
				if (old_partial_l[file_reclaim.total_blocks] <= file_reclaim.total_blocks / 3){
					vector<int>new_partial_l = old_partial_l;
					int costl = C->cost_increase(new_partial_l,n+1);
					//cout << costl << endl;
					new_partial_l[file_reclaim.total_blocks + 3] = new_partial_l[file_reclaim.total_blocks + 3] + costl;
					if (new_partial_l[file_reclaim.total_blocks + 3] <= b){
						new_primier[new_count] = new_partial_l;
						new_count = new_count + 1;
					}
					//cout << "" <<endl;
					/*for (int m = 0; m < new_partial_l.size(); m++){
						cout << new_partial_l[m];
					}*/
				}
				
				
				old_partial_m[n + 1] = 2;
				

				old_partial_m[file_reclaim.total_blocks + 1] = old_partial_m[file_reclaim.total_blocks + 1] + 1;
				

				if (old_partial_m[file_reclaim.total_blocks + 1] <= file_reclaim.total_blocks / 3){
					vector<int>new_partial_m = old_partial_m;
					int costm = C->cost_increase(new_partial_m, n + 1);
					new_partial_m[file_reclaim.total_blocks + 3] = new_partial_m[file_reclaim.total_blocks + 3] + costm;
					if (new_partial_m[file_reclaim.total_blocks + 3] <= b){
						new_primier[new_count] = new_partial_m;
						new_count = new_count + 1;
					}
					/*cout << "new";
					for (int m = 0; m < new_partial_m.size(); m++){
						cout << new_partial_m[m];
					}
					cout << "" << endl;*/
				}

				old_partial_r[n + 1] = 3;
				old_partial_r[file_reclaim.total_blocks + 2] = old_partial_r[file_reclaim.total_blocks + 2] + 1;
				if (old_partial_r[file_reclaim.total_blocks + 2] <= file_reclaim.total_blocks / 3){
					vector<int>new_partial_r = old_partial_r;
					int costr = C->cost_increase(new_partial_r, n + 1);
					new_partial_r[file_reclaim.total_blocks + 3] = new_partial_r[file_reclaim.total_blocks + 3] + costr;
					if (new_partial_r[file_reclaim.total_blocks + 3] <= b){
						new_primier[new_count] = new_partial_r;
						new_count = new_count + 1;
					}
				}
				

				/*need a function to calculate the cost increase*/

				/*need a function to calculate number of 1,2,3*/
			
		}
		(*x1)[n + 1] = new_primier;
		cout << "n is " << n << endl;
		cout << "map size"<<new_primier.size() << endl;
		return branching_recursion(x1, n + 1, b, v1);
	}
}
