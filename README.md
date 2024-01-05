# Diario-Pessoal

**Universidade Federal do Rio de Janeiro**

**Trabalho**: Diário Pessoal de Registros em linguagem C.

**Disciplina**: Programação de Computadores II.

**Alunos**: 
* Matheus Magalhães Nascimento Silva (DRE: 123504503); 
* Vitor Hugo Guerra Guimarães de Sousa (DRE: 123600066); 
* Kaique Fabricio Eufrásio (DRE: 123228961);
* Francisco Theodoro Arantes Florencio (DRE: 123099825).

**Data**: 5 de dezembro de 2023.

---
## **Problemática abordada pelo grupo:**
  A problemática abordada pelo grupo se resume à necessidade (ou
vontade) que muitas pessoas têm de registrar experiências e eventos
significativos vividos, mas que, por conta da falta de tempo e/ou organização
causada(s) pela rotina exaustiva que muitos vivem, ou mesmo pela falta de
praticidade dos métodos tradicionais de escrita, acabam por não registrá-los,
perdendo assim a oportunidade de visitá-los posteriormente e refletir sobre
eventos passados.

---
## **Projeto de solução:**
  A fim de solucionar a problemática, o grupo idealizou um Diário Pessoal
de Registros. Nele, o usuário poderá criar registros diários, editá-los ou
visitá-los, quando bem entender. Com acesso pelo terminal, o programa é
simples e minimalista, oferecendo uma experiência dinâmica e funcional.
Como requisitos funcionais, o grupo estabeleceu: a necessidade de se
utilizar uma senha pessoal para o usuário poder utilizar o programa, a fim de
proteger seus próprios dados e registros, para que outros usuários não possam
acessá-los livremente; o programa deve permitir a criação de novos registros e a
edição e visualização de registros passados.

