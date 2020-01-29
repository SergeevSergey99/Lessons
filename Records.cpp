// Подключение библиотеки для работы с файлами
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	// Установка потока чтения из файла
	// с именем records
	ifstream fin("records");
	// Если нет такого файла
	if(!fin.is_open())
	{	
		// заканчиваем работу программы
		return 42;
	}
	int n = 1;
	// Пока файл не закончится
	while(!fin.eof())
	{
		string Name, Score;
		// Чтение текста из установленного файла
		// и запись его в переменные
		fin >> Name >> Score;
		// Вывод, прочитанной из файла, информации на экран
		cout << n << ": " << Name << "\t-\t" << Score << endl;
		n++;
	}
	// Закрытие файла
	fin.close();
}

