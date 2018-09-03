#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "declaracoes.h"
#include "funcoesAuxiliares.h"
#include "exame.h"

tipoAgendamento *adicionarNovoAgendamento(tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos)
{
    tipoAgendamento *pAuxiliar = NULL;
    pAuxiliar = pAgend;

    pAgend = realloc(pAgend, (*quantAgendamentos+1)*sizeof(tipoAgendamento));
    if (pAgend == NULL)
    {
        printf("Erro ao reservar memoria.");
        pAgend = pAuxiliar;
    }
    else
    {
        int posicao, numeroContribuinte, numAgendamento;

        numeroContribuinte = lerInteiro("\nNumero de contribuinte: ", CONTRIBUITE_MIN, CONTRIBUITE_MAX);
        posicao = procurarCliente(vetorClientes, *quantClientes, numeroContribuinte);

         if (posicao == -1)
            {
                printf("\n\nATENCAO: o nr. contribuinte inserido nao existe.\n");
            }
            else
            {
                escreverCliente(vetorClientes[posicao]);
                pAgend[*quantAgendamentos].codigo = *quantAgendamentos; //Número único do agendamento
                pAgend[*quantAgendamentos].numContribuinteCliente.numContribuinte = numeroContribuinte;

                pAgend[*quantAgendamentos].dataVisita = lerData();
                pAgend[*quantAgendamentos].horaVisita = lerHorario();

                /* Fazer validação para verificar se não existem agendamentos para a mesma data e hora */
                /* Ideia - criar uma funcao do tipo procurarAgendamento e verificar se já existe algum agendamento com essa data/hora
                e por fim chamar essa função aqui à cabeça */



                lerString("Insira a descricao do problema: ", pAgend[*quantAgendamentos].descricaoProblema, TEXTO_LONGO);
                //pAgend[*quantAgendamentos].custoReparacao = lerFloat("Insira o valor da reparacao ou visita: ", 0.0, 99999999.99); // Retirar daqui e colocar no registarVisita
                //pAgend[*quantAgendamentos].grauSatisfacao = lerInteiro("Insira o grau de satisfacao do cliente: ", 1, 3); // Retirar daqui e colocar no registarVisita
                // Nao precisas incrementar -> pAgend[*quantAgendamentos].codigo++; //Incrementa o codigo unico de agendamento
                (*quantAgendamentos)++;


                //RUI
                printf("Valor quantAgendamentos=%d || endereco = %d", *quantAgendamentos, quantAgendamentos);
            }
    }
    return pAgend;
}

/* esta próxima função serve para listar todas os agendamentos com os clientes (vetor dinamico - Chamar no menu clientes)*/

void listarClientesComAgendamentos (tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos)
{
    int i = 0;

    if (quantAgendamentos > 0)
    {
        printf("\n\n*********** LISTAGEM dos Agendamentos ***********\n\n");
        for (i = 0; i < quantAgendamentos; i++)
        {
            // Mostra os detalhes do cliente na listagem para o qual realizámos um agendamento
            escreverCliente(vetorClientes[i]);

            printf("\n\nDados do Agendamento\n\n");

            printf("codigo: %d\n", pAgend[i].codigo+1); //O user verá sempre um valor acima (array começa a 0, user vê 1...)
            printf("\n");
            printf("data: %d/%d/%d\n", pAgend[i].dataVisita);
            printf("hora: %d\:%dH\n", pAgend[i].horaVisita);
            printf("descricao problema: %s\n", pAgend[i].descricaoProblema);

            // Custo e grau de satisfação são mostrados com o valor 0 enquanto não houver alteração de custo/grau de satisfação.
            printf("custo: %.2f euros\n", pAgend[i].custoReparacao);
            printf("grau de satisfacao: %d\n", pAgend[i].grauSatisfacao);

            printf("\n");
            printf("-------------------");
            printf("\n");
        }
    }
    else
    {
        printf("\n\nATENCAO: Nao existem agendamentos inseridos.\n\n");
    }
}


