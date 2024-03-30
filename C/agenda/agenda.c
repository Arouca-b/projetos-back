#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct agenda{
    char* nome;
    char* DDD;
    char* telefone;
    struct agenda *prox;
}AGENDA;

//imprimir
void imprimir_contato(AGENDA* contato);
void mostrar_contatos(AGENDA*);
void menu_arquivos();
void erro_valor();

int cont_char(char* text);


//Dados - Inserção e Exclusão
char* inicialiar(char* primeira);
int valida();
AGENDA* inserir_contato(AGENDA*, char*, char*, char*);
int valida();
void insere_nome(char **nome);
void padronizar_nome(char** nome);
void insere_ddd(char** DDD);
void insere_number(char** telefone);
AGENDA* ordenar_nomes(AGENDA *lista, AGENDA *contato);
AGENDA* excluir_contato(AGENDA* lista, AGENDA* contato);

//outros
AGENDA* procura_contato(AGENDA* lista);
AGENDA* acao_escolha(int opcao, AGENDA*);
void editar_arquivo(FILE* fp, char* nomeAr);
char* nome_arquivo(char*);
void prosseguir();


AGENDA* ler_arquivo(AGENDA* lista);
void salvar_arquivo(AGENDA* contato);


void main(){
    int escolha;
    AGENDA *agenda;
    agenda = ler_arquivo(agenda);
    do{
        menu_arquivos();
        escolha = valida();
        agenda = acao_escolha(escolha, agenda);
    }while (escolha!=0);
}

AGENDA* ler_arquivo(AGENDA* lista) {
    FILE *fp = fopen("contato.txt", "r");
    if (fp == NULL) {
    	fclose(fp);
        return NULL;
    }
    char text[50];
    char *enter;
    int tam;

    while (!feof(fp)) {
        tam = 0;
        AGENDA *pega_contatos = (AGENDA*) malloc(sizeof(AGENDA)); // Aloca memória para a estrutura
            
        if (pega_contatos == NULL) {
            printf("Erro na alocação de memória para pega_contatos\n");
            exit(1);
        }

        fscanf(fp, "%s", text);
        tam = cont_char(text);
        pega_contatos->nome = (char*)malloc(tam);
        strcpy(pega_contatos->nome, text);
        
        fscanf(fp, "%s", text);
        tam = cont_char(text);
        pega_contatos->DDD = (char*)malloc(tam); 
        strcpy(pega_contatos->DDD, text);

        fscanf(fp, "%s %c", text, enter);
        tam = cont_char(text);
        pega_contatos->telefone = (char*)malloc(tam);    
        strcpy(pega_contatos->telefone, text);

        lista = ordenar_nomes(lista, pega_contatos);
        //if (fscanf(fp, "%s %s %s", pega_contatos->nome, pega_contatos->DDD, pega_contatos->telefone) == 3) {
            // Se a leitura for bem-sucedida, adicione pega_contatos à lista
            //lista = ordenar_nomes(lista, pega_contatos);
        //} else {
            //free(pega_contatos); // Libera memória se a leitura falhar
        //}
    }

    fclose(fp);
    return lista;
}

int cont_char(char* text){
    int i = 0;
    for (; text[i] != '\0'; i++);
    return i;
}


void salvar_arquivo(AGENDA* contato){
    FILE *lista_contatos = fopen("contato.txt", "w");
    if (lista_contatos == NULL){
        printf("\n\nErro ao salvar arquivo!!\n\n");
        exit(1);
    }
    AGENDA* persegue = contato;
    AGENDA* prox = persegue->prox;
    while (contato!=NULL){
        fprintf(lista_contatos ,"%s     %s      %s\n", contato->nome, contato->DDD, contato->telefone);
        //fwrite(contato, sizeof(AGENDA), 1, lista_contatos);
        contato = contato->prox;
    }
    fclose(lista_contatos);

    fflush(stdout);
    while (persegue != NULL){
        free(persegue->nome);
        free(persegue->DDD);
        free(persegue->telefone);
        free(persegue);
        persegue = prox;
        if (prox != NULL){
            prox = prox->prox;
        }else{
            free(prox);
        }
    }
}

void menu_arquivos(){
    printf("\t\t\t\t\t\tAGENDA\n\n");
    printf("\t\t\t\t\t   LISTA DE CONTATO\n\n\n");
    printf("\t1 - Adicionar Contato\n");
    printf("\t2 - Procurar Contato\n");
    printf("\t3 - Imprimir lista de contatos\n");
    printf("\t0 - Fechar Contatos\n\n");
    printf("\tEscolha: ");
}

