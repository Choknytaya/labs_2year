#include "../include/lab1.h"

int dopust_char(int c) { // допустимый символ
    return isalnum(c) || c == '_';
}

int l1(void) { // открытие файла
    FILE *file = fopen("t1.txt", "r"); 
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int comment_1 = 0; // (//)
    int comment_2 = 0; // (/* ... */)
    int in_string = 0; // строка
    int in_char = 0;   // символьный литерал
    int cikl = 0;       // флаг для слова "for" или "while"
    int pod = 0;       // флаг для скобки после слова

    char line[MAX_LINE];

    int start = 0, end = 0; // объявляем заранее

    while (fgets(line, sizeof(line), file)) {
        int len = strlen(line);
        int i = 0;

        while (i < len) { // обработка
            if (!in_string && !in_char && !comment_1 && !comment_2) {
                if (line[i] == '/' && i + 1 < len && line[i + 1] == '/') {
                    comment_1 = 1;
                } else if (line[i] == '/' && i + 1 < len && line[i + 1] == '*') {
                    comment_2 = 1;
                }
            }

            if (comment_1) {
                printf("%c", line[i]);
                i++;
                continue;
            }

            if (comment_2) {
                if (line[i] == '*' && i + 1 < len && line[i + 1] == '/') {
                    comment_2 = 0;
                    printf("*/");
                    i += 2;
                } else {
                    printf("%c", line[i]);
                    i++;
                }
                continue;
            }

            if (!in_char && line[i] == '"' && (i == 0 || line[i - 1] != '\\')) { // строка
                in_string = !in_string;
                printf("%c", line[i]);
                i++;
                continue;
            }

            if (!in_string && line[i] == '\'' && (i == 0 || line[i - 1] != '\\')) { // литерал
                in_char = !in_char;
                printf("%c", line[i]);
                i++;
                continue;
            }

            if (in_string || in_char) { // внутри строки или литерала
                printf("%c", line[i]);
                i++;
                continue;
            }

            if (dopust_char(line[i])) { // допустимый символ
                start = i;
                while (i < len && dopust_char(line[i])) {
                    i++;
                }
                end = i;

                if (end > start) {
                    int k = start; // объявляем внутри блока
                    if ((end - start) == 3) {
                        if (line[k] == 'f' && line[k + 1] == 'o' && line[k + 2] == 'r') {
                            cikl = 1;
                        }
                    }
                    if ((end - start) == 5) {
                        if (line[k] == 'w' && line[k + 1] == 'h' && line[k + 2] == 'i' && line[k + 3] == 'l' && line[k + 4] == 'e') {
                            cikl = 1;
                        }
                    }

                    if (cikl == 1) {
                        for (int j = start; j < end; j++) {
                            printf("%c", line[j]);
                        }
                    }

                    while (i < len && isspace(line[i])) i++; // пропускаем пробелы
                    if (cikl == 1) {
                        start = end;
                        cikl = 0;
                        pod = 1;
                    }
                    if (i < len && line[i] == '(' && pod) {
                        printf("\033[31m"); // цвет
                        for (int j = start; j < end; j++) {
                            printf("%c", line[j]);
                        }
                        printf("\033[0m"); // сброс цвета
                        for (int j = end; j < i; j++) {
                            printf("%c", line[j]);
                        }
                        printf("(");
                        i++;
                        continue;
                    } else { // нет скобки
                        for (int j = start; j < end; j++) {
                            printf("%c", line[j]);
                        }
                    }
                }
            } else { // остальной текст
                printf("%c", line[i]);
                i++;
            }
        }
        comment_1 = 0; // сброс комментариев в конце строки
    }

    fclose(file);
    return 0;
}