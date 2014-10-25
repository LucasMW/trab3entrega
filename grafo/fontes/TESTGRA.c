/***************************************************************************
*  $MCI Módulo de implementação: TGRA Teste grafo genérico
*
*  Arquivo gerado:              TestGRA.c
*  Letras identificadoras:      TGRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\Grafo.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Lucas Menezes (LM); Lorenzo Saraiva (LS); Felipe Santos(FS).
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       LM,LS  22/SET/2014 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "grafo.h"


static const char RESET_GRAFO_CMD         [ ] = "=resetgrafo"     ;
static const char CRIAR_GRAFO_CMD         [ ] = "=criargrafo"     ;
static const char DESTRUIR_GRAFO_CMD      [ ] = "=destruirgrafo"  ;
static const char ESVAZIAR_GRAFO_CMD      [ ] = "=esvaziargrafo"  ;
static const char INSERIR_NO_CMD          [ ] = "=inserirno"	  ;
static const char INSERIR_ARESTA_CMD      [ ] = "=inseriraresta"  ;
static const char OBTER_VALOR_NO_CMD      [ ] = "=obtervalorno"	  ;
static const char EXC_NO_CMD              [ ] = "=excluirno"      ;
static const char EXC_ARESTA_CMD          [ ] = "=excluiraresta"  ;
static const char IMPRIMIR_GRAFO_CMD      [ ] = "=imprimirgrafo"  ;
static const char OBTER_ID_CMD		  [ ] = "=obteridcorr"    ;
static const char OBTER_VALOR_CORR_CMD	  [ ] = "=obtervalorcorr" ;
static const char IR_VIZINHO_CMD          [ ] = "=irvizinho"      ;
static const char EXC_CORR_CMD		  [ ] = "=excluircorr"	  ;
static const char IR_PARA_CMD		  [ ] = "=irpara"	  ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO   10
#define DIM_VALOR     100

GRA_tppGrafo   VTGRAFO[ DIM_VT_GRAFO ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxGrafo( int inxGrafo , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRA &Testar grafo
*
*  $ED Descrição da função
*     Podem ser criadas até 10 grafos, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     
*     =criargrafo                   inxGrafo   
*     =destruirgrafo                inxGrafo	
*     =esvaziargrafo                inxGrafo
*     =inserirno					inxGrafo  string  CondRetEsp
*     =inseriraresta                inxGrafo  NoId_X NoId_Y Value CondRetEsp
*     =obtervalorno					inxGrafo  NoId StringEsp CondRetEsp
*     =imprimirgrafo				inxGrafo  CondRetEsp
*     =excluirno					inxGrafo  NoId	CondRetEsp
*	  =excluircorr					inxGrafo  CondRetEsp
*     =obteridcorr                  inxGrafo  ValorEsp CondRetEsp
*     =obtervalorcorr               inxGrafo  StringEsp  ConRetEsp
*     =obteridcorr                  inxGrafo  idEsp CondRetEs
*	  
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
	   GRA_tppGrafo epGrafo=NULL;


      int inxGrafo  = -1 ,
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

      /* Efetuar reset de teste de grafo */

         if ( strcmp( ComandoTeste , RESET_GRAFO_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_GRAFO ; i++ )
            {
               VTGRAFO[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de grafo */

      /* Testar CriarGrafo */

         else if ( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxGrafo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxGrafo( inxGrafo , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */


                 GRA_CriarGrafo(&VTGRAFO[ inxGrafo ],free) ;
				 //epgrafo retornado por ref

            return TST_CompararPonteiroNulo( 1 , VTGRAFO[ inxGrafo ] ,
               "Erro em ponteiro de novo grafo."  ) ;

         } /* fim ativa: Testar CriarGrafo */

      /* Testar Esvaziar grafo grafo */

         else if ( strcmp( ComandoTeste , ESVAZIAR_GRAFO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxGrafo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            GRA_EsvaziarGrafo( VTGRAFO[ inxGrafo ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar grafo grafo */

      /* Testar Destruir grafo */

         else if ( strcmp( ComandoTeste , DESTRUIR_GRAFO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxGrafo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

           CondRet=(TST_tpCondRet)GRA_DestruirGrafo( VTGRAFO[ inxGrafo ] ) ;
            VTGRAFO[ inxGrafo ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir grafo */

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INSERIR_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxGrafo , &StringDado, &CondRetEsp ) ;
			
            if ( ( numLidos != 3 )  || ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			intpointer=(int*)malloc(sizeof(int));
			if(!intpointer)
				return TST_CondRetMemoria;
           pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;

			
			
            CondRet =(TST_tpCondRet) GRA_InserirNo( VTGRAFO[ inxGrafo ],&pDado,intpointer) ;


            if ( CondRet != GRA_CondRetOK )
            {
               free( pDado ) ;
            } 

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir No no grafo."                   ) ;

         } /* fim ativa: Testar inserir nó */

		 else if (strcmp( ComandoTeste , IMPRIMIR_GRAFO_CMD ) == 0)
		 {
			 numLidos = LER_LerParametros( "ii",&inxGrafo,&CondRetEsp) ;
			  if ( ( numLidos != 2 )|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			  CondRet =(TST_tpCondRet) GRA_ImprimirGrafo( VTGRAFO[ inxGrafo ]) ;
			   if ( CondRet != CondRetEsp )
            {
              printf("\nA CondRet foi %d\n",CondRet);
            } 
			   return TST_CompararInt( CondRetEsp, CondRet, "DEU RUIM");
		 }

         /* fim ativa: Testar ImprimirGrafo */

		 /* Testar InserirAresta */
		  else if (strcmp( ComandoTeste , INSERIR_ARESTA_CMD ) == 0)
		 {
			 numLidos = LER_LerParametros( "iiiii",&inxGrafo,&i,&j,&valorAresta,&CondRetEsp) ;
			  if ( ( numLidos != 5 )|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			  CondRet =(TST_tpCondRet) GRA_InserirAresta( VTGRAFO[ inxGrafo ],i,j,valorAresta) ;
			   if ( CondRet != CondRetEsp )
            {
              printf("\nA CondRet foi %d\n",CondRet);
            } 
			   return TST_CompararInt( CondRetEsp, CondRet, "Condição de retorno errada no InserirAresta");
		 }

      /* Testar excluir aresta */

		 /* Testar ObterValorNo*/
		  
		 else if (strcmp( ComandoTeste , OBTER_VALOR_NO_CMD ) == 0)
		 {
			 numLidos = LER_LerParametros( "iisi",&inxGrafo,&i,&StringDado,&CondRetEsp) ;
			  if ( ( numLidos != 4 )|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			  
			 pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
			 strcpy(pDado,StringDado);
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */
		
		
            CondRet =(TST_tpCondRet) GRA_ObterValorNo( VTGRAFO[ inxGrafo ],i,(void**)&strp);
			
		  if(pDado==NULL)
		  {	
			
			  return TST_CompararPonteiroNulo( 1 , pDado ,"Dado deveria existir." ) ;
		  }
		  if(CondRetEsp!=CondRet)
		  {
			  
		     return TST_CompararInt( CondRetEsp, CondRet, "Condição de retorno errada no ObterValor");
		  }
		
			  return TST_CompararString( *strp , pDado ,
                         "\tValor diferente o esperado " ) ;
		  
		 }
		 /* fim ativa: Testar ObterValorNo */

		   else if (strcmp( ComandoTeste , OBTER_VALOR_CORR_CMD ) == 0)
		 {
			 numLidos = LER_LerParametros( "isi",&inxGrafo,&StringDado,&CondRetEsp) ;
			  if ( ( numLidos != 3 )|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			  
			 pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
			 strcpy(pDado,StringDado);
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */
		
		
            CondRet =(TST_tpCondRet) GRA_ObterValorNoCorrente( VTGRAFO[ inxGrafo ],(void**)&strp);
			
		  if(pDado==NULL)
		  {	
			
			  return TST_CompararPonteiroNulo( 1 , pDado ,"Dado deveria existir." ) ;
		  }
		  if(CondRetEsp!=CondRet)
		  {
			  
		     return TST_CompararInt( CondRetEsp, CondRet, "Condição de retorno errada no ObterValorNoCorrente");
		  }
		
			  return TST_CompararString( *strp , pDado ,
                         "\tValor diferente o esperado " ) ;
		  
		 }
		 /* fim ativa: Testar ObterValorNoCorrrente */

		 else if (strcmp( ComandoTeste , EXC_ARESTA_CMD ) == 0)
		 {
			 numLidos = LER_LerParametros( "iiii",&inxGrafo,&i,&j,&CondRetEsp) ;
			  if ( ( numLidos != 4 )|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			  CondRet =(TST_tpCondRet) GRA_ExcluirAresta( VTGRAFO[ inxGrafo ],i,j) ;
			   if ( CondRet != CondRetEsp )
            {
              printf("\nA CondRet foi %d\n %d %d",CondRet,i,j);
            } 
			   return TST_CompararInt( CondRetEsp, CondRet, "Condição de retorno errada no ExcluirAresta");
		 }

          /* fim ativa: GRA  Excluir aresta */

		    else if (strcmp( ComandoTeste , IR_PARA_CMD ) == 0)
		 {
			 numLidos = LER_LerParametros( "iii",&inxGrafo,&noCorrente,&CondRetEsp) ;
			  if ( ( numLidos != 3 )|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			  CondRet =(TST_tpCondRet) GRA_IrParaNo( VTGRAFO[ inxGrafo ],noCorrente) ;
			  
			   if ( CondRet != CondRetEsp )
            {
              printf("\nA CondRet foi %d\n %d %d",CondRet,i,j);
            } 
			   return TST_CompararInt( CondRetEsp, CondRet, "Condição de retorno errada no IrPara");
		 }

		   else if (strcmp( ComandoTeste , EXC_NO_CMD ) == 0)
		 {
			 numLidos = LER_LerParametros( "iii",&inxGrafo,&i,&CondRetEsp) ;
			  if ( ( numLidos != 3 )|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			  CondRet =(TST_tpCondRet) GRA_ExcluirNo( VTGRAFO[ inxGrafo ],i) ;
			   if ( CondRet != CondRetEsp )
            {
              printf("\nA CondRet foi %d\n",CondRet);
            } 
			   return TST_CompararInt( CondRetEsp, CondRet, "Condição de retorno errada no ExcluirNo");
		 }

		 else if (strcmp( ComandoTeste , EXC_CORR_CMD ) == 0)
		 {
			 numLidos = LER_LerParametros( "ii",&inxGrafo, &CondRetEsp) ;
			  if ( ( numLidos != 2 )|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			  CondRet =(TST_tpCondRet) GRA_ExcluirNoCorrente( VTGRAFO[ inxGrafo ]) ;
			   if ( CondRet != CondRetEsp )
            {
              printf("\nA CondRet foi %d\n %d %d",CondRet,i,j);
            } 
			   return TST_CompararInt( CondRetEsp, CondRet, "Condição de retorno errada no ExcluirNoCorrente");
		 }

		  else if (strcmp( ComandoTeste , ESVAZIAR_GRAFO_CMD ) == 0)
		 {
			 numLidos = LER_LerParametros( "ii",&inxGrafo, &CondRetEsp) ;
			  if ( ( numLidos != 2 )|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			  CondRet =(TST_tpCondRet) GRA_EsvaziarGrafo( VTGRAFO[ inxGrafo ]) ;
			   if ( CondRet != CondRetEsp )
            {
              printf("\nA CondRet foi %d\n %d %d",CondRet,i,j);
            } 
			   return TST_CompararInt( CondRetEsp, CondRet, "Condição de retorno errada no EsvaziarGrafo");
		 }

		 else if (strcmp( ComandoTeste , OBTER_ID_CMD ) == 0)
		 {
			 numLidos = LER_LerParametros( "iii",&inxGrafo, &CondRetEsp, &noCorrenteEsperado) ;
			  if ( ( numLidos != 3 )|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			  CondRet =(TST_tpCondRet) GRA_ObterNoCorrente( VTGRAFO[ inxGrafo ],&noCorrente) ;
			   if ( CondRet != CondRetEsp )
            {
              printf("\nA CondRet foi %d\n %d %d",CondRet,i,j);
            } 
			   return TST_CompararInt( noCorrenteEsperado, noCorrente , "Nó diferente do esperado");
		 }

		  else if (strcmp( ComandoTeste , IR_VIZINHO_CMD ) == 0)
		 {
			 numLidos = LER_LerParametros( "iii",&inxGrafo, &CondRetEsp, &noCorrente) ;
			  if ( ( numLidos != 3 )|| ( ! ValidarInxGrafo( inxGrafo , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			  CondRet =(TST_tpCondRet) GRA_IrNoVizinho( VTGRAFO[ inxGrafo ],noCorrente) ;
			   if ( CondRet != CondRetEsp )
            {
              printf("\nA CondRet foi %d\n %d %d",CondRet,i,j);
            } 
			    return TST_CompararInt( CondRetEsp, CondRet, "Condição de retorno errada no IrNoVizinho");
		 }
      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TGRA &Testar grafo */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TGRA -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim fun��o: TGRA -Destruir valor */


/***********************************************************************
*
*  $FC Fun��o: TGRA -Validar indice de grafo
*
***********************************************************************/

   int ValidarInxGrafo( int inxGrafo , int Modo )
   {

      if ( ( inxGrafo <  0 )
        || ( inxGrafo >= DIM_VT_GRAFO ))
      {
         return FALSE ;
      } /* if */

      if ( Modo == VAZIO )
      {
         if ( VTGRAFO[ inxGrafo ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( VTGRAFO[ inxGrafo ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */

      return TRUE ;

   } /* Fim fun��o: TGRA -Validar indice de grafo */

/********** Fim do m�dulo de implementa��o: TGRA Teste grafo de s�mbolos **********/
