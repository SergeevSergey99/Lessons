/*#include <iostream>
using namespace std;
int main() {
	short mas[256] = {};
	int n;
	cout << "Введите колличество букв: ";
	cin >> n;
	cout << "Вводите буквы через пробел:\n";
	for (int i = 0; i < n; i++){
		char tmp;
		cin >> tmp;
		mas[(int)tmp]++;	
	}
	cout << "\nБуквы отсортированные по алфавиту:\n";
	for(int i = 0; i < 256; i++){
		while(mas[i] > 0){
			cout << (char)i << " ";
			mas[i]--;
		}

	}
}
*/