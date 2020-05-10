#include<stdio.h>
#include<stdlib.h>


#define LIST_INIT_SIZE 100//线性表储存空间的初始分量 
#define LISTINCREMENT//线性表储存空间的分配增量
#define OVERFLOW 1
#define OK 0
#define INVALID 1
#define TRUE 1
#define FALSE 0
 
typedef ElemType int
typedef Status int
 

typedef struct{
	ElemType *elem;//存储空间基址 
	int length;//当前长度（元素个数） 
	int listsize;//当前分配存储容量 
}SqList;

Status InitList_Sq(SqList& L);
void DestroyList(SqList& L);
void ClearList(SqList& L);
int ListEmpty(SqList L);
int ListLength(SqList L);
ElemType GetElem(SqList L,i,&e);
int LocateElem(SqList L,e,compare());
SqList* PriorElem(SqList L,ElemType cur_e,ElemType& pre_e);
SqList* NextElem(SqList L,ElemType cur_e,ElemType& next_e);
void ListInsert(SqList& L,int i,ElemType e);
ElemType(SqList &L,int i,ElemType& e);
void ListTraverse(SqList L,visit());

Status InitList_Sq(SqList& L){
//构造一个空的线性表L
L.elem = (ELemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
if(!L.elem) exit(OVERFLOW);// 储存分配失败
L.length = 0;//空表长为0
L.listsize =  LIST_INIT_SIZE;
return OK;
} 

void DestroyList(SqList& L){
L.length = 0;
L.listsize = 0;
free(L.elem);
free(&L);
printf("List Destroyed/n");
}

void ClearList(SqList& L){
if(!L.elem) exit(INVALID);
if(!L.length) free(L.elem);
L.elem = (ELemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
if(!L.elem) exit(OVERFLOW);// 储存分配失败
L.length = 0;//空表长为0
L.listsize =  LIST_INIT_SIZE;
}

int ListEmpty(SqList L){
if(!L.elem) exit(INVALID);
if(L.length) return TRUE;
else return FALSE;
}

int ListLength(SqList L){
if(!L.elem) exit(INVALID);
return L.length; 
} 
 
ElemType GetElem(SqList L,i,&e){
if(!Elem||i<0||i>L.length) exit(INVALID);
e = (L.elem + (i-1)*;
return e; 
}

int LocateElem(SqList L,e,compare()){
	
}

