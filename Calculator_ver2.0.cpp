#include<stdio.h>
#include<stdlib.h> 
#include<math.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//#define OVERFLOW -2 

typedef int ElemType; 
typedef int Status;

//利用线性表制作的向量计算器
#define LIST_INIT_SIZE 100//储存空间初始分配量（数据元素个数） 
#define LISTINCREMENT 10 //储存空间分配增量 （数据元素个数）
typedef struct{
	
	ElemType *elem;//储存空间基础地址
	int length;//表中当前数据元素个数 
	int listsize;//当前分配的存储容量【sizeof（ElemType）】
		 
}SqList,Vector,*vector;

//向量初始化实现 
void Init_Vector(Vector &V, int dim){//输入向量引用与向量维度dim 
 	V.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
 	if(!V.elem) exit(OVERFLOW); 
 	V.length = dim;//初始化数据元素个数 
 	V.listsize = LIST_INIT_SIZE * sizeof(ElemType);//初始化当前储存容量 
 	//V.col = type;//初始化向量类型 
	 for(int i = 0;i < dim;i++) {
 		scanf("%d",&V.elem[i]);
	}	 
 } 
 
 void Print_Vector(Vector &V){
 	if(V.length == 0) printf("Invalid vector to print"); 
 	for(int i = 0;i < V.length;i++) printf(" %d",V.elem[i]);
 	//for(int i = 0;i <= V.length - 1;i++) printf("%f ",V.elem[i]);
 	putchar('\n');
 } 

//向量数值清0实现 
void Vector_clear(Vector &V){//将向量值化为0向量 
	if(V.elem == NULL) printf("vector doesn't exist");
	else{
		for(int i = 0;i < V.length;i++){
		V.elem[i] = 0;	
		}
	} 
}

//向量删除实现 
void Vector_delete(Vector &V){//释放向量所占空间
	ElemType* p = V.elem;
	V.length = 0;
	V.listsize = 0;
	free(p); 
} 

//向量加法实现 
vector Vector_add(vector va, vector vb){
	if(!va->elem || !vb->elem) printf("vectors don't exist");
	//if(va->col != vb->col) printf("invalid addition：different vector type");//行向量与列向量不能相加 
	if(va->length != vb->length) printf("invalid addition: different vector dimension"); //非同维向量不可相加
	ElemType* v1;
	ElemType* v2;
	vector vs;
	v1 = va->elem;//向量va储存基址 
	v2 = vb->elem;//向量vb储存基址
	vs = va;
	for(int i = 0;i < va->length;i++){
		*(v1 + i) += *(v2 + i);
	}
	return vs;
}

//向量减法实现
vector Vector_subtract(vector va, vector vb){
	if(!va->elem || !vb->elem) printf("vectors don't exist");
	//if(va->col != vb->col) printf("invalid addition：different vector type");//行向量与列向量不能相加 
	if(va->length != vb->length) printf("invalid addition: different vector dimension"); //非同维向量不可相加
	ElemType* v1;
	ElemType* v2;
	vector vs;
	v1 = va->elem;//向量va储存基址 
	v2 = vb->elem;//向量vb储存基址
	vs = va;
	for(int i = 0;i < va->length;i++){
		*(v1 + i) -= *(v2 + i);
	}
	return vs;
} 

//向量点乘实现 
vector Vector_dot_multiply(vector va, vector vb){
	if(!va->elem || !vb->elem) printf("vectors don't exist");
	if(va->length != vb->length) printf("invalid addition: different vector dimension"); //非同维向量不可相乘
	ElemType* v1;
	ElemType* v2;
	vector vs;
	v1 = va->elem;//向量va储存基址 
	v2 = vb->elem;//向量vb储存基址
	vs = va;//va储存乘法结果
	for(int i = 0;i < va->length;i++){
		*(v1 + i) = *(v1 + i) * *(v2 + i);
	}//遍历，计算对应分量之积 
	return vs; 
	
} 

//向量模长计算
double Vector_module(vector v){
	double module = 0;
	vector product = Vector_dot_multiply(v,v);//返回向量点乘的积向量
	ElemType* vt = product->elem;
	for(int i = 0;i < v->length;i++){
		module += *(vt + i);//计算积向量分量之和 
	} 
	return sqrt(abs(module)); 
} 

//向量夹角余弦值计算
double Vector_cos(vector va, vector vb) {
	double cos = 0;
	double mod_va = Vector_module(va);
	double mod_vb = Vector_module(vb);
	
	vector vavb = Vector_dot_multiply(va,vb);
	double mod_vavb = Vector_module(vavb);
	
	return mod_vavb/(mod_va * mod_vb);
}
 

//利用顺序表制作的多项式计算器 
//---------------------------------------------------------------------------------------------------------------------------
//数据元素表示
typedef struct{
	//int coef; //整系数多项式
	float coef; //实系数多项式 
	int expn;
}datatype;

