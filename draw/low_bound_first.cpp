//#include "stdafx.h"
#include "low_bound_first.h"


low_bound_first::low_bound_first()
{
}


low_bound_first::~low_bound_first()
{
}
void low_bound_first::lbf(){
	extern content file_reclaim;
	extern map<int, vector<int>>order;
	extern vector<int>branching_o;
	map<int, vector<int>>p0;
	vector<int>pl;
	vector<int>pm;
	vector<int>pr;
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
	int best = 0;

	for (int x = 0; x < file_reclaim.total_blocks / 3; x++){
		for (int i = 0; i < file_reclaim.total_blocks / 3; i++){
			int n = 0;
			n = c_sample.getc_cost(branching_o[x], branching_o[i + file_reclaim.total_blocks / 3]);
			best = best + n;
			cout << "first is " << branching_o[x] << endl;
			cout << "second is " << branching_o[i + file_reclaim.total_blocks / 3] << endl;
			
			n = c_sample.getc_cost(branching_o[x], branching_o[i + file_reclaim.total_blocks * 2 / 3]);
			best = best + n;
			cout <<"initial best" <<best;

		}
	}
	for (int x = 0; x < file_reclaim.total_blocks / 3; x++){
		for (int i = 0; i < file_reclaim.total_blocks / 3; i++){
			int n = 0;
			n = c_sample.getc_cost(branching_o[x + file_reclaim.total_blocks / 3], branching_o[i + file_reclaim.total_blocks * 2 / 3]);
			best = best + n;
		}
	}
	map<int, vector<int>>p;
	r bi;
	bi=lbf_recur(&p1, &p0,&p, 0,best,0,0,0);
	for (int i = 0; i >= 0; i++){
		//r goblin;
		bi = lbf_recur(bi.x1, bi.x2, bi.results, bi.n, bi.b, bi.signal, bi.count, bi.set);
		if (bi.set == 1){
			break;
		}
	}
}

