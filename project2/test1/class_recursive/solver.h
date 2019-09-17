#pragma once
#include <stdio.h>
#include <vector>
#include "umfpack.h"
#include "create_matrix.h"
using namespace std;

class solver
{
	create_matrix cm;
public:
	solver();
	~solver();
	void solve_matrix();
};

