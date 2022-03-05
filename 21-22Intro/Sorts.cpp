#include<iostream>
#include<ctime>
using namespace std;

// Массив из N элементов
const int N = 1000;
int mas[N] = {};

void INPUT()
{
    // Ввод элементов массива
    for (int i = 0; i < N; i++)
    {
        cin >> mas[i];
    }
}
void RAND_MAS()
{
    // Генерация элементов массива
    for (int i = 0; i < N; i++)
    {
        mas[i] = rand() % 1000;
    }
}
void BUBBLE_SORT() 
{
    // Сортировка
    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N - 1 - j; i++)
        {
            if (mas[i] > mas[i + 1]) 
            {
                int tmp = mas[i];
                mas[i] = mas[i + 1];
                mas[i + 1] = tmp;
            }
        }
    }
}

int merge_mas[N];
void MERGE_SORT(int start, int length) 
{
    if (length <= 1)
        return;

    MERGE_SORT(start, length / 2);
    MERGE_SORT(start + length / 2, length - length / 2);
    
    int i = start;
    int j = start + length / 2;
        for (int k = start; k < start + length; k++)
    {
        if (j >= start + length or (i < start + length / 2 and mas[i] < mas[j]))
        {
            merge_mas[k] = mas[i];
            i++;
        }
        else
        {
            merge_mas[k] = mas[j];
            j++;
        }
    }

    for (size_t i = start; i < start + length; i++)    
        mas[i] = merge_mas[i];
}

void OUTPUT()
{
    // Вывод массива на экран
    for (int i = 0; i < N; i++)
    {
        cout << mas[i] << " ";
    }
    cout << endl;
    cout << endl;
}

int main() 
{
    RAND_MAS();
    OUTPUT();

    clock_t start  = clock();
    BUBBLE_SORT();
    clock_t sort_time = clock() - start;

    OUTPUT();

    cout << "SortTime: " << sort_time * 1.0 / CLOCKS_PER_SEC << endl << endl;

    system("pause");
}
