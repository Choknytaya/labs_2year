#include "../include/lab4.h"

void showTrunks(struct Trunk* p) {
    if (p == NULL) return;
    showTrunks(p->prev);
    printf("%s", p->str);
}

void printTree(struct Node* root, struct Trunk* prev, int isLeft) {
    if (root == NULL) return;

    char* prev_str = "     ";
    struct Trunk* trunk = (struct Trunk*)malloc(sizeof(struct Trunk));
    trunk->prev = prev;
    trunk->str = prev_str;

    printTree(root->right, trunk, 1);

    if (!prev) {
        trunk->str = "-----";
    }
    else if (isLeft) {
        trunk->str = ".----";
        prev_str = "    |";
    }
    else {
        trunk->str = "`----";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    printf(" %d\n", root->key);

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "    |";

    printTree(root->left, trunk, 0);
    free(trunk);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int height(struct Node* node) {
    return node ? node->height : 0;
}

int getBalance(struct Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

struct Node* balance(struct Node* p) {
    if (!p) return p;

    p->height = max(height(p->left), height(p->right)) + 1;
    int balanceFactor = getBalance(p);

    if (balanceFactor > 1) {
        if (getBalance(p->left) < 0)
            p->left = leftRotate(p->left);
        return rightRotate(p);
    }
    if (balanceFactor < -1) {
        if (getBalance(p->right) > 0)
            p->right = rightRotate(p->right);
        return leftRotate(p);
    }
    return p;
}

struct Node* insert(struct Node* node, int key) {
    if (!node) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; //дубль

    return balance(node);
}

struct Node* findMin(struct Node* p) { //мин
    return p->left ? findMin(p->left) : p;
}

void freeTree(struct Node* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}


int diameter(struct Node* root, int* height) { //диаметр + макс
    if (root == NULL) {
        *height = 0;
        return 0;
    }
    
    int leftHeight = 0, rightHeight = 0;
    int leftDiameter = diameter(root->left, &leftHeight);
    int rightDiameter = diameter(root->right, &rightHeight);
    
    *height = max(leftHeight, rightHeight) + 1;
    
    return max(leftHeight + rightHeight, max(leftDiameter, rightDiameter));
}

int findMinLeafDistance(struct Node* root, int* minDepth) { //нах мин
    if (root == NULL) {
        *minDepth = INT_MAX;
        return INT_MAX;
    }
    
    if (root->left == NULL && root->right == NULL) {
        *minDepth = 0;
        return INT_MAX;
    }
    
    int leftMinDepth, rightMinDepth;
    int leftMin = findMinLeafDistance(root->left, &leftMinDepth);
    int rightMin = findMinLeafDistance(root->right, &rightMinDepth);
    
    int currentMin = INT_MAX;
    if (root->left != NULL && root->right != NULL) {
        currentMin = leftMinDepth + rightMinDepth + 2;
    }
    
    *minDepth = min(leftMinDepth, rightMinDepth) + 1;
    
    return min(currentMin, min(leftMin, rightMin));
}


void findMinMaxLeafPaths(struct Node* root, int* minPath, int* maxPath) { //поиск
    if (root == NULL) {
        *minPath = 0;
        *maxPath = 0;
        return;
    }

    int h = 0;
    *maxPath = diameter(root, &h);

    int minDepth = 0;
    *minPath = findMinLeafDistance(root, &minDepth);
    
    if (*minPath == INT_MAX) {
        *minPath = 0; //если 2 нет
    }
}

struct Node* readTreeFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        return NULL;
    }

    struct Node* root = NULL;
    int key;

    while (fscanf(file, "%d", &key) == 1) {
        root = insert(root, key);
    }

    fclose(file);
    return root;
}

int l4(void) {
    const char* filename = "for4.txt";
    
    struct Node* root = readTreeFromFile(filename);
    
    if (root == NULL) {
        printf("Не удалось построить дерево из файла %s\n", filename);
        printf("Ошибка файла\n");
        return 1;
    }

    printf("АВЛ-дерево %s:\n", filename);
    printTree(root, NULL, 0);
    printf("\n");

    int minPath, maxPath;
    findMinMaxLeafPaths(root, &minPath, &maxPath);
    
    printf("Минимальный путь между листьями: %d\n", minPath);
    printf("Максимальный путь между листьями: %d\n", maxPath);

    freeTree(root); //чистка
    
    return 0;
}