typedef struct{
	
	datatype* term;//储存空间基础地址
	int length;//表中当前多项式项数 
	int listsize;//当前分配的存储容量
 
}ArrayPoly,*Polyptr;//定义引用和指针

void Init_ArrayPoly(ArrayPoly &poly, int terms){//输入多项式项数初始化多项式 
	 poly.term = (datatype*)malloc(LIST_INIT_SIZE * sizeof(datatype));
	 if(!poly.term) exit(OVERFLOW);
	 poly.length = terms;//记录多项式长度 
	 poly.listsize = LIST_INIT_SIZE * sizeof(ElemType);//记录已分配存储容量
	 for(int i = 0;i < terms;i++){
	 	scanf("%f %d",&poly.term[i].coef,&poly.term[i].expn);
	 } 
} 

//输出线性表多项式 
void Print_ArrayPoly(ArrayPoly &poly){
	if(!poly.term)
		printf("此链表为空\n");
	int i;
	double calculation;
	for(i = 0;i < poly.length;i++) calculation += poly.term[i].coef;
	
	if(fabs(calculation) < 1e-5){
		printf("0");
	}
	else{
	
	for(i = 0;i < poly.length - 1;i++){
		if(poly.term[i].expn == 0) printf("%.3f + ",poly.term[i].coef);
		if(poly.term[i].expn > 0){
		if(poly.term[i].coef >= 0)
			printf("%.3fx^%d + ",poly.term[i].coef,poly.term[i].expn);
		else
			printf("%.3fx^%d ",poly.term[i].coef,poly.term[i].expn);			
		}
	}
	if(poly.term[i].expn > 0) printf("%.3fx^%d\n",poly.term[i].coef,poly.term[i].expn);
	if(poly.term[i].expn == 0) printf("%.3f ",poly.term[i].coef);
	} 
}

//多项式加法实现 
Polyptr Add_ArrayPoly(Polyptr p1, Polyptr p2){//输入两个多项式的存储基址 
	int void_count = 0;
	datatype* pa = p1->term;
	datatype* pb = p2->term;
	datatype* media = (datatype*)malloc((p1->length+p2->length)*sizeof(datatype));
	datatype* pc = media;//指针指向和的存储基地址
	
	datatype* pa_last = p1->term + p1->length -1;//记录线性表末位元素地址 
	datatype* pb_last = p2->term + p2->length -1;
	while(pa <= pa_last && pb <= pb_last){
		
		if(pa->expn == pb->expn){//出现同次项
			if(pa->coef + pb->coef == 0) void_count++;
			else{
				pc->coef = pa->coef + pb->coef;
				pc->expn = pa->expn;
				pa++;
				pb++;
				pc++;		
			} 
		}
		
		if(pa->expn < pb->expn){
			pc->coef = pa->coef;
			pc->expn = pa->expn;
			pa++;
			pc++;
		}
		
		if(pb->expn < pa->expn){
			pc->coef = pb->coef;
			pc->expn = pb->expn;
			pb++;
			pc++;					
		}
		
	
	} 
	while(pa <= pa_last){//pb完成遍历
	pc->expn = pa->expn;
	pc->coef = pa->coef;
	pa++;
	pc++; 
	} 

	while(pb <= pb_last){//pa完成遍历
	pc->expn = pb->expn;
	pc->coef = pb->coef;
	pb++;
	pc++; 
	} 	
	
	p1->term = media;
	p1->length = p1->length + p2->length - void_count ;
	
	return p1;//返回sum的地址 
} 

//多项式减法实现 
Polyptr Subtract_ArrayPoly(Polyptr p1, Polyptr p2){
	int i;
	for(i = 0;i < p2->length;i++){
		p2->term[i].coef = -(p2->term[i].coef);
	}
	Polyptr minus = Add_ArrayPoly(p1,p2);
	return minus;
}

//深拷贝当前多项式 
Polyptr Clone_ArrayPoly(Polyptr p){
	Polyptr clone = (ArrayPoly*)malloc(sizeof(ArrayPoly));	
	for(int i = 0;i<p->length;i++){
		clone->term[i] = p->term[i];
	}
	
	clone->length = p->length;
	clone->listsize = p->listsize;
	return clone;
}


