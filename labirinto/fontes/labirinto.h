/***************************************************************************
*
* $MCD Módulo de definição: LAB LABIRINTO em Grafo  
*
* Arquivo gerado: labirinto.h
* Letras identificadoras: LAB
*
* Nome da base de software: Arcabouço para a automação de testes de programas redigidos em C
*
* Projeto: INF 1301 Trabalho 3
* Gestor: LES/DI/PUC-Rio
* Autores:  Lucas Menezes <LM>, Lorenzo Saraiva <LS>
*
* $HA Histórico de evolução:
* Versão Autor Data Observações
* 1     LM,LS 24/out/2014 Início do Desenvolvimento

* $ED Descrição do módulo
* 
*	Este módulo implementa um Labirinto usando o um grafo genérico
*	Este módulo armazena em si 
* 

***************************************************************************/
typedef struct LAB_tagLabirinto * LAB_tppLabirinto ;

typedef enum {

         	LAB_CondRetOK ,
               /* Concluiu corretamente */
		 LAB_CondRetFaltouMemoria ,
		      /* Não há memória pra alocar */
        	 LAB_CondRetLabirintoVazio ,
               /* o grafo não contém elementos */
		 

   } LAB_tpCondRet ;

 typedef enum
	   {
		   PosNormal,
		   /* Posiçao sem nada de anormal */
		   PosInicio,
		   /*Posição do início do labirinto */
		   PosSaida
		  /* Posição que demarca o fim do labirinto */
	   } PosJog_Tipo;
			/* Tipo da Poisção: 0 normal, 1 entrada, 2 saída */
/***********************************************************************
*
*  $FC Função: LAB  &Criar Labirinto
*
*  $ED Descrição da função
*     Cria a estrutura básica do Labirinto Vazio
*     Os possíveis tipos de elementos armazenados nos nós do grafo são desconhecidos a priori
*     Esta função inicializa as estruturas reguladoras do grafo
*
*  $EP Parâmetros
*	  refLab		- endereço ponteiro para a cabeça do labirinto a ser gerado, a ser retornado por referência
*                     
*
*  $FV Valor retornado
*     Se executou corretamente retornará a LAB_CondRetOK
*     Se ocorreu alguma alocação de memória não conseguir ser realizada
*     a função retornará LAB_CondRetFaltouMemoria.
*    
*
***********************************************************************/
LAB_tpCondRet LAB_CriarLabirinto( LAB_tppLabirinto* refLab);

/***********************************************************************
*
*  $FC Função: GRA  &Destruir Labirinto
*
*  $ED Descrição da função
*     Esvazia o Labirinto recebido e destrói suas estruturas de controle.
*
*  $EP Parâmetros
*	  labirinto			- ponteiro para a cabeça do labirinto a ser destruido
*
*  $FV Valor retornado
*     Se executou corretamente retorna retornará a LAB_CondRetOK
*    
*    
*
***********************************************************************/


LAB_tpCondRet LAB_DestruirLabirinto( LAB_tppLabirinto labirinto );

/***********************************************************************
*
*  $FC Função: LAB  &Inserir Posicao Norte
*
*  $ED Descrição da função
*     Insere uma posição jogavel  ao norte da corrente
*     Caso seja a primeira posição a ser inserida, se torna a corrente
*
*  $EP Parâmetros
*	   labirinto			- ponteiro para a cabeça do labirinto a inserir a posição
*                     
*
*  $FV Valor retornado
*     Se executou corretamente retornará a LAB_CondRetOK
*     Se ocorreu alguma alocação de memória não conseguir ser realizada
*     a função retornará LAB_CondRetFaltouMemoria.
* 
*
***********************************************************************/

LAB_tpCondRet LAB_InserirPosicaoNorte ( LAB_tppLabirinto labirinto );

/***********************************************************************
*
*  $FC Função: LAB  &Inserir Posicao Sul
*
*  $ED Descrição da função
*     Insere uma posição jogavel  ao sul da corrente
*     Caso seja a primeira posição a ser inserida, se torna a corrente
*
*  $EP Parâmetros
*	   labirinto			- ponteiro para a cabeça do labirinto a inserir a posição
*                     
*
*  $FV Valor retornado
*     Se executou corretamente retornará a LAB_CondRetOK
*     Se ocorreu alguma alocação de memória não conseguir ser realizada
*     a função retornará LAB_CondRetFaltouMemoria.
*	  Se ja existir a posição retonará LAB_CondRetPosicaoJaExiste
*
***********************************************************************/

LAB_tpCondRet LAB_InserirPosicaoSul ( LAB_tppLabirinto labirinto );

