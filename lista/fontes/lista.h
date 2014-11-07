#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, Lucas Menezes <LM>
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  6		  LM	05/nov/2014 Adicionando assertivas e revis�o do m�dulo
*	  5		  LM	02/set/2014 Adaptar Interfaces de fun��es aos padr�es da disciplina
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         LIS_CondRetFaltouMemoria,
               /* Faltou mem�ria ao tentar criar um elemento de lista */
		 LIS_CondRetNaoDestruiu
		 /* N�o Conseguiu Destruir a lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*	  refplista   -endere�o ponteiro para a cabe�a da lista a ser gerada, a ser retornada por refer�ncia
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $EAE Assertivas de entrada
*	  refplista deve ser o endere�o de uma vari�vel do tipo 
*	  LIS_tppLista alocada pelo c�digo usu�rio da fun��o. 
*	  refplista deve ser, portanto, um ponteiro n�o nulo
*	  ExcluirValor � um ponteiro para uma fun��o que ir� excluir os
*	  valores que ser�o usados na lista
*	  ExcluirValor n�o pode ser nulo
*  $FV Valor retornado
*     Se executou corretamente retorna LIS_CondRetOK
*     Se faltou mem�ria, retorna LIS_CondRetFaltouMemoria
*	  
*
*  $EAS Assertivas de sa�da
*	  Se a fun��o operar corretamente, retornar� LIS_CondRetOK
*	   e o valor da vari�vel LIS_tppLista cujo endere�o foi passado 
*	   � fun��o receber� a lista criada por refer�ncia.
*	  Se ocorreu alguma aloca��o de mem�ria n�o conseguir ser realizada
*	  A fun��o retornar� LIS_CondRetFaltouMem�ria e o valor de refplista
*	  n�o ser� modificado 
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista* refplista,
             void   ( * ExcluirValor ) ( void * pDado ) ) ;
 


/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
* $EAE Assertivas de entrada
*	  pLista deve ser uma vari�vel do tipo LIS_tppLista alocada pelo trecho
*	  usu�rio da fun��o. 
*	  pLista deve conter um lista gerado por esse m�dulo, i.e.
*	  pela fun��o LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro n�o nulo.
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
* $EAS Assertivas de sa�da
*	
*	Se a fun��o operar corretamente o retorno ser� LIS_CondRetOK
*	e o valor da vai�vel LIS_tppLista passada continuar� o mesmo,
*	por�m, a lista foi liberada da mem�ria e n�o pode mais ser acessada
*	cabe ao trecho usu�rio da fun��o atribuir NULL � vari�vel ap�s
*	o uso da fun��o
***********************************************************************/

    LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;
	
	
	


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser esvaziada
*  $EAE Assertivas de entrada
*	  pLista deve ser uma vari�vel do tipo LIS_tppLista alocada pelo trecho
*	  usu�rio da fun��o. 
*	  pLista deve conter um lista gerado por esse m�dulo, i.e.
*	  pela fun��o LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro n�o nulo.
*  $FV Valor Retornado
*	  Se operou corrtemente retorna LIS_CondRetOK
*	  Se a lista j� estava vazia retorna LIS_CondRetListaVazia
*  $EAS Assettivas de Sa�da
*	Se operou corrtemente retorna LIS_CondRetOK e 
*	  a pLista continua com seu valor, por�m a lista liberou
*	  todos os seus elementos, retornando ao estado de cria��o.
*	Se a lista j� estava vazia retorna LIS_CondRetListaVazia
*	  e a lista n�o � modificada.
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento antes
*
*  $ED Descri��o da fun��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*	  
*  $EP Par�metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*  $EAE Assertivas de entrada
*	  pLista deve ser uma vari�vel do tipo LIS_tppLista alocada pelo trecho
*	  usu�rio da fun��o. 
*	  pLista deve conter um lista gerado por esse m�dulo, i.e.
*	  pela fun��o LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro n�o nulo. 
*	  pValor deve ser um ponteiro para o tipo de elemento que a lista est� armazenando
*	  (todos os elementos da lista s�o do mesmo tipo)
*	  o m�dulo aceita tamb�m o valor NULL.
*  $FV Valor retornado
*    Se executou corretamente, LIS_CondRetOK
*    Se faltou mem�ria, LIS_CondRetFaltouMemoria
*  $EAS Assertivas de Sa�da
*	Se executou corretamente, retorna LIS_CondRetOK e
*	 o valor recebido por pValor foi inserido na lsita numa posi��o
*	 anterior a do elemento corrente.
*	Se faltou mem�ria, retorna LIS_CondRetFaltouMemoria e  
*	 a lista n�o � modificada
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*  $EAE Assertivas de entrada
*	  pLista deve ser uma vari�vel do tipo LIS_tppLista alocada pelo trecho
*	  usu�rio da fun��o. 
*	  pLista deve conter um lista gerado por esse m�dulo, i.e.
*	  pela fun��o LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro n�o nulo. 
*	  pValor deve ser um ponteiro para o tipo de elemento que a lista est� armazenando
*	  (todos os elementos da lista s�o do mesmo tipo)
*	  o m�dulo aceita tamb�m o valor NULL.
*  $FV Valor retornado
*    Se executou corretamente, LIS_CondRetOK
*    Se faltou mem�ria, LIS_CondRetFaltouMemoria
*  $EAS Assertivas de Sa�da
*	Se executou corretamente, retorna LIS_CondRetOK e
*	 o valor recebido por pValor foi inserido na lsita numa posi��o
*	 posterior a do elemento corrente.
*	Se faltou mem�ria, retorna LIS_CondRetFaltouMemoria e  
*	 a lista n�o � modificada
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        );


