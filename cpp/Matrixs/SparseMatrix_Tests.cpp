#include <iostream>
#include "SparseMatrix.hpp"
#include "Matrix.hpp"
using namespace std;
using namespace wfx;

template<typename T>
void print(Matrix<T>& m, string str=""){
    int row = m.row(), col = m.column();
    cout<<"//"<<str<<endl;
    printf("[%d X %d]:\n", row,col);
    for(int i=0; i<row; ++i){
        for(int j=0; j<col; ++j) cout<<m[i][j]<<"\t";
        cout<<endl;
    }
    cout<<endl;
}

int main(){
    Matrix<int> m1(3,5);
    m1[0][1] = 1;
    m1[1][2] = 2;
    m1[1][3] = 3;
    m1[2][3] = 4;
    m1[2][4] = 5;
    print(m1, "m1 after create and assigned some values:");
    /*
    //m1 after create and assigned some values:
	[3 X 5]:
	0       1       0       0       0
	0       0       2       3       0
	0       0       0       4       5
	*/
    
    
    MatrixTriple<int> mt1(m1);
    mt1.printMatrix("mt1 created from m1:");
	/*
	mt1 created from m1:
	size:5
	[3 X 5]
	0       1       0       0       0
	0       0       2       3       0
	0       0       0       4       5
	*/
	
	m1[0][1] = -1;
	
	MatrixTriple<int> mt2(m1);
	mt2.printMatrix("m1[0][1]=-1, mt2 created from m1:");
	/*
	m1[0][1]=-1, mt2 created from m1:
	size:5
	[3 X 5]
	0       -1      0       0       0
	0       0       2       3       0
	0       0       0       4       5
	*/
	
	mt1 += mt2;
	mt1.printMatrix("mt1 += mt2; mt1:");
	/*
	mt1 += mt2; mt1:
	size:4
	[3 X 5]
	0       0       0       0       0
	0       0       4       6       0
	0       0       0       8       10
	*/
	
	mt1 = mt1 + mt2;
	mt1.printMatrix("mt1 = mt1 + mt2; mt1:");
	/*
	mt1 = mt1 + mt2; mt1:
	size:5
	[3 X 5]
	0       -1      0       0       0
	0       0       6       9       0
	0       0       0       12      15
	*/
	
	MatrixTriple<int> mt3 = mt2.transpose();
	mt3.printMatrix("mt3 = mt2.transpose(); mt3:");
	/*
	mt3 = mt2.transpose(); mt3:
	size:5
	[5 X 3]
	0       0       0
	-1      0       0
	0       2       0
	0       3       4
	0       0       5
	*/
	
	Matrix<int> m4 = mt1.toMatrix();
	Matrix<int> m5 = mt3.toMatrix();
	
	mt3 = mt3 * mt1;
	mt3.printMatrix("mt3 = mt3 * mt1; mt3:");
	/*
	mt3 = mt3 * mt1; mt3:
	size:8
	[5 X 5]
	0       0       0       0       0
	0       1       0       0       0
	0       0       12      18      0
	0       0       18      75      60
	0       0       0       60      75
	*/
	
	
	Matrix<int> m6 = m5 * m4;
	print(m6, "m6 = m5 * m4; m6:");
	/*
	//m6 = m5 * m4; m6:
	[5 X 5]:
	0       0       0       0       0
	0       1       0       0       0
	0       0       12      18      0
	0       0       18      75      60
	0       0       0       60      75
	*/
	
    return 0;
}
