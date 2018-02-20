#ifndef _MatrixTriple_H_
#define _MatrixTriple_H_

#include "../Vector/Vector.hpp"
#include "../require.hpp"
#include "Matrix.hpp"
#include<iostream>
#include<sstream>
#include<string>

template<typename T>
class MatrixTriple{
private:
    struct Triple{
        T val; 		//value
        int x,y;	//coordinate of value in the matrix
        Triple():x(0),y(0),val(T()){}
        Triple(int x, int y, T val=T()):x(x),y(y),val(val){}
    };
private:
    T _zero;
    int _row, _col;
    Vector<Triple> _v;
public:
    /*****constructors*******/
	MatrixTriple(const Matrix<T>& mtx):_zero(T()), _row(mtx.row()), _col(mtx.column()){
		//init from a Matrix with row priority
		for(int i=0; i<_row; ++i){
			for(int j=0; j<_col; ++j){
				if(mtx[i][j] != _zero) _v.push_back( Triple(i,j,mtx[i][j]) );
			}
		}
	}
	
	MatrixTriple(const MatrixTriple& mt):_zero(mt._zero), _row(mt.row()),_col(mt.column()){
		_v = mt._v;
	}
	
	MatrixTriple& operator=(const MatrixTriple& mt){
		if(this == &mt) return *this;
		_zero = mt._zero;
		_row = mt._row;
		_col = mt._col;
		_v = mt._v; 
		return *this;
	}
	
    /**************/
	//return the number of  row of the matrix
    int row()const { return _row; }
	//return the number of column of the matrix
    int column()const { return _col; }
    //return the number of elements in the matrix
    int size()const { return _v.size(); }
    
    void printMatrix(std::string hint="") const{
        using namespace std;
        int k=0, n = size();
        cout<<hint<<endl;
        cout<<"size:"<<n<<endl;
        cout<<"["<<_row<<" X "<<_col<<"]"<<endl;
        for(int i=0; i<_row; ++i){
            for(int j=0; j<_col; ++j){
                if(k < n && i == _v[k].x && j == _v[k].y) cout<<_v[k++].val<<'\t';
                else cout<<_zero<<'\t';
            }
            cout<<endl;
        }
        cout<<endl;
    }
    
    /*���α�������ϡ�����A��B���к�i���к�j
     *�������������к�i���к�j����ȣ������c=A[i][j] + B[i][j], 
	 *	  ���c��Ϊ0���Ͱ�i,j,c�����Ԫ��ŵ����������ȥ
	 *���򣬽�������������˳����Ž�С��Ԫ�طŵ����������ȥ��Ȼ���������þ����е���һ��Ԫ�� 
	 */ 
    MatrixTriple& operator+=(MatrixTriple& mtx){
    	stringstream ss;
    	require(mtx.row() == _row,
			(ss<<"row do not match. this.row="<<_row<<" mtx.row="<<mtx.row(),ss));
    	require(mtx.column() == _col, 
			(ss.str(""), ss<<"column do not match. this.column="<<_col<<" mtx.column="<<mtx.column(),ss));
			
    	int i=0, j=0, n1=size(), n2=mtx.size();
    	Vector<Triple> res;
    	Vector<Triple> &v1 = _v, &v2 = mtx._v;
    	
    	while(i<n1 && j<n2){
    		if(v1[i].x == v2[j].x){
    			if(v1[i].y == v2[j].y ){
    				Triple t = v1[i];
    				t.val = v1[i].val + v2[j].val;
    				//check if the result is zero, do not push zero to result vector 
    				if(t.val != _zero) res.push_back( t );
					++i;
    				++j;
				}
				else res.push_back( v1[i].y < v2[j].y ? v1[i++] : v2[j++]);
			}
			else res.push_back( v1[i].x < v2[j].x ? v1[i++] : v2[j++] );
		}
		
		while(i<n1) res.push_back(v1[i++]);
		while(j<n2) res.push_back(v2[j++]);
		_v = res; 
		return *this;
	}
	
	MatrixTriple operator+(MatrixTriple& mt)const {
		MatrixTriple ret(*this);
		ret += mt;
		return ret;
	}
	
	//return the value at row=x and col=y
	T getValue(int x,int y)const {
		for(int i=0,n=size(); i<n; ++i) {
			if(_v[i].x == x && _v[i].y == y) return _v[i].val;
			if(_v[i].x > x ||(_v[i].x==x && _v[i].y > y)) break;
		}
		return _zero;
	}
	
	MatrixTriple operator*(MatrixTriple& mt)const {
		stringstream ss;
		require(_col == mt.row(), 
			(ss<<"operator*: dimension do not match. this.col="<<_col<<" mtx.row="<<mt.row(), ss));
		int n = _row, k = _col, m = mt.column();
		MatrixTriple ret(*this);
		ret._v.clear();
		ret._col = n;
		ret._col = m;
		for(int i=0; i<n; ++i){
			for(int j=0; j<m; ++j){
				T s = T();
				for(int h=0; h<k; ++h) s += getValue(i,h) * mt.getValue(h,j);
				if(s != _zero ) ret._v.push_back( Triple(i,j,s) );
			}
		}
		return ret;
	}
	
	//return the transposed matrix of this matrix
	/*������Ԫ���и�Ԫ�ص������е��±꣬�����䰴��ԭ���������ȵ�˳��洢 
	 ��������Ϊ��
	 1.�����ڵ�ǰ�������ҳ���һ�е�����Ԫ�أ�������ת�þ����е�һ�е�Ԫ�أ�
	   ���Խ��������η����������� 
	 2.����ͬ���ķ������н��У�ֱ���ҳ���N-1�е�����Ԫ�أ������������η���
	   ��������� 
	*/ 
	MatrixTriple transpose()const {
		MatrixTriple ret(*this);
		ret._v.clear();
		ret._col = _row;
		ret._row = _col;
		for(int i=0; i<_col; ++i){
			for(int j=0,n=_v.size(); j<n; ++j){
				if(_v[j].y == i) ret._v.push_back( Triple( _v[j].y, _v[j].x, _v[j].val) );
			}
		}
		return ret;
	}
	
	//convert to Matrix
	Matrix<T> toMatrix(){
		int k=0,n = _v.size();
		Matrix<T> mtx(_row, _col);
		for(int i=0; i<_row; ++i){
			for(int j=0; j<_col; ++j){
				if(k < n){
					if(i == _v[k].x && j==_v[k].y) mtx[i][j] = _v[k++].val;
					else mtx[i][j] = _zero;
				}else mtx[i][j] = _zero;
			}
		}
		return mtx;
	}
};


#endif
