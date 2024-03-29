/***************************************************************************
*  $MCI Módulo de implementação: MAT Matriz nxn
*
*  Arquivo gerado:              MATRIZ.C
*  Letras identificadoras:      MAT
*
*  Projeto: INF 1301 Trabalho 1 Arcabouço de Testes
*  Autor:   pmb Pedro Moll Bernardes
*
*  $HA Histórico de evolução:
*     4		  pmb   9/set/2019 revisão final do módulo
*	  3		  pmb   6/set/2019 ajustes de debug durante testes integrados
*     2       pmb   30/ago/2019 alteração das funcionalidade de inicialização/manipulação
*     1       pmb   27/ago/2019 início desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <string.h>
#include   "matriz.h"

   typedef struct tgNoMatriz {

         struct tgNoMatriz * pNoNorte ;
         struct tgNoMatriz * pNoSul ;
		 struct tgNoMatriz * pNoLeste ;
		 struct tgNoMatriz * pNoOeste ;
		 struct tgNoMatriz * pNoNordeste ;
		 struct tgNoMatriz * pNoSudeste ;
		 struct tgNoMatriz * pNoSudoeste ;
		 struct tgNoMatriz * pNoNoroeste ;
				/* Ponteiros para os nós vizinhos */

         void* Valor ;
               /* Valor do nó */

   } tpNoMatriz ;
   
   typedef struct tgMatriz {

         tpNoMatriz * pNo01 ;
               /* Ponteiro para o primeiro nó*/

         tpNoMatriz * pNoCorr ;
               /* Ponteiro para o nó corrente da matriz */
			   
		 void (*ExcluirElemento) (void * Elemento);
			  /* Referencia uma função para destruir o valor salvo em um nó */

   } tpMatriz ;
   
/***** Protótipos das funções encapuladas no módulo *****/

   int PreencherMatriz(ptMatriz pMatriz, int dimensao);

   static tpNoMatriz * CriarNo() ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT Criar matriz
*  ****/

   MAT_tpCondRet MAT_CriarMatriz( ptMatriz * pMatriz, int dimensao, void (*ExcluirElemento) (void * Elemento) )
   {
	  ptMatriz nptr;
	  
	  if( dimensao < 1 ) /* a matriz deve ter dimensão maior que zero */
		  return MAT_CondRetDimensaoInvalida;

      nptr = ( ptMatriz ) malloc( sizeof( tpMatriz )) ;
      if ( nptr == NULL )
      {
         return MAT_CondRetFaltouMemoria ;
      } /* if */

      nptr->pNo01 = NULL ;
      nptr->pNoCorr = NULL ;
	  nptr->ExcluirElemento = ExcluirElemento;
	  *pMatriz = nptr;
	  
	  if(!PreencherMatriz( *pMatriz, dimensao))
		  return MAT_CondRetFaltouMemoria;

      return MAT_CondRetOK ;

   } /* Fim função: MAT Criar matriz */


/***************************************************************************
*
*  Função: MAT Destruir matriz
*  ****/

   MAT_tpCondRet MAT_DestruirMatriz( ptMatriz pMatriz )
   {
	  tpNoMatriz * pNo;
	  tpNoMatriz * pNoAnterior;
	  int baixo_cima;

	  if( pMatriz == NULL)
		  return MAT_CondRetMatrizNaoExiste;
	  
	  pNo = pMatriz->pNo01;
	  pNoAnterior = pNo;
	  
	  baixo_cima = 0; /* valor 1 indica que a coluna deve ser percorrida ao contrário */
	  
	  while( pNo != NULL ){ /* até acabarem as colunas */
		while(1){ /* anda na vertical até encontrar um NULL, indicando o fim da coluna */
			if( ! baixo_cima ){
				pNo = pNoAnterior->pNoSul;
				if(pNo == NULL)
					break;
				if(pNoAnterior->Valor != NULL)
					pMatriz->ExcluirElemento(pNoAnterior->Valor);
				free( pNoAnterior );
				pNoAnterior = pNo;
					/* passamos para o nó de baixo eliminamos o anterior */
			}else{
				pNo = pNoAnterior->pNoNorte;
				if(pNo == NULL)
					break;
				if(pNoAnterior->Valor != NULL)
					pMatriz->ExcluirElemento(pNoAnterior->Valor);
				free( pNoAnterior );
				pNoAnterior = pNo;
					/* passamos para o nó de cima eliminamos o anterior */
			}
		}
		pNo = pNoAnterior->pNoLeste;
		if(pNoAnterior->Valor != NULL)
			pMatriz->ExcluirElemento(pNoAnterior->Valor);
		free(pNoAnterior);
		pNoAnterior = pNo;
		baixo_cima = !(baixo_cima); /* a próxima coluna deve ser percorrida na direção contrária */
	  }
	  free( pMatriz );
	  
	  return MAT_CondRetOK;
   } /* Fim função: MAT Destruir matriz */


