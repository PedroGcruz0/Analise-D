#include <stdio.h>
#include <stdlib.h> // Para alocação de memória (malloc, free)
#include <stdbool.h> // Para usar o tipo de dado bool (true/false)
#include <math.h> // Para a função sqrt

/**
 * @brief Encontra todos os números primos até n usando o Crivo de Eratóstenes.
 * * @param n O número limite para a busca.
 * @param count Um ponteiro para uma variável inteira que armazenará a quantidade de primos encontrados.
 * @return Um ponteiro para um array de inteiros contendo os números primos. A memória para este array é alocada dinamicamente e deve ser liberada pelo chamador.
 */
int* encontrar_primos(int n, int* count) {
    // 1. Aloca um array booleano para marcar os números.
    // O tamanho é n + 1 para que o índice corresponda ao número (primos[i] -> número i).
    bool* primos_marcados = (bool*) malloc((n + 1) * sizeof(bool));
    if (primos_marcados == NULL) {
        printf("Erro de alocação de memória.\n");
        *count = 0;
        return NULL;
    }

    // 2. Inicializa todos os números como potencialmente primos (true).
    for (int i = 0; i <= n; i++) {
        primos_marcados[i] = true;
    }

    primos_marcados[0] = false; // 0 não é primo
    primos_marcados[1] = false; // 1 não é primo

    // 3. Implementa o Crivo de Eratóstenes.
    // Itera de 2 até a raiz quadrada de n.
    for (int p = 2; p * p <= n; p++) {
        // Se p ainda está marcado como primo...
        if (primos_marcados[p]) {
            // ...marca todos os seus múltiplos como não primos.
            for (int i = p * p; i <= n; i += p) {
                primos_marcados[i] = false;
            }
        }
    }

    // 4. Primeira passagem: Conta quantos números primos foram encontrados.
    *count = 0;
    for (int p = 2; p <= n; p++) {
        if (primos_marcados[p]) {
            (*count)++;
        }
    }

    // 5. Aloca memória para o array final que conterá apenas os números primos.
    int* primos_encontrados = (int*) malloc(*count * sizeof(int));
    if (primos_encontrados == NULL) {
        printf("Erro de alocação de memória.\n");
        free(primos_marcados); // Libera a memória do array de marcação
        *count = 0;
        return NULL;
    }

    // 6. Segunda passagem: Preenche o array final com os números primos.
    int j = 0;
    for (int p = 2; p <= n; p++) {
        if (primos_marcados[p]) {
            primos_encontrados[j] = p;
            j++;
        }
    }

    // 7. Libera a memória do array de marcação, que não é mais necessário.
    free(primos_marcados);

    // 8. Retorna o array com os resultados.
    return primos_encontrados;
}

int main() {
    int n;
    int status;

    // Loop para garantir que o usuário digite um número válido
    while (1) {
        printf("Digite um número inteiro N > 0: ");
        status = scanf("%d", &n);

        if (status == 1 && n > 0) {
            // Entrada válida e positiva, sai do loop
            break;
        } else {
            // Limpa o buffer de entrada para evitar loops infinitos
            // se o usuário digitar um caractere em vez de um número.
            while (getchar() != '\n');
            
            if (status != 1) {
                printf("Entrada inválida. Por favor, digite um número inteiro.\n");
            } else {
                printf("O número deve ser maior que 0. Tente novamente.\n");
            }
        }
    }

    int quantidade_primos = 0;
    // Chama a função para encontrar os primos. Passamos o endereço da variável
    // 'quantidade_primos' para que a função possa preenchê-la com o total.
    int* primos_encontrados = encontrar_primos(n, &quantidade_primos);

    // Exibe os resultados
    if (primos_encontrados != NULL) {
        printf("------------------------------\n");
        printf("Valor de N: %d\n", n);
        printf("Números primos encontrados: ");
        for (int i = 0; i < quantidade_primos; i++) {
            printf("%d ", primos_encontrados[i]);
        }
        printf("\n");
        printf("Quantidade de números primos encontrados: %d\n", quantidade_primos);
        printf("------------------------------\n");

        // Libera a memória alocada para o array de resultados. Essencial em C!
        free(primos_encontrados);
    }

    return 0;
}