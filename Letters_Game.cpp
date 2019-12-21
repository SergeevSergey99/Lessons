/*#include<iostream>
#include<windows.h>
#define X 20
#define Y 10

using namespace std;

char Screen[X][Y] = {};
int countRight = 0;
int countAll = 0;

char letter = ' ';
void Draw() 
{
	system("cls");
	for (int j = 0; j < Y; j++)
	{
		for (int i = 0; i < X; i++)
		{
			// 			Screen[i][j] = j + i *X;
			cout << Screen[i][j];
		}
		cout << '\n';
	}
	cout << "\nUgadano " << countRight << " / " << countAll;
}
int x = 0, y = -1;
void Update() 
{
	if(y >= 0)
		Screen[x][y] = 0;
	y++;
	if (y == Y)
	{

		y = -1;
		x = rand() % X;
		countAll++;
		letter = rand() % 26 + (int)'A';
		return;
	}
	Screen[x][y] = letter;
}

bool Keys() 
{
	if (GetKeyState(27) >> 7)
		return false;
	if (GetKeyState((int)letter) >> 7)
	{
		Screen[x][y] = 0;
		y = -1;
		x = rand() % X;
		letter = rand() % 26 + (int)'A';
		countAll++;
		countRight++;
	}
	return true;
}
int main() 
{
	x = rand() % X;
	letter = rand() % 26 + (int)'A';
	bool isWork = true;
	while (isWork)
	{
		isWork = Keys();
		Update();
		Draw();
		Sleep(100);
	}
	system("pause");

	return 0;
}*/