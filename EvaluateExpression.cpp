#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h> 

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1


//------------------------------------------------------------------------------------
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
	if(s.base == s.top) printf("OPTR_stack Empty\n");
	elem = *(--s.top);
} 

//操作数栈出栈 
void OPND_stack_Pop(OPND_stack &s, double &elem){
	if(s.base == s.top) printf("OPND_stack Empty\n");//
	elem = *(--s.top);
}

//取操作符栈栈顶元素 
char OPTR_stack_Top(OPTR_stack &s){
	if(s.base == s.top) printf("OPTR_stack Empty\n");
	return *(s.top - 1);
} 

// 取操作数栈栈顶元素
double OPND_stack_Top(OPND_stack &s){
	if(s.base == s.top) printf("OPND_stack Empty\n");
	return *(s.top - 1);
}

//计算函数
double Operate(double operand1, char _operator, double operand2){
	switch(_operator){
		case'+':return operand1 + operand2;break;
		case'-':return operand1 - operand2;break;
		case'*':return operand1 * operand2;break;
		case'/':return operand1 / operand2;break;
		case'^':return pow(operand1, operand2);break;
		default:return 0;
	}
} 
 
//操作符判断函数 
bool Ischar(char ch){
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#' || ch == '^')
	return 1;
	else return 0;
} 

bool Isnum(char num){
	if(num >= '0' && num <= '9') return 1;
	else return 0;
} 

//运算符优先级表 
unsigned char prior_table[][8] ={
                {'>', '>', '<', '<', '<', '>', '>', '<'},
                {'>', '>', '<', '<', '<', '>', '>', '<'},
                {'>', '>', '>', '>', '<', '>', '>', '<'},
                {'>', '>', '>', '>', '<', '>', '>', '<'},
                {'<', '<', '<', '<', '<', '=', ' ', '<'},
                {'>', '>', '>', '>', ' ', '>', '>', '>'},
                {'<', '<', '<', '<', '<', ' ', '=', '<'},
                {'>', '>', '>', '>', '<', '>', '>', '>'}
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
		case '^':row = 7;break;
	}
	
	switch(optr2){
		case '+':col = 0;break;
		case '-':col = 1;break;
		case '*':col = 2;break;
		case '/':col = 3;break;
		case '(':col = 4;break;
		case ')':col = 5;break;
		case '#':col = 6;break;
		case '^':col = 7;break;		
	}
	
	return prior_table[row][col];
}  

//字符串结构体 
typedef struct string{
	char value[1000];
	int length;
}string;

//历史函数存储栈
typedef struct{
	string* base;
	string* top;
	int stacksize;
}function_stack; 

//函数栈初始化 
void Init_Function_stack(function_stack &s){
	s.base = (string*)malloc(STACK_INIT_SIZE * sizeof(string));
	if(!s.base) printf("Function_stack Initiation Failed\n");
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
}

//函数入栈 
void Function_stack_Push(function_stack &s, string elem){
	if(s.top - s.base >= s.stacksize){
		s.base = (string*)realloc(s.base, STACKINCREMENT * sizeof(string));
		if(!s.base) printf("Function_stack Increment Failed\n");
		
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;	
	}
	*s.top++ = elem;	
} 

//函数出栈
void Function_stack_Pop(function_stack &s, string &elem){
	if(s.base == s.top) printf("Function_stack Empty\n");
	elem = *(--s.top);
} 
 
//获取函数栈栈顶元素 
string Function_stack_Top(function_stack &s){
	if(s.base == s.top) printf("Function_stack Empty\n");
	return *(s.top - 1);
} 


//string结构体初始化 
void Init_string(string &s){
	//printf("输入字符串\n");
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
/*	putchar('!');
	string special1;
	special1.length = 2;
	special1.value[0] = '(';
	special1.value[1] = '-';	
	
	string key1;
	key1.length = 3;
	key1.value[0] = '(';
	key1.value[1] = '0';
	key1.value[1] = '-';	
	MonoVariableSwap(expression,special1,key1);

	string special2;
	special2.length = 2;
	special2.value[0] = '-';
	special2.value[1] = '-';
	
	string key2;
	key2.length = 1;
	key2.value[0] = '+';
	MonoVariableSwap(expression,special2,key2);

	string special3;
	special3.length = 2;
	special3.value[0] = '-';
	special3.value[1] = '-';
	
	string key3;
	key3.length = 1;
	key3.value[0] = '+';
	MonoVariableSwap(expression,special3,key3);
*/	
	string special4;
	special4.length = 2;
	special4.value[0] = '+';
	special4.value[1] = '-';
	
	string key4;
	key4.length = 1;
	key4.value[0] = '-';
	MonoVariableSwap(expression,special4,key4);
} 	
	
	




//字符串复制
 

