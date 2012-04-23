//平方探测散列表
#ifndef PROBING_HASHTABLE_H
#define PROBING_HASHTABLE_H
#include<vector>
enum EntryType{ACTIVE, EMPTY, DELETED};
template<class T>
class ProbingHashTable
{
public:
	ProbingHashTable(int size=101);
	bool contains(const T& obj)const;
	void clear();
	bool insert(const T& obj);
	bool remove(const T& obj);
private:
	struct HashEntry
	{
		T hashObj;
		EntryType info;
		HashEntry(const T& obj=T(), EntryType e=EMPTY)
			:hashObj(obj), info(e){}
	};
private:
	bool isActive(int currentPos)const;
	int findPos(const T& obj)const;
	void reHash();
	int myHash(const T& obj)const;
private:
	vector<HashEntry> array;
	int currentSize;
};
//int hash(string key);
#endif

//int hash(string key)
//{
//	int hashVal = 0;
//	for(int i=0; i<key.length(); i++)
//	{
//		hashVal += 37*hashVal + key[i];
//	}
//	return hashVal;
//}

template<class T>
int ProbingHashTable<T>::myHash(const T& obj)const
{
	int hashVal = hash(obj);
	hashVal %= array.size();
	if(hashVal<0)
		hashVal += array.size();
	return hashVal;
}

template<class T>
ProbingHashTable<T>::ProbingHashTable(int size)
	:array(size)
{
	clear();
}

template<class T>
bool ProbingHashTable<T>::contains(const T& obj)const
{
	return isActive(findPos(obj));
}

template<class T>
void ProbingHashTable<T>::clear()
{
	for(int i=0; i<array.size(); ++i)
	{
		array[i].info = EMPTY;
	}
	currentSize = 0;
}

template<class T>
bool ProbingHashTable<T>::insert(const T& obj)
{
	int currentPos = findPos(obj);
	if(isActive(currentPos))
	{
		return false;
	}
	array[currentPos] = HashEntry(obj, ACTIVE);
	if(++currentSize>=array.size()/2)
	{
		reHash();
	}
	return true;
}

template<class T>
bool ProbingHashTable<T>::remove(const T& obj)
{
	int currentPos = findPos(obj);
	if(isActive(currentPos))
	{
		array[currentPos].info = DELETED;
		--currentSize;
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
int ProbingHashTable<T>::findPos(const T& obj)const
{
	int offset = 1;
	int currentPos = myHash(obj);
	while(array[currentPos].info!=EMPTY && array[currentPos].hashObj!=obj)
	{
		currentPos += offset;
		offset += 2;
		currentPos %= array.size();
	}
	return currentPos;
}

template<class T>
bool ProbingHashTable<T>::isActive(int currentPos)const
{
	return array[currentPos].info==ACTIVE;
}

template<class T>
void ProbingHashTable<T>::reHash()
{
	vector<HashEntry> oldArray = array;
	array.resize(2*array.size());
	clear();
	for(int i=0; i<oldArray.size(); ++i)
	{
		if(oldArray[i].info==ACTIVE)
			insert(oldArray[i].hashObj);
	}
}
