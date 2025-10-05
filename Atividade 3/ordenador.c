#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Protótipos das Funções
void bubbleSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
void printSystemInfo();
void swap(int* a, int* b);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <bubble|quick>\n", argv[0]);
        return 1;
    }

    // --- Leitura do Arquivo ---
    FILE *file = fopen("arq.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo arq.txt");
        return 1;
    }

    int *numeros = NULL;
    int count = 0;
    int capacity = 1000; // Capacidade inicial
    numeros = (int *)malloc(capacity * sizeof(int));
    if (numeros == NULL) {
        perror("Falha ao alocar memória inicial");
        fclose(file);
        return 1;
    }

    int num;
    while (fscanf(file, "%d", &num) == 1) {
        if (count >= capacity) {
            capacity *= 2;
            int *temp = (int *)realloc(numeros, capacity * sizeof(int));
            if (temp == NULL) {
                perror("Falha ao realocar memória");
                free(numeros);
                fclose(file);
                return 1;
            }
            numeros = temp;
        }
        numeros[count++] = num;
    }
    fclose(file);

    // --- Coleta de Informações do Sistema ---
    printSystemInfo();

    // --- Medição de Desempenho ---
    clock_t start, end;
    double cpu_time_used_ms;

    start = clock(); // Inicia a contagem do tempo

    if (strcmp(argv[1], "bubble") == 0) {
        bubbleSort(numeros, count);
    } else if (strcmp(argv[1], "quick") == 0) {
        quickSort(numeros, 0, count - 1);
    } else {
        fprintf(stderr, "Algoritmo desconhecido: %s. Use 'bubble' ou 'quick'.\n", argv[1]);
        free(numeros);
        return 1;
    }

    end = clock(); // Finaliza a contagem do tempo

    cpu_time_used_ms = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    
    // Estimativa da memória utilizada (baseada no array alocado)
    // Medir o uso de RAM do processo inteiro não é padronizado em C.
    long memory_used_kb = (count * sizeof(int)) / 1024;


    printf("Resultados para o algoritmo: %s\n", argv[1]);
    printf("Tempo de execucao: %.2f ms\n", cpu_time_used_ms);
    printf("Memoria RAM: %ld KB\n", memory_used_kb);
    


    
    // Libera a memória alocada
    free(numeros);

    return 0;
}


// --- Implementação das Funções Auxiliares ---

void printSystemInfo() {
    printf("--- Informacoes da Plataforma e S.O. ---\n");
    printf("Linguagem: C\n");

    // Identifica o sistema operacional em tempo de compilação
    #if defined(_WIN32)
        printf("Sistema Operacional: Windows\n");
    #elif defined(__linux__)
        printf("Sistema Operacional: Linux\n");
    #elif defined(__APPLE__) && defined(__MACH__)
        printf("Sistema Operacional: macOS\n");
    #else
        printf("Sistema Operacional: Desconhecido\n");
    #endif
    
}


void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Algoritmo Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Partição para o Quicksort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Algoritmo Quicksort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}