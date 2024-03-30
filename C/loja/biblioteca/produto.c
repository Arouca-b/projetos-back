
#include "produto.h"
#include <stdio.h>
#include <stdlib.h>
#include "mensagens.h"

//FUN��ES DE PRODUTOS
PRODUTO *alocar_espaco_produtos(){
    PRODUTO *prod1 = (PRODUTO *) calloc(1, sizeof(PRODUTO));
    if (prod1 == NULL) {
        exit(1);
    }
    return prod1;
}

PRODUTO *realocar_espaco_produtos(PRODUTO *prod2, int quant) {
    prod2 = realloc(prod2, (quant + 1) * sizeof(PRODUTO));
    if (prod2 == NULL) {
        exit(1);
    }
    return prod2;
}
// FIM ALOCA��O DE MEM�RIA

PRODUTO *inserir_prod(int *quant, PRODUTO *prod1) { // Inserir novos produtos
    int indice = *quant, cod = 0;
    int verifica_duplicidade = 0;
    PRODUTO *novo = alocar_espaco_produtos();

    system("clear||cls");
    printf("\t\t\t\tNOVO PRODUTO\n\n");

    printf("\t\t\tCodigo: ");
    scanf("%d%*c", &cod);
    fflush(stdout);
    fflush(stdin);
    verifica_duplicidade = procurar_produto(cod, prod1, *quant);
    while (verifica_duplicidade != -1){ //VERIFICAR SE J� EXISTE UM PRODUTO COM C�DIGO
        system("clear||cls");
        printf("\n\n\t\t\t\x1b[31mCodigo ja Cadastrado\n\n");
        printf("\t\t\t\t\x1b[0mNOVO PRODUTO\n\n");
        printf("\t\t\tCodigo: ");
        scanf("%d%*c", &cod);
        verifica_duplicidade = procurar_produto(cod, prod1, *quant);
    }
    novo->cod = cod;
    printf("\t\t\tNome produto: ");
    scanf("%99[^\n]", novo->desc);
    fflush(stdin);
    // receber valor estoque
    printf("\t\t\tEstoque: ");
    scanf("%d", &novo->estoque);
    getchar();

    printf("\t\t\tPreco: R$ ");
    scanf("%f", &novo->preco);
    getchar();

    novo->preco_estoque = novo->preco * novo->estoque;
    prod1 = ordenar_produtos(prod1, novo, indice);
    (*quant)++;
    system("clear||cls");
    printf("\n\n\t\t\t\t  PRODUTO CADASTRADO COM SUCESSO!\n\n");
    pausa();
    return prod1;
}

//ordenar caso cliente insira os c�digos do poduto
PRODUTO *ordenar_produtos(PRODUTO *origem, PRODUTO *novo,int quant) { // ordenar produtos pelo c�digo
    int i = 0;
    if (quant == 0) {
        origem = novo;
    } else {
        while (i < quant) {
            if (origem[i].cod > novo->cod) {
                break;
            }
            i++;
        }
        origem = realocar_espaco_produtos(origem, quant);

        while (quant > i) {
            origem[quant] = origem[quant - 1];
            quant--;
        }
        origem[i] = *novo;
    }
    return origem;
}

//Case 5

PRODUTO *produtos_cadastrados(PRODUTO *lista_Produtos, int *quant_produtos){
    int opcao = 0, codigo_produto = 0, posicao = 0;
    do{
        system("clear||cls");
        printf("\n\t\t\t\t\tLISTA DE PRODUTOS\n\n\n");
        imprimir_produtos(lista_Produtos, *quant_produtos);
        printf("\n\n\t -> 1 - Excluir Produto");
        printf("\n\t -> 2 - Editar Produto\n");
        printf("\n\n\t -> 0 - Sair\n");
        printf("\t\tEscolha: ");
        scanf("%d", &opcao);
        getchar();
        if (opcao == 0){
            system("clear||cls");
            return lista_Produtos;
        }

        printf("\t\t-> Codigo produto: ");
        scanf("%d", &codigo_produto);
        getchar();
        posicao = procurar_produto(codigo_produto, lista_Produtos, *quant_produtos);

        if (posicao == -1){
            erro();
            printf("\t\t\t\t\tInsira um Codigo valido!\n");
        }else{
            switch (opcao){
                case 1:
                    lista_Produtos = excluirProduto(lista_Produtos, posicao, quant_produtos);
                    break;

                case 2:
                    lista_Produtos[posicao]= editarProduto(lista_Produtos[posicao]);
                    salvar_lista_produtos(lista_Produtos, *quant_produtos);
                    break;

                default:
                    system("clear||cls");
                    printf("\n\n\n\n\t\t\t\t\tOPCAO INVALIDA\n\n");
                    break;
            }
            pausa();
        }
    } while (posicao == -1);
    return lista_Produtos;
}

