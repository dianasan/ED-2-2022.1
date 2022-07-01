#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "arrays.h"


int tam_res = 7;

void imprimePart(int tot_parts);
int* encontraMenorCodMen(Cliente **vetor_men);
//As funções estão abaixo do main.

void main() {

    char nome_arq[40];
    FILE *entrada;
    FILE *res;

    printf("Insira o nome do arquivo que será particionado: ");
    scanf("%s",nome_arq);

    entrada = fopen(nome_arq, "r+b");//abre o arquivo para leitura sem apagar o conteúdo.

    if (entrada == NULL)
    {
        printf("Não foi possível abrir o arquivo!\n");
        exit(1);
    }

    res = fopen("reservatorio.dat", "w+b");

    if(res == NULL){
        printf("Erro na criação do reservatório!\n");
         exit(1);
    }

 
    Cliente **vetor_men = (Cliente **) malloc(sizeof(Cliente)*tam_mem);
    Cliente *cli_temp = (Cliente *) malloc(sizeof(Cliente));

    

    //Gerando o vetor de memória
    for(int i = 0; i < tam_mem; i++)
    {
        vetor_men[i] = lerCliente(entrada);
    }

    int fim_arq = feof(entrada);
    int num_particao = 1;
    int res_total = 0;
    int part_total = 0;

    while(!fim_arq || res_total != 0) //verifica se o arquivo chegou ao fim ou se não há mais nada no reservatório
    {
        if(!verificaVazio(vetor_men))//se o vetor da meória não for vazio
        {
            int *menor_cod_mem = encontraMenorCodMen(vetor_men);
            char destino[15];
            FILE* particao_final;
            snprintf(destino, 15, "Part_%d.dat", num_particao);
            if(part_total == 0)
                particao_final = fopen(destino, "w+b");
            else
                particao_final = fopen(destino, "a+b");
            
            salvarCliente(vetor_men[*menor_cod_mem], particao_final); //Salva o código do cliente.
            fclose(particao_final); //Libera a partição. 

            part_total++;

            if(!fim_arq) //Caso o arquivo ainda não tenha chegado ao fim
            {
                if(res_total < tam_res)
                {
                    cli_temp = lerCliente(entrada);
                    while(cli_temp != NULL && cli_temp ->cod < vetor_men[*menor_cod_mem]->cod && res_total < tam_res)
                    //Verifica a capacidade do reservatório, bem como se o código do cliente é menor e válido.
                    {
                        salvarCliente(cli_temp, res);
						res_total++;
                        if(res_total < tam_res)
                        {
                            cli_temp = lerCliente(entrada);
                            fim_arq - feof(entrada);
						}
						else
                        {
                            cli_temp = NULL;
                        }
                    }
                    vetor_men[*menor_cod_mem] = cli_temp;
                }
                else
                {
                    vetor_men[*menor_cod_mem] = NULL;
                }

            	fim_arq = feof(entrada);
            }
            else 
            {
                vetor_men[*menor_cod_mem] = NULL;
            }
            free(menor_cod_mem);
        }
        else
        {
            num_particao++;
			rewind(res);

            for(int i = 0; i < res_total; i++)
            {
                vetor_men[i] = lerCliente(res);
            }

            res_total = 0;
            part_total = 0;
            rewind(res);
        }
    }

    if(!verificaVazio(vetor_men))
    {
    	while(!verificaVazio(vetor_men))
    	{
            int *menor_cod_mem = encontraMenorCodMen(vetor_men);
            char destino[15];
            FILE* particao_final;
            snprintf(destino, 15, "Part_%d.dat", num_particao);
            if(part_total == 0)
                particao_final = fopen(destino, "w+b");
            else
                particao_final = fopen(destino, "a+b");
            
            salvarCliente(vetor_men[*menor_cod_mem], particao_final); //Salva o codigo
            fclose(particao_final); //Libera part destino 

            part_total++;
            vetor_men[*menor_cod_mem] = NULL;
            free(menor_cod_mem);
    	}

    }
    fclose(entrada);
    fclose(res);
    imprimePart(num_particao);
    free(vetor_men);
}

void imprimePart(int tot_parts) {
	FILE *part;
	Cliente* clint;

	int cont = 1;
	int num_cli = 0;
	char destino[15];

	while(cont <= tot_parts)
    {
		snprintf(destino, 15, "Part_%d.dat", cont);
		printf("\n Partição Nº %d \n", cont);
        part = fopen(destino, "a+b");
        num_cli = 0;

        printf("| ");
        while(!feof(part)) {
        	clint = lerCliente(part);
             
        	if(clint != NULL)
            {
                printf("%d | ", clint->cod);

                num_cli++;
            }
		}
		printf("\n");
		printf("Quantidade de clientes na partição: %d \n", num_cli);
        cont++;
        fclose(part);
	}
	free(clint);
}

int* encontraMenorCodMen(Cliente **vetor_men){
    int* menor_cod_mem = NULL;
    for(int i = 0; i < tam_mem; i++) //Pega o menor codigo do array
    {
            if(vetor_men[i] != NULL)
            {
                if(menor_cod_mem == NULL)
                {
                    menor_cod_mem = (int *) malloc(sizeof(int));
                    *menor_cod_mem = i;
                }
                else if(vetor_men[i]->cod < vetor_men[*menor_cod_mem]->cod)
                {
                    *menor_cod_mem = i;
                }
            }
    }
    return menor_cod_mem;
}
