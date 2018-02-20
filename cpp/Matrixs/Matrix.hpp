#ifndef _Matrix_h_
#define _Matrix_h_

#include "../Vector/Vector.hpp"
#include "../require.hpp"

/*
implement Matrix using Vector of Vectors.
*/
template<typename T>
class Matrix{

private:
    Vector<Vector<T> > _mtx;

public:
    /*construct zero matrix of the given size*/
    Matrix(int row, int col, T value=T()){
        for(int i=0; i<row; ++i) _mtx.push_back( Vector<T>(col, col, value) );
    }

    /*construct from 2D array*/
//    Matrix(T **a, int row, int col){
//        for(int i=0; i<row; ++i) _mtx.push_back( Vector<T>(a[i], 0, col) );
//    }

    /*construct from part of another matrix*/
    Matrix(Matrix& mtx, int row, int col){
        for(int i=0; i<row; ++i) _mtx.push_back( Vector<T>(mtx[i], 0, col) );
    }

    /*copy constructor*/
    Matrix(const Matrix& mtx) { _mtx = mtx._mtx; }

    /*assignment operator*/
    Matrix& operator=(const Matrix& mtx){
        if(this == &mtx) return *this;
        _mtx = mtx._mtx;
        return *this;
    }
    
    //return a row of Vector according to the idx, do not check the index
	Vector<T>& operator[](int idx) { return _mtx[idx]; }
	
	const Vector<T>& operator[](int idx)const{ return _mtx[idx]; }
	
    //return the row of the matrix
    int row()const { return _mtx.size(); }

    //return the column of the matrix
    int column()const { return _mtx.size()? _mtx[0].size() : 0 ; }
	
	// += operator
    Matrix& operator+=(T value){
    	for(int i=0,n=row(); i<n; ++i){
    		for(int j=0,m=column(); j<m; ++j){
    			_mtx[i][j] += value;
			}
		}
		return *this;
	}
	
	// + operator
	Matrix operator+(T value){
    	Matrix<T> ret(*this);
    	ret += value;
		return ret; 
	}
	
	// -= operator
    Matrix& operator-=(T value){
    	(*this) += (-value);
		return *this;
	}
	
	// - operator
	Matrix operator-(T value){
    	Matrix<T> ret(*this);
    	ret += (-value);
		return ret; 
	}
	
	
	// += operator, caller is responsible for the size of the two matrix
	Matrix& operator+=(Matrix& mtx){
		stringstream ss;
        require(row() == mtx.row() && column() == mtx.column(),
                (ss<<"operator+=():dimension do not match, this row="<<row()<<" col="<<column()
                <<" mtx.row="<<mtx.row()<<" mtx.col="<<mtx.column(), ss));
        for(int i=0,n=row(); i<n; ++i){
            for(int j=0,m=column(); j<m; ++j){
                _mtx[i][j] += mtx[i][j];
            }
        }
        return *this;
	}

    // + operator, caller is responsible for the size of the two matrix
    Matrix operator+(Matrix& mtx){
        stringstream ss;
        require(row() == mtx.row() && column() == mtx.column(),
                (ss<<"operator+():dimension do not match, this row="<<row()<<" col="<<column()
                <<" mtx.row="<<mtx.row()<<" mtx.col="<<mtx.column(), ss));
        Matrix ret(*this);
        ret += mtx;
        return ret;
    }
    
    	// -= operator, caller is responsible for the size of the two matrix
	Matrix& operator-=(Matrix& mtx){
		stringstream ss;
        require(row() == mtx.row() && column() == mtx.column(),
                (ss<<"operator+=():dimension do not match, this row="<<row()<<" col="<<column()
                <<" mtx.row="<<mtx.row()<<" mtx.col="<<mtx.column(), ss));
        for(int i=0,n=row(); i<n; ++i){
            for(int j=0,m=column(); j<m; ++j){
                _mtx[i][j] -= mtx[i][j];
            }
        }
        return *this;
	}

    // - operator, caller is responsible for the size of the two matrix
    Matrix operator-(Matrix& mtx){
        stringstream ss;
        require(row() == mtx.row() && column() == mtx.column(),
                (ss<<"operator+():dimension do not match, this row="<<row()<<" col="<<column()
                <<" mtx.row="<<mtx.row()<<" mtx.col="<<mtx.column(), ss));
        Matrix ret(*this);
        ret -= mtx;
        return ret;
    }
    
	// /= operator
	Matrix& operator/=(T value){
		require( value>1e-9||value<-1e-9, "operator/(T value): devided by zero");
		for(int i=0,n=row(); i<n; ++i){
			for(int j=0,m=column(); j<m; ++j){
				_mtx[i][j] /= value;
			}
		}
		return *this;
	}

	// / operator
	Matrix operator/(T value){
		require( value>1e-9||value<-1e-9, "operator/(T value): devided by zero");
		Matrix ret(*this);
		ret /= value;
		return ret;
	}

	// *= operator
	Matrix& operator*=(T value){
		for(int i=0,n=row(); i<n; ++i){
			for(int j=0,m=column(); j<m; ++j){
				_mtx[i] [j] *= value;
			}
		}
		return *this;
	}

	// * operator
	Matrix operator*(T value){
		Matrix ret(*this);
		ret *= value;
		return ret;
	}
	

	
	// * operator, caller is responsible for the size of the two matrix
	Matrix operator*(Matrix& mtx){
		stringstream ss;
		require(column() == mtx.row(),
                (ss<<"operator*():dimension do not match, this row="<<row()<<" col="<<column()
                <<" mtx.row="<<mtx.row()<<" mtx.col="<<mtx.column(), ss));
		
		int n = row(), m = mtx.column(), p = column();
		Matrix ret(n,m);
		for(int i=0; i<n; ++i){
			for(int j=0; j<m; ++j){
				for(int k=0; k<p; ++k) {
					ret[i][j] += _mtx[i][k] * mtx[k][j];
				}
			}
		}
		return ret;
	}
	
	//return a transposed matrix of this matrix
	Matrix transpose(){
		int n = row(), m = column();
		Matrix ret(m,n);
		for(int i=0; i<n; ++i){
			for(int j=0; j<m; ++j){
				ret._mtx[j][i] = _mtx[i][j];
			}
		}
		return ret;
	}
};


#endif