//多项式乘法实现 
Polyptr Multiply_ArrayPoly(Polyptr p1, Polyptr p2){
	int i;
	datatype* pa = p1->term;//指向两个多项式的存储基址 
	datatype* pb = p2->term;
	datatype* pa_last = p1->term + p1->length - 1;
	datatype* pb_last = p2->term + p2->length - 1;
	Polyptr sum_ptr = (ArrayPoly*)malloc(sizeof(ArrayPoly));//指向和多项式的指针 
	sum_ptr->length = 0;
	
	Polyptr pc = (ArrayPoly*)malloc(sizeof(ArrayPoly));
	pc->term = (datatype*)malloc((p1->length) * sizeof(datatype));

	while(pb<=pb_last){
		pc->length = p1->length;
		datatype* pcc = pc->term;//pcc指向term 
		pa = p1->term;	
		while(pa<=pa_last){
			pcc->coef = pa->coef * pb->coef;
			pcc->expn = pa->expn + pb->expn;
			pa++;
			pcc++;
		}
		sum_ptr = Add_ArrayPoly(sum_ptr,pc);
		pb++;
	}
	sum_ptr->term[sum_ptr->length].coef = 0;
	sum_ptr->term[sum_ptr->length].expn = -1;
	return sum_ptr;
}


//多项式求导实现 
Polyptr Diff_ArrayPoly(Polyptr p, int degree){
	if(!degree) return p;
	int i,j;
	for(i = 0;i < degree;i++){
		for(j = 0;j < p->length;j++){
			p->term[j].coef = p->term[j].expn * p->term[j].coef;
			if(p->term[j].expn == 0){
				p->term[j].coef = 0;
			}
			p->term[j].expn --;				
			}	
		}
	return p;
}


 

//利用有序链表制作的多项式计算器
//---------------------------------------------------------------------------------------------------------------------------

//多项式储存单元
typedef struct Pnode{
	datatype data;
	struct Pnode *next;
}Pnode,*Link_List;

//多项式表示为含头结点的单链表 
typedef Link_List polynominal;

//--------------------------------------多项式基本操作--------------------------------// 
//定义ccompare函数的返回值 
#define a_e_b 0  //a = b
#define a_g_b 1  //a > b
#define a_s_b -1 //a < b
int compare(datatype a, datatype b)
{
    if(a.expn == b.expn)
        return a_e_b;
    if(a.expn > b.expn)
        return a_g_b;
    if(a.expn < b.expn)
        return a_s_b;
}

//定义polyn_locate函数的返回类型 
typedef struct{
    polynominal p;//指向多项式某项的结点 
    int type;//判断查找元素与多项式项的关系 
}locate;

//定义poly_locate函数的返回类型中的type值
#define prior -1  //要找元素值不存在且小于链表中的某一结点，返回这一节点的前驱 
#define curor 0   //要找元素存在
#define nextor 1  //要找元素值不存在且大于链表中的结点，后插 

locate polyn_locate(polynominal HEAD, datatype e, int(*compare)(datatype, datatype))//函数指针 
{
    locate ptr; 
    ptr.p = HEAD;
    while((ptr.p) -> next)//用ptr.p遍历链表中的所有结点 
    {
        if(compare( (ptr.p -> next -> data), e) == a_e_b)
        {//如果ptr.p的后继元素与查找值相等，返回后继元素指针 
            ptr.p = ptr.p -> next;
            ptr.type = curor;
            return ptr;
        }
        if(compare( ptr.p -> next -> data, e) == a_g_b)
        {//如果ptr.p的后继元素大于查找值，返回后继元素的前驱指针 
            ptr.type = prior;
            return ptr;
        }
        if(compare( ptr.p -> next -> data, e) == a_s_b)
        {//如果ptr.p的后继元素小于查找值，则继续遍历 
            ptr.p = ptr.p -> next;
        }
    }
    ptr.type = nextor;//e是多项式中最大的元素 
    return ptr;
}

//定义polyn_print函数打印多项式 
void polyn_print(polynominal HEAD)
{

    polynominal p = HEAD -> next;
    if(!p)
        printf("此链表为空\n");
    else
    {
        while(p -> next)
        {
            if (p -> data.coef >= 0){
            	if(p->data.expn == 0) printf("%.3f + ",p -> data.coef);
            	else if(p->data.expn < 0) printf("");
            	else printf("%.3fx^%d + ",p -> data.coef,p -> data.expn);
			} 
                
            else
            	if(p->data.expn == 0) printf("%.3f ",p -> data.coef);
            	else if(p->data.expn < 0) printf("");
                else printf("%.3fx^%d ",p -> data.coef,p -> data.expn);   

            p = p -> next;
        }
 		if(p->data.expn == 0) printf("%.3f\n",p->data.coef);       
		else printf("%.3fx^%d\n",p -> data.coef,p -> data.expn);

    }
    
    
    
}

