/***************************************************************************
*
* $MCD Módulo de definição: GRA GRAFO Genérico 
*
* Arquivo gerado: grafo.h
* Letras identificadoras: GRA
*
* Nome da base de software: Arcabouço para a automação de testes de programas redigidos em C
*
* Projeto: INF 1301 Trabalho 3
* Gestor: LES/DI/PUC-Rio
* Autores:  Lucas Menezes <LM>, Lorenzo Saraiva <LS>
*
* $HA Histórico de evolução:
* Versão Autor Data Observações
* 1     LM,LS 22/set/2014 Início do Desenvolvimento
* 2		LM,LS 23/OUT/2014 início da melhoria do módulo
* $ED Descrição do módulo
* Implementa Um grafo genérico não dirigido, i.e. , 
* (para todo nó A e B) A está ligado em B <=> B está ligado em A.
* 
* O grafo é definido como um conjunto de vértices (ou nós) e suas arestas.
* 
* Cada vértice gerado é identificado por um inteiro >= 1 e não há dois vértice com 
* a mesma identificação coexistindo no mesmo grafo.
* 
* As operações com vértices e arestas são feitas indicando as identificações dos vértices envolvidos
* Ao Criar um vértice, a identificação dele é fornecida ao usuário, 
* para que possa ser posteriormente operado
* 
* Podem existir n grafos em operação simultaneamente.
* Os grafos possuem uma cabeça encapsulando o seu estado.
* 
* Alternativamente aos indices dos nós, os grafos podem ser operados por operações
* de elemento corrente
*
* Cada grafo é homogêneo quanto ao tipo dos dados que armazena.
* Cada vértice do grafo referencia o valor que contém.
*
* Os ponteiros para os dados são copiados para elementos da grafo
* Não é copiado o valor apontado por estes ponteiros.
*
* O controle da destruição do valor de um vértice a ser excluído
* é realizado por uma função fornecida pelo usuário.
*
* Cada grafo referencia uma função que determina como devem ser
* desalocados os dados nele contidos.
*
* Esta função é chamada antes de se desalocar um vértice
* de um grafo.



***************************************************************************/
typedef struct GRA_tagGrafo * GRA_tppGrafo ;

typedef enum {

         	GRA_CondRetOK ,
               /* Concluiu corretamente */
		 GRA_CondRetFaltouMemoria ,
		      /* Não há memória pra alocar */
        	 GRA_CondRetGrafoVazio ,
               /* o grafo não contém elementos */
		 GRA_CondRetArestaJaExiste,
	       /* A aresta já existe */		
		 GRA_CondRetNoNaoExiste,
	       /* O nó não existe */
		 GRA_CondRetArestaNaoExiste,
	       /* A aresta já existe */
   		GRA_CondRetJaEsta,
			/* Já está no nó */
		GRA_CondRetCaminhoExiste,
			/* Há caminho entre dois vértices */
		GRA_CondRetCaminhoNaoExiste
			/* Não há caminho entre os dois vértices */
   } GRA_tpCondRet ;
/***********************************************************************
*
*  $FC Função: GRA  &Criar grafo
*
*  $ED Descrição da função
*     Cria um grafo genérico não dirigido vazio
*     Os possíveis tipos de elementos armazenados nos nós do grafo são desconhecidos a priori
*     Esta função inicializa as estruturas reguladoras do grafo
*
*  $EP Parâmetros
*	  refgrafo		- endereço ponteiro para a cabeça do grafo a ser gerado, a ser retornado por referência
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo nó
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retornará a GRA_CondRetOK
*     Se ocorreu alguma alocação de memória não conseguir ser realizada
*     a função retornará GRA_CondRetFaltouMemoria.
*    
*
***********************************************************************/
GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo* refgrafo,  void   ( * ExcluirValor ) ( void * pDado ));

/***********************************************************************
*
*  $FC Função: GRA  &Destruir grafo
*
*  $ED Descrição da função
*     Esvazia o grafo recebido e destrói suas estruturas de controle.
*
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo a ser destruido
*
*  $FV Valor retornado
*     Se executou corretamente retorna retornará a GRA_CondRetOK
*    
*    
*
***********************************************************************/


GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo grafo );

/***********************************************************************
*
*  $FC Função: GRA  &Inserir Nó
*
*  $ED Descrição da função
*     A função trata de inserir um novo nó no grafo, dando a ele um id único, pelo qual poderá ser 
*     identificado e operado posteriormente. Também o associará a uma informação qualquer, passada
*	  pelo parâmetro pInfo. Por definição um novo nó não tem arestas.
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo 
*	  pInfo			- endereço a informação a ser armazenada no grafo
*	  pNoId			- endereço da variável que receberá o id do grafo criado, retornado por referência
*  $FV Valor retornado
*     Se executou corretamente retornará GRA_CondRetOK
*     Se Faltou memória em qualquer parte do processo, retornará GRA_CondRetFaltouMemoria
*
*     
***********************************************************************/
GRA_tpCondRet   GRA_InserirNo ( GRA_tppGrafo grafo, void * pInfo,int* pNoId);

/***********************************************************************
*
*  $FC Função: GRA  &Excluir Nó
*
*  $ED Descrição da função
*     A função recebe um grafo o id do nó a ser excluído do respectivo grafo.
*     Se o Nó a ser removido é o nó corrente, o nó corrente passa ser outro qualquer
*	  
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo
*	  Id			- id do no a ser excluido
*  $FV Valor retornado
*     Se executou corretamente retornará GRA_CondRetOK
*     Se o no nao existir retornará GRA_CondRetNoNaoExiste
*	  Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio
*
*     
***********************************************************************/

GRA_tpCondRet   GRA_ExcluirNo ( GRA_tppGrafo grafo, int Id);

/***********************************************************************
*
*  $FC Função: GRA  &Excluir Nó Corrente
*
*  $ED Descrição da função
*     A função exclui o no corrente do grafo. 
*		O no corrente passa a ser outro qualquer.
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo
*  $FV Valor retornado
*     Se executou corretamente retornará GRA_CondRetOK
*	  Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio
*
*     
***********************************************************************/

GRA_tpCondRet   GRA_ExcluirNoCorrente ( GRA_tppGrafo grafo);

/***********************************************************************
*
*  $FC Função: GRA  &Inserir aresta
*
*  $ED Descrição da função
*     A função insere uma nova aresta entre os nós cujos Id foram passados como parâmetro. Por definição
*	  toda aresta que liga o nó A ao B, liga o nó B ao A também. 
*
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo no qual a aresta será inserida
*	  no_x_Id		- ID de um dos vértices onde será colocada a aresta
*	  no_y_Id		- ID do outro vértice onde será colocada a aresta
*	  idAresta		- Inteiro a ser adicionado à aresta 
*
*  $FV Valor retornado
*     Se executou corretamente retorna GRA_CondRetOK
*	  Se um dos nós nao existe, retorna GRA_CondRetNoNaoExiste
*	  Se a aresta já existe, retorna GRA_CondRetArestaJaExiste
*	  Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio
*    
*
***********************************************************************/

GRA_tpCondRet  GRA_InserirAresta( GRA_tppGrafo grafo, int no_x_Id, int no_y_Id, int idAresta);


/***********************************************************************
*
*  $FC Função: GRA  &Excluir aresta
*
*  $ED Descrição da função
*     A função exclui uma aresta existente entre os nós cujos Id foram passados como parâmetros.
*	  
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo cuja aresta será destruida
*	  no_x_Id		- ID de um dos vértices cuja aresta será destruída
*	  no_y_Id		- ID do outro vértice cuja aresta será destruída
*
*  $FV Valor retornado
*     Se executou corretamente retorna GRA_CondRetOK
*	  Se um dos nós nao existe, retorna GRA_CondRetNoNaoExiste
*	  Se a aresta não existe, retorna GRA_CondRetArestaNaoExiste
*	  Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio
*    
*
***********************************************************************/
GRA_tpCondRet  GRA_ExcluirAresta (GRA_tppGrafo grafo, int no_x_Id, int no_y_Id);

