/*

Ass: João Victor Alves de Meira
Ass: João Victor Tavares Pinho

*/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

// Variáveis usadas para garantir que seja executada as funções na ordem correta.

int verihisto = 1;
int veriima = 1;
int veriarq = 1;

int main(void){
	
	printf("\tPrograma de Limiarizacao de Imagens\n\n");	
		
	Tcabeca *cabeca = cria_cabeca(); //Inicialização da cabeça da lista encadeada
	
	if(!cabeca) return 0;
	
	int op=0;
	
	printf("Imagem: %s\tFormato: %s\tTamanho: %dx%d\tPixel de maior intensidade: %u\n\n", cabeca->nome, cabeca->formato, cabeca->num_linha, cabeca->num_coluna, cabeca->max_pixel);
	
	while(op != 4){
		
		printf("1-Gerar Histograma\n2-Carregar Imagem\n3-Limiarizar Imagem\n4-Sair\nEscolher: ");
		scanf("%d", &op);
		printf("\n");
		
		switch(op){
			
			case 1:{
				
				if(verihisto == 1){
					unsigned int *histograma = (unsigned int *)calloc(256, sizeof(unsigned int)); // Alocação de memória para gerar o histograma
					GeraHistograma(histograma, cabeca); // Lê o arquivo PGM P2 e contabiliza o número de vezes que cada intensidade de pixel aparece na imagem, gerando o histograma
					cabeca->limiar = CalcularLimiar(histograma, (cabeca->num_coluna)*(cabeca->num_linha), cabeca->max_pixel); // Função utilizada para calcula o limiar da imagem
					free(histograma); 
					printf("O limiar da imagem eh %d . Para economizar memoria nao iremos armazenar os pixels de intensidade igual a %d", cabeca->limiar, cabeca->n_guardar);
					printf("\n\n");
					verihisto--;
				} else{
					printf("Histograma ja gerado\n\n");
				}
				
				break;
				
			}
			
			case 2:{
				if(verihisto == 0){
					if(veriima==1){
						CarregarImagem(cabeca); // Lê o arquivo PGM P2 e armazena essa imagem na memória, usa um conceito parecido com matriz esparsa para a economia de memória 
						veriima--;
					} else{
						printf("Imagem ja carregada\n\n");
					}
				} else{
					printf("Gere o histograma primeiro\n\n");
				}
				break;
			}
			
			case 3:{
				if(veriima==0){
					if(veriarq==1){
						CriaNovoArquivo(cabeca); // Percorre a lista encadeade com a intensidade e posição dos pixels na imagem, trocando para 0 ou 1 a partir do valor do limiar
						veriarq--;
					} else{
						printf("Arquivo novo ja criado\n\n");
					}
				} else{
					printf("Imagem ainda nao carregada\n\n");
				}
				break;
			}
			
			case 4:{
				
				if(cabeca->prim){
					printf("Liberando imagem da memoria e saindo\n");
					DesalocaLista(&cabeca->prim); // Desaloca a lista encadeada 
					free(cabeca);
				} else{
					printf("Saindo\n");
				}
				break;
			}
			
			default:{
				printf("Opcao Invalida\n\n");
				break;
			}
			
		}
	}
	
}
