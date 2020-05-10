#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<math.h>
#include<sys/types.h>
#include<memory.h>
#include<Windows.h>
#include<vector>
#include<stack>
#include<iostream>
using namespace std;

//---------图的邻接矩阵表示---------//
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 50
#define INITIAL_LENGTH 20
#define Width 100
#define MAX_DICT_SIZE 109749
#define MAX_Route 10

typedef enum { DG, DN, UDG, UDN } GraphKind;

typedef struct PreType {//前驱元素
	int VexIndex;//前驱下标
	int PathNum;//最短路径编号
}PreType;

typedef struct VListCell {//结点信息列表
	int PathOrder;//路径编号
	unsigned int PathLength;//路径长度
	int PreVertex;//前驱结点编号
	int PrePathOrder;//前驱路径下标
}VListCell，VList[MAX_VERTEX_NUM];

typedef struct InfoType {//图的弧上存储词和词长
	char Characters[INITIAL_LENGTH];
	int WordLength;
}InfoType;

typedef struct VertexType {
	int index;//顶点下标
	VListCell table[MAX_VERTEX_NUM];//回溯表
}VertexType;

typedef struct ArcCell {//邻接矩阵的元素
	unsigned int adj;//权值—>存储词频
	//InfoType *info;//指向该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {//有向无环图
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;
	int vexnum, arcnum;//顶点数与弧数
	GraphKind kind;//图的类型变量（有向无环图）
}MGraph;

typedef struct Character {
	char content[3];//汉字结构体
}Character;

typedef struct buff {//缓冲区结构体
	char characters[50];//字符串形式存储汉字的
	char freq[10];//字符串形式存储词频
	char attr[5];//字符串形式存储词性
	unsigned int frequency;
	double idf;
}buff;

typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//路径矩阵结构体
typedef int ShortPathTable[MAX_VERTEX_NUM];//最短路径长结构体
typedef bool Final[MAX_VERTEX_NUM];//是否有最短路径

