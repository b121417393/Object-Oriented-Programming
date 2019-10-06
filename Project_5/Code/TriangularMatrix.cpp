#include "TriangularMatrix.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

#define ELEMENT_LEN 10

//constructor
Matrix::Matrix(int n)
{
	data = new double[n*(n+1)/2];
	my_size = n;
	my_type = 0;
	memset(data, 0, n*(n+1)/2);
	return;
}

//Returns the number of rows of the matrix
int Matrix::size() const
{
	return my_size;
}

//Returns the type of the matrix
int Matrix::type() const
{
	return my_type;
}

//Returns the value of the i-th column and the j-th row of the matrix
double Matrix::operator()(int i, int j)const
{
	if(my_type == 0) //lower
		if(j > i) 
			return 0;
		else
			return data[ (i-1) * i / 2 + j-1 ];

	else //upper
		if(j < i) 
			return 0;
		else
			return data[ (my_size + my_size - i + 2)*(i - 1)/2  +  (j - i )];
}

// copy constructor
Matrix::Matrix(const Matrix &m)
{
	my_type = m.type();
	my_size = m.size();
	data = new double[(my_size+1)*my_size/2];

	if(my_type == 0) //lower
	{
		int tmp_row = 1, tmp_col = 1;
		for(int i = 0; i < (my_size+1)*my_size/2; i++)
		{
			data[i] = m(tmp_row, tmp_col);
			tmp_col ++;
			if(tmp_col > tmp_row)
			{
				tmp_row += 1;
				tmp_col = 1;
			}
		}
	}
	else //upper
	{
		int tmp_row = 1, tmp_col = 1;
		for(int i = 0; i < (my_size+1)*my_size/2; i++)
		{
			data[i] = m(tmp_row, tmp_col);
			tmp_col ++;
			if(tmp_col > my_size)
			{
				tmp_row += 1;
				tmp_col = tmp_row;
			}
		}
	}
	return;
}

// destructor
Matrix::~Matrix()
{
	delete data;
	return;
}

//Read matrix content
void Matrix::readMatrix()
{
	cout << "specify number of rows:" << endl;
	cin >> my_size;
	cout << "is upper or lower triangular: (upper: 1, lower:0)" << endl;
	cin >> my_type;
	cout << "input elements of the matrix:" << endl;
	delete data;
	data = new double[my_size * (my_size + 1) / 2];
	for(int i = 0; i < my_size * (my_size + 1) / 2; i ++)
	{
		cin >> data[i];
	}
	return;
}

//copy assignment
void Matrix::operator=(const Matrix& m)
{
	delete data;
	my_type = m.type();
	my_size = m.size();
	data = new double[ my_size * (my_size + 1)/2];
	
	if(my_type == 0) //lower
	{
		int tmp_row = 1, tmp_col = 1;
		for(int i = 0; i < (my_size+1)*my_size/2; i++)
		{
			data[i] = m(tmp_row, tmp_col);
			tmp_col ++;
			if(tmp_col > tmp_row)
			{
				tmp_row += 1;
				tmp_col = 1;
			}
		}
	}
	else //upper
	{
		int tmp_row = 1, tmp_col = 1;
		for(int i = 0; i < (my_size+1)*my_size/2; i++)
		{
			data[i] = m(tmp_row, tmp_col);
			tmp_col ++;
			if(tmp_col > my_size)
			{
				tmp_row += 1;
				tmp_col = tmp_row;
			}
		}
	}
}

//Matrix A+=B = Matrix A + Matrix B
void Matrix::operator+=(const Matrix& m)
{
	if(m.type() != my_type)
	{
		cout<<"You cannot add an upper triangular matrix with a lower triangular matrix" << endl;
		return;
	}

	else if(my_size != m.size())
	{
		cout<<"You cannot add a triangular matrix with a different size triangular matrix" << endl;
		return;
	}

	if(my_type == 0) // lower
	{
		int tmp_row = 1, tmp_col = 1;
		for(int i = 0; i < my_size * (my_size + 1)/2; i++)
		{
			data[i] += m(tmp_row, tmp_col);
			tmp_col ++;
			if(tmp_col > tmp_row)
			{
				tmp_row ++;
				tmp_col = 1;
			}
		}
	}
	else //upper
	{
		int tmp_row = 1, tmp_col = 1;
		for(int i = 0; i < my_size * (my_size + 1)/2; i++)
		{
			data[i] += m(tmp_row, tmp_col);
			tmp_col ++;
			if(tmp_col > my_size)
			{
				tmp_row++;
				tmp_col = tmp_row;
			}
		}
	}
}

