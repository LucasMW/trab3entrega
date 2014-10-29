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

LAB_tpCondRet LAB_InserirPosicaoNorte ( LAB_tppLabirinto labirinto ,  PosJog_Tipo tipo)
{
	/* Insere uma Posição ao Norte da Corrente */
	int temp;
	LAB_PosJog posicao;
	posicao=(LAB_PosJog)malloc(sizeof(struct LAB_PosicaoJogavel));
	posicao->tipo = tipo;
	posicao->idNorte=0;
	posicao->idOeste=0;
	posicao->idLeste=0;
	posicao->idSul= labirinto->idCorrente;
	if (labirinto->idCorrente = 0){
		if( GRA_InserirNo( labirinto->pGrafo,posicao,&labirinto->idCorrente ) != GRA_CondRetOK)
			return LAB_CondRetFaltouMemoria;
		return LAB_CondRetOK;
	}
	temp = labirinto->idCorrente;
	if (GRA_InserirNo( labirinto->pGrafo,posicao,&labirinto->idCorrente ) != GRA_CondRetOK)
		return LAB_CondRetOK;
	if (GRA_InserirAresta(labirinto->pGrafo,temp,labirinto->idCorrente, 'V')!= GRA_CondRetOK)
		return LAB_CondRetFaltouMemoria; /* Aqui deve ser checada a condret retornada para ver corretamente o erro */
	return LAB_CondRetOK;
}

/* Fim função: LAB &Inserir Posicao Norte */
