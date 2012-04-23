#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
const int npos = -1;

void multiply(const vector<int> &a, const vector<int> &b, vector<int> &result);
void convert(vector<int> &v);
void add(const vector<int> &a, const vector<int> &b, int aPointPos, int bPointPos, vector<int> &result);
void stringToVector(const string &s, vector<int> &v, int &pointPos);
void vectorToString(const vector<int> &v, string &s, int pointPos);
void printHelp();
int main()
{
	string s;  //use string to store the user input
	string result; //use string to store the result
	vector<int> a, b;//use vector to store the integer
	int aPointPos, bPointPos;//the positon of point
	cout<<"please input the first bignumbers:\n";
	cin>>s;
	a.reserve(s.size());//reserve places to avoid vector frequent expending
	stringToVector(s, a, aPointPos);
	cout<<"please input the second bignumbers:\n";
	cin>>s;
	b.reserve(s.size());
	stringToVector(s, b, bPointPos);

	printHelp();//print help infomation
	int i;
	cin>>i;
	switch(i)
	{
		case 1:      //add
		{
			int numOfPoint = aPointPos>bPointPos ? aPointPos : bPointPos;
			int numOfInt = a.size()-aPointPos>b.size()-bPointPos ? a.size()-aPointPos : b.size()-bPointPos;
			vector<int> c;
			c.reserve(numOfPoint+numOfInt);
			add(a, b, aPointPos, bPointPos, c);
			vectorToString(c, s, numOfPoint);
			break;
		}
		case 2:      //substract
		{
			break;
		}
		case 3:      //multiply
		{
			vector<int> c(a.size()+b.size()-1, 0);//create a vector and initialize with 0
			multiply(a, b, c);
			vectorToString(c, s, aPointPos+bPointPos);
			break;
		}
		case 4:      //divide
		{
			break;
		}
		default:
			break;
	}
	cout<<"The result: "<<s<<endl;
	return 0;
}

void multiply(const vector<int> &a, const vector<int> &b, vector<int> &result)
{
	int i,j,k;
	int temp;
	for(i=0; i<a.size(); ++i)
	{
		for(j=0; j<b.size(); ++j)
		{
			result[i+j] += a[i]*b[j];
		}
	}
	convert(result);
}

void stringToVector(const string &s, vector<int> &v, int &pointPos)
{
        pointPos = s.find('.');//get the position of point
	int i;
	for(i=s.size()-1; i>=0; --i)
	{
		if(i!=pointPos)
			v.push_back(s[i]-'0');   //store interger from low bit to high bit
	}
	pointPos = pointPos==npos ? 0 : s.size()-pointPos-1;  //calculate the number of bit after point
}

void printHelp()
{
	cout<<"please choose your operator: \n"
	    <<"+: 1\n"
	    <<"-: 2\n"
	    <<"*: 3\n"
	    <<"/: 4\n"
	    <<endl;
}

void vectorToString(const vector<int> &v, string &s, int pointPos)
{
	stringstream sstrm;
	for(int i=v.size()-1; i>=0; --i)
	{
		sstrm<<v[i];
	}
	sstrm>>s;
	if(pointPos>0)   //insert the point
		s.insert(s.size()-pointPos, ".");
}

void add(const vector<int> &a, const vector<int> &b, int aPointPos, int bPointPos, vector<int> &result)
{
	int it_a=0;
	int it_b=0;
	while(it_a<aPointPos-bPointPos)
	{
		result.push_back(a[it_a++]);
	}
	while(it_b<bPointPos-aPointPos)
	{
		result.push_back(b[it_b++]);
	}
	while(it_a<a.size()&&it_b<b.size())
	{
		result.push_back(a[it_a++]+b[it_b++]);
	}
	while(it_a<a.size())
	{
		result.push_back(a[it_a++]);
	}
	while(it_b<b.size())
	{
		result.push_back(b[it_b++]);
	}
	convert(result);
}

void convert(vector<int> &v)
{
	for(int i=0; i<v.size()-1; ++i)
	{
		if(v[i]>9)
		{
			v[i+1] += v[i]/10;
			v[i] %= 10;
		}
	}
}
