#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

// --- ESTRUTURAS DE DADOS ---

// Estrutura para um nó da lista
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Estrutura para a lista encadeada
typedef struct LinkedList {
    Node* head;
} LinkedList;

// --- FUNÇÕES DA LISTA ENCADEADA ---

// Cria e retorna um novo nó com o dado fornecido
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Erro de alocação de memória para o nó.\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Inicializa e retorna uma nova lista encadeada
LinkedList* create_linked_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        fprintf(stderr, "Erro de alocação de memória para a lista.\n");
        exit(1);
    }
    list->head = NULL;
    return list;
}

// Libera toda a memória alocada para a lista
void free_list(LinkedList* list) {
    if (list == NULL) return;
    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

// Adiciona um nó em uma posição específica
void add_node(LinkedList* list, int data, int position) {
    Node* new_node = create_node(data);
    if (position == 0) {
        new_node->next = list->head;
        list->head = new_node;
        return;
    }

    Node* current = list->head;
    int current_pos = 0;
    while (current_pos < position - 1 && current != NULL) {
        current = current->next;
        current_pos++;
    }

    // Se a posição for inválida (fora dos limites), a ação é ignorada
    if (current == NULL) {
        free(new_node); // Libera o nó que não será usado
        return;
    }

    new_node->next = current->next;
    current->next = new_node;
}

// Remove a primeira ocorrência de um nó com o dado especificado
void remove_node(LinkedList* list, int data) {
    if (list->head == NULL) return;

    if (list->head->data == data) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }

    Node* current = list->head;
    while (current->next != NULL) {
        if (current->next->data == data) {
            Node* temp = current->next;
            current->next = temp->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

// --- FUNÇÃO PRINCIPAL E LÓGICA DE EXECUÇÃO ---

int main() {
    clock_t start = clock(); // Inicia a medição de tempo

    // 1. LER O ARQUIVO DE ENTRADA
    FILE* file = fopen("arq-novo.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Erro: O arquivo 'arq-novo.txt' não foi encontrado.\n");
        return 1;
    }

    // Descobre o tamanho do arquivo para alocar um buffer
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* content = (char*)malloc(file_size + 1);
    fread(content, 1, file_size, file);
    content[file_size] = '\0';
    fclose(file);

    // 2. PARSE DO CONTEÚDO
    char* current_pos = content;
    char* line_end;
    char* last_numeric_line_end = NULL;
    int num_actions = 0;

    // Encontra a linha que contém o número de ações
    while ((line_end = strchr(current_pos, '\n')) != NULL) {
        *line_end = '\0'; // Temporariamente termina a string na quebra de linha
        
        char* temp = current_pos;
        bool is_numeric = true;
        while(*temp) {
            if(!isdigit(*temp) && !isspace(*temp)) {
                is_numeric = false;
                break;
            }
            temp++;
        }

        if (is_numeric && strlen(current_pos) > 0) {
            num_actions = atoi(current_pos);
            last_numeric_line_end = line_end;
        }

        *line_end = '\n'; // Restaura a quebra de linha
        current_pos = line_end + 1;
    }
    
    // Separa as strings
    *last_numeric_line_end = '\0';
    char* initial_list_str = content;
    char* actions_str = last_numeric_line_end + 1;

    // 3. CRIAÇÃO DA LISTA INICIAL
    LinkedList* list = create_linked_list();
    char* token = strtok(initial_list_str, " \n\r");
    Node* last_node = NULL;
    while (token != NULL) {
        Node* new_node = create_node(atoi(token));
        if (list->head == NULL) {
            list->head = new_node;
        } else {
            last_node->next = new_node;
        }
        last_node = new_node;
        token = strtok(NULL, " \n\r");
    }

    // 4. PROCESSAMENTO DAS AÇÕES
    char* action_ptr = actions_str;
    int actions_processed = 0;
    while (*action_ptr && actions_processed < num_actions) {
        // Pula espaços em branco
        while (*action_ptr && isspace(*action_ptr)) {
            action_ptr++;
        }
        if (!*action_ptr) break;

        char action_type = *action_ptr;
        action_ptr++;
        
        int arg1, arg2;
        switch (toupper(action_type)) {
            case 'A':
                if (sscanf(action_ptr, "%d %d", &arg1, &arg2) == 2) {
                    add_node(list, arg1, arg2);
                }
                break;
            case 'R':
                if (sscanf(action_ptr, "%d", &arg1) == 1) {
                    remove_node(list, arg1);
                }
                break;
            case 'P':
                // A impressão é comentada para não afetar o tempo de I/O na medição
                // print_list(list);
                break;
        }

        // Avança o ponteiro para o próximo comando
        while (*action_ptr && !isalpha(*action_ptr)) {
            action_ptr++;
        }
        actions_processed++;
    }

    // 5. FINALIZAÇÃO E MEDIÇÃO DE TEMPO
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tempo total de execução: %.4f segundos\n", time_spent);

    // 6. LIBERAÇÃO DE MEMÓRIA
    free(content);
    free_list(list);

    return 0;
}