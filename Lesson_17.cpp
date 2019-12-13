#include <iostream>
#include <conio.h>
#include <windows.h>
#define X 20
#define Y 10

using namespace std;

char lifenow[X][Y] = {};
char lifenext[X][Y] = {};
void Draw()
{
	system("cls");
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			cout << lifenow[j][i];
		}
		cout << endl;
	}
}
void Fill()
{
	srand(unsigned(0));

	
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			lifenow[j][i] = ((rand() % 3 == 0)?'o':0);
		}
	}
}
bool Keys() 
{
	unsigned char button;
	if (_kbhit())
	{
		button = _getch();
		switch (button) 
		{
			case 27: return true;
				break;
		}
	}
	return false;

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
			if (lifenow[j][i] == 'o' && cnt == 3) lifenext[j][i] = 'o';
			if (lifenow[j][i] == 0 && (cnt == 3 || cnt == 2)) lifenext[j][i] = 'o';
		}
		
	}
	Swap();
}
int main()
{

	while (true)
	{
		if(Keys())
			break;
		Update();
		Draw();
		Sleep(250);
	}
	return 0;
}