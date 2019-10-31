/* George Gantus - 10691988 */
/* Renata Brito -  10373663 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
struct No{// Ao ler os dados estes serão colocados em uma lista encadeada
    struct Dados dados;
    struct Dados *prox;
};