PRODUTO *excluirProduto(PRODUTO *produtos, int posicao, int *quantidade){
    if (posicao < *quantidade - 1){
        for (int i = posicao; i < *quantidade - 1; i++){
            produtos[i] = produtos[i+1];
        }
    }
    (*quantidade)--;
    if (*quantidade){
        produtos = realocar_espaco_produtos(produtos, *quantidade - 1);
        salvar_lista_produtos(produtos, *quantidade);
    }else{
        remove("listaProdutos.txt");
    }
    return produtos;
}

PRODUTO editarProduto(PRODUTO produto){
    int opcao = 0;

    do{
        system("clear||cls");
        imprimir_produto_unico(produto);
        printf("\n\n\t\t -> 1 - Alterar Descricao\n");
        printf("\t\t -> 2 - Alterar Preco\n");
        printf("\t\t -> 3 - Alterar Estoque\n");
        printf("\n\n\t\t -> 0 - Sair\n");
        printf("\n\n\t\t-> Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao){
        case 1:
            printf("\n\n\t\t Old Descrition: %s\n", produto.desc);
            printf("\n\n\t\t New Descrition: ");
            scanf("%s%*c", produto.desc);
            break;

        case 2:
            printf("\n\n\t\t Old price: %.2f\n", produto.preco);
            printf("\n\n\t\t New price: ");
            scanf("%f%*c", &produto.preco);
            produto.preco_estoque = produto.estoque * produto.preco;
            break;

        case 3:
            printf("\n\n\t\t Old estoque: %d\n", produto.estoque);
            printf("\n\n\t\t New Estoque: ");
            scanf("%d%*c", &produto.estoque);
            produto.preco_estoque = produto.estoque * produto.preco;
            break;

        default:
            system("clear||cls");
            printf("\n\n\n\t\t\t\tAtualizacao realizada com sucesso\n");
            break;
        }
    } while (opcao!=0);
    return produto;
}


void imprimir_produtos(PRODUTO *produtos, int quant) { // IMPRIMIR TODOS OS PRODUTOS
    printf("\t\t--------------------------------------------------------------------------\n\t\t");
    printf("|%12s| ", "Codigo   ");
    printf("%19s|", "     Descricao     ");
    printf("%13s", "Quantidade |");
    printf(" %12s", "Preco unt |");
    printf("%11s |\n", "Preco  ");
    for (int i = 0; i < quant; i++) {
        printf("\t\t| %7d    |", produtos[i].cod);
        printf(" %14s     |", produtos[i].desc);
        printf("  %8d  |", produtos[i].estoque);
        printf("%10.2f  |", produtos[i].preco);
        printf("%10.2f  |\n", produtos[i].preco_estoque);
    }
    printf("\t\t--------------------------------------------------------------------------\n\n");
}

void atualizar_estoque(PRODUTO *produtos, int quant) { //ATUALIZAR QUANTIDADE DE ESTOQUE, SOMANDO OU DIMINUIDO
    int cod, posicao_produto, op = 0, estoque;
    system("clear||cls");
    printf("\t\t\t\t\tATUALIZAcAO DE ESTOQUE\n\n");
    printf("\t\t-> Codigo produto: ");
    scanf("%d%*c", &cod);
    posicao_produto = procurar_produto(cod, produtos, quant);
    if (posicao_produto != -1) {
        printf("\n1. Inserir itens\n");
        printf("2. Excluir itens\n\n");
        scanf("%d%*c", &op);
        system("clear||cls");
        printf("\t\t\tATUALIZACAO DE ESTOQUE\n\n");
        imprimir_produto_unico(produtos[posicao_produto]);
        if (op == 1) {
        printf("\n\t\t-> Qtd itens inserir no estoque: ");
            scanf("%d%*c", &estoque);
            produtos[posicao_produto].estoque += estoque;
            produtos[posicao_produto].preco_estoque = produtos[posicao_produto].estoque * produtos[posicao_produto].preco;
        }else {
            if (op == 2) {
                printf("\n\t\t-> Qtd itens retirar do estoque: ");
                scanf("%d%*c", &estoque);
                produtos[posicao_produto].estoque -= estoque;
                produtos[posicao_produto].preco_estoque = produtos[posicao_produto].estoque * produtos[posicao_produto].preco;
            }
        }
        printf("\t\t\t\t\tEstoque atualizado\n\n");
        pausa();
    } else {
        erro(); // Caso n�o ache o produto no banco de dados
    }
    system("clear||cls");
    salvar_lista_produtos(produtos, quant);
}

