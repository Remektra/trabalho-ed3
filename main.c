#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false = 0, true} bool;

struct Cabecalho{
    bool status; // consistência do arquivo de dados, '0' => arquivo de dados está inconsistente ou ‘1’=> arquivo de dados está consistente.
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
//struct Dados lerCsv( FILE *fp); FAZER DPS PQ AINDA NAO SABEMOS LER CSV

int main()
{
    struct No *origem;
    origem == NULL;
    struct No *fim;
    FILE *arquivo;
    arquivo = fopen("conjuntoDados.csv","r");

    return 0; EXIT_SUCCESS;
}
int inserirLista(struct No **origem,struct No **fim,struct Dados dado){
    struct No *novo = calloc(1,sizeof(struct No));
    novo->dados = dado;
    if(*origem == NULL){
        *origem = novo;
    }else{
        *fim;
    }
}
/*struct Dados lerCsv(FILE *fp){

    struct Dados aux;
    if(fscanf(fp, "%[^,]%c%[^,]%"c%d%"c%[^,]%"c%[^,]%"c"))
        return aux;

}
    char teste1[100];
    char teste2[100];
    char teste3[100];
    char teste4[100];
    char teste5[100];
    char teste6[100];

    char teste7[100];
    char teste8[100];
    char teste9[100];
    char teste10[100];
    char teste11[100];
    int teste;
    
    fscanf(arquivo,"%[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^,]%*c %[^\n]",teste1,teste2,teste3,teste4,teste5,teste6);
    fscanf(arquivo,"%[^,]%*c %[^,]", nome, sobrenome); [^,] -> le todo mundo antes da virgula %*c le a virgula e descarta a letiura (*) ler proximo campo
    printf("%s e %s e %s e %s e %s e %s\n",teste1,teste2,teste3,teste4,teste5,teste6);
    fscanf(arquivo,"%[^,]%*c %[^,]%*c %d%*c %[^,]%*c %[^,]%*c %[^\n]",teste7,teste8,&teste,teste9,teste10,teste11);
    printf("%s e %d e %s e %s e %s e %s\n",teste7,teste,teste8,teste9,teste10,teste11);

*/
