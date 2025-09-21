import re #importa a biblioteca de expressões regulares para ajudar a separar os comandos

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

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
        new_node = Node(data)
        if position == 0:
            new_node.next = self.head
            self.head = new_node
            return
        current_node = self.head
        current_pos = 0
        while current_pos < position - 1 and current_node is not None:
            current_node = current_node.next
            current_pos += 1
        if current_node is not None:
            new_node.next = current_node.next
            current_node.next = new_node
        else:
            print(f"Aviso: Posição {position} está fora do alcance. Ação ignorada.")

    def remove(self, data):
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
            print("Lista Vazia")
            return
        result = []
        while current_node is not None:
            result.append(str(current_node.data))
            current_node = current_node.next
        print(" ".join(result))

#processar os comandos
def process_commands(linked_list, num_actions, actions_list):
   
    print("Lista Inicial:")
    linked_list.print_list()
    print("-" * 20)

    #processa cada ação
    for i, command_str in enumerate(actions_list):
        if i >= num_actions:
            print(f" Atingido o número de ações ({num_actions}). Ignorando o resto.")
            break
            
        command = command_str.split()
        action_type = command[0].upper()
        
        print(f"Ação {i+1}/{num_actions}: {command_str}")

        if action_type == 'A':
            try:
                numero = int(command[1])
                posicao = int(command[2])
                linked_list.add(numero, posicao)
            except (IndexError, ValueError):
                print(f"Erro: Comando 'A' mal formatado: {command_str}")
        elif action_type == 'R':
            try:
                numero = int(command[1])
                linked_list.remove(numero)
            except (IndexError, ValueError):
                print(f" comando 'R' mal formatado: {command_str}")
        elif action_type == 'P':
            linked_list.print_list()
        else:
            print(f"Ação desconhecida: {action_type}")
        
        if action_type != 'P':
            print("Estado da Lista:", end=" ")
            linked_list.print_list()
        
        print("-" * 20)

#ler e interpretar o arquivo
def parse_input_file(file_content):
    
    lines = file_content.split('\n')
    
    #encontra a linha que contém o número de ações
    action_count_line_index = -1
    for i, line in enumerate(lines):
        if line.strip().isdigit():
            action_count_line_index = i
            break
    
    if action_count_line_index == -1:
        full_text = "".join(lines).replace("\n", " ")
        # Separa os comandos (A, R, P) usando expressão regular
        parts = re.split(r'\s*([ARP])\s*', full_text)
        initial_list_str = parts[0]
        # Remonta os comandos
        commands_raw = [parts[i] + parts[i+1] for i in range(1, len(parts)-1, 2)]
        num_actions = len(commands_raw) # O número de ações é o total encontrado

    else:
        initial_list_str = " ".join(lines[:action_count_line_index])
        num_actions = int(lines[action_count_line_index].strip())
        actions_str = " ".join(lines[action_count_line_index + 1:])
        
        #usa para separar os comandos concatenados
        actions_parts = re.split('(A |R |P)', actions_str)
        commands_raw = []
        for i in range(1, len(actions_parts), 2):
            command = actions_parts[i] + actions_parts[i+1]
            commands_raw.append(command.strip())
            
    #limpa a lista de comandos
    cleaned_commands = [cmd.strip() for cmd in commands_raw if cmd.strip()]
    
    return initial_list_str, num_actions, cleaned_commands

if __name__ == "__main__":
    filename = input("digite o nome do arquivo de entrada")
    
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            content = f.read()

        # interpreta o arquivo
        initial_str, n_actions, actions = parse_input_file(content)
        
        # cria a lista encadeada inicial
        initial_values = [int(x) for x in initial_str.split()]
        ll = LinkedList(initial_values)
        
        # processa os comandos
        process_commands(ll, n_actions, actions)

    except FileNotFoundError:
        print(f"Erro: O arquivo '{filename}' não foi encontrado.")
    except Exception as e:
        print(f"Ocorreu um erro inesperado: {e}")