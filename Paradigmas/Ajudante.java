public class Ajudante extends Funcionario{
    private int tempo;

    public int getTempo(){
        return this.tempo;
    }
    public void setTempo(int tempo){
        this.tempo = tempo;
    }

    public Ajudante(){}

    public Ajudante(String nome, int registro, double salario, Data contratacao,int tempo){
        super(nome,registro,salario,contratacao);
        this.setTempo(tempo);
    }

    @Override
    public void exibirDados(){
        super.exibirDados();
        System.out.println("Dias do ajudante: "+ tempo);
    }
}