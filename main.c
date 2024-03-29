/* 
   Este programa funciona como um diário de registros pessoais com salvamento local dos arquivos de texto.
   O programa foi feito para o projeto final da turma de Programação de Computadores II de 2023.2.
   Neste arquivo main estão definidas e implementadas as funções que são chamadas no contexto do menu principal do programa. 
   As demais implementações de funções foram feitas nos 3 arquivos .h incluidos abaixo.
*/
#include "lista.h"
#include "senha.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAX_SENHA 50
#define MAX_TAMANHO 200
#define MAX_TAMANHO_ENT 4000

// Assinatura das funções implementadas no final da main, essas funções são usadas para o menu principal do programa.
void adicionarEntrada(LISTA *lista);
void editarEntrada(LISTA *lista);
void LerEntradaPorData(LISTA *lista);
void listarEntradasPorDatas(LISTA *lista);
void excluiArquivo(LISTA *lista);

int main(){
  FILE *ponteiroSenha;
  ponteiroSenha = fopen("senha.bin", "rb");
  int choice, k = 1;
  char *senha = (char *)malloc(50 * sizeof(char));
  char *pssw = (char *)malloc(50 * sizeof(char));
  
  char banner[] = 
        "  █████   ██████  █████ ████\n"
        " ███░░   ███░░███░░███ ░███\n"
        "░░█████ ░███████  ░███ ░███\n"
        " ░░░░███░███░░░   ░███ ░███\n"
        " ██████ ░░██████  ░░████████\n"
        "░░░░░░   ░░░░░░    ░░░░░░░░\n"
        "               ██████████   █████   █████████   ███████████   █████    ███████\n"
        "              ░░███░░░░███ ░░███   ███░░░░░███ ░░███░░░░░███ ░░███   ███░░░░░███\n"
        "               ░███   ░░███ ░███  ░███    ░███  ░███    ░███  ░███  ███     ░░███\n"
        "               ░███    ░███ ░███  ░███████████  ░██████████   ░███ ░███      ░███\n"
        "               ░███    ░███ ░███  ░███░░░░░███  ░███░░░░░███  ░███ ░███      ░███\n"
        "               ░███    ███  ░███  ░███    ░███  ░███    ░███  ░███ ░░███     ███\n"
        "               ██████████   █████ █████   █████ █████   █████ █████ ░░░███████░\n"
        "              ░░░░░░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░    ░░░░░░░\n";
  
  printf("\n");
  printf("%s", banner); // Imprime o banner na tela.
  printf("\n");

  if (!ponteiroSenha) {
    printf("Primeira vez entrando? Digite uma senha, por favor: ");
    scanf("%s", senha);
    salvarSenha(senha);
  } else {
    while (k) {
      printf("\n******** Login ********\n");
      printf("\n%s[1]%s Digite a senha.\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
      printf("%s[2]%s Mudar senha.\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
      printf("%s[3]%s Sair.\n\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
      scanf("%d", &choice);

      printf("\n");
      switch (choice) {
      case 1:
        printf("Senha: ");
        scanf("%s", senha);
        lerSenha(pssw);
        if (strcmp(senha, pssw) == 0) {
          printf("\n... Senha correta, carregando menu ...\n");
          k--;
        } else {
          printf("\nSenha incorreta! Tente novamente!\n");
        }
        break;

      case 2:
        atualizarSenha();
        break;

      case 3:
        printf("Encerrando o programa...\n");
        exit(0);
      default:
        printf("Opção inválida. Tente novamente.\n");
      }
    }
  }

  criaDiretorio();  // Função implementada no head "functions". Verifica se existe um diretório e, se não existir, cria um novo. 

  // Aqui uma lista é inicializada e alocada dinamicamente.
  LISTA *lista = (LISTA *)malloc(sizeof(LISTA));  // Alocação da lista.
  inicializarLista(lista);  // Função implementada no head "lista". Inicializa uma lista.
  popularListaDeArquivo(lista); // Função implementada no head "lista". Ler um arquivo de index binário e insere na lista. 

  while (1) {
    printf("\n******************* Menu *******************\n");
    printf("\n%s[1]%s Adicionar entrada.\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("%s[2]%s Editar entrada.\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("%s[3]%s Ler entrada (seleciona por data).\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("%s[4]%s Excluir entrada (seleciona por data).\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("%s[5]%s Listar entradas por data.\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("%s[6]%s Salvar e sair.\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("\nEscolha uma opção: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      adicionarEntrada(lista);
      break;
    case 2:
      editarEntrada(lista);
      break;
    case 3:
      LerEntradaPorData(lista);
      break;
    case 4:
      excluiArquivo(lista);
      break;
    case 5:
      listarEntradasPorDatas(lista);
      break;
    case 6:
      printf("\nEncerrando o programa...\n");
      salvarEmArquivo(lista);
      exit(0);
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  }

  return 0;
}

// Grava texto do usuário, insere a data referente ao texto na lista.
// Ordena a lista e depois salva o texto em um arquivo .txt.
void adicionarEntrada(LISTA *lista) {
    DATA *pdata = (DATA *)malloc(sizeof(DATA));
    DATA data; 
    pdata = &data;
    char texto[MAX_TAMANHO_ENT];

    printf("\nDigite a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);

    // Verifica se a data é válida.
    if((validarData(pdata)) == 0) return;

    // Verifica se existe entrada com essa data.
    if (buscarData(lista, data.dia, data.mes, data.ano)) {
        printf("\nData já ocupada.\n");
    } 
        else {
        inserirElemento(lista, data);              // Insere data na lista.
        ordenarLista(lista);                       // Ordena a lista.
        printf("\nDigite a entrada: ");
        getchar();                                 // LimponteiroSenha o buffer do teclado.
        fgets(texto, MAX_TAMANHO_ENT, stdin);      // Grava entrada na variável texto.
        gravarTextoNoArquivo(texto, nome_diretorio, data);
        printf("\nEntrada adicionada com sucesso!\n");
    }
}

// Função recebe uma data e, se existir entrada com tal data, grava texto novo no final do arquivo.
void editarEntrada(LISTA *lista) {
    // Declaração das variáveis locais da função.
    DATA *pdata = (DATA *)malloc(sizeof(DATA));
    DATA data;
    pdata = &data;
    char texto[MAX_TAMANHO_ENT];

    printf("\nDigite a data (DD MM AAAA): "); 
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano); // Salva entrada. 

    // Verifica se a data é válida.
    if((validarData(pdata)) == 0) return;

    if (buscarData(lista, data.dia, data.mes, data.ano)) { // Verifica se existe entrada com essa data.
        printf("\nDigite a entrada (sera adicionada ao final do arquivo):\n");
        getchar();                                 // Limpa o buffer do teclado.
        fgets(texto, MAX_TAMANHO_ENT, stdin);      // Grava entrada na variável texto.
        adcionaTextoNoArquivo(texto, nome_diretorio, data); // Função implementada no head "functions". Adiciona o char texto no final do arquivo.
        printf("\nEntrada adicionada ao registro anterior com sucesso!\n"); 
    } else {
        printf("\nNão existe arquivo com a data fornecida.\n");
    }
}

// Função recebe uma data e, se existir registro com ela, abre e imprime o arquivo para a leitura em tela.
void LerEntradaPorData(LISTA *lista) {
    // Declaração das variáveis locais da função.
    DATA *pdata = (DATA *)malloc(sizeof(DATA));
    DATA data;
    pdata = &data;
    char texto[MAX_TAMANHO_ENT];

    printf("\nDigite a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano); // Grava a data fornecida na variável data.
    
    if((validarData(pdata)) == 0) return; // Verifica se a data é válida
 
    if (buscarData(lista, data.dia, data.mes, data.ano)){ // Verifica se existe entrada com essa data.
        FILE *arquivoBuscado; 
        // As duas linhas seguintes adicionam o diretório "ArquivosUsuario" ao nome do arquivo para abertura correta.
        char caminhoArquivoBuscado[MAX_TAMANHO + strlen(nome_diretorio) + 15];
        sprintf(caminhoArquivoBuscado, "%s/%d_%d_%d.txt", nome_diretorio, data.dia, data.mes, data.ano);
        
        arquivoBuscado = fopen(caminhoArquivoBuscado, "r"); // Abre arquivo para leitura.
        if (arquivoBuscado == NULL) { // Verifica se a abertura foi bem sucedida. 
            printf("\nErro ao abrir o arquivo.\n");
            return;
        }

        printf("\nA entrada desse dia é:\n");

        // Ler linhas até que não haja mais para leitura.
        while (fgets(texto, sizeof(texto), arquivoBuscado) != NULL) {
            printf("%s", texto);
        }

        fclose(arquivoBuscado); }
        else {
            printf("\nNão há entrada para esta data.\n");
    }
}

// Imprime a lista atual com todas as entradas.
void listarEntradasPorDatas(LISTA *lista) { 
  if (lista->inicio == NULL) {
    printf("\nVocê não possui entradas.\n"); 
    return;
  }
  exibirLista(lista); // Função implementada no head "lista", pecorre a lista inteira e imprime na tela.
}

// Exclui uma entrada do diário a ponteiroSenhartir de uma DATA fornecida.
void excluiArquivo(LISTA *lista) {
    // Declaração das variáveis locais da função.
    DATA *pdata = (DATA *)malloc(sizeof(DATA));
    DATA data;
    pdata = &data;

    printf("\nDigite a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano); // Grava a data fornecida na variável data.

    if((validarData(pdata)) == 0) return; // Verifica se a data é válida.

    if (buscarData(lista, data.dia, data.mes, data.ano)){ // Verifica se existe entrada com essa data.
        // As duas linhas seguintes adicionam o diretório "ArquivosUsuario" ao nome do arquivo para excluir. 
        char caminhoArquivoBuscado[MAX_TAMANHO + strlen(nome_diretorio) + 15];
        sprintf(caminhoArquivoBuscado, "%s/%d_%d_%d.txt", nome_diretorio, data.dia, data.mes, data.ano);

        if (remove(caminhoArquivoBuscado) == 0) {
        removerElemento(lista, data); // Funçãao implementada no head "lista". Pocura e remove um elemento fornecido da lista.
        printf("\nArquivo excluído com sucesso.\n"); } 
        else {
        printf("\nErro ao excluir o arquivo.\n");
        } } 
        else {
        printf("\nNão há entrada para esta data.\n");
    }
}