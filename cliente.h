#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct cliente {
    int cod;
    char nome[50];
    char data_nascimento[11];
} Cliente;

void salvarCliente(Cliente* cliente, FILE *entrada)
{
    fwrite(&cliente->cod, sizeof(int), 1, entrada);
    fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), entrada);
    fwrite(cliente->data_nascimento, sizeof(char), sizeof(cliente->data_nascimento), entrada);
}

Cliente *lerCliente(FILE *entrada)
{
    Cliente *cli_temp = (Cliente *) malloc(sizeof(Cliente));
    if(0 >= fread(&cli_temp->cod, sizeof(int), 1, entrada))
    {
        return NULL;
    }
    else
    {
        fread(cli_temp->nome, sizeof(char), sizeof(cli_temp->nome), entrada);
        fread(cli_temp->data_nascimento, sizeof(char), sizeof(cli_temp->data_nascimento), entrada);
    }
    return cli_temp;
}



#endif