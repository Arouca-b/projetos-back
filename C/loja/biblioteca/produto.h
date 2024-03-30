#ifndef PRODUTO_H
#define PRODUTO_H
#include "dados.h"

//PRODUTOS
PRODUTO* alocar_espaco_produtos();
PRODUTO* realocar_espaco_produtos(PRODUTO *prod2, int quant);
PRODUTO *excluirProduto(PRODUTO *produtos, int posicao, int *quantidade);
PRODUTO editarProduto(PRODUTO produto);
PRODUTO *produtos_cadastrados(PRODUTO *lista_Produtos, int *quant_produtos);
void imprimir_produtos(PRODUTO* produtos, int quant);
void imprimir_produto_unico(PRODUTO produtos);
PRODUTO *inserir_prod(int *quant, PRODUTO* prod1);
PRODUTO *ordenar_produtos(PRODUTO *origem, PRODUTO *novo, int quant);
void atualizar_estoque(PRODUTO *produtos, int quant);
int procurar_produto(int cod, PRODUTO *prod2, int quant);
void consultar_preco(PRODUTO *produto, int quant_produtos);
void salvar_lista_produtos(PRODUTO *produtos, int quant_produtos);
PRODUTO *recupera_lista_produtos(PRODUTO *produtos, int* quant_produtos);
PRODUTO *recuperar_estoque_preVenda(PRODUTO* lista_produtos, int quantidade_l, PRODUTO* lista_preVenda, int quantidade_preVenda);
//FIM PRODUTOS

#endif // PRODUTO_H
