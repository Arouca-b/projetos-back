#ifndef DADOS_H
#define DADOS_H
//PRODUTO
typedef struct {
    int cod, estoque;
    char desc[100];
    float preco;
    float preco_estoque;
} PRODUTO;

//VENDAS

typedef struct {
    int quantidade_produtos;
    int codigoVenda;
    int dia;
    int mes;
    int ano;
    int hora;
    int minutos;
    int segundos;
    float preco_venda;
    PRODUTO *itemvenda;
} VENDA;

typedef struct{
    int qVendas_mes;
    int mes;
    float arrecadado_mensal;
    VENDA *vendas_mes;
} FATURAMENTO_MES;

typedef struct{
    int ano;
    int mes_Inical; //mes que que empresa começou a utilizar o serviço
    int meses_Em_Atividade;//Quantidade de meses usando o sistema
    float arrecadado_anual;
    int quantidade_vendas;
    FATURAMENTO_MES *faturamentoMes;
} FATURAMENTO;

#endif // BIBLIOTECA_LOJA_H