//将项结点有序插入多项式
void polyn_order_insert(polynominal HEAD, datatype e, int(*compare)(datatype, datatype))
{

    locate ptr = polyn_locate(HEAD, e, compare);//内部调用polyn_locate函数 
    if (ptr.type == nextor)
    {
        //尾插一个节点 
        polynominal new_node = (polynominal)malloc(sizeof(Pnode));
        new_node -> data = e;
        ptr.p -> next = new_node;
        new_node -> next = NULL;
    }
    if (ptr.type == prior)
    {
        //在前驱之后插入节点 
        polynominal new_node = (polynominal)malloc(sizeof(Pnode));
        new_node -> data = e;
        new_node -> next = ptr.p -> next;
        ptr.p -> next = new_node;
    }
    if (ptr.type == curor)
    {	
		//如果此项存在则合并系数 
        (ptr.p -> data).coef += e.coef;
    }
}



//定义多项式初始化函数
 void polyn_create(polynominal HEAD, int m)
{
    //实系数指数多项式 
    int i = 0;
    HEAD -> next = NULL;
    datatype temp;
    scanf("%f %d",&(temp.coef), &(temp.expn));
    while(temp.coef != 0 && i < m)//有效输入为系数非零
    {
		//向多项式中插入新的项节点
        polyn_order_insert(HEAD, temp, compare);
        ++i;
        if(i<m) scanf("%f %d",&(temp.coef), &(temp.expn));
    }
}


//定义多项式析构函数 
void polyn_destroy(polynominal HEAD)
{
    while(HEAD)
    {
        polynominal p = HEAD;
        HEAD = HEAD -> next;
        free(p);
    }
}

//计算多项式长度 
int polyn_length(polynominal HEAD)
{
    polynominal p = HEAD -> next;
    int i = 0;
    while(p)
    {
        i += 1;
        p = p -> next;
    }
    return i;

}

//两个多项式相加 
polynominal polyn_add(polynominal pa, polynominal pb)
{ 
    polynominal hc = pa;//和链表头结点 
    polynominal pc = hc;//和链表游标 
    polynominal hb = pb;//链表b的头结点 
    pb = pb -> next;//链表a首元结点 
    pa = pa -> next;//链表b首元结点 
    int type;
    while(pa && pb)
    {
        type = compare(pa -> data, pb -> data);
        if (type == a_e_b)
        {
            (pa -> data).coef = (pa -> data).coef + (pb -> data).coef;//指数相同合并系数 
            if (pa -> data.coef == 0)
            {
                pc -> next = pa;//删除链表pa结点 
                pa = pa -> next;
                free(pc -> next);
                pc -> next = NULL;
                hb -> next = pb -> next;//删除链表pb结点 
                free(pb);
                pb = hb -> next;

            }
            else
            {
                pc -> next = pa; //将结点存至和链
                pc = pa;
                hb -> next  = pb -> next;//改变b的头结点 
                free(pb);
                pb = hb -> next; 
                pa = pa -> next;
            }
        }
        if (type == a_s_b)
        {
            pc -> next = pa;//将结点存至和链
            pc = pa;
            pa = pa -> next;
        }
        if (type == a_g_b)
        {
            pc -> next = pb;//将结点存至和链
            pc = pb;
            pb = pb -> next;
            hb -> next = pb;
        }
    }

    if(pa == NULL)
    {
        if(pb == NULL)
            free(hb);
        else
        {
            pc -> next = pb;
            free(hb);
        }
    }
    else//a非空，b空 
    {
        free(hb);
        pc -> next = pa;
    }
    return hc;

}


polynominal polyn_subtract(polynominal pa, polynominal pb)
{
    //先把pb链(减数)取负,然后调用加法函数即可
    //从首元开始遍历非和链,对每一项系数取相反数
    if(!pb || !pa) printf("False");
	polynominal hb = pb; 
    while(hb)
    {
        hb -> data.coef = (0 - (hb -> data).coef);
        hb = hb -> next; 
    }
    polynominal pc = polyn_add(pa, pb);
    return pc;
}

//多项式乘法中申请额外空间储存因数pa初始值 
polynominal polyn_clone(polynominal HEAD)
{
 
    polynominal pnode  = HEAD;
    polynominal pclone_head,pclone_node;
    if(pnode != NULL)
    {
        pclone_head = (polynominal)malloc(sizeof(Pnode));//初始化clone链表头指针 
		pclone_head->data = pnode->data;//头结点非空则拷贝数据 
		pclone_head->next = NULL;//设置clone多项式的头结点指针域为空 
		pclone_node = pclone_head;// 设置clone多项式的游标并移至头结点 
		pnode = pnode->next;// 原链表游标后移至首元 
    }
    while(pnode != NULL)
    {
        polynominal temp_node = (polynominal)malloc(sizeof(Pnode));//初始化转存结点 
		temp_node->data = pnode->data;//将pnode的数据存入temp_node 
		temp_node->next = NULL;//设置转存结点指针域为空 
 		pclone_node -> next = temp_node;//将temp_node插入pclone链表中 
        pclone_node = pclone_node -> next;//游标后移至temp结点 
        pnode = pnode -> next;//游标后移 
    }
    return pclone_head;
}

