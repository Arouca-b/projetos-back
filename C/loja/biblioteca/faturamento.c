
#include <stdio.h>
#include <stdlib.h>
#include "faturamento.h"
#include "vendas.h"
#include "mensagens.h"
#include <time.h>

FATURAMENTO *alocar_faturamento(){
    FATURAMENTO* fat = (FATURAMENTO*) calloc(1,sizeof(FATURAMENTO));
    if (fat == NULL){
        exit(1);
    }
    fat->faturamentoMes = alocar_faturamentoMes();
    return fat;
}

FATURAMENTO *realocar_faturamento(FATURAMENTO *fat, int anos) {
    fat = realloc(fat, (anos + 1) * sizeof(FATURAMENTO));
    if (fat == NULL) {
        exit(1);
    }
    return fat;
}

void salvar_dados_sistema(FATURAMENTO *sistema, int anos, int codigo_venda){
    //SALVA DADOS DA LISTA DE PRODUTOS
    FILE *arquivo;
    arquivo = fopen("sistema.txt", "wb");

    fwrite(&anos, sizeof(int), 1, arquivo);    //quantidade de protudos no BD
    fwrite(&codigo_venda, sizeof(int), 1, arquivo);
    fwrite(sistema, sizeof(FATURAMENTO) - sizeof(FATURAMENTO_MES*), anos+1, arquivo); //produtos
    fclose(arquivo);
    for(int i = 0; i < anos+1 ; i++){
        salvar_faturamento_mes(sistema[i].faturamentoMes, sistema[i].meses_Em_Atividade);
    }
}

void salvar_faturamento_mes(FATURAMENTO_MES *sistema, int meses){
    FILE *arquivo;
    arquivo = fopen("sistema_mensal.txt", "wb");
    fwrite(sistema, sizeof(FATURAMENTO_MES) - sizeof(VENDA*), meses+1, arquivo); //produtos
    fclose(arquivo);

    for(int i = 0; i < meses+1; i++){
        salva_venda(sistema[i].vendas_mes, sistema[i].qVendas_mes);
    }
}

FATURAMENTO *recuperar_dados_sistema(FATURAMENTO* sistema, int* anos, int *codigo_venda){
    // RECUPERAR DADOS DA LISTA DE PRODUTOS
    FILE *arquivo;
    sistema = alocar_faturamento();
    arquivo = fopen("sistema.txt", "rb");
    if (arquivo == NULL){
        return sistema;
    }

    fread(anos, sizeof(int), 1, arquivo);//quantidade de produtos
    fread(codigo_venda, sizeof(int), 1, arquivo);
    if ((*anos) > 0 ){
        sistema = realocar_faturamento(sistema, (*anos));
    }

    fread(sistema, sizeof(FATURAMENTO) - sizeof(FATURAMENTO_MES*) , (*anos)+1, arquivo);
    fclose(arquivo);
    for(int i = 0; i < *anos + 1; i++){
        sistema[i].faturamentoMes = recuperar_mes(sistema[i].faturamentoMes, sistema[i].meses_Em_Atividade);
    }
    return sistema;
}

FATURAMENTO_MES* recuperar_mes(FATURAMENTO_MES* sistema, int quantidade_meses){
    FILE *arquivo;
    arquivo = fopen("sistema_mensal.txt", "rb");
    if (arquivo == NULL){
        system("clear||cls");
        printf("\n\nERRO AO RECUPERAR ARQUIVO MENSAL\n\n\n");
        exit(1);
    }

    if (quantidade_meses>0){
        sistema = realocar_faturamentoMes(sistema, quantidade_meses);
    }

    fread(sistema, sizeof(FATURAMENTO_MES) - sizeof(VENDA*), quantidade_meses+1, arquivo);
    fclose(arquivo);

    for (int i = 0; i < quantidade_meses + 1; i++){
        sistema[i].vendas_mes = recupera_historico_vendas(sistema[i].vendas_mes, sistema[i].qVendas_mes);
    }
    return sistema;
}

