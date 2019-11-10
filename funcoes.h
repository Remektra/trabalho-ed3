/* George Gantus - 10691988 */
/* Renata Brito -  10373663 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ERRO 0
#define OK   1
#define TAMREGISTRO 85


/* Struct que define o registro de cabeçalho */
struct Cabecalho{
    char status; // consistência do arquivo de dados, '0' => arquivo de dados está inconsistente ou ‘1’=> arquivo de dados está consistente.
    int numeroVertices; // indica o número de cidades diferentes que estão armazenadas no arquivo de dados, 0 => nenhum registro.
    int numeroArestas; // indica o número de registros que estão armazenados no arquivo de dados, 0 => nenhum registro.
    char dataUltimaCompactacao[11]; // formato DD/MM/AAAA, ‘##/##/####’ foi carregado com dados pela primeira vez
};

/* Struct que define o registro de dados*/
/* Tamanho fixo de registro de 85 bytes.*/
struct Dados{
    int RRN; // numero relativo de registro.
    char estadoOrigem[3]; // tamanho fixo 2 bytes, o 3 é o "\0".
    char estadoDestino[3]; // tamanho fixo 2 bytes, o 3 é o "\0".
    int distancia; // tamanho fixo 4 bytes.
    char cidadeOrigem[100]; // tamanho variavel, delimitador entre campos pipe "|", lixo = "#"
    char cidadeDestino[100]; // tamanho variavel, delimitador entre campos pipe "|".
    char tempoViagem[100]; // tamanho variavel, delimitador entre campos pipe "|".
};
/* Struct que define uma lista das cidades*/
struct  NoCidades{
    char cidade[100];
    struct NoCidades *prox;
    int quantidade;
};

// Comentários de cada função esta acima da mesma.


/* Recebe o nome da cidade e a lista de cidades (struct NoCidades), e então faz a busca.
   Caso encontra retorna 1, caso não, retorna 0.
*/
int buscaCidade(char *cidade,struct NoCidades *inicio);
/* Recebe o nome da cidade e onde esta o endereço da lista de cidades (struct NoCidades), e então tenta inserir
    Caso consiga, retorna o tamanho da lista, caso não, retorna zero.
*/
int insereCidade(char *cidade,struct NoCidades **inicio);
/* Função responsável por ler o arquivo csv e escrever os dados em um arquivo binário.
*/
int CsvtoBin(char*,char*,struct NoCidades **inicio); 
/* Função responsável por escrever o cabeçalho no arquivo binário. 
*/
void escreveCabecalho(struct Cabecalho c,FILE *file);
/* Essa função foi disponibilizada para comparação no run.codes.
*/
void binarioNaTela1(char*);
/* Função responsável por ler e exibir todos os registros presentes no arquivo binário.
*/
int print_reg(char*); 
/* Essa função é responsavel por ler um registro do arquivo binario
    Para que possamos ter o acesso dos dados em uma struct (Dados).
*/
void lerRegistro(FILE *file,struct Dados *r);
/* Função responsavel por ler um campo string delimitado entre aspas (").
   Foi disponibilizada tambem.
*/
void scan_quote_string(char *str);
/*Procura todos os registros que satisfazem um criterio de busca e os imprime ou os exclui dependendo do parametro opr
se opr == 1 imprime senao apaga(coloca *)
*/
int procuraRegistro(char *campo,char *nomeArq,char *valor, int dist,int opr);
/* Função responsável por ler o cabeçalho do arquivo binario e retorna-lo na struct Cabecalho.
*/
struct Cabecalho leCabecalho(FILE *file);
/*Função responsável por ler ate o delimitador de tamanho do campo.
*/
void lerAtePipe(char*,FILE*); 
/* Função responsável por adiciona um novo registro no arquivo binário se maneira estática.
    Retorna o tamanho da lista ou zero se nao foi possivel inserir.
*/
int adicionaRegistro(struct Dados dados,char *nomeArq);
/* Função responsável por encontrar um registro no arquivo binário por meio do seu RRN.
    Um registro não existe se não houver uma distância entre a cidade de origem e cidade destino,
    Caso exista ira retornar a struct com o registro encontrado.
*/
struct Dados buscaPorRRN(char *nomeArquivo,int RRN);
/* Função responsável por exibir um registro. 
*/
void printaRegistro(struct Dados registro,int RRN);
/* Função responsavel por verificar a quantidade de arestas do arquivo de dados binário.
*/
int atualizaArestas(char *nomeArq, struct NoCidades **inicio);
/* Função reponsável por atualizar um registro do arquivo binário, 
    passando seu RRN, o nome do campo e oque deseja inserir.
*/
int attRegistroPorRRN(char *nomeArq,int rrn,char *campo, char *valor,int distancia);
/* Função responsável por escrever um registro no arquivo binário,
    Ela por si, necessitará do registro já criado.
*/
void insereRegistroBin(struct Dados dado,FILE *file,int update);
/* Função responsável por escrever um novo arquivo binário sem os dados dos registros excluidos.   
    Fazendo assim uma compactação do arquivo.
*/
int comprimirArquivo(char *nomeArq,char *Comprimido);


