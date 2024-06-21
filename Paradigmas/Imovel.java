public abstract class Imovel{
    protected Endereco endereco;
    protected double preco;
    
    //metodo get-set
    public double getPreco(){
        return this.preco;
    }

    public void setPreco(double preco){
        if(preco > 0)
            this.preco=preco;
    }

    public Endereco getEndereco(){
        return this.endereco;
    }

    public void setEndereco(Endereco endereco){
        this.endereco=endereco;
    }

    public Imovel(){}

    public Imovel(double preco,Endereco endereco){
        this.setPreco(preco);
        this.setEndereco(endereco);
    }

    public abstract double calcularValorImovel();

}