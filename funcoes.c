/*

Ass: João Victor Alves de Meira
Ass: João Victor Tavares Pinho

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int verinome = 0; // Variável usada para verificar se o usuário digitou o nome de um arquivo valido-

// Função para criar a estrutura Tcabeca com informações da imagem PGM

Tcabeca *cria_cabeca(){
	
	Tcabeca *cabeca = (Tcabeca *)malloc(sizeof(Tcabeca));
	
	if(!cabeca){
		printf("Erro ao alocar cabeca\n\n");
		return NULL;
	}
	
	FILE *arq = NULL;
	
	char caminho[100];
	
	do{
		
		if(verinome>=1){
			printf("Nome do arquivo errado ou arquivo nao esta na pasta Imagens\n");
		}
		
		setbuf(stdin, NULL);
		printf("Escreva o nome do arquivo PGM que deseja limiarizar: ");
		scanf("%s", &cabeca->nome);
		sprintf(caminho, "Imagens/%s.pgm", cabeca->nome);
		printf("\n");
		
		arq = fopen(caminho, "r");
		
		verinome++;
		
	}while(!arq);
	
	fscanf(arq, "%s", cabeca->formato);
	fscanf(arq, "%hd", &cabeca->num_linha);
	fscanf(arq, "%hd", &cabeca->num_coluna);
	fscanf(arq, "%d", &cabeca->max_pixel);
	cabeca->limiar = 0;
	cabeca->n_guardar = 0;
	cabeca->prim = NULL;
	cabeca->ult = NULL;
	
	fclose(arq);
	
	return cabeca;
	
}

// Função para gerar o histograma da imagem PGM

void GeraHistograma(unsigned int *histograma, Tcabeca *cabeca){
	
	char caminho[100];
	sprintf(caminho, "Imagens/%s.pgm", cabeca->nome);
	
	FILE *arq = NULL;
	arq = fopen(caminho, "r");
	
	if(!arq){
		printf("Erro ao abrir arquivo para gerar histograma\n\n");
		return;
		
	}
	
	int i;
	
	char desp[3];
	short int desp1;
	fscanf(arq, "%s", desp);
	fscanf(arq, "%hd", &desp1);
	fscanf(arq, "%hd", &desp1);
	fscanf(arq, "%hd", &desp1);
	
	unsigned char intensidade;
	
	while(!feof(arq)){
		
		fscanf(arq, "%d", &intensidade);
		(*(histograma+intensidade))++;
	}
	
	int maior = 0;
	for(i=0; i<256; i++){
		printf("%d - %d\n", i, *(histograma+i));
		if(*(histograma+i) > maior){
			maior = *(histograma+i);
			cabeca->n_guardar = i;
		}
	}
	
	printf("\n");
	
	fclose(arq);
		
}

// Função para calcular o limiar de Otsu para binarização da imagem PGM

unsigned char CalcularLimiar(const unsigned int *hist, int totalPixels, unsigned char maxPixel){
	
	int i;
	
    float sum = 0;
    for(i=0; i <= maxPixel; i++) {
        sum += i * hist[i];
    }

    float sumB = 0;
    int wB = 0;
    int wF = 0;
    float varMax = 0;
    unsigned char limiar = 0;

    for (i = 0; i <= maxPixel; i++) {
        wB += hist[i]; // Pixels de fundo
        if (wB == 0) continue;

        wF = totalPixels - wB; // Pixels de primeiro plano
        if (wF == 0) break;

        sumB += i * hist[i];
        float meanB = sumB / wB;
        float meanF = (sum - sumB) / wF;
        float varBetween = wB * wF * (meanB - meanF) * (meanB - meanF);

        if (varBetween > varMax) {
            varMax = varBetween;
            limiar = i;
        }
    }

    return limiar;
}

// Função para criar um novo elemento da lista de pixels. 

Tlista *CriaElemento(unsigned char intensidade, unsigned short int linha, unsigned short int coluna){
	
	Tlista *novo = (Tlista *)calloc(1, sizeof(Tlista));
	
	if(!novo){
		printf("Erro ao alcocar novo elemento\n\n");
		return NULL;
	}
	
	novo->intensidade = intensidade;
	novo->linha = linha;
	novo->coluna = coluna;
	novo->prox = NULL;
	
	return novo;
	
}

// Função para adicionar um novo elemento à lista de pixels. Adiciona o novo elemento no final da lista usando o ponteiro ult da estrutura Tcabeca

void AdicionaLista(Tcabeca *cabeca, Tlista *novo){
	
    if(!cabeca->prim){
        cabeca->prim = novo;
    } else{
        cabeca->ult->prox = novo;
    }
    
    cabeca->ult = novo;
}

// Função para carregar a imagem PGM na memória e armazenar os pixels relevantes

void CarregarImagem(Tcabeca *cabeca){
	
	char caminho[100];
	sprintf(caminho, "Imagens/%s.pgm", cabeca->nome);
	
	FILE *arq = NULL;
	arq = fopen(caminho, "r");
	
	if(!arq){
		printf("Erro ao abrir arquivo para carrega Imagem\n\n");
		return;
		
	}
	
	char desp[3];
	short int desp1;
	fscanf(arq, "%s", desp);
	fscanf(arq, "%hd", &desp1);
	fscanf(arq, "%hd", &desp1);
	fscanf(arq, "%hd", &desp1);
	
	unsigned short int linha = 0, coluna = 0;
	unsigned char intensidade;
	
	while(!feof(arq)){
		
		if(feof(arq)) break;
		
		fscanf(arq, "%d", &intensidade);
		
		
		if(coluna == cabeca->num_coluna){
			coluna = 0;
			linha++;
		}
		
		if(intensidade != cabeca->n_guardar){
			AdicionaLista(cabeca, CriaElemento(intensidade, linha, coluna));
		}
		
		coluna++;
	}
	
	printf("Imagem carregada na memoria\n\n");
	
}

// Função para criar um novo arquivo PGM com base na imagem limiarizada

void CriaNovoArquivo(Tcabeca *cabeca){
	
	char nome[50];
	char caminho[100];
	
	setbuf(stdin, NULL);
	printf("Salvar como: ");
	scanf("%s", nome);
	printf("\n");
	
	sprintf(caminho, "Limiarizadas/%s.pgm", nome);
	FILE *arq = fopen(caminho, "w");
	
	if(!arq){
		printf("Erro ao criar novo arquivo\n\n");
		return;
	}
	
	Tlista *aux = cabeca->prim;
	unsigned short int i, j, linha = 0, coluna = 0;
	
	fprintf(arq, "%s\n%d %d\n%d\n", cabeca->formato, cabeca->num_linha, cabeca->num_coluna, 1);
	
	unsigned limiar_nGuardar;
	
	// Determina o valor de limiar_nGuardar, que será usado para escrever no arquivo os pixels após a limiarização
	
	if(cabeca->n_guardar > cabeca->limiar){
		limiar_nGuardar = 1; 
	} else{
		limiar_nGuardar = 0; 
	}
	
	// Loop para percorrer todos os pixels da imagem (linhas e colunas) 

	for(i=0; i<cabeca->num_linha; i++){
		for(j=0; j<cabeca->num_coluna; j++){
			if(aux){ // Verifica se existe um pixel armazenado na lista de pixels
				if(aux->linha == i && aux->coluna == j){ // Se o pixel estiver na lista de pixels, verifica se sua intensidade é maior que o limiar
					if(aux->intensidade> cabeca->limiar){ // Se a intensidade for maior, escreve "1" no arquivo (pixel branco)
						fprintf(arq, "%d ", 1);
					} else{ // Caso contrário, escreve "0" no arquivo (pixel preto)
						fprintf(arq, "%d ", 0);
					}
					
					aux = aux->prox;  // Avança para o próximo pixel armazenado na lista
				} else{ // Caso não exista um pixel armazenado na lista para a posição (i, j)
                    	// Escreve no arquivo o valor de limiar_nGuardar (0 ou 1)
					
					fprintf(arq, "%d ", limiar_nGuardar);
					
				} 
			} else{ // Caso não existam mais pixels na lista de pixels, escreve no arquivo o valor de limiar_nGuardar (0 ou 1)
				fprintf(arq, "%d ", limiar_nGuardar);
			}
			
		}
		fprintf(arq, "\n");
	}

}

// Função para desalocar a lista de pixels

void DesalocaLista(Tlista **prim){
	
    Tlista *aux = *prim;
    while(aux){
        Tlista *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    *prim = NULL;
}
