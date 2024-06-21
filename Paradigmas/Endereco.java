public class Endereco{
    //atributos
    private String rua;
    private int numero;
    private String bairro;
    private String cidade;
    private String estado;

    //metodo get-set
    public int getNumero(){
        return this.numero;
    }

    public String getRua(){
        return this.rua;
    }

    public String getBairro(){
        return this.bairro;
    }

    public String getCidade(){
        return this.cidade;
    }

    public String getEstado(){
        return this.estado;
    }

    public void setNumero(int numero){
        if(numero > 0)
            this.numero=numero;
    }

    public void setRua(String rua){
        this.rua=rua;
    }

    public void setBairro(String bairro){
        this.bairro=bairro;
    }

    public void setCidade(String cidade){
        this.cidade=cidade;
    }

    public void setEstado(String estado){
        this.estado=estado;
    }

    //construtores
    public Endereco(){}

    public Endereco(int numero,String rua,String bairro,String cidade,String estado){
        this.setNumero(numero);
        this.setRua(rua);
        this.setBairro(bairro);
        this.setCidade(cidade);
        this.setEstado(estado);
    }




}