public class Carro{
    // Atributos
    private char tipoComb;
    // Método get
    public char getTipoComb(){
        return this.tipoComb;
    }

    // Método set
    public void setTipoComb(char tipoComb){
        if(tipoComb =='F'|| tipoComb =='D')
            this.tipoComb = tipoComb;
    }

    public Carro(){}
}