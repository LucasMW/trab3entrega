/***************************************************************************
*  $MCI M�dulo de implementa��o: LAB Labirinto (implementado por grafo)
*
*  Arquivo gerado:              labirinto.c
*  Letras identificadoras:      LAB
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Lucas Menezes (LM); Lorenzo Saraiva (LS); Felipe Santos(FS).
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       LM   24/OUT/2014 in�cio desenvolvimento

***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


#define LAB_OWN
#include "labirinto.h"
#undef LAB_OWN



/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabe�a do labirinto
*
*
***********************************************************************/

typedef enum
		 {
			 LAB_NaoPronto,
			 LAB_Pronto,
			 LAB_Jogando,
			 LAB_GameOver,
			 LAB_Vitoria
		 } LAB_Estado;
   typedef struct LAB_tagLabirinto {

          GRA_tppGrafo pGrafo ;
               /* Ponteiro para a cabe�a do grafo de que armazena as posi��es do labirinto*/

         char pronto;
               /* Vari�vel de Estado se o O labirinto est� pronto pra executar*/
		 int Rodada;
				/* conta o n�mero de jogadas j� feitas */

         
		 
		 LAB_Estado estado;
		 int idCorrente;
			/* id da posi��o corrente */

   } LAB_tpLabirinto ;

   /***********************************************************************
*
*  $TC Tipo de dados: LAB Descritor da posi��o jog�vel do Labirinto
*
*
***********************************************************************/
   typedef enum
	   {
		   PosNormal,
		   /* Posi�ao sem nada de anormal */
		   PosInicio,
		   /*Posi��o do in�cio do labirinto */
		   PosSaida
		  /* Posi��o que demarca o fim do labirinto */
	   } PosJog_Tipo;
			/* Tipo da Pois��o: 0 normal, 1 entrada, 2 sa�da */
	   

   struct LAB_PosicaoJogavel
   {
	      
	   PosJog_Tipo tipo;
   };
   typedef struct LAB_PosicaoJogavel* LAB_PosJog;


  

   /***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static int VerificaPronto( LAB_tppLabirinto labirinto);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***************************************************************************
*
*  Fun��o: LAB  &Criar Labirinto
*  ****/

LAB_tpCondRet LAB_CriarLabirinto( LAB_tppLabirinto* refLab)
{
	LAB_tpLabirinto* tempLab;
	tempLab=(LAB_tpLabirinto*)malloc(sizeof(LAB_tpLabirinto));
	
	if(!tempLab)
		return  LAB_CondRetFaltouMemoria;
		/* if */
	if(GRA_CriarGrafo(&tempLab->pGrafo,free)!=GRA_CondRetOK)
		return LAB_CondRetFaltouMemoria;
		/* if */

	/* if */
	/* N�o houve problemas , retorne OK */
	tempLab->idCorrente=0; //Id Corrents must not exist
	tempLab->estado=LAB_NaoPronto;
	*refLab=tempLab; //return by reference
	return LAB_CondRetOK;
}

/* Fim fun��o: LAB &Destruir Labirinto */

LAB_tpCondRet LAB_DestruirLabirinto( LAB_tppLabirinto labirinto)
{
	GRA_DestruirGrafo(labirinto->pGrafo);
	labirinto->pGrafo=NULL; //make it useless
	labirinto->estado=LAB_NaoPronto;
	labirinto->pronto=0;
	labirinto->Rodada=0;
	free(labirinto);
	labirinto=NULL; //never be acessed again
	return LAB_CondRetOK;
	
}

/* Fim fun��o: LAB &Destruir Labirinto */