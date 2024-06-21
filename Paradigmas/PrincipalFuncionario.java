public class PrincipalFuncionario{
        
    public static void main(String[ ] args){

        Funcionario Func;
        Data def;
        Ajudante tst;

        tst = new Ajudante();
        def = new Data();
        Func = new Funcionario();

        def.setDia(5);
        def.setMes(10);
        def.setAno(2000);

        Func.setContratacao(def);

        Func.setNome("Jair");
        Func.setRegistro(755);
        Func.setSalario(2500.53);
        
        tst.setTempo(31);
        tst.setNome("julin");
        tst.setRegistro(0);
        tst.setContratacao(def);
        tst.setSalario(1500.34);
        //vetObjetos[1] = new Funcionario("jonas", 2000, 7500);
        Func.exibirDados();

        tst.exibirDados();
        //vetObjetos[1].exibirDados();
    }   
}

