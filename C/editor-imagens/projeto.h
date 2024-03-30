FILE *fpin, *fpout;
int **imagem, ncol, nlin, quant_nivel_cinza;

void abrir_arquivos(void);
void ler_cabecalho(void);
void ler_imagem(void);
void gravar_cabecalho(void);
void gravar_imagem(void);
void fechar_arquivos(void);

void abrir_arquivos(void) {
   char nomeIN[50], nomeOUT[50];   
   printf("Qual o nome do arquivo que contém a imagem?\n");
   scanf("%[^\n]%*c",nomeIN);
   if ((fpin=fopen(nomeIN,"r"))==NULL){
        printf("Nao foi possivel abrir arquivo de imagem\n");
        while (fpin == NULL){
        system("clear||cls");
        printf("Verifique se o arquivo está na mesma pasta do projeto e verifique se o nome da imagem foi digitado corretamente!!!\n\n\n");
        printf("Qual o nome do arquivo que contém a imagem?\n");
        scanf("%[^\n]%*c",nomeIN);
        if ((fpin=fopen(nomeIN,"r"))==NULL) {
            printf("Nao foi possivel abrir arquivo de imagem\n");
        }
      }
   }
   printf("\nQual o nome do arquivo de saída?\n");
   scanf("%[^\n]%*c",nomeOUT);
   if ((fpout=fopen(nomeOUT,"w"))==NULL) {
        printf("Nao foi possivel abrir arquivo de saida\n");
        while (fpin == NULL){
        system("clear||cls");
        printf("\t\t\tVerifique se o nome da imagem de saída foi digitado corretamente!!!\n\n\n");
        printf("\nQual o nome do arquivo de saída?\n");
        scanf("%[^\n]%*c",nomeOUT);
        if ((fpout=fopen(nomeOUT,"w"))==NULL) {
              printf("Nao foi possivel abrir arquivo de saida\n");
        }
      }
   }
   system("clear||cls");
   printf("\n\t\t\t\tArquivos abertos com sucesso! %s %s\n\n",nomeIN, nomeOUT);
} // Fim: abrir_arquivos

void ler_imagem(void) {
  int cont, col, lin;
  imagem = (int **)malloc((nlin+1)*sizeof(int *));
  for (cont=0;cont<nlin;cont++) {
    imagem[cont]=(int *)malloc((ncol+1)*sizeof(int));
    if (imagem[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
  }
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      fscanf(fpin,"%d ",&imagem[lin][col]);
    }
  }
} // Fim: ler_imagem

void ler_cabecalho(void) {
     char controle[4];
     fscanf(fpin,"%s\n",controle);
     fscanf(fpin,"%d %d\n",&ncol,&nlin);
     fscanf(fpin,"%d\n",&quant_nivel_cinza);
} // Fim: ler_cabecalho

void fechar_arquivos(void) {
  fclose(fpin);
  fclose(fpout);
} // Fim: fechar_arquivos

void gravar_imagem(void) {
  int lin, col;
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      fprintf(fpout,"%d ",imagem[lin][col]);
    }
    fprintf(fpout,"\n");
  }
}

void gravar_cabecalho(void) {
     fprintf(fpout,"P2\n");
     fprintf(fpout,"%d %d\n",ncol,nlin);
     fprintf(fpout,"%d\n",quant_nivel_cinza);
}

void abrir_imagem(void) {
    abrir_arquivos();
    ler_cabecalho();
    ler_imagem();
}

void fechar_imagem(void) {
    gravar_cabecalho();
    gravar_imagem();
    fechar_arquivos();
}
