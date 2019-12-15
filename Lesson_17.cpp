/*#include <iostream>
#include <windows.h>
#define X 32
#define Y 16

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
			printf("%c", lifenow[j][i]);
//			cout << lifenow[j][i];
		}
		printf("\n");
//		cout << endl;
	}
}
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
	if (GetKeyState(27) >> 7)
		return true;
	if (GetKeyState(' ') >> 7)
		Fill();
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
			if (lifenow[j][i] == 0 && cnt == 3) lifenext[j][i] = 'O';
			if (lifenow[j][i] == 'O' && (cnt == 3 || cnt == 2)) lifenext[j][i] = 'O';
		}

	}
	Swap();
}
int main()
{
	srand(unsigned(0));

	while (true)
	{
		if(Keys())
			break;
		Update();
		Draw();
		Sleep(80);
	}
	return 0;
}*/