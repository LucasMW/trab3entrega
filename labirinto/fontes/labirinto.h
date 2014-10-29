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

LAB_tpCondRet LAB_InserirPosicaoNorte ( LAB_tppLabirinto labirinto, PosJog_Tipo tipo );
