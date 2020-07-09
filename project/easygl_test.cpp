// a_test.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "router.h"
#include "graphics.h"
#include "pathRender.h"
#include "easygl_constants.h"
using namespace std;
void delay(void);
void draw(int **matrix, int *init, int *source, int *par);





void draw(int **matrix, int *init,int *source,int *par){
	int num = par[1];
	int row = par[2];
	int rec_len = par[0];
	int mark = 0;//mark for the source 
	//cout << "mark=0" << endl;
	int *rec_init;
	//int *rec_source;
	rec_init = init;//recive target coordinate
	//rec_source = source;
	while (mark == 0){
		cout << source[0] << endl;
		if (rec_init[0] - 2 >= 0 && rec_init[1] >= 0){//target has a point in the left
			if (rec_init[0] - 2 == source[0] && rec_init[1] == source[1]){//left is the source?
				cout << "find target left" << endl;//furthur replaced by drawing red line
				cout << "drawline from" << rec_init[0] << rec_init[1] << "to" << rec_init[0] - 2 << rec_init[1] << endl;
				setlinestyle(SOLID);
				setcolor(RED);
				drawline(100 * (rec_init[0] - 2) / 2 + 100., 100 * (num - rec_init[1] / 2) + 1 * row + 5., (rec_init[0] - 2) / 2 + 150., 100 * (num - rec_init[1] / 2) + 1 * row + 5.);
                flushinput();
                delay();
                delay();
				mark = 1;
				continue;
			}
		}
		//left point is not the target try right
		if (rec_init[0] + 2 <= 2 * num && rec_init[1] >= 0){//target has a point in the right
			if (rec_init[0] + 2 == source[0] && rec_init[1] == source[1]){//right is the source?
				cout << "find target right" << endl;//furthur replaced by drawing red line
				setlinestyle(SOLID);
				setcolor(RED);
				drawline(100 * (rec_init[0]) / 2 + 50., 100 * (num - rec_init[1] / 2) + 1 * row + 5., 100 * (rec_init[0]) / 2 + 100., 100 * (num - rec_init[1] / 2) + 1 * row + 5.);
                flushinput();
                delay();
                delay();
				mark = 1;
				continue;
			}
		}
		if (rec_init[0] >= 0 && rec_init[1] + 2 <= 2 * num){//target has a point in the above
			if (rec_init[0] == source[0] && rec_init[1] + 2 == source[1]){//above is the source?
				cout << "find target above" << endl;//furthur replaced by drawing red line
				setlinestyle(SOLID);
				setcolor(RED);
				drawline((100 * ((rec_init[0])) / 2) + 1 * row + 5., 100 * (num - (rec_init[1]) / 2 - 1) + 55., (100 * ((rec_init[0])) / 2) + 1 * row + 5., 100 * (num - (rec_init[1]) / 2 - 1) + 105.);
                flushinput();
                delay();
                delay();
				mark = 1;
				continue;
			}
		}
		if (rec_init[0] >= 0 && rec_init[1] - 2 >= 0){//target has a point in the below
			if (rec_init[0] == source[0] && rec_init[1] - 2 == source[1]){//below is the source?
				cout << "find target below" << endl;//furthur replaced by drawing red line
				setlinestyle(SOLID);
				setcolor(RED);
				drawline((100 * ((rec_init[0])) / 2 + 1) + 1 * row + 5., 100 * (num - (rec_init[1]) / 2 - 1) + 155., (100 * ((rec_init[0])) / 2 + 1) + 1 * row + 5., 100 * (num - (rec_init[1]) / 2 - 1) + 205.);
                flushinput();
                delay();
                delay();
				mark = 1;
				continue;
			}
		}
		//none of the four is the target
		if (rec_init[0] - 1>=0){
			if (matrix[rec_init[0] - 1][rec_init[1]] == rec_len){//left value==current value?
				rec_len = rec_len - 1;//change current wire value
				rec_init[0] = rec_init[0] - 2;//change source to new coordinate
				rec_init[1] = rec_init[1];
				setlinestyle(SOLID);
				setcolor(RED);
				drawline((100 * (rec_init[0])) / 2 + 50., 100 * (num - (rec_init[1]) / 2) + 1 * row + 5., (100 * (rec_init[0])) / 2 + 100., 100 * (num - (rec_init[1]) / 2) + 1 * row + 5.);
                flushinput();
                delay();
                delay();
				
				cout << "mark the path left" << endl;
				continue;//find the next target finish this loop to next
			}
		}
		
		if (rec_init[0] + 1<=2*num){
			if (matrix[rec_init[0] + 1][rec_init[1]] == rec_len){//right value==current value?
				rec_len = rec_len - 1;//change current wire value
				rec_init[0] = rec_init[0] + 2;//change source to new coordinate
				cout << "rec_init=" << rec_init[0] << endl;
				rec_init[1] = rec_init[1];
				setlinestyle(SOLID);
				setcolor(RED);
				drawline((100 * (rec_init[0] - 2) / 2) + 50., 100 * (num - (rec_init[1]) / 2) + 1 * row + 5., (100 * (rec_init[0] - 2) / 2) + 100., 100 * (num - (rec_init[1]) / 2) + 1 * row + 5.);
                flushinput();
                delay();
                delay();
				
				cout << "mark the path right" << endl;
				continue;//find the next target finish this loop to next
			}
		}
		
		if (rec_init[1] + 1<=2*num){
			if (matrix[rec_init[0]][rec_init[1] + 1] == rec_len){//above value==current value?
				rec_len = rec_len - 1;//change current wire value
				rec_init[0] = rec_init[0];//change source to new coordinate
				rec_init[1] = rec_init[1] + 2;
				setlinestyle(SOLID);
				setcolor(RED);
				drawline((100 * ((rec_init[0])) / 2) + 1 * row + 5., 100 * (num - (rec_init[1]) / 2-1) + 155., (100 * ((rec_init[0])) / 2) + 1 * row + 5., 100 * (num - (rec_init[1]) / 2-1) + 205.);
                flushinput();
                delay();
                delay();
				
				cout << "mark the path above" << endl;
				continue;//find the next target finish this loop to next
			}
		}
		
		if (rec_init[1] - 1>=0){
			if (matrix[rec_init[0]][rec_init[1] - 1] == rec_len){//below value==current value?
				rec_len = rec_len - 1;//change current wire value
				rec_init[0] = rec_init[0];//change source to new coordinate
				rec_init[1] = rec_init[1] - 2;
				setlinestyle(SOLID);
				setcolor(RED);
				drawline((100 * ((rec_init[0])) / 2 + 1) + 1 * row + 5., 100 * (num - (rec_init[1]) / 2-1) + 55., (100 * ((rec_init[0])) / 2 + 1) + 1 * row + 5., 100 * (num - (rec_init[1]) / 2-1) + 105.);
                flushinput();
                delay();
                delay();
				
				cout << "mark the path below" << endl;
				continue;//find the next target finish this loop to next
			}
		}

	}//while

}
void delay(void) {

	/* A simple delay routine for animation. */

	int i, j, k, sum;

	sum = 0;
	for (i = 0; i<100; i++)
	for (j = 0; j<i; j++)
	for (k = 0; k<1000; k++)
		sum = sum + i + j - k;
}
