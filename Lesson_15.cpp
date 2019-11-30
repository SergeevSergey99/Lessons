/*#include<iostream>
using namespace std;

int main()
{
	int mas[1000], n;
	
	cout << "Сколько элементов в массиве? : ";
	cin >> n;
	if (n <= 0)
	{
		cout << "Неправильный у вас какой-то массив";
		return 0;
	}
	cout << "Задайте им значения" << endl;
	for(int i = 0; i < n; i++)
	{
		cin >> mas[i];
	}

	int x;
	cout << "Какой элемент вы хотите искать в массиве? : ";
	cin >> x;

	bool isInMas = false;
	for(int i = 0; i < n; i++)
	{
		if (mas[i] == x)
			{
				isInMas = true;
				cout <<"Элемент "<< x << " имеет номер " << i + 1 << endl;
			}
	}
	
	if(!isInMas)
	{
				cout <<"Элемента "<< x << " в массиве нет";
		
	}

	return 0;
}


*/