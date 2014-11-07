#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, Lucas Menezes <LM>
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  6		  LM	05/nov/2014 Adicionando assertivas e revisão do módulo
*	  5		  LM	02/set/2014 Adaptar Interfaces de funções aos padrões da disciplina
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento de lista */
		 LIS_CondRetNaoDestruiu
		 /* Não Conseguiu Destruir a lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*	  refplista   -endereço ponteiro para a cabeça da lista a ser gerada, a ser retornada por referência
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $EAE Assertivas de entrada
*	  refplista deve ser o endereço de uma variável do tipo 
*	  LIS_tppLista alocada pelo código usuário da função. 
*	  refplista deve ser, portanto, um ponteiro não nulo
*	  ExcluirValor é um ponteiro para uma função que irá excluir os
*	  valores que serão usados na lista
*	  ExcluirValor não pode ser nulo
*  $FV Valor retornado
*     Se executou corretamente retorna LIS_CondRetOK
*     Se faltou memória, retorna LIS_CondRetFaltouMemoria
*	  
*
*  $EAS Assertivas de saída
*	  Se a função operar corretamente, retornará LIS_CondRetOK
*	   e o valor da variável LIS_tppLista cujo endereço foi passado 
*	   à função receberá a lista criada por referência.
*	  Se ocorreu alguma alocação de memória não conseguir ser realizada
*	  A função retornará LIS_CondRetFaltouMemória e o valor de refplista
*	  não será modificado 
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista* refplista,
             void   ( * ExcluirValor ) ( void * pDado ) ) ;
 


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
* $EAE Assertivas de entrada
*	  pLista deve ser uma variável do tipo LIS_tppLista alocada pelo trecho
*	  usuário da função. 
*	  pLista deve conter um lista gerado por esse módulo, i.e.
*	  pela função LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro não nulo.
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
* $EAS Assertivas de saída
*	
*	Se a função operar corretamente o retorno será LIS_CondRetOK
*	e o valor da vaiável LIS_tppLista passada continuará o mesmo,
*	porém, a lista foi liberada da memória e não pode mais ser acessada
*	cabe ao trecho usuário da função atribuir NULL à variável após
*	o uso da função
***********************************************************************/

    LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;
	
	
	


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*  $EAE Assertivas de entrada
*	  pLista deve ser uma variável do tipo LIS_tppLista alocada pelo trecho
*	  usuário da função. 
*	  pLista deve conter um lista gerado por esse módulo, i.e.
*	  pela função LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro não nulo.
*  $FV Valor Retornado
*	  Se operou corrtemente retorna LIS_CondRetOK
*	  Se a lista já estava vazia retorna LIS_CondRetListaVazia
*  $EAS Assettivas de Saída
*	Se operou corrtemente retorna LIS_CondRetOK e 
*	  a pLista continua com seu valor, porém a lista liberou
*	  todos os seus elementos, retornando ao estado de criação.
*	Se a lista já estava vazia retorna LIS_CondRetListaVazia
*	  e a lista não é modificada.
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*	  
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*  $EAE Assertivas de entrada
*	  pLista deve ser uma variável do tipo LIS_tppLista alocada pelo trecho
*	  usuário da função. 
*	  pLista deve conter um lista gerado por esse módulo, i.e.
*	  pela função LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro não nulo. 
*	  pValor deve ser um ponteiro para o tipo de elemento que a lista está armazenando
*	  (todos os elementos da lista são do mesmo tipo)
*	  o módulo aceita também o valor NULL.
*  $FV Valor retornado
*    Se executou corretamente, LIS_CondRetOK
*    Se faltou memória, LIS_CondRetFaltouMemoria
*  $EAS Assertivas de Saída
*	Se executou corretamente, retorna LIS_CondRetOK e
*	 o valor recebido por pValor foi inserido na lsita numa posição
*	 anterior a do elemento corrente.
*	Se faltou memória, retorna LIS_CondRetFaltouMemoria e  
*	 a lista não é modificada
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*  $EAE Assertivas de entrada
*	  pLista deve ser uma variável do tipo LIS_tppLista alocada pelo trecho
*	  usuário da função. 
*	  pLista deve conter um lista gerado por esse módulo, i.e.
*	  pela função LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro não nulo. 
*	  pValor deve ser um ponteiro para o tipo de elemento que a lista está armazenando
*	  (todos os elementos da lista são do mesmo tipo)
*	  o módulo aceita também o valor NULL.
*  $FV Valor retornado
*    Se executou corretamente, LIS_CondRetOK
*    Se faltou memória, LIS_CondRetFaltouMemoria
*  $EAS Assertivas de Saída
*	Se executou corretamente, retorna LIS_CondRetOK e
*	 o valor recebido por pValor foi inserido na lsita numa posição
*	 posterior a do elemento corrente.
*	Se faltou memória, retorna LIS_CondRetFaltouMemoria e  
*	 a lista não é modificada
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        );


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento à esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $EAE Assertivas de entrada
*	  pLista deve ser uma variável do tipo LIS_tppLista alocada pelo trecho
*	  usuário da função. 
*	  pLista deve conter um lista gerado por esse módulo, i.e.
*	  pela função LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro não nulo. 
*	  pLista deve conter uma lista não vazia 
*  $FV Valor retornado
*	  Se operou corretamente, retorna LIS_CondRetOK
*     Se a lista já estiver vazia , retorna LIS_CondRetListaVazia
*  $EAS Assertivas de Saída
*	Se operou corretamente, retorna LIS_CondRetOK e
*	  o elemento corrente é excluído. 
*	  O elemento da esquerda será o novo corrente.
*	  Se este não existir, será o elemento da direita.
*	  se os dois não existirem a lista se tornou vazia
*	Se a lista já estiver vazia , retorna LIS_CondRetListaVazia
*	  A lista não é modificada
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*  $EAE Assertivas de entrada
*	  pLista deve ser uma variável do tipo LIS_tppLista alocada pelo trecho
*	  usuário da função. 
*	  pLista deve conter um lista gerado por esse módulo, i.e.
*	  pela função LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro não nulo. 
*	  pLista deve conter uma lista não vazia 
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
* $EAS Assertivas de Saída
*	Se a função retornar um ponteiro não nulo, este é o valor do elemento corrente
*	se a função retornar nulo , pode ser que a lista esteja vazia ou que o elemento
*	corrente seja null
*
***********************************************************************/

   void * LIS_ObterValor( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*  $EAE Assertivas de entrada
*	  pLista deve ser uma variável do tipo LIS_tppLista alocada pelo trecho
*	  usuário da função. 
*	  pLista deve conter um lista gerado por esse módulo, i.e.
*	  pela função LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro não nulo. 
*	  pLista deve conter uma lista não vazia
*	$FV Valor retornado
*	  Se executou corretamente, retorna LIS_CondRetOK
*	  Se a lista estava vazia, retorna LIS_CondRetListaVazia
*  $EAS Assertivas de Saída
*	Se executou corretamente, retorna LIS_CondRetOK e
*	  o elemento corrente é o primeiro elemento da lista
*   Se a lista estava vazia, retorna LIS_CondRetListaVazia
*	  a lista não é modificada
*
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista ) ;
   


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*  $EAE Assertivas de entrada
*	  pLista deve ser uma variável do tipo LIS_tppLista alocada pelo trecho
*	  usuário da função. 
*	  pLista deve conter um lista gerado por esse módulo, i.e.
*	  pela função LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro não nulo. 
*	  pLista deve conter uma lista não vazia
*	$FV Valor retornado
*	  Se executou corretamente, retorna LIS_CondRetOK
*	  Se a lista estava vazia, retorna LIS_CondRetListaVazia
*  $EAS Assertivas de Saída
*	Se executou corretamente, retorna LIS_CondRetOK e
*	  o elemento corrente é o último elemento da lista
*   Se a lista estava vazia, retorna LIS_CondRetListaVazia
*	  a lista não é modificada

