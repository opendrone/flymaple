#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>

using namespace std;

template<typename T>
class Matrix {
	int rows,cols;
	T * data;
public:
	Matrix();
	Matrix(const Matrix<T> & m);
	Matrix(const int rows,const int cols);
	~Matrix();
	T & operator()(int row,int col) const;
	int size1() const;
	int size2() const;
	Matrix<T> minor(int rows,int cols) const;
	Matrix<T> & operator=(const Matrix<T> & b);
	
	template<typename N> friend Matrix<N> operator*(const Matrix<N> & a,const Matrix<N> & b);
	template<typename N> friend Matrix<N> inv(const Matrix<N> & a);
	template<typename N> friend Matrix<N> trans(const Matrix<N> & a);
	template<typename N> friend N det(const Matrix<N> & a);
};

template<typename T>
Matrix<T>::Matrix()
:rows(0),cols(0),data(0)
{
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & m)
:rows(m.rows),cols(m.cols),data(0)
{
	T * tmp = new T[rows * cols]();
	for(int i = 0 ; i < rows * cols ; i++) tmp[i] = m.data[i];
	data = tmp;
}

template<typename T>
Matrix<T>::Matrix(const int row,const int col)
:rows(row),cols(col)
{
#ifndef NDEBUG
	assert(rows > 0 && cols > 0);
#endif
	data = new T[rows * cols]();
}

template<typename T>
Matrix<T>::~Matrix()
{
	if(data) delete[] data;
}

template<typename T>
T & Matrix<T>::operator()(int row,int col) const
{
#ifndef NDEBUG
	assert(0 <= row && row < rows);
	assert(0 <= col && col < cols);
#endif
	return data[row * cols + col];
}

template<typename T>
int Matrix<T>::size1() const
{
	return rows;
}

template<typename T>
int Matrix<T>::size2() const
{
	return cols;
}

template<typename T>
Matrix<T> Matrix<T>::minor(int r,int c) const
{
#ifndef NDEBUG
	assert(0 <= r && r < rows);
	assert(0 <= c && c < cols);
	assert(rows >= 2 && cols >= 2);
#endif
	Matrix<T> retVal(rows - 1,cols - 1);
	for(int h = 0 ; h < rows ; h++)
		for(int w = 0 ; w < cols ; w++) {
			if(h == r || w == c) continue;
			int newrows = (h >= r)?h-1:h;
			int newcols = (w >= c)?w-1:w;
			retVal(newrows,newcols) = data[h * cols + w];
		}
	return retVal;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & b)
{
	rows = b.rows; cols = b.cols;
	T * tmp = new T[rows * cols]();
	for(int i = 0; i < rows * cols ; i++) tmp[i] = b.data[i];
	if(data) delete[] data;
	data = tmp;
	return *this;
}

template<typename T>
Matrix<T> operator*(const Matrix<T> & a,const Matrix<T> & b)
{
#ifndef NDEBUG
	assert(a.cols == b.rows);
#endif
	Matrix<T> retVal(a.rows,b.cols);
	for(int h = 0 ; h < a.rows ; h++)
		for(int w = 0 ; w < b.cols ; w++) {
			T sum = 0;
			for(int i = 0 ; i < a.cols ; i++)
				sum += a(h,i) * b(i,w);
			retVal(h,w) = sum;
		}
	return retVal;
}

template<typename T>
Matrix<T> inv(const Matrix<T> & m)
{
#ifndef NDEBUG
	assert(m.cols && m.rows);
	assert(m.cols == m.rows);	//必须是方阵
	assert(m.cols > 1 && m.rows > 1);
	assert(0 != det(m));
#endif
	Matrix<T> retVal = m;
	T * a = retVal.data;
	int n = retVal.rows;
	int * is= new int[n];
	int * js= new int[n];
	for (int k=0; k<=n-1; k++) {
		T d=0.0;
		for (int i=k; i<=n-1; i++)
			for (int j=k; j<=n-1; j++) { 
				int l=i*n+j; T p=((a[l] > 0)?a[l]:-a[l]);
				if (p>d) { d=p; is[k]=i; js[k]=j;}
			}
			if (d + 1.0 == 1.0) {
				delete[] is; delete[] js;
				assert(0);
			}
			if (is[k]!=k)
				for (int j=0; j<=n-1; j++) {
					int u=k*n+j; int v=is[k]*n+j;
					T p=a[u]; a[u]=a[v]; a[v]=p;
				}
			if (js[k]!=k)
				for (int i=0; i<=n-1; i++) {
					int u=i*n+k; int v=i*n+js[k];
					T p=a[u]; a[u]=a[v]; a[v]=p;
				}
			int l = k*n+k;
			a[l]=1.0/a[l];
			for (int j=0; j<=n-1; j++)
				if (j!=k) { int u=k*n+j; a[u]=a[u]*a[l];}
			for (int i=0; i<=n-1; i++)
				if (i!=k)
					for (int j=0; j<=n-1; j++)
						if (j!=k) { 
							int u=i*n+j;
							a[u]=a[u]-a[i*n+k]*a[k*n+j];
						}
			for (int i=0; i<=n-1; i++)
				if (i!=k) {
					int u=i*n+k; 
					a[u]=-a[u]*a[l];
				}
	}
	for (int k=n-1; k>=0; k--) { 
		if (js[k]!=k)
			for (int j=0; j<=n-1; j++) { 
				int u=k*n+j; int v=js[k]*n+j;
				T p=a[u]; a[u]=a[v]; a[v]=p;
			}
		if (is[k]!=k)
			for (int i=0; i<=n-1; i++) { 
				int u=i*n+k; int v=i*n+is[k];
				T p=a[u]; a[u]=a[v]; a[v]=p;
			}
		}
	delete[] is; 
	delete[] js;
	
	return retVal;
}

template<typename T>
Matrix<T> trans(const Matrix<T> & m)
{
#ifndef NDEBUG
	assert(m.cols && m.rows);
#endif
	Matrix<T> retVal(m.cols,m.rows);
	for(int h = 0 ; h < m.rows ; h++)
		for(int w = 0 ; w < m.cols ; w++)
			retVal(w,h) = m(h,w);
	return retVal;
}

template<typename T> 
T det(const Matrix<T> & m)
{
#ifndef NDEBUG
	assert(m.cols && m.rows);
	assert(m.cols == m.rows);
#endif
	double retVal = 0;
	if(m.rows == 1) retVal = m(0,0);
	else if(m.rows == 2) retVal = m(0,0) * m(1,1) - m(1,0) * m(0,1);
	else {
		for(int w = 0 ; w < m.cols ; w++) {
			Matrix<T> minor = m.minor(0,w);
			retVal += ((w+1)%2 + (w+1)%2 - 1) * m(0,w) * det(minor);
		}
	}
	return retVal;
}

#endif
