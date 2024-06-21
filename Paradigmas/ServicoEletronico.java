public abstract class ServicoEletronico implements Loja{
    protected int peso;
    protected String nome;
    protected String marca;

    public ServicoEletronico(){}
    
    public ServicoEletronico(int peso,String nome,String marca){
        this.setPeso(peso);
        this.setNome(nome);
        this.setMarca(marca);
    }

    public void setPeso(int peso){
        this.peso = peso;
    }

    public int getPeso(){
        if(peso > 0)
            return this.peso;
        return 0;
    }

    public String getNome(){
        return nome;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public String getMarca(){
        return this.marca;
    }

    public void setMarca(String marca){
        this.marca = marca;
    }
    
    public void ligar(char tipo){
        if(tipo == 't')
            System.out.println("ligando a Tv");
        System.out.println("ligando o celular");
    }

    public void desligar(char tipo){
        if(tipo == 't')
            System.out.println("desligando a Tv");
        System.out.println("desligando o celular");
    }
     
}