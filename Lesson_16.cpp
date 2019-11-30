#include <iostream>

using namespace std;

int main()
{
	string str;

	cout << "Введите текст:\n";	
	cin >> str;

	int n = str.length();
	for(int i = 0; i < n; i++)
	{
		if(str[i] != str[n - 1 - i])
		{
			cout << "Строка не является полиндромом";
			return 0;
		}
	}
	
	cout << "Строка является полиндромом";

	return 0;
}
