//链地址散列表
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<vector>
#include<list>
#include<string>
#include<algorithm>
using namespace std;
template<class T>

class HashTable
{
public:
	explicit HashTable(int size=101);
	bool contains(const T& obj)const;
	void clear();
	bool insert(const T& obj);
	bool remove(const T& obj);
private:
	void reHash();//expand the size of HashTable
	int myHash(const T& obj)const;  //hash function
private:
	vector<list<T> > theLists; //The array of lists
	int currentSize;

};
int hash(string key);
int hash(int key);
#endif

int hash(string key)
{
	int hashVal = 0;
	for(int i=0; i<key.length(); ++i)
	{
		hashVal = 37*hashVal + key[i];
	}
	return hashVal;
}

int hash(int key)
{
	return key*key;
}

template<class T>
int HashTable<T>::myHash(const T& obj)const
{
	int hashVal = hash(obj);
	hashVal %= theLists.size();
	if(hashVal<0)
		hashVal += theLists.size();
	return hashVal;
}
template<class T>
void HashTable<T>::reHash()
{
	vector<list<T> > oldLists = theLists;
	theLists.resize(theLists.size()*2);
	int i;
	for(i=0; i<theLists.size(); ++i)
	{
		theLists[i].clear();
	}
	typename list<T>::iterator itr;
	currentSize = 0;
	for(i=0; i<oldLists.size(); ++i)
	{
		itr = oldLists[i].begin();
		while(itr!=oldLists[i].end())
		{
			insert(*itr++);
		}
	}
}

template<class T>
HashTable<T>::HashTable(int size)
	:theLists(size)
{
	clear();
}

template<class T>
bool HashTable<T>::contains(const T& obj)const
{
	const list<T> & theList = theLists[myHash(obj)];
	return (find(theList.begin(), theList.end(), obj)!=theList.end());
}

template<class T>
void HashTable<T>::clear()
{
	for(int i=0; i<theLists.size(); i++)
	{
		theLists[i].clear();
	}
	currentSize = 0;
}

template<class T>
bool HashTable<T>::insert(const T& obj)
{
	list<T> & theList = theLists[myHash(obj)];
	if(find(theList.begin(), theList.end(), obj)==theList.end())
	{
		theList.push_back(obj);
		if(++currentSize>theLists.size())
		{
			reHash();
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool HashTable<T>::remove(const T& obj)
{
	list<T>& theList = theLists[myHash(obj)];
	typename list<T>::iterator itr = find(theList.begin(), theList.end(), obj);
	if(itr!=theList.end())
	{
		theList.erase(itr);
		--currentSize;
		return true;
	}
	else
	{
		return false;
	}
}
