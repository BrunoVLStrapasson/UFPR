public class Data{
    // Atributos
    private int dia;
    private int mes;
    private int ano;
    // Métodos get
    public int getDia(){
        return this.dia;
    }
    public int getMes(){
        return this.mes;
    }
    public int getAno(){
        return this.ano;
    }

    public void setDia(int dia){
    if(dia >=1 && dia <= 31)
        this.dia = dia;
    }
    public void setMes(int mes){
    if(mes >=1 && mes <= 12)
        this.mes = mes;
    }
    public void setAno(int ano){
    if(ano > 0)
        this.ano = ano;
    }
    
    //construtores
    public Data(){}
    
    public Data(int dia,int mes,int ano){
        this.setDia(dia);
        this.setMes(mes);
        this.setAno(ano);
    }
}