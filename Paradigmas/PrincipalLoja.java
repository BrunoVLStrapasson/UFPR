import java.util.ArrayList;
import java.util.HashSet;
import java.util.TreeSet;
import java.util.*;

public class PrincipalLoja{

    public static void main(String args[]){

        //cria objetos
        Loja servico = new Servico('R',10);
        Loja televisao = new Televisao(10,"Tv42","semp",42);
        Loja celular = new Celular(1,"G10","Motorola");

        Loja tv1 = new Televisao(30,"LGeletronics","LG",75);
        Loja tv2 = new Televisao(4,"Mondial","Sony",32);
        Loja tv3 = new Televisao(16,"Britania","Philco",50);

        //cria hashset
        HashSet<Loja> televisoes = new HashSet<Loja>();
        televisoes.add(tv1);
        televisoes.add(tv2);
        televisoes.add(tv3);

        for(Loja tvs : televisoes){
            System.out.println(tvs);
        }

        /*TreeSet<ServicoEletronico> tree = new TreeSet<>();
        tree.add((ServicoEletronico)tv1);
        tree.add((ServicoEletronico)tv2);
        tree.add((ServicoEletronico)tv3);
        

        for (ServicoEletronico tv : tree) {
            System.out.println(tv);
        }
        */

        //cria array list e insere os elementos
        ArrayList<Loja> lojas = new ArrayList<Loja>();
        lojas.add(servico);
        lojas.add(televisao);
        lojas.add(celular);
        
        for(Loja loja : lojas){
            loja.vender();
            loja.acionarGarantia();
            if(loja instanceof Televisao){
                ((ServicoEletronico)loja).ligar('t');
                ((ServicoEletronico)loja).desligar('t');
            }
            if(loja instanceof Celular){
                ((ServicoEletronico)loja).ligar('c');
                ((ServicoEletronico)loja).desligar('c');

            }
            System.out.println("----------");
        }
    }
}