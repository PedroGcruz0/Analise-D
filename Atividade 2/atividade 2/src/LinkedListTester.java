import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class LinkedListTester {

    public static void main(String[] args) {
        long inicio = System.nanoTime(); // Inicia a medição de tempo

        String filename = "arq-novo.txt";
        try {
            String content = new String(Files.readAllBytes(Paths.get(filename)));
            
            // 1. Interpretar o arquivo
            String[] lines = content.split("\\r?\\n");
            int actionCountLineIndex = -1;
            for (int i = 0; i < lines.length; i++) {
                if (lines[i].trim().matches("\\d+")) {
                    actionCountLineIndex = i;
                    break;
                }
            }

            String initialListStr = String.join(" ", Arrays.copyOfRange(lines, 0, actionCountLineIndex));
            int numActions = Integer.parseInt(lines[actionCountLineIndex].trim());
            String actionsStr = String.join(" ", Arrays.copyOfRange(lines, actionCountLineIndex + 1, lines.length));
            
            // Separa os comandos usando uma expressão regular
            String[] commandsRaw = actionsStr.split("(?=[ARP])");
            List<String> actions = new ArrayList<>();
            for(String cmd : commandsRaw) {
                if (!cmd.trim().isEmpty()) {
                    actions.add(cmd.trim());
                }
            }
            
            // 2. Criar a lista encadeada
            int[] initialValues = Arrays.stream(initialListStr.split("\\s+"))
                                        .mapToInt(Integer::parseInt)
                                        .toArray();
            LinkedList linkedList = new LinkedList(initialValues);

            // 3. Processar os comandos
            for (int i = 0; i < actions.size() && i < numActions; i++) {
                String[] command = actions.get(i).split("\\s+");
                String actionType = command[0].toUpperCase();

                switch (actionType) {
                    case "A":
                        if (command.length == 3) {
                            linkedList.add(Integer.parseInt(command[1]), Integer.parseInt(command[2]));
                        }
                        break;
                    case "R":
                        if (command.length == 2) {
                            linkedList.remove(Integer.parseInt(command[1]));
                        }
                        break;
                    case "P":
                        // linkedList.printList(); // Comentado para não afetar o tempo de I/O na medição
                        break;
                }
            }

        } catch (IOException e) {
            System.err.println("Erro ao ler o arquivo: " + filename);
            e.printStackTrace();
        } catch (Exception e) {
            System.err.println("Ocorreu um erro inesperado.");
            e.printStackTrace();
        }

        long fim = System.nanoTime(); // Finaliza a medição de tempo
        double tempoTotal = (fim - inicio) / 1_000_000_000.0;
        System.out.printf("Tempo total de execução: %.4f segundos%n", tempoTotal);
    }
}