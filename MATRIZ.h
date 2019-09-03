

typedef tpMatriz pMatriz;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0 ,
               /* Executou correto */

         MAT_CondRetMatrizNaoExiste = 1 ,
               /* Matriz não existe */

         MAT_CondRetDirecaoVazia = 2 ,
               /* Nó não possui vizinho na direção especificada */

         MAT_CondRetFaltouMemoria = 3 ,
               /* Faltou memória ao alocar dados */
			   
		 MAT_CondRetMatrizJaExiste = 4 ,
               /* Ja existe uma matriz nesse endereço */
			   
		 MAT_CondRetDirecaoInvalida = 5 ,
			/* A direcao deve ser "n" "s", "e", "o", "ne", "se", "so" ou "no" */
		 
		 MAT_CondRetDimensaoInvalida = 6 ,
			/* A dimensao da nova matriz deve ser maior ou igual a 1 */

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT Criar matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia.
*     Caso já exista uma matriz, esta será destruída.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( tpMatriz* pMatriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Destruir matriz
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, anulando a matriz corrente.
*     Faz nada caso a matriz corrente não exista.
*
***********************************************************************/

   void MAT_DestruirMatriz( tpMatriz* pMatriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para direção especificada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetArvoreNaoExiste
*     MAT_CondRetArvoreVazia
*     MAT_CondRetDirecaoVazia
*
***********************************************************************/

   MAT_tpCondRet MAT_IrVizinho( tpMatriz* pMatriz, char* Direcao ) ;


/***********************************************************************
*
*  $FC Função: MAT Obter valor corrente
*
*  $EP Parâmetros
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetArvoreNaoExiste
*     MAT_CondRetArvoreVazia
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValorCorr( tpMatriz* pMatriz, char * ValorParm ) ;

