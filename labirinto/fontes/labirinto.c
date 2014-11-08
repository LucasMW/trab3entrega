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
#include <string.h>


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça do labirinto
*
*
***********************************************************************/

typedef enum
	   {
		   PosLivre,

		   PosParede,

		   PosEntrada,

		   PosSaida

	   } PosJog_Tipo;

   struct LAB_PosicaoJogavel
   {

	   PosJog_Tipo tipo;

	   int corrente;
	   /* 1 é a corrente, 0 nao é*/
	   int caminho;
	   
   };
   typedef struct LAB_PosicaoJogavel* LAB_PosJog;


			
   typedef struct LAB_tagLabirinto {

          GRA_tppGrafo pGrafo ;
               /* Ponteiro para a cabeça do grafo de que armazena as posições do labirinto*/	 

		 int idCorrente;
			/* id da posição corrente */

		 int xEntrada;

		 int yEntrada;

		 int xSaida;

		 int ySaida;

		 int xMax;

		 int yMax;


   } LAB_tpLabirinto ;

   typedef struct LAB_tagLabirinto * LAB_tppLabirinto ;



int CheckFileExists(char* path)
{
FILE* tester;
int r=0;
tester=fopen(path,"wt");
if(tester)
 r=1;
fclose(tester);
return r;
}

   void LAB_CriarLabirinto( LAB_tppLabirinto* refLab)
{
	LAB_tpLabirinto* tempLab;
	tempLab=(LAB_tpLabirinto*)malloc(sizeof(LAB_tpLabirinto));
	
	if(!tempLab)
		return ;
		/* if */
	if(GRA_CriarGrafo(&tempLab->pGrafo,free)!=GRA_CondRetOK)
		return ;
		/* if */

	/* if */
	/* Não houve problemas , retorne OK */
	tempLab->idCorrente=0; //Id Corrents must not exist
	
	*refLab=tempLab; //return by reference
	return;
}

void ExibirLabirinto ( LAB_tppLabirinto labirinto, int playMode){
	
	
	int i, j;
	LAB_PosJog posicao;
	system("cls");
	if (!playMode)
		printf("Comandos:\nIr Cima:    w	Ir Baixo:    s	Ir Esquerda:    a  Ir Direita:    d\n Destruir Parede:    q Construir Parede: e  Jogar:   r\n Salvar:   z Carregar:   l\n Novo:    n\n");
	else
		printf("Comandos:\nIr Cima:    w	Ir Baixo:    s	Ir Esquerda:    a  Ir Direita:    d\n Construir:   r Salvar:   z Carregar:   l\n Solucionar :    o\n");
	for (i = 0; i < labirinto->xMax; i++){
		for (j = 0; j <labirinto->yMax; j++){
			GRA_ObterValorNo(labirinto->pGrafo, (i * labirinto->xMax + j + 1),(void**)&posicao);
			if (posicao->tipo == PosParede){
				if (posicao->corrente == 0)
				printf(" # ");
				else{
					if (playMode)
					printf("|P|");
					else
					printf("|#|");
				}
			}
			else
				if (posicao->tipo == PosEntrada){
					if (posicao->corrente == 0)
					printf(" E ");
					else
					{
					if (playMode)
					printf("|P|");
					else
					printf("|E|");
				}
				}
				else 
					if (posicao->tipo == PosLivre){
						if (playMode == 2){
							if (posicao->caminho == 1)
								printf (" X ");
							else {
								printf (" * ");
							}
						}
						else{
						if (posicao->corrente == 0)
						printf(" * ");
						else
						{
					if (playMode == 1)
					printf("|P|");
					else
					printf("|*|");
				}
						}
					}
					else
						if(posicao->corrente == 0)
						printf(" S ");
						else
							printf("|S|");
			}
			printf("\n");
			}
	
}
	  

void inserirEntrada ( LAB_tppLabirinto labirinto, int x, int y){
	
	LAB_PosJog posicao;
	GRA_ObterValorNo(labirinto->pGrafo, (y * labirinto->xMax + x ) + 1,(void**)&posicao);
	labirinto->idCorrente = (y * labirinto->xMax + x) + 1;
	posicao->tipo = PosEntrada;
	posicao->corrente = 1;
	labirinto->yEntrada = y;
	labirinto->xEntrada = x;
}