AGENDA* acao_escolha(int opcao, AGENDA* agenda){ // Execução da ação escolhida pelo cliente
    system("clear||cls");
    switch (opcao){
        case 1:{
            char *nome = inicialiar(nome), *DDD = inicialiar(DDD),  *telefone = inicialiar(telefone);
            printf("\t\t\tINSERIR CONTATO\n\n");
            printf("\tNOME: ");
            insere_nome(&nome);
            printf("\n\tDDD: ");
            insere_ddd(&DDD);
            printf("\tTELEFONE: ");
            insere_number(&telefone);
            agenda = inserir_contato(agenda, nome, DDD, telefone);
            system("clear||cls");
            printf("\n\n\n\n\t\t\tCONTATO ADICIONADO COM SUCESSO!!!");
            fflush(stdout);
            sleep(2);
            system("clear||cls");
            free(nome);
            free(DDD);
            free(telefone);
            break;
        }

        case 2:
            agenda = procura_contato(agenda);
            break;

        case 3:
            mostrar_contatos(agenda);
            break;
        
        case 4:
            break;
        
        
        default:
            if (agenda!= NULL){
                salvar_arquivo(agenda);
            }            
            break;
    }
    return agenda;
}

int valida(){ //validar entrada das opções menu
    char a[4];
    scanf("%3s%*c", a);
    fflush(stdin);
    if (((a[0] >= 48 && a[0] <= 53) || a[0] == 56) && a[1]=='\0'){
        return a[0] - 48;
    }
    erro_valor();
    return valida();
}

void erro_valor(){//Caso usuário insira um valor fora dos parâmetros
    system("clear||cls");
    printf("\n\t\t\t\tInsira um valor válido!!\n\n");
    sleep(2);
    system("clear||cls");
    menu_arquivos();
}

AGENDA* inserir_contato(AGENDA *contato, char* nome, char* DDD, char* telefone){ //inserir novos contatos
    AGENDA *contato2 = (AGENDA*) malloc(sizeof(AGENDA));
    int tam = strlen(nome);
    //alocar espaço para nome
    contato2->nome = malloc(tam*sizeof(char));
    strcpy(contato2->nome, nome);
    tam = strlen(DDD);
    contato2->DDD = malloc(tam*sizeof(char));
    strcpy(contato2->DDD, DDD);
    tam = strlen(telefone);
    contato2->telefone = malloc(tam*sizeof(char));
    strcpy(contato2->telefone, telefone);
    printf("DADOS: %s %s %s\n\n", contato2->nome,contato2->DDD, contato2->telefone);
    return ordenar_nomes(contato, contato2);
}

AGENDA* ordenar_nomes(AGENDA *lista, AGENDA *contato){ //Ordenar os contatos por nome
  
    AGENDA *q = lista;
    AGENDA *ant = q;
    if (lista == NULL){
        contato->prox = NULL;
        return contato;
    }
    if (contato->nome[0] <= q->nome[0]){
        contato->prox = q;
        return contato;
    }

   while (contato->nome[0] > q->nome[0] && q->prox != NULL){
        ant = q;
        q = q->prox;
    }

    if (contato->nome[0] > q->nome[0] && q->prox == NULL){
        q->prox = contato;
        contato->prox = NULL;
        return lista;
    }

    ant->prox = contato;
    contato->prox = q;
    return lista;
}

char* inicialiar(char* primeira){
    int i = 0;
    primeira = malloc((i+1) * sizeof(char));
    return primeira;
}



//INSERIR DADOS

void padronizar_nome(char** nome){ //Padronizar todos os nomes para começar com letras maiúsculas
    char *nome_n = (*nome);
    if(nome_n[0] >= 'a' && nome_n[0] <= 'z'){
        nome_n[0] -= 32;
    }

    for (int i = 1; nome_n[i] != '\0'; i++){
        if((nome_n[i] >= 'A' && nome_n[i] <= 'Z') && nome_n[i-1] != ' '){
            nome_n[i] += 32;
        }else if(nome_n[i-1] == ' ' && nome_n[i] >= 'a' && nome_n[i] <= 'z'){
            nome_n[i] -= 32;
        }
        
    }
}