/***********************************************************************
*
*  $FC Função: LAB  &Inserir Posicao Oeste
*
*  $ED Descrição da função
*     Insere uma posição jogavel  ao oeste da corrente
*     Caso seja a primeira posição a ser inserida, se torna a corrente
*
*  $EP Parâmetros
*	   labirinto			- ponteiro para a cabeça do labirinto a inserir a posição
*                     
*
*  $FV Valor retornado
*     Se executou corretamente retornará a LAB_CondRetOK
*     Se ocorreu alguma alocação de memória não conseguir ser realizada
*     a função retornará LAB_CondRetFaltouMemoria.
*	  Se ja existir a posição retonará LAB_CondRetPosicaoJaExiste
*
***********************************************************************/

LAB_tpCondRet LAB_InserirPosicaoOeste ( LAB_tppLabirinto labirinto );

/***********************************************************************
*
*  $FC Função: LAB  &Inserir Posicao Leste
*
*  $ED Descrição da função
*     Insere uma posição jogavel  ao leste da corrente
*     Caso seja a primeira posição a ser inserida, se torna a corrente
*
*  $EP Parâmetros
*	   labirinto			- ponteiro para a cabeça do labirinto a inserir a posição
*                     
*
*  $FV Valor retornado
*     Se executou corretamente retornará a LAB_CondRetOK
*     Se ocorreu alguma alocação de memória não conseguir ser realizada
*     a função retornará LAB_CondRetFaltouMemoria.
*	  Se ja existir a posição retonará LAB_CondRetPosicaoJaExiste
*
***********************************************************************/

LAB_tpCondRet LAB_InserirPosicaoLeste ( LAB_tppLabirinto labirinto );

/***********************************************************************
*
*  $FC Função: LAB  &Ir Posicao Norte
*
*  $ED Descrição da função
*      Troca o idCorrente do labirinto para o que está ao norte do corrente
*
*  $EP Parâmetros
*	   labirinto			- ponteiro para a cabeça do labirinto a percorrer
*                     
*
*  $FV Valor retornado
*     Se executou corretamente retornará a LAB_CondRetOK
*     Se o labirinto estiver vazio retornará LAB_CondRetLabirintoVazio
*	  Se nao houver caminho ao norte da corrente retornará LAB_CondRetNaoExisteCaminho
*
***********************************************************************/

LAB_tpCondRet IrPosicaoNorte ( LAB_tppLabirinto labirinto );

/***********************************************************************
*
*  $FC Função: LAB  &Ir Posicao Sul
*
*  $ED Descrição da função
*      Troca o idCorrente do labirinto para o que está ao sul do corrente
*
*  $EP Parâmetros
*	   labirinto			- ponteiro para a cabeça do labirinto a percorrer
*                     
*
*  $FV Valor retornado
*     Se executou corretamente retornará a LAB_CondRetOK
*     Se o labirinto estiver vazio retornará LAB_CondRetLabirintoVazio
*	  Se nao houver caminho ao sul da corrente retornará LAB_CondRetNaoExisteCaminho
*
***********************************************************************/

LAB_tpCondRet IrPosicaoSul ( LAB_tppLabirinto labirinto );

/***********************************************************************
*
*  $FC Função: LAB  &Ir Posicao Oeste
*
*  $ED Descrição da função
*      Troca o idCorrente do labirinto para o que está ao oeste do corrente
*
*  $EP Parâmetros
*	   labirinto			- ponteiro para a cabeça do labirinto a percorrer
*                     
*
*  $FV Valor retornado
*     Se executou corretamente retornará a LAB_CondRetOK
*     Se o labirinto estiver vazio retornará LAB_CondRetLabirintoVazio
*	  Se nao houver caminho ao oeste da corrente retornará LAB_CondRetNaoExisteCaminho
*
***********************************************************************/

LAB_tpCondRet IrPosicaoOeste ( LAB_tppLabirinto labirinto );

/***********************************************************************
*
*  $FC Função: LAB  &Ir Posicao Leste
*
*  $ED Descrição da função
*      Troca o idCorrente do labirinto para o que está ao leste do corrente
*
*  $EP Parâmetros
*	   labirinto			- ponteiro para a cabeça do labirinto a percorrer
*                     
*
*  $FV Valor retornado
*     Se executou corretamente retornará a LAB_CondRetOK
*     Se o labirinto estiver vazio retornará LAB_CondRetLabirintoVazio
*	  Se nao houver caminho ao leste da corrente retornará LAB_CondRetNaoExisteCaminho
*
***********************************************************************/

LAB_tpCondRet IrPosicaoLeste ( LAB_tppLabirinto labirinto );