//tipoAgendamento *registarAgendamento <- OLD
//RUI alterar para void? <- OLD
void registarAgendamento(tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos, int *quantAgendamentosRegistados)
{

    int codigoUnico, posicao;

    codigoUnico = lerInteiro("Insira o codigo unico do Agendamento a procurar: ", 1, 9999999);
    codigoUnico--; // Para igualar o que o User vê ao código verdadeiro.

    posicao = procurarAgendamento(pAgend, vetorClientes, *quantClientes, *quantAgendamentos, codigoUnico);

    //RUI
    printf("\n#RUI# Posicao obtida: %d\n", posicao);

    if (posicao > -1) // Se encontrar a posicao permite adicinar custo e grau de satisfacao
        {
            pAgend[posicao].custoReparacao = lerFloat("Insira o valor da reparacao ou visita: ", 0.0, 99999999.99);
            pAgend[posicao].grauSatisfacao = lerInteiro("Insira o grau de satisfacao do cliente: ", 1, 3);

            // Incrementar o total de Agendamentos Registados
            (*quantAgendamentosRegistados)++;
        }
    else
        {
            printf("\n\nATENCAO: o Agendamento que pretende registar nao existe.\n");
        }
}

void listarAgendamentosPorData (tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos)
{
    int i = 0;
    int posicao;
    tipoData dataSearch;

    if (quantAgendamentos > 0)
    {
        dataSearch = lerData();
        posicao = procurarAgendamentoPorData(pAgend, vetorClientes, quantClientes, quantAgendamentos, dataSearch);
        if (posicao > -1)
        {
            printf("\n\n*********** LISTAGEM dos Agendamentos ***********\n\n");
            for (i = 0; i < quantAgendamentos; i++)
            {
                // Mostra os detalhes do cliente na listagem para o qual realizámos um agendamento
                escreverCliente(vetorClientes[i]);

                printf("\n\nDados do Agendamento\n\n");

                printf("codigo: %d\n", pAgend[i].codigo+1); //O user verá sempre um valor acima (array começa a 0, user vê 1...)
                printf("\n");
                printf("data: %d/%d/%d\n", pAgend[i].dataVisita);
                printf("hora: %d\:%dH\n", pAgend[i].horaVisita);
                printf("descricao problema: %s\n", pAgend[i].descricaoProblema);

                // Custo e grau de satisfação são mostrados com o valor 0 enquanto não houver alteração de custo/grau de satisfação.
                printf("custo: %.2f euros\n", pAgend[i].custoReparacao);
                printf("grau de satisfacao: %d\n", pAgend[i].grauSatisfacao);

                printf("\n");
                printf("-------------------");
                printf("\n");

            }
            printf("\n\n Total de Agendamentos para a data indicada: %d", quantAgendamentos);
        }
        else
        {
            printf("\n\nATENCAO: o Agendamento que pretende procurar nao existe.\n");
        }
    }
    else
    {
        printf("\n\nATENCAO: Nao existem agendamentos inseridos.\n\n");
    }
}

/*-------------------------------- FUNÇÕES ESTATÍSTICAS --------------------------------------- */

// TESTES - Ainda não funciona correctamente.

void listarClientesComMaisAgendamentosReg (tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos, int *quantAgendamentosRegistados)
{
    int mais;
    int i;

    if (quantAgendamentos == 0)
    {
        printf("\n Nao existem agendamentos inseridos!");
    }
    else
    {
        mais = vetorClientes[0].numContribuinte;
        for (i = 1; i < quantAgendamentos; i++)
        {
            if (vetorClientes[i].numContribuinte > mais)
            {
                mais = vetorClientes[i].numContribuinte;
            }
        }
        printf("\n Clientes com mais agendamentos registados: %d\n", mais);
        for(i = 0; i < quantAgendamentos; i++)
        {
            if (vetorClientes[i].numContribuinte == mais)
            {
                escreverCliente(vetorClientes[i]);
            }
        }
    }
}


/* ------------------------------- FUNÇÕES AUXILIARES DE PROCURAR ----------------------------- */


int procurarAgendamento(tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos, int codigoUnico)
{
    int posicao = -1;
    int i = 0;

    for (i = 0; i < quantAgendamentos; i++)
    {
       if (pAgend[i].codigo == codigoUnico)
       {
           posicao = i;
           i = quantAgendamentos;
       }
    }
    return posicao;
}



int procurarAgendamentoPorData(tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos, tipoData dataSearch)
{
    int posicao = -1;
    int i = 0;

    for (i = 0; i < quantAgendamentos; i++)
    {
       if (pAgend[i].dataVisita.dia == dataSearch.dia && pAgend[i].dataVisita.mes == dataSearch.mes && pAgend[i].dataVisita.ano == dataSearch.ano)
       {
           posicao = i;
           i = quantAgendamentos;
       }
    }
    return posicao;
}
