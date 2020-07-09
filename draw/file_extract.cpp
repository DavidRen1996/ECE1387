//#include "stdafx.h"
#include "file_extract.h"


file_extract::file_extract()
{
}


file_extract::~file_extract()
{
}
content file_extract::extraction(){
	content newfile;
	vector<vector<int>>temp;
	int k = 0;
	temp.resize(1);//do not forget to give an initial length to vector row
	ifstream infile;
	infile.open("cct2.txt");
	while (!infile.eof()){
		int n;
		//int i = 0;
		infile >> n;
		if (n == -1){
			k = k + 1;
			temp.resize(k+2);//k+2 is the new size for vector
			
		}
		else {
			//cout << k;
			temp[k].push_back(n);
		}


	}
	cout << "k=" << k <<endl;
	for (int i = 0; i < k-1; i++){
		newfile.file_content.insert(pair<int, vector<int>>(i, temp[i]));
	}
	
	//map<int, vector<int>>::iterator i;
	int nsize = newfile.file_content.size();
	newfile.total_blocks = nsize - 1;//get total blocks
	vector<int>fanouts;
	for (int m = 0; m < nsize-1; m++){
		int a = 0;
		a = newfile.file_content[m].size();
		fanouts.push_back(a);
	}
	cout << "nsize" << nsize << endl;
	newfile.block_fanout = fanouts;
	newfile.total_blocks = nsize;
	return newfile;


}
map<int, vector<int>> file_extract::get_connection(){
	content s = extraction();
	map<int, vector<int>>cost_value;
	for (int i = 0; i < s.total_blocks; i++){
		vector<int>temp = s.file_content[i];
		vector<int>value;
		vector<int>final_value;
		vector<int>store;
		cout << s.total_blocks << endl;
		for (int m = i + 1; m < s.total_blocks; m++){
			int length = temp.size();
			vector<int>compare = s.file_content[m];
			int c_length = compare.size();
			int cost = 0;
			for (int y = 1; y < length; y++){
				for (int x = 1; x < c_length; x++){
					if (temp[y] == compare[x]){
						cost = cost + 1;

					}
				}
			}
			store.push_back(cost);
		}
		if (i == 0){
			int ss = store.size();
			cout << "store size" << ss << endl;
			value.push_back(0);
			final_value.insert(final_value.end(), value.begin(), value.end());//将vec1压入
			final_value.insert(final_value.end(), store.begin(), store.end());
			cost_value.insert(pair<int, vector<int>>(i, final_value));

		}
		else {
			for (int x = 0; x < i; x++){
				vector < int >c = cost_value[x];
				vector<int>temp_store;
				for (int j = x+1; j < s.total_blocks; j++){
					temp_store.push_back(c[j]);
				}
				value.push_back(temp_store[i - x - 1]);
			}
			value.push_back(0);
			final_value.insert(final_value.end(), value.begin(), value.end());//将vec1压入
			final_value.insert(final_value.end(), store.begin(), store.end());
			cost_value.insert(pair<int, vector<int>>(i, final_value));
		}
	}
	return cost_value;
}
