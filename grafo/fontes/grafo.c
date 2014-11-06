/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo Genérico (implementado por listas)
*
*  Arquivo gerado:              grafo.c
*  Letras identificadoras:      GRA
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
*     1       LM,LS   22/SET/2014 início desenvolvimento
*	  2		  LM,LS	  23/OUT/2014 início da melhoria do módulo	
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


#define GRA_OWN
#include "grafo.h"
#undef GRA_OWN



/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de grafo
*
*
***********************************************************************/

   typedef struct GRA_tagGrafo {

         LIS_tppLista  pOrigens ;
               /* Ponteiro para a cabeça da lista de origens*/

         LIS_tppLista  pVertices ;
               /* Ponteiro para a cabeça da lista de vértices*/

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

		 int idCorrente;
			/* Ponteiro para o id do vértice corrente */

   } GRA_tpGrafo ;

   /***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor do nó do Grafo
*
*
***********************************************************************/

   struct GRA_verticeGrafo
   {
	   int verticeId;
			/* id único que identifica aquele vértice */
	   void *pInfo;
		   /* ponteiro para a Informação armazenada no vértice */
	   LIS_tppLista listaArestas;
			/* Ponteiro para a Lista de Adjacências de cada vértice */
	   char marked;
			/* Está marcado? 0 para não, 1 para sim */
   };
   typedef struct GRA_verticeGrafo* GRA_noGrafo;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da aresta do Grafo
*
*
***********************************************************************/

   struct GRA_arestaGrafo{
   
   GRA_noGrafo noApontado;
 	/* no apontado pela aresta */
   int verticeId;
	/*id do vertice apontado pela aresta*/
   int idAresta;
   	/* id unico da aresta*/
   };
   typedef struct GRA_arestaGrafo* GRA_tpAresta;

   /***** Protótipos das funções encapuladas no módulo *****/

   static int IdExisteJa( GRA_tppGrafo grafo, int id );
   static void visit(GRA_noGrafo noCorr,int* visited,int tam,int* ordened);
/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: GRA  &Criar Grafo
*  ****/

GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo* refgrafo,  void   ( * ExcluirValor ) ( void * pDado ))
{
	GRA_tpGrafo* tempgraf;
	tempgraf=(GRA_tpGrafo*)malloc(sizeof(GRA_tpGrafo));
	tempgraf->ExcluirValor = ExcluirValor;
	if(!tempgraf)
		return  GRA_CondRetFaltouMemoria;
		/* if */
	if(LIS_CriarLista(&tempgraf->pOrigens,tempgraf->ExcluirValor)!=LIS_CondRetOK)
		return GRA_CondRetFaltouMemoria;
		/* if */
	if(LIS_CriarLista(&tempgraf->pVertices,tempgraf->ExcluirValor)!=LIS_CondRetOK)
		return GRA_CondRetFaltouMemoria;
	/* if */
	/* Não houve problemas , retorne OK */
	tempgraf->idCorrente = 0;
	*refgrafo=tempgraf; //return by reference
	return GRA_CondRetOK;
}

/* Fim função: GRA &Criar Grafo */

/***************************************************************************
*
*  Função: GRA &Destruir Grafo
*  ****/

GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo grafo )
{
	GRA_EsvaziarGrafo(grafo);
	LIS_DestruirLista(grafo->pOrigens);
	grafo->pOrigens=NULL;
	LIS_DestruirLista(grafo->pVertices);
	grafo->pVertices=NULL;
	free(grafo);
	grafo=NULL; //never be acessed again
	return GRA_CondRetOK;
}	 
/* Fim função: GRA  &Destruir grafo */

/***************************************************************************
*
*  Função: GRA &Inserir No
*  ****/


