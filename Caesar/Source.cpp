#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    char tex[101]; // Исходная строка
    char shifr[101]; // Зашифрованная строка
    char rle[300]; // Сжатая строка
    char vosst[101]; // Восстановленная после RLE строка
    char rasshifr[101]; // Окончательно расшифрованная строка

    int i = 0;
    int j = 0;

    cout << "Введите строку из цифр: ";
    cin.getline(tex, 101);

    if (cin.fail())
    {
        cout << "Ошибка! Максимум 100 символов.";
        return 0;
    }

    // Проверка и шифрование
    while (tex[i] != '\0')
    {
        if (tex[i] < '0' || tex[i] > '9')
        {
            cout << "Ошибка! Допускаются только цифры.";
            return 0;
        }

        shifr[i] = (tex[i] - '0' + 3) % 10 + '0';
        i++;
    }

    shifr[i] = '\0';

    cout << "\nРезультат:" << endl;
    cout << "Исходная строка: " << tex << endl;
    cout << "Зашифрованная строка: " << shifr << endl;

    // Сжатие RLE
    i = 0;
    j = 0;

    while (shifr[i] != '\0')
    {
        int count = 1;

        while (shifr[i] != '\0' && shifr[i] == shifr[i + 1])
        {
            count++;
            i++;
        }

        rle[j] = shifr[i];
        j++;

        int temp = count;
        int digits = 0;
        char num[10];

        while (temp > 0)
        {
            num[digits] = temp % 10 + '0';
            temp /= 10;
            digits++;
        }

        while (digits > 0)
        {
            digits--;
            rle[j] = num[digits];
            j++;
        }

        // Разделитель между группами
        rle[j] = ' ';
        j++;

        i++;
    }

    if (j > 0)
    {
        j--;
    }    

    rle[j] = '\0';

    cout << "Сжатая строка: " << rle << endl;

    // Распаковка RLE
    i = 0;
    j = 0;

    while (rle[i] != '\0')
    {
        char digit = rle[i];
        i++;

        int count = 0;

        while (rle[i] >= '0' && rle[i] <= '9')
        {
            count = count * 10 + (rle[i] - '0');
            i++;
        }

        if (rle[i] == ' ')
        {
            i++;
        }
            
        for (int k = 0; k < count; k++)
        {
            vosst[j] = digit;
            j++;
        }
    }

    vosst[j] = '\0';

    cout << "Восстановленная зашифрованная строка: " << vosst << endl;

    // Расшифровка Цезаря
    i = 0;

    while (vosst[i] != '\0')
    {
        rasshifr[i] = (vosst[i] - '0' - 3 + 10) % 10 + '0';
        i++;
    }

    rasshifr[i] = '\0';

    cout << "Расшифрованная строка: " << rasshifr << endl;

    // Сравнение с исходной строкой
    i = 0;

    while (tex[i] != '\0' && tex[i] == rasshifr[i])
    {
        i++;
    }

    if (tex[i] == rasshifr[i])
    {
        cout << "Проверка: строки совпадают!" << endl;
    }

    else
    {
        cout << "Проверка: строки не совпадают!" << endl;
    }

    return 0;
}