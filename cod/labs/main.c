#include <stdio.h>
#include "../include/lab1.h"
#include "../include/lab2.h"
#include "../include/lab3.h"
#include "../include/lab4.h"
#include "../include/lab5.h"


int main ()
{
    int mode;
    while (1)
    {
        printf("\n1. Подсвечивание параметров программы.\n");
        printf("2. Одномерные массивы.\n");
        printf("3. Линейные списки.\n");
        printf("4. Двоичные деревья поиска.\n");
        printf("5. Поиск кратчайших путей в ориентированном графе.\n");
        printf("0. Выход.\n");

        if (scanf("%d", &mode) != 1) 
        {
            printf("Неверный ввод. Введите число.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        switch (mode)
        {
            case 1: l1(); break;
            case 2: l2(); break;
            case 3: l3(); break;
            case 4: l4(); break;
            case 5: l5(); break;
            case 0: printf("Выход."); return 0;
        }
    }
    
}