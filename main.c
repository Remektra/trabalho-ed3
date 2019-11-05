/* George Gantus - 10691988 */
/* Renata Brito -  10373663 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

int main(){
    struct NoCidades *inicio = NULL;
    struct Dados aux;
    int opt;
    char nomeArqGer[50];
    char nomeCampo[50];
    char valor[50] = "";
    int distancia = -1;
    int loop_fun_5 = 0;
    int loop_fun_6 = 0;
    int check5 = 1;
    int check6 = 1;
    char nome_arq_csv[50];
    int RRN;
    scanf("%d", &opt);  /* Digita o número da opção a ser considerada */

    switch (opt){
    case 1:
        scanf("%s",nome_arq_csv);
        scanf("%s",nomeArqGer);        
        CsvtoBin(nome_arq_csv,nomeArqGer,&inicio);
        break;
    case 2:
        scanf("%s",nomeArqGer);
        print_reg(nomeArqGer);
        break;
    case 3:
        scanf("%s",nomeArqGer);
        scanf("%s",nomeCampo);
        if(!strcmp(nomeCampo,"distancia")){
            scanf("%d",&distancia);
        }else{
            scan_quote_string(valor);
            //printf("%s",valor);
        }
        procuraRegistro(nomeCampo,nomeArqGer,valor,distancia,1);
        break;
    case 4:
        scanf("%s",nomeArqGer);
        scanf("%d",&RRN); 
        aux = buscaPorRRN(nomeArqGer,RRN);
        if(aux.distancia < 0){
            printf("Registro inexistente.");
        }else{
            printaRegistro(aux,RRN);
        }
        break;
    case 5:
        scanf("%s",nomeArqGer);
        scanf("%d",&loop_fun_5);
        while (loop_fun_5!=0)
        {
            scanf("%s",nomeCampo);
            //printf("%d",loop_fun_5);
            //printf("%s",nomeCampo);
            if(!strcmp(nomeCampo,"distancia")){
                scanf("%d",&distancia);
            }else{
                scan_quote_string(valor);
                //printf("%s",valor);
            }
            check5 = procuraRegistro(nomeCampo,nomeArqGer,valor,distancia,0);
            loop_fun_5--;
        }
        if(check5 != 0 && loop_fun_5 == 0){
            binarioNaTela1(nomeArqGer);
        }
        break;
    case 6:
    //preencher uma struct dados com os dados lidos do teclado e enviar para a função adiciona registro
        scanf("%s",nomeArqGer);
        scanf("%d",&loop_fun_6);
        while (loop_fun_6!=0)
        {
            scan_quote_string(aux.estadoOrigem);
            //printf("%s",aux.estadoOrigem);
            scan_quote_string(aux.estadoOrigem);
            scanf("%d",&distancia);
            scan_quote_string(aux.cidadeOrigem);
            //printf("%s",aux.cidadeOrigem);
            scan_quote_string(aux.cidadeDestino);
            scan_quote_string(aux.tempoViagem);
            adicionaRegistro(aux,nomeArqGer);

            loop_fun_6--;
        }
        if(check6 != 0 && loop_fun_6 == 0){
            binarioNaTela1(nomeArqGer);
        }
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