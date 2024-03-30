
#ifndef BIBLIOTECA_LOJA_H
#define BIBLIOTECA_LOJA_H
#include "dados.h"

VENDA* alocar_espaco_vendas();
VENDA* realocar_espaco_vendas(VENDA *prod2, int quant);
VENDA* venda_de_produto(VENDA* sistema_compras, int* quantidade_vendas, PRODUTO *produtos, int quantidade_produtos, int codigo_venda);
void pre_venda(PRODUTO *lista_produtos, int quantidade_produtos);
void salva_pre_venda(PRODUTO* produtos_comprados, int quantidade, float valor_total);
VENDA concluir_venda(VENDA venda_efetuada, int codigo_venda);
void salva_venda(VENDA *historico_vendas, int quantidade_vendas);
void imprimir_vendas(VENDA vendas);
void relatorio_faturamento(VENDA *vendas, int quant_vendas, float faturamentoMes);
VENDA *recupera_historico_vendas(VENDA *historico_vendas, int quantidade_vendas);
int posicao_venda(VENDA *vendas_realizadas, int quantidade_vendas, int codigo_venda);
//FIM VENDAS

#endif // VENDAS_H
