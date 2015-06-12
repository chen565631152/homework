/*
* 实现一个list类命名为MyList，其功能与python数组类似。可以用数组实现，也可以用链表实现。
* 必须使用template <class T>，不允许使用<iostream>以外的库。
* 需要实现的功能与测试代码见下。请务必搞清楚每一项的意义，比如什么时候需要用友元函数什么时候需要const什么时候需要&。
* 当某些由用户正常操作可能产生的run time error（如pop一个空数组，或访问一个超出下标的元素），
* 请使用try-catch-throw处理错误。
* 以下类定义不保证完全正确，请根据实际需求修改，以实现样例功能为主。
*/

/*
* 本练习不涉及到虚类和类继承，但是期末考试我就不知道了。如果有时间可以用书上的shape类来练习。
*/
#include<iostream>
using namespace std;
template<class T> class Mylist;
template<class T> Mylist<T> operator+(const Mylist<T> &l1, const Mylist<T> &l2);
template<class T> ostream &operator<<(ostream&os, const Mylist<T>&obj);
template<class T> Mylist<T> operator+(const Mylist<T> &l1, const T &item);
template<class T>
class Mylist
{
	friend ostream & operator<< <T>(ostream &os, const Mylist<T> &obj);//输出运算符重载 
	
	friend Mylist<T> operator+ (const Mylist<T> &l1, const Mylist<T> &l2) //+运算符重载
	{
		Mylist<T> array;
		while (array.size < l1.size + l2.size)
		{
			array.double_space();
		}
		array.initial = l1.initial + l2.initial + 1;
		for (int i = 0; i <= l1.initial; ++i) 
		{
			array.a[i] = l1.a[i];
		}
		for (int i = l1.initial + 1; i <= array.initial; ++i) 
		{
			array.a[i] = l2.a[i - l1.initial - 1];
		}
		return array;
	}
	
	friend Mylist<T> operator+(const Mylist<T> &l1, const T &item) //同push(T item)，但不修改l1，返回一个新数组
	{
		Mylist<T> l2;
		l2 = l1;
		l2.push(item);
		return l2;
	}

private:
	T *a;
	int size;
	int initial;
	void double_space() //数组大小不够的时候可以将数组大小翻倍的操作
	{
		T *b;
		size =size*2;
		b = new T[size];
		int i;
		for (i = 0; i <= initial; ++i) b[i] = a[i];
		delete []a;
		a = b;
	}

public:
	Mylist(int length = 100)    //创建一个长度为length的空列表 ，未输入参数时创建一个长度为100的空列表 
	{
		size = length;
		initial = -1;
		a = new T[size];
	}
	
	Mylist(int num, const T&item)  //将item重复num次填入数组中
	{
		size = num;
		a = new T[size];
		for (int i = 0; i < num; ++i)
		{
			a[i] = item;
		} 
	    initial= num - 1;
	}
	
	Mylist(const Mylist<T> &l)  //深复制另外一个Mylist
	{
		size = l.size;
		initial = l.initial;
		a = new T[size];
		for (int i = 0; i <= initial; ++i) 
		{
			a[i] = l.a[i];
		}
	}
	
	Mylist(T *arr, int len)  //以arr的前len个元素构造数组 
	{
		size = len;
		a = new T[size];
		for (int i = 0; i < len; ++i) 
		{
			a[i] = arr[i];
		}
	    initial= size - 1;
	}
	
	void push(const T &item); //将item添加在Mylist最后 
	T pop();//将Mylst中最后一个元素删除，并返回这个删除的元素 
	void insert(int index, const T&item);//将item插入到place处 
	void clean();//清空数组
	int get_size();//返回MyList中元素的数量
	void erase(int start, int end); //删除MyList中第start到第end位的元素，包括两边
	T get_item(int index);//返回第index个元素
	Mylist<T> get_item(int start, int end);//返回MyList中第start到第end位的元素，包括两边。此处需要像python一样接受负数，具体见测试代码
	void remove(const T &item);//删除Mylist中第一个和item相等的元素 
	void quicksort(T a[], int low, int high);
	int mid_num(T a[], int low, int high);
	void sort(bool less = true);//实现一个快速排序或归并排序，对支持比较运算符的类进行排序 
	//若less=true,按照从小到大的顺序排，否则按照从大到小的顺序排 
	void reverse();//将MyList的元素倒过来
	//int count(const T &item);//返回MyList中和item相等的元素的个数
	Mylist<T> & operator=(const Mylist<T> &l);//赋值运算符重载 
	T &operator[](int index);//返回第index个元素 
	Mylist<T> &operator +=(const T &item);//同push(T item)
	int count(const T &item);//返回MyList中和item相等的元素的个数
	Mylist<T> &operator+=(const Mylist<T>&l1);//将一个MyList加入到本个MyList之后
	~Mylist()
	{
		delete[]a;
	}
};

//将一个MyList加入到本个MyList之后
template<class T>
Mylist<T>& Mylist<T>::operator+=(const Mylist<T>&l1)
{
	*this = *this + l1;
	return(*this);
}

//返回MyList中和item相等的元素的个数
template<class T>
int Mylist<T>::count(const T &item)
{
	int num = 0;
	for (int i = 0; i <= initial; ++i)
	{
		if (a[i] == item) ++num;
		else;
	}
	return num;
}

//同push(T item) 
template<class T>
Mylist<T>& Mylist<T>::operator+=(const T &item)
{
	push(item);
	return *this;
}

//返回第index个元素
template<class T>
T& Mylist<T>::operator[](int index)
{
	return a[index];
}

