#include "stdafx.h"
#include "net.h"


net::net()//get net number
{
	//net_number = i;
}


net::~net()
{
}
mov net:: moveable(int i){//return the number of fixed blocks in a net, also return the number of fixed blocks in that net
	int net = i;
	//extern vec_rec rec_val;
	vector<int>rec = get_num(net);//get the net and its content
	extern vector<double>fget;
	vector<double>f_rec = fget;//vector that only contain block number
	vector<int>mv;
	int m_num = 0;
	int n = rec.size();//get size of the net vector
	//cout << "net size=" << n << endl;
	int m = f_rec.size();//get size of fixed block number
	//cout << "fix size=" << m << endl;
	for (int x = 0; x < n; x++){//loop over all contents in net
		for (int y = 0; y < m; y++){//loop over all content in block vector
			if (rec[x] == f_rec[y]){//find fixed block
				m_num = m_num + 1;
				//cout << m_num;
				mv.push_back(rec[x]);
				break;
			}
			else{
				continue;
			}
		}
	}

	mov m_return;
	if (m_num == 0){//the net has no connection to fixed block
		m_return.mv.push_back(1);
		m_return.m_num = m_num;
	}
	else{
		m_return.mv = mv;
		m_return.m_num = m_num;
	}

	//cout << "number of fixed" << m_num << endl;
	return m_return;
}
vector<int> net::get_num(int i){
	int net = i;// net number for search
	int block = 0;//store the value of block number
	extern vec_rec rec_val;
	vec_rec globalVector = rec_val;
	vector<int>net_content;//return the net i's content in a vector
	int stop = globalVector.total_numbers - globalVector.fixed_numbers - 2;//count stop when finished cheking all blocks
	
	int begin = 1;//tell the for loop the number is node or net
	for (int i = 0; i < stop; i++){
		if (globalVector.a[i] == -1){//judge if is the end of line
			begin = 1;
			continue;//move to next line
		}
		else{
			if (begin == 1){//if the number is the block?
				block = globalVector.a[i];//assign the block number to store
				begin = 0;//start searching for net i
				i = i + 1;
				continue;
			}
			else{//number is for a net
				if (globalVector.a[i] == net){
					net_content.push_back(block);
				}
			}

		}
	}

	return net_content;
}
double net::get_weight(int net_number){// get net i's weight
	vector<int>net_recv = get_num(net_number);//get net i's content
	int net_size = net_recv.size();
	//cout << "net i'"<<i<<"s size is= " <<net_size << endl;
	double weight = 2.0 / net_size;
	//cout << "net i'" << i << "s weight is= " << weight << endl;
	return weight;
}
double net::get_wl(int i){//must take special care about net:: function is to get wl of a net, take input of net number i
	vector<int>mb = get_mv(i);
	extern vec_rec rec_val;
	vec_rec w = rec_val;
	int f_size = w.fixed_numbers / 3;
	//mov n_wl = moveable(i);
	xy wl_recv = vans.get_cfile();//get moveable blocks and x,y coordiante
	//cout << n_wl.mv[0] - f_size - 1;
	int m_length = mb.size();
	double Xmax = 0;
	double Xmin = 100;
	double Ymax = 0;
	double Ymin = 100;
	//cout << mb[1] << endl;
	//cout << wl_recv.y[mb[0] - f_size - 1] << endl;
	for (int x = 0; x < m_length; x++){//loop all moveable blocks 

		if (wl_recv.x[mb[x] - f_size-1]>Xmax){
			Xmax = wl_recv.x[mb[x] - f_size - 1];
		}
		if (wl_recv.x[mb[x] - f_size - 1] < Xmin){
			Xmin = wl_recv.x[mb[x] - f_size - 1];
		}

		if (wl_recv.y[mb[x] - f_size - 1]>Ymax){
			Ymax = wl_recv.y[mb[x] - f_size - 1];
		}
		
		if (wl_recv.y[mb[x] - f_size - 1] < Ymin){
				Ymin = wl_recv.y[mb[x] - f_size - 1];
		}

	}
	double x_l = Xmax - Xmin;
	double y_l = Ymax - Ymin;
	double r_value=0;

	r_value = x_l + y_l;
	return r_value;
}
vector<int>net::get_mv(int i){
	mov g_mv = moveable(i);
	vector<int>con = get_num(i);
	vector<int>move_b;
	for (int d = 0; d < con.size(); d++){
		int set = 0;
		for (int c = 0; c < g_mv.m_num; c++){
			if (con[d] == g_mv.mv[c]){
				set = 1;
				break;
			}
		}
		if (set == 0){
			move_b.push_back(con[d]);
		}
	}
	return move_b;
}