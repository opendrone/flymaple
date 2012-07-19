#ifndef VECTOR_H
#define VECTOR_H
#define NDEBUG
#include "Matrix.h"

template<typename T>
class Vector {
	int sz;
	T * data;
public:
	Vector();
	Vector(const Vector<T> & v);
	Vector(int sz);
	~Vector();
	T & operator()(int i) const;
	int size() const;
	Vector<T> & operator=(const Vector<T> & b);
	
	template<typename T1,typename T2> friend T1 inner_prod(const Vector<T1> & a,const Vector<T2> & b);
	template<typename T1,typename T2> friend Vector<T1> cross_prod(const Vector<T1> & a,const Vector<T2> & b);
	template<typename T1,typename T2> friend Vector<T1> operator+(const Vector<T1> & a,const Vector<T2> & b);
	template<typename T1,typename T2> friend Vector<T1> operator-(const Vector<T1> & a,const Vector<T2> & b);
	template<typename T1> friend Vector<T1> operator*(const Vector<T1> & a,double s);
	template<typename T1> friend Vector<T1> operator*(double s,const Vector<T1> & a);
	template<typename T1> friend Vector<T1> operator/(const Vector<T1> & a,double s);
};

template<typename T>
Vector<T>::Vector()
:sz(0),data(0)
{
}

template<typename T>
Vector<T>::Vector(const Vector<T> & v)
:sz(v.sz),data(0)
{
	T * tmp = new T[sz]();
	for(int i = 0 ; i < sz ; i++) tmp[i] = v.data[i];
	data = tmp;
}

template<typename T>
Vector<T>::Vector(int s)
:sz(s)
{
#ifndef NDEBUG
	assert(sz > 0);
#endif
	data = new T[sz]();
}

template<typename T>
Vector<T>::~Vector()
{
	if(data) delete[] data;
}

template<typename T>
T & Vector<T>::operator()(int i) const
{
#ifndef NDEBUG
	assert(0 <= i && i < sz);
#endif
	return data[i];
}

template<typename T>
int Vector<T>::size() const
{
	return sz;
}

template<typename T>
Vector<T> & Vector<T>::operator=(const Vector<T> & b)
{
	sz = b.sz;
	T * tmp = new T[sz]();
	for(int i = 0 ; i < sz ; i++) tmp[i] = b.data[i];
	if(data) delete[] data;
	data = tmp;
	return *this;
}

template<typename T1,typename T2>
T1 inner_prod(const Vector<T1> & a,const Vector<T2> & b)
{
#ifndef NDEBUG
	assert(a.sz == b.sz);
	assert(a.sz > 0);
#endif
	T1 sum = 0;
	for(int i = 0 ; i < a.size() ; i++) sum += a.data[i] * b.data[i];
	return sum;
}

template<typename T1,typename T2> 
Vector<T1> cross_prod(const Vector<T1> & a,const Vector<T2> & b)
{
#ifndef NDEBUG
	assert(a.sz == b.sz);
	assert(a.sz > 0);
#endif
	Vector<T1> retVal(a.sz);
	Matrix<T1> m(3,a.sz);
	for(int w = 0 ; w < a.sz ; w++) {
		m(0,w) = 1;	m(1,w) = a(w);	m(2,w) = b(w);
	}
	for(int w = 0 ; w < a.sz ; w++) {
		Matrix<T1> minor = m.minor(0,w);
		retVal(w) = ((w + 1)%2 + (w + 1)%2 - 1) * det(minor);
	}
	return retVal;
}

template<typename T1,typename T2> 
Vector<T1> operator+(const Vector<T1> & a,const Vector<T2> & b)
{
#ifndef NDEBUG
	assert(a.sz == b.sz);
	assert(a.sz > 0);
#endif
	Vector<T1> retVal(a.sz);
	for(int i = 0 ; i < a.sz ; i++) retVal(i) = a(i) + b(i);
	return retVal;
}

template<typename T1,typename T2> 
Vector<T1> operator-(const Vector<T1> & a,const Vector<T2> & b)
{
#ifndef NDEBUG
	assert(a.sz == b.sz);
	assert(a.sz > 0);
#endif
	Vector<T1> retVal(a.sz);
	for(int i = 0 ; i < a.sz ; i++) retVal(i) = a(i) - b(i);
	return retVal;
}

template<typename T1> 
Vector<T1> operator*(const Vector<T1> & a,double s)
{
	Vector<T1> retVal(a.sz);
	for(int i = 0 ; i < a.sz ; i++) retVal(i) = a(i) * s;
	return retVal;
}

template<typename T1> 
Vector<T1> operator*(double s,const Vector<T1> & a)
{
	return operator*(a,s);
}

template<typename T1> 
Vector<T1> operator/(const Vector<T1> & a,double s)
{
	Vector<T1> retVal(a.sz);
	for(int i = 0 ; i < a.sz ; i++) retVal(i) = a(i) * 1.0 / s;
	return retVal;
}

#endif
