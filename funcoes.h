/* George Gantus - 10691988 */
/* Renata Brito -  10373663 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ERRO 0
#define OK   1
#define TAMREGISTRO 85


typedef enum { false = 0, true} bool;

struct Cabecalho{
    char status; // consistência do arquivo de dados, '0' => arquivo de dados está inconsistente ou ‘1’=> arquivo de dados está consistente.
    int numeroVertices; // indica o número de cidades diferentes que estão armazenadas no arquivo de dados, 0 => nenhum registro.
    int numeroArestas; // indica o número de registros que estão armazenados no arquivo de dados, 0 => nenhum registro.
    char dataUltimaCompactacao[11]; // formato DD/MM/AAAA, ‘00/00/0000’ foi carregado com dados pela primeira vez
};

// Tamanho fixo de registro de 85 bytes.
struct Dados{
    int RRN; // numero relativo de registro.
    bool removido;
    char estadoOrigem[3]; // tamanho fixo 2 bytes, o 3 é o "\0".
    char estadoDestino[3]; // tamanho fixo 2 bytes, o 3 é o "\0".
    int distancia; // tamanho fixo 4 bytes.
    char cidadeOrigem[100]; // tamanho variavel, delimitador entre campos pipe "|", lixo = "#"
    char cidadeDestino[100]; // tamanho variavel, delimitador entre campos pipe "|".
    char tempoViagem[100]; // tamanho variavel, delimitador entre campos pipe "|".
};
struct  NoCidades{
    char cidade[100];
    struct NoCidades *prox;
};
int buscaCidade(char *cidade,struct NoCidades *inicio);//retorna 0 se nao achou e 1 se achou
int insereCidade(char *cidade,struct NoCidades **inicio);//retorna o tamanho da lista ou zero se nao foi possivel inserir
int CsvtoBin(char*,char*,struct NoCidades **inicio); // Função que lê do arquivo CSV e gera um arquivo binário
void binarioNaTela1(char*); 
void lerAtePipe(char*,FILE*); // Função responsável por ler ate o delimitador de tamanho do campo
int print_reg(char*); // Função responsável por ler e exibir todos os registros presentes no arquivo binário 
void printaCabecalho();//Apenas para testes
struct Dados buscaPorRRN(char *nomeArquivo,int RRN);//retorna o registro ou distancia negativa se nao foi encontrado
void printaRegistro(struct Dados registro,int RRN);
struct Cabecalho leCabecalho(FILE *file);
//Procura todos os registros que satisfazem um criterio de busca e os imprime ou os exclui dependendo do parametro opr
//se opr == 1 imprime senao apaga(coloca *)
int procuraRegistro(char *campo,char *nomeArq,char *valor, int dist,int opr);
int adicionaRegistro(struct Dados dados,char *nomeArq);//
void scan_quote_string(char *str);