#include <iostream>
using namespace std;

class Pixel 
{
protected:
	int x = 0, y = 0, color = 0;
public:
	Pixel()
	{
		x = 0;
		y = 0;
		color = 0;
	}
	Pixel(int x, int y, int color)
	{
		this->x = x;
		this->y = y;
		this->color = color;
	}
	void printPixel()
	{
		cout << "color: " << color << endl;
		cout << "x: " << x << endl;
		cout << "y: " << y << endl;
	}
};


class Pixel3d : public Pixel
{
private:
	int z = 0;
public:
	Pixel3d() 
	{
		z = 0;
	}
	Pixel3d(int x, int y, int z, int color) : Pixel(x, y, color)
	{
		this->z = z;
	}
	void printPixel() 
	{
		Pixel::printPixel();

		cout << "z: " << z << endl;
	}
 
	friend Pixel3d operator + (Pixel3d a, Pixel3d b);

};

Pixel3d operator + (Pixel3d a, Pixel3d b) 
{
	a.color = a.color + b.color;
	a.x = a.x + b.x;
	a.y = a.y + b.y;
	a.z = a.z + b.z;

	return a;
}

int main() 
{
	Pixel3d p1_3d(1, 2, 3, 42);
	Pixel3d p2_3d(5, 2, 1, 100);
	
	p1_3d = p1_3d + p2_3d;
	p1_3d.printPixel();

	return 0;
}