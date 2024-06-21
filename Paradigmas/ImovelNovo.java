public class ImovelNovo extends Imovel{
    
    public ImovelNovo(double preco,Endereco endereco){
        super(preco,endereco);
    }

    @Override
    public double calcularValorImovel() {
        // Exemplo: Adicionar um valor adicional de 10% ao preço base para imóveis novos
        return preco * 1.10;
    }

}