# Limiarização de Imagens com Economia de Memória

O programa em questão é um programa desenvolvido em linguagem C para realizar a limiarização de imagens em formato PGM (Portable Graymap Format) com o objetivo de converter uma imagem em tons de cinza em uma imagem binária, ou seja, com apenas dois valores de pixel: preto e branco. O limiar utilizado para realizar essa conversão é calculado pelo método de Otsu.

O conceito de limiarização de imagens é muito utilizado em processamento de imagens para separar objetos de interesse do restante do fundo, sendo comumente empregado em tarefas de segmentação de imagens.

## Funcionamento do Programa

O programa segue um menu de opções onde o usuário pode executar as seguintes ações:

- Gerar Histograma: Gera o histograma da imagem PGM, contabilizando o número de vezes que cada intensidade de pixel aparece na imagem. O histograma é utilizado para calcular o limiar de Otsu, que será usado posteriormente para a limiarização.
- Carregar Imagem: Carrega a imagem PGM selecionada na memória do programa. O programa utiliza um conceito parecido com matriz esparsa para economizar memória, armazenando apenas os pixels de interesse (não considerando os pixels de maior intensidade).
- Limiarizar Imagem: Realiza a limiarização da imagem carregada na memória, convertendo-a em uma imagem binária (preto e branco). O limiar utilizado é o valor calculado previamente no passo 1.
- Sair: Encerra o programa.

## Economia de Memória

Para economizar memória durante o processamento da imagem, o programa utiliza uma lista encadeada para armazenar apenas os pixels relevantes (pixels de intensidade diferente do pixel de maior intensidade). Dessa forma, evita-se a alocação de memória desnecessária para os pixels que não serão utilizados na limiarização.

Ao carregar a imagem na memória, o programa verifica a intensidade de cada pixel e, se a intensidade for igual ao valor do pixel de maior intensidade (armazenado na variável n_guardar), esse pixel é ignorado e não é adicionado à lista encadeada. Somente os pixels de interesse, ou seja, os pixels com intensidade diferente do valor de n_guardar, são armazenados na lista encadeada. Isso garante que a lista conterá apenas os pixels que serão limiarizados.

Essa abordagem resulta em uma economia significativa de memória, pois evita a necessidade de alocar espaço para armazenar todos os pixels da imagem original, que pode ser muito grande, especialmente em imagens de alta resolução.


## Este programa permite limiarizar imagens no formato PGM (Portable Gray Map). Siga os passos abaixo para utilizar o programa corretamente:

- Este projeto foi desenvolvido e compilado utilizando exclusivamente o ambiente de desenvolvimento Dev-C++ versão 5.11. Para executar o programa, é necessário abrir o arquivo "projeto.dev" no Dev-C++ e, em seguida, compilar e executar o arquivo "Projeto Final.c" pressionando a tecla "F11".

1. Escolher o arquivo a ser limiarizado
No primeiro passo, você deve escrever o nome do arquivo PGM que deseja limiarizar. Certifique-se de digitar o nome do arquivo sem a extensão ".pgm". O programa assume que o arquivo já é ".pgm" e está localizado na pasta "Imagens" dentro do diretório atual.

2. Gerar o histograma
No segundo passo, você deve gerar o histograma da imagem digitando "1" no prompt. O histograma fornecerá informações sobre a distribuição dos níveis de cinza presentes na imagem.

3. Carregar a imagem na memória
No terceiro passo, você deve carregar a imagem na memória digitando "2" no prompt. Isso permitirá que o programa acesse e manipule os pixels da imagem.

4. Limiarizar a imagem
No quarto passo, você deve limiarizar a imagem digitando "3" no prompt. Em seguida, o programa solicitará que você digite o nome do novo arquivo que conterá a imagem limiarizada, que lembrando deve ser sem a extensão ".pgm" pois o programa já assume que o arquivo será .pgm. A imagem limizarizada será salva na pasta "Limiarizadas" no diretório atual.Certifique-se de inserir um nome válido para o novo arquivo.

5. Sair do programa
Basta digitar "4" no prompt. Isso desalocará a imagem em memória e encerrará a execução do programa.

Lembre-se de seguir a ordem dos passos corretamente para obter os resultados desejados. O arquivo PGM a ser limiarizado deve estar localizado na pasta "Imagens" dentro do diretório atual.

## Observações

Observação sobre o Projeto Final:

Este programa foi desenvolvido como projeto final para a disciplina de Estrutura de Dados 1. O principal objetivo do projeto era demonstrar o conhecimento adquirido ao longo da disciplina em relação a ponteiros, alocação dinâmica e, principalmente, a implementação de listas encadeadas.

Um dos principais critérios de avaliação do projeto era a eficiência do programa, tanto em velocidade quanto em armazenamento de memória, logo tinhamos que obrigatóramente alocar a imagem na memória. Para atingir esse objetivo, foi optado por carregar a imagem na memória utilizando uma abordagem semelhante à matriz esparsa para fazer a alocação dos pixels relevantes na memória. Essa estratégia permitiu que o programa economizasse memória, armazenando apenas os pixels de interesse, evitando a alocação desnecessária de memória para pixels que não seriam utilizados na limiarização.

Além disso, o projeto também abordou o cálculo do limiar de Otsu para a limiarização da imagem, uma técnica que é amplamente utilizada em processamento de imagens para segmentação. A implementação do histograma e do cálculo do limiar também contribuíram para a eficiência do programa.

Por fim, o projeto final demonstrou de forma prática o domínio dos conceitos aprendidos na disciplina e a habilidade dos autores para resolver esse problema de processamento de imagens utilizando estruturas de dados como listas encadeadas de forma eficiente e eficaz.