import java.util.Scanner;

public class PrincipalVerificaParidade{

    public static void main(String args[]){

        Scanner input = new Scanner(System.in);

        int num;
        System.out.println("digite um inteiro: ");

        num = input.nextInt();

        if(num % 2 == 0){
            System.out.println("O valor digitado eh par.");
        }else{
            System.out.println("O valor digitado eh impar.");
        }


    }
}