r low_bound_first::lbf_recur(map<int, map<int, vector<int>>>*x1, map<int, vector<int>>*x2, map<int, vector<int>>*results, int n, int b, int signal, int count, int set){
	//cout << "number at input" << n << endl;
	DG.draw_lbf((*x2));
	
	extern content file_reclaim;
	extern map<int, vector<int>>order;
	extern vector<int>branching_o;
	int x1nz = 0;
	for (int i = 0; i <(*x1).size(); i++){
		if ((*x1)[i].size() != 0){
			x1nz = x1nz + 1;
		}
	}
	if (x1nz == 0 && (*x2).size() == 0){//no more unprocessed partial solution
		int best = b;
		for (int i = 0; i < (*results).size(); i++){
			vector<int>temp = (*results)[i];
			if (temp[file_reclaim.total_blocks + 3] < best){
				best = temp[file_reclaim.total_blocks + 3];
			}
		}
		cout << "best= " << best << endl;
		r result;
		result.b = b;
		result.count = 0;
		result.n = n;
		result.results = results;
		result.set = 1;
		result.signal = signal;
		result.x1 = x1;
		result.x2 = x2;
		return result;
	}

	else{
		if (count == 2000){
			r result;
			result.b = b;
			result.count = 0;
			result.n = n;
			result.results = results;
			result.set = 0;
			result.signal = signal;
			result.x1 = x1;
			result.x2 = x2;
			cout << "intermediate return" << endl;
			return result;
		}
		else{
			/*have not reached end yet*/
			if (signal == 0){
				map<int, vector<int>>size_c;
				map<int, vector<int>>new_primier;
				size_c = (*x2);
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
					
					if (old_partial_l[file_reclaim.total_blocks] <= file_reclaim.total_blocks / 3){
						vector<int>new_partial_l = old_partial_l;
						int costl = c_sample.cost_increase(new_partial_l, n + 1);
						//cout << costl << endl;
						new_partial_l[file_reclaim.total_blocks + 3] = new_partial_l[file_reclaim.total_blocks + 3] + costl;
						if (new_partial_l[file_reclaim.total_blocks + 3] <= b){
							new_primier[new_count] = new_partial_l;
							new_count = new_count + 1;
						}
						
					}


					old_partial_m[n + 1] = 2;


					old_partial_m[file_reclaim.total_blocks + 1] = old_partial_m[file_reclaim.total_blocks + 1] + 1;


					if (old_partial_m[file_reclaim.total_blocks + 1] <= file_reclaim.total_blocks / 3){
						vector<int>new_partial_m = old_partial_m;
						int costm = c_sample.cost_increase(new_partial_m, n + 1);
						new_partial_m[file_reclaim.total_blocks + 3] = new_partial_m[file_reclaim.total_blocks + 3] + costm;
						if (new_partial_m[file_reclaim.total_blocks + 3] <= b){
							new_primier[new_count] = new_partial_m;
							new_count = new_count + 1;
						}
					
					}

					old_partial_r[n + 1] = 3;
					old_partial_r[file_reclaim.total_blocks + 2] = old_partial_r[file_reclaim.total_blocks + 2] + 1;
					if (old_partial_r[file_reclaim.total_blocks + 2] <= file_reclaim.total_blocks / 3){
						vector<int>new_partial_r = old_partial_r;
						int costr = c_sample.cost_increase(new_partial_r, n + 1);
						new_partial_r[file_reclaim.total_blocks + 3] = new_partial_r[file_reclaim.total_blocks + 3] + costr;
						if (new_partial_r[file_reclaim.total_blocks + 3] <= b){
							new_primier[new_count] = new_partial_r;
							new_count = new_count + 1;
						}
					}

				}
				if (new_primier.size() == 0){//no available vectors for x2(no better or legal solution)
					if ((*x1)[n].size() != 0){
						(*x2) = (*x1)[n];
					}
					else{
						n = n - 1;
						(*x2) = (*x1)[n];
					}
					cout << "doom" << endl;
					count = count + 1;
					return lbf_recur(x1, x2, results, n, b, signal,count,set);
				}
				else{
					map<int, vector<int>>new_x2;
					int new_x2_length = 0;
					int lb = 3000;
					int npsize = new_primier.size();
					//cout << "new primier size " << new_primier.size() << endl;

					//int count_nz_new_primier = new_primier.size();
					map<int, vector<int>>temp = new_primier;
					map<int, vector<int>>reclaim;
					
					for (int i = 0; i <npsize; i++){
						vector<int>temp;
						temp = new_primier[i];
						if (temp[file_reclaim.total_blocks + 3] < lb){
							lb = temp[file_reclaim.total_blocks + 3];
						}
					}
					//cout << "lb= " << lb << endl;
					for (int i = 0; i < npsize; i++){
						vector<int>temp;
						temp = new_primier[i];
						if (temp[file_reclaim.total_blocks + 3] == lb){
							new_x2[new_x2_length] = temp;
							new_x2_length = new_x2_length + 1;
							new_primier.erase(i);
							//cout << "erased number " << i<< endl;
						}
					}
					(*x2) = new_x2;
				//	cout << "x2 size at section1 " << (*x2).size() << endl;
					map<int, vector<int>>temp2 = *x2;
					
					int kkp = new_primier.size();
					int count_nz = 0;
					int *pp;
					pp = &count_nz;
					cout << *pp << endl;
					for (int i = 0; count_nz< kkp; i++){
						//vector<int>t = temp[i];
						//cout << i;

						if (new_primier[i].size() != 0){
							vector<int>t = new_primier[i];
							reclaim[count_nz] = t;
							count_nz = count_nz + 1;
							//cout << "count is " << count_nz;
						}

					}

					if (reclaim.size() > 0){
						(*x1)[n + 1] = reclaim;
						//x1.erase(n);
					}

					//cout << "x1[n+1] size at section1 " << (*x1)[n + 1].size() << endl;
					map<int, vector<int>>temp1 = (*x1)[n + 1];
					
					if (n + 1 == file_reclaim.total_blocks - 2){
						signal = 1;
					}
				
					count = count + 1;
					return lbf_recur(x1, x2, results, n + 1, b, signal,count,set);
				}
			}
			else{
				/*reach end at this time*/

				if (n == file_reclaim.total_blocks - 2){
					signal = 1;
					
					map<int, vector<int>>size_c;
					map<int, vector<int>>new_primier;
					size_c = (*x2);
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
						
						if (old_partial_l[file_reclaim.total_blocks] <= file_reclaim.total_blocks / 3){
							vector<int>new_partial_l = old_partial_l;
							int costl = c_sample.cost_increase(new_partial_l, n + 1);
							//cout << costl << endl;
							new_partial_l[file_reclaim.total_blocks + 3] = new_partial_l[file_reclaim.total_blocks + 3] + costl;
							if (new_partial_l[file_reclaim.total_blocks + 3] <= b){
								new_primier[new_count] = new_partial_l;
								new_count = new_count + 1;
								b = new_partial_l[file_reclaim.total_blocks + 3];
							}
							
						}


						old_partial_m[n + 1] = 2;


						old_partial_m[file_reclaim.total_blocks + 1] = old_partial_m[file_reclaim.total_blocks + 1] + 1;


						if (old_partial_m[file_reclaim.total_blocks + 1] <= file_reclaim.total_blocks / 3){
							vector<int>new_partial_m = old_partial_m;
							int costm = c_sample.cost_increase(new_partial_m, n + 1);
							new_partial_m[file_reclaim.total_blocks + 3] = new_partial_m[file_reclaim.total_blocks + 3] + costm;
							if (new_partial_m[file_reclaim.total_blocks + 3] <= b){
								new_primier[new_count] = new_partial_m;
								new_count = new_count + 1;
								b = new_partial_m[file_reclaim.total_blocks + 3];
							}
							
						}

						old_partial_r[n + 1] = 3;
						old_partial_r[file_reclaim.total_blocks + 2] = old_partial_r[file_reclaim.total_blocks + 2] + 1;
						if (old_partial_r[file_reclaim.total_blocks + 2] <= file_reclaim.total_blocks / 3){
							vector<int>new_partial_r = old_partial_r;
							int costr = c_sample.cost_increase(new_partial_r, n + 1);
							new_partial_r[file_reclaim.total_blocks + 3] = new_partial_r[file_reclaim.total_blocks + 3] + costr;
							if (new_partial_r[file_reclaim.total_blocks + 3] <= b){
								new_primier[new_count] = new_partial_r;
								new_count = new_count + 1;
								b = new_partial_r[file_reclaim.total_blocks + 3];
							}
						}

					}
					int rsize = (*results).size();
					for (int i = 0; i < new_primier.size(); i++){
						vector<int>temp = new_primier[rsize];
						rsize = rsize + 1;
					}
					if ((*x1)[n].size() != 0){
						//x1.erase(n);
						int low = 3000;
						map<int, vector<int>>temp = (*x1)[n];
						for (int i = 0; i < (*x1)[n].size(); i++){
							vector<int>t = temp[i];
							for (int k = 0; k < t.size(); k++){
								if (t[file_reclaim.total_blocks + 3] < low){
									low = t[file_reclaim.total_blocks + 3];
								}
							}
						}
						int x2_count = 0;
						map<int, vector<int>>temp11 = (*x1)[n];
						for (int i = 0; i < (*x1)[n].size(); i++){
							vector<int>t = temp[i];
							if (t[file_reclaim.total_blocks + 3] == low){
								(*x2)[x2_count] = t;
								x2_count = x2_count + 1;
								temp11.erase(i);
							}
						}
						int size11 = temp11.size();
						map<int, vector<int>>reclaim1;
						int reclaim1_count = 0;
						for (int i = 0; reclaim1_count < size11; i++){

							if (temp11[i].size() != 0){
								reclaim1[reclaim1_count] = temp11[i];
								reclaim1_count = reclaim1_count + 1;
							}

						}
						(*x1)[n] = reclaim1;
						for (int i = 0; i < temp11.size(); i++){
							vector<int>().swap(temp11[i]);
						}
						for (int i = 0; i < reclaim1.size(); i++){
							vector<int>().swap(reclaim1[i]);
						}
						for (int i = 0; i < size_c.size(); i++){
							vector<int>().swap(size_c[i]);
						}
						//cout << "get a solution" << endl;
						//cout << "size of x1!!!!!!!!!!!!!" << (*x1).size() << endl;
						count = count + 1;
						return  lbf_recur(x1, x2, results, n, b, signal,count,set);
					}
					else{
						
						for (int i = n; i > 0; i--){
							if ((*x1)[i].size() != 0){
								n = i;
								break;
							}
						}
						//cout << "n for pick up is " << n << endl;
						int low = 3000;
						map<int, vector<int>>temp = (*x1)[n];
						for (int i = 0; i < (*x1)[n].size(); i++){
							vector<int>t = temp[i];
							for (int k = 0; k < t.size(); k++){
								if (t[file_reclaim.total_blocks + 3] < low){
									low = t[file_reclaim.total_blocks + 3];
								}
							}
						}
						int x2_count = 0;
						map<int, vector<int>>temp11 = (*x1)[n];
						
						map<int, vector<int>>x2_temp;
						for (int i = 0; i < (*x1)[n].size(); i++){
							vector<int>t = temp11[i];
							if (t[file_reclaim.total_blocks + 3] == low){
								x2_temp[x2_count] = t;
								x2_count = x2_count + 1;
								temp11.erase(i);
							}
						}
						(*x2) = x2_temp;
						//cout << "x2 length" << x2_count << endl;
						int size11 = temp11.size();
						map<int, vector<int>>reclaim1;
						int reclaim1_count = 0;
						for (int i = 0; reclaim1_count < size11; i++){

							if (temp11[i].size() != 0){
								reclaim1[reclaim1_count] = temp11[i];
								reclaim1_count = reclaim1_count + 1;
							}

						}
						(*x1)[n] = reclaim1;
						for (int i = 0; i < temp11.size(); i++){
							vector<int>().swap(temp11[i]);
						}
						for (int i = 0; i < reclaim1.size(); i++){
							vector<int>().swap(reclaim1[i]);
						}
						for (int i = 0; i < size_c.size(); i++){
							vector<int>().swap(size_c[i]);
						}
						
						count = count + 1;
						return  lbf_recur(x1, x2, results, n, b, signal,count,set);

					}

				}
				else{
					
					map<int, vector<int>>size_c;
					map<int, vector<int>>size_temp;
					map<int, vector<int>>new_primier;
					size_temp = (*x2);
					vector<int> nz;
					int nz_size = 0;
					
					int sz = size_temp.size();
					for (int i = 0; nz_size <sz; i++){
						if (nz_size == size_temp.size()){
							break;
						}
						if (size_temp[i].size() != 0){

							nz.push_back(i);
							nz_size = nz_size + 1;

						}
					}

					for (int i = 0; i < nz_size; i++){
						size_c[i] = size_temp[nz[i]];
					}
					//cout << "x2 size" << x2.size() << endl;
					int nsize = size_c.size();
					int primier = 3 * nsize;
					int new_count = 0;
					for (int k = 0; k < nsize; k++){

						//for (int i = 0; i < nsize; i++){
						vector<int>old_partial_l = size_c[k];
						//cout << "left size" << old_partial_l.size() << endl;
						vector<int>old_partial_m = size_c[k];
						vector<int>old_partial_r = size_c[k];

						old_partial_l[n + 1] = 1;
						old_partial_l[file_reclaim.total_blocks] = old_partial_l[file_reclaim.total_blocks] + 1;
						
						if (old_partial_l[file_reclaim.total_blocks] <= file_reclaim.total_blocks / 3){
							vector<int>new_partial_l = old_partial_l;
							int costl = c_sample.cost_increase(new_partial_l, n + 1);
							//cout << costl << endl;
							new_partial_l[file_reclaim.total_blocks + 3] = new_partial_l[file_reclaim.total_blocks + 3] + costl;
							if (new_partial_l[file_reclaim.total_blocks + 3] <= b){
								new_primier[new_count] = new_partial_l;
								new_count = new_count + 1;
							}
							
						}


						old_partial_m[n + 1] = 2;


						old_partial_m[file_reclaim.total_blocks + 1] = old_partial_m[file_reclaim.total_blocks + 1] + 1;


						if (old_partial_m[file_reclaim.total_blocks + 1] <= file_reclaim.total_blocks / 3){
							vector<int>new_partial_m = old_partial_m;
							int costm = c_sample.cost_increase(new_partial_m, n + 1);
							new_partial_m[file_reclaim.total_blocks + 3] = new_partial_m[file_reclaim.total_blocks + 3] + costm;
							if (new_partial_m[file_reclaim.total_blocks + 3] <= b){
								new_primier[new_count] = new_partial_m;
								new_count = new_count + 1;
							}
						}

						old_partial_r[n + 1] = 3;
						old_partial_r[file_reclaim.total_blocks + 2] = old_partial_r[file_reclaim.total_blocks + 2] + 1;
						if (old_partial_r[file_reclaim.total_blocks + 2] <= file_reclaim.total_blocks / 3){
							vector<int>new_partial_r = old_partial_r;
							int costr = c_sample.cost_increase(new_partial_r, n + 1);
							new_partial_r[file_reclaim.total_blocks + 3] = new_partial_r[file_reclaim.total_blocks + 3] + costr;
							if (new_partial_r[file_reclaim.total_blocks + 3] <= b){
								new_primier[new_count] = new_partial_r;
								new_count = new_count + 1;
							}
						}

					}
					//x1[n] = x1[n].erase();
					if (new_primier.size() == 0){
						//cout << "dead n= " << n << endl;
						(*x1).erase(n);//no subbranchs can have a better solution
						for (int i = n - 1; i >= 0; i--){
							if ((*x1)[i].size() != 0){
								n = i;
								break;
							}
						}

						map<int, vector<int>>new_x2;
						int new_x2_length = 0;
						int lb = 3000;
						int npsize = (*x1)[n].size();
						for (int i = 0; i < npsize; i++){
							vector<int>temp;
							temp = (*x1)[n][i];
							if (temp[file_reclaim.total_blocks + 3] < lb){
								lb = temp[file_reclaim.total_blocks + 3];
							}
						}
						for (int i = 0; i <npsize; i++){
							vector<int>temp;
							temp = (*x1)[n][i];
							if (temp[file_reclaim.total_blocks + 3] == lb){
								new_x2[new_x2_length] = temp;
								new_x2_length = new_x2_length + 1;

								(*x1)[n].erase(i);
							}
						}
						(*x2) = new_x2;
						//cout << "new x2 size is " << x2.size() << endl;
						int kkp = (*x1)[n].size();
						int count_nz = 0;
						int *pp;
						pp = &count_nz;
						map<int, vector<int>>reclaim2;
						//cout << "new primier size is " << kkp << endl;
						for (int i = 0; count_nz< kkp; i++){

							if ((*x1)[n][i].size() != 0){
								vector<int>t = (*x1)[n][i];
								reclaim2[count_nz] = t;
								count_nz = count_nz + 1;
								//cout << "count is " << count_nz;
							}

						}


						(*x1)[n] = reclaim2;
						//x1.erase(n);

						for (int i = 0; i < new_x2.size(); i++){
							vector<int>().swap(new_x2[i]);
						}
						for (int i = 0; i < reclaim2.size(); i++){
							vector<int>().swap(reclaim2[i]);
						}
						count = count + 1;
						return  lbf_recur(x1, x2, results, n, b, signal,count,set);
					}
					else{
						map<int, vector<int>>new_x2;
						int new_x2_length = 0;
						int lb = 3000;
						int npsize = new_primier.size();
						for (int i = 0; i < npsize; i++){
							vector<int>temp;
							temp = new_primier[i];
							if (temp[file_reclaim.total_blocks + 3] < lb){
								lb = temp[file_reclaim.total_blocks + 3];
							}
						}
						for (int i = 0; i <npsize; i++){
							vector<int>temp;
							temp = new_primier[i];
							if (temp[file_reclaim.total_blocks + 3] == lb){
								new_x2[new_x2_length] = temp;
								new_x2_length = new_x2_length + 1;

								new_primier.erase(i);
							}
						}
						(*x2) = new_x2;
						//cout << "new x2 size is " << x2.size() << endl;
						int kkp = new_primier.size();
						int count_nz = 0;
						int *pp;
						pp = &count_nz;
						map<int, vector<int>>reclaim2;
						//cout << "new primier size is " << kkp << endl;
						for (int i = 0; count_nz< kkp; i++){
							//vector<int>t = temp[i];
							//cout << i;

							if (new_primier[i].size() != 0){
								vector<int>t = new_primier[i];
								reclaim2[count_nz] = t;
								count_nz = count_nz + 1;
								//cout << "count is " << count_nz;
							}

						}

						if (reclaim2.size() > 0){
							(*x1)[n + 1] = reclaim2;
							//x1.erase(n);
						}
						for (int i = 0; i < new_x2.size(); i++){
							vector<int>().swap(new_x2[i]);
						}
						for (int i = 0; i < reclaim2.size(); i++){
							vector<int>().swap(reclaim2[i]);
						}
						count = count + 1;

						return  lbf_recur(x1, x2, results, n + 1, b, signal,count,set);
					}



				}
			}
		}
		
	}
}
