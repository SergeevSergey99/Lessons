#include<iostream>
using namespace std;

// ���������� ������ B ����� ��� ����� ���� ������������ � ������ A
class B;

class A 
{
private:
	int x;
public:
	// �����������
	A(int a) { x = a; }
	// ������������� �������
	// ������� ����� ������ �� ��� �������� ����, ������� 
	// � 5 ������� ����� ���� �������� B ����� ������� ����� ��� ����� ����� �����
	friend int sum(A a, B b);
};

class B 
{
private:
	int y;
public:
	// �����������
	B(int b) { y = b; }
	// ������������� �������
	friend int sum(A a, B b);
};

// ����������� ������������� �������
int sum(A a, B b) 
{
	// ������� ����� ������ � private ��������� �������
	int result = a.x + b.y;
	return result;
}

int main() 
{
	A a(5);
	B b(7);
	cout << sum(a, b) << endl;
}