GRA_tpCondRet   GRA_InserirNo ( GRA_tppGrafo grafo, void * pInfo, int * pNoId)
{
	/* Todo nó adicionado, como não tem aresta é uma nova componente conexa */
	GRA_noGrafo novoNo, novaOrigem;
	
	int id=1; //ids começam em 1
		if(LIS_IrFinalLista(grafo->pVertices)!=LIS_CondRetListaVazia)
		{	
			while(IdExisteJa(grafo,id))
			{	id++;
				//printf("id: %d\t",id);
			}	//Garantirá que id sera sempre diferente
		}
		else
			id=1; //ids começam em 1
		/* if */
    novoNo=(GRA_noGrafo)malloc(sizeof(struct GRA_verticeGrafo)); //cria nó
	novaOrigem=(GRA_noGrafo)malloc(sizeof(struct GRA_verticeGrafo));
	if(!novoNo)
		return GRA_CondRetFaltouMemoria;
		/* if */
	novoNo->verticeId=id;
	novoNo->pInfo=pInfo;
	novaOrigem->verticeId = id;
	novaOrigem->pInfo=pInfo;
	if(LIS_CriarLista(&novoNo->listaArestas,free)==LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
		/* if */
	LIS_InserirElementoApos(grafo->pVertices,novoNo); //cria nova elementolista na lista de nós representando esse vértice
	LIS_InserirElementoApos(grafo->pOrigens,novaOrigem); //Linka a componente conexa ao novo nó sem arestas
	grafo->idCorrente = id;
	*pNoId = id;
	return GRA_CondRetOK;
}

/* Fim função: GRA  &Inserir No */

/***************************************************************************
*
*  Função: GRA &Excluir No
*  ****/

GRA_tpCondRet   GRA_ExcluirNo ( GRA_tppGrafo grafo, int Id)
{
	GRA_noGrafo noRemovido;
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return  GRA_CondRetGrafoVazio;
		/* if */
	if(!IdExisteJa(grafo,Id))
		return GRA_CondRetNoNaoExiste;
		/* if */
	do{
		noRemovido=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(noRemovido->verticeId==Id)
			break;
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);
	LIS_DestruirLista(noRemovido->listaArestas);
	LIS_ExcluirElemento( grafo->pVertices);
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia){
		grafo->idCorrente = 0;
		return GRA_CondRetOK;
	}
	
	noRemovido = (GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
	if (grafo->idCorrente == Id)
		grafo->idCorrente = noRemovido->verticeId;
		/* if */
	
	
	return GRA_CondRetOK;
}

/* Fim função: GRA  &Excluir No */

/***************************************************************************
*
*  Função: GRA &Excluir No Corrente
*  ****/

GRA_tpCondRet   GRA_ExcluirNoCorrente ( GRA_tppGrafo grafo )
{
	return (GRA_ExcluirNo(grafo, grafo->idCorrente));
}

/* Fim função: GRA  &Excluir No Corrente */

/***************************************************************************
*
*  Função: GRA &Inserir Aresta
*  ****/

GRA_tpCondRet  GRA_InserirAresta( GRA_tppGrafo grafo, int node_i, int node_j, int idAresta)
{
	int i = 0, j = 0;
	GRA_noGrafo  noOrigem, noDestino;
	GRA_tpAresta aresta1, aresta2, noTemp;
	
	
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
		/* if */
	
	if (!IdExisteJa(grafo, node_j))
		return GRA_CondRetNoNaoExiste;
		/* if */
	if  (!IdExisteJa(grafo, node_i))
		return GRA_CondRetNoNaoExiste;
		/* if */
	aresta1= (GRA_tpAresta)malloc(sizeof(struct GRA_arestaGrafo));
	aresta2= (GRA_tpAresta)malloc(sizeof(struct GRA_arestaGrafo));
	if((aresta1==NULL)|(aresta2==NULL)) // Checa se faltou memória pra alguma delas 
		return GRA_CondRetFaltouMemoria;
	LIS_IrInicioLista(grafo->pVertices);	
	
	do{
		noOrigem=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(noOrigem->verticeId==node_i)
			break; //EXISTE
		/* if */
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);
	
	LIS_IrInicioLista(grafo->pVertices);

	do{
		noDestino=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(noDestino->verticeId==node_j)
			break; //EXISTE
		/* if */
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);

	LIS_IrInicioLista(noOrigem->listaArestas);

	do{
		noTemp = (GRA_tpAresta)LIS_ObterValor(noOrigem->listaArestas);
		if (noTemp == NULL)
			break;
		/* if */
		if (noTemp->verticeId == noDestino->verticeId){
		return GRA_CondRetArestaJaExiste;
		}
		/* if */
	}while(LIS_AvancarElementoCorrente( noOrigem->listaArestas ,1 )!=LIS_CondRetFimLista);

	aresta1->verticeId = noDestino->verticeId;
	aresta1->noApontado = noDestino;
	aresta1->idAresta	= idAresta;

	LIS_InserirElementoApos(noOrigem->listaArestas,aresta1);
	
	LIS_IrInicioLista(noDestino->listaArestas);

	do{
		noTemp = (GRA_tpAresta)LIS_ObterValor(noDestino->listaArestas);
		if (noTemp == NULL)
			break;
		/* if */
		if (noTemp->verticeId == noOrigem->verticeId){

		return GRA_CondRetArestaJaExiste;
		}
		/* if */
	}while(LIS_AvancarElementoCorrente( noDestino->listaArestas ,1 )!=LIS_CondRetFimLista);
	
	aresta2->verticeId = noOrigem->verticeId;
	aresta2->noApontado = noOrigem;
	aresta2->idAresta	= idAresta;

	LIS_InserirElementoApos(noDestino->listaArestas, aresta2);
	
	

	return GRA_CondRetOK;
}
/* Fim função: GRA  &Inserir Aresta */

/***************************************************************************
*
*  Função: GRA &Excluir Aresta
*  ****/

GRA_tpCondRet  GRA_ExcluirAresta( GRA_tppGrafo grafo, int node_i, int node_j)
{
	int i = 0, j = 0, flag = 0;
	GRA_noGrafo  noOrigem, noDestino;
	GRA_tpAresta noComp;
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
	/* if */
	if (!IdExisteJa(grafo, node_j))
		return GRA_CondRetNoNaoExiste;
	/* if */
	if  (!IdExisteJa(grafo, node_i))
		return GRA_CondRetNoNaoExiste;
	/* if */
	LIS_IrInicioLista(grafo->pVertices);	
	
	do{
		noOrigem=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(noOrigem->verticeId==node_i)
			break; //EXISTE
		/* if */
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);

	LIS_IrInicioLista(grafo->pVertices);

	do{
		noDestino=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(noDestino->verticeId==node_j)
			break; //EXISTE
		/* if */
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);

	LIS_IrInicioLista(noOrigem->listaArestas);
	LIS_IrInicioLista(noDestino->listaArestas);
	do{
		noComp = (GRA_tpAresta)LIS_ObterValor(noOrigem->listaArestas);
		if (noComp == NULL)
			break;
		/* if */
		if (noComp->verticeId == noDestino->verticeId){
			LIS_ExcluirElemento( noOrigem->listaArestas );
			flag = 1;
			break;
		}
		/* if */
	}while(LIS_AvancarElementoCorrente( noOrigem->listaArestas ,1 )!=LIS_CondRetFimLista);
	
	if (flag == 0)
		return GRA_CondRetArestaNaoExiste;
	/* if */
	flag = 0;
	

	do{
		noComp = (GRA_tpAresta)LIS_ObterValor(noDestino->listaArestas);
		if (noComp == NULL)
			break;
		/* if */
		if (noComp->verticeId == noOrigem->verticeId){
		LIS_ExcluirElemento( noDestino->listaArestas );
		flag = 1;
		break;
		}
		/* if */
	}while(LIS_AvancarElementoCorrente( noDestino->listaArestas ,1 )!=LIS_CondRetFimLista);
	
	if (flag == 0)
		return GRA_CondRetArestaNaoExiste;
	/* if */
	return GRA_CondRetOK;
}
/* Fim função: GRA  &Excluir Aresta */

/***************************************************************************
*
*  Função: GRA &Obter Id Aresta
*  ****/

GRA_tpCondRet  GRA_ObterIdAresta( GRA_tppGrafo grafo, int node_i, int node_j, int * pId)
{
	int i = 0, j = 0, flag = 0;
	GRA_noGrafo  noOrigem, noDestino;
	GRA_tpAresta noComp;
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
	/* if */
	if (!IdExisteJa(grafo, node_j))
		return GRA_CondRetNoNaoExiste;
	/* if */
	if  (!IdExisteJa(grafo, node_i))
		return GRA_CondRetNoNaoExiste;
	/* if */
	LIS_IrInicioLista(grafo->pVertices);	
	
	do{
		noOrigem=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(noOrigem->verticeId==node_i)
			break; //EXISTE
		/* if */
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);

	LIS_IrInicioLista(grafo->pVertices);

	do{
		noDestino=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(noDestino->verticeId==node_j)
			break; //EXISTE
		/* if */
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);

	LIS_IrInicioLista(noOrigem->listaArestas);

	do{
		noComp = (GRA_tpAresta)LIS_ObterValor(noOrigem->listaArestas);
		if (noComp == NULL)
			break;
		/* if */
		if (noComp->verticeId == noDestino->verticeId){
			*pId = noComp->idAresta;
			return GRA_CondRetOK;
		}
		/* if */
	}while(LIS_AvancarElementoCorrente( noOrigem->listaArestas ,1 )!=LIS_CondRetFimLista);

	return GRA_CondRetArestaNaoExiste;
}
/* Fim função: GRA  &Obter Id Aresta */

/***************************************************************************
*
*  Função: GRA &Imprimir Grafo
*  ****/

GRA_tpCondRet  GRA_ImprimirGrafo(GRA_tppGrafo grafo)
{
	/* vá em cada vértice e imprima suas componentes conexas */
	GRA_noGrafo p; //percorredor
	GRA_tpAresta acs;  //percorredor
	LIS_tppLista l; //percorredor
	printf("\n");
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
	/* if */
	do
	{
		p=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		printf("Vertice %d Arestas: ",p->verticeId);
		l=p->listaArestas;
		if(LIS_IrInicioLista(l)!=LIS_CondRetListaVazia)
		{
			printf("{ ");
			do 
			{
				
				acs=(GRA_tpAresta)LIS_ObterValor(l);
				printf("%d ",acs->verticeId);
			
			}while(LIS_AvancarElementoCorrente(l,1)!=LIS_CondRetFimLista);
			printf("} ");
		}
		else
			printf("NADA");
		/* if */
		printf("\n");
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);

		

	return GRA_CondRetOK;
}

/* Fim função: GRA  &Imprimir grafo */

/***************************************************************************
*
*  Função: GRA &Esvaziar grafo
*  ****/

GRA_tpCondRet GRA_EsvaziarGrafo( GRA_tppGrafo grafo )
{
	GRA_noGrafo noTemp;
	if (LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
	/* if */
	do{
		noTemp=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		LIS_EsvaziarLista(noTemp->listaArestas);
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);

	
	LIS_EsvaziarLista(grafo->pOrigens);
	LIS_EsvaziarLista(grafo->pVertices);
	grafo->idCorrente = 0;
	

	return GRA_CondRetOK;
}

/* Fim função: GRA  &Esvaziar grafo */

/***************************************************************************
*
*  Função: GRA &Obter No Corrente
*  ****/


GRA_tpCondRet GRA_ObterNoCorrente( GRA_tppGrafo grafo, int * refId)
{
	*refId = grafo->idCorrente;
	if (grafo->idCorrente == 0){
		return GRA_CondRetGrafoVazio;
	}	
	/* if */
	return GRA_CondRetOK;

}

/* Fim função: GRA  &Obter No Corrente */

/***************************************************************************
*
*  Função: GRA &Ir No Vizinho
*  ****/


GRA_tpCondRet GRA_IrNoVizinho( GRA_tppGrafo grafo, int noVizinho)
{
	GRA_noGrafo noOrigem;
	GRA_tpAresta aresta;
	if (grafo->idCorrente == noVizinho)
		return GRA_CondRetJaEsta;
	/* if */
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return  GRA_CondRetGrafoVazio;
	/* if */
	if(!IdExisteJa(grafo,noVizinho))
		return GRA_CondRetNoNaoExiste;
	LIS_IrInicioLista(grafo->pVertices);
	do{
		noOrigem=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(noOrigem->verticeId==grafo->idCorrente)
			break;
		/* if */
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);
	LIS_IrInicioLista(noOrigem->listaArestas);
	do{
		aresta=(GRA_tpAresta)LIS_ObterValor(noOrigem->listaArestas);
		if(aresta->verticeId==noVizinho){
			grafo->idCorrente = noVizinho;
			return GRA_CondRetOK;
		}
		/* if */
	}while(LIS_AvancarElementoCorrente(noOrigem->listaArestas,1)!=LIS_CondRetFimLista);

	return GRA_CondRetArestaNaoExiste;

}

/* Fim função: GRA  &Ir No Vizinho */

/***************************************************************************
*
*  Função: GRA &Obert Valor no
*  ****/


GRA_tpCondRet GRA_ObterValorNo(GRA_tppGrafo grafo, int noId,void** endVar)
{
	GRA_noGrafo no;
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return  GRA_CondRetGrafoVazio;
	do 
	{   no=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(no->verticeId==noId)
		{ /* Achou */
			*endVar=no->pInfo;
			return GRA_CondRetOK;
		}
		/* if */
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);
	/* Nao Achou */
	return GRA_CondRetNoNaoExiste;
}
/* Fim função: GRA  &Obter valor no */

/***************************************************************************
*
*  Função: GRA &Ir para no
*  ****/


GRA_tpCondRet GRA_IrParaNo(GRA_tppGrafo grafo,int noId)
{
	GRA_noGrafo no;
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
	/* if */
	do
	{ 
		no=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(no->verticeId==noId)
		{ /* Achou */
			grafo->idCorrente = noId;
			return GRA_CondRetOK;
		}
		/* if */
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);
	/* Nao Achou */
	return GRA_CondRetNoNaoExiste;
}
/* Fim função: GRA  &Ir para no */

/***************************************************************************
*
*  Função: GRA &Obter Valor No Corrente
*  ****/


GRA_tpCondRet GRA_ObterValorNoCorrente(GRA_tppGrafo grafo, void** endVar)
{
	return (GRA_ObterValorNo(grafo,grafo->idCorrente,endVar));
}
/* Fim função: GRA  &Obter valor No Corrente */

/***************************************************************************
*
*  Função: GRA &Obter Vertices
*  ****/

GRA_tpCondRet GRA_ObterVertices(GRA_tppGrafo grafo,int* refPtrIds,int *tam)
{
	LIS_tppLista l;
	GRA_noGrafo p;
	int i=0;
	
	l= grafo->pVertices;
	if(LIS_IrInicioLista(l)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
	do
	{
		i++; //cont then;
	}
	while(LIS_AvancarElementoCorrente(l,1)!=LIS_CondRetFimLista);
	LIS_IrInicioLista(l);
	refPtrIds=(int*)malloc(sizeof(int)*i);
	if(!refPtrIds)
		return GRA_CondRetFaltouMemoria;
	*tam=i;
	i=0;
	do
	{
		p=(GRA_noGrafo)LIS_ObterValor(l);
		refPtrIds[i]=p->verticeId; // give the vertice
		i++; 
	}
	while(LIS_AvancarElementoCorrente(l,1)!=LIS_CondRetFimLista);

	return GRA_CondRetOK;
}
/* Fim função: GRA  &Obter Vértices */
GRA_tpCondRet GRA_ObterArestasNo(GRA_tppGrafo grafo,int noId,int* refPtrIds,int *tam)
{
	GRA_noGrafo p; //percorredor
	GRA_tpAresta acs; //percorredor
	LIS_tppLista l,la; //percorredor
	int i=0;
	l=grafo->pVertices;
	if(LIS_IrInicioLista(l)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
	do
	{	p=(GRA_noGrafo)LIS_ObterValor(l);
		la=p->listaArestas;
		if(LIS_IrInicioLista(la)==LIS_CondRetListaVazia)
			return GRA_CondRetArestaNaoExiste;
		do 
		i++;
		while(LIS_AvancarElementoCorrente(la,1)!=LIS_CondRetFimLista);
		refPtrIds=(int*)malloc(sizeof(int)*i);
		if(!refPtrIds)
			return GRA_CondRetFaltouMemoria;
		*tam=i;
		i=0;
		LIS_IrInicioLista(la);
		do 
		{	
			acs=(GRA_tpAresta)LIS_ObterValor(la);
			refPtrIds[i]=acs->verticeId;	
			
		}	
		while(LIS_AvancarElementoCorrente(la,1)!=LIS_CondRetFimLista);

	}
	while(LIS_AvancarElementoCorrente(l,1)!=LIS_CondRetFimLista);
	return GRA_CondRetOK;
}
/* Fim função: GRA  &Obter Arestas do No */

/***************************************************************************
*
*  Função: GRA &DFS
*  ****/

GRA_tpCondRet GRA_DFS(GRA_tppGrafo grafo, int** refPtrIds, int * tam,int noId)
{
/* vá em cada vértice e imprima suas componentes conexas */
	GRA_noGrafo p; //percorredor
	GRA_tpAresta acs; //percorredor
	LIS_tppLista l; //percorredor
	LIS_tppLista visitados;
	int i,j,size; //counter
	static int *visited;
	static int* ordened;
	int * nosIds;
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
 
	if(LIS_CriarLista(&visitados,free)!=LIS_CondRetOK) /* Lista de Operação. A serem Visitados */
		return GRA_CondRetFaltouMemoria;
	LIS_IrInicioLista(grafo->pVertices);
	i=0;
	do
	{
		p=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(p->verticeId>i)
		i=p->verticeId;
	}
	/* vector position represents id*/
	while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);
	
	visited=(int*)malloc(sizeof(int)*i);
	nosIds=(int*)malloc(sizeof(int)*i);
	ordened=(int*)malloc(sizeof(int)*i);
	size=i;
	for(i=0;i<size;i++)
		visited[i]=0; //Unmark ALL
	for(i=0;i<size;i++)
		ordened[i]=0; //Unmark ALL
	LIS_IrInicioLista(grafo->pVertices);
 
	do
	{
		p=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(p->verticeId==noId)
			break; //Found
	}

	while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);
	
	visit(p,visited,size,ordened);
	for(i=0,j=0;i<size;i++)
	{
		if(visited[i]==1)
			j++; //Contar os Visitados
 
	}
	*refPtrIds=(int*)malloc(sizeof(int)*j);
	*tam=j;
	for(i=0,j=0;i<size;i++)
	{
		if(ordened[i]!=0)
		{
			*(*refPtrIds+j)=ordened[i]; // Receber em cada posição do vetor o id do nó visitado.
			j++;
		}
	}
	free(ordened);
	free(visited);
	return GRA_CondRetOK;
}
/* Fim função: GRA  &DFS */

GRA_tpCondRet GRA_ExisteCaminho(GRA_tppGrafo grafo, int noInicioId, int noFimId)
{
	int* ptrIds;
	int tam;
	int i;
	GRA_tpCondRet ret;
	printf("Looking for Caminho entre %d e %d\n",noInicioId,noFimId);
	ret=GRA_DFS(grafo,&ptrIds,&tam,noInicioId);
	if(ret!=GRA_CondRetOK)
		return ret;
	
	//printf("\n< ");
	for(i=0;i<tam;i++)
	{	//printf("%d; ",ptrIds[i]);
		if(ptrIds[i]==noFimId)
			return GRA_CondRetCaminhoExiste;
	}
	//printf(">");
	return GRA_CondRetCaminhoNaoExiste;
	
}


GRA_tpCondRet GRA_BFS(GRA_tppGrafo grafo, int** refPtrIds, int * tam,int noId)
{
/* vá em cada vértice e imprima suas componentes conexas */
	GRA_noGrafo p; //percorredor
	GRA_tpAresta acs; //percorredor
	LIS_tppLista l; //percorredor
	LIS_tppLista fila;
	int i,j,size; //counter
	static int *visited;
	static int* ordened;
	int * nosIds;
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
 
	if(LIS_CriarLista(&fila,free)!=LIS_CondRetOK) /* Lista de Operação. A serem Visitados */
		return GRA_CondRetFaltouMemoria;
	LIS_IrInicioLista(grafo->pVertices);
	i=0;
	do
	{
		p=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(p->verticeId>i)
		i=p->verticeId;
	}
	/* vector position represents id*/
	while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);
	
	visited=(int*)malloc(sizeof(int)*i);
	nosIds=(int*)malloc(sizeof(int)*i);
	ordened=(int*)malloc(sizeof(int)*i);
	size=i;
	for(i=0;i<size;i++)
		visited[i]=0; //Unmark ALL
	for(i=0;i<size;i++)
		ordened[i]=0; //Unmark ALL
	
	LIS_IrInicioLista(grafo->pVertices);
	do
	{
	
		p=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		p->marked=0; //Unmark All
	}
	while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);
	/* Algoritmo BFS */

	GRA_IrParaNo(grafo,noId);
	GRA_ObterValorNoCorrente(grafo,(void**)&p);
	p->marked;
	LIS_InserirElementoApos(fila,p);
	while(LIS_IrInicioLista(fila)!=LIS_CondRetListaVazia)
	{
		p=(GRA_noGrafo)LIS_ObterValor(fila);
		LIS_IrInicioLista(p->listaArestas);
		do 
		{
			acs=(GRA_tpAresta)LIS_ObterValor(p->listaArestas);
			if(acs->noApontado->marked=0) // Se Não está marcado?
			{
				/* visite ele */

				acs->noApontado->marked=1; //visitei
				LIS_InserirElementoApos(fila,acs->noApontado);

			}
			else 
			{
				if(LIS_ProcurarValor(fila,acs->noApontado)==LIS_CondRetOK)
				{				/* visite ele */

				}
			}
			
		}
		while(LIS_AvancarElementoCorrente(p->listaArestas,1));
		LIS_ProcurarValor(fila,p);
		LIS_ExcluirElemento(fila); /* Exclui p */
	}
	
	visit(p,visited,size,ordened);
	for(i=0,j=0;i<size;i++)
	{
		if(visited[i]==1)
			j++; //Contar os Visitados
 
	}
	*refPtrIds=(int*)malloc(sizeof(int)*j);
	*tam=j;
	for(i=0,j=0;i<size;i++)
	{
		if(ordened[i]!=0)
		{
			*(*refPtrIds+j)=ordened[i]; // Receber em cada posição do vetor o id do nó visitado.
			j++;
		}
	}
	free(ordened);
	free(visited);
	return GRA_CondRetOK;
}
/* Fim função: GRA  &BFS */



