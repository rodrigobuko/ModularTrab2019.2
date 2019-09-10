/***************************************************************************
*  $MCI Módulo de definição: MAT Matriz nxn
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
*
*  Projeto: INF 1301 Trabalho 1 Arcabouço de Testes
*  Autor:   pmb Pedro Moll Bernardes
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       pmb   09/set/2019 revisão final do módulo
*	  3       pmb   07/set/2019 ajustes nas condições de retorno
*	  2       pmb   03/set/2019 ajustes nos cabeçalhos
*     1       pmb   27/ago/2019 início desenvolvimento
*
***************************************************************************/

/***********************************************************************
*
*  $TC Tipo de dados: Ponteiro para matriz
*
*
***********************************************************************/

	typedef struct tgMatriz * ptMatriz;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0 ,
            /* Executou corretamente */

         MAT_CondRetMatrizNaoExiste = 1 ,
            /* Matriz não existe */

         MAT_CondRetDirecaoVazia = 2 ,
            /* Nó não possui vizinho na direção especificada */

         MAT_CondRetFaltouMemoria = 3 ,
            /* Faltou memória ao alocar dados */
			   
		 MAT_CondRetDirecaoInvalida = 4 ,
			/* A direção deve ser "n", "s", "e", "o", "ne", "se", "so" ou "no" */
		 
		 MAT_CondRetDimensaoInvalida = 5 ,
			/* A dimensão da nova matriz deve ser maior ou igual a 1 */
			
		 MAT_CondRetValorJaInserido = 6 ,
			/* Já existe valor salvo no nó corrente*/
			
		 MAT_CondRetValorNaoInserido = 7 ,
			/* Não há valor salvo no nó */
			

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT Criar matriz
*
*  $EP Parâmetros
*  	  $P pMatriz - ponteiro que apontará para a matriz criada, passado por referência.
*  	  $P dimensao - a matriz criada será quadrada com esse valor de linhas e colunas. Deve ser maior que zero.
*	  $P ExcluirElemento - Referência de uma função para destruir o valor salvo em um nó da matriz.
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia e seus nós, inicialmente vazios. Faz as ligações entre os nós.
*	  Caso a dimensão passada seja inválida ou falte memória, retorna erro.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*	  MAT_CondRetDimensaoInvalida
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( ptMatriz * pMatriz, int dimensao, void (*ExcluirElemento) (void * Elemento)) ;


/***********************************************************************
*
*  $FC Função: MAT Destruir matriz
*
*  $EP Parâmetros
*  	  $P pMatriz - ponteiro que aponta para a matriz sobre a qual se deseja operar.
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, liberando o ponteiro passado como parâmetro e excluindo o valor de cada nó.
*     Nada faz caso a matriz referenciada não exista.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetMatrizNaoExiste
*
***********************************************************************/

   MAT_tpCondRet MAT_DestruirMatriz( ptMatriz pMatriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para direção especificada
*
*  $EP Parâmetros
*  	  $P pMatriz - ponteiro que aponta para a matriz sobre a qual se deseja operar.
*     $P Direcao - strings que indicam para qual dos nós vizinhos pCorr irá.
*		pode ser "n", "s", "e", "o", "ne", "se", "so" ou "no"

*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetDirecaoVazia
*     MAT_CondRetDirecaoInvalida
*
***********************************************************************/

   MAT_tpCondRet MAT_IrVizinho( ptMatriz pMatriz, char* Direcao ) ;


/***********************************************************************
*
*  $FC Função: MAT Inserir valor
*
*  $EP Parâmetros
*  	  $P pMatriz - ponteiro que aponta para a matriz sobre a qual se deseja operar.
*     $P Valor   - ponteiro para o valor que será inserido.
*
*  $ED Descrição da função
*     Insere o valor desejado no nó corrente da matriz
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetValorJaInserido
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirValor( ptMatriz pMatriz, void * Valor ) ;
   

/***********************************************************************
*
*  $FC Função: MAT Excluir valor
*
*  $EP Parâmetros
*  	  $P pMatriz - ponteiro que aponta para a matriz sobre a qual se deseja operar.
*
*  $ED Descrição da função
*     Exclui o valor do nó corrente da matriz, que passa a ser NULL
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetValorNaoInserido
*
***********************************************************************/

   MAT_tpCondRet MAT_ExcluirValor( ptMatriz pMatriz ) ;
   
   
/***********************************************************************
*
*  $FC Função: MAT Obter valor corrente
*
*  $EP Parâmetros
*  	  $P pMatriz - ponteiro que aponta para a matriz sobre a qual se deseja operar.
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetValorNaoInserido
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValorCorr( ptMatriz pMatriz, void ** ValorParm ) ;


/********** Fim do módulo de definição: MAT Matriz nxn **********/