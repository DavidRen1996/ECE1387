#pragma once
#include <vector>
#include "extract.h"
#include "recurs.h"
using namespace std;
struct mov{
	vector<int>mv;//moveable content
	int m_num;//number of moveable blocks
};

class net
{
	extract vans;
	//int net_number;
public:
	net();
	~net();
	mov moveable(int i);//i=6,7...
	vector<int> get_num(int i);//i=6,7....
	double get_weight(int net_number);//i=6,7...
	double get_wl(int i);//get net number i
	vector<int>net::get_mv(int i);
};

