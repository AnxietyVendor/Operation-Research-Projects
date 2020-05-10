#include<stdio.h>
#include<stdlib.h>
//clearest 
void swap(int &p, int &q){
	int temp = 0;
	temp = p;
	p = q;
	q = temp;
} 

//false
void swap1(int p, int q){
	int temp = 0;
	temp = p;
	p = q;
	q = temp;
} 

//false
void swap2(int *p, int *q){
	int *temp = NULL;
	temp = p;
	p = q;
	q = temp;
}
//little bit complex 
void swap3(int *p, int *q){
	int temp ;
	temp = *p;
	*p = *q;
	*q = temp;
}

int min(int x,int y){
	return x<y?x:y;
}

void print(int arr[],int len){
	int i;
    for (i = 0; i < len; i++)
    printf("%d ", arr[i]);
} 

void bubble_sort(int arr[],int len){
	int i,j,temp;
	for(i = 0;i < len-1;i++){
		for(j = 0;j < len-1-i;j++){
		//the biggest element will sink to the bottom  
			if(arr[j] > arr[j+1]){
				/*temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp; 
				*/
				//swap1(arr[j],arr[j+1]);
				//swap2(arr+j,arr+j+1);
				swap3(arr+j,arr+j+1);
			}
		}
	}
} 

void selection_sort(int arr[],int len){
	int i,j;
	for(i = 0;i<len - 1;i++){
		int min = i;
		for(j = i + 1;j<len;j++){
			if(arr[j] < arr[min])
				min = j; 
		swap(arr[min],arr[i]);		
		}
	}
}

void insertion_sort(int arr[],int len){
	int i,j,temp;
	for(i = 1;i<len;i++){
		for(j = 0;j < i;j++)
			if(arr[i] < arr[j])
				swap(arr[i],arr[j]);
	}
	
} 

void shell_sort(int arr[], int len){
	int gap,i,j;
	int temp;
	for(gap = len>>1;gap > 0;gap = gap >>1)
		//通过移位运算符来获得递减增量
		//移位运算结果是a>>1整体的值而非a的值
		for(i = gap;i<len;i++){
			temp = arr[i];
			//从第gap位开始作为标准值 
			for(j = i-gap;j >= 0 && arr[j] >temp;j-=gap) 
				arr[j+gap] = arr[j];
			arr[j+gap] = temp;
		} 
} 

void merge_sort(int arr[],int len){
	int* a = arr;
	int* b = (int*)malloc(len * sizeof(int));
	int seg,start;
	for(seg = 1;seg < len;seg +=seg){
		for(start = 0;start < len;start += seg + seg){
			int low = start;
			int mid = min(start + seg,len);
			int high = min(start + seg + seg,len);
			int k = low;
			int start1 = low,end1 = mid;
			int start2 = mid,end2 = high;
			while(start1 < end1 && start2 < end2)
				b[k++] = a[start1] < a[start2]?a[start1++]:a[start2++];
			while(start1 < end1)
				b[k++] = a[start++];
			while(start2 < end2)
				b[k++] = a[start2++];
		}
		int* temp = a;
		a = b;
		b = temp;
		
	//print(a,len);
	//print(b,len);
	}
	if(a!= arr){
		int i;
		for(i = 0;i<len;i++)
			b[i] = a[i];
		b =a;
	}
	free(b);
}

int main(){
	int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
	int len = (int)sizeof(arr)/sizeof(*arr);
	
	
	printf("sizeof(arr): %d\n",(int)sizeof(arr));
	//返回所占内存字节数而非数组元素个数 
	printf("sizeof(*arr): %d\n",(int)sizeof(*arr));
	//计算得出数组元素个数 
	
	//bubble_sort(arr,len);
	//selection_sort(arr,len);
	//insertion_sort(arr,len);
	//shell_sort(arr,len);
	merge_sort(arr,len);
 	int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;
}