void insere_nome(char** nome){// inserir nome do contato
    char ch;
    int i = 1;
    do{
        ch = getchar();
        if(ch != '\n'){

            (*nome) = realloc(*nome, (i + 1) * sizeof(char));
            (*nome)[i-1] = ch;
            (*nome)[i] = '\0';
            i++;
        }
    }while (ch != '\n');
    padronizar_nome(nome);//nome já é o endereço de memória da váriavel, vai dar erro se colocar o &
}

void insere_ddd(char** DDD){ //inserir DDD do contato
    char ddd;
    int i = 1;
    do{
        ddd = getchar();
        if(ddd != '\n' && i < 4){
            *DDD = realloc(*DDD, (i + 1) * sizeof(char));
            (*DDD)[i-1] = ddd;
            (*DDD)[i] = '\0';
            i++;
        }
    }while (ddd != '\n');

}

void insere_number(char** telefone){ //inserir telefone do contato
    char number;
    int i = 1;
    do{
        number = getchar();
        if(number != '\n' && i < 11){
            *telefone = realloc(*telefone, (i + 1) * sizeof(char));
            (*telefone)[i-1] = number;
            (*telefone)[i] = '\0';
            i++;
        }
    }while (number != '\n');
}
//FIM INSERIR DADOS

//IMPRIMIR CONTATO
void mostrar_contatos(AGENDA *agenda){
    system("clear||cls");
    if (agenda==NULL){
        printf("\n\n\t\t\t\tLISTA DE CONTATOS VAZIA!!!\n");
    }else{
       printf("\t\t\t\t   LISTA DE CONTATOS\n\n\n\n");

        for (AGENDA *p = agenda; p != NULL; p=p->prox){
            imprimir_contato(p);
        }
    }
    printf("\n\n\n\t\t\t    Pressione ENTER para continuar!!!\n\n");
    scanf("%*c");
    fflush(stdin);
    system("clear||cls");
}

void imprimir_contato(AGENDA* contato){
        printf("\tNome: %s\n", contato->nome);
        printf("\tNúmero: (%s) %s\n", contato->DDD, contato->telefone);
        printf("\n");
}
//FIM IMPRIMIR CONTATO

void sem_contatos(){
    printf("\n\n\t\t\t\tLISTA DE CONTATOS VAZIA!!!\n");
    printf("\n\n\n\t\t\t    Pressione ENTER para continuar!!!\n\n");
    scanf("%*c");
    fflush(stdin);
    system("clear||cls");
}

AGENDA* procura_contato(AGENDA* lista){
    AGENDA* contato = lista;
    char *nome = inicialiar(nome);
    if (lista == NULL){
        sem_contatos();
        return lista;
    }
    printf("\n\n\n\t\t\t\t\tPROCURAR CONTATO\n\n");
    printf("Insira nome do contato: ");
    insere_nome(&nome);
    while (contato != NULL){
        if (strcmp(contato->nome, nome) == 0){
            system("clear||cls");
            printf("\n\n\n\t\t\t\t\tPROCURAR CONTATO\n\n");
            imprimir_contato(contato);
            printf("\t1 - Excluir\n");
            printf("\t2 - Editar\n");
            break;
        }
        contato = contato->prox;
    }
    if (contato == NULL){
        system("clear||cls");
        printf("\n\n\t\t\t\tCONTATO NÃO ENCONTRADO!!!\n");
    }else if(strcmp(contato->nome, nome) == 0){
            int i, valida = 0;
            valida = scanf("%d%*c", &i);
            fflush(stdin);
            while (!valida || i != 1 && i!=2){
                system("clear||cls");
                imprimir_contato(contato);
                printf("\n\n\t\t\t\tInsira um valor válido\n\n");
                printf("1 - Excluir\n");
                printf("2 - Editar\n");
                valida = scanf("%d%*c", &i);
                fflush(stdin);
            }
            if (i == 1){
                lista = excluir_contato(lista, contato);
                system("clear||cls");
                printf("\n\n\t\t\t\tCONTATO EXCLUÍDO!!!\n"); 
            }else if(i==2){
                
            }
        }
    printf("\n\n\n\t\t\t    Pressione ENTER para continuar!!!\n\n");
    scanf("%*c");
    fflush(stdin);
    system("clear||cls");
    return lista;
}


AGENDA* excluir_contato(AGENDA* lista, AGENDA* contato){
    AGENDA *procura = lista;
    if (procura == contato){
        return procura->prox;
    }
    
    while(procura->prox != contato){
        procura = procura->prox;
    }
    procura->prox = contato->prox;
    return lista;
}
