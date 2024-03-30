#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "projeto.h"
/*– Rotação de 90 graus
– rotação de -90 graus
– Inversão horizontal
– Inversão vertical
– Negativo
– Aumento de brilho
– Diminuição de brilho
– Detecção e redução de ruidos 2D e 3D
– Encerrar*/

//função para encerramento de ação
void sucess(void){
  system("clear||cls"); 
  printf("\n\n\n\n\n\n\t\t\t  Arquivo Criado com sucesso, verifique sua pasta!! \n\n");
  sleep(3);
  system("clear||cls");
}

int main(void) {
  int lin = 0, col = 0, new_lin = 0, new_col = 0, brilho = 0, tam = 0;
  char opcao[100];
  do{
    //exibir menu para o usuário
    do{
      printf("\n\t================================================================");
      printf("\n\t\t\t\t AROUCA-PHOTOEDITS \n");
      printf("\t================================================================\n");
      printf("\n\t\t-------------------------------------------------");
      printf("\n\t\t|\t1 - Rotacao de 90 graus\t\t\t |");
      printf("\n\t\t|\t2 - Rotacao de -90 graus\t\t |");
      printf("\n\t\t|\t3 - Inversao horizontal\t\t\t |");
      printf("\n\t\t|\t4 - Inversao vertical\t\t\t |");
      printf("\n\t\t|\t5 - Negativo\t\t\t\t |");
      printf("\n\t\t|\t6 - Aumentar brilho\t\t\t |");
      printf("\n\t\t|\t7 - Diminuir brilho\t\t\t |");
      printf("\n\t\t|\t8 - Deteccao e reducao de ruidos 2D\t |");
      printf("\n\t\t|\t\t\t\t\t\t |");
      printf("\n\t\t|\t0 - Encerrar\t\t\t\t |");
      printf("\n\t\t-------------------------------------------------");
      printf("\n\n\tEscolha uma opcao: ");
      scanf("%99[^\n]%*c", opcao);
      
      //validação de entrada para opção
      for (tam = 0; opcao[tam] != '\0'; tam++){ //verifica quantos caracteres foram digitados
        if ( (int) opcao[0] < 48 || (int) opcao[0] > 56){ //Se maior que 1, então insere mensagem
          system("clear||cls");
          printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t-------------------------------------\n");
          printf("\t\t\t\t\t| Opcao invalida, insira uma correta |\n");       
          printf("\t\t\t\t\t-------------------------------------\n");
          sleep(2);
          system("clear||cls");
          break;
        }else if(tam>1){
          system("clear||cls");
          printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t-------------------------------------\n");
          printf("\t\t\t\t\t| Opcao invalida, insira uma correta |\n");       
          printf("\t\t\t\t\t-------------------------------------\n");
          sleep(2);
          system("clear||cls");
          break;
          }
      }
    } while (tam!=1 || (int) opcao[0] < 48 || (int) opcao[0] > 56);
    
    //executar acao com base na escolha do usuario
    switch (opcao[0]){

    case '1':{
      // Rotacionar a imagem para +90 graus
      abrir_imagem();
      int n_imagem[nlin][ncol];
      for( lin = 0; lin < nlin; lin++){
        for( col = 0; col < ncol; col++){
          n_imagem[lin][col] = imagem[lin][col]; 
          // inserir valores da imagem na matriz auxiliar para não sobreescrever e danificar a imagem
        }
      }
      for (lin = 0; lin < nlin; lin++){
        for (col = 0; col < ncol; col++){
          new_lin = col;
          new_col = nlin - lin - 1; //para inverter os pixels das linhas
          imagem[new_lin][new_col] = n_imagem[lin][col]; //atribuicao dos pixels rotacionados
        }
      }

      fechar_imagem();
      sucess();
      }
      break;

    case '2':{
      // Rotacionar a imagem para -90 graus
      abrir_imagem();
      int n_imagem[nlin][ncol];     //declaração de matriz auxiliar
      for( lin = 0; lin < nlin; lin++){
        for( col = 0; col < ncol; col++){
          n_imagem[lin][col] = imagem[lin][col]; 
          // inserir valores da imagem na matriz auxiliar para nao sobreescrever e danificar a imagem
        }
      }

      for( lin = 0; lin < nlin; lin++){
        for ( col = 0; col < ncol; col++){
          new_lin = ncol - col - 1;  //para inverter os pixels das colunas
          new_col = lin;
          imagem[new_lin][new_col] = n_imagem[lin][col]; //atribuicao dos pixels das colunas que serao invertidos
        }
      }
      fechar_imagem();
      sucess();
      break;
}

    case '3':{
      //inversao horizontal
      abrir_imagem();
      for(lin = 0; lin < nlin - 1; lin++){ //Usado para acessar todos os elementos da matriz
      for (col = 0; col < ncol/2; col++){
        int aux = imagem[lin][col]; //variavel auxiliar para receber valor do elemento que sera trocado
        imagem[lin][col] = imagem[lin][ncol - col - 1]; //irá inverter os elementos da coluna em analise
        imagem[lin][ncol - col - 1] = aux; //atribuicao de um novo valor para a coluna invertida
    }
  }
      fechar_imagem();
      sucess();
      break;
}

    case '4':{
      //inversao vertical
      abrir_imagem();
      for(lin = 0; lin < nlin/2; lin++){//Usado para acessar todos os elementos da matriz
      for (col = 0; col < ncol -1; col++){
        int aux = imagem[lin][col]; //variavel auxiliar para receber valor do elemento que sera trocado
        imagem[lin][col] = imagem[nlin - lin - 1][col]; //inverter elementos da linha
        imagem[nlin - lin - 1][col] = aux;  //atribuicao de um novo valor para a linha invertida
        }
      }
      fechar_imagem();
      sucess();
      break;
}

    case '5':
      //negativar imagem
      abrir_imagem();
      for ( lin=0;lin<nlin;lin++) {//Usado para acessar todos os elementos da matriz
        for (col=0;col<ncol;col++) {
            imagem[lin][col] = quant_nivel_cinza - imagem[lin][col];   //pixel máximo - valor do elemento em analise
    }
  }
      fechar_imagem();
      sucess();
      break;

    case '6':{
      //aumentar brilho
      int retorno = 1;
      abrir_imagem();
      system("clear||cls");
      printf("\n\t\t\t\t Aumentar Brilho \n\n\n\n");
      printf("Insira a porcentagem do brilho(0-100): ");
      retorno = scanf("%d", &brilho);
      scanf("%*c");
      
      while ((retorno == 0) || (brilho>100||brilho<0)){ //validação de entrada
        system("clear||cls");
        printf("\n\n\t\t\t\tVALOR INVÁLIDO\n\n");
        printf("\n\t\t\t\t Aumentar Brilho \n\n\n\n");
        printf("Insira a porcentagem do brilho(0-100): ");
        retorno = scanf("%d", &brilho);
        scanf("%*c");
      }

      brilho = (quant_nivel_cinza/100.0) * brilho; //porcentagem brilho

      //for para percorrer os elementos da imagem e aumentar brilho
      for (lin = 0; lin < nlin; lin++){
        for (col = 0; col < ncol; col++){
          imagem[lin][col] = imagem[lin][col] + brilho;
          imagem[lin][col] = imagem[lin][col] > quant_nivel_cinza ? quant_nivel_cinza:imagem[lin][col];
        }
      }
      fechar_imagem();
      sucess();
      break;
    }
    case '7':{
      //Diminuir brilho
      int retorno = 1;
      abrir_imagem();
      system("clear||cls");
      printf("\n\t\t\t\t Diminuir Brilho \n\n\n\n");
      printf("Insira a porcentagem do brilho(0-100): ");
      retorno = scanf("%d", &brilho);
      scanf("%*c");
      
      while ((retorno == 0) || (brilho>100||brilho<0)){ //validação de entrada
        system("clear||cls");
        printf("\n\n\t\t\t\t\tVALOR INVÁLIDO\n\n");
        printf("\n\t\t\t\t Diminuir Brilho \n\n\n\n");
        printf("Insira a porcentagem do brilho(0-100): ");
        retorno = scanf("%d", &brilho);
        scanf("%*c");
      }

      brilho = (quant_nivel_cinza/100.0) * brilho; //porcentagem brilho

      for (lin = 0; lin < nlin; lin++){ //usado para acessar todos os elementos da matriz
        for (col = 0; col < ncol; col++)
        {
          imagem[lin][col] -= brilho; //diminuir o brilho
          imagem[lin][col] = imagem[lin][col] < 0 ? 0:imagem[lin][col]; // Validação de valor para o elemento da imagem
        }
      }

      fechar_imagem();
      sucess();
      break;
    }
      case '8':{
        int retorno=1, limite = 0, diferenca = 0, max_lin = 0, max_col = 0, fixo = 0;
        float media = 0, q_vizinhos = 0;

        abrir_imagem();
        system("clear||cls");
        printf("\n\t\t\t\t Detecção de Ruído \n\n\n\n");
        printf("Insira o valor do ruído(0 - 255): ");
        retorno = scanf("%d", &limite);
        scanf("%*c");
        while (retorno == 0 ||(limite>quant_nivel_cinza||limite<0)){ //validação de entrada do ruído
          system("clear||cls");
          printf("\n\n\t\t\t\t\tVALOR INVÁLIDO\n\n");
          printf("\n\t\t\t\t Detecção de Ruído \n\n\n\n");
          printf("Insira o valor do ruído(0 - 255): ");
          retorno = scanf("%d", &limite);
          scanf("%*c");
        }
          //for para percorrer matriz e identificar ruido
          for (lin = 0; lin < nlin; lin++){
            for (col = 0; col < ncol; col++){
              diferenca = media = q_vizinhos = 0;

                //INICIO (condicionais para não pegar lixo e os elementos não vizinhos)
                if (lin>0){ //SE o elemento estiver em uma linha diferente de 0, é certo que ele vai ter vizinhos na parte de cima, na linha da própria posição E tem a possibilidade de ter vizinhos na de baixo;
                  new_lin = lin - 1;
                  max_lin = lin + 1;
                  if (lin == nlin - 1){//Mas se o elemento estiver na última linha, ele só vai ter vizinhos na parte de cima e na linha da própria posição
                    max_lin = lin;
                  }
                }else{ //Se ele estiver na primeira linha, só vai ter vizinho na própria linha e na linha de baixo;  
                  new_lin = 0;
                  max_lin = lin + 1;
                }

                if (col > 0){ //Mesma situação da linha, ele pode ter vizinhos na sua direita, esquerda e no centro
                  fixo = new_col = col-1;
                  max_col = col + 1;
                  if (col == ncol - 1){ // Mas se ele estiver na última linha, só vai ter vizinhos no centro e na sua esquerda
                    max_col = col;
                  }
                }else{ //Se ele estiver na primeira linha, só vai ter vizinhos no centro e na sua direita
                  fixo = new_col = 0;
                  max_col = col + 1;
                }
                //OBS: new e max, serão utilizados no for seguinte
                //new é para a posição "minima" dos vizinhos
                //max é para identificar até qual posição tem os vizinhos
                //ex: elemento 00, posição dos vizinhos[01,10,11] o limite é max_linha = 1, max coluna = 1, new_coluna = 0 e new_linha = 0
                //FIM DOS CONDICIONAIS

                for (; new_lin <= max_lin; new_lin++){ //For para percorrer as linhas dos vizinhos, não tem inicialização no for pq cada elemento pode ter um max diferente, ele será inicializado sempre nos condicionais acima
                  new_col = fixo;
                  for (; new_col <= max_col; new_col++){//Percorrer os elementos da coluna, também não está inicializada. Variavel fixo serve para lembrar da posição minima dos vizinhos quando formos para a próxima linha
                    if (new_lin == lin && new_col == col){ //se estiver na mesma cordenada do elemento em análise, irá saltar para o próximo elemento da linha
                      continue;
                    }
                    media+=imagem[new_lin][new_col];
                    q_vizinhos++;
                  }
                }
                q_vizinhos = (q_vizinhos == 3) ? 0.333: (q_vizinhos == 5) ? 0.2: 0.125;
                media *= q_vizinhos;
                diferenca = (int) media - imagem[lin][col]; //calcular diferença da media para o elemento
                diferenca = (diferenca < 0) ? diferenca * -1: diferenca;
                if(diferenca > limite){ //teste efetuado para identificar ruido e substituir o valor pela media dos seus vizinhos
                  imagem[lin][col] = (int) media;
                }
            }
        }
      }
      fechar_imagem();
      sucess();
      break;
    default:
      //mensagem de encerramento
      system("clear||cls");
      printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t----------------\n");
      printf("\t\t\t\t\t| Volte sempre |\n");       
      printf("\t\t\t\t\t----------------\n");
      printf("\n\n\n\n\n\n\n\n\n");
      break;
    }
  } while (opcao[0]!='0');
  return 0;
}