/***************************************************************************
*
*  Função: MAT Ir vizinho
*  ****/

	MAT_tpCondRet MAT_IrVizinho( ptMatriz pMatriz, char* Direcao ){
		
		tpNoMatriz * pNo;
		if( pMatriz == NULL)
			return MAT_CondRetMatrizNaoExiste;
		
		if( strcmp(Direcao,"n") == 0 )
			pNo = pMatriz->pNoCorr->pNoNorte;
		else if( strcmp(Direcao,"s") == 0 )
			pNo = pMatriz->pNoCorr->pNoSul;
		else if( strcmp(Direcao,"e") == 0 )
			pNo = pMatriz->pNoCorr->pNoLeste;
		else if( strcmp(Direcao,"o") == 0 )
			pNo = pMatriz->pNoCorr->pNoOeste;
		else if( strcmp(Direcao,"ne") == 0 )
			pNo = pMatriz->pNoCorr->pNoNordeste;
		else if( strcmp(Direcao,"se") == 0 )
			pNo = pMatriz->pNoCorr->pNoSudeste;
		else if( strcmp(Direcao,"so") == 0 )
			pNo = pMatriz->pNoCorr->pNoSudoeste;
		else if( strcmp(Direcao,"no") == 0 )
			pNo = pMatriz->pNoCorr->pNoNoroeste;
		else
			return MAT_CondRetDirecaoInvalida;
		
		if( pNo == NULL )
			return MAT_CondRetDirecaoVazia;
		
		pMatriz->pNoCorr = pNo;
		
		return MAT_CondRetOK;
	} /* Fim função: MAT Ir para nó vizinho */
	
	
/***************************************************************************
*
*  Função: MAT Inserir valor
*  ****/

	MAT_tpCondRet MAT_InserirValor( ptMatriz pMatriz, void * Valor ){
		
		if( pMatriz == NULL)
			return MAT_CondRetMatrizNaoExiste;
		
		if( pMatriz->pNoCorr->Valor != NULL)
			return MAT_CondRetValorJaInserido;
		
		pMatriz->pNoCorr->Valor = Valor;

		return MAT_CondRetOK;
		
	} /* Fim função: MAT Obter valor do nó corrente */
	
	
	/***************************************************************************
*
*  Função: MAT Excluir valor
*  ****/

	MAT_tpCondRet MAT_ExcluirValor( ptMatriz pMatriz ){
		
		if( pMatriz == NULL)
			return MAT_CondRetMatrizNaoExiste;
		
		if( pMatriz->pNoCorr->Valor == NULL)
			return MAT_CondRetValorNaoInserido;
		
		pMatriz->ExcluirElemento(pMatriz->pNoCorr->Valor);
		
		pMatriz->pNoCorr->Valor = NULL;
		
		return MAT_CondRetOK;
		
	} /* Fim função: MAT Obter valor do nó corrente */
	
	
/***************************************************************************
*
*  Função: MAT Obter valor corr
*  ****/

	MAT_tpCondRet MAT_ObterValorCorr( ptMatriz pMatriz, void ** ValorParm ){
		
		void * valorDeRetorno;
		
		if( pMatriz == NULL)
			return MAT_CondRetMatrizNaoExiste;
		
		valorDeRetorno = pMatriz->pNoCorr->Valor;
		
		if( valorDeRetorno == NULL)
			return MAT_CondRetValorNaoInserido;
		
		*ValorParm = valorDeRetorno;
		
		return MAT_CondRetOK;
	} /* Fim função: MAT Obter valor do nó corrente */
	
	
/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: MAT Criar nó da matriz
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     O valor  e os ponteiros do nó criado estarão nulos.
*
***********************************************************************/

   tpNoMatriz * CriarNo( )
   {

      tpNoMatriz * pNo ;

      pNo = ( tpNoMatriz * ) malloc( sizeof( tpNoMatriz )) ;
      if ( pNo == NULL )
      {
         return NULL ; /* faltou memória */
      } /* if */

      pNo->pNoNorte = NULL ;
      pNo->pNoSul = NULL ;
      pNo->pNoLeste = NULL ;
	  pNo->pNoOeste = NULL ;
	  pNo->pNoNordeste = NULL ;
	  pNo->pNoSudeste = NULL ;
	  pNo->pNoSudoeste = NULL ;
	  pNo->pNoNoroeste = NULL ;
      pNo->Valor  = NULL ;
      return pNo ;

   } /* Fim função: MAT criar nó da matriz */


