
#include <Windows.h> 
#include <WinGDI.h>  // файл, где описана структура BitmapInfoHeader
#include <stdio.h>
#include <locale.h> 
#include <math.h>
#include <iostream> 
#include <cmath>
#include <tchar.h>

#define _CRT_SECURE_NO_WARNING
#pragma comment(linker, "/STACK:8388608")   //  8388608 67108864


BITMAPFILEHEADER bfh; // переменная для хранения заголовка Bitmap
BITMAPINFOHEADER bih; // переменная для хранения заголовка Bitmap

#define WIDTH 28
#define HEIGHT 28
using namespace std;
double aktiva(double x)
{
    double k = 2.71828182845904523536028747135266249775724709369995;
    double y = 0;
    // y = x;
     //   y = 1 / (pow(k, -1 * x) + 1);
   // if (x > 0) y = x;
  //  else
    y = 1 / (1 + pow(k, -x));
    //x * 0.01;;
    return y;

}

int main(int argc, char* argv[])
{


    int a[WIDTH * HEIGHT ] = { 0 };
    int res = 0; // вспомогательная переменная
    FILE* fd;  // file descriptor, файловый дескриптор
    int point; // точка
    int name = 0;
    setlocale(LC_ALL, "rus");
    //////////////////////////////////
    double w[WIDTH * HEIGHT][10];//веса 1 круга
    double b[10];//1 kryg
    //double c[16];
    //double h[16][16];// weight 2 
  //  double d[16];//2 kryg
    //double e[16];
   // double p[10][16];// weight 3 
    //double f[16];//3 kryg
    double r[10];//result
    double o[10];//error
    double ne[10];// что должны получить
   // double xx[10][WIDTH * HEIGHT];
    double owibka = 0;
    double  y[10] = { 0 };
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        for (int j = 0; j < 10; j++)
            w[i][j] = 0.001;

    for (int i = 0; i < 10; i++)
        b[i] = 1;
    for (int i = 0; i < 10; i++)
        r[i] = 1;
    for (int i = 0; i < 10; i++)
        y[i] = 1;


    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    BOOL bbb;

    hFind = FindFirstFile(L"0\\0\\*", &FindFileData);
    if (hFind != INVALID_HANDLE_VALUE)
        bbb = FindNextFile(hFind, &FindFileData);

   do
    {
       
       bbb = FindNextFile(hFind, &FindFileData);
        _tprintf(TEXT("The first file found is %s\n"), FindFileData.cFileName);
        char name_str[64];
        //sprintf_s(name_str, "%d.bmp", name);
       
        //sprintf_s(name_str, "0//0//%d//1.bmp", name);
       // name_str = ( char)FindFileData.cFileName;
       // name_str= FindFileData.cFileName
       // fopen_s(&fd, name_str, "r"); // открываем файл для чтения
        fopen_s(&fd, (const char*)FindFileData.cFileName, "r"); // открываем файл для чтения

       // fopen_s(&fd,(const char*)FindFileData.cFileName, "r");
        if (fd == NULL)
        {
            printf("File not opened\n");
            //cout<< name;
            break;
        }

        // чтение заголовка файла
        res = fread(&bfh, sizeof(bfh), 1, fd);
        if (res > 0) {
            //printf("Заголовок файла прочитан\n");
        }
        else
        {
            printf("Заголовок файла не прочитан\n");
            break;
        }

        // вывод информации
      ///  printf("Тип файла: %X\n", bfh.bfType);
      //  printf("Размер файла в байтах: %d\n", bfh.bfSize);
       // printf("\n");

        // чтение описания bmp
        res = fread(&bih, sizeof(bih), 1, fd);
        if (res > 0) {
            //printf("Заголовок BITMAP прочитан\n");
        }
        else
        {
            printf("Заголовок BITMAP не прочитан\n");
            exit(0);
        }

        // вывод информации

      //  printf("Размер структуры заголовка bitmap: %d\n", bih.biSize);

       // printf("Высота изображения: %d\n", bih.biHeight);
       // printf("Ширина изображения: %d\n", bih.biWidth);
       // printf("Бит на пиксел: %d\n", bih.biBitCount);
      //  printf("BitCount = %d\n", bih.biBitCount);


        for (int i = 0; i < bih.biWidth; i++)
        {
            for (int j = 0; j < bih.biHeight; j++)
            {
                point = 0;
                fread(&point, bih.biBitCount / 8, 1, fd);
                ////printf("%14u ", point);
               //printf("%X ", point);
               // a[(i - 1) * j + j] = point;
                a[i * j + j] = point;
                // a[i * j + j] = a[i * j + j] - 3422552064;
                a[i * j + j] = a[i * j + j] / 16777215;
                //cout << a[i * j + j] << " ";
                // printf("%10 ", point);
              //   printf("%X ", a[(i - 1) * j + j]);//000000 - black
                if (a[i * j + j] == 0) a[i * j + j] = 1;
                else a[i * j + j] = 0;
            }
            //   printf("\n");
        }

        // for (int i = 0; i < bih.biWidth * bih.biHeight; i++)
       //  {
       //      a[i] = 0;
       //  }
        fclose(fd);
        //double a[WIDTH * HEIGHT];

        for (int j = 0; j < 10; j++)
            for (int i = 0; i < WIDTH * HEIGHT; i++)
            {
                //for (int j = 0; i < WIDTH * HEIGHT * 16; i++)
                r[j] = r[j] + a[i] * w[i][j];
            }
        for (int j = 0; j < 10; j++)
        {
            r[j] = r[j] - b[j];// - f[j];
            y[j] = aktiva(r[j]);
        }


        int namer = name % 10;
        for (int i = 0; i < 10; i++)
            if (i != namer)ne[i] = 0;
            else ne[i] = 1;


        owibka = 0;
        for (int i = 0; i < 10; i++)
        {
            owibka = owibka + (ne[i] - y[i]) * (ne[i] - y[i]);
            o[i] = (ne[i] - y[i]) * (ne[i] - y[i]);
        }
        int result = 0;
        for (int i = 0; i < 10; i++)
        {
            if (ne[i] == 1) result = i;
        }///////////////////////////////
        double rt = 0;
        for (int i = 0; i < 10; i++)
        {
            rt = rt + (ne[i] - y[i]);
        }
        double al[WIDTH * HEIGHT][10] = { 0 };
        for (int k = 0; k < 10; k++)
            for (int i = 0; i < WIDTH * HEIGHT; i++)
            {

                al[i][k] = 2 * rt * y[k] * (1 - y[k]) * a[i];
            }
        ///////

        double al1[10] = { 0 };
        for (int k = 0; k < 10; k++)

        {

            al1[k] = -2 * rt;
        }

        double alifa = 0.01;
        //if (name < 6)
            //for (int j = 0; j < 10; j++)
           for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
          //  int i = name%10;
               int j = name % 10;
               
                w[i][j] = w[i][j] - alifa * al[i][j];// w1[10] [WIDTH * HEIGHT][16];
            }
       
        //for (int j = 0; j < 10; j++)
        {
           int j = name % 10;
            b[j] = b[j] - alifa * al1[j];
        }


         name++;
         

    }while (b != NULL);
    FindClose(hFind);

    
    char name_str[64];
    //sprintf_s(name_str, "%d.bmp", name);
    sprintf_s(name_str, "x.bmp");

    fopen_s(&fd, name_str, "r"); // открываем файл для чтения
    if (fd == NULL)
    {
        printf("File not opened\n");
        exit(0);
    }

    // чтение заголовка файла
    res = fread(&bfh, sizeof(bfh), 1, fd);
    if (res > 0) {
        //printf("Заголовок файла прочитан\n");
    }
    else
    {
        printf("Заголовок файла не прочитан\n");
        exit(0);
    }

    // вывод информации
  ///  printf("Тип файла: %X\n", bfh.bfType);
  //  printf("Размер файла в байтах: %d\n", bfh.bfSize);
   // printf("\n");

    // чтение описания bmp
    res = fread(&bih, sizeof(bih), 1, fd);
    if (res > 0) {
        //printf("Заголовок BITMAP прочитан\n");
    }
    else
    {
        printf("Заголовок BITMAP не прочитан\n");
        exit(0);
    }

    // вывод информации

  //  printf("Размер структуры заголовка bitmap: %d\n", bih.biSize);

   // printf("Высота изображения: %d\n", bih.biHeight);
   // printf("Ширина изображения: %d\n", bih.biWidth);
   // printf("Бит на пиксел: %d\n", bih.biBitCount);

    for (int i = 0; i < bih.biWidth; i++)
    {
        for (int j = 0; j < bih.biHeight; j++)
        {
            point = 0;
            fread(&point, bih.biBitCount / 8, 1, fd);
            //printf("%14u ", point);
           // printf("%X ", point);
            a[i * j + j] = point;
            //a[i * j + j] = a[i * j + j] - 3422552064;//-cc
            a[i * j + j] = a[i * j + j] / 16777215;//%
            //   printf("%X ", a[(i - 1) * j + j]);//000000 - black
        }
        //   printf("\n");
    }
    fclose(fd);


    for (int j = 0; j < 10; j++)
        for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
            //for (int j = 0; i < WIDTH * HEIGHT * 16; i++)
            r[j] = r[j] + a[i] * w[i][j];
        }
    for (int j = 0; j < 10; j++)
    {
        r[j] = r[j] - b[j];// - f[j];
        y[j] = aktiva(r[j]);
    }


    int max = 0;
    for (int i = 1; i < 10; i++)
    {
        if (y[i] > y[max]) { max = i; }
    }
    cout << endl << max;
    return 0;
}