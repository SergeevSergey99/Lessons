/*#include <iostream>
//Необходимо для новых команд
#include <windows.h>
using namespace std;
//колличество элементов по горизонтали
#define X 32
//колличество элементов по вертикали
#define Y 16
// Массив элементов одного кадра
char lifenow[X][Y] = {};

void Draw()
{
	// Очистка экрана
	system("cls");
	//Построчный вывод слоев кадра
	for (int i = 0; i < Y; i++)
	{
		//Посимвольный вывод одного  слоя кадра
		for (int j = 0; j < X; j++)
		{
			cout << lifenow[j][i];
		}
		// Перевод на новую строку
		// Чтобы не вывести кадр одной строчкой
		cout << endl;
	}
}
char lifenext[X][Y] = {};
void Fill()
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			lifenow[j][i] = ((rand() % 3 == 0)?'O':0);
		}
	}
}
bool Keys()
{	
	// Функция GetKeyState дает много информации о клавише
	// Так как необходимо только узнать, нажата ли она?
	// Необходимо сделать СДВИГ вправо на 7 символов с помощью >> 
	if (GetKeyState(27) >> 7) // Если нажата клавиша
		// с кодом 27 (ESC), то возвращаем ложь 
		return false;
	if (GetKeyState(' ') >> 7)
		Fill();
	return true;
}
int countOfOther(int i, int j)
{
	int cnt = 0;
	//if (lifenow[(i) % X][(j) % Y] != 0) cnt++;
	if (lifenow[(i - 1) % X][(j) % Y] != 0) cnt++;
	if (lifenow[(i + 1) % X][(j) % Y] != 0) cnt++;
	if (lifenow[(i) % X][(j - 1) % Y] != 0) cnt++;
	if (lifenow[(i - 1) % X][(j - 1) % Y] != 0) cnt++;
	if (lifenow[(i + 1) % X][(j - 1) % Y] != 0) cnt++;
	if (lifenow[(i) % X][(j + 1) % Y] != 0) cnt++;
	if (lifenow[(i - 1) % X][(j + 1) % Y] != 0) cnt++;
	if (lifenow[(i + 1) % X][(j + 1) % Y] != 0) cnt++;
	return cnt;
}
void Swap()
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			lifenow[j][i] = lifenext[j][i];
		}
	}
}
void Update()
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			int cnt = countOfOther(j, i);
			if (cnt < 2 || cnt > 3) lifenext[j][i] = 0;
			if (lifenow[j][i] == 0 && cnt == 3) lifenext[j][i] = 'O';
			if (lifenow[j][i] == 'O' && (cnt == 3 || cnt == 2)) lifenext[j][i] = 'O';
		}

	}
	Swap();
}

int main()
{
	srand(unsigned(0));

	bool GameIsRun = true;
	while (GameIsRun) // Повтор пока GameIsRun == true
	{
		GameIsRun = Keys(); // Если нажата 
		// клавиша выхода ESC, то GameIsRun = false
		Update(); // Подготовка кадра
		Draw(); // Отрисовка кадра
		Sleep(60); // Задержка между кадрами
	}
	return 0;
}

*/