FATURAMENTO *verifica_datas(FATURAMENTO* sistema, int* anos){
    time_t currentTime;
    struct tm *localTime;
    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    if (sistema[*anos].ano == 0){
        sistema[*anos].ano = localTime->tm_year + 1900;
        sistema[*anos].mes_Inical = sistema[*anos].faturamentoMes[sistema[*anos].meses_Em_Atividade].mes = localTime->tm_mon + 1;
    }else{
        if (sistema[*anos].ano != localTime->tm_year + 1900){
            (*anos)++;
            sistema = realocar_faturamento(sistema, *anos);
            sistema[*anos].ano = localTime->tm_year + 1900;
            sistema[*anos].meses_Em_Atividade = 0;
            sistema[*anos].faturamentoMes = alocar_faturamentoMes();
            sistema[*anos].mes_Inical = sistema[*anos].faturamentoMes[sistema[*anos].meses_Em_Atividade].mes = localTime->tm_mon + 1;
            sistema[*anos].quantidade_vendas = 0;
        }

        if (sistema[*anos].faturamentoMes[sistema[*anos].meses_Em_Atividade].mes != localTime->tm_mon + 1){
            sistema[*anos].meses_Em_Atividade++;
            printf("alterou");
            pausa();
            sistema[*anos].faturamentoMes = realocar_faturamentoMes(sistema[*anos].faturamentoMes, sistema[*anos].meses_Em_Atividade);
            sistema[*anos].faturamentoMes[sistema[*anos].meses_Em_Atividade].mes = localTime->tm_mon + 1;
            sistema[*anos].faturamentoMes[sistema[*anos].meses_Em_Atividade].qVendas_mes = 0;
            sistema[*anos].faturamentoMes[sistema[*anos].meses_Em_Atividade].vendas_mes = alocar_espaco_vendas();
        }
    }
    return sistema;
}

FATURAMENTO renda_anual(FATURAMENTO sistema, PRODUTO *lista_Produtos, int produtos_Em_Estoque, int *codigo_venda){

    sistema.faturamentoMes[sistema.meses_Em_Atividade] = renda_mensal(sistema.faturamentoMes[sistema.meses_Em_Atividade], lista_Produtos, produtos_Em_Estoque, *codigo_venda);
    sistema.quantidade_vendas++;
    sistema.faturamentoMes[sistema.meses_Em_Atividade].vendas_mes[sistema.faturamentoMes[sistema.meses_Em_Atividade].qVendas_mes-1].codigoVenda = sistema.quantidade_vendas;

    sistema.arrecadado_anual += sistema.faturamentoMes[sistema.meses_Em_Atividade].vendas_mes[sistema.faturamentoMes[sistema.meses_Em_Atividade].qVendas_mes-1].preco_venda;
    (*codigo_venda)++;
    return sistema;
}

FATURAMENTO_MES renda_mensal(FATURAMENTO_MES mesAtual, PRODUTO *produtos, int produtos_em_estoque, int codigo_venda){
    if (mesAtual.mes <= 0 || mesAtual.mes > 12){
        time_t currentTime;
        struct tm *localTime;
        currentTime = time(NULL);
        localTime = localtime(&currentTime);
        mesAtual.mes = localTime->tm_mon + 1;
    }
    
    mesAtual.vendas_mes = venda_de_produto(mesAtual.vendas_mes, &mesAtual.qVendas_mes, produtos, produtos_em_estoque, codigo_venda);
    mesAtual.arrecadado_mensal += mesAtual.vendas_mes[mesAtual.qVendas_mes-1].preco_venda;

    return mesAtual;
}


//FATURAMENTO MENSAL
FATURAMENTO_MES *alocar_faturamentoMes(){
    FATURAMENTO_MES* fat = (FATURAMENTO_MES*) calloc(1,sizeof(FATURAMENTO_MES));
    if (fat == NULL){
        exit(1);
    }
    fat->vendas_mes = alocar_espaco_vendas();
    return fat;
}

FATURAMENTO_MES *realocar_faturamentoMes(FATURAMENTO_MES *fat_m, int meses) {
    fat_m = realloc(fat_m, (meses + 1) * sizeof(FATURAMENTO_MES));
    if (fat_m == NULL) {
        exit(1);
    }
    return fat_m;
}

void relatorio_Financeiro(FATURAMENTO *sistema, int anos){
    int opcao = 0;
    int valor = 0;
    int ano_analise = 0;
    do{
        system("clear||cls");
        printf("\n\t\t\t\t\tSISTEMA FINANCEIRO\n\n");
        imprimir_relatorios_anuais(sistema, anos);
        printf("\n\t\t\t1 - Relatorio Ano");
        printf("\n\t\t\t2 - Relatorio Venda");
        printf("\n\n\t\t\t0 - Sair");
        printf("\n\n\t\t\t-> Escolha: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao){
        case 1:
            printf("\n\n\t\t\t-> Insira o ano que deseja verificar: ");
            scanf("%d", &valor);
            getchar();
            ano_analise = procurar_ano(sistema, anos, valor);
            if (ano_analise!=-1){
                imprimir_relatorios_mensais(sistema[ano_analise].faturamentoMes, sistema[ano_analise].meses_Em_Atividade);
                break;
            }
            erro();
            break;

        case 2:
            printf("\n\n\t\tInsira codigo venda: ");
            scanf("%d", &valor);
            getchar();
            detalhe_venda(sistema, anos, valor);
            break;
        }
    }while (opcao!=0);
    system("clear||cls");
}

