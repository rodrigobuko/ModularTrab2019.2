
/***********************************************************************
*
*  $TC Tipo de dados: Ponteiro para matriz
*
*
***********************************************************************/

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
*  $EP Parâmetros
*  	  $P tpMatriz - ponteiro que apontará para a matriz criada.
*  	  $P PonteirosDosValores - aponta para uma lista contendo os ponteiros para os valores que cada célula deverá ter.
*  	  $P dimensao - a matriz criada será quadrada com esse valor de linhas e colunas. Deve ser maior que zero.
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia e seus nós. Preenche os valores e as ligações dos nós.
*     Caso já exista uma matriz, retorna um erro.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*	  MAT_CondRetDimensaoInvalida
*	  MAT_CondRetMatrizJaExiste
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( tpMatriz* pMatriz, void** PonteirosDosValores, int dimensao ) ;


/***********************************************************************
*
*  $FC Função: MAT Destruir matriz
*
*  $EP Parâmetros
*  	  $P tpMatriz - ponteiro que aponta para a matriz sobre a qual se deseja operar.
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, anulando o ponteiro passado como parâmetro.
*     Faz nada caso a matriz corrente não exista.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetMatrizJaExiste
*
***********************************************************************/

   MAT_tpCondRet MAT_DestruirMatriz( tpMatriz* pMatriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para direção especificada
*
*  $EP Parâmetros
*  	  $P tpMatriz - ponteiro que aponta para a matriz sobre a qual se deseja operar.
*     $P Direcao - caracteres que indicam para qual dos nós vizinhos pCorr irá.
*		pode ser "n", "s", "e", "o", "ne", "se", "so" ou "no"

*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetDirecaoVazia
*
***********************************************************************/

   MAT_tpCondRet MAT_IrVizinho( tpMatriz* pMatriz, char* Direcao ) ;


/***********************************************************************
*
*  $FC Função: MAT Obter valor corrente
*
*  $EP Parâmetros
*  	  $P tpMatriz - ponteiro que aponta para a matriz sobre a qual se deseja operar.
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValorCorr( tpMatriz* pMatriz, char * ValorParm ) ;

