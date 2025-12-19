#include "../include/lab2.h"

void quick(int arr[], int low, int high) {
    if (low < high) {
        int opor = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < opor) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int r_pl = i + 1;
        quick(arr, low, r_pl - 1);
        quick(arr, r_pl + 1, high);
    }
}

void selection(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_el = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_el]) {
                min_el = j;
            }
        }
        int temp = arr[min_el];
        arr[min_el] = arr[i];
        arr[i] = temp;
    }
}

void pr_arr(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int* from_file(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия");
        return NULL;
    }
    if (fscanf(file, "%d", size) != 1) {
        printf("Ошибка чтения размера массива.\n");
        fclose(file);
        return NULL;
    }

    int* arr = malloc(*size * sizeof(int));

    if (!arr) {
        printf("Ошибка выделения памяти.\n");
        fclose(file);
        return NULL;
    }
    for (int i = 0; i < *size; i++) {
        if (fscanf(file, "%d", &arr[i]) != 1) {
            printf("Ошибка чтения элемента.\n");
            free(arr);
            fclose(file);
            return NULL;
        }
    }
    fclose(file);
    return arr;
}

int* gen_rand(int size) {
    int* arr = malloc(size * sizeof(int));
    if (!arr) {
        printf("Ошибка выделения памяти.\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
    return arr;
}

int l2(void) {
    srand(time(0));
    int choice, method, size;
    int* array;

    printf("Выберите метод сортировки:\n1. Быстрая сортировка\n2. Сортировка выбором\n");
    if (scanf("%d", &method) != 1) {
        printf("Ошибка ввода.\n");
        return 1;
    }

    printf("Выберите способ задания массива:\n1. Ввод с клавиатуры\n2. Генерация случайных чисел\n3. Чтение из файла\n");
    if (scanf("%d", &choice) != 1) {
        printf("Ошибка ввода.\n");
        return 1;
    }

    if (choice == 1) {
        printf("Введите размер массива: ");
        if (scanf("%d", &size) != 1) {
            printf("Ошибка ввода.\n");
            return 1;
        }
        array = malloc(size * sizeof(int));
        if (!array) {
            printf("Ошибка выделения памяти.\n");
            return 1;
        }
        printf("Введите элементы массива:\n");
        for (int i = 0; i < size; i++) {
            if (scanf("%d", &array[i]) != 1) {
                printf("Ошибка ввода.\n");
                free(array);
                return 1;
            }
        }
    } else if (choice == 2) {
        printf("Введите размер массива: ");
        if (scanf("%d", &size) != 1) {
            printf("Ошибка ввода.\n");
            return 1;
        }
        array = gen_rand(size);
        if (!array) return 1;
    } else if (choice == 3) {
        const char* filename = "second.txt";
        array = from_file(filename, &size);
        if (!array) return 1;
    } else {
        printf("Неверный выбор.\n");
        return 1;
    }

    printf("Исходный массив: ");
    pr_arr(array, size);

    if (method == 1) {
        quick(array, 0, size-1);
        printf("Отсортированный массив (быстрая сортировка): ");
    } else if (method == 2) {
        selection(array, size);
        printf("Отсортированный массив (сортировка выбором): ");
    } else {
        printf("Неверный выбор метода сортировки.\n");
        free(array);
        return 1;
    }

    pr_arr(array, size);
    free(array);
    return 0;
}