#include<iostream>
using namespace std;

struct MyVector 
{
	MyVector(int n, int def = 0) 
	{
		size = n;
		capacity = n;
		arr = new int[n];

		for (int i = 0; i < n; i++)
		{
			arr[i] = def;
		}
	}

	void Add(int item) 
	{
		if (size >= capacity) 
		{
			int * tmpArr = new int[capacity * 2];
			capacity = capacity * 2;

			for (int i = 0; i < size; i++)
				tmpArr[i] = arr[i];
			delete[] arr;
			arr = tmpArr;
		}
	
		arr[size] = item;
		size++;
	}
	void RemoveLast()
	{
		if (size > 0)
			size--;
	}
	~MyVector() 
	{
		delete[] arr;
	}

	int GetSize(){return size;}
	int GetCapacity(){return capacity;}

	int & operator [] (int index) 
	{
		return arr[index];
	}
private:
	int * arr;
	int size;
	int capacity;
};

int main() 
{
	MyVector vec1(5);
	vec1[1] = 42;
	for (size_t i = 0; i < vec1.GetSize(); i++)
	{
		cout << vec1[i] << " ";
	}
	cout << endl << vec1.GetSize() << " " << vec1.GetCapacity();
}