//多项式乘法 
polynominal polyn_multiply(polynominal pa, polynominal pb)
{
    polynominal p = (polynominal)malloc(sizeof(Pnode));//乘积储存空间 
	p->next = NULL;//设置指针域为空 
	polynominal pac = pa->next;//pac指向因数pa首元 
	polynominal pbc = pb->next;//pbc指向因数pb首元 
    while(pbc)
    {
        polynominal pc = polyn_clone(pa);//复制因数pa来与pb各项相乘 
		polynominal pcc = pc->next;//pcc指向pa_clone首元 
        while(pac)
        {
            pcc->data.coef = (pac->data.coef) * (pbc->data.coef);//pbc若误写为pb，将导致内存溢出 
			pcc->data.expn = (pac->data.expn) + (pbc->data.expn);
			pcc = pcc->next;
			pac = pac->next;
		} //pc中储存pa与因数pb第一项相乘得到的升幂多项式 
		pac = pa->next;//pac指向pa首元 
		p = polyn_add(p,pc);//合并p与pc 
		pbc = pbc->next;//pbc指向因数pb的第二项
    }
    polyn_destroy(pa);
    polyn_destroy(pb);
    return p;
}

//多项式求导
polynominal polyn_derivate(polynominal pa, int degree){
	if(!pa) printf("Invaid Operation");
	else{
		polynominal ph = pa;
		for(int i = 0;i < degree;i++){
		
		polynominal p = ph->next;//游标指向链表首元
		while(p) {
			p->data.coef = (p->data.coef)*(p->data.expn);
			p->data.expn = p->data.expn-1;
			p = p->next;
		}
		}
	return ph;
	}
}

//表达式计算 
//-----------------------------------------------------------------------------------------------------------------------------------------
#define STACK_INIT_SIZE 100//存储空间初始分量
#define STACKINCREMENT 10//存储空间分配增量
#define LENGTH 100//缓存空间初始分配量 

//操作符栈的结构体 
typedef struct{
	char *base;
	char *top;
	int stacksize;
}OPTR_stack;

//操作数栈的结构体
typedef struct{
	double *base;
	double *top;
	int stacksize;
}OPND_stack;


//操作符栈的初始化 
void Init_OPTR_stack(OPTR_stack &s){
	s.base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	if(!s.base) printf("OPTR_stack Initiation Failed\n");
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
}

//操作数栈的初始化 
void Init_OPND_stack(OPND_stack &s){
	s.base = (double*)malloc(STACK_INIT_SIZE * sizeof(double));
	if(!s.base) printf("OPND_stack Initiation Failed\n");
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
}

//操作符栈入栈 
void OPTR_stack_Push(OPTR_stack &s, char elem){
	if(s.top - s.base >= s.stacksize){
		s.base = (char*)realloc(s.base, STACKINCREMENT * sizeof(char));
		if(!s.base) printf("OPTR_stack Increment Failed\n");
		
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;	
	}
	*s.top++ = elem;
}

//操作数栈出栈
void OPND_stack_Push(OPND_stack &s, double elem){
	if(s.top - s.base >= s.stacksize){
		s.base = (double*)realloc(s.base, STACKINCREMENT * sizeof(double));
		if(!s.base) printf("OPND_stack Increment Failed\n");
	
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	}
	*s.top++ = elem;
} 

//操作符栈出栈 
void OPTR_stack_Pop(OPTR_stack &s, char &elem){
	//if(s.base == s.top) printf("OPTR_stack Empty\n");
	elem = *(--s.top);
} 

//操作数栈出栈 
void OPND_stack_Pop(OPND_stack &s, double &elem){
	//if(s.base == s.top) printf("OPND_stack Empty\n");//
	elem = *(--s.top);
}

//取操作符栈栈顶元素 
char OPTR_stack_Top(OPTR_stack &s){
	//if(s.base == s.top) printf("OPTR_stack Empty\n");
	return *(s.top - 1);
} 

// 取操作数栈栈顶元素
double OPND_stack_Top(OPND_stack &s){
	//if(s.base == s.top) printf("OPND_stack Empty\n");
	return *(s.top - 1);
}

//计算函数2
double Operate(double operand1, char _operator, double operand2){
	switch(_operator){
		case'+':return operand1 + operand2;break;
		case'-':return operand1 - operand2;break;
		case'*':return operand1 * operand2;break;
		case'/':return operand1 / operand2;break;
		default:return 0;
	}
} 
 
//操作符判断函数 
bool Ischar(char ch){
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#')
	return 1;
	else return 0;
} 

bool Isnum(char num){
	if(num >= '0' && num <= '9') return 1;
	else return 0;
} 

