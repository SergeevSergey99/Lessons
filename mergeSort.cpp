#include<iostream>
using namespace std;
int TempMas[1000];
void MergeSort(int * Arr, int N) 
{
	// Если в массиве 1 элемент, то он отсортирован
	if (N <= 1)
		return;
	// Середина массива размера N
	int M = N / 2;
	// Сортируем первую половину
	MergeSort(Arr, M);
	// Сортируем вторую половину
	MergeSort(Arr + M, N - M);
	// Начинаем соединять половины
	int left = 0, right = M;
	for (int i = 0; i < N; i++)
	{
		// Записываем во временный массив меньший из элементов
		// начала левой и правой половины
		if (right >= N || left < M && Arr[left] <= Arr[right])
			// сдвигаем начало левой половины
			TempMas[i] = Arr[left++];
		else 
			// сдвигаем начало правой половины
			TempMas[i] = Arr[right++];
	}
	// Записываем временный массив в настоящий
	for (int i = 0; i < N; i++)
		Arr[i] = TempMas[i];
}
int main() 
{
	int Mas[8];
	for (int i = 0; i < 8; i++)	
	{
		// Записываем в массив случайные числа
		Mas[i] = rand() % 100;
		// Выводим их на экран
		cout << Mas[i] << " ";
	}
	cout << endl;
	// Сортируем
	MergeSort(Mas, 8);
	// Выводи на экран отсортированный
	for (int i = 0; i < 8; i++)
		cout << Mas[i] << " ";
}