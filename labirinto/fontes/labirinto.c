/***************************************************************************
*  $MCI Módulo de implementação: LAB Labirinto (implementado por grafo)
*
*  Arquivo gerado:              labirinto.c
*  Letras identificadoras:      LAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Lucas Menezes (LM); Lorenzo Saraiva (LS); Felipe Santos(FS).
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       LM   24/OUT/2014 início desenvolvimento

***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


#define LAB_OWN
#include "labirinto.h"
#undef LAB_OWN



/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça do labirinto
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
               /* Ponteiro para a cabeça do grafo de que armazena as posições do labirinto*/

         char pronto;
               /* Variável de Estado se o O labirinto está pronto pra executar*/
		 int Rodada;
				/* conta o número de jogadas já feitas */

         
		 
		 LAB_Estado estado;
		 int idCorrente;
			/* id da posição corrente */

   } LAB_tpLabirinto ;

   /***********************************************************************
*
*  $TC Tipo de dados: LAB Descritor da posição jogável do Labirinto
*
*
***********************************************************************/
  
	   

   struct LAB_PosicaoJogavel
   {
	      
	   PosJog_Tipo tipo;
	   int idNorte;
	   int idSul;
	   int idOeste;
	   int idLeste;
   };
   typedef struct LAB_PosicaoJogavel* LAB_PosJog;


  

   /***** Protótipos das funções encapuladas no módulo *****/

   static int VerificaPronto( LAB_tppLabirinto labirinto);

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: LAB  &Criar Labirinto
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
	/* Não houve problemas , retorne OK */
	tempLab->idCorrente=0; //Id Corrents must not exist
	tempLab->estado=LAB_NaoPronto;
	*refLab=tempLab; //return by reference
	return LAB_CondRetOK;
}

/* Fim função: LAB &Destruir Labirinto */

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

/* Fim função: LAB &Destruir Labirinto */

/***************************************************************************
*
*  Função: LAB &Inserir Posicao Norte
*  ****/

LAB_tpCondRet LAB_InserirPosicaoNorte ( LAB_tppLabirinto labirinto, PosJog_Tipo tipo )
{
	LAB_PosJog posicaoNova, posicaoOrigem;
	posicaoNova = (LAB_PosJog)malloc(sizeof(LAB_PosJog));
	posicaoNova->tipo = tipo;
	posicaoNova->idLeste = 0;
	posicaoNova->idOeste = 0;
	posicaoNova->idNorte = 0;
	posicaoNova->idSul = labirinto->idCorrente;
	if (labirinto->idCorrente = 0){
		if( GRA_InserirNo( labirinto->pGrafo,posicaoNova,&labirinto->idCorrente ) != GRA_CondRetOK)
			return LAB_CondRetFaltouMemoria;
		return LAB_CondRetOK;
	}
	
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente,(void**)&posicaoOrigem);
	if (posicaoOrigem->idNorte != 0){
		free(posicaoNova);
		return LAB_tpCondRetJaExistePosicao;	
	}
	if (GRA_InserirNo( labirinto->pGrafo,posicaoNova,&labirinto->idCorrente ) != GRA_CondRetOK)
		return LAB_CondRetFaltouMemoria;
	if (GRA_InserirAresta(labirinto->pGrafo,labirinto->idCorrente,posicaoNova->idSul, 0)!= GRA_CondRetOK)
		return LAB_CondRetFaltouMemoria; /* Aqui deve ser checada a condret retornada para ver corretamente o erro */
	posicaoOrigem->idNorte = labirinto->idCorrente;
	return LAB_CondRetOK;
}

/* Fim função: LAB &Inserir Posicao Norte */

/***************************************************************************
*
*  Função: LAB &Inserir Posicao Sul
*  ****/

