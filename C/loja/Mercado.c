#include "biblioteca/vendas.h"
#include "biblioteca/produto.h"
#include "biblioteca/dados.h"
#include "biblioteca/mensagens.h"
#include "biblioteca/faturamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


int main() {
    setlocale(LC_ALL, "Portuguese");
    int quant_produtos = 0, anos = 0, codigo_venda = 0;
    int opcao = 0;
    PRODUTO *lista_Produtos = recupera_lista_produtos(lista_Produtos, &quant_produtos);
    FATURAMENTO *sistema_Controle = recuperar_dados_sistema(sistema_Controle, &anos, &codigo_venda);
    //VENDA *vendas_prod = recupera_historico_vendas(vendas_prod, &quant_vendas);

    if (codigo_venda == 0 && quant_produtos == 0 && sistema_Controle[0].ano == 0){
        creditos();
    }
    sistema_Controle = verifica_datas(sistema_Controle, &anos);

    do{
        menu();
        fflush(stdin);
        opcao = escolhe_opcao(6); //O parametro é a quantidade de opções disponiveis

        switch (opcao) {
            case 1:
                lista_Produtos = inserir_prod(&quant_produtos, lista_Produtos);
                salvar_lista_produtos(lista_Produtos, quant_produtos);
            break;

            case 2:
                if (quant_produtos) {
                    atualizar_estoque(lista_Produtos, quant_produtos);
                } else {
                    falta_dados();
                }
            break;

            case 3:
                if (quant_produtos) {
                    sistema_Controle[anos] = renda_anual(sistema_Controle[anos], lista_Produtos, quant_produtos, &codigo_venda);
                    //vendas_prod = venda_de_produto(vendas_prod, &quant_vendas, lista_Produtos, quant_produtos);
                    salvar_dados_sistema(sistema_Controle, anos, codigo_venda);
                } else {
                    falta_dados();
                }
            break;

            case 4:
                if (quant_produtos) {
                    consultar_preco(lista_Produtos, quant_produtos);
                } else {
                    falta_dados();
                }
            break;

            case 5:
                if (quant_produtos) {
                    lista_Produtos = produtos_cadastrados(lista_Produtos, &quant_produtos);
                } else {
                    falta_dados();
                }
            break;

            case 6:
                if (sistema_Controle[anos].quantidade_vendas){
                    relatorio_Financeiro(sistema_Controle, anos);
                }else{
                    falta_dados();
                }
            break;
        }
        salvar_dados_sistema(sistema_Controle, anos, codigo_venda);
    }while (opcao != 0);
    limpar_memoria(sistema_Controle, anos, lista_Produtos);
    despedida();
}