int procurar_produto(int cod, PRODUTO *prod2, int quant){//PROCURAR DETERMINADO PRODUTO NO ESTOQUE
    for (int posicao = 0; posicao < quant; posicao++) {
        if (prod2[posicao].cod == cod) {
            return posicao;
        }
    }
    return -1;
}

void consultar_preco(PRODUTO *produto, int quant_produtos) { // PESQUISA PRODUTO E IMPRIME O PRE�O
    int cod, posicao = 0;
    system("clear||cls");
    printf("\t\t\t\t\tCONSULTA PRECO\n\n\n");
    imprimir_produtos(produto, quant_produtos);
    printf("\t\t-> Insira Codigo do produto para consultar preco ou 0 para fechar consulta!\n\n");
    printf("\t\t-> Codigo: ");
    scanf("%d%*c", &cod);
    if (cod == 0){
        system("clear||cls");
        return;
    }

    posicao = procurar_produto(cod, produto, quant_produtos);
    if (posicao != -1) {
        system("clear||cls");
        printf("\t\t\t\t\tCONSULTA PRECO\n\n\n");
        imprimir_produto_unico(produto[posicao]);
        pausa();
    } else {
        erro();
    }
}

void imprimir_produto_unico(PRODUTO produtos){
    printf("\t\t--------------------------------------------------------------------------\n\t\t");
    printf("|%12s| ", "Codigo   ");
    printf("%19s|", "     Descricao     ");
    printf("%13s", "Quantidade |");
    printf(" %12s", "Preco unt |");
    printf("%11s |\n", "Preco  ");
    printf("\t\t| %7d    |", produtos.cod);
    printf(" %14s     |", produtos.desc);
    printf("  %8d  |", produtos.estoque);
    printf("%10.2f  |", produtos.preco);
    printf("%10.2f  |\n", produtos.preco_estoque);
    printf("\t\t--------------------------------------------------------------------------\n\n");
}

void salvar_lista_produtos(PRODUTO *produtos, int quant_produtos) { // SALVAR A LISTA DE PRODUTOS DO MERCADO
    FILE *fp;
    fp = fopen("listaProdutos.txt", "wb");
    fwrite(&quant_produtos, sizeof(int), 1, fp);    //quantidade de protudos no BD
    fwrite(produtos, sizeof(PRODUTO), quant_produtos, fp); //produtos
    fclose(fp);
}

//Caso tehha um problema na venda, todos os produtos voltam para o estoque
PRODUTO *recuperar_estoque_preVenda(PRODUTO* lista_produtos, int quantidade_l, PRODUTO* lista_preVenda, int quantidade_preVenda){
    int indice, cod;
    for (int i = 0; i < quantidade_preVenda; i++){
        cod = lista_preVenda[i].cod;
        indice = procurar_produto(cod, lista_produtos, quantidade_l);
        lista_produtos[indice].estoque += lista_preVenda[i].estoque;
    }
    return lista_produtos;
}

PRODUTO *recupera_lista_produtos(PRODUTO *produtos, int *quant_produtos){ // RECUPERAR DADOS DA LISTA DE PRODUTOS
    FILE *fp;
    FILE *pre_venda;
    PRODUTO *repor_vendas_nao_concluidas = alocar_espaco_produtos();
    int quant_pre_venda = 0;
    produtos = alocar_espaco_produtos();

    fp = fopen("listaProdutos.txt", "rb");
    if(fp == NULL) { //se não existir lista de produto
        return produtos;//alocar 1 espaço
    }

    fread(quant_produtos, sizeof(int), 1, fp);//quantidade de produtos
    produtos = realocar_espaco_produtos(produtos, (*quant_produtos) - 1);//realocar memoria para armazenar todos esses produtos, (*quant_produtos) - 1 porque na funcao ha uma adicao na quantidade de alocacao

    fread(produtos, sizeof(PRODUTO), *quant_produtos, fp);

    fclose(fp);

    pre_venda = fopen("preVenda.txt", "rb");
    if (pre_venda == NULL){
        free(repor_vendas_nao_concluidas);
        return produtos;
    }

    fread(&quant_pre_venda, sizeof(int), 1, pre_venda);
    repor_vendas_nao_concluidas = realocar_espaco_produtos(repor_vendas_nao_concluidas, quant_pre_venda-1);
    fread(repor_vendas_nao_concluidas, sizeof(PRODUTO), quant_pre_venda, pre_venda);
    produtos = recuperar_estoque_preVenda(produtos, *quant_produtos, repor_vendas_nao_concluidas, quant_pre_venda);
    free(repor_vendas_nao_concluidas);
    remove("preVenda.txt");
    return produtos;
}
// FIM PRODUTOS
