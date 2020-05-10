#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2 
typedef int ElemType; 
typedef int Status;

typedef ElemType* Triplet;

/* 
typedef struct{
	ElemType* Triplet;
	int transposed;//所有向量默认为列向量，转置后transposed = 1成为列向量 
}vector;
*/

Status InitTriplet(Triplet& T,ElemType v1,ElemType v2,ElemType v3){
	T = (int*)malloc(3*sizeof(int));
	if(!T) exit(OVERFLOW);
	T[0] = v1;T[1] = v2;T[2] = v3; 
	return OK; 
}//InitTriplet 

Status DestroyTriplet(Triplet& T){
	free(T);
	T = NULL;
	return OK;
}//DestroyTriplet

Status Get(Triplet T,int i,ElemType &e){
	//1<=i<=3
	if(i<1||i>3) return ERROR;
	e = T[i-1];
	return OK;
}//Get
 
 Status Put(Triplet &T,int i,ElemType e){
 	if(i<1||i>3) return ERROR;
 	T[i-1] = e;
	printf("\n");
 	return OK;
 }//Put
 
 Status IsAscending(Triplet T){
 	//Ascending 1 not 0
	return (T[0]<T[1] && T[1]<T[2]); 
 }//IsAscending
 
 Status IsDescending(Triplet T){
 	//Descending 1 not 0
 	return (T[0]>T[1] && T[1]>T[2]);
 }//IsDescending
 
Status Max(Triplet T,ElemType& e){
	e=(T[0]>=T[1]?(T[0]>=T[2]?T[0]:T[2]):(T[1]>=T[2]?(T[1]):(T[2])));
	return OK;
}//Max

Status Min(Triplet T,ElemType& e){
	e=(T[0]<=T[1]?(T[0]<=T[2]?(T[0]):(T[2])):(T[1]<=T[2])?(T[1]):(T[2]));
	return OK;
}//Min

Status Add(Triplet& T1,Triplet& T2,Triplet& result){
	int i;
	for(i=0;i<3;i++){
		result[i] = T1[i] + T2[i];
	}
	return OK;
}//Add

Status Sub(Triplet& T1,Triplet& T2,Triplet& result){
	int i;
	for(i=0;i<3;i++){
		result[i] = T1[i] - T2[i];
	}
	return OK;
}//Sub

void print(Triplet& T){ 
	int i;
	for(i=0;i<3;i++){
		printf("%d ",T[i]); 
	} 
	printf("\n");
}

int main(){
	Triplet T1;
	
	int elem1;
	int elem2;
	int elem3;
	
	printf("Enter 3 numbers to initiate a Triplet\n");
	scanf("%d %d %d",&elem1,&elem2,&elem3);//输入三元组元素 
	InitTriplet(T1,elem1,elem2,elem3);//初始化三元组T1 
	printf("Triplet:");
	print(T1);
	printf("\n");
	
	int e_get; 
	int index;
	
	printf("Enter an index\n");
	scanf("%d",&index);
	Get(T1,index,e_get);//取出指定位置的元素 
	printf("Get:%d Elem:%d\n",Get(T1,index,e_get),e_get);
	
	int e_put;
	printf("Enter an insertion and an index\n");
	scanf("%d %d",&e_put,&index);
	printf("Before:");
	print(T1);
	Put(T1,index,e_put);//在指定位置放置指定元素 
	printf("After:");
	print(T1);
	printf("Put:%d\n",e_put);
	
	printf("IsAscending:%d\n",IsAscending(T1));//判断升序 
	printf("IsDecending:%d\n",IsDescending(T1));//判断降序 
	
	int min,max;
	Max(T1,max);
	Min(T1,min);
	printf("MAX:%d\n",max);//打印最大值 
	printf("Min:%d\n",min); //打印最小值 
	
	Triplet T2;
	printf("Enter 3 numbers to initiate a Triplet\n");
	scanf("%d %d %d",&elem1,&elem2,&elem3);//输入三元组元素 
	InitTriplet(T2,elem1,elem2,elem3);//初始化三元组T1 
	printf("Triplet:");
	print(T2);
	printf("\n");
	
	Triplet T3;
	printf("Enter 3 numbers to initiate a Triplet\n");
	scanf("%d %d %d",&elem1,&elem2,&elem3);//输入三元组元素 
	InitTriplet(T3,elem1,elem2,elem3);//初始化三元组T1 
	printf("Triplet:");
	print(T3);
	printf("\n");
	
	Triplet result;//生成三元组用以存放结果 
	InitTriplet(result,0,0,0);
	
	printf("ADD result:");//加法结果 
	Add(T2,T3,result);
	print(result);
	

	printf("SUB result:");//减法结果 
	Sub(T2,T3,result);
	print(result);
	return 0;
}