/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento � esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $EAE Assertivas de entrada
*	  pLista deve ser uma vari�vel do tipo LIS_tppLista alocada pelo trecho
*	  usu�rio da fun��o. 
*	  pLista deve conter um lista gerado por esse m�dulo, i.e.
*	  pela fun��o LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro n�o nulo. 
*	  pLista deve conter uma lista n�o vazia 
*  $FV Valor retornado
*	  Se operou corretamente, retorna LIS_CondRetOK
*     Se a lista j� estiver vazia , retorna LIS_CondRetListaVazia
*  $EAS Assertivas de Sa�da
*	Se operou corretamente, retorna LIS_CondRetOK e
*	  o elemento corrente � exclu�do. 
*	  O elemento da esquerda ser� o novo corrente.
*	  Se este n�o existir, ser� o elemento da direita.
*	  se os dois n�o existirem a lista se tornou vazia
*	Se a lista j� estiver vazia , retorna LIS_CondRetListaVazia
*	  A lista n�o � modificada
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*  $EAE Assertivas de entrada
*	  pLista deve ser uma vari�vel do tipo LIS_tppLista alocada pelo trecho
*	  usu�rio da fun��o. 
*	  pLista deve conter um lista gerado por esse m�dulo, i.e.
*	  pela fun��o LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro n�o nulo. 
*	  pLista deve conter uma lista n�o vazia 
*  $FV Valor retornado
*     n�o NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
* $EAS Assertivas de Sa�da
*	Se a fun��o retornar um ponteiro n�o nulo, este � o valor do elemento corrente
*	se a fun��o retornar nulo , pode ser que a lista esteja vazia ou que o elemento
*	corrente seja null
*
***********************************************************************/

   void * LIS_ObterValor( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento inicial
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*  $EAE Assertivas de entrada
*	  pLista deve ser uma vari�vel do tipo LIS_tppLista alocada pelo trecho
*	  usu�rio da fun��o. 
*	  pLista deve conter um lista gerado por esse m�dulo, i.e.
*	  pela fun��o LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro n�o nulo. 
*	  pLista deve conter uma lista n�o vazia
*	$FV Valor retornado
*	  Se executou corretamente, retorna LIS_CondRetOK
*	  Se a lista estava vazia, retorna LIS_CondRetListaVazia
*  $EAS Assertivas de Sa�da
*	Se executou corretamente, retorna LIS_CondRetOK e
*	  o elemento corrente � o primeiro elemento da lista
*   Se a lista estava vazia, retorna LIS_CondRetListaVazia
*	  a lista n�o � modificada
*
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista ) ;
   


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento final
*
*  $ED Descri��o da fun��o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*  $EAE Assertivas de entrada
*	  pLista deve ser uma vari�vel do tipo LIS_tppLista alocada pelo trecho
*	  usu�rio da fun��o. 
*	  pLista deve conter um lista gerado por esse m�dulo, i.e.
*	  pela fun��o LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro n�o nulo. 
*	  pLista deve conter uma lista n�o vazia
*	$FV Valor retornado
*	  Se executou corretamente, retorna LIS_CondRetOK
*	  Se a lista estava vazia, retorna LIS_CondRetListaVazia
*  $EAS Assertivas de Sa�da
*	Se executou corretamente, retorna LIS_CondRetOK e
*	  o elemento corrente � o �ltimo elemento da lista
*   Se a lista estava vazia, retorna LIS_CondRetListaVazia
*	  a lista n�o � modificada

