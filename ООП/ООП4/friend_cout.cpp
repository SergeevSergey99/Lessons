#include<iostream>
using namespace std;

class Point 
{
public:
	int x = 0;
	int y = 0;

	// �����������
	Point(int X, int Y) 
	{
		x = X;
		y = Y;
	}

	// ���������� �������������� ��������� ������ ������ �� �����
	friend ostream& operator<< (ostream& out, const Point& point);
};

// ���������� ��������� ������ ������ �� �����
ostream& operator << (ostream& out, const Point& point) 
{
	// ���������� � ����� ������ ������ ������
	out << "(" << point.x << ", " << point.y << ")";
	return out;
}

int main() 
{
	setlocale(LC_ALL, "Rus");

	Point p(5, 6);

	cout << "p = " << p << endl;
}

