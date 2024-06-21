public class ImovelVelho extends Imovel{
    
    public ImovelVelho(double preco,Endereco endereco){
        super(preco,endereco);
    }

    @Override
    public double calcularValorImovel() {
        // Exemplo: Reduzir 15% do preço base para imóveis velhos
        return preco * 0.85;
    }
}