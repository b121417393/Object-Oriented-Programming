#include <iostream> 

using namespace std;

class Matrix{

	public:

		Matrix (int n=2);  //constructor
		Matrix (const Matrix& m); // copy constructor
		~Matrix(); // destructor

		void readMatrix(); //Read matrix content
		int size() const; //Returns the number of rows of the matrix
		int type() const;

		void operator=(const Matrix& m); //copy assignment
		double operator()(int i, int j) const; //Returns the value of the i-th column and the j-th row of the matrix
		friend ostream& operator<<(ostream& out, const Matrix& x); //Can print the contents of the matrix with cout << x
		Matrix operator+(const Matrix& rt);  //Matrix plus matrix
		Matrix operator-(const Matrix& rt);  //Matrix subtracte matrix
		Matrix operator*(const Matrix& rt);  //Matrix multiplicate matrix
		Matrix operator*(double s);  //Matrix multiplicate constant
		friend Matrix operator*(double s, const Matrix& rt);  //Constant multiplicate matrix

		void operator+=(const Matrix& m);  //Matrix A+=B = Matrix A + Matrix B
		void operator-=(const Matrix& m);  //Matrix A-=B = Matrix A - Matrix B
		void operator*=(const Matrix& m);  //Matrix A*=B = Matrix A * Matrix B
		void operator*=(double s);  //Matrix A*=S = Matrix A * constant S

	private:
		double *data;
		int my_size;
		int my_type; // type (upper: 1, lower:0)

};