*
***********************************************************************/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista ) ;
    

/***********************************************************************
*
*  $FC Fun��o: LIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*     dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  $EAE Assertivas de Entrada
*	  pLista deve ser uma vari�vel do tipo LIS_tppLista alocada pelo trecho
*	  usu�rio da fun��o. 
*	  pLista deve conter um lista gerado por esse m�dulo, i.e.
*	  pela fun��o LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro n�o nulo. 
*	  pLista deve conter uma lista n�o vazia
*	  numElem um valor inteiro positivo ou negativo que n�o extrapole
*	  a lista, i.e.,cujo m�dulo � menor que o n�mero de elementos
*	  da lista.
*     valores positivos andam para frente e negativos, para tr�s.
*  $FV Valor retornado
*     LIS_CondRetOK         - se numElem elementos tiverem sido andados
*     LIS_CondRetFimLista   - se encontrou o fim (ou in�cio)da lista antes de andar numElem
*                         elementos
*     LIS_CondRetListaVazia - se a lista est� vazia
*	$EAS Assertivas de Sa�da
*	  Se executou corretamente retorna LIS_CondRetOK e
*	   foi andado o n�mero de elementos (para frente ou para tr�s)
*	   indicado por numElem, e elemento corrente � o da posi��o 
*	   chegada
*	  Se encontrou o fim (ou o in�cio) antes de andar todos os elementos, retorna LIS_CondRetFimLista 
*	   o elemento corrente da lista � o fim (se tentava avan�ar pra frente)
*	   ou o in�cio (se tentava avan�ar pra tr�s)
*	  Se a lista est� vazia, retorna LIS_CondRetListaVazia e
*		a lista m�o � modificada
*	  
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara ponteiro e n�o conte�do apontado.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $EAE Assertivas de Entrada
*	  pLista deve ser uma vari�vel do tipo LIS_tppLista alocada pelo trecho
*	  usu�rio da fun��o. 
*	  pLista deve conter um lista gerado por esse m�dulo, i.e.
*	  pela fun��o LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro n�o nulo. 
*	  pLista deve conter uma lista n�o vazia
*	  pValor deve ser um ponteiro para o tipo de elemento que a lista est� armazenando
*	  (todos os elementos da lista s�o do mesmo tipo)
*	  o m�dulo aceita tamb�m o valor NULL.
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente � o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que cont�m o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro n�o foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*  $EAS Assertivas de Sa�da
*	Se executou corretamente, retorna LIS_CondRetOK e 
*	  o elemento corrente � o elemento procurado
*	Se o elemento nao foi encontrado, retorna LIS_CondRetNaoEncontrou
*	 o elemento corrente en�o � modificado
*	Se a Lista for vazia, retorna LIS_CondRetListaVazia
*	 e a lista n�o � modificada
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;

#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif
