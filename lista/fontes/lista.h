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
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
*  $EAE Assertivas de entrada
*     ExcluirValor é um ponteiro para uma função que irá excluir os
*        valores que serão usados na lista
*
*  $EAE Assertivas de saída
*     Retorna um ponteiro válido para a lista que foi criada se tiver sido executado
*       corretamente.
*     Retorna NULL caso ocorra erro.
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista* refplista,
             void   ( * ExcluirValor ) ( void * pDado ) ) ;
   /* Mudança: Retorna Condições de Retorno, e recebe o ponteiro onde jogará a lista por referência */
   /* CondRet: 
   OK
   FaltouMemoria
   */


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
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     A lista foi destruída.
*     Memória total da lista (todos os elementos) é liberada.
*     Havendo erro no processo de destruição, a lista poderá acabar
*     com alguma inconsistência (inválida). Estrutura de lista desconfigurada.
* 
* 
***********************************************************************/

    LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;
	/* Mudança: Retorna agora condições de retorno 
	nome mudado para começar com LIS
	CondRet:
	OK
	NaoDestruiu
	*/


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Lista vazia, nenhum elemento na lista.
*     Memória total da lista é liberada (de todos os elementos).
* 
* 
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;
   /* Mudança: retorna agora condição de retorno
   CondRet:
   OK
   ListaVazia
   */


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
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
* 
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se LIS_CondRetOK:
*       Caso a lista antes esteja vazia, passa a ter o primeiro elemento
*        e seu valor será pValor. Nó corrente passa a ser este elemento.
*       Senão, lista passa a ter mais um elemento e este por sua vez é
*        inserido uma posição antes do nó corrente (vizinho predecessor).
* 	 Nó corrente não se altera.
*     Se LIS_CondRetFaltouMemoria:
*       A lista não é modificada.
*
* 
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
*     
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
* $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se LIS_CondRetOK:
*       Caso a lista anterir esteja vazia, passa a ter um elemento,
*         valorado com pValor. Nó corrente passa a ser este elemento.
*       Senão, lista passa a ter mais um elemento. Este é inserido 
* 	  subsequentemente após o nó corrente. Nó corrente não se altera.
*     Se LIS_CondRetFaltouMemoria:
*       A lista não é alterada.
* 
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
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se LIS_CondRetOK:
*       Se Lista anterior diferente de vazia. Passa a ter menos um elemento.
*       Excluí elemento corrente. Seu valor é liberado.
*       Existindo elementoa à esquerda do que era o corrente, passa a ser
* 	o novo elemento corrente.
*       Senão, caso exista elemento à direita, este vira o corrente.
*       Caso contrário, lista está (virou) vazia.
*     Se LIS_CondRetListaVazia:
*       Lista anterior estava vazia. Não sofre alteração.
* 
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
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Para retorno == NULL;
*       Lista vazia ou elemento inserido no nó corrente é NULL.
*     Caso contrário;
*       Se lista não estiver vazia, retono é o elemento inserido no nó corrente.
* 
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
*
* $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Caso a lista esteja vazia;
*       Lista não é alterada.
*     Senão;
*       Nó corrente passa a ser o primeiro nó.
* 
* 
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista ) ;

   /* Mudança: Adicionado LIS no nome, pois pertence a esse modulo
   Adicionadas Condições de Retorno 
   CondRet
   OK
   ListaVazia -Não é erro, segundo a especificação acima, só não faz nada
   */



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
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se lista estiver vazia;
*       Lista não é alterada.
*     Caso contrário;
*       Nó corrente passa a ser o último nó.
* 
* 
***********************************************************************/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista ) ;
   /* Mudança: O nome foi pra LIS_IrFinalLista pois é parte do módulo LIS
   adicionadas condições de retorno
   OK
   ListaVazia -Não é erro, segundo a especificação acima, só não faz nada
   */
    

/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
* $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se LIS_CondRetOK:
*       Lista não era vazia.
*       Se numElem == 0:
*         Lista permanece inalterada.
*       Se numElem > 0:
*         Andou-se numElem elementos para o fim da lista sem erros.
*       Se numElem < 0:
*         Andou-se numElem elementos para o início da lista sem erros.
*     Se LIS_CondRetFimLista:
*       Se numElem > 0:
*         Andous-se n < numElem elementos para o fim da lista sem erros.
*       Se numElem < 0:
*         Andous-se n < numElem elementos para o início da lista sem erros
*     Se LIS_CondRetListaVazia:
*       Lista vazia. Não é alterada.
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
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
 * $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se LIS_CondRetOK:
*       Novo nó corrente é o primeiro nó a partir do antigo corrente 
*       (inclusive) até o final da lista cujo valor é igual a pValor.
*     Se LIS_CondRetNaoAchou:
*       Lista não é alterada.
*     Se LIS_CondRetListaVazia:
*       Lista vazia. Não é alterada.
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
