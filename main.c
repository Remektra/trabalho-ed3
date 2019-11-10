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
    char nomeCampo[50] = "";
    char valor[50] = "";
    int distancia = -1;
    int loop_fun_5 = 0;
    int loop_fun_6 = 0;
    int loop_fun_7 = 0;
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
            if(!strcmp(nomeCampo,"distancia")){
                scanf("%d",&distancia);
            }else{
                scan_quote_string(valor);
            }
            check5 = procuraRegistro(nomeCampo,nomeArqGer,valor,distancia,0);
            loop_fun_5--;
        }
        if(check5 != 0 && loop_fun_5 == 0){
            atualizaArestas(nomeArqGer,&inicio);
            binarioNaTela1(nomeArqGer);
        }
        break;
    case 6:
        scanf("%s",nomeArqGer);
        scanf("%d",&loop_fun_6);
        while (loop_fun_6!=0)
        {
            scan_quote_string(aux.estadoOrigem);
            scan_quote_string(aux.estadoDestino);
            scanf("%d",&aux.distancia);
            scan_quote_string(aux.cidadeOrigem);
            scan_quote_string(aux.cidadeDestino);
            scan_quote_string(aux.tempoViagem);
            adicionaRegistro(aux,nomeArqGer);

            loop_fun_6--;
        }
        if(check6 != 0 && loop_fun_6 == 0){
            atualizaArestas(nomeArqGer,&inicio);
            binarioNaTela1(nomeArqGer);
        }
        break;
    case 7:
        scanf("%s",nomeArqGer);
        scanf("%d",&loop_fun_7);
        for(int i = 0;i < loop_fun_7;i++){
            scanf("%d",&RRN);
            scanf("%s",nomeCampo);
            if(!strcmp(nomeCampo,"distancia")){
                scanf("%d",&distancia);
            }else{
                scan_quote_string(valor);
            }
            check6 = attRegistroPorRRN(nomeArqGer,RRN,nomeCampo,valor,distancia);
            if(check6 == 0){
                break;
            }
        }
            if(check6 != 0){
            atualizaArestas(nomeArqGer,&inicio);
            binarioNaTela1(nomeArqGer);
            }
        break;
    case 8:
        scanf("%s",nome_arq_csv);
        scanf("%s",nomeArqGer); 
        check6 = comprimirArquivo(nome_arq_csv,nomeArqGer);
        if(check6 != 0){
            binarioNaTela1(nomeArqGer); 
        }
        break;
    }
    free(inicio);
    return 0;
}