void inserirSaida ( LAB_tppLabirinto labirinto, int x, int y){
	
	LAB_PosJog posicao;
	GRA_ObterValorNo(labirinto->pGrafo, (y * labirinto->xMax + x) + 1,(void**)&posicao);
	posicao->tipo = PosSaida;
	labirinto->ySaida = y;
	labirinto->xSaida = x;
	
}

void destroiParede ( LAB_tppLabirinto labirinto) {
	LAB_PosJog posicao;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&posicao);
	if (posicao->tipo != PosParede)
		return;
	posicao->tipo = PosLivre;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente - labirinto->xMax ,(void**)&posicao);
	if (posicao->tipo != PosParede)
		GRA_InserirAresta(labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente - labirinto->xMax, 0);
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente + labirinto->xMax ,(void**)&posicao);
	if (posicao->tipo != PosParede)
		GRA_InserirAresta(labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente + labirinto->xMax, 0);
	if (labirinto->idCorrente % labirinto->xMax != 0){
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente + 1 ,(void**)&posicao);
	if (posicao->tipo!= PosParede)
		GRA_InserirAresta(labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente + 1, 0);
	}
	if (labirinto->idCorrente % labirinto->xMax != 1){
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente - 1 ,(void**)&posicao);
	if (posicao->tipo != PosParede)
		GRA_InserirAresta(labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente - 1, 0);
	}
	ExibirLabirinto ( labirinto,0);

}

void constroiParede ( LAB_tppLabirinto labirinto) {
	LAB_PosJog posicao;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&posicao);
	if (posicao->tipo != PosLivre)
		return;
	posicao->tipo = PosParede;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente - labirinto->xMax ,(void**)&posicao);
	if (posicao->tipo == PosLivre)
		GRA_ExcluirAresta(labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente - labirinto->xMax);
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente + labirinto->xMax ,(void**)&posicao);
	if (posicao->tipo == PosLivre)
		GRA_ExcluirAresta(labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente + labirinto->xMax);
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente + 1 ,(void**)&posicao);
	if (posicao->tipo == PosLivre,0)
		GRA_ExcluirAresta(labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente + 1);
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente - 1 ,(void**)&posicao);
	if (posicao->tipo == PosLivre)
		GRA_ExcluirAresta(labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente - 1);
	ExibirLabirinto ( labirinto,0);

}

void GeraLabirinto ( LAB_tppLabirinto labirinto, int xMax, int yMax ){
	
	int i, total;
	LAB_PosJog posicaoNova;
	total  = xMax * yMax;
	printf("a");
	for ( i = 0; i < total; i++){
		posicaoNova = (LAB_PosJog)malloc(sizeof(struct LAB_PosicaoJogavel));
		printf("a1");
		posicaoNova->tipo = PosParede;	
		printf("a2");
		posicaoNova->corrente = 0;
		printf("a3");
		posicaoNova->caminho = 0;
		printf("a4");
		GRA_InserirNo( labirinto->pGrafo,posicaoNova,&labirinto->idCorrente ); 
		printf("a5");
	}
	labirinto->xMax = xMax;
	labirinto->yMax = yMax;	
}

