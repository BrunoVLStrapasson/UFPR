public class Televisao extends ServicoEletronico implements TamanhoComparator{
    private int tam;

    public Televisao(int peso,String nome,String marca,int tam){
        super(peso,nome,marca);
        this.tam = tam;

    }

    /*@Override
    public void ligar(){
        System.out.println("ligando a Tv");
    }

    @Override
    public void desligar(){
        System.out.println("desligando a Tv");
    }*/

    public int getTam(){
        if (tam > 0)
            return this.tam;
        return 0;
    }

    public void setTam(int tam){
        this.tam = tam;
    }

    @Override
    public int compareTo(Televisao tv1, Televisao tv2) {
        return Integer.compare(tv2.getTam(), tv1.getTam());
    }

    public void vender(){
        System.out.println("Produto vendido. "+ nome);
    }

    public void acionarGarantia(){
        System.out.println("garantia acionada "+ nome);
    }

    @Override
    public String toString() {
        return "Televisao{" + "peso=" + getPeso() + ", nome='" + getNome() + '\'' + ", marca='" + getMarca() + '\'' + ", tam=" + getTam() + '}';
    }

}