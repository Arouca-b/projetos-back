
#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include <unistd.h> // Para sistemas Unix/Linux
//#include <windows.h> // Para sistemas Windows


//MENSAGENS

void pausa() {
    printf("\n\n\t\t\t\t    aperte ENTER para continuar\n\n");
    scanf("%*c");
    system("clear||cls");
}

void creditos(){
    printf("\n\n\n\n\t\t\t***  **  **  **  **  **  **  **  **  **  **  ***\n");
    printf("\t\t\t*                                              *\n");
    printf("\t\t\t*                                              *\n");
    printf("\t\t\t*           PROJETO DESENVOLVIDO POR:          *\n");
    printf("\t\t\t*              --> BRENO AROUCA <--            *\n");
    printf("\t\t\t*                                              *\n");
  /*printf("\t\t\t*                => PROFESSOR <=               *\n");
    printf("\t\t\t*                 --> EDGAR <--                *\n");
    printf("\t\t\t*                                              *\n");*/
    printf("\t\t\t*             PROGRAMA PARA SIMULAR            *\n");
    printf("\t\t\t*          MERCADO - LOJA - RESTAURANTE        *\n");
    printf("\t\t\t*                                              *\n");
    printf("\t\t\t*              REGISTRO DE PRODUTOS            *\n");
    printf("\t\t\t*                       &                      *\n");
    printf("\t\t\t*              EFETUACAO DE VENDAS             *\n");
    printf("\t\t\t*                                              *\n");
    printf("\t\t\t*                                              *\n");
    printf("\t\t\t***  **  **  **  **  **  **  **  **  **  **  ***\n");
    sleep(8);
    system("clear||cls");
}

void menu() {
    printf("\t\t\t*------------------------------------------*\n");
    printf("\t\t\t|                                          |\n");
    printf("\t\t\t|               MERCADO NEGRO              |\n");
    printf("\t\t\t|                                          |\n");
    printf("\t\t\t|                                          |\n");
    printf("\t\t\t|    1.   Inserir Produto                  |\n");
    printf("\t\t\t|    2.   Atualizar estoque                |\n");
    printf("\t\t\t|    3.   Realizar venda                   |\n");
    printf("\t\t\t|    4.   Consultar preco                  |\n");
    printf("\t\t\t|    5.   Produtos Cadastrados             |\n");
    printf("\t\t\t|    6.   Relatorio Faturamento            |\n");
    printf("\t\t\t|                                          |\n");
    printf("\t\t\t|                                          |\n");
    printf("\t\t\t|    0.   Sair                             |\n");
    printf("\t\t\t*------------------------------------------*\n\n\n");

    printf("\t\t\tEscolhe: ");
}

int escolhe_opcao(int qtd_opcoes) {
    char t[20];
    int opcao = 0;
    scanf("%19[^\n]", t);
    opcao = atoi(t);
    getchar();
    if ((opcao > qtd_opcoes|| opcao < 0)) {
        system("clear||cls");
        printf("\n\n\t\t\t\t OPCAO INVALIDA\n\n");
        pausa();
        return -1;
    }
    return opcao;
}

void falta_dados() {
    system("clear||cls");
    printf("\n\n\t\t\t\tAlimente o Banco de dados primeiro!!\n\n");
    pausa();
}

void erro() {
    system("clear||cls");
    printf("\n\n\t\t\tNao encontrado no banco de dados!!\n\n");
    pausa();
}

void limpar_memoria(FATURAMENTO *sistema, int anos, PRODUTO *lista_produtos) {
    free(lista_produtos);

    for (int i = 0; i < anos; i++){
        for (int meses = 0; meses < sistema[i].meses_Em_Atividade; meses++){
            for (int vendas = 0; vendas < sistema[i].faturamentoMes[meses].qVendas_mes; i++){
                for (int produtos = 0; produtos < sistema[i].faturamentoMes[meses].vendas_mes[vendas].quantidade_produtos; produtos++){
                    free(sistema[i].faturamentoMes[meses].vendas_mes[vendas].itemvenda);
                }
                free(sistema[i].faturamentoMes[meses].vendas_mes);
            }
            free(sistema[anos].faturamentoMes);
        }
    }
    free(sistema);
}

void despedida(){
    system("clear||cls");
    printf("\n\n\n\n\t\t\t\tHORA DE DESCANSAR, AMANHA E DIA DE SOFRER(TRABALHAR) DE NOVO!!\n\n\n\n\n\n\n\n");
}

void inoperante(){
    system("clear||cls");
    printf("\n\n\n\n\t\t\t\tEstamos em manutenção\n\n\n");
    pausa();
}