void salvaLabirinto (LAB_tppLabirinto labirinto){
	
	FILE *fp;
	int i,j,temp,arestas=0;
	LAB_PosJog posicao;
	char filename[50], tempStr[5];
	printf("Digite o nome que deseja dar ao labirinto\n");
	scanf("%s",filename);
	strcpy(tempStr,".txt");
	strcat(filename,tempStr);
	fp=fopen(filename, "w");
	if(fp == NULL){
		printf("NULL");
		system("pause");
		exit(-1);
	}

	fprintf(fp,"%d\n",labirinto->xEntrada);
	fprintf(fp,"%d\n",labirinto->yEntrada);
	fprintf(fp,"%d\n",labirinto->xSaida);
	fprintf(fp,"%d\n",labirinto->ySaida);
	fprintf(fp,"%d\n",labirinto->xMax);
	fprintf(fp,"%d\n",labirinto->yMax);

	for (i = 0; i < labirinto->xMax; i++){
		for (j = 0; j <labirinto->yMax; j++){
			fprintf(fp,"%d ",(i * labirinto->xMax + j + 1));
			GRA_ObterValorNo(labirinto->pGrafo, (i * labirinto->xMax + j + 1) ,(void**)&posicao);
			fprintf(fp,"%d ",posicao->tipo);
			if (GRA_ObterIdAresta (labirinto->pGrafo, (i * labirinto->xMax + j + 1), ((i - 1) * labirinto->xMax + j + 1),&temp)==GRA_CondRetOK)
				arestas++;
			if (GRA_ObterIdAresta (labirinto->pGrafo, (i * labirinto->xMax + j + 1), ((i + 1) * labirinto->xMax + j + 1),&temp)==GRA_CondRetOK)
				arestas++;
			if (GRA_ObterIdAresta (labirinto->pGrafo, (i * labirinto->xMax + j + 2), (i  * labirinto->xMax + j + 1),&temp)==GRA_CondRetOK)
				arestas++;
			if (GRA_ObterIdAresta (labirinto->pGrafo, (i * labirinto->xMax + j), (i  * labirinto->xMax + j + 1),&temp)==GRA_CondRetOK)
				arestas++;
			 
			fprintf(fp,"%d ",arestas);

			if (GRA_ObterIdAresta (labirinto->pGrafo, (i * labirinto->xMax + j + 1), ((i - 1) * labirinto->xMax + j + 1),&temp)==GRA_CondRetOK)
				fprintf(fp,"%d ",((i - 1) * labirinto->xMax + j + 1));
			if (GRA_ObterIdAresta (labirinto->pGrafo, (i * labirinto->xMax + j + 1), ((i + 1) * labirinto->xMax + j + 1),&temp)==GRA_CondRetOK)
				fprintf(fp,"%d ",((i + 1) * labirinto->xMax + j + 1));
			if (GRA_ObterIdAresta (labirinto->pGrafo, (i * labirinto->xMax + j + 2), (i  * labirinto->xMax + j + 1),&temp)==GRA_CondRetOK)
				fprintf(fp,"%d ",(i  * labirinto->xMax + j + 2));
			if (GRA_ObterIdAresta (labirinto->pGrafo, (i * labirinto->xMax + j), (i  * labirinto->xMax + j + 1),&temp)==GRA_CondRetOK)
				fprintf(fp,"%d ",(i * labirinto->xMax + j));
			arestas = 0;
			fprintf(fp,"\n");
		}
		
	}
fclose(fp);

}

void carregaLabirinto ( LAB_tppLabirinto * refLab, char filename[]){
	
	FILE *fp;
	int i,j,m,temp,x,y,idNo,idAresta,qtdArestas,xEnt,yEnt,xSai,ySai;
	char tempStr[5];
	PosJog_Tipo tipo;
	LAB_PosJog posicao;
	LAB_tppLabirinto labirinto;
	strcpy(tempStr,".txt");
	strcat(filename,tempStr);
	
	fp=fopen(filename, "r");
	LAB_CriarLabirinto(&labirinto);
	fscanf(fp,"%d %d",&xEnt,&yEnt);
	labirinto->xEntrada = xEnt;
	labirinto->yEntrada = yEnt;
	fscanf(fp,"%d %d",&xSai,&ySai);
	labirinto->xSaida = xSai;
	labirinto->ySaida = ySai;
	fscanf(fp,"%d %d",&x,&y);
	GeraLabirinto(labirinto,x,y);
	for (i = 0; i < labirinto->xMax; i++){
		for (j = 0; j <labirinto->yMax; j++){
			fscanf(fp,"%d", &idNo);
			GRA_ObterValorNo(labirinto->pGrafo, idNo ,(void**)&posicao);
			fscanf(fp,"%d", &tipo);
			posicao->tipo = tipo;
			fscanf(fp,"%d", &qtdArestas);
			for ( m = 0; m < qtdArestas; m++){
				fscanf(fp,"%d",&idAresta);
				GRA_InserirAresta(labirinto->pGrafo,idNo,idAresta,0);
			}			
		}
		
	}
	ExibirLabirinto(labirinto,0);
	*refLab = labirinto;

}

/* Fim função: LAB &Gera Labirinto */

/***************************************************************************
*
*  Função: LAB &Exibir Labirinto 
*  ****/



void irNorte (LAB_tppLabirinto labirinto){
	LAB_PosJog origem,destino;
	if (labirinto->idCorrente <= labirinto->yMax)
		return;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&origem);
	origem->corrente = 0;
	labirinto->idCorrente = labirinto->idCorrente - labirinto->xMax;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente,(void**)&destino);
	destino->corrente = 1;
	ExibirLabirinto(labirinto,0);
	}

