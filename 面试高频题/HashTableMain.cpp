#include"HashTable.h"
#include"ProbingHashTable.h"
#include<string>
#include<iostream>
using namespace std;

int main()
{
	ProbingHashTable<string> hashTable(3);
	cout<<hashTable.insert("a")<<endl;
	cout<<hashTable.contains("a");
	cout<<hashTable.remove("b")<<endl;
	cout<<hashTable.remove("a")<<endl;
	cout<<cout<<hashTable.contains("a")<<endl;
	hashTable.clear();
	return 0;
}
