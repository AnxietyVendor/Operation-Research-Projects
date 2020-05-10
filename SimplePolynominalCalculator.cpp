#include<stdio.h>
#include<stdlib.h> 
#include<math.h>

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

int main()
{
	
	
	printf("请选择计算功能：\n");
	printf("输入1进入向量运算模式\n");
	printf("输入2进入多项式运算模式（顺序表）\n");
	printf("输入3进入多项式运算模式（链式表）\n");
	printf("输入4退出计算器\n");
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
	
	if(mode == 4){//退出计算器 
	return 0;
	} 
	

}




