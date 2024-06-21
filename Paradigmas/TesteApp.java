import java.util.HashSet;

// Interface Loja
interface Loja {
    void vender();
    void acionarGarantia();
}

// Classe abstrata ProdutoEletronico
abstract class ProdutoEletronico implements Loja, Comparable<ProdutoEletronico> {
    private String modelo;
    private double preco;
    private String marca;

    // Construtores
    public ProdutoEletronico() {
        // Construtor padrão
    }

    public ProdutoEletronico(String modelo, double preco, String marca) {
        this.modelo = modelo;
        this.preco = preco;
        this.marca = marca;
    }

    // Método específico para produtos eletrônicos
    public void exibirDetalhes() {
        System.out.println("Produto Eletrônico - Modelo: " + modelo + ", Marca: " + marca + ", Preço: R$" + preco);
    }

    // Métodos da interface Loja
    public void vender() {
        System.out.println("Vendendo um produto eletrônico!");
    }

    public void acionarGarantia() {
        System.out.println("Acionando garantia de um produto eletrônico!");
    }

    // Método da interface Comparable
    @Override
    public int compareTo(ProdutoEletronico outroProduto) {
        return Double.compare(this.preco, outroProduto.preco);
    }

    // Métodos específicos para a classe ProdutoEletronico
    public abstract void ligar();

    public abstract void desligar();

    // Métodos getter e setter
    public String getModelo() {
        return modelo;
    }

    public void setModelo(String modelo) {
        this.modelo = modelo;
    }

    public double getPreco() {
        return preco;
    }

    public void setPreco(double preco) {
        this.preco = preco;
    }

    public String getMarca() {
        return marca;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }
}

// Subclasse concreta Televisao
class Televisao extends ProdutoEletronico {
    private int polegadas;

    // Construtor completo
    public Televisao(String modelo, double preco, String marca, int polegadas) {
        super(modelo, preco, marca);
        this.polegadas = polegadas;
    }

    // Método para exibir todos os dados do objeto
    public void exibirDados() {
        System.out.println("Televisão - Modelo: " + getModelo() + ", Marca: " + getMarca() +
                ", Preço: R$" + getPreco() + ", Polegadas: " + polegadas);
    }

    // Getter e Setter para o atributo específico
    public int getPolegadas() {
        return polegadas;
    }

    public void setPolegadas(int polegadas) {
        this.polegadas = polegadas;
    }

    // Implementação dos métodos da interface Loja
    @Override
    public void vender() {
        System.out.println("Vendendo uma televisão!");
    }

    @Override
    public void acionarGarantia() {
        System.out.println("Acionando garantia de uma televisão!");
    }

    // Implementação dos métodos específicos para a classe Televisao
    @Override
    public void ligar() {
        System.out.println("Ligando a televisão");
    }

    @Override
    public void desligar() {
        System.out.println("Desligando a televisão");
    }
}

// Classe principal
public class TesteApp {
    public static void main(String[] args) {
        // Criação de três instâncias de televisão
        Televisao tv1 = new Televisao("LG Electronics", 5000.00, "LG", 75);
        Televisao tv2 = new Televisao("Mondial", 1200.00, "Sony", 32);
        Televisao tv3 = new Televisao("Britânia", 2500.00, "Philco", 50);

        // Criação de uma HashSet<ProdutoEletronico>
        HashSet<ProdutoEletronico> eletronicosSet = new HashSet<>();

        // Adição dos objetos à coleção
        eletronicosSet.add(tv1);
        eletronicosSet.add(tv2);
        eletronicosSet.add(tv3);

        // Iteração pela coleção exibindo os dados de cada objeto
        for (ProdutoEletronico eletronico : eletronicosSet) {
            eletronico.exibirDetalhes();
            if (eletronico instanceof Televisao) {
                ((Televisao) eletronico).exibirDados();
            }
            eletronico.vender();
            eletronico.acionarGarantia();
            eletronico.ligar();
            eletronico.desligar();
            System.out.println("-------------");
        }
    }
}