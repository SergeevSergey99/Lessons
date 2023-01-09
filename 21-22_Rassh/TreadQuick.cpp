#include<vector>
#include <thread>
#include <iostream>
using namespace std;

void QuickSort(vector<int>& vec, int start = 0, int end = -1)
{
	if (end == -1)
		end = vec.size() - 1;
	int i = start;
	int j = end;
	
	int temp;
	int pivot = vec[(i + j) / 2];
	while (i <= j)
	{
		while (vec[i] < pivot)
			i++;
		while (vec[j] > pivot)
			j--;
		if (i <= j)
		{
			temp = vec[i];
			vec[i] = vec[j];
			vec[j] = temp;
			i++;
			j--;
		}
	}
	if (j > start)
		QuickSort(vec, start, j);
	if (i < end)
		QuickSort(vec, i, end);
}

void Quick2Treads(vector<int> &vec) 
{
	int i = 0;
	int j = vec.size() - 1;
	int temp;
	int pivot = vec[(i + j) / 2];
	while (i <= j)
	{
		while (vec[i] < pivot)
			i++;
		while (vec[j] > pivot)
			j--;
		if (i <= j)
		{
			temp = vec[i];
			vec[i] = vec[j];
			vec[j] = temp;
			i++;
			j--;
		}
	}
	thread * t1 = nullptr;
	thread * t2 = nullptr;
	if (j > 0)
		t1 = new thread(QuickSort, ref(vec), 0, j);
	if (i < vec.size() - 1)
		t2 = new thread(QuickSort, ref(vec), i, vec.size() - 1);
	t1->join();
	t2->join();
}

void CheckVector(vector<int> &vec) 
{
	for (int i = 0; i < vec.size() - 1; i++)
	{
		if (vec[i] > vec[i + 1])
		{
			cout << "Error" << endl;
			return;
		}
	}
	cout << "OK" << endl;
}
void ShuffleVector(vector<int>& vec)
{
	int temp;
	int j;
	for (int i = 0; i < vec.size(); i++)
	{
		j = rand() % vec.size();
		temp = vec[i];
		vec[i] = vec[j];
		vec[j] = temp;
	}
}
void AddRandEllementsToVector(vector<int>& vec, int count, int range = 100) 
{
	for (size_t i = 0; i < count; i++)
	{
		vec.push_back(rand() % range);
	}
}
void PrintVector(vector<int> &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

int main()
{
	vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	AddRandEllementsToVector(vec, 10000000);
	ShuffleVector(vec);
	//PrintVector(vec);
	long start = clock();
	//Quick2Treads(vec);
	QuickSort(vec);
	long end = clock();
	//PrintVector(vec);
	CheckVector(vec);
	cout << "Time: " << (end - start) * 1.0f / CLOCKS_PER_SEC << endl;
	return 0;
}