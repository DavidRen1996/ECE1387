struct path{
	int *grid;
	int **fifo;
	int n, l, con_num, pl, n_con, w_con, t_con;
};
path pathRender(path f_in, int n);