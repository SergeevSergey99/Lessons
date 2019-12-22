#include<iostream>
#include<windows.h>
#define X 20
#define Y 10

using namespace std;
// массив кадра
char Screen[X][Y] = {};

void Draw() 
{
	// Очистка экрана
	system("cls");
	//Отрисовка содержимого массива кадра
	for (int j = 0; j < Y; j++)
	{
		for (int i = 0; i < X; i++)
		{
			cout << Screen[i][j];
		}
		cout << '\n';
	}
}
void Update() 
{
	/*
	* Добавить код логики
	*/
}

bool Keys() 
{
	// Если нажата ESC выходим
	if (GetKeyState(27) >> 7)
		return false;

	return true;
}
int main() 
{
	// Рисуем новые кадры пока не нажмем кнопку выхода
	while (Keys())
	{
		// Логика программы
		Update();
		// Отрисовка кадра
		Draw();
		// Задержка между кадрами
		Sleep(100);
	}
	// Пауза перед завершением
	system("pause");

	return 0;
}