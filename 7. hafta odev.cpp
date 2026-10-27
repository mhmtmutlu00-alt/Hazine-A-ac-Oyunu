#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// İşletim sistemine göre ekran temizleme ve bekleme kütüphaneleri(internetten baktım :D)
#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#define CLEAR() system("cls")
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#define CLEAR() system("clear")
#endif

// ANSI Renk Kodları(Gene internetten baktım :D)
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

// Düğüm yapısı
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// düğümü oluşturma
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// bst eleman ekleme
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) return createNode(value);
    if (value < root->data) root->left = insert(root->left, value);
    else if (value > root->data) root->right = insert(root->right, value);
    return root;
}

// düğüm kontrolü
int isVisited(int val, int path[], int pathLen) {
    for (int i = 0; i < pathLen; i++) {
        if (path[i] == val) return 1;
    }
    return 0;
}

// Piksel Art Küçük Ağaç Çizimi (Ziyaret edildiyse yeşil yanar)
void printTreeIcon(int val, int path[], int pathLen) {
    if (isVisited(val, path, pathLen)) {
        printf(GREEN "  🌲  " RESET);
    } else {
        printf("  🌲  ");
    }
}

// Çember Düğüm Çizimi (Ziyaret edildiyse yeşil yanar)
void printCircleNode(int val, int path[], int pathLen) {
    if (isVisited(val, path, pathLen)) {
        printf(GREEN "( %2d )" RESET, val);
    } else {
        printf("( %2d )", val);
    }
}

// Konsol 2D Grafik Ağacı (Ağaçlar ve Çemberler Animasyonlu)
void drawTreeGraph(int path[], int pathLen) {
    CLEAR();
    printf("==================================================\n");
    printf("       HAZINE AGACI - PIXEL ART 2D KONSOL OYUNU   \n");
    printf("==================================================\n\n");

    // Kök seviyesi
    printf("                    ");
    printTreeIcon(40, path, pathLen);
    printf("\n                    ");
    printCircleNode(40, path, pathLen);
    printf("  <-- Kok (Root)\n\n");

    printf("                   /        \\\n\n");

    // 1.seviye 
    printf("              ");
    printTreeIcon(20, path, pathLen);
    printf("              ");
    printTreeIcon(60, path, pathLen);
    printf("\n              ");
    printCircleNode(20, path, pathLen);
    printf("          ");
    printCircleNode(60, path, pathLen);
    printf("\n\n");

    printf("             /    \\          /    \\\n\n");

    // 2. seviye 
    printf("           ");
    printTreeIcon(10, path, pathLen);
    printf("   ");
    printTreeIcon(30, path, pathLen);
    printf("   ");
    printTreeIcon(50, path, pathLen);
    printf("   ");
    printTreeIcon(70, path, pathLen);
    printf("\n           ");
    printCircleNode(10, path, pathLen);
    printf(" ");
    printCircleNode(30, path, pathLen);
    printf(" ");
    printCircleNode(50, path, pathLen);
    printf(" ");
    printCircleNode(70, path, pathLen);
    printf("\n\n");

    printf("==================================================\n");
}

// Hedefe giden yolu bulma ve kaydetme
int findPath(struct Node* root, int target, int path[], int *pathLen) {
    if (root == NULL) return 0;

    path[(*pathLen)++] = root->data;

    if (root->data == target) return 1;

    if (target < root->data) {
        if (findPath(root->left, target, path, pathLen)) return 1;
    } else {
        if (findPath(root->right, target, path, pathLen)) return 1;
    }

    (*pathLen)--;
    return 0;
}

int main() {
    #ifdef _WIN32
    system("chcp 65001 > nul"); // Windows konsolunda UTF-8 / Emoji desteği
    #endif

    struct Node* root = NULL;
    int values[] = {40, 20, 60, 10, 30, 50, 70};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    // Başlangıç durumu (hiçbir şey yanmıyor)
    int activePath[100];
    int activeLen = 0;
    drawTreeGraph(activePath, activeLen);

    int target;
    printf("\nAramak istediginiz hazine degerini (sayiyi) girin: ");
    scanf("%d", &target);

    int fullPath[100];
    int fullPathLen = 0;

    if (findPath(root, target, fullPath, &fullPathLen)) {
        // Kökten hedefe doğru yavaş yavaş yeşil yanma animasyonu
        for (int i = 1; i <= fullPathLen; i++) {
            SLEEP(800); // 0.8 saniye bekle
            drawTreeGraph(fullPath, i);
            printf("\nKaziliyor... Adim %d: ( %d ) dugumu ve agaci yesillendi!\n", i, fullPath[i - 1]);
        }
        printf("\n" GREEN "HAZINE BULUNDU! Sandik acildi!" RESET "\n");
    } else {
        printf("\n" GREEN "Bosuna kazdin! Bu agacta boyle bir hazine yok." RESET "\n");
    }

    return 0;
}