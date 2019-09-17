struct van{
	int *grid;
	int **fifo;
	int n, l, con_num, pl, n_con, w_con, t_con;
};
van path(van f_in, int n);