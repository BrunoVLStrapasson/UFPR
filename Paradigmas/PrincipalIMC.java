import java.util.Scanner;

public class PrincipalIMC{

    public static void main(String args[]){

        System.out.println("Entre com o valor diferente de -1.");
        
        Scanner input = new Scanner(System.in);
        
        int num,peso;
        int valor = 0;
        int cont = 0;

        num = input.nextInt();

        while(num != -1){

            peso = num;

            input = new Scanner(System.in);
            double altura = Double.parseDouble(input.next());

            if(peso/altura*altura >= 25){
                cont++;
            }

            input = new Scanner(System.in);
            num = input.nextInt();

        }
        
        System.out.println(valor +" Pessoas acima do peso.");

        input.close();
    }

}