---
## **Fluxograma da solução viabilizada:**
[Link do Fluxograma](https://modeler.cloud.camunda.io/share/c6463f7b-349c-4cd3-88e1-8fdd9da7fb0c)

---
## **Como ocorreu a implementação?**
  Para implementar a solução através de um programa em C, o grupo sabia
que iria precisar de diversas funções auxiliares, como: funções para manipular a
lista ligada, funções para criação e validação de senha, funções para receber e
estrutura as datas, entre outras. Sendo assim, para tornar o código mais
organizado e legível, os integrantes concordaram em uma implementação das
funções auxiliares através de bibliotecas, de modo que no programa principal
elas fossem apenas incluídas. As bibliotecas desenvolvidas foram: **senha.h,
lista.h e functions.h**.

---
  A biblioteca **senha.h** contempla todas as funções necessárias para a
implementação da senha, desde a criação de uma nova senha à verificação ou
alteração da senha atual. No entanto, na biblioteca implementada, a senha não é
criptografada, ela é somente gravada em um arquivo binário. As funções
presentes em **senha.h** são:

* `void salvarSenha(char *senha)`: Função usada para abrir (ou criar,
caso não exista) o arquivo binário e gravar a senha, recebida como um
ponteiro char no argumento, no arquivo.
* `void lerSenha(char *senha)`: Abre o arquivo binário da senha e lê a
senha gravada nele.
* `void atualizarSenha()`: Abre o arquivo binário de senha, valida o
acesso do usuário (ao pedir a senha atual como confirmação) e, ao validar,
pede a nova senha e grava ela no arquivo, substituindo a anterior.

  A biblioteca **lista.h** contém todas as funções implementadas para a
criação e manipulação da lista ligada utilizada no programa principal, e suas
funções foram baseadas nos slides de lista ligada da Profa. Giseli Rabello. As
funções e estruturas de dados presentes em **lista.h** são:

* `typedef int bool`: Define um tipo de dado int booleano.
* `typedef struct DATA`: Estrutura que guarda datas, composta por dia,
mês e ano.
* `typedef struct REGISTRO`: Estrutura de dados que armazena uma
data.
* `typedef struct ELEMENTO`: Estrutura de dados que representa o
elemento da lista. Contém um elemento de tipo registro e um ponteiro que
aponta para o próximo elemento da lista.
*  `typedef ELEMENTO* PONT`: Ponteiro de elementos.
*  `typedef struct LISTA`: Estrutura que implementa a lista. Contém dois
PONTS: um para o início e um para o fim.
* `void inicializarLista(LISTA* l)`: Inicializa a lista vazia.
* `int tamanho(LISTA* l)`: Retorna o tamanho da lista.
* `void limparLista(LISTA* lista)`: Apaga todos os elementos da
lista.
* `void exibirLista(LISTA* l)`: Exibe todos os elementos da lista.
* `void removerElemento(LISTA* lista, DATA data)`: Remove
um elemento específico, especificado pela data.
* `void reinicializarLista(LISTA* l)`: Reinicializa a lista, fazendo
com que ela aponte para o início novamente.
* `bool buscarData(LISTA* l, int dia, int mes, int ano)`:
Busca uma data específica na lista. Retorna True caso encontre o elemento, e
False caso contrário.
* `bool inserirElemento(LISTA* l, DATA data)`: Insere um novo
elemento na lista.
* `void salvarEmArquivo(LISTA* l)`: Salva a lista no arquivo binário
do índice.
* `int compararDatas(DATA data1, DATA data2)`: Compara as
duas datas recebidas como parâmetro.
* `void trocarDatas(DATA* data1, DATA* data2)`: Troca as duas
datas fornecidas entre si na lista.
* `int particionar(DATA* arrayData, int baixo, int
alto)`: Particiona o array de datas para o algoritmo de quicksort.
* `void popularListaDeArquivo(LISTA* l)`: Preenche a lista com as
datas presentes no arquivo índice.
* `void editarLista(LISTA* l)`: Edita uma data específica presente na
lista.
* `void ordenarRapido(DATA* arrayData, int baixo, int
alto)`: Algoritmo de quicksort para ordenar a lista.
* `void ordenarLista(LISTA *l)`: Converte a lista para um array e o
ordena.

  A biblioteca **functions.h** tem as funções necessárias para: validar a data
recebida pelo usuário; criar um diretório para armazenar os arquivos de texto;
gravar o registro no seu respectivo arquivo; adicionar mais texto ao final de um
registro já existente. As funções presentes nesta biblioteca, bem como os
#defines, são:

* `#define MAX_TAMANHO 200`: Define um tamanho máximo para o nome
dos arquivos que serão criados.
*  `#define ANSI_COLOR_BLUE “\x1b[34m”`: Define a cor azul utilizada
para determinados textos do menu principal.
* `#define ANSI_COLOR_RESET “\x1b[0m”`: Define a cor padrão
(cinza) utilizada para determinados textos do menu principal.
* `#define ANSI_COLOR_RED “\x1b[31m”`: Define a cor vermelha
utilizada para determinados textos do menu principal.
* `const char *nome_diretorio = “ArquivosUsuario”`: Define
um nome constante para a pasta onde os arquivos dos registros do usuário
serão armazenados.
* `int validarData(DATA* data)`: Verifica se a data inserida pelo
usuário é válida. Por exemplo, verifica se, em um ano bissexto, no mês de
fevereiro, o dia inserido está entre 1 e 29.
* `void criaDiretorio()`: Cria um diretório para armazenar os arquivos
de registros. O diretório tem o nome definido pelo const char explicado
anteriormente.
* `void gravarTextoNoArquivo(char *texto, const char
*nome_diretorio, DATA data)`: Recebe como argumento: o texto do
registro; nome do diretório do arquivo do registro; data do registro. A partir
disso, grava o texto no arquivo.
* `void adcionaTextoNoArquivo(char *texto, const char
*nome_diretorio, DATA data)`: Bem similar à função de gravar
texto. No entanto, ao invés de gravar um texto no início, ela adiciona um texto
novo no final do texto já gravado no arquivo.

  Por último, com quase todas as funções principais e auxiliares necessárias
implementadas em suas respectivas bibliotecas, na **main.c** o grupo teve apenas o
trabalho de organizar as chamadas das funções, implementar algumas outras
poucas funções (que utilizam as já estabelecidas nas bibliotecas mencionadas
anteriormente), a impressão do menu e de aspectos visuais. As funções de
**main.c**, bem como seus #defines são:
* `#define TAMANHO_MAX_SENHA 50`: Define um tamanho máximo para a
senha.
* `#define MAX_TAMANHO 200`: Define um tamanho mínimo para o nome
do diretório dos arquivos.
* `#define MAX_TAMANHO_ENT 4000`: Define um tamanho máximo para
as entradas.
* `void adicionarEntrada(LISTA *lista)`: Adiciona uma entrada à
lista.
* `void editarEntrada(LISTA *lista)`: Edita uma entrada
específica da lista.
* `void LerEntradaPorData(LISTA *lista)`: Imprime uma entrada,
relativa à data inserida, da lista.
* `void listarEntradasPorDatas(LISTA *lista)`: Lista todas as
datas presentes na lista.
* `int main()`: Função principal do programa. Implementa todas as
funcionalidades do programa como documentado no arquivo **main.c**.

  Com todas as funções explicadas, se faz válido detalhar o processo que
envolve a lista ligada (parte principal do programa, inerente à toda a lógica
implementada) durante a execução do programa.
Primeiramente, ao iniciar, o programa tenta fazer a leitura de um arquivo
de nome "index.bin" no diretório principal. A finalidade deste arquivo é
justamente servir como um índice de todas as entradas salvas do programa.
Sendo assim, se o arquivo já existir, a função `popularListaDeArquivo`
é executada e a lista é preenchida com os valores presentes no "*index.bin*".

  Se o arquivo não existir, o programa começa a funcionar com a lista vazia
e, conforme o usuário adiciona, altera ou exclui novas entradas, ela é atualizada.
Neste caso, o arquivo só é criado quando o usuário escolhe a opção [6], no
menu principal, "Salvar e sair". Quando isso acontece, é gravado nele (arquivo
do índice) os elementos presentes na lista através da função `salvarEmArquivo`.

  Com a principal lógica detalhada, é necessário agora explicar a lógica da
senha. O programa, sempre que iniciado, busca pelo arquivo binário
"*senha.bin*", que armazena a lista, através da função fopen, no modo de leitura
binária ("`rb`"). Caso este arquivo não consiga ser aberto pelo programa,
significa que ele não existe, e por conseguinte, é a primeira vez que o usuário
acessa o programa. Sendo assim, o programa criará o arquivo binário
"*senha.bin*" e solicitará ao usuário a criação de uma senha de acesso, que será
gravada no arquivo binário, tudo isso com o uso da função `void
salvarSenha`. A partir disso, como foi dito anteriormente, em toda execução
o programa procurará o arquivo binário e, agora que a senha já foi
implementada, ele encontrará. Com isso, ele abrirá o menu inicial. Para que o
usuário tenha acesso ao menu principal (depois do inicial), ele precisará digitar
sua senha. O programa verificará, através da função `void lerSenha`, se a
senha inserida pelo usuário é igual à senha presente no "*senha.bin*" aberto. Se
for, validará o acesso ao menu principal, senão, retornará ao menu inicial.

  A senha pode ainda ser alterada, caso seja vontade do usuário. Para tal,
ele deverá escolher esta opção no menu inicial. Para alterar a senha, o programa
solicitará, primeiramente, que o usuário insira a sua senha atual, a fim de
verificar que se trata do usuário, e não um terceiro tentando modificar a senha
do usuário. Se a senha inserida pelo usuário for igual à senha do "*senha.bin*", o
programa validará e solicitará, agora, a criação de uma nova senha. Quando o
usuário digitá-la e confirmá-la, o arquivo apagará a senha antiga de "*senha.bin*",
e irá gravar a nova senha no mesmo arquivo. Tudo isso ocorrerá com o uso da
função `void atualizarSenha`.

---
## **Casos de testes projetados após a implementação do programa:**

  Após todo o processo de produção do programa, com o código final
pronto, foi hora de testá-lo. Para isso, o grupo estabeleceu uma bateria de testes
que contemplavam todos os cenários possíveis de utilização por parte do
usuário, e por conseguinte, denunciariam quaisquer erros existentes no código
final.

  Abaixo, segue a tabela dos testes, contendo o teste, sua descrição e o seu
respectivo resultado esperado:

Teste | Descrição | Resultado Esperado
: --- : |  : ---- : | : --- : 
1º | Compilar o arquivo principal **main.c** | Arquivo compilado, sem erros ou avisos.