/***********************************************************************
*
*  $FC Função: MAT Preencher matriz
*
*  $ED Descrição da função
*     Cria todos os nós e faz a ligação entre eles.
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz que será preenchida
*	  $P Dimensao - a dimensão n da matriz quadrada nxn que será formada. Deve ser maior que zero.
* 
*  $FV Valor retornado
*     retorna 0 caso haja falta de memória
*     retorna 1 caso a matriz seja preenchida corretamente
*
***********************************************************************/

   int PreencherMatriz( ptMatriz pMatriz, int dimensao )
   {
	   tpNoMatriz * pNo;
	   tpNoMatriz * pNoAnterior;
	   int esquerda_direita, i, j;
	   
	   /* primeiro nó */
	    pNoAnterior = CriarNo();
		
		pMatriz->pNo01 = pNoAnterior;
		pMatriz->pNoCorr = pNoAnterior;
	   
	   /* primeira linha */
		for(j = 1; j < dimensao; j++ ){
			pNo = CriarNo();
			if(pNo == NULL){ /* faltou memória */
				return 0;
			}
			
			pNo->pNoOeste = pNoAnterior;
			pNoAnterior->pNoLeste = pNo;
			
			pNoAnterior = pNo;
        }
		esquerda_direita = 0; /* a proxima linha deve ser percorrida para a esquerda */
		
	   /* demais linhas */
	    for(i = 1; i < dimensao; i++ ){
			
			if( esquerda_direita ){ /*percorrendo a linha da esquerda para a direita */
				for(j = 0; j < dimensao; j++ ){
					
					pNo = CriarNo();
					if(pNo == NULL){ /* faltou memória */
						return 0;
					}
			
					if( j != 0 ){ /* são feitas as ligações com o nó anterior (da esquerda), com o nó de cima, com o nó acima do anterior, e do nó anterior com o nó acima do atual*/
						pNo->pNoOeste = pNoAnterior;
						pNoAnterior->pNoLeste = pNo;
						
						pNo->pNoNoroeste = pNoAnterior->pNoNorte;
						pNo->pNoNoroeste->pNoSudeste = pNo;
						
						pNo->pNoNorte = pNo->pNoNoroeste->pNoLeste;
						pNo->pNoNorte->pNoSul = pNo;
						
						pNoAnterior->pNoNordeste = pNo->pNoNorte;
						pNo->pNoNorte->pNoSudoeste = pNoAnterior;
					}
					else{ /*nó mais à esquerda da linha, é ligado apenas com o nó de cima */
						pNoAnterior->pNoSul = pNo;
						pNo->pNoNorte = pNoAnterior;
					}
					pNoAnterior = pNo;
				}
				esquerda_direita = 0; /* a proxima linha será percorrida da direita para a esquerda */
			}
			else{ /*percorrendo a linha da direita para a esquerda */
				for(j = dimensao - 1; j >= 0; j-- ){
					
					pNo = CriarNo();
					if(pNo == NULL){ /* faltou memória */
						return 0;
					}
					
					if( j != dimensao-1 ){ /* são feitas as ligações com o nó anterior (da direita), com o nó de cima, com o nó acima do anterior, e do nó anterior com o nó acima do atual*/
						pNo->pNoLeste = pNoAnterior;
						pNoAnterior->pNoOeste = pNo;
						
						pNo->pNoNordeste = pNoAnterior->pNoNorte;
						pNo->pNoNordeste->pNoSudoeste = pNo;
						
						pNo->pNoNorte = pNo->pNoNordeste->pNoOeste;
						pNo->pNoNorte->pNoSul = pNo;
						
						pNoAnterior->pNoNoroeste = pNo->pNoNorte;
						pNo->pNoNorte->pNoSudeste = pNoAnterior;
					}
					else{ /* nó mais à direita da linha, é ligado apenas com o nó de cima */
						pNoAnterior->pNoSul = pNo;
						pNo->pNoNorte = pNoAnterior;
					}
					pNoAnterior = pNo;
				}
				esquerda_direita = 1; /* a proxima linha será percorrida da esquerda para a direita */
			}
		}
		return 1;
   } /* Fim função: MAT Preencher matriz */
   
   
/********** Fim do módulo de implementação: MAT Matriz nxn **********/