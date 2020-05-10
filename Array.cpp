//Array.h
#ifndef ARRAY_H
#define ARRAY_H
#include<cassert>

//数组类模板定义
template<class T>
class Array{
private:
	T* list;//T类型指针，存放动态分配的数组内存首地址 
	int size;//数组元素个数 
public:
	Array(int sz = 500);//构造函数 
	Array(const Array<T> &a);//复制构造函数
	~Array();
	Array<T>& operator=(const Array<T> &rhs);//重载”=”使得数组可以整体赋值
	T& operator [] (int i);//重载“[]”，使Array对象可以起到普通C++数组的作用
	const T& operator [] (int i)const;//"[]" 运算符对const类型重载
	operator T*() const;//到T*类型的转换，使Array对象可以起到普通C++数组的作用 
	operator const T*() const;//到T*类型转换操作符针对const的重载
	int getSize() const;//取数组的大小
	void resize(int sz);//修改数组大小
};

//构造函数
template<class T>
Array<T>::Array(int sz){
	assert(sz>=0);//异常检验 
	size = sz;
	list=new T [size]; 
} 

//析构函数
template<class T>
Array<T>::~Array(){
	delete list [];
} 

//复制构造函数
template<class T>
Array<T>::Array(const Array<T> &a){
	size = a.size;
	list = new T[size];
	for(i = 0;i<size;i++){
		list[i] = a.list[i];
	} 
	
//重载"=“运算符，将对象rhs赋值给本对象，实现对象之间的整体赋值
template<class T>
Array<T>& Array<T>::operator=(const Array<T> &rhs){
	if(&rhs != s){
		if(size!= rhs.size){
			delete [] list;
			size = rhs.size;
			list = new T [size];
		}
		for(int i = 0;i<size;i++){
			list[i]=rhs.list[i];
		}
	}
	return *this;
} 

//重载下标运算符，实现与普通数组一样通过下标访问元素，并且具有越界检查功能
template<class T>
T& Array<T>::operator[] (int n){
	assert(n>=0 && n<=size);
	return list[n];
} 

template<class T>
const T& Array<T>::operator[](int n) const{
	assert(n>=0 && n<=size);
	return list[n];
}

//重载指针转换运算符，将Array类的对象名转换为T类型的指针
//指向当前对象的私有数组
//因而可以像使用普通数组首地址一样使用Array类的对象名
template<class T>
Array<T>::operator const T*() const{
	return list;
} 

//取当前数组的大小
template<class T>
int Array<T>::getSize() const{
	return size;
} 

//将数组大小修改为sz
template<class T>
void Array<T>::resize(int sz){
	assert(sz>=0);
	if(sz==size)
		return;
	T* newList = new T [sz];


	int n = (sz<size?)sz:size;
	for(int i = 0;i<n;i++){
		newList[i] = list[i];
	delete [] list;
	list = newList;
	size = sz;
	}
} 
#endif //ARRAY_H
