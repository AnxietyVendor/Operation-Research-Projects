#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct{
	unsigned int weight;//结点权重 
	unsigned int parent,lchild,rchild;//指针域
	char data;
	char code[10000]; 
}HTNode, *HuffmanTree;

typedef char* *HuffmanCode;//动态分配数组存储赫夫曼编码表 

void Select(HuffmanTree &HT, int limit, int &index1, int &index2){
//选择parent为0且weight最小的两个结点，序号分别是s1，s2
	int temp1 = 99998, temp2 = 99999;
	for(int i = 1;i <= limit;i++){
		if(HT[i].parent == 0){
			if(HT[i].weight < temp1){
				temp1 = HT[i].weight;
				index1 = i;				
			}
		}
	} 
			
	for(int i = 1;i <= limit;i++){
		if(HT[i].parent == 0 && i != index1){
			if(HT[i].weight < temp2){
				temp2 = HT[i].weight;
				index2 = i;				
			}
		}	
	}
}

//Huffman编码函数 
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n){
	if(n <= 1) return;
	int s1,s2;
	int m = 2*n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	HTNode* p;
	int i;
	for(p = HT + 1, i = 1;i <= n;++i, ++p, ++w){
		p->weight = *w;
		p->lchild = 0;
		p->rchild = 0;
		p->parent = 0;
	}

	for(;i <= m;++i, ++p){
		p->weight = 0;
		p->lchild = 0;
		p->rchild = 0;
		p->parent = 0;		
	}	
		
	for(i = n + 1;i <= m;++i){//建赫夫曼树 
		Select(HT, i-1, s1, s2);//选择parent为0且weight最小的两个结点，序号分别是s1，s2
		HT[s1].parent = i;HT[s2].parent = i;
		HT[i].lchild = s1;HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//输出Huffman树的存储 
	printf("存储结构内容：\n");
	printf("weight parent lchild rchild\n");
	for(int j =1;j <= m;j++){
		printf("%d     %d     %d     %d\n",HT[j].weight,HT[j].parent,HT[j].lchild,HT[j].rchild);
	}
	
 	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));//分配n个字符编码的头指针向量
	char* cd = (char*)malloc(n * sizeof(char));//分配求编码的工作空间
	cd[n - 1] = '\0';//编码结束符
	int start;
	for(i = 1;i <= n;i++){
		start = n - 1;//指向工作空间末端
	for(int c = i,f = HT[i].parent;f != 0;c = f, f = HT[f].parent){//从叶子到根逆向编码
		if(HT[f].lchild == c) cd[--start] = '0';
		else cd[--start] = '1';
		}
	HC[i] = (char *)malloc((n - start) * sizeof(char));//为第i个字符编码分配空间
	strcpy(HC[i], &cd[start]);//将编码从cd赋值到HC[i]
	}
	free(cd);
	putchar('\n'); 
	printf("原码  密码\n");
 	for(int i = 1;i <= n;i++){
 		printf("%c      %s\n",HT[i].weight,HC[i]); 	
 		HT[i].data = (char)HT[i].weight;
 		strcpy(HT[i].code,HC[i]);
	} 
} 


//输出Huffman编码表 
void CodeTable_Printer(HuffmanTree &HT, int n){
	printf("in\n");
	for(int i =1;i <= n;i++){
		printf("%d %d %d %d\n",HT[i].weight,HT[i].lchild,HT[i].rchild,HT[i].parent);
	}
} 

//全局权值数组
int global_weights[8] = {5,29,7,8,14,23,3,11}; 
int global_char[52] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'}; 

void Encrypt(HuffmanTree HT){
	printf("输入加密内容：\n");
	char* raw;
	gets(raw);
	for(int i = 0;*(raw + i) != '\0';i++){
		for(int j = 1;j <= 52;j++){
			if(isalpha(*(raw + i)) && *(raw + i) == HT[j].data) {
				printf("%s",HT[j].code);	
			}
		}
	}
	putchar('\n');
}

void Decrypt(HuffmanTree HT){
	printf("输入密码长度：\n");
	int length;
	scanf("%d",&length); 
	getchar();//接受尾部回车 
	char* secret = (char *)malloc(length * sizeof(char));
	printf("输入解密内容(01序列)：\n");
	gets(secret);
	
	int pos = 103;
	for(int i = 0;i < length;i++){
		if(secret[i] == '0'){//向左
			pos = HT[pos].lchild;
			if(HT[pos].lchild == 0) {
				printf("%c",HT[pos].data); 
				pos = 103;
			}
		}
		if(secret[i] == '1'){//向右 
			pos = HT[pos].rchild;
			if(HT[pos].rchild == 0) {
				printf("%c",HT[pos].data); 
				pos = 103;
			}
		}
	}
	if(pos != 103) printf("Decrypting Failed!\n");
}


int main(){
	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT, HC, global_char, 52);
	Encrypt(HT);
	Decrypt(HT);
	return 0;
}
