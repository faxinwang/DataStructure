#include "Matrix.hpp"
#include<iostream>
using namespace std;

template<typename T>
void print(Matrix<T>& m, string str=""){
    int row = m.row(), col = m.column();
    cout<<"//"<<str<<endl;
    printf("[%dX%d]:\n", row,col);
    for(int i=0; i<row; ++i){
        for(int j=0; j<col; ++j) printf("%-5d", m[i][j]);
        printf("\n");
    }
    cout<<endl;
}

int main(){
	/********** test create ***********/
	
	//create zero matrix
    Matrix<int> m1(4, 6);
    print(m1, "m1 after created:");
    /*
    //m1 after created:
	[4X6]:
	0    0    0    0    0    0
	0    0    0    0    0    0
	0    0    0    0    0    0
	0    0    0    0    0    0
	*/
	
    //create matrix with value 3
    Matrix<int> m2(4, 6, 3);
    print(m2, "m2 after created:");
    /*
    //m2 after created:
	[4X6]:
	3    3    3    3    3    3
	3    3    3    3    3    3
	3    3    3    3    3    3
	3    3    3    3    3    3
	*/
	
	//copy constructor
    Matrix<int> m3(m2);
    print(m3, "m3 after copy constructed from m2:");
    /*
	//m3 after copy constructed from m2:
	[4X6]:
	3    3    3    3    3    3
	3    3    3    3    3    3
	3    3    3    3    3    3
	3    3    3    3    3    3
	*/
	
	//partly copied from m3
	Matrix<int> m4(m3,4,3);
	print(m4, "m4 after partly copy constructed from m3:");
	/*
	//m4 after partly copy constructed from m3:
	[4X3]:
	3    3    3
	3    3    3
	3    3    3
	3    3    3
	*/
	
	/********** test operators ***************/
	
	//operator+(T value)
	Matrix<int> m5 = m4 + 2;
	print(m5, "m5 = m4 + 2, m5:");
	/*
	//m5 = m4 + 2, m5:
	[4X3]:
	5    5    5
	5    5    5
	5    5    5
	5    5    5
	*/
	
	//operator+=(T value)
	m5+=2;
	print(m5, "m5 += 2; m5:");
	/*
	//m5 += 2; m5:
	[4X3]:
	7    7    7
	7    7    7
	7    7    7
	7    7    7
	*/
	
//	operator+=(Matrix<T> mtx)
	m5 += m4;
	print(m5,"m5 += m4; m5:");
	/*
	//m5 += m4; m5:
	[4X3]:
	10   10   10
	10   10   10
	10   10   10
	10   10   10
	*/
	
	//operator+(Matrix<T> mtx)
	Matrix<int> m6 = m5 + m4;
	print(m6, "m6 = m5 + m4; m6:");
	/*
	//m6 = m5 + m4; m6:
	[4X3]:
	13   13   13
	13   13   13
	13   13   13
	13   13   13
	*/
	
	//operator*(T value)
	m6 = m6 * 2;
	print(m6, "m6 = m6 * 2; m6:");
	/*
	//m6 = m6 * 2; m6:
	[4X3]:
	26   26   26
	26   26   26
	26   26   26
	26   26   26
	*/
	
	//operator*=(T value)
	m6 *= 2;
	print(m6, "m6 *= 2; m6:");
	/*
	//m6 *= 2; m6:
	[4X3]:
	52   52   52
	52   52   52
	52   52   52
	52   52   52
	*/
	
	//operator/(T value)
	m6 = m6 / 2;
	print(m6,"m6 = m6 / 2; m6:");
	/*
	//m6 = m6 / 2; m6:
	[4X3]:
	26   26   26
	26   26   26
	26   26   26
	26   26   26
	*/
	
	//operator/=(T value)
	m6 /= 5;
	print(m6,"m6 /= 5; m6:");
	/*
	//m6 /= 5; m6:
	[4X3]:
	5    5    5
	5    5    5
	5    5    5
	5    5    5
	*/
	
	Matrix<int> m7(3,4,2);
	print(m7,"m7 after created with value 2");
	/*
	//m7 after created with value 2
	[3X4]:
	2    2    2    2
	2    2    2    2
	2    2    2    2
	*/
	
	//opeator*(Matrix<T> &mtx)
	m7 = m6 * m7;
	print(m7, "m7 = m6 * m7; m7:");
	/*
	//m7 = m6 * m7; m7:
	[4X4]:
	30   30   30   30
	30   30   30   30
	30   30   30   30
	30   30   30   30
	*/
	
	//operator-=(T value)
	m7 -= 10;
	print(m7, "m7 -= 10; m7:");
	/*
	//m7 -= 10; m7:
	[4X4]:
	20   20   20   20
	20   20   20   20
	20   20   20   20
	20   20   20   20
	*/
	
	//operator-(T value)
	//Matrix(const Matrix& mtx)
	Matrix<int> m8 = m7 - 10;
	print(m8, "m8 = m7 - 10; m8:");
	/*
	//m8 = m7 - 10; m8:
	[4X4]:
	10   10   10   10
	10   10   10   10
	10   10   10   10
	10   10   10   10
	*/
	
	//operator-(Matrix<T> &mtx)
	m8 = m7 - m8;
	print(m8, "m8 = m7 - m8; m8:");
	/*
	//m8 = m7 - m8; m8:
	[4X4]:
	10   10   10   10
	10   10   10   10
	10   10   10   10
	10   10   10   10
	*/
	
	//operator-=(Matrix<T> &mtx)
	m8 -= m8;
	print(m8, "m8 -= m8; m8:");
	/*
	//m8 -= m8; m8:
	[4X4]:
	0    0    0    0
	0    0    0    0
	0    0    0    0
	0    0    0    0
	*/
	
	//modify m1 and gets its transposed matrix
	m1[0][2] = 1;
	m1[0][4] = 2;
	m1[1][2] = 3;
	m1[1][5] = 3;
	m1[2][3] = 4;
	m1[2][5] = 5;
	m1[3][1] = 6;
	m1[3][5] = 7;
	print(m1, "m1 after modified:");
	
	Matrix<int> m1tran = m1.transpose();
	print(m1tran, "m1's transposed matrix:");
	
	Matrix<int> product1 = m1 * m1tran;
	print(product1, "product1 = m1 * m1tran, product1:");
	
    return 0;
}
