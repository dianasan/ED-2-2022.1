#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

int tam_mem = 7;

int verificaVazio(Cliente **vetor_clientes){
    int vazio = 1;
    for(int i = 0; i < tam_mem; i++)
    {
        if(vetor_clientes[i] != NULL)
            vazio = 0;
    }
    return vazio;
}


#endif