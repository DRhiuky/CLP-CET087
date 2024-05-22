import java.util.Scanner;

public class Fatorial {

    // Função para calcular o fatorial de um número
    public static long fatorial(int n) {
        if (n == 0 || n == 1) {
            return 1;
        }
        long resultado = 1;
        for (int i = 2; i <= n; i++) {
            resultado *= i;
        }
        return resultado;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite um número para calcular seu fatorial: ");
        int n = scanner.nextInt();

        if (n < 0) {
            System.out.println("O fatorial não está definido para números negativos.");
        } else {
            long inicio = System.nanoTime();
            long resultado = fatorial(n);
            long fim = System.nanoTime();

            double tempoGasto = (fim - inicio) / 1e9;

            System.out.println("O fatorial de " + n + " é: " + resultado);
            System.out.println("Tempo gasto para calcular: " + tempoGasto + " segundos");
        }

        scanner.close();
    }
}
