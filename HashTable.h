#include <vector>
using namespace std;
template<class HashObject>
class HashTable
{
public:
	explicit HashTable(int size = 101);
	bool contains(const HashObject& x) const;  //检测散列表中是否包含该元素
	void clear();
	void insert(const HashObject& x);
	void remove(const HashObject& x);
private:  //辅助函数
	void rehash();
	int hashFunction(const HashObject & x) const;  //散列函数，返回散列值
private:  //成员变量
	vector<list<HashObject> > theLists;  //元素列表
	int currentSize;  //当前散列表中元素个数
};

template<class HashObject>
HashTable<HashObject>::HashTable(int size /* = 101 */)
{
	theLists.reserve(size);  //为数组分配初始内存
}