void EvalueExpression(char* expression){
	char Operator;
	int i = 0, precision = -1, head = 0;
	double combine, operand1, operand2, string_num;
	
	OPTR_stack OPTR;
	Init_OPTR_stack(OPTR);//初始化操作符栈 
	
	OPND_stack OPND;
	Init_OPND_stack(OPND);//初始化操作数栈 
	
	OPTR_stack_Push(OPTR,'#');//向操作符栈中压入'#' 
	puts(expression);

	while(expression[i] != '#' || OPTR_stack_Top(OPTR) != '#'){ 
		//putchar('!');
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
	 
	printf("%.6lf\n",OPND_stack_Top(OPND));	
}
 

int main(){
	printf("输入1进入单变量求值模式\n");
	printf("输入2进入表达式求值模式\n");
	printf("输入3进入函数自定义模式\n");
	printf("输入4调用历史函数\n"); 	
	printf("输入5退出计算器\n");

	//储存历史数据
	function_stack History;//函数历史存储栈 
	//Init_Function_stack(History);//初始化函数历史存储栈 
	
	 
	string function_history;//历史函数 
	string variable_history;//历史变量名 
	int count_history; 

	loop:int mode;
	printf("---------------------------------------------------------\n");
	scanf("%d",&mode);
	getchar();
	
	if(mode==1){
	//单变量求值模式 
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

	for(int j = 0;j < count;j++) MonoVariableSwap(expression,variable,key);
	puts(expression.value);

	EvalueExpression(expression.value);
	
	goto loop;
	} 
	
	if(mode == 2){
	//表达式求值 
	printf("输入表达式：\n"); 
	string expression;
	Init_string(expression);
	//puts(expression.value);
	Detail(expression);
	EvalueExpression(expression.value);	
	
	goto loop;
	}
	
	if(mode == 3){
	//函数定义模式 
	
	
	//清空历史记录
	//function_history.length;//历史函数 
	//string variable_history;//历史变量名 
	count_history = 0; 
	int count = 0;//记录变量个数 
	printf("输入变量名：\n");
	
	string variable;//变量名初始化 
	Init_string(variable);
	
	variable_history.length = variable.length;//更新历史变量 
	strcpy(variable_history.value,variable.value);
	
	
	printf("输入单变量个数：\n"); 
	scanf("%d",&count);
	++count;
	count_history = count; 
	getchar(); 
	//printf("%d",count);	
	
	printf("输入函数表达式：\n");
	printf("DEF "); 
	
	string function;//储存含单变量的函数表达式 
	Init_string(function);
	//puts(function.value);
	
	//记录历史函数 
	string history;
	function_history.length = function.length;
	strcpy(function_history.value,function.value);
	
	//Function_stack_Push(History, function_history);//历史函数入栈 
	
	
	printf("变量赋值为：\n");
	string key;
	Init_string(key);
	
 
	//替换函数表达式中的变量值 
	for(int j = 0;j < count;j++) {
		MonoVariableSwap(function,variable,key);
	}	
	puts(function.value);	
	
	printf("RUN ");
	string expression;
	
	int mark = 0;
	for(;function.value[mark] != '=';mark++) putchar(function.value[mark]);
	++mark;
	
	putchar('\n');
	
	for(int i = 0;mark < function.length;i++,mark++){
		expression.length++;
		expression.value[i] = function.value[mark];
	}
	puts(expression.value);
	
	Detail(expression);
	putchar('!');
	puts(expression.value);
	
	
	EvalueExpression(expression.value); 
	goto loop;
	} 
	
	if(mode == 4){
	
	char flag = 1;
	//puts(Function_stack_Top(History));//显示历史函数
	puts(function_history.value);//显示历史函数
	

	string neo_function;
	neo_function.length = function_history.length;
	strcpy(neo_function.value,function_history.value);

	/*
	puts(Function_stack_Top(History).value);//显示历史函数
	string neo_function;//接受历史栈中的函数 
	neo_function.length = Function_stack_Top(History).length;
	strcpy(neo_function.value,Function_stack_Top(History).value);
	
	printf("是否为感兴趣的历史函数?若是则输入1，若不是则输入0\n");
	flag = getchar();
	while(flag == '0'){
		Function_stack_Pop(History,neo_function);
		neo_function.length = Function_stack_Top(History).length;
		strcpy(neo_function.value,Function_stack_Top(History).value);
		puts(neo_function.value);
		printf("是否为感兴趣的历史函数?若是则输入1，若不是则输入0\n");
		flag = getchar();	
	}
	*/
	printf("变量赋值为：\n");
	string neo_key;
	Init_string(neo_key);

	for(int j = 0;j < count_history;j++) MonoVariableSwap(neo_function,variable_history,neo_key);

	printf("RUN ");
	
	string expression;
	
	int mark = 0;
	for(;neo_function.value[mark] != '=';mark++) putchar(neo_function.value[mark]);
	++mark;
	
	putchar('\n');
	
	for(int i = 0;mark < neo_function.length;i++,mark++){
		expression.length++;
		expression.value[i] = neo_function.value[mark];
	}
	//puts(expression.value);
	
	EvalueExpression(expression.value);

	
	goto loop;
	}

	//退出 
	if(mode == 5) return 0;
	
	
} 
