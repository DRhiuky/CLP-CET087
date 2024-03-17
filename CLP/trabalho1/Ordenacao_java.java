import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class Ordenacao_java {
    private int[][] vetores;
    private int numVetores;
    private int tamVetores;
    private String arquivoSaida;

    // Construtor da classe Ordenacao_java
    public Ordenacao_java(int numVetores, int tamVetores, String arquivoSaida) {
        this.numVetores = numVetores;
        this.tamVetores = tamVetores;
        this.arquivoSaida = arquivoSaida;
        this.vetores = new int[numVetores][tamVetores];
    }

    // Função para criar vetores aleatórios
    public void criaVetores() {
        Random rand = new Random();
        for (int i = 0; i < numVetores; i++) {
            for (int j = 0; j < tamVetores; j++) {
                vetores[i][j] = rand.nextInt(1000); // números inteiros aleatórios entre 0 e 999
            }
        }
    }

    // Função para ordenar vetor usando o algoritmo de ordenação por inserção
    public void insertionSort(int[] arr) {
        int n = arr.length;
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    // Função para embaralhar vetor
    public void embaralhaVetor(int[] arr) {
        Random rand = new Random();
        int n = arr.length;
        if (n > 1) {
            for (int i = n - 1; i > 0; i--) {
                int j = rand.nextInt(i + 1);
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Função principal
    public void executar() {
        criaVetores();

        try (FileWriter fw = new FileWriter(arquivoSaida)) {
            int x = numVetores; // Número de ciclos

            while (x > 0) {
                // Medir o tempo de execução
                long startTime = System.nanoTime();

                // Ordenar 1024 vetores e registrar o tempo de execução
                for (int i = 0; i < numVetores; i++) {
                    insertionSort(vetores[i]);
                }

                long endTime = System.nanoTime();
                double timeSpent = (endTime - startTime) / 1e9; // Convertendo para segundos

                // Escrever o tempo de processamento no arquivo
                fw.write(String.format("%.9f\n", timeSpent));

                x--; // Decrementa o número de ciclos

                // Re-embaralha os vetores para próximo ciclo
                for (int i = 0; i < numVetores; i++) {
                    embaralhaVetor(vetores[i]);
                }
            }
        } catch (IOException e) {
            System.out.println("Erro ao escrever no arquivo.");
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        int numVetores = 1024;
        int tamVetores = 100;
        String arquivoSaida = "tempos3_java.txt";

        Ordenacao_java Ordenacao_java = new Ordenacao_java(numVetores, tamVetores, arquivoSaida);
        Ordenacao_java.executar();
    }
}