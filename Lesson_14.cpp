#include <cmath>
#include <iostream>

int rec_fact(int x)
{
	if (x <= 1) return 1;
	return x * rec_fact(x-1);
}

bool isSimple(int x)
{
	int max = (int) sqrt(x);
	for(int i = 2; i <= max; i++)
	{
		if(x % i == 0)
			return false;
	}
	return true;
}
int main()
{
	int a;
	std::cin>>a;
	std::cout<<"Число "<<a<< (isSimple(a)?" простое":" не простое");
	std::cout << std::endl << rec_fact(a);
	
	return 0;
}