/***************************************************************************

*****  Código das funções encapsuladas no módulo  *****/




/***********************************************************************
*
*  $FC Função: GRA  -IdExisteJa
*  $ED Descrição da função
*     Checa se já existe um nó com o Id passado
*
***********************************************************************/

static int IdExisteJa(GRA_tppGrafo grafo,int id)
{	GRA_noGrafo p;
	LIS_IrInicioLista(grafo->pVertices);
	p=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
	if(p->verticeId==id)
		return 1; // EXISTE
		/* if */
	while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista)
	{	
		p=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		//printf("<id %d, pvid %d>\n",id,p->verticeId);
		if(p->verticeId==id)
			return 1; //EXISTE
			/* if */

	}
	return 0; //NAO EXISTE
}
/***********************************************************************
*
*  $FC Função: GRA  -Visit
*  $ED Descrição da função
*     Função recursiva que percorre as arestas de cada nó
*	  Usada pela DFS.
*	  Ela retorna a ordem dos índices dos vértices visitados
*
***********************************************************************/
static void visit(GRA_noGrafo noCorr,int* visited,int tam,int* ordened)
{
	int i;
	
	GRA_noGrafo p; //percorredor
	GRA_tpAresta acs; //percorredor
	LIS_tppLista l; //percorredor
		 printf("Iteration\n");
 printf("Visited <");
 for(i=0;i<tam;i++)
 {
	 printf("%d",visited[i]);
 }
 printf(">\n");
  printf("Ordened <");
 for(i=0;i<tam;i++)
 {
	 printf("%d",ordened[i]);
 }
 printf(">\n");

	if(visited[noCorr->verticeId-1]==0) //Se não visitado
	{	printf("visiting %d\n",noCorr->verticeId);
		
		l=noCorr->listaArestas;
		
		if(l&&LIS_IrInicioLista(l)!=LIS_CondRetListaVazia)
		{
			
			do
			{
				
				acs=(GRA_tpAresta)LIS_ObterValor(l);
				p=acs->noApontado;
				
				visit(p,visited,tam,ordened); //visite cada nó adjacente a esse
				
			}
			while(LIS_AvancarElementoCorrente(l,1)!=LIS_CondRetFimLista);
		}
	 visited[noCorr->verticeId-1]=1; //Esse -1 é para que o último nóexista também
		for(i=0;i<tam;i++)
		{
			if(ordened[i]==0)
			{	ordened[i]=noCorr->verticeId;
				break;
			}
		}
	}
	return;
}