typedef bool PreNode[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//记录每个结点在N最短路径的直接前驱
typedef unsigned int CumulativeWeight[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//记录到每个结点的N最短路径权值之和

void Initialize_DN(MGraph &G,int vexnum, int arcnum) {//初始化有向无环图
	for (int i = 0; i <= vexnum; i++) {//初始化n+1个结点向量下标
		G.vexs[i].index = i;
	}

	for (int i = 0; i <= vexnum; i++) {//n+1个结点
		for (int j = 0; j <= vexnum; j++) {//建立相邻顶点之间的有向弧
			if (i + 1 == j) {
				G.arcs[i][j].adj = 1;//权值初步设置为1
			}
			else G.arcs[i][j] = { INFINITY};
		}
	}
	G.vexnum = vexnum;
	G.arcnum = arcnum;
	G.kind = DN;
}

//求解最短路径
void ShortestPath(MGraph G, PathMatrix &P, ShortPathTable &D, Final &final, Character *p) {
	int i = 0, j, v, w, min;
	int v0 = 0;
	for (v = 0; v < G.vexnum; ++v) {
		final[v] = FALSE;
		D[v] = G.arcs[v0][v].adj;
		for (w = 0; w < G.vexnum; ++w)  P[v][w] = FALSE;  // 设空路径
		if (D[v] < INFINITY) { P[v][v0] = TRUE;  P[v][v] = TRUE; }
	}
	D[v0] = 0;  final[v0] = TRUE;        // 初始化，v0顶点属于S集
	//--- 开始主循环，每次求得v0到某个v顶点的最短路径，并加v到S集 ---
	for (i = 1; i < G.vexnum; ++i) {         // 其余G.vexnum-1个顶点
		min = INFINITY;                    // 当前所知离v0顶点的最近距离
		for (w = 0; w < G.vexnum; ++w)
			if (!final[w])                           // w顶点在V-S中
				if (D[w] < min) { v = w;  min = D[w]; }  // w顶点离v0顶点更近
		final[v] = TRUE;                       // 离v0顶点最近的v加入S集
		for (w = 0; w < G.vexnum; ++w)             // 更新当前最短路径及距离
			if (!final[w] && (min + G.arcs[v][w].adj < D[w])) {
				// 修改D[w]和P[w], w∈V-S
				D[w] = min + G.arcs[v][w].adj;
				for (j = 0;j < G.vexnum;j++) P[w][j] = P[v][j]; //第v行赋值于第w行
				P[w][w] = TRUE;   // P[w] = P[v]+[w]
			}
	}


	printf("1-最短路径分词结果：\n");
	for (int i = 0; i < G.vexnum - 1; i++) {
		if (P[G.vexnum - 1][i]) printf("/");
		printf("%s", (p + i)->content);
	}
	putchar('/');
	putchar('\n');
	putchar('\n');
	putchar('\n');
}



//连接不同的弧
void CreateArc(MGraph &G, buff *set, Character *p, char *sentence, int numOfcharacters) {
	int interval = 0;//记录汉字数量
	for (int i = 0; i < MAX_DICT_SIZE; ++i) {//遍历词典
		if (strstr(sentence, set[i].characters)) {//如果词条中的词出现在语句中
			for (int j = 0; j <= numOfcharacters; ++j) {//遍历汉字
				if (strstr(set[i].characters, (p + j)->content)) {//现在词典条目中，记录位置
						interval = strlen(set[i].characters) / 2;//汉字个数
						if (strlen(set[i].characters) >= 2) {

							if (strlen(set[i].characters) == 2) {//如果匹配一个汉字
								G.arcs[j][j + interval].adj = set[i].frequency;
							}

							if (strlen(set[i].characters) > 2) {//如果匹配一个词语
								for (int k = j; k <= numOfcharacters - interval;k++) {//找到子串中所有词的位置
									if (strstr(set[i].characters, (p + k)->content) && strstr(set[i].characters, (p + k + interval - 1)->content)) {
										G.arcs[k][k + interval].adj = set[i].frequency;//比较首尾汉字判断加边位置
									}
								}
							}
						}
				}
			}
		}
	}
}



//求解N最短路径，如何找出有向无环图中的所有路径？
void NShortestPath(MGraph &G, Character *p) {
	//尝试输出N-最短路径

	bool* is_in_stack = new bool[G.vexnum + 1]();//入栈状态变量
	stack<int>vertex_stack;
	int current_position = 0;//标记入栈结点
	vector<vector<int>>paths;//存储所有路径
	vector<int>path;//存储单条路径

	vertex_stack.push(0);//起点入栈
	is_in_stack[0] = 1;//设置起点已入栈，1表示在栈中，0 表示不在
	int top_element;//记录栈顶元素
	int tmp;
	while (!vertex_stack.empty())//若栈顶非空
	{
		top_element = vertex_stack.top();//查看栈顶元素，判断是否已经到达终点
		if (top_element == G.vexnum)//若到达终点，输出路径，弹出栈中两个点，设置出栈状态
		{
			while (!vertex_stack.empty())
			{
				tmp = vertex_stack.top();//存储即将出栈的栈顶元素
				vertex_stack.pop();//出栈
				path.push_back(tmp);//压入路径
			}
			paths.push_back(path);//将路径加入路径组

			for (vector<int>::reverse_iterator rit = path.rbegin(); rit != path.rend(); rit++)
			{//声明一个迭代器，来逆向访问path容器（path中结点按照升序排列）
				vertex_stack.push(*rit);
			}
			path.clear();//清除路径

			vertex_stack.pop();//栈顶数字（末端节点）大于栈底
			is_in_stack[top_element] = 0;//末端节点不在栈中
			current_position = vertex_stack.top();//找到第一条路径上倒数第二个节点的位置

			top_element = vertex_stack.top();//获取信息后让倒数第二个节点出栈
			vertex_stack.pop();//在某些情况下不出栈会导致死循环
			is_in_stack[top_element] = 0;
		}
		else
		{
			int i = 0;//遍历邻接矩阵所用的游标
			for (i = current_position + 1; i <= G.vexnum + 1; i++)//从第二个节点开始
			{
				if (is_in_stack[i] == 0 && G.arcs[top_element][i].adj != INFINITY)//未入栈，而且节点之间有边相连
				{
					is_in_stack[i] = 1;//stack In
					vertex_stack.push(i);//入栈
					current_position = 0;//位置置零
										 //在栈顶元素的行上搜索，自然从零开始，以免漏掉节点
					break;
				}
			}

			if (i == G.vexnum + 2)//该结点与终点不连通
			{
				top_element = vertex_stack.top();
				is_in_stack[top_element] = 0;
				current_position = vertex_stack.top();//返回路径上的前一结点
				vertex_stack.pop();//出栈
			}
		}
	}

	//逆向输出储存在paths容器中的内容(最长到最短)
	printf("N-最短路径分词结果：\n");
	for (int i = 0; i < paths.size(); i++)
	{
		unsigned int total = 0;//计算总词频（路径长度）
		bool PathVector[MAX_VERTEX_NUM];

		for (int j = paths[i].size() - 1; j >= 1; j--) {//计算路径长度
			int x = paths[i][j];
			int y = paths[i][j - 1];
			total += G.arcs[x][y].adj;
		}
		printf("路径 %d:", paths.size() - i);

		for (int k = paths[i].size() - 1; k >= 1; k--) PathVector[paths[i][k]] = TRUE;//记录分隔符输出位置
		for (int col = 0; col < G.vexnum - 1; col++) {//输出分词结果
			if (PathVector[col]) printf("/");
			printf("%s", (p + col)->content);
		}
		putchar('/');
		
		putchar('\t');
		printf("总词频: %d", total - 1);
		putchar('\n');

		memset(PathVector, FALSE, sizeof(PathVector));//重置分隔符输出位置
	}

}