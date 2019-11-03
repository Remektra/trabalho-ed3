/* George Gantus - 10691988 */
/* Renata Brito -  10373663 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

int main(){
    int opt;
    char nomeArqGer[50];
    char nome_arq_csv[50];
    scanf("%d", &opt);  /* Digita o número da opção a ser considerada */

    switch (opt){
    case 1:
        scanf("%s",nome_arq_csv);
        scanf("%s",nomeArqGer);        
        CsvtoBin(nome_arq_csv,nomeArqGer);
        binarioNaTela1("arquivoGerado.bin");
        //CsvtoBin(csv,bin);
        break;
    case 2:
        scanf("%s",nomeArqGer);
        print_reg(nomeArqGer);
        //bin = fopen("arquivoGerado.bin","rb");
        //print_reg(bin);
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    }

    return 0;
}


























/* int inserirLista(struct No **origem,struct No **fim,struct Dados dado){//função que insere os elementos lidos na lista encadeada
    struct No *novo = calloc(1,sizeof(struct No));
    if(novo == NULL){
        return 0;
    }
    novo->dados = dado;
    if(*origem == NULL){
        *origem = novo;
    }else{
        (*fim)->prox = novo;
        *fim = novo;
    }
    return 1;
}*/
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




/* TO DO LIST */
/*
CsvtoBin: Terminar o cabecalho com data de ultima mnodificação atualizada no final e contador de arestas
 */