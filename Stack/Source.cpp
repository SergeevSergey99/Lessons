#include<iostream>
#include<string>

template<typename T>
class Stack
{
public:

	void push(T x) 
	{
		mas[i] = x;
		i++;
	}

	T pop() 
	{
		T temp;
		temp = mas[i - 1];
		i--;
		return temp;
	}

	int size() 
	{
		return i;
	}

	T top() 
	{
		return mas[i - 1];
	}

private:
	int i = 0;
	T mas[1000];
};

int main()
{
	Stack<std::string> st;

	st.push("ds");
	st.push("vcydjuf");
	st.push("vuifdh");
	st.push("\fnkjr");
	st.push("uyucb");
	st.push("rtyuiol");

	while (st.size() > 0)
		std::cout << st.pop() << std::endl;

	return 0;
}