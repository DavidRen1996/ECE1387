#pragma once

#include <vector>
#include <iostream>
#include "block.h"
#include "extract.h"
#include "recurs.h"
using namespace std;
class create_matrix;
class spread
{
	block bm;
	extract em;
	create_matrix *cd;
public:
	vector<double>get_nb(int x);//x represents if to get x or y value
	spread();
	~spread();
};

