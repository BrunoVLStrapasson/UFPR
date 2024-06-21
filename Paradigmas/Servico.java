public class Servico implements Loja{
    private char tipo;
    private int duracao;

    public Servico(char tipo,int duracao){
        this.setTipo(tipo);
        this.setDuracao(duracao);
    }

    public char getTipo(){
        if(tipo == 'R' || tipo == 'L' || tipo == 'D')
            return this.tipo;
        return ' ';
    }

    public void setTipo(char tipo){
        this.tipo = tipo;
    }

    public int getDuracao(){
        return this.duracao;
    }

    public void setDuracao(int duracao){
        this.duracao = duracao;
    }

    public void vender(){
        System.out.println("Servico vendido."+ tipo);
    }

    public void acionarGarantia(){
        System.out.println("garantia acionada");
    }
}