//运算符优先级表 
unsigned char prior_table[][7] ={
                {'>', '>', '<', '<', '<', '>', '>'},
                {'>', '>', '<', '<', '<', '>', '>'},
                {'>', '>', '>', '>', '<', '>', '>'},
                {'>', '>', '>', '>', '<', '>', '>'},
                {'<', '<', '<', '<', '<', '=', ' '},
                {'>', '>', '>', '>', ' ', '>', '>'},
                {'<', '<', '<', '<', '<', ' ', '='}
               };

//优先级函数 
char Precede(char optr1, char optr2){
	int row;
	int col;
		
	switch(optr1){
		case '+':row = 0;break;
		case '-':row = 1;break;
		case '*':row = 2;break;
		case '/':row = 3;break;
		case '(':row = 4;break;
		case ')':row = 5;break;
		case '#':row = 6;break;
	}
	
	switch(optr2){
		case '+':col = 0;break;
		case '-':col = 1;break;
		case '*':col = 2;break;
		case '/':col = 3;break;
		case '(':col = 4;break;
		case ')':col = 5;break;
		case '#':col = 6;break;		
	}
	
	return prior_table[row][col];
}  

//字符串结构体 
typedef struct string{
	char value[100000];
	int length;
}string;

//结构体初始化 
void Init_string(string &s){
	gets(s.value);
	s.length = strlen(s.value);	
} 

//生成next数组 
void GetNext(string T, int next[]){
	int i,j;
	i = 0;//指向字符串每个字符的下标
	j = -1;
	next[i] = j;//将next[0]设为0
	while(i < T.length){
		if(j == -1 || T.value[i] == T.value[j])
		{++i; ++j; next[i] = j;}
		else j = next[j];
	} 

}

//kmp函数,返回主串中模式串所在下标 
int KMP(string S, string T, int next[]){//传入主串，模式串和next数组
	int i,j;
	i = j = 0;
	while(i < S.length && j < T.length){//i为主串下标，j为模式串下标 
		if(j == -1 || S.value[i] == T.value[j])
		{++i; ++j;}
		else j = next[j];
	}
	if(j == T.length) return i - T.length;
	else return -1;
} 


//字符串处理函数(将输入字符串中的变量名替换为变量的值)
void VariableExchange(string variable, string &expression, string key, int index){//从expression字符数组中找到variable数组，并替换为key数组  
	if(variable.length == key.length){//变量名和变量值等长时 
		for(int i = 0;i < variable.length;i++){
			expression.value[i + index] = key.value[i];
		}
	}
	
	if(variable.length < key.length){//变量名比值短，需要将变量名之后的部分后移
		expression.length = expression.length + key.length - variable.length;
		
		for(int i = expression.length;i >= index + variable.length;i--){
			expression.value[i + (key.length - variable.length)] = expression.value[i];
		}
		for(int j = 0;j < key.length;j++){//填充 
			expression.value[j + index] = key.value[j];
		} 
	}
	
	if(variable.length > key.length){//变量名比值长，需要将变量名之后的部分前移
		
		for(int i = index + variable.length;i < expression.length;i++){
			expression.value[i - (variable.length - key.length)] = expression.value[i];
		}
		for(int k = expression.length + key.length - variable.length;k < expression.length;k++) expression.value[k] = '\0';
		
		expression.length = expression.length + key.length - variable.length;
		
		
		
		for(int j = 0;j < key.length;j++){//填充 
			expression.value[j + index] = key.value[j];
		} 
	}
	

} 

void MonoVariableSwap(string &expression, string variable, string key){
	int *next = (int *)malloc(variable.length * sizeof(int));
	int index;
	GetNext(variable,next);
	index = KMP(expression,variable,next);
	VariableExchange(variable,expression,key,index);
}

//细节处理
void Detail(string &expression){
	string special;
	special.length = 1;
	special.value[0] = '-';
	
	string key;
	key.length = 2;
	key.value[0] = '0';
	key.value[1] = '-';
	MonoVariableSwap(expression,special,key);
} 

