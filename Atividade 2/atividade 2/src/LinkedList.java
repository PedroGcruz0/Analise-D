public class LinkedList {
    Node head;

    /**
     * Construtor para iniciar a lista com um array de valores.
     * @param initialValues Um array de inteiros para popular a lista.
     */
    public LinkedList(int[] initialValues) {
        if (initialValues == null || initialValues.length == 0) {
            this.head = null;
            return;
        }
        this.head = new Node(initialValues[0]);
        Node currentNode = this.head;
        for (int i = 1; i < initialValues.length; i++) {
            currentNode.next = new Node(initialValues[i]);
            currentNode = currentNode.next;
        }
    }

    /**
     * Adiciona um nó com 'data' em uma 'position' específica.
     * Se a posição não existir, a ação é ignorada.
     */
    public void add(int data, int position) {
        Node newNode = new Node(data);
        if (position == 0) {
            newNode.next = this.head;
            this.head = newNode;
            return;
        }

        Node currentNode = this.head;
        int currentPos = 0;
        // Navega até o nó ANTERIOR à posição de inserção
        while (currentPos < position - 1 && currentNode != null) {
            currentNode = currentNode.next;
            currentPos++;
        }
        
        // Se currentNode se tornou nulo, a posição era inalcançável.
        if (currentNode == null) {
            return;
        }

        newNode.next = currentNode.next;
        currentNode.next = newNode;
    }

    /**
     * Remove a primeira ocorrência do nó que contém 'data'.
     * Se o valor não for encontrado, nada acontece.
     */
    public void remove(int data) {
        if (this.head == null) {
            return;
        }

        if (this.head.data == data) {
            this.head = this.head.next;
            return;
        }

        Node currentNode = this.head;
        while (currentNode.next != null) {
            if (currentNode.next.data == data) {
                currentNode.next = currentNode.next.next;
                return; // Para após remover o primeiro encontrado
            }
            currentNode = currentNode.next;
        }
    }

    /**
     * Imprime todos os valores da lista em sequência.
     */
    public void printList() {
        if (this.head == null) {
            // System.out.println("Lista Vazia");
            return;
        }
        StringBuilder sb = new StringBuilder();
        Node currentNode = this.head;
        while (currentNode != null) {
            sb.append(currentNode.data).append(" ");
            currentNode = currentNode.next;
        }
        System.out.println(sb.toString().trim());
    }
}