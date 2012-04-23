//01背包问题
#include<iostream>
#include<cmath>
using namespace std;
const int V = 1000; //总的体积
const int T = 5;    //物品的种类
int f[V+1];  //f[v]背包体积为v时的最大价值
int w[T] = {8, 10, 4, 5, 5};  //价值
int c[T] = {600, 400, 200, 200, 300};  //体积
const int INF = -66536;
const bool EMPTY = false;//true表示背包可以不装满，false表示背包必须装满

int package()
{
	int i;
	f[0] = 0;
	if(EMPTY)  //可以不装满
	{
		for(i=1; i<=T; ++i)
			f[i] = 0;
	}
	else       //必须装满
	{
		for(i=1; i<=T; ++i)
			f[i] = INF;
	}
	for(i=0; i<T; i++)
	{
		for(int v=V; v>=c[i]; --v)
		{
			f[v] = max(f[v], f[v-c[i]]+w[i]);
		}
	}
	return f[V];
}

int main()
{
	cout<<package()<<endl;
	return 0;
}