void EvalueExpression(char* expression){
	char Operator;
	int i = 0, precision = -1, head = 0;
	double combine, operand1, operand2, string_num;
	
	OPTR_stack OPTR;
	Init_OPTR_stack(OPTR);//初始化操作符栈 
	
	OPND_stack OPND;
	Init_OPND_stack(OPND);//初始化操作数栈 
	
	OPTR_stack_Push(OPTR,'#');//向操作符栈中压入'#' 

	while(expression[i] != '#' || OPTR_stack_Top(OPTR) != '#'){ 
		if(Isnum(expression[i])){//如果当前字符是数字 
			string_num = 0;//最终的入栈元素
			while(Isnum(expression[i])||expression[i] == '.'){//未进入while循环 
				if(expression[i] == '.')
				head = 1;//识别到小数，开始记录精度 
				else string_num = string_num * 10 + expression[i] - '0';//将数值字符转化为对应数字
				
				if(head) precision++;//小数位数加一 
				i++;//游标后移						
			}//此时的expression[i]不是数字 
			if(precision != -1) string_num = string_num / pow(10,precision);//根据记录的精度将整数化为浮点数 
			//printf("入栈操作数OPND:%lf\n",string_num);
			OPND_stack_Push(OPND, string_num);
			precision = -1;head = 0;//恢复精度和识别的默认值 
			}
		else{//如果当前字符不是数字 
			switch(Precede(OPTR_stack_Top(OPTR), expression[i])){
				case'<'://printf("入栈操作符：%c\n",expression[i]);
						OPTR_stack_Push(OPTR,expression[i]);i++;break;
				
				case'>':
						OPTR_stack_Pop(OPTR,Operator);
						//printf("出栈操作符：%c\n", Operator);
						OPND_stack_Pop(OPND,operand1);
						//printf("出栈操作数2：%lf\n",operand1);	
						OPND_stack_Pop(OPND,operand2);
						//printf("出栈操作数2：%lf\n",operand2);
						combine = Operate(operand2, Operator, operand1);
						//printf("入栈操作数:%lf\n",combine);
						OPND_stack_Push(OPND, combine); 
						break;
				
				case'=':OPTR_stack_Pop(OPTR,Operator);
						i++;
						break; 
			} 
		}
	}
	printf("%.3lf\n",OPND_stack_Top(OPND));	
}

//--------------------------------------------------------------------------------------------------------------------------






