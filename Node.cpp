//Node.h
#ifndef NODE_H
#define NODE_H

//类模板的定义
template<class T>
class Node{
private:
	Node<T>* next;//指针域 
public:
	T data;//数据域 
	
	Node(const T& data,Node<T>* next = NULL);//构造函数 
	void insertAfter(Node<T>* p);
	void insertBefore(Node<T>* q);
	Node<T>* deleteAfter();//删除后继节点 
	Node<T>* nextNode();//获取后继节点的地址
	const Node<T>* nextNode() const;//获取后续结点的地址 
}; 

//类的实现部分
//构造函数，初始化数据和指针成员
template<class T>
Node<T>::Node(const T& data, Node<T>* next/* = 0*/):data(data),next(next){}

//返回后继节点的指针
template<class T>
Node<T>* Node<T>::nextNode(){
	return next;
} 

//返回后继节点的指针
template<class T>
const Node<T>* Node<T>::nextNode() const{
	return next; 
}

//在当前节点之后插入一个节点p
template<class T>
void insertAfter(Node<T>* p){
	this->next = p;
	p->next = next;
} 

//在当前节点之前插入一个节点p 

//删除当前节点的后继节点，并返回地址
template<class T>
Node<T>* Node<T>::deleteAfter(){
	Node<T>* tempPtr = next;//暂时储存next指针地址 
	if(next == 0)//如果该节点是末尾 
		return 0;//返回0 
	next = tempPtr->next; //后继节点为表尾，则返回0；否则更新后继结点 
	return tempPtr;
} 
