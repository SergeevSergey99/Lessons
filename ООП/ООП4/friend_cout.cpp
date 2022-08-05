#include<iostream>
using namespace std;

class Point 
{
public:
	int x = 0;
	int y = 0;

	// Конструктор
	Point(int X, int Y) 
	{
		x = X;
		y = Y;
	}

	// Объявление дружественного оператора вывода текста на экран
	friend ostream& operator<< (ostream& out, const Point& point);
};

// Перегрузка оператора вывода текста на экран
ostream& operator << (ostream& out, const Point& point) 
{
	// Добавление в поток вывода нужных данных
	out << "(" << point.x << ", " << point.y << ")";
	return out;
}

int main() 
{
	setlocale(LC_ALL, "Rus");

	Point p(5, 6);

	cout << "p = " << p << endl;
}