LAB_tpCondRet LAB_InserirPosicaoSul ( LAB_tppLabirinto labirinto, PosJog_Tipo tipo )
{
	LAB_PosJog posicaoNova, posicaoOrigem;
	posicaoNova = (LAB_PosJog)malloc(sizeof(LAB_PosJog));
	posicaoNova->tipo = tipo;
	posicaoNova->idLeste = 0;
	posicaoNova->idOeste = 0;
	posicaoNova->idNorte = labirinto->idCorrente;
	posicaoNova->idSul = 0;
	if (labirinto->idCorrente = 0){
		if( GRA_InserirNo( labirinto->pGrafo,posicaoNova,&labirinto->idCorrente ) != GRA_CondRetOK)
			return LAB_CondRetFaltouMemoria;
		return LAB_CondRetOK;
	}
	
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente,(void**)&posicaoOrigem);
	if (posicaoOrigem->idSul != 0){
		free(posicaoNova);
		return LAB_tpCondRetJaExistePosicao;	
	}
	if (GRA_InserirNo( labirinto->pGrafo,posicaoNova,&labirinto->idCorrente ) != GRA_CondRetOK)
		return LAB_CondRetFaltouMemoria;
	if (GRA_InserirAresta(labirinto->pGrafo,labirinto->idCorrente,posicaoNova->idNorte, 0)!= GRA_CondRetOK)
		return LAB_CondRetFaltouMemoria; /* Aqui deve ser checada a condret retornada para ver corretamente o erro */
	posicaoOrigem->idSul = labirinto->idCorrente;
	return LAB_CondRetOK;
}

/* Fim função: LAB &Inserir Posicao Sul */


/***************************************************************************
*
*  Função: LAB &Inserir Posicao Oeste
*  ****/

LAB_tpCondRet LAB_InserirPosicaoOeste ( LAB_tppLabirinto labirinto, PosJog_Tipo tipo )
{
	LAB_PosJog posicaoNova, posicaoOrigem;
	posicaoNova = (LAB_PosJog)malloc(sizeof(LAB_PosJog));
	posicaoNova->tipo = tipo;
	posicaoNova->idLeste = labirinto->idCorrente;
	posicaoNova->idOeste = 0;
	posicaoNova->idNorte = 0;
	posicaoNova->idSul = 0;
	if (labirinto->idCorrente = 0){
		if( GRA_InserirNo( labirinto->pGrafo,posicaoNova,&labirinto->idCorrente ) != GRA_CondRetOK)
			return LAB_CondRetFaltouMemoria;
		return LAB_CondRetOK;
	}
	
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente,(void**)&posicaoOrigem);
	if (posicaoOrigem->idOeste != 0){
		free(posicaoNova);
		return LAB_tpCondRetJaExistePosicao;	
	}
	if (GRA_InserirNo( labirinto->pGrafo,posicaoNova,&labirinto->idCorrente ) != GRA_CondRetOK)
		return LAB_CondRetFaltouMemoria;
	if (GRA_InserirAresta(labirinto->pGrafo,labirinto->idCorrente,posicaoNova->idLeste, 0)!= GRA_CondRetOK)
		return LAB_CondRetFaltouMemoria; /* Aqui deve ser checada a condret retornada para ver corretamente o erro */
	posicaoOrigem->idOeste = labirinto->idCorrente;
	return LAB_CondRetOK;
}

/* Fim função: LAB &Inserir Posicao Oeste */

/***************************************************************************
*
*  Função: LAB &Inserir Posicao Leste
*  ****/