*
***********************************************************************/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista ) ;
    

/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*     direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $EAE Assertivas de Entrada
*	  pLista deve ser uma variável do tipo LIS_tppLista alocada pelo trecho
*	  usuário da função. 
*	  pLista deve conter um lista gerado por esse módulo, i.e.
*	  pela função LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro não nulo. 
*	  pLista deve conter uma lista não vazia
*	  numElem um valor inteiro positivo ou negativo que não extrapole
*	  a lista, i.e.,cujo módulo é menor que o número de elementos
*	  da lista.
*     valores positivos andam para frente e negativos, para trás.
*  $FV Valor retornado
*     LIS_CondRetOK         - se numElem elementos tiverem sido andados
*     LIS_CondRetFimLista   - se encontrou o fim (ou início)da lista antes de andar numElem
*                         elementos
*     LIS_CondRetListaVazia - se a lista está vazia
*	$EAS Assertivas de Saída
*	  Se executou corretamente retorna LIS_CondRetOK e
*	   foi andado o número de elementos (para frente ou para trás)
*	   indicado por numElem, e elemento corrente é o da posição 
*	   chegada
*	  Se encontrou o fim (ou o início) antes de andar todos os elementos, retorna LIS_CondRetFimLista 
*	   o elemento corrente da lista é o fim (se tentava avançar pra frente)
*	   ou o início (se tentava avançar pra trás)
*	  Se a lista está vazia, retorna LIS_CondRetListaVazia e
*		a lista mão é modificada
*	  
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $EAE Assertivas de Entrada
*	  pLista deve ser uma variável do tipo LIS_tppLista alocada pelo trecho
*	  usuário da função. 
*	  pLista deve conter um lista gerado por esse módulo, i.e.
*	  pela função LIS_CriarLista;
*	  pLista deve ser, portanto, um ponteiro não nulo. 
*	  pLista deve conter uma lista não vazia
*	  pValor deve ser um ponteiro para o tipo de elemento que a lista está armazenando
*	  (todos os elementos da lista são do mesmo tipo)
*	  o módulo aceita também o valor NULL.
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*  $EAS Assertivas de Saída
*	Se executou corretamente, retorna LIS_CondRetOK e 
*	  o elemento corrente é o elemento procurado
*	Se o elemento nao foi encontrado, retorna LIS_CondRetNaoEncontrou
*	 o elemento corrente enão é modificado
*	Se a Lista for vazia, retorna LIS_CondRetListaVazia
*	 e a lista não é modificada
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
