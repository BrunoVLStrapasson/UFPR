public class PrincipalCarro{
    public static void main(String[] args){

    Carro objeto1 = new Carro();
    objeto1.setTipoComb('F');

    if(objeto1.getTipoComb() == 'F')
        System.out.println("Combustível: flex");
    else if(objeto1.getTipoComb() == 'D')
        System.out.println("Combustível: diesel");
    else
        System.out.println("Não especificado");
    }
}