void irSul (LAB_tppLabirinto labirinto){
	LAB_PosJog origem,destino;
	if (labirinto->idCorrente > (labirinto->xMax * labirinto->yMax) - labirinto->xMax)
		return;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&origem);
	origem->corrente = 0;
	labirinto->idCorrente = labirinto->idCorrente + labirinto->xMax ;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente,(void**)&destino);
	destino->corrente = 1;
	ExibirLabirinto(labirinto,0);
	}

void irLeste (LAB_tppLabirinto labirinto){
	LAB_PosJog origem,destino;
	if (labirinto->idCorrente == labirinto->xMax * labirinto->yMax)
		return;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&origem);
	origem->corrente = 0;
	labirinto->idCorrente = labirinto->idCorrente + 1;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente,(void**)&destino);
	destino->corrente = 1;
	ExibirLabirinto(labirinto,0);
	}

void irOeste (LAB_tppLabirinto labirinto){
	LAB_PosJog origem,destino;
	if (labirinto->idCorrente == 1)
		return;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&origem);
	origem->corrente = 0;
	labirinto->idCorrente = labirinto->idCorrente - 1;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente,(void**)&destino);
	destino->corrente = 1;
	ExibirLabirinto ( labirinto,0);		
	}

int andarNorte ( LAB_tppLabirinto labirinto){

	LAB_PosJog origem,destino;
	int temp;
	if (labirinto->idCorrente <= labirinto->yMax)
		return 0;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&origem);
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente - labirinto->xMax,(void**)&destino);
	if (destino->tipo == PosParede || GRA_ObterIdAresta (labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente - labirinto->xMax, &temp)==GRA_CondRetArestaNaoExiste)
		return 0;
	origem->corrente = 0;
	labirinto->idCorrente = labirinto->idCorrente - labirinto->xMax;
	destino->corrente = 1;
	ExibirLabirinto(labirinto,1);
	return 1;
}
int andarSul (LAB_tppLabirinto labirinto){
	LAB_PosJog origem,destino;
	int temp;
	if (labirinto->idCorrente > (labirinto->xMax * labirinto->yMax) - labirinto->xMax)
		return 0;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&origem);
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente + labirinto->xMax,(void**)&destino);
	if (destino->tipo == PosParede || GRA_ObterIdAresta (labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente + labirinto->xMax,&temp)==GRA_CondRetArestaNaoExiste)
		return 0;
	origem->corrente = 0;
	labirinto->idCorrente = labirinto->idCorrente + labirinto->xMax;
	destino->corrente = 1;
	ExibirLabirinto(labirinto,1);
	return 1;
}

int andarOeste (LAB_tppLabirinto labirinto){
	LAB_PosJog origem,destino;
	int temp;
	if (labirinto->idCorrente == 1)
		return 0;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&origem);
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente - 1,(void**)&destino);
	if (destino->tipo == PosParede ||GRA_ObterIdAresta (labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente - 1,&temp)==GRA_CondRetArestaNaoExiste )
		return 0;
	origem->corrente = 0;
	labirinto->idCorrente = labirinto->idCorrente - 1;
	destino->corrente = 1;
	ExibirLabirinto(labirinto,1);
	return 1;
}

int andarLeste (LAB_tppLabirinto labirinto){
	LAB_PosJog origem,destino;
	int temp;
	if (labirinto->idCorrente == labirinto->xMax * labirinto->yMax)
		return 0;
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&origem);
	GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente + 1,(void**)&destino);
	if (destino->tipo == PosParede ||GRA_ObterIdAresta (labirinto->pGrafo, labirinto->idCorrente, labirinto->idCorrente + 1,&temp)==GRA_CondRetArestaNaoExiste)
		return 0;
	origem->corrente = 0;
	labirinto->idCorrente = labirinto->idCorrente + 1;
	destino->corrente = 1;
	ExibirLabirinto(labirinto,1);
	return 1;
}