int main()
{	
	printf("请选择计算功能：\n");
	printf("输入1进入向量运算模式\n");
	printf("输入2进入多项式运算模式（顺序表）\n");
	printf("输入3进入多项式运算模式（链式表）\n");
	printf("输入4进入表达式求值运算模式\n");
	printf("输入5进入单变量表达式求值运算模式\n"); 
	printf("输入6退出计算器\n");
	printf("向量计算功能：+ - ^(夹角余弦值)\n");
	printf("多项式计算功能：+ - * d(求导)\n"); 
	 
	
	loop:int mode;
	printf("---------------------------------------------------------\n");
	scanf("%d",&mode);
	
	if(mode == 1){
	//----------------------------------------初始化向量------------------------------//
 	int dim1;
	int dim2;

	printf("***************输入+计算向量的和*****************\n");
	printf("***************输入-计算向量的差*****************\n");
	printf("***************输入^计算多项式的夹角余弦值***************\n");	 
	printf("输入向量1维度：");
	scanf("%d",&dim1);
	 
	Vector va;
	Vector vb;
	
	Init_Vector(va,dim1);
	Print_Vector(va);
	
	char _operator;
    
	if(getchar() == '\n'){
		printf("输入操作符：");
    	scanf("%c",&_operator);
	}
	
	if(_operator == '+'){
		printf("输入向量2维度：");
		scanf("%d",&dim2);
		Init_Vector(vb,dim2);
		Print_Vector(vb);
		
		printf("输出结果：\n");
		vector result = Vector_add(&va,&vb);
		Print_Vector(*result); 
	}

	if(_operator == '-'){
		printf("输入向量2维度：");
		scanf("%d",&dim2);
		Init_Vector(vb,dim2);
		Print_Vector(vb);
		
		printf("输出结果：\n");
		vector result = Vector_subtract(&va,&vb);
		Print_Vector(*result);
	}


	if(_operator == '^'){
		printf("输入向量2维度：");
		scanf("%d",&dim2);
		Init_Vector(vb,dim2);
		Print_Vector(vb);
		
		double cos = Vector_cos(&va,&vb);
		printf("输出结果：\n");
		printf("%lf\n",cos); 
	}
	goto loop;
	
	}
	
	if(mode == 2){
	//多项式计算顺序表实现
	int terms1;
	int terms2;
	printf("***************输入+计算多项式的和*****************\n");
	printf("***************输入-计算多项式的差*****************\n");
	printf("***************输入*计算多项式的积*****************\n");
	printf("***************输入d计算多项式的导数***************\n");	
	 
	printf("输入多项式1项数：") ;
	scanf("%d",&terms1);	
	
	ArrayPoly a1;
	Init_ArrayPoly(a1,terms1);//初始化多项式a1
	Print_ArrayPoly(a1);
	
	char _operator;
	if(getchar() == '\n'){
		printf("输入操作符：");
    	scanf("%c",&_operator);
	} 
	
		if(_operator == '+'){
			
		printf("输入多项式2项数：") ;
		scanf("%d",&terms2);
		
		ArrayPoly a2;
		Init_ArrayPoly(a2,terms2);//初始化多项式a1
		Print_ArrayPoly(a2);
		
		Polyptr result = Add_ArrayPoly(&a1,&a2);
		printf("输出结果：\n");
		Print_ArrayPoly(*result); 
	
	goto loop;		
	}
	
	if(_operator == '-'){
			
		printf("输入多项式2项数：") ;
		scanf("%d",&terms2);
		
		ArrayPoly a2;
		Init_ArrayPoly(a2,terms2);//初始化多项式a1
		Print_ArrayPoly(a2);

		Polyptr result = Subtract_ArrayPoly(&a1,&a2);
		printf("输出结果：\n");
		Print_ArrayPoly(*result); 	
    goto loop;		
	}
	
	if(_operator == '*'){
			
		printf("输入多项式2项数：") ;
		scanf("%d",&terms2);
		
		ArrayPoly a2;
		Init_ArrayPoly(a2,terms2);//初始化多项式a1
		Print_ArrayPoly(a2);
		
		Polyptr result = Multiply_ArrayPoly(&a1,&a2);
		printf("输出结果：\n");
		Print_ArrayPoly(*result);
		 
	goto loop;
	}
	
	if(_operator == 'd'){
			
		int degree;
		printf("输入求导阶数：") ;
		scanf("%d",&degree);
		
		Polyptr result = Diff_ArrayPoly(&a1,degree);
		Print_ArrayPoly(*result);
		
	goto loop; 
	}
	}
	
	if(mode == 3){
	//多项式计算链式表实现 
	//----------------------------------------初始化多项式----------------------------//
	int length1;
	int length2;
	
	printf("***************输入+计算多项式的和*****************\n");
	printf("***************输入-计算多项式的差*****************\n");
	printf("***************输入*计算多项式的积*****************\n");
	printf("***************输入d计算多项式的导数***************\n");
	
	printf("输入多项式1项数：") ;
	scanf("%d",&length1);
	 
    polynominal pa = (polynominal)malloc(sizeof(Pnode));
    polyn_create(pa,length1);

    polyn_print(pa);
	putchar('\n') ;
	
	char _operator;
    
	if(getchar() == '\n'){
		printf("输入操作符：");
    	scanf("%c",&_operator);
	} 
//----------------------------------------多项式基本操作----------------------------// 

		
	if(_operator == '+'){
			
		printf("输入多项式2项数：") ;
		scanf("%d",&length2);
	
    	polynominal pb = (polynominal)malloc(sizeof(Pnode));
    	polyn_create(pb,length2);
    	polyn_print(pb);
    	putchar('\n') ;
		
		polynominal p_add =  polyn_add(pa, pb);
	    //putchar('\n') ;
		polyn_print(p_add);
	goto loop;
	}

		
	if(_operator == '-'){
			
		printf("输入多项式2项数：") ;
		scanf("%d",&length2);
		
    	polynominal pb = (polynominal)malloc(sizeof(Pnode));
    	polyn_create(pb,length2);
    	polyn_print(pb);
    	putchar('\n') ;
		
		polynominal p_sub =  polyn_subtract(pa, pb);
		//putchar('\n') ;
		polyn_print(p_sub);
	goto loop;	
	}

		
	if(_operator == '*'){
			
		printf("输入多项式2项数：") ;
		scanf("%d",&length2);
	
    	polynominal pb = (polynominal)malloc(sizeof(Pnode));
    	polyn_create(pb,length2);
    	polyn_print(pb);
    	putchar('\n') ;
		
		polynominal p_multi = polyn_multiply(pa, pb);
		//putchar('\n') ;
    	polyn_print(p_multi);
    goto loop;
	}
	
	
	if(_operator == 'd'){
		
		int degree;
		printf("输入求导阶数：") ;
		scanf("%d",&degree);
		
		polynominal p_d1 = polyn_derivate(pa,degree);
		polyn_print(p_d1);
	goto loop;
	}
	} 
	
	if(mode == 4){
	getchar(); 
	printf("输入表达式：\n"); 
	string expression;
	Init_string(expression);
	Detail(expression);

	EvalueExpression(expression.value);
	goto loop;
	} 
	
	if(mode == 5){
	getchar();
	
	int count = 0;//记录变量个数 
	printf("输入变量名：\n");
	
	string variable;
	Init_string(variable);
	
	printf("输入单变量个数：\n"); 
	scanf("%d",&count);	
	getchar(); 	
	
	printf("输入表达式：\n"); 
	string expression;
	Init_string(expression);
	
	printf("变量赋值为：\n");
	string key;
	Init_string(key);

	for(int j = 0;j < count;j++){
	Detail(expression);
	MonoVariableSwap(expression,variable,key);
	}
	
	puts(expression.value);
	
	
	puts(expression.value);

	EvalueExpression(expression.value); 
	goto loop;
	}
	
	if(mode == 6){//退出计算器 
	return 0;
	} 
}