/***********************************************************************
*
*  $FC Função: GRA  &Obter Id Aresta
*
*  $ED Descrição da função
*     A função obtem o Id de uma aresta existente entre os nós cujos Id foram passados como parâmetros.
*	  
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo cuja aresta será destruida
*	  no_x_Id		- ID de um dos vértices cuja aresta será destruída
*	  no_y_Id		- ID do outro vértice cuja aresta será destruída
*	  pId			- ponteiro para inteiro para retornar o valor por referência
*
*  $FV Valor retornado
*     Se executou corretamente retorna GRA_CondRetOK
*	  Se um dos nós nao existe, retorna GRA_CondRetNoNaoExiste
*	  Se a aresta não existe, retorna GRA_CondRetArestaNaoExiste
*	  Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio
*    
*
***********************************************************************/
GRA_tpCondRet  GRA_ObterIdAresta (GRA_tppGrafo grafo, int no_x_Id, int no_y_Id, int * pId);

/***********************************************************************
*
*  $FC Função: GRA  &Esvaziar Grafo
*
*  $ED Descrição da função
*     Esta Função esvazia o grafo, liberando todos os elementos. O grafo fica como se
*	  tivesse sido recém criado.
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo a ser esvaziado
*	 
*  $FV Valor retornado
*     Se executou corretamente retornará GRA_CondRetOK
*	  Se o grafo já estava vazio, retorna GRA_CondRetGrafoVazio
*
*     
***********************************************************************/

GRA_tpCondRet GRA_EsvaziarGrafo( GRA_tppGrafo grafo );

/***********************************************************************
*
*  $FC Função: GRA  &Imprimir Grafo
*
*  $ED Descrição da função
*     Esta Função para cada vértice do grafo recebido exibirá seu id
*	  e o conjunto dos ids dos vértices adjacentes a esse		
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo a ser impresso
*	 
*  $FV Valor retornado
*     Se executou corretamente retornará GRA_CondRetOK
*     Se o grafo está vazio, retornará GRA_CondRetGrafoVazio
*
*     
***********************************************************************/
GRA_tpCondRet  GRA_ImprimirGrafo(GRA_tppGrafo grafo);

/***********************************************************************
*
* $FC Função: GRA &Obter Valor do Nó Corrente
*
* $ED Descrição da função
* 	Esta Função transmite ao ponteiro cujo endereço é recebido
*   a informação do nó corrente. Este passa a apontar 
*	para essa informação.
* $EP Parâmetros
* 	grafo - ponteiro para a cabeça do grafo a ser impresso
* 	pInfo - o endereço do ponteiro que receberá o nó
* $FV Valor retornado
* 	Se executou corretamente retornará GRA_CondRetOK.
* 	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
*
*
***********************************************************************/

GRA_tpCondRet GRA_ObterValorNoCorrente(GRA_tppGrafo grafo, void ** pInfo);

/***********************************************************************
*
* $FC Função: GRA &Obter Nó Corrente
*
* $ED Descrição da função
* 	Esta Função recebe um grafo e retorna por ref o Id 
	do nó corrente, pelo qual ele poderá ser acessado e operado.
* $EP Parâmetros
* 	grafo - ponteiro para a cabeça do grafo a ser impresso
* 	refId - o endereço da variável que receberá o valor do id do nó
* $FV Valor retornado
* 	Se executou corretamente retornará GRA_CondRetOK.
* 	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
	Se o nó não existir retornará GRA_CondRetNoNaoExiste..
*
*
***********************************************************************/
GRA_tpCondRet GRA_ObterNoCorrente( GRA_tppGrafo grafo, int * refId);

