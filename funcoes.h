/*

Ass: Jo�o Victor Alves de Meira
Ass: Jo�o Victor Tavares Pinho

*/

// Defini��o das estruturas de dados. Estrutura para representar o n�s da lista de pixels

typedef struct lista{
	
	unsigned char intensidade; // Intensidade do pixel
	unsigned short int linha, coluna; // Posi��o do Pixel na imagem
	struct lista *prox; // Ponteiro para o pr�ximo elemento da lista
	
}Tlista;

	//Estrutura para representar a cabe�a da lista da imagem PGM

typedef struct cabeca{
	
	char nome[20], formato[20]; // Nome do arquivo PGM e seu formato que � P2
	unsigned short int num_linha, num_coluna; // Tamanho da imagem, LarguraxComprimento
	unsigned char max_pixel; // Pixel de maior intensidade da imagem, usado na fun��o calcula limiar
	unsigned char n_guardar; // Elemento que mais aparece, justamente o que n�o iremos guardar
	unsigned char limiar; // Limiar da imagem, a partir dele sabemos se o pixel ir� virar 0 ou 1, ou seja, preto ou branco
	Tlista *prim; // Ponteiro para o primeiro elemento da Lista de Pixels
	Tlista *ult;  //Ponteiro para o �ltimo elemento da Lista de Pixels, serve para termos uma inser��o mais r�pido no final da lista 
	
}Tcabeca;

// Declara��o das func�es

Tcabeca *cria_cabeca();
void GeraHistograma(unsigned int *histograma, Tcabeca *cabeca);
unsigned char CalcularLimiar(const unsigned int *hist, int totalPixels, unsigned char maxPixel);
Tlista *CriaElemento(unsigned char intensidade, unsigned short int linha, unsigned short int coluna);
void AdicionaLista(Tcabeca *cabeca, Tlista *novo);
void CarregarImagem(Tcabeca *cabeca);
void CriaNovoArquivo(Tcabeca *cabeca);
void DesalocaLista(Tlista **prim);
