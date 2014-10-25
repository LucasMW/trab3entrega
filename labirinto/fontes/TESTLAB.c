/***************************************************************************
*  $MCI Módulo de implementação: TLAB Teste módulo Labirinto 
*
*  Arquivo gerado:              TestLAB.c
*  Letras identificadoras:      TLAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Labirinto.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Lucas Menezes (LM); Lorenzo Saraiva (LS); Felipe Santos(FS).
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       LM,LS  25/OUT/2014 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "labirinto.h"


static const char RESET_LABIRINTO_CMD         [ ] = "=resetlabirinto"     ;
static const char CRIAR_LABIRINTO_CMD         [ ] = "=criarlabirinto"     ;
static const char DESTRUIR_LABIRINTO_CMD      [ ] = "=destruirlabirinto"  ;
static const char ESVAZIAR_LABIRINTO_CMD      [ ] = "=esvaziarlabirinto"  ;
static const char INSERIR_NO_CMD          [ ] = "=inserirno"	  ;
static const char INSERIR_ARESTA_CMD      [ ] = "=inseriraresta"  ;
static const char OBTER_VALOR_NO_CMD      [ ] = "=obtervalorno"	  ;
static const char EXC_NO_CMD              [ ] = "=excluirno"      ;
static const char EXC_ARESTA_CMD          [ ] = "=excluiraresta"  ;
static const char IMPRIMIR_LABIRINTO_CMD      [ ] = "=imprimirlabirinto"  ;
static const char OBTER_ID_CMD		  [ ] = "=obteridcorr"    ;
static const char OBTER_VALOR_CORR_CMD	  [ ] = "=obtervalorcorr" ;
static const char IR_VIZINHO_CMD          [ ] = "=irvizinho"      ;
static const char EXC_CORR_CMD		  [ ] = "=excluircorr"	  ;
static const char IR_PARA_CMD		  [ ] = "=irpara"	  ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LABIRINTO   10
#define DIM_VALOR     100

LAB_tppLabirinto   VTLABIRINTO[ DIM_VT_LABIRINTO ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLabirinto( int inxLabirinto , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLAB &Testar labirinto
*
*  $ED Descrição da função
*     Podem ser criadas até 10 labirintos, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     
*     =criarlabirinto                   inxLabirinto   
*     =destruirlabirinto                inxLabirinto	
*     =esvaziarlabirinto                inxLabirinto
*     =inserirno					inxLabirinto  string  CondRetEsp
*     =inseriraresta                inxLabirinto  NoId_X NoId_Y Value CondRetEsp
*     =obtervalorno					inxLabirinto  NoId StringEsp CondRetEsp
*     =imprimirlabirinto				inxLabirinto  CondRetEsp
*     =excluirno					inxLabirinto  NoId	CondRetEsp
*	  =excluircorr					inxLabirinto  CondRetEsp
*     =obteridcorr                  inxLabirinto  ValorEsp CondRetEsp
*     =obtervalorcorr               inxLabirinto  StringEsp  ConRetEsp
*     =obteridcorr                  inxLabirinto  idEsp CondRetEs
*	  
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
	   LAB_tppLabirinto epLabirinto=NULL;


      int inxLabirinto  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char   StringDado[  DIM_VALOR ] ;
      char * pDado ;
	  char ** strp;

      int ValEsp = -1 ;

      int i ;
	  int j;
	  int noCorrente;
	  int noCorrenteEsperado;
	  int* intpointer;
      int numElem = -1 ;
	  int valorAresta;
      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de labirinto */

         if ( strcmp( ComandoTeste , RESET_LABIRINTO_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LABIRINTO ; i++ )
            {
               VTLABIRINTO[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de labirinto */

      /* Testar CriarLabirinto */

         else if ( strcmp( ComandoTeste , CRIAR_LABIRINTO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxLabirinto ) ;

			
            if ( ( numLidos != 1 )
              || ( ! ValidarInxLabirinto( inxLabirinto , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			
            LAB_CriarLabirinto(&VTLABIRINTO[ inxLabirinto ]) ;
				 //eplabirinto retornado por ref

            return TST_CompararPonteiroNulo( 1 , VTLABIRINTO[ inxLabirinto ] ,
               "Erro em ponteiro de novo labirinto."  ) ;

         } /* fim ativa: Testar CriarLabirinto */
		    /* Testar CriarLabirinto */

         else if ( strcmp( ComandoTeste , DESTRUIR_LABIRINTO_CMD ) == 0 )
         {

           numLidos = LER_LerParametros( "i" ,
                       &inxLabirinto ) ;
		   
            if ( ( numLidos != 1 )
              || ( ! ValidarInxLabirinto( inxLabirinto , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			
            LAB_DestruirLabirinto(VTLABIRINTO[ inxLabirinto ]) ;
				 //eplabirinto retornado por ref
			VTLABIRINTO[inxLabirinto]=0;
            return TST_CompararPonteiroNulo( 0 , VTLABIRINTO[ inxLabirinto ] ,
               "Erro em ponteiro de labirinto."  ) ;

         } /* fim ativa: Testar DestruirLabirinto */
   }
   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLAB -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLAB -Validar indice de labirinto
*
***********************************************************************/

   int ValidarInxLabirinto( int inxLabirinto , int Modo )
   {

      if ( ( inxLabirinto <  0 )
        || ( inxLabirinto >= DIM_VT_LABIRINTO ))
      {
         return FALSE ;
      } /* if */

      if ( Modo == VAZIO )
      {
         if ( VTLABIRINTO[ inxLabirinto ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( VTLABIRINTO[ inxLabirinto ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */

      return TRUE ;

   } /* Fim função: TLAB -Validar indice de labirinto */

/********** Fim do módulo de implementação: TLAB Teste labirinto de símbolos **********/
