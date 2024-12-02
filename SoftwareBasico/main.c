#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#include "memalloc.h"

int main() {

    void* m1, * m2;

    iniciaAlocador();

    imprimeMapa(); //memoria vazia, nao imprime nada

    m1 = (void*) alocaMem(25);
    imprimeMapa();
    
    liberaMem(m1);   
    imprimeMapa();
    
    m2 = (void*) alocaMem(10);
    imprimeMapa();
    
    liberaMem(m2);
    imprimeMapa();

    m2 = (void*) alocaMem(5);//acha o melhor espaço disponivel, e o usa   
    imprimeMapa();

    liberaMem(m2);
    imprimeMapa();
    //aloca novo bloco
    m2 = (void*) alocaMem(150);
    imprimeMapa();

    m1 = (void*) alocaMem(20);//usa o melhor espaço disponivel
    imprimeMapa();
    

    finalizaAlocador();
    //memoria vazia, nao imprime nada
    imprimeMapa();

}