void rightHandSolver( LAB_tppLabirinto labirinto){

	int i,dirV = 0, dirH = 0, visitados[500],marked = 0,loopCount = 0,solved = 0;
	LAB_PosJog posicao;
	for (i = 0; i < 500; i++)
		visitados[i] = 0;
	
	while (1){
		if (labirinto->idCorrente == labirinto->ySaida * labirinto->xMax + labirinto->xSaida + 1){
			printf("Solucionado\n");
			solved = 1;
			break;
		}
		if ( loopCount > labirinto->xMax * labirinto->yMax * 2){
			printf("Não há soluçao!!\n");
			break;
		}
		loopCount++;
		if (visitados[labirinto->idCorrente] != 1){
			marked++;
			visitados[labirinto->idCorrente] = 1;
		}
	if ( visitados[labirinto->idCorrente + 1] == 0)
		if (andarLeste(labirinto)==1){
			dirH = 1;
			continue;
		}
	if ( visitados[labirinto->idCorrente + labirinto->xMax] == 0)
		if (andarSul(labirinto)==1){
			dirV = 1;
			continue;
		}
	if ( visitados[labirinto->idCorrente - 1] == 0)
		if (andarOeste(labirinto) == 1){
			dirH = 0;
			continue;
		}
	if ( visitados[labirinto->idCorrente - labirinto->xMax] == 0)
		if (andarNorte(labirinto) == 1){
			dirV = 0;
			continue;
		}
		if (dirV == 0){
			if (andarNorte(labirinto) == 1){
				dirV = 0;
				continue;
			}
			if (dirH == 0){
				if (andarOeste(labirinto) == 1){
					dirH = 0;
					continue;
				}
			if (andarSul(labirinto) == 1){
				dirV = 1;
				continue;
			}
			if (andarLeste(labirinto) == 1){
				dirH = 1;
				continue;
			}				
			}else{
				if (andarLeste(labirinto) == 1){
					dirH = 1;
					continue;
				}
				if (andarSul(labirinto) == 1){
				dirV = 1;
				continue;
			}
				if (andarOeste(labirinto) == 1){
				dirH = 0;
				continue;
				}
			}
			
		}else{
		if (andarSul(labirinto) == 1){
			dirV = 1;
			continue;
			}
			if (dirH == 0){
				if (andarOeste(labirinto) == 1){
					dirH = 0;
					continue;
				}
				if (andarNorte(labirinto) == 1){
				dirV = 0;
				continue;
				}
				if (andarLeste(labirinto) == 1){
				dirH = 1;
				continue;
				}
			}else{
				if (andarLeste(labirinto) == 1){
					dirH = 1;
					continue;
				}
				if (andarNorte(labirinto) == 1){
				dirV = 0;
				continue;
				}
				if (andarOeste(labirinto) == 1){
				dirH = 0;
				continue;
				}
			}	
		
		}

	}
	if (solved){
		for (i = 1; i <= labirinto->xMax * labirinto->yMax; i++){
			if (visitados[i] == 1){
				GRA_ObterValorNo(labirinto->pGrafo, i,(void**)&posicao);
				posicao->caminho = 1;
			}
		}
	
	}
	ExibirLabirinto(labirinto,2);
	printf("Aperta qualquer comando para voltar a exibição normal");
}



/* Fim função: LAB &Exibir Labirinto */


