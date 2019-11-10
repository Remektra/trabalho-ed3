/* George Gantus - 10691988 */
/* Renata Brito -  10373663 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(){
    struct NoCidades *inicio = NULL; // Inicia o ponteiro para a lista das cidades como NULL.
    struct Dados aux; // Uma struct auxiliar de dados do arquivo que usaremos em algumas funções.
    int opt; // Opção do switch case.
    char nomeArqGer[50]; // Char para obter o nome do arquivo que deseja gerar.
    char nomeCampo[50] = ""; // Char para obter o nome do campo do registro em algumas funções.
    char valor[50] = ""; // Char para obter um valor, usaremos em algumas funções. 
    int distancia = -1;
    int loop_fun = 0; // loop para algumas funções que foi solocitado para executação N vezes.
    int check = 1; // variavel para verificar a situação de alguns casos. (0,1)
    char nome_arq_csv[50]; // Char que recebe o nome do arquivo CSV no run,codes.
    int RRN; // Número relativo de registro.
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
        scanf("%d",&loop_fun);
        while (loop_fun!=0)
        {
            scanf("%s",nomeCampo);
            if(!strcmp(nomeCampo,"distancia")){
                scanf("%d",&distancia);
            }else{
                scan_quote_string(valor);
            }
            check = procuraRegistro(nomeCampo,nomeArqGer,valor,distancia,0);
            loop_fun--;
        }
        if(check != 0 && loop_fun == 0){
            atualizaArestas(nomeArqGer,&inicio);
            binarioNaTela1(nomeArqGer);
        }
        break;
    case 6:
        scanf("%s",nomeArqGer);
        scanf("%d",&loop_fun);
        while (loop_fun!=0)
        {
            scan_quote_string(aux.estadoOrigem);
            scan_quote_string(aux.estadoDestino);
            scanf("%d",&aux.distancia);
            scan_quote_string(aux.cidadeOrigem);
            scan_quote_string(aux.cidadeDestino);
            scan_quote_string(aux.tempoViagem);
            adicionaRegistro(aux,nomeArqGer);

            loop_fun--;
        }
        if(check != 0 && loop_fun == 0){
            atualizaArestas(nomeArqGer,&inicio);
            binarioNaTela1(nomeArqGer);
        }
        break;
    case 7:
        scanf("%s",nomeArqGer);
        scanf("%d",&loop_fun);
        for(int i = 0;i < loop_fun;i++){
            scanf("%d",&RRN);
            scanf("%s",nomeCampo);
            if(!strcmp(nomeCampo,"distancia")){
                scanf("%d",&distancia);
            }else{
                scan_quote_string(valor);
            }
            check = attRegistroPorRRN(nomeArqGer,RRN,nomeCampo,valor,distancia);
            if(check == 0){
                break;
            }
        }
            if(check != 0){
            atualizaArestas(nomeArqGer,&inicio);
            binarioNaTela1(nomeArqGer);
            }
        break;
    case 8:
        scanf("%s",nome_arq_csv);
        scanf("%s",nomeArqGer); 
        check = comprimirArquivo(nome_arq_csv,nomeArqGer);
        if(check != 0){
            binarioNaTela1(nomeArqGer); 
        }
        break;
    }
    free(inicio);
    return 0;
}
