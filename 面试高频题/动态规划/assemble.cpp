//装配线调度问题
#include<iostream>
using namespace std;
//定义全局数据变量
const int STATION_NUM = 6;//装配站数量
const int LINE_NUM = 2;   //装配线数量
const int e1 = 2;//进入装配线1所需时间
const int e2 = 4;//进入装配线2所需时间
const int x1 = 3;//离开装配线1所需时间
const int x2 = 2;//离开装配线2所需时间
int a[LINE_NUM][STATION_NUM] = {{7, 9, 3, 4, 8, 4},   //每个装配站的装配时间
                         {8, 5, 6, 4, 5, 7}};
int t[LINE_NUM][STATION_NUM-1] = {{2, 3, 1, 3, 4},    //从装配站移走所需时间
				  {2, 1, 2, 2, 1}}; 	    		  

void fastestWay(int l[][STATION_NUM-1], int &lLast, int &fLast);  //计算最快装配路线
void printStations(int l[][STATION_NUM-1], int lLast, int fLast);       //打印最快装配路线

int main()
{
	int l[LINE_NUM][STATION_NUM-1];  //最快装配路线通过的装配线的编号
	int fLast;              //最快装配时间
	int lLast;              //最后一个装配站所在装配线的编号
	fastestWay(l, lLast, fLast);
	printStations(l, lLast, fLast);
	return 0;
}

void fastestWay(int l[][STATION_NUM-1], int &lLast, int &fLast)
{
	int f[LINE_NUM][STATION_NUM];
	int i, j;
	for(i=0; i<LINE_NUM; i++)
	{
		for(j=0; j<STATION_NUM; j++)
		{
			f[i][j] = 0;
		}
	}
	f[0][0] = e1 + a[0][0];  //装配线1的第一个装配站
	f[1][0] = e2 + a[1][0];  //装配线2的第一个装配站

	int v1, v2;
	for(i=1; i<STATION_NUM; i++)
	{
		//装配线1的第j个装配站
		v1 = f[0][i-1];
		v2 = f[1][i-1]+t[1][i-1];
		if(v2>v1)
		{
			f[0][i] = v1 + a[0][i];
			l[0][i-1] = 1;
		}
		else
		{
			f[0][i] = v2 + a[0][i];
			l[0][i-1] = 2;
		}
		//装配线2的第j个装配站
		v1 = f[1][i-1];
		v2 = f[0][i-1]+t[0][i-1];
		if(v2>v1)
		{
			f[1][i] = v1 + a[1][i];
			l[1][i-1] = 2;
		}
		else
		{
			f[1][i] = v2 + a[1][i];
			l[1][i-1] = 1;
		}
	}

	v1 = f[0][STATION_NUM-1] + x1;
	v2 = f[1][STATION_NUM-1] + x2;
	if(v1>v2)
	{
		fLast = v2;
		lLast = 2;
	}
	else
	{
		fLast = v1;
		lLast = 1;
	}
}

void printStations(int l[][STATION_NUM-1], int lLast, int fLast)
{
	cout<<"\nThe total time of the fastest way: "<<fLast<<"\n";
	cout<<"The fastest way: \n";
	int lineNum;
	cout<<"station "<<STATION_NUM<<", line "<<lLast<<"\n";
	lineNum = lLast;
	for(int i=STATION_NUM-2; i>=0; i--)
	{
		cout<<"station "<<i+1<<", line "<<l[lineNum-1][i]<<"\n";
		lineNum = l[lineNum][i]; 
	}
}
