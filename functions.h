/* 
   Neste arquivo estão implementadas as funções mais gerais do programa, as quais não fazemparte nem das funções que gerenciam a lista
   nem das funções pertinentes a senha.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_TAMANHO 200

// Define as cores que serão usadas na interface do programa.
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"

const char *nome_diretorio = "ArquivosUsuario";

// Confere se a data passada como argumento é uma data válida.
int validarData(DATA* data) {
  if (data->ano < 1000 || data->ano > 3000) {  //verifica o campo ano
    printf("\nData inválida, ano deve estar entre 1000 e 3000.\n");
    return 0;
  }
  if (data->mes < 1 || data->mes > 12) { // Verifica o campo 'mes' (Esse campo é verificado novamente adiante).
    printf("\nData inválida, mês deve estar entre 1 e 12.\n");
    return 0;
  }
  if (data->dia < 1 || data->dia > 31) { // Verifica o campo 'dia'.
    printf("\nData inválida, dia deve estar entre 1 e 31.\n");
    return 0;
  }

  // Validação de dias em meses específicos de 28, 29, 30 e 31 dias.
  if ((data->mes == 4 || data->mes == 6 || data->mes == 9 || data->mes == 11) &&
      data->dia > 30) {
    printf("\nData inválida, neste mês, o máximo de dias é 30.\n");
    return 0;
  }
  if (data->mes == 2) {
    if ((data->ano % 4 == 0 && data->ano % 100 != 0) || data->ano % 400 == 0) {
      if (data->dia > 29) {
        printf("\nData inválida, Fevereiro em ano bissexto tem no máximo 29 dias.\n");
        return 0;
      }
    } else {
      if (data->dia > 28) {
        printf("\nData inválida, Fevereiro em ano não bissexto tem no máximo 28 dias.\n");
        return 0;
      }
    }
  }
  return 1; // A data é válida.
}

// Verifica se existe um diretório com o nome "ArquivosUsuario".
// Se não existir, cria o diretório.
void criaDiretorio(){
    // Verifica se o diretório existe.
    struct stat st = {0};
    if (stat(nome_diretorio, &st) == -1) {
        // Se não existe, cria o diretório.
        if (mkdir(nome_diretorio, 0700) == 0) {
            printf("\nDiretório criado com sucesso!\n");
        } else {
            printf("\nErro ao criar o diretório.\n");
        }
    } 
}

// Cria um arquivo .txt com o nome igual a data escolhida.
// Depois, a entrada fornecida é gravada no arquivo recém criado.
void gravarTextoNoArquivo(char *texto, const char *nome_diretorio, DATA data) {
  FILE *arquivo;
  char nomeArquivo[MAX_TAMANHO];

  // Criando o nome do arquivo usando os valores da estrutura de data.
  sprintf(nomeArquivo, "%d_%d_%d.txt", data.dia, data.mes, data.ano);

  // Abrindo o arquivo para escrita.
  char caminhoArquivo[MAX_TAMANHO + strlen(nome_diretorio) +
                      2]; // +2 para o '/' e o caractere nulo.
  sprintf(caminhoArquivo, "%s/%s", nome_diretorio, nomeArquivo);
  arquivo = fopen(caminhoArquivo, "w");

  if (arquivo == NULL) {
    printf("\nErro ao abrir o arquivo.\n");
    return;
  }

  // Gravando o texto no arquivo.
  fputs(texto, arquivo);

  // Fechando o arquivo.
  fclose(arquivo);
}

// Adiciona texto em um arquivo txt já criado anteriormente.
// O novo texto é adicionado no final do arquivo existente.
void adcionaTextoNoArquivo(char *texto, const char *nome_diretorio, DATA data) {
  FILE *arquivo;
  char nomeArquivo[MAX_TAMANHO];

  // Cria o nome do arquivo usando os valores da estrutura de data.
  sprintf(nomeArquivo, "%d_%d_%d.txt", data.dia, data.mes, data.ano);

  // Abrindo o arquivo para escrita no final.
  char caminhoArquivo[MAX_TAMANHO + strlen(nome_diretorio) +
                      2]; // +2 para o '/' e o caractere nulo.
  sprintf(caminhoArquivo, "%s/%s", nome_diretorio, nomeArquivo);
  arquivo = fopen(caminhoArquivo, "a");

  if (arquivo == NULL) {
    printf("\nErro ao abrir o arquivo.\n");
    return;
  }

  // Gravando o texto no arquivo.
  fputs(texto, arquivo);

  // Fechando o arquivo.
  fclose(arquivo);
}

