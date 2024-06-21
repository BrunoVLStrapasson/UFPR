import java.util.Scanner;

public class PrincipalFuncoes{

    public static void main(String args[]){

        System.out.println("Entre com o valor de x:");
        
        Scanner input = new Scanner(System.in);
        
        int num ;
        int valor = 0;

        num = input.nextInt();

        if(num <= 5){
            valor = num;
        } else if(num> 5 && num<=10){
            valor = 2*num+1;
        }else{
            valor = num - 3;
        }
        
        System.out.println("f(x)= "+ valor);
    }

}
