#include <stdio.h>
#include "graphics.h"
#include "pathRender.h"
#include "a_test.h"
#include "router.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include  <vector>
#include <fstream>
using namespace std;
// Callbacks for event-driven window handling.
void delay(void);


// For example showing entering lines and rubber banding

int main() {
	
	int m = 0;
	double num[200];
	ifstream file;
	file.open("circuit.txt");
	while (!file.eof())
	{
		file >> num[m++];
	}
	int n = num[0];//need modified to auto extract data from num
	int w = num[1];
	int p = 3;
	int q = 3;
	int x = 0;
	int y = 0;
	int z = num[19];
	int **a = new int*[2 * n + 1];
	for (int k = 0; k<2 * n + 1; k++) {
		a[k] = new int[2 * n + 1];
	}
	for (int i = 0; i < 2 * n + 1; i++){
		//cout << i;
		for (int j = 0; j < 2 * n + 1; j++){
			if (i % 2 == 0){
				if (j % 2 == 0){
					a[i][j] = 0;//switch blocks are 0
				}
				else
					a[i][j] = 1;//pathes are 1
			}
			else {
				if (j % 2 == 1){
					a[i][j] = 0;//logic blocks are 0
				}
				else
					a[i][j] = 1;// paths are 1
			}
		}

	}
	
	a[2 * p + 2][2 * q] = 's';//we use the swicth behind source logic to be source
	a[2 * x + 2][2 * y] = 't';//we use the swicth behind target logic to be target
	cout << a[2 * x + 2][2 * y] << endl;
	cout << a[2 * p + 2][2 * q] << endl;
	int *rng = new int[2];
	rng[0] = 2 * p + 2;// need improve to auto assign
	rng[1] = 2 * q;
	path recv;
	recv.n = 0;
	recv.fifo = a;//bad naming fifo is used to receive 2n+1,2n+1 matrix
	recv.grid = rng;//used to recive expansion list
	recv.l = 2;
	recv.con_num = 2;
	recv.pl = 0;
	recv.n_con = 2;
	recv.w_con = 0;
	recv.t_con = 0;

	for (recv.con_num = 0; recv.n == 0; recv.con_num = recv.con_num + 2){
		recv = pathRender(recv, n);
		cout << "finish a loop" << endl;
	}
	int source[2] = { 2 * p + 2, 2 * q };
	int init_arr[2] = { 2 * x + 2, 2 * y };
	cout << recv.pl << endl;
	int pass_len = recv.pl;
	int par[3] = { recv.pl, n, z };
	printf("About to start graphics.\n");
	init_graphics("Some Example Graphics", WHITE);

	/* still picture drawing allows user to zoom, etc. */
	// Set-up coordinates from (xl,ytop) = (0,0) to 
	// (xr,ybot) = (1000,1000)
	init_world(0., 0., 1000., 1000.);
	update_message("Interactive graphics example.");
	
	for (int y_num = 0; y_num < 4; y_num++){//drawing the logic blocks
		for (int l_num = 0; l_num < 4; l_num++){
			setcolor(DARKGREEN);
			//drawtext(500., 610., "drawrect", 150.);
			drawrect(100 * l_num + 50., 100 * y_num + 50., 100 * l_num + 100., 100 * y_num + 100.);//x,y for start and finish, start at 50,50 ,length of square is 50
			flushinput();
			delay();
		}
		
	}
	for (int len_num = 0; len_num < 5; len_num++){
		for (int lines = 0; lines < 4; lines++){
			for (int row = 0; row < 8; row++){
				setlinestyle(SOLID);
				drawline(100 * lines + 50., 100 * len_num + 1 * row + 5., 100 * lines + 100., 100 * len_num + 1 * row + 5.);//from above to below
                flushinput();
			    delay();
			}
		}
	}
	for (int len_num = 0; len_num < 4; len_num++){
		for (int lines = 0; lines < 5; lines++){
			for (int row = 0; row < 8; row++){
				setlinestyle(SOLID);
				drawline(100 * lines + 1 * row + 5., 100 * len_num + 55., 100 * lines + 1 * row + 5., 100 * len_num + 105.);//from left to right
                flushinput();
			    delay();
			}
		}
	}
	draw(recv.fifo, init_arr, source, par);
	delay();
	delay();
	flushinput();

	//clearscreen();
	update_message("Non-interactive (animation) graphics example.");


	/* Draw an interactive still picture again.  I'm also creating one new button. */
	//close_graphics();
	printf("Graphics closed down.\n");
	//system("pause");
	return (0);
}