void detalhe_venda(FATURAMENTO *sistema, int anos, int codigo_venda){
    int ano_t = 0, mes_t = 0, posicao = 0;
    ano_t = procurar_limite_ano(sistema, anos, codigo_venda);
    mes_t = procurar_limite_mes(sistema, ano_t, codigo_venda);
    posicao = posicao_venda(sistema[ano_t].faturamentoMes[mes_t].vendas_mes, sistema[ano_t].faturamentoMes[mes_t].qVendas_mes, codigo_venda);
    if (posicao==-1){
        erro();
        return;
    }
    imprimir_vendas(sistema[ano_t].faturamentoMes[mes_t].vendas_mes[posicao]);
    pausa();
}

int procurar_limite_ano(FATURAMENTO *sistema, int anos, int codigo_venda){
    int limite = 0;
    if (anos == 0 && sistema[0].quantidade_vendas < codigo_venda){
        return -1;
    }

    for(int i = 0; i < anos + 1; i++){
        limite += sistema[i].quantidade_vendas;
        if(limite >= codigo_venda){
            return i;
        }
    }
    return -1;
}

int procurar_limite_mes(FATURAMENTO *sistema_ano, int tamanho, int codigo_venda){
    int limite = 0;

    for(int i = 0; i < tamanho; i++){
        limite += sistema_ano[i].quantidade_vendas;
    }

    for (int i = 0; i < sistema_ano[tamanho-1].meses_Em_Atividade + 1; i++){
        limite += sistema_ano[tamanho-1].faturamentoMes[i].qVendas_mes;
        if(limite >= codigo_venda){
            return i;
        }
    }

    return -1;
}

void imprimir_relatorios_anuais(FATURAMENTO *sistema, int anos_atuacao){
    printf("\t\t------------------------------------------------------------------------\n\t\t");
    printf("|%7s| ", "Ano  ");
    printf(" %14s|", "  Qtd Vendas  ");
    printf("%16s", " Meses atuando |");
    printf("%14s|", "  Arrecadado  ");
    printf(" %14s", "Media/mes   |");
    for (int i = 0; i < anos_atuacao + 1; i++) {
        printf("\n\t\t|%6d |", sistema[i].ano);
        printf("  %8d      |", sistema[i].quantidade_vendas);
        printf("       %2d      |", sistema[i].meses_Em_Atividade);
        printf("  %10.2f  |", sistema[i].arrecadado_anual);
        printf("  %10.2f  |", (float) (sistema[i].arrecadado_anual/(sistema[i].meses_Em_Atividade+1)));
    }
    printf("\n\t\t------------------------------------------------------------------------\n\n");
}

void imprimir_relatorios_mensais(FATURAMENTO_MES* sistema_ano, int quant_meses){
    int opcao;

    system("clear||cls");
    printf("\n\t\t\t\t\tSISTEMA FINANCEIRO\n\n");
    printf("\t\t--------------------------------------------------------\n\t\t");
    printf("|  %s  | ", "Mes");
    printf("%12s", "  Qtd Vendas   |");
    printf("%14s|", "  Arrecadado  ");
    printf(" %14s", "Media/vendas |");
    for (int i = 0; i < quant_meses + 1; i++) {
        printf("\n\t\t|%5d  |", sistema_ano[i].mes);
        printf("       %2d       |", sistema_ano[i].qVendas_mes);
        printf("  %10.2f  |", sistema_ano[i].arrecadado_mensal);
        printf("  %10.2f  |", (float) (sistema_ano[i].arrecadado_mensal/(sistema_ano[i].qVendas_mes)));
    }
    printf("\n\t\t--------------------------------------------------------\n\n");
    printf("\n\t\t\t 1 - Detalhe mes");
    printf("\n\n\t\t\t 0 - Sair");
    printf("\n\n\t\t\t -> Escolha: ");
    scanf("%d", &opcao);
    getchar();
    switch (opcao){
        case 1:{
            int mes, posicao;
            printf("\n\n\t\t -> Mes desejado: ");
            scanf("%d", &mes);
            getchar();
            posicao = procurar_mes(sistema_ano, quant_meses, mes);
            if (posicao==-1){
                erro();
                break;
            }
            relatorio_faturamento(sistema_ano[posicao].vendas_mes, sistema_ano[posicao].qVendas_mes, sistema_ano[posicao].arrecadado_mensal);
            break;
        }
    }
    system("clear||cls");
}

int procurar_ano(FATURAMENTO *sistema, int anos, int ano){
    for (int i = 0; i < anos + 1; i++){
        if (sistema[i].ano == ano){
            return i;
        }
    }
    return -1;
}

int procurar_mes(FATURAMENTO_MES *sistema, int quant_meses, int mes){
    for (int i = 0; i < quant_meses + 1; i++){
        if (sistema[i].mes == mes){
            return i;
        }
    }
    return -1;
}
