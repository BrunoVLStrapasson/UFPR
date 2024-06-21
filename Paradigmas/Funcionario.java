public class Funcionario{
    // Atributos
    protected String nome;
    protected int registro;
    protected double salario;
    protected Data contratacao;

    // Métodos get/set
    public String getNome(){
        return this.nome;
    }
    public void setNome(String nome){
        this.nome = nome;
    }

    public int getRegistro(){
        return this.registro;
    }
    public void setRegistro(int registro){
        this.registro = registro;
    }

    public double getSalario(){
        return this.salario;
    }
    public void setSalario(double salario){
        this.salario = salario;
    }

    public Data getContratacao(){
        return this.contratacao;
    }
    public void setContratacao(Data contratacao){
        this.contratacao = contratacao;
    }


    public Funcionario(){}

    // esse eh um construtor
    public Funcionario(String nome, int registro, double salario, Data contratacao){
        this.setNome(nome);
        this.setRegistro(registro);
        this.setSalario(salario);
        this.setContratacao(contratacao);
    }
    
    public void cadastrar(String nome,int registro, double salario,Data contratacao) 
    {
        this.nome = nome;
        this.registro = registro;
        this.salario = salario;
        this.contratacao = contratacao;
    }

    public void exibirDados()
    {
        System.out.println("Nome: " + this.nome);
        System.out.println("Ano: " + this.registro);
        System.out.println("Salario: "+ this.salario);
        System.out.printf("Data de contratacao: %d / %d / %d \n", this.contratacao.getDia(), this.contratacao.getMes(), this.contratacao.getAno());
        
    }
}




