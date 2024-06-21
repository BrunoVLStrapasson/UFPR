public class Celular extends ServicoEletronico{

    public Celular(int peso,String nome,String marca){
        super(peso,nome,marca);
    }

    /*@Override
    public void ligar(){
        System.out.println("ligando o celular");
    }

    @Override
    public void desligar(){
        System.out.println("desligando o celular");
    }*/

    public void Atualizar(){
        System.out.println("atualizando o android");
    }

    public void vender(){
        System.out.println("Produto vendido. "+ nome);
    }

    public void acionarGarantia(){
        System.out.println("garantia acionada para "+ nome);
    }
}