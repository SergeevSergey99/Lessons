#include <iostream>
#define X 20
#define Y 10

using namespace std; 

char screenChar[X][Y] = {};

void Draw()
{
		for(int i = 0; i < Y; i++)
		{
			for(int j = 0; j < X; j++)
			{
				cout << screenChar[j][i] ;
			}
			cout << endl;
		}
}

int main()
{
	for(int j = 0; j < Y; j++)
	{
		for(int i = 0; i < X; i++)
		{
			screenChar[i][j] = (char)(i+50);
		}
	}
	
	Draw();

	return 0;
}