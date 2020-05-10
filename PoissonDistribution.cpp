#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#define MAX 10000

double U_Random();
int possion();

void main()
{
	int count = 0;
	for (int i = 0; i < 3; i++) {
		double u = U_Random();
		int p = possion();
		if (p >= 26) count++;
		Sleep(10);
	}
	printf("%lf", count / MAX);
	system("pause");
}

int possion()  /* 产生一个泊松分布的随机数，Lamda为总体平均数*/
{
	int Lambda = 20, k = 0;
	long double p = 1.0;
	long double l = exp(-Lambda);  /* 为了精度，才定义为long double的，exp(-Lambda)是接近0的小数*/
	//printf("%.15Lfn", l);
	while (p >= l)
	{
		double u = U_Random();
		p *= u;
		k++;
	}
	return k - 1;
}


double U_Random()   /* 产生一个0~1之间的随机数 */
{
	/*
	double f;
	srand((unsigned)time(NULL));
	f = (float)(rand() % 100);
	return f / 100;
	*/
	LARGE_INTEGER seed;
	double f;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);
	f = (float)(rand() % 100);
	return f / 100;
}