//删除Mylist中第一个和item相等的元素
template <class T>
void Mylist<T>::remove(const T &item)
{
	for (int i = 0; i <=initial; ++i)
	{
		if (a[i] == item)
		{
			erase(i, i);
			return;
		}
	}
}

//将MyList的元素倒过来
template<class T>
void Mylist<T>::reverse()
{
	Mylist<T> array;
	array = *this;
	for (int i = 0; i <= initial; ++i)
	{
		a[i] = array.a[initial - i];
	} 
}

/*实现一个快速排序或归并排序，对支持比较运算符的类进行排序 
若less=true,按照从小到大的顺序排，否则按照从大到小的顺序排*/
template<class T>
void Mylist<T>::sort(bool less)
{
	int low;
	int high;
	low = 0;
	high = initial;
	try
	{
		quicksort(a, low, high);
		if (!less) reverse();
	}
	catch(int)
	{
		cout<<"The index is out of range."<<endl;
	}	
}
template<class T>
void Mylist<T>::quicksort(T a[], int low, int high)  //the function of quicksort
{
	T mid;
	if (low >= high)    return;
	mid = mid_num(a, low, high);
	quicksort(a, low, mid - 1);
	quicksort(a, mid + 1, high);
}
template<class T>
int Mylist<T>::mid_num(T a[], int low, int high) //the function to calculate the mid number of the array
{
	T num = a[low];
	do
	{
		while (low < high && a[high] >= num)    --high;
		if (low < high)
		{
		     a[low] = a[high];
			  ++low;
	    }
		while (low < high && a[low] <= num)    ++low;
		if (low < high)
		{
		    a[high] = a[low];
			--high;
		 }
	} while (low != high);
	a[low] = num;
	return low;
}

//输出运算符重载
template<class T>
ostream &operator<<(ostream &os, const Mylist<T> &obj)
{
	os << '[';
	for (int i = 0; i < obj.initial; ++i)
	{
		os << obj.a[i] << ", ";
	}
	if (obj.initial < 0)
	{
		os << ']';
	}
	else os << obj.a[obj.initial] << ']';
	return os;
}

//将item添加在Mylist最后
template<class T>
void Mylist<T>::push(const T &item)
{
	if (initial == size - 1)
	{
		double_space();
	}
	a[++initial] = item;
}

//将Mylst中最后一个元素删除，并返回这个删除的元素 
template<class T>
T Mylist<T>::pop()
{
	try
	{
		if (initial < 0)    throw(1);
		return a[initial--];
	}
	catch (int)
	{ 
	   cout << "The list is empty. " << endl;
	   return 0; 
	}
}

//将item插入到place处
template<class T>
void Mylist<T>::insert(int index, const T&item)
{
	if (initial == size - 1)
	{
		double_space();
	}
	for (int i = initial; i >= index; --i)
	{
		a[i + 1] = a[i];
	}
	a[index] = item;
	++initial;
}

//清空数组
template<class T>
void Mylist<T>::clean()
{
	size = 0;
	initial = -1;
}

//返回MyList中元素的数量
template<class T>
int Mylist<T>::get_size()
{
	return (initial + 1);
}

//删除MyList中第start到第end位的元素，包括两边
template<class T>
void Mylist<T>::erase(int start, int end)
{
	for (int i = start; i < start + initial- end; ++i)
	{
		a[i] = a[i + end - start + 1];
	}
	initial = start + initial- end - 1;
}

//返回第index个元素
template<class T>
T Mylist<T>::get_item(int index)
{
	return a[index];
}

//返回MyList中第start到第end位的元素，包括两边。此处需要像python一样接受负数，具体见测试代码。
template<class T>
Mylist<T> Mylist<T>::get_item(int start, int end)
{
	if (start < 0)    start =start+initial+1;
	if (end < 0)    end =end+initial+1;
	if (start > end)
	{
		Mylist<T> sub;
		return sub;
	}
	else
	{
		Mylist<T> sublist(end - start + 1);
		for (int i = 0; i < end - start + 1; ++i)
		{
			sublist.a[i] = a[start + i];
			++sublist.initial;
		}
		return sublist;
	}
}

//赋值运算符重载
template<class T>
Mylist<T>& Mylist<T>::operator=(const Mylist &l)
{
	if (this == &l) //in case of duplicating itself
	{
		return *this;
	}
	delete[]a;
	size = l.size;
	initial = l.initial;
	a = new T[size];
	for (int i = 0; i <=initial; ++i)
	{
		a[i] = l.a[i];
	}
	return *this;
}


//testing program
int main()
{
	Mylist<int> a, b;
	int i;
	for (i = 0; i < 5; ++i)
	{
		a.push(i);
	}
	cout << a << endl;// a = [0, 1, 2, 3, 4]
	a[3] = 15;
	cout << a << endl;// a = [0, 1, 2, 15, 4]
	a.sort();
	cout << a << endl;// a = [0, 1, 2, 4, 15]
	a.reverse();
	cout << a << endl;// a = [15, 4, 2, 1, 0]
	a += 12;
	cout << a << endl;// a = [15, 4, 2, 1, 0, 12]
	for (i = 0; i < a.get_size(); ++i)
	{
		cout << a.get_item(i) << endl;
	}
	cout << a.count(5) << endl;
	b.clean();
	cout << b << endl;
	cout << b.get_size() << endl;
	a.erase(2, 5);
	cout << a << endl;//a = [15, 4]
	b = a + a;
	cout << b << endl;
	b.insert(3, 116);
	cout << b << endl;
	b.remove(4);
	cout << b << endl;
	Mylist<double>c(10, 3.14);
	cout << c << endl;
	for (i = 0; i < 100; ++i)
	{
		c.push(1.1*i);
	}
	cout << c.get_item(100, 105) << endl;

	return 0;
}
