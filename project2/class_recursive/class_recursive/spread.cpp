#include "stdafx.h"
#include "spread.h"
#include "create_matrix.h"

spread::spread()
{
}


spread::~spread()
{
}
vector<double>spread::get_nb(int x){
	create_matrix cc;
	cd = &cc;
	vector<double>bValues = cd->get_b(x);
	bound b = bm.get_boundary();
	double x0 = (b.x_max + b.x_min) / 2;
	cout << "x0= " << x0 << endl;
	double y0 = (b.y_max + b.y_min) / 2;
	double x1 = (b.x_min + x0) / 2;
	double x2 = (b.x_max + x0) / 2;
	double y1 = (b.y_max + y0) / 2;
	double y2 = (b.y_min + y0) / 2;
	xy e_get = em.get_cfile();
	cout << "sb size is= " << bValues.size() << endl;
	for (int i = 0; i < bValues.size(); i++){
		double n = bValues[i];
		cout << "sb[i] value is =" << n << endl;
		cout << "eget is " << e_get.x[i] << endl;
		if (x == 1){
			if (e_get.x[i] <= x0){//left upper
				bValues[i] = n + x1;//weight =1
				cout << "eget is " << e_get.x[i] << endl;
				continue;
			}
			else{
				
					bValues[i] = n + x2;//weight =1
					continue;
				
			}
			
		}
		else{
			if (e_get.x[i]<=y0){
				bValues[i] = n + y1;//weight =1
				continue;
			}
			else{
					bValues[i] = n + y2;//weight =1
					continue;
				}
			}


		}
	cout << "start showing b" << endl;
	for (int i = 0; i < bValues.size(); i++){
		cout << bValues[i] << endl;
	}
	return bValues;
}