int main (){
	int linhas, colunas, xEntrada, yEntrada, xSaida, ySaida, n = 1, playMode = 0, loadFlag = 0;
	char dir,filename[50];
	LAB_PosJog posicao;
	LAB_tppLabirinto labirinto;
	printf("Deseja carregar um labirinto ja existente? ( s | n )\n");
	scanf("%c",&dir);
	if (dir == 's'){
		printf("Qual o nome do arquivo?\n");
		scanf("%s",filename);
		carregaLabirinto(&labirinto,filename);
		loadFlag = 1;
	}
	if (!loadFlag){
	printf("Informe o numero de linhas:\n");
	scanf("%d",&linhas);
	printf("Informe o numero de colunas:\n");
	scanf("%d",&colunas);
	printf("Informe a coordenada x da entrada:\n");
	scanf("%d",&xEntrada);
	
	
	
	do{
	while(xEntrada >= colunas){	
		printf("Valor alto demais! Insira um valor de 0 a %d\n", colunas - 1);
		scanf("%d",&xEntrada);
	}
	printf("Informe a coordenada y da entrada:\n");
	scanf("%d",&yEntrada);
	while(yEntrada >= linhas){	
		printf("Valor alto demais! Insira um valor de 0 a %d\n", linhas - 1);
		scanf("%d",&yEntrada);
	}
	printf("Informe a coordenada x da saida:\n");
	scanf("%d",&xSaida);
	while(xSaida >= colunas){	
		printf("Valor alto demais! Insira um valor de 0 a %d\n", colunas - 1);
		scanf("%d",&xSaida);
	}
	printf("Informe a coordenada y da saida:\n");
	scanf("%d",&ySaida);
	while(ySaida >= linhas){	
		printf("Valor alto demais! Insira um valor de 0 a %d\n", linhas - 1);
		scanf("%d",&ySaida);
	}
	if (ySaida == yEntrada && xSaida == xEntrada)
		printf("Entrada e saida no mesmo lugar! Tente de novo!\n");
	}while (ySaida == yEntrada && xSaida == xEntrada);
	
	LAB_CriarLabirinto(&labirinto);
	printf("1");
	system("pause");
	GeraLabirinto(labirinto,linhas,colunas);
	printf("2");
	system("pause");
	inserirEntrada(labirinto,xEntrada,yEntrada);
	printf("3");
	system("pause");
	inserirSaida(labirinto,xSaida,ySaida);
	printf("4");
	system("pause");
	ExibirLabirinto(labirinto,0);
	}
	while (n){
		scanf("%c",&dir);
		if (playMode == 0){
		if (dir == 'w')
			irNorte(labirinto);
		if (dir == 'a')
			irOeste(labirinto);
		if (dir == 's')
			irSul(labirinto);
		if (dir == 'd')
			irLeste(labirinto);
		if (dir == 'q')
			destroiParede(labirinto);
		if (dir == 'e')
			constroiParede(labirinto);
		if (dir == 'z')
			salvaLabirinto(labirinto);
		if (dir =='l')
		{
			printf("Qual o nome do arquivo?\n");
			scanf("%s",filename);
			carregaLabirinto(&labirinto,filename);
		}
		if (dir == 'r'){
			playMode = 1;
		GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&posicao);
		posicao->corrente = 0;
		labirinto->idCorrente = labirinto->yEntrada * labirinto->xMax + labirinto->xEntrada + 1;
		GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&posicao);
		posicao->corrente = 1;
		ExibirLabirinto(labirinto,playMode);
		}
		if (dir == 'n'){
		printf("Informe o numero de linhas:\n");
	scanf("%d",&linhas);
	printf("Informe o numero de colunas:\n");
	scanf("%d",&colunas);
	printf("Informe a coordenada x da entrada:\n");
	scanf("%d",&xEntrada);
	
	
	
	do{
	while(xEntrada >= colunas){	
		printf("Valor alto demais! Insira um valor de 0 a %d\n", colunas - 1);
		scanf("%d",&xEntrada);
	}
	printf("Informe a coordenada y da entrada:\n");
	scanf("%d",&yEntrada);
	while(yEntrada >= linhas){	
		printf("Valor alto demais! Insira um valor de 0 a %d\n", linhas - 1);
		scanf("%d",&yEntrada);
	}
	printf("Informe a coordenada x da saida:\n");
	scanf("%d",&xSaida);
	while(xSaida >= colunas){	
		printf("Valor alto demais! Insira um valor de 0 a %d\n", colunas - 1);
		scanf("%d",&xSaida);
	}
	printf("Informe a coordenada y da saida:\n");
	scanf("%d",&ySaida);
	while(ySaida >= linhas){	
		printf("Valor alto demais! Insira um valor de 0 a %d\n", linhas - 1);
		scanf("%d",&ySaida);
	}
	if (ySaida == yEntrada && xSaida == xEntrada)
		printf("Entrada e saida no mesmo lugar! Tente de novo!\n");
	}while (ySaida == yEntrada && xSaida == xEntrada);
	
	LAB_CriarLabirinto(&labirinto);
	GeraLabirinto(labirinto,linhas,colunas);
	inserirEntrada(labirinto,xEntrada,yEntrada);
	inserirSaida(labirinto,xSaida,ySaida);
	ExibirLabirinto(labirinto,playMode);
		}
		}
		else{
		GRA_ObterValorNo(labirinto->pGrafo, labirinto->idCorrente ,(void**)&posicao);
		if (posicao->tipo == PosSaida)
			printf("Parabens! Voce chegou a saida!\n");
		if (dir == 'w')
			andarNorte(labirinto);
		if (dir == 'a')
			andarOeste(labirinto);
		if (dir == 's')
			andarSul(labirinto);
		if (dir == 'd')
			andarLeste(labirinto);
		if (dir == 'r'){
			playMode = 0;
			ExibirLabirinto(labirinto,playMode);
		}
		if (dir == 'o')
			rightHandSolver(labirinto);
		if (dir == 'z')
			salvaLabirinto(labirinto);
		if (dir =='l')
		{
			printf("Qual o nome do arquivo?\n");
			scanf("%s",filename);
			carregaLabirinto(&labirinto,filename);
		}
		}
	}
}