#include "Structure.h"

int main() {
	
	//*****************************************************************************************
	//读入文件
	
	FILE *fp = NULL;

	buff set[MAX_DICT_SIZE];//存储词条
	unsigned long long int total = 1;//记录总数

	fp = fopen("C:/Users/mi/Desktop/dict.txt", "r");//以只读形式打开dict.txt
	if (fp == NULL) {
		perror("call to fopen!");
		exit(1);
	}
	for (int i = 0; i < MAX_DICT_SIZE; i++) {//读入词条
		fscanf(fp, "%s %s %s\n", set[i].characters, set[i].freq, set[i].attr);
		set[i].frequency = atoi(set[i].freq);
		total += set[i].frequency;
	}

	for (int i = 0; i < MAX_DICT_SIZE; i++) set[i].idf = log(total / set[i].frequency);

	fclose(fp);
	/*
	for (int i = 0; i < 50; i++) {//读入词条
		printf("%s %s %s\n", set[i].characters, set[i].freq, set[i].attr);
	}
	*/
	//**********************************************************************************************
	//输入字符串
	char Sentence[Width];

	

	loop:printf("输入汉字\n");
	gets_s(Sentence);
	
	int numOfcharacter = strlen(Sentence)/2;
	int vexnum = numOfcharacter + 1;//n个汉字对应n+1个顶点
	int arcnum = vexnum + 1;

	//printf("%d\n",numOfcharacter);//汉字长度为2byte

	//单个汉字（字符数组）以线性结构存储在p所指空间中
	Character* p = (Character*)malloc(numOfcharacter * sizeof(Character));

	for (int i = 0;i < strlen(Sentence);i += 2) {//子串原子化
		(p + i/2)->content[0] = Sentence[i];
		(p + i/2)->content[1] = Sentence[i + 1];
		(p + i/2)->content[2] = '\0';
	}

	//尝试输出1最短路径
	MGraph G;
	Initialize_DN(G, vexnum, arcnum);//初始化图

	CreateArc(G, set, p, Sentence, numOfcharacter);
	
	PathMatrix P;
	ShortPathTable D;
	Final final;
	//输出1-最短路径分词结果
	ShortestPath(G, P, D, final,p);
	putchar('\n');
	
	//输出弧上权值
	/*
	for (int i = 0; i < vexnum; i++) {
		for (int j = 0; j < vexnum; j++) {
			printf("%d\t", G.arcs[i][j].adj);
		}
		putchar('\n');
	}*/

	//输出N-最短路径分词结果
	NShortestPath(G, p);
	
	putchar('\n');

	printf("输入回车键继续分词\n");
	if (getchar() == '\n') goto loop;

	//system("pause");
	return 0;
}

