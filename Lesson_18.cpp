#include<iostream>
using namespace std;
int mas[10000];
void Bubble_sort(int n)
{
	for(int i = 0; i < n; i++)
	{	for(int j = 0; j < n - 1; j++)
		{
			if(mas[j] > mas[j + 1])
			{
				int tmp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = tmp;
			}
		}
	}
}
void Fill(int n)
{
	cout << "Введите элементы в массив:" << endl;
	for(int i = 0; i < n; i++)
		cin >> mas[i];
}
void Out(int n)
{
	cout << endl << "Содержимое массива:" << endl;
	for(int i = 0; i < n; i++)
		cout << mas[i] << " ";
}
int main()
{
	int n;
	cout << "Введите количество сортируемых элементов: ";
	cin >> n;
	// вызываем функцию для заполнения элементов значениями
	Fill(n);
	// вызываем функцию для сортировки этих элементов
	Bubble_sort(n);
	// вызываем функцию для вывода этих элементов на экран
	Out(n);
	return 0;
}
