/* George Gantus - 10691988 */
/* Renata Brito -  10373663 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#define TAMREGISTRO 85

//contar caracteres ate o \0
//Ler dados do arquivo CSV e salvar no arquivo binário
void binarioNaTela1(char *nomeArquivoBinario) {

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar. */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela1): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}
void lerAtePipe(char *campo,FILE *file){
    char c;
    int contador = 0;
    fread(&c,1,1,file);
    while(c != '|'){
        campo[contador] = c;
        contador ++;
        fread(&c,1,1,file);
    }
    campo[contador] = '\0';

}

int CsvtoBin(FILE *csv,FILE *bin){
    bin = fopen("arquivoGeradoooo.bin","wb");
    struct Cabecalho cabecalho;
    struct Dados dado;
    //Dados para criar o cabecalho
    strcpy(cabecalho.dataUltimaCompactacao,"00/00/0000");   
    cabecalho.numeroArestas = 0;
    cabecalho.numeroVertices = 0;
    cabecalho.status = '0';
  
    fwrite(&cabecalho.status,1,1,bin);
    fwrite(&cabecalho.numeroVertices,sizeof(int),1,bin);//OBS sizeof(int) é de 4bits por padrao do GCC
    fwrite(&cabecalho.numeroArestas,sizeof(int),1,bin);
    fwrite(cabecalho.dataUltimaCompactacao,10,1,bin);
    //Fim do cabecalho

    char delimitador = '|';
    char lixo = '#';
    char limpalinha[100];
    int a,b,c;
    dado.distancia = -1;//Esta linha e a de baixo servem para tratar os casos onde a leitura seja nula ja que iniciamos o campo com um valor conhecido
    dado.estadoDestino[0] = dado.estadoOrigem[0] = dado.cidadeDestino[0] = dado.cidadeOrigem[0] = dado.tempoViagem[0] = '\0';
    //tratar a primeira linha
    fscanf(csv,"%[^\n]%*c%*c",limpalinha);
    while(cabecalho.numeroArestas < 10){
        fscanf(csv,"%[^,]%*c %[^,]%*c %d%*c %[^,]%*c %[^,]%*c %[^\n]%*c",dado.estadoOrigem,dado.estadoDestino,&dado.distancia,dado.cidadeOrigem,dado.cidadeDestino,dado.tempoViagem);
        //tratamento de nulos OBS: nulo do int ja tratado ao startar a variavel com -1
        printf(" %s %s %d %s %s %s \n",dado.estadoOrigem,dado.estadoDestino,dado.distancia,dado.cidadeOrigem,dado.cidadeDestino,dado.tempoViagem);
        if(dado.estadoDestino[0] == '\0'){
            dado.estadoDestino[1] = '#';
        }
        if(dado.estadoOrigem[0]== '\0'){
            dado.estadoOrigem[1] = '#';  
        }
        //escrita dos campos de tamanho fixo
        fwrite(dado.estadoOrigem,2,1,bin);//escreve os dois primeiros bytes de dado.estado origem arquivo binario
        fwrite(dado.estadoDestino,2,1,bin);
        fwrite(&dado.distancia,sizeof(int),1,bin);
        
        //campos de tamanho varaivel

        /*Não se realizou o tratamento de truncamento pq na especificação do trabalho foi 
          dito que não era necessário pois o arquivo de dados garantia regularidade */

        a = strlen(dado.cidadeOrigem);
        b = strlen(dado.cidadeDestino);
        c = strlen(dado.tempoViagem);
        fwrite(dado.cidadeOrigem,a,1,bin);
        fwrite(&delimitador,1,1,bin);
        fwrite(dado.cidadeDestino,b,1,bin);
        fwrite(&delimitador,1,1,bin);
        fwrite(dado.tempoViagem,c,1,bin);
        fwrite(&delimitador,1,1,bin);
        for(int i = 0; i < 77 - (a+b+c+3);i++){//escreve lixo no resto dos espaços livres
            fwrite(&lixo,1,1,bin);
        }
       cabecalho.numeroArestas++;
    }
    /*Atualizar o Cabecalho*/
    fseek(bin,0,SEEK_SET);
    cabecalho.status = '1';
    fwrite(&cabecalho.status,1,1,bin);
    fwrite(&cabecalho.numeroVertices,sizeof(int),1,bin);
    printf("TA FAZENDO ISSo");
    fwrite(&cabecalho.numeroArestas,sizeof(int),1,bin);
    fwrite(cabecalho.dataUltimaCompactacao,10,1,bin);
    fclose(bin);
    /*Abertura e fechamento de arquivo nao vao ser feitas aqui*/
    return 0;
}

void print_reg(FILE *file){
    struct Dados registro;
    struct Cabecalho cab;
    char c;
    int contador = 0;
    int rrn = 0;
    fseek(file, (rrn*TAMREGISTRO)+19, SEEK_SET);//Pular o cabeçalho
    while(contador < 10){
        registro.estadoOrigem[2] = registro.estadoDestino[2] = '\0';
        fread(registro.estadoOrigem,2,1,file);
        fread(registro.estadoDestino,2,1,file);
        fread(&registro.distancia,4,1,file);
        //Campos de tamanhoVariavel ------>Ler ate o delimitador char a char
        lerAtePipe(registro.cidadeOrigem,file);
        lerAtePipe(registro.cidadeDestino,file);
        lerAtePipe(registro.tempoViagem,file);
        rrn++;
        contador++;
        fseek(file,(rrn*TAMREGISTRO)+19,SEEK_SET);
        printf("%s %s %d %s %s %s \n",registro.estadoOrigem,registro.estadoDestino,registro.distancia,registro.cidadeOrigem,registro.cidadeDestino,registro.tempoViagem);
    }
    
}

int main(){
    FILE *csv;
    FILE *bin;
    int opt;
    char nomeArqGer[50];
    char nome_arq_csv[50];
    scanf("%d", &opt);  /* Digita o número da opção a ser considerada */

    switch (opt){
    case 1:
        // scanf("%s",nome_arq_csv);
        // scanf("%s",nomeArqGer);        
        bin = fopen("arquivoGerado.bin","ab");
        csv = fopen("conjuntoDados.csv","rb");
        CsvtoBin(csv,bin);
        fclose(csv);
        fclose(bin);
        // CsvtoBin(nome_arq_csv,nomeArqGer);
        binarioNaTela1("arquivoGerado.bin");
        break;
    case 2:
        //scanf("%s",nomeArqGer);
        //bin = fopen(nomeArqGer,"rb");
        // print_reg(nomeArqGer);
        bin = fopen("arquivoGerado.bin","rb");

        print_reg(bin);
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