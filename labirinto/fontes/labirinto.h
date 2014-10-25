/***************************************************************************
*
* $MCD M�dulo de defini��o: LAB LABIRINTO em Grafo  
*
* Arquivo gerado: labirinto.h
* Letras identificadoras: LAB
*
* Nome da base de software: Arcabou�o para a automa��o de testes de programas redigidos em C
*
* Projeto: INF 1301 Trabalho 3
* Gestor: LES/DI/PUC-Rio
* Autores:  Lucas Menezes <LM>, Lorenzo Saraiva <LS>
*
* $HA Hist�rico de evolu��o:
* Vers�o Autor Data Observa��es
* 1     LM,LS 24/out/2014 In�cio do Desenvolvimento

* $ED Descri��o do m�dulo
* 
*	Este m�dulo implementa um Labirinto usando o um grafo gen�rico
*	Este m�dulo armazena em si 
* 

***************************************************************************/
typedef struct LAB_tagLabirinto * LAB_tppLabirinto ;

typedef enum {

         	LAB_CondRetOK ,
               /* Concluiu corretamente */
		 LAB_CondRetFaltouMemoria ,
		      /* N�o h� mem�ria pra alocar */
        	 LAB_CondRetLabirintoVazio ,
               /* o grafo n�o cont�m elementos */
		 

   } LAB_tpCondRet ;
/***********************************************************************
*
*  $FC Fun��o: LAB  &Criar Labirinto
*
*  $ED Descri��o da fun��o
*     Cria a estrutura b�sica do Labirinto Vazio
*     Os poss�veis tipos de elementos armazenados nos n�s do grafo s�o desconhecidos a priori
*     Esta fun��o inicializa as estruturas reguladoras do grafo
*
*  $EP Par�metros
*	  refLab		- endere�o ponteiro para a cabe�a do labirinto a ser gerado, a ser retornado por refer�ncia
*                     
*
*  $FV Valor retornado
*     Se executou corretamente retornar� a LAB_CondRetOK
*     Se ocorreu alguma aloca��o de mem�ria n�o conseguir ser realizada
*     a fun��o retornar� LAB_CondRetFaltouMemoria.
*    
*
***********************************************************************/
LAB_tpCondRet LAB_CriarLabirinto( LAB_tppLabirinto* refLab);

/***********************************************************************
*
*  $FC Fun��o: GRA  &Destruir Labirinto
*
*  $ED Descri��o da fun��o
*     Esvazia o Labirinto recebido e destr�i suas estruturas de controle.
*
*  $EP Par�metros
*	  labirinto			- ponteiro para a cabe�a do labirinto a ser destruido
*
*  $FV Valor retornado
*     Se executou corretamente retorna retornar� a LAB_CondRetOK
*    
*    
*
***********************************************************************/


LAB_tpCondRet LAB_DestruirLabirinto( LAB_tppLabirinto labirinto );