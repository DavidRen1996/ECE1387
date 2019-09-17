#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
struct content{
	map<int,vector<int>>file_content;
	vector<int>block_fanout;
	int total_blocks;
	//int total_nets;
};
class file_extract
{

public:
	file_extract();
	~file_extract();
	content extraction();
	map<int, vector<int>> get_connection();
};

