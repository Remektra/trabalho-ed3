/* George Gantus - 10691988 */
/* Renata Brito -  10373663 */

#include "funcoes.h"

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

int CsvtoBin(char* nome_arq_csv,char* nomeArqGe){
    FILE* csv;
    FILE* bin;
    csv = fopen(nome_arq_csv,"rb"); // abre o arquivo csv
    bin = fopen(nomeArqGe,"wb"); // cria o arquivo binário 
    if(!csv){
        printf("Falha no carregamento do arquivo.");
        return ERRO; // caso tenha ocorrido algum erro com o arquivo, retorna 0 
    }
    if(!bin){
        printf("Falha no carregamento do arquivo.");
        return ERRO; // caso tenha ocorrido algum erro com o arquivo, retorna 0
    }
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
    char aux;
    int cntaux;
    dado.distancia = -1;//Esta linha e a de baixo servem para tratar os casos onde a leitura seja nula ja que iniciamos o campo com um valor conhecido
    dado.estadoDestino[0] = dado.estadoOrigem[0] = dado.cidadeDestino[0] = dado.cidadeOrigem[0] = dado.tempoViagem[0] = '\0';
    //tratar a primeira linha
    fscanf(csv,"%[^\n]%*c%*c",limpalinha);
    while(cabecalho.numeroArestas < 10){
        cntaux = 0;
        fscanf(csv,"%[^,]%*c %[^,]%*c %d%*c %[^,]%*c %[^,]%*c",dado.estadoOrigem,dado.estadoDestino,&dado.distancia,dado.cidadeOrigem,dado.cidadeDestino);
        fscanf(csv,"%c",&aux);
        if(aux == '\n'){
            dado.tempoViagem[0] = '\0';
        }else{
            while (aux != '\n'){
                dado.tempoViagem[cntaux]= aux;
                fscanf(csv,"%c",&aux);
                cntaux++;
            }
            dado.tempoViagem[cntaux]='\0';
        }
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
    fclose(csv);
    
    return 0;
}

int print_reg(char* nome_arq){
    FILE *file;
    file = fopen(nome_arq,"rb"); // abre o arquivo gerado para leitura
    if(!file){
        printf("Falha no carregamento do arquivo.");
        return ERRO; // caso tenha ocorrido algum erro com o arquivo, retorna 0 
    }
    struct Dados registro;
    struct Cabecalho cab;
    char c;
    int contador = 0;
    int rrn = 0;
    fseek(file, (rrn*TAMREGISTRO)+19, SEEK_SET);//Pular o cabeçalho
    while(!feof(file)){
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
    return 0;
}
