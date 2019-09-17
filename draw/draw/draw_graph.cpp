#include "draw_graph.h"


draw_graph::draw_graph()
{
}


draw_graph::~draw_graph()
{
}
void draw_graph::draw_depth(map<int, vector<int>>x1){
	extern content file_reclaim;
	extern map<int, vector<int>>order;
	extern vector<int>branching_o;
	for (int i = 0; i < x1.size(); i++){
		if (x1[i].size() != 0){
			vector<int>t = x1[i];
			int deviation = 0;
			double x_coordinate = 500;
			double y_coordinate = 0;
			double prex_coordinate = 500;
			double prey_coordinate = 0;
			for (int k = 0; k < file_reclaim.total_blocks; k++){
				int num = pow(3, k + 1);
				if (t[k] == 0){
					break;
				}
				else{
					if (t[k] == 1){
						x_coordinate = x_coordinate - (1000 / num);
					}
					else {
						if (t[k] == 2){
							x_coordinate = x_coordinate;

						}
						else{
							x_coordinate = x_coordinate + (1000 / num);
						}

					}
					y_coordinate = y_coordinate + 50;
				}
			}
			for (int k = 0; k < file_reclaim.total_blocks; k++){
				int num = pow(3, k + 1);
				if (t[k + 1] == 0){
					break;
				}
				else{
					if (t[k] == 1){
						prex_coordinate = prex_coordinate - (1000 / num);
					}
					else {
						if (t[k] == 2){
							prex_coordinate = prex_coordinate;

						}
						else{
							prex_coordinate = prex_coordinate + (1000 / num);
						}

					}
					prey_coordinate = prey_coordinate + 50;
				}
			}
			setcolor(RED);
			setlinestyle(SOLID);
			drawline(prex_coordinate, prey_coordinate, x_coordinate, y_coordinate);
		}
	}
}
void draw_graph::draw_lbf(map<int, vector<int>>x2){
	extern content file_reclaim;
	extern map<int, vector<int>>order;
	extern vector<int>branching_o;
	for (int i = 0; i < x2.size(); i++){
		if (x2[i].size() != 0){
			vector<int>t = x2[i];
			int deviation = 0;
			double x_coordinate = 500;
			double y_coordinate = 0;
			double prex_coordinate = 500;
			double prey_coordinate = 0;
			for (int k = 0; k < file_reclaim.total_blocks; k++){
				int num = pow(3, k+1);
				if (t[k] == 0){
					break;
				}
				else{
					if (t[k] == 1){
						x_coordinate = x_coordinate - (1000 / num);
					}
					else {
						if (t[k] == 2){
							x_coordinate = x_coordinate;

						}
						else{
							x_coordinate = x_coordinate + (1000 / num);
						}

					}
					y_coordinate = y_coordinate + 50;
				}
			}
			for (int k = 0; k < file_reclaim.total_blocks; k++){
				int num = pow(3, k+1);
				if (t[k+1] == 0){
					break;
				}
				else{
					if (t[k] == 1){
						prex_coordinate = prex_coordinate - (1000 / num);
					}
					else {
						if (t[k] == 2){
							prex_coordinate = prex_coordinate;

						}
						else{
							prex_coordinate = prex_coordinate + (1000 / num);
						}

					}
					prey_coordinate = prey_coordinate + 50;
				}
			}
			setcolor(RED);
			setlinestyle(SOLID);
			drawline(prex_coordinate, prey_coordinate, x_coordinate, y_coordinate);
		}
	}
}
