#include "../include/lab3.h"

Node_3l* createNode(int value) {
    Node_3l* newNode = (Node_3l*)malloc(sizeof(Node_3l));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void append(Node_3l** head, int value) {
    Node_3l* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    Node_3l* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

int contains(Node_3l* head, int value) {
    Node_3l* current = head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Node_3l* difference(Node_3l* L1, Node_3l* L2) {
    Node_3l* result = NULL;
    Node_3l* current = L1;
    
    while (current != NULL) {
        if (!contains(L2, current->data)) {
            append(&result, current->data);
        }
        current = current->next;
    }
    
    return result;
}

void printList(Node_3l* head) {
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    
    Node_3l* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}

void deleteList(Node_3l** head) {
    Node_3l* current = *head;
    Node_3l* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL;
}

Node_3l* createListFromString(const char* input) {
    Node_3l* list = NULL;
    char* rest = (char*)malloc(strlen(input) + 1);
    if (!rest) return NULL;
    
    strcpy(rest, input);
    char* token = strtok(rest, " ");
    
    while (token != NULL) {
        // Проверяем, является ли токен числом
        int valid = 1;
        for (int i = 0; token[i] != '\0'; i++) {
            if (!isdigit(token[i]) && !(i == 0 && token[i] == '-')) {
                valid = 0;
                break;
            }
        }
        
        if (valid) {
            int value = atoi(token);
            append(&list, value);
        }
        token = strtok(NULL, " ");
    }
    
    free(rest);
    return list;
}

int l3(void) {
    int choice;
    char input[1000];
    
    printf("Программа для работы с линейными списками\n");
    printf("Функция: формирование списка из элементов L1, которых нет в L2\n\n");
    
    do {
        printf("Меню:\n");
        printf("1. Ввод списков\n");
        printf("2. Выход\n");
        printf("Выберите опцию: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода! Пожалуйста, введите число.\n");
            while (getchar() != '\n'); // Очистка буфера
            continue;
        }
        getchar(); 
        
        switch (choice) {
            case 1: {
                printf("Введите список 1 (целые числа через пробел): ");
                if (fgets(input, sizeof(input), stdin) == NULL) {
                    printf("Ошибка чтения ввода!\n");
                    break;
                }
                input[strcspn(input, "\n")] = 0;
                
                Node_3l* L1 = createListFromString(input);
                if (L1 == NULL) {
                    printf("Ошибка при создании списка 1!\n");
                    break;
                }
                
                printf("Введите список 2 (целые числа через пробел): ");
                if (fgets(input, sizeof(input), stdin) == NULL) {
                    printf("Ошибка чтения ввода!\n");
                    deleteList(&L1);
                    break;
                }
                input[strcspn(input, "\n")] = 0;
                
                Node_3l* L2 = createListFromString(input);
                if (L2 == NULL) {
                    printf("Ошибка при создании списка 2!\n");
                    deleteList(&L1);
                    break;
                }
                
                printf("\nИсходные списки:\n");
                printf("Список 1: ");
                printList(L1);
                printf("Список 2: ");
                printList(L2);
                
                Node_3l* result = difference(L1, L2);
                printf("Результат (элементы L1, которых нет в L2): ");
                printList(result);
                
                deleteList(&L1);
                deleteList(&L2);
                deleteList(&result);
                break;
            }
                
            case 2:
                printf("Выход из программы.\n");
                break;
                
            default:
                printf("Неверный выбор. Пожалуйста, выберите 1 или 2.\n");
        }
        
        printf("\n");
    } while (choice != 2);
    
    return 0;
}