/***********************************************************************
*
* $FC Função: GRA &Ir nó vizinho
*
* $ED Descrição da função
* 	Esta função recebe o iD do nó vizinho para onde se deseja mudar o nó corrente
*
* $EP Parâmetros
* 	grafo - ponteiro para a cabeça do grafo a ser impresso
* 	noVizinho - inteiro para o Id do nó que se deseja ir
* 	
* $FV Valor retornado
* 	Se executou corretamente retornará GRA_CondRetOK.
* 	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
* 	Se o nó não existir retornará GRA_CondRetNoNaoExiste.
*	Se não houver aresta entre os nós retornará GRA_CondRetArestaNaoExiste
*   Se o nó desejado já for o corrente retornará GRA_CondRetJaEsta
*
*
***********************************************************************/

GRA_tpCondRet GRA_IrNoVizinho( GRA_tppGrafo grafo, int noVizinho);
/***********************************************************************
*
* $FC Função: GRA &Obter Valor do Nó
*
* $ED Descrição da função
* 	Esta Função recebe um id do vértice e faz o ponteiro cujo endereço 
* 	é recebido apontar para a informação do nó.
* $EP Parâmetros
* 	grafo - ponteiro para a cabeça do grafo a ser impresso
* 	noId - inteiro para o Id do nó cujo valor será recebido
* 	endVar - o endereço do ponteiro que receberá o nó
* $FV Valor retornado
* 	Se executou corretamente retornará GRA_CondRetOK.
* 	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
* 	Se o nó não existir retornará GRA_CondRetNoNaoExiste.
*
*
***********************************************************************/
GRA_tpCondRet GRA_ObterValorNo(GRA_tppGrafo grafo, int noId,void** endVar);

/***********************************************************************
*
* $FC Função: GRA &Ir Para Nó
*
* $ED Descrição da função
* 	Esta Função recebe um id do vértice e o situa o elemento corrente
* 	da estrutura.
* 	Caso o nó não exista, a função vai manter o valor corrente recebido
*
* $EP Parâmetros
* 	grafo - ponteiro para a cabeça do grafo a ser impresso
* 	noId - inteiro para o Id do nó que virará corrente
* 	
* $FV Valor retornado
* 	Se executou corretamente retornará GRA_CondRetOK.
* 	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
* 	Se o nó não existir retornará GRA_CondRetNoNaoExiste.
*
*
***********************************************************************/
GRA_tpCondRet GRA_IrParaNo(GRA_tppGrafo grafo,int noId);

/***********************************************************************
*
* $FC Função: GRA &DFS
*
* $ED Descrição da função
*	Esta função retorna o um vetor de ids de nós de grafo
*	que são o todos os que são posíveis se chegar pelo no recebido.
* $EP Parâmetros
*	grafo - ponteiro para a cabeça do grafo a ser impresso
*	noId - inteiro para o Id do nó que virará corrente
*	refPtrIds - Endereço do vetor que recebrá os ids
*	refTam - Endereço de um inteiro que receberá o tamanho do vetor
* $FV Valor retornado
*	Se executou corretamente retornará GRA_CondRetOK.
*	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
*	Se o nó não existir retornará GRA_CondRetNoNaoExiste.
*
*
***********************************************************************/
 
GRA_tpCondRet GRA_DFS(GRA_tppGrafo grafo, int** refPtrIds, int * reftam,int noId);

/***********************************************************************
*
* $FC Função: GRA &ExisteCaminho
*
* $ED Descrição da função
*	Esta função verifica se existe caminho entre dois vértices
*	cujos ids são informados, de um determinado grafo.
*	
* $EP Parâmetros
*	grafo - ponteiro para a cabeça do grafo a ser impresso
*	noInicioId - Id do vértice pelo qual se começa
*	noFimId - Id do vértice ao qual se chega
* $FV Valor retornado
*	Se o caminho for encontrado retornará GRA_CondRetCaminhoExiste
*	Se o caminho não for encontrado retornará GRA_CondRetCaminhoNaoExiste
*	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
*	Se o vértice inicial não existir retornará GRA_CondRetNoNaoExiste.
*
*
***********************************************************************/
 
GRA_tpCondRet GRA_ExisteCaminho(GRA_tppGrafo grafo, int noInicioId, int noFimId);