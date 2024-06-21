import java.util.ArrayList;
import java.util.Scanner;

public class PrincipalImovel{
    public static void main(String args[]){

        Scanner scanner = new Scanner(System.in);
        ArrayList<Imovel> imoveis = new ArrayList<Imovel>();

        // Inserindo instâncias alternadas de ImovelNovo e ImovelVelho
        for (int i = 0; i < 2; i++) {
            System.out.println("Informe a rua do imóvel " + (i + 1) + ":");
            String rua = scanner.next();
            System.out.println("Informe o número do imóvel " + (i + 1) + ":");
            int numero = scanner.nextInt();
            System.out.println("Informe o bairro do imóvel " + (i + 1) + ":");
            String bairro = scanner.next();
            System.out.println("Informe a cidade do imóvel " + (i + 1) + ":");
            String cidade = scanner.next();
            System.out.println("Informe o estado do imóvel " + (i + 1) + ":");
            String estado = scanner.next();
            System.out.println("Informe o preço do imóvel " + (i + 1) + ":");
            double preco = scanner.nextDouble();

            Endereco endereco = new Endereco(numero ,rua , bairro, cidade, estado);

            if (i % 2 == 0) {
                imoveis.add(new ImovelNovo(preco,endereco));
            } else {
                imoveis.add(new ImovelVelho(preco,endereco));
            }
        }

        // Exibindo o valor de cada imóvel
        for (int i = 0; i < imoveis.size(); i++) {
            System.out.println("O valor do imóvel " + (i + 1) + " localizado em " + imoveis.get(i).endereco.toString() + " é: R$ " + imoveis.get(i).calcularValorImovel());
        }

        scanner.close();



    }
}