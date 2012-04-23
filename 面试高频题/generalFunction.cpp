#include<iostream>
using namespace std;

#define max(a, b) (((long)(a-b)&0x10000000)?b:a)  //compare a and b

int main()
{
	int a = 10;
	int b = 20;
	cout<<max(a, b)<<endl;
	return 0;
}
