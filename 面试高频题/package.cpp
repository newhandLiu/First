#include<iostream>
#include<vector>
#include<stack>
using namespace std;
//背包问题
//W[]：物品的重量数组，假设是按有序排列的
//N：物品的个数
//V：背包的最大承重量
//result: 返回结果，若为空，则表示没有符合条件的解
void package(int W[], int N, int V, stack<int> &result);

int main()
{
 	int W[] = {2, 3, 4, 5, 6, 7};
	stack<int> result;
	package(W, 6, 10, result);
	cout<<"一组解为：";
	while(!result.empty())
	{
		cout<<W[result.top()]<<" ";
		result.pop();
	}
	cout<<endl;
	return 0;
}

void package(int W[], int N, int V, stack<int> &result)
{
	int i=-1, j;
	int v;//当前背包重量
	while(i<N)
	{
		for(i=i+1; i<N; ++i)  //挑选第一个入栈元素
		{
			if(W[i]==V)
			{
				result.push(i);
				return;
			}
			else if(W[i]<V)
			{
				result.push(i);
				v = W[i]*2;
				break;
			}			
		}
		while(!result.empty())
		{
			j = result.top();//获取下一个入栈元素的下标
			result.pop();//弹出栈顶元素
			v -= W[j];
			for(j=j+1; j<N; ++j)  
			{
				if(v+W[j]==V)
				{
					result.push(j);
					result.push(i);//把第一个入栈的元素重新压入栈
					return;
				}
				else if(v+W[j]<V)
				{
					result.push(j);
					v += W[j];
				}
				else
				{
					break;
				}
			}
		}
	}
}
