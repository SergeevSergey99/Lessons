/*#include <iostream>
using namespace std;
void Sort(int *mas, int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
		{
			if (mas[i] > mas[j])
			{
				int tmp = mas[i];
				mas[i] = mas[j];
				mas[j] = tmp;
			}
		}
}
void Out(int *mas, int n) 
{
	for (int i = 0; i < n; i++)
		cout << mas[i] << " ";
	cout << endl;
}
int main() {
	

	int a[5] = { 14, 42, 3, 10, 4 };
	int b[10] = { 17, 100, -5, 73, 0, 1, 88, 22, 50, 36};
	int c[15] = { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	//Вызов функции сортировки для массива а
	Sort(a, 5);
	//Вызов функции сортировки для массива b
	Sort(b, 10);
	//Вызов функции сортировки первых 11 элементов для массива c
	Sort(c, 11);

	//Вывод элементов массива a на экран
	Out(a, 5);
	//Вывод элементов массива b на экран
	Out(b, 10);
	//Вывод элементов массива c на экран
	Out(c, 15);
	system("pause");
	return 0;
}*/