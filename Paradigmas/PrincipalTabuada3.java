import java.util.Scanner;

public class PrincipalTabuada3{

    public static void main(String args[]){

        int num = 3;
        int soma = 0;

        for(int i=0;i<=10;i++){
            soma+=i*num;
        }
        
        System.out.println("O valor calculado foi: "+ soma);
    }

}