//Matrix A-=B = Matrix A - Matrix B
void Matrix::operator-=(const Matrix& m)
{
	if(m.type() != my_type)
	{
		cout<<"You cannot minus an upper triangular matrix with a lower triangular matrix" << endl;
		return;
	}
	else if(my_size != m.size())
	{
		cout<<"You cannot minus a triangular matrix with a different size triangular matrix" << endl;
		return;
	}

	if(my_type == 0) // lower
	{
		int tmp_row = 1, tmp_col = 1;
		for(int i = 0; i < my_size * (my_size + 1)/2; i++)
		{
			data[i] -= m(tmp_row, tmp_col);
			tmp_col ++;
			if(tmp_col > tmp_row)
			{
				tmp_row ++;
				tmp_col = 1;
			}
		}
	}
	else //upper
	{
		int tmp_row = 1, tmp_col = 1;
		for(int i = 0; i < my_size * (my_size + 1)/2; i++)
		{
			data[i] -= m(tmp_row, tmp_col);
			tmp_col ++;
			if(tmp_col > my_size)
			{
				tmp_row++;
				tmp_col = tmp_row;
			}
		}
	}
}

//Matrix A*=B = Matrix A * Matrix B
void Matrix::operator*=(const Matrix& m)
{
	if(m.type() != my_type)
	{
		cout<<"You cannot multiply an upper triangular matrix with a lower triangular matrix" << endl;
		return;
	}
	else if(my_size != m.size())
	{
		cout<<"You cannot multiply a triangular matrix with a different size triangular matrix" << endl;
		return;
	}

	if(my_type == 0) // lower
	{
		double tmp[my_size * (my_size + 1)/2], val = 0;
		int tmp_row = 1, tmp_col = 1;

		for(int i = 0; i < my_size * (my_size + 1)/2; i++)
		{
			val = 0;
			for(int j = tmp_col; j <= tmp_row; j++) 
				val += (*this)(tmp_row, j) * m(j, tmp_col);
			tmp[i] = val;
			tmp_col ++;
			if(tmp_col > tmp_row)
			{
				tmp_row ++;
				tmp_col = 1;
			}
		}

		for(int i = 0; i < my_size * (my_size + 1)/2; i++)
			data[i] = tmp[i];
	}
	else //upper
	{
		double tmp[my_size * (my_size + 1)/2], val = 0;
		int tmp_row = 1, tmp_col = 1;

		for(int i = 0; i < my_size * (my_size + 1)/2; i++)
		{
			val = 0;
			for(int j = tmp_row; j <= tmp_col; j++) 
				val += (*this)(tmp_row, j) * m(j, tmp_col);
			tmp[i] = val;
			tmp_col ++;
			if(tmp_col > my_size)
			{
				tmp_row++;
				tmp_col = tmp_row;
			}
		}

		for(int i = 0; i < my_size * (my_size + 1)/2; i++)
			data[i] = tmp[i];
	}
}

//Matrix A*=S = Matrix A * constant S
void Matrix::operator*=(double s)
{
	int data_size = (my_size + 1) * my_size / 2;

	for(int i = 0; i < data_size; i++)
		data[i] *= s;

	return;
}

//Matrix plus matrix
Matrix Matrix::operator+(const Matrix& rt)
{
	Matrix tmp((*this));
	tmp += rt;
	return tmp;
}

//Matrix subtracte matrix
Matrix Matrix::operator-(const Matrix& rt)
{
	Matrix tmp((*this));
	tmp -= rt;
	return tmp;
}

//Matrix multiplicate matrix
Matrix Matrix::operator*(const Matrix& rt)
{
	Matrix tmp((*this));
	tmp *= rt;
	return tmp;
}

//Matrix multiplicate constant
Matrix Matrix::operator*(double s)
{
	Matrix tmp((*this));
	tmp *= s;
	return tmp;
}

//Constant multiplicate matrix
Matrix operator*(double s, const Matrix& rt)
{
	Matrix tmp(rt);
	tmp *= s;
	return tmp;
}  

//Can print the contents of the matrix with cout << x
ostream& operator<<(ostream& out, const Matrix& x)
{
	out << endl;
	for(int i = 1; i <= x.size(); i++)
	{
		out << setw(ELEMENT_LEN)<<x(i,1);
		for(int j = 2; j <= x.size(); j++)
		{
			out<<" "<<setw(ELEMENT_LEN)<<x(i,j);
		}
		out << endl;
	}
	return out;
}

