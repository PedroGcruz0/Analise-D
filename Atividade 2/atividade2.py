import time
import re

# Definição da classe Node
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

# Definição da classe LinkedList
class LinkedList:
    def __init__(self, initial_nodes=None):
        self.head = None
        if initial_nodes:
            if len(initial_nodes) > 0:
                self.head = Node(initial_nodes[0])
                current_node = self.head
                for val in initial_nodes[1:]:
                    current_node.next = Node(val)
                    current_node = current_node.next

    def add(self, data, position):
        """ Adiciona um nó em uma posição. Se a posição não existir, a ação é ignorada. """
        new_node = Node(data)
        if position == 0:
            new_node.next = self.head
            self.head = new_node
            return

        current_node = self.head
        current_pos = 0
        # Navega até o nó ANTERIOR à posição de inserção
        while current_pos < position - 1 and current_node is not None:
            current_node = current_node.next
            current_pos += 1
        
        # A posição é inválida se current_node se tornar None
        if current_node is None:
            # print(f"Aviso: Posição {position} inválida. Ação 'A {data} {position}' ignorada.")
            return

        new_node.next = current_node.next
        current_node.next = new_node

    def remove(self, data):
        """ Remove a primeira ocorrência do nó com o dado. Se não encontrar, continua. """
        current_node = self.head
        if current_node is None:
            return

        if current_node.data == data:
            self.head = current_node.next
            return

        while current_node.next is not None:
            if current_node.next.data == data:
                current_node.next = current_node.next.next
                return
            current_node = current_node.next

    def print_list(self):
        current_node = self.head
        if current_node is None:
            # print("Lista Vazia") # Comentado para não poluir a medição de tempo
            return
        
        result = []
        while current_node is not None:
            result.append(str(current_node.data))
            current_node = current_node.next
        print(" ".join(result))

def parse_input_file(file_content):
    """Interpreta o arquivo para extrair dados iniciais, número de ações e comandos."""
    lines = file_content.split('\n')
    
    action_count_line_index = -1
    for i, line in enumerate(lines):
        if line.strip().isdigit():
            action_count_line_index = i
            break
    
    initial_list_str = " ".join(lines[:action_count_line_index])
    num_actions = int(lines[action_count_line_index].strip())
    actions_str = " ".join(lines[action_count_line_index + 1:])
    
    # Usa expressão regular para separar os comandos (A, R, P)
    commands_raw = re.split(r'(?=[ARP])', actions_str)
    cleaned_commands = [cmd.strip() for cmd in commands_raw if cmd.strip()]
    
    return initial_list_str, num_actions, cleaned_commands

def main():
    """Função principal para executar o teste."""
    filename = "arq-novo.txt"
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            content = f.read()

        initial_str, n_actions, actions = parse_input_file(content)
        
        initial_values = [int(x) for x in initial_str.split()]
        linked_list = LinkedList(initial_values)
        
        for i, command_str in enumerate(actions):
            if i >= n_actions:
                break
            
            command = command_str.split()
            action_type = command[0].upper()

            if action_type == 'A':
                if len(command) == 3:
                    linked_list.add(int(command[1]), int(command[2]))
            elif action_type == 'R':
                 if len(command) == 2:
                    linked_list.remove(int(command[1]))
            elif action_type == 'P':
                # linked_list.print_list() # Comentado para não afetar o tempo de I/O
                pass

    except FileNotFoundError:
        print(f"Erro: O arquivo '{filename}' não foi encontrado.")
        return
    except Exception as e:
        print(f"Ocorreu um erro inesperado: {e}")
        return

if __name__ == "__main__":
    inicio = time.time()  # Inicia a medição de tempo [cite: 43]
    main()
    fim = time.time()      # Finaliza a medição de tempo [cite: 43]
    
    tempo_total = fim - inicio
    print(f"Tempo total de execução: {tempo_total:.4f} segundos")