LAB_tpCondRet LAB_InserirPosicaoLeste ( LAB_tppLabirinto labirinto, PosJog_Tipo tipo )
{
	LAB_PosJog posicaoNova, posicaoOrigem;
	posicaoNova = (LAB_PosJog)malloc(sizeof(LAB_PosJog));
	posicaoNova->tipo = tipo;
	posicaoNova->idLeste = 0;
	posicaoNova->idOeste = labirinto->idCorrente;
	posicaoNova->idNorte = 0;
	posicaoNova->idSul = 0;
	if (labirinto->idCorrente = 0){
		if( GRA_InserirNo( labirinto->pGrafo,posicaoNova,&labirinto->idCorrente ) != GRA_CondRetOK)
			return LAB_CondRetFaltouMemoria;
		return LAB_CondRetOK;
	}
	
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente,(void**)&posicaoOrigem);
	if (posicaoOrigem->idLeste != 0){
		free(posicaoNova);
		return LAB_tpCondRetJaExistePosicao;	
	}
	if (GRA_InserirNo( labirinto->pGrafo,posicaoNova,&labirinto->idCorrente ) != GRA_CondRetOK)
		return LAB_CondRetFaltouMemoria;
	if (GRA_InserirAresta(labirinto->pGrafo,labirinto->idCorrente,posicaoNova->idOeste, 0)!= GRA_CondRetOK)
		return LAB_CondRetFaltouMemoria; /* Aqui deve ser checada a condret retornada para ver corretamente o erro */
	posicaoOrigem->idOeste = labirinto->idCorrente;
	return LAB_CondRetOK;
}

/* Fim função: LAB &Inserir Posicao Oeste */

/***************************************************************************
*
*  Função: LAB &Ir Posicao Norte
*  ****/

LAB_tpCondRet IrPosicaoNorte ( LAB_tppLabirinto labirinto ){

	LAB_PosJog posicaoCorrente;
	if (GRA_ObterValorNo(labirinto->pGrafo,labirinto->idCorrente,(void**)&posicaoCorrente)!= GRA_CondRetOK)
		return LAB_CondRetLabirintoVazio;
	if (posicaoCorrente->idNorte == 0)
		return LAB_CondRetNaoExisteCaminho;
	labirinto->idCorrente = posicaoCorrente->idNorte;
	return LAB_CondRetOK;
	
}

/* Fim função: LAB &Ir Posicao Norte */

/***************************************************************************
*
*  Função: LAB &Ir Posicao Sul
*  ****/

LAB_tpCondRet IrPosicaoSul ( LAB_tppLabirinto labirinto ){

	LAB_PosJog posicaoCorrente;
	if (GRA_ObterValorNo(labirinto->pGrafo,labirinto->idCorrente,(void**)&posicaoCorrente)!= GRA_CondRetOK)
		return LAB_CondRetLabirintoVazio;
	if (posicaoCorrente->idSul == 0)
		return LAB_CondRetNaoExisteCaminho;
	labirinto->idCorrente = posicaoCorrente->idSul;
	return LAB_CondRetOK;
	
}

/* Fim função: LAB &Ir Posicao Sul */

/***************************************************************************
*
*  Função: LAB &Ir Posicao Oeste 
*  ****/

LAB_tpCondRet IrPosicaoOeste ( LAB_tppLabirinto labirinto ){

	LAB_PosJog posicaoCorrente;
	if (GRA_ObterValorNo(labirinto->pGrafo,labirinto->idCorrente,(void**)&posicaoCorrente)!= GRA_CondRetOK)
		return LAB_CondRetLabirintoVazio;
	if (posicaoCorrente->idOeste  == 0)
		return LAB_CondRetNaoExisteCaminho;
	labirinto->idCorrente = posicaoCorrente->idOeste ;
	return LAB_CondRetOK;
	
}

/* Fim função: LAB &Ir Posicao Oeste */

/***************************************************************************
*
*  Função: LAB &Ir Posicao Leste
*  ****/

LAB_tpCondRet IrPosicaoLeste ( LAB_tppLabirinto labirinto ){

	LAB_PosJog posicaoCorrente;
	if (GRA_ObterValorNo(labirinto->pGrafo,labirinto->idCorrente,(void**)&posicaoCorrente)!= GRA_CondRetOK)
		return LAB_CondRetLabirintoVazio;
	if (posicaoCorrente->idLeste == 0)
		return LAB_CondRetNaoExisteCaminho;
	labirinto->idCorrente = posicaoCorrente->idLeste;
	return LAB_CondRetOK;
	
}

/* Fim função: LAB &Ir Posicao Leste */

