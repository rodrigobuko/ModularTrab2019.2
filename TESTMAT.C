/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTMAT.C
*  Letras identificadoras:      TMAT
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo matriz.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo matriz:
*
*     "=criar"      - chama a fun��o MAT_CriarMatriz( )
*     "=ir"         - chama a fun��o MAT_IrVizinho( )
*     "=obter"
*                   - chama a fun��o MAT_ObterValorCorr( ) e compara
*                     o valor retornado com o valor <Char>
*     "=destroi"    - chama a fun��o MAT_DestruirMatriz( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "matriz.h"
#include    "lista.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_MAT_CMD       "=criar"
#define     IR_VIZINHO_CMD      "=ir"
#define     OBTER_VAL_CMD       "=obter"
#define     INSERIR_VAL_CMD     "=inserir"
#define     EXCLUIR_VAL_CMD     "=excluir"
#define     DESTROI_CMD         "=destruir"

/* DEFINES */

#define     QTD_MAT             10

/*****  Inicializa��o de vari�veis est�ticas do m�dulo  *****/

static ptMatriz vMatriz[QTD_MAT] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

/*****  Prot�tipo de ExcluirElemento  *****/

void ExcluirElemento(void * p);

/***********************************************************************
*
*  $FC Fun��o: TMAT Efetuar opera��es de teste espec�ficas para matriz
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     matriz sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      MAT_tpCondRet CondRetObtido   = MAT_CondRetOK ;
      MAT_tpCondRet CondRetEsperada = MAT_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char StringDado[]  = "??" ;
      int  IntDado1      = -1 ;
	  int  IntDado2      = -1 ;
	  
	  int i;
	  LIS_tppLista ListaDada;
	  LIS_tppLista ListaObtida;
	  
      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

	

      /* Testar MAT Criar matriz */

         if ( strcmp( ComandoTeste , CRIAR_MAT_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "iii" ,
                               &IntDado1, &IntDado2, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_CriarMatriz( vMatriz[IntDado1], IntDado2 ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar matriz." );

         } /* fim ativa: Testar MAT Criar matriz */

      /* Testar MAT Ir para vizinho */

         else if ( strcmp( ComandoTeste , IR_VIZINHO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "isi" ,
                               &IntDado1, StringDado , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_IrVizinho( vMatriz[IntDado1], StringDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para vizinho." );

         } /* fim ativa: Testar MAT Ir para n� vizinho */

      /* Testar MAT Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici" ,
                               &IntDado1, &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_ObterValorCorr( vMatriz[IntDado1], &ListaObtida ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , *((char *)LIS_ObterValor(ListaObtida)) ,
                                     "Conte�do do n� est� errado." ) ;

         } /* fim ativa: Testar MAT Obter valor corrente */

      /* Testar MAT Inserir valor no n� corrente */

         else if ( strcmp( ComandoTeste , INSERIR_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "isi" ,
                               &IntDado1, StringDado , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			
			ListaDada = LIS_CriarLista(ExcluirElemento);
			
			for (i = 0; StringDado[i]!='\0'; i++)
			{
				LIS_InserirElementoApos(ListaDada, &(StringDado[i]));
			}
			
            CondRetObtido = MAT_InserirValor( vMatriz[IntDado1], ListaDada ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir valor." );

         } /* fim ativa: Testar MAT Inserir valor no n� corrente */

      /* Testar MAT excluir valor */

         else if ( strcmp( ComandoTeste , EXCLUIR_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &IntDado1, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_ExcluirValor( vMatriz[IntDado1] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao excluir valor corrente." );

         } /* fim ativa: Testar MAT excluir valor */

      /* Testar MAT Destruir matriz */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i", &IntDado1 ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */
            MAT_DestruirMatriz( vMatriz[IntDado1] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar MAT Destruir matriz */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TMAT Efetuar opera��es de teste espec�ficas para matriz */

/*****  Fun��o necess�ria para passar para lista  *****/

   void ExcluirElemento(void * p)
   {
	   free(p);
   }



/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
