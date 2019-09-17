//#include "stdafx.h"
#include "solver.h"


solver::solver()
{
}


solver::~solver()
{
}
void solver::solve_matrix(){
	extern vec_rec rec_val;
	extern vector<int> nget;
	int m_length = nget.size();
	vector<vector<double>>r_q = cm.matrix_calculation();
	int coordinate = 0;
	cout << "X coordinate input 1, Y coordinate input 0" << endl;
	cin >> coordinate;
	vector<double>r_b = cm.get_b(coordinate);
	linear_parameter matl = cm.mat(r_q, r_b);
	int i_size = matl.Ai.size();
	cout<<i_size;

	int x_size = matl.Ax.size();
	cout<<x_size;
	/*int    *Ap = new int(m_length);
	int    *Ai = new int(i_size);
	double *Ax = new double(x_size);
	double *b = new double(m_length);
	double *x = new double(m_length);
	cout<<"work"<<endl;*/
	int    Ap[86];
	int    Ai[1729];
	double Ax[1729];
	double b [85];
	double x[85];
	cout<<"work"<<endl;
	cout<<r_b[0]<<endl;
	cout<<matl.Ai[1728]<<endl;;
	for (int k = 0; k < m_length+1; k++){
		Ap[k] = matl.Ap[k];
		cout<<Ap[k]<<endl;
		b[k] = r_b[k];
		//Ap[k] = matl.Ap[k];
	}
	for (int y = 0; y < i_size; y++){
		Ai[y] = matl.Ai[y];
	}
	for (int r = 0; r < x_size; r++){
		Ax[r] = matl.Ax[r];
	}
	cout<<Ap[1]<<endl;
	cout<<matl.Ap[3]<<endl;
	double *null = (double *)NULL;
	int i;
	void *Symbolic, *Numeric;
	(void)umfpack_di_symbolic(m_length, m_length, Ap, Ai, Ax, &Symbolic, null, null);
	cout<<"still work"<<endl;
	(void)umfpack_di_numeric(Ap, Ai, Ax, Symbolic, &Numeric, null, null);
	umfpack_di_free_symbolic(&Symbolic);
	(void)umfpack_di_solve(UMFPACK_A, Ap, Ai, Ax, x, b, Numeric, null, null);
	cout<<"still work"<<endl;
	umfpack_di_free_numeric(&Numeric);
	cout<<"still work"<<endl;
	for (i = 0; i < m_length; i++) printf("x [%d] = %g\n", i, x[i]);

	//return void;
		
	
}
