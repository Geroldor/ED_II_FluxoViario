#ifndef _DIGRAPH__
#define _DIGRAPH__

#include <stdbool.h>
#include "lista.h"

/*
Um Grafo Direcionado (Digraph) G e' constituido por um conjunto de vertices V e 
um conjunto de arestas E, denotado por G=(V,E). 

Pode-se associar um dado (tipo Info) a arestas e a vertices de G.
A cada vertices e' associado um nome (veja createGraph e addNode).

Arestas de um grafo podem ser temporariamente desabilitadas. Uma aresta quando 
desabilitada, parece ter sido removida (ou seja, parece nao existir no grafo). 
Porem, as informacoes associadas a tal aresta sao mantidas (apesar de inacessiveis). 
Posteriormente, a aresta pode ser habilitada novamente, retornando ao 
estado que estava antes da desabilitacao.

Podem ser definidos subgrafos de um dado grafo. Um subgrafo pode ser entendido 
como uma vis�o (ou filtro) sobre o grafo original. Ou, ainda, um subgrafo 
define (delimita) uma "regi�o" do grafo a ser acessada.
Note que um subgrafo continua estreitamente relacionado ao grafo original, 
de forma que um v�rtice do subgrafo e' exatamente o mesmo vertice do grafo 
original (ou seja, n�o � uma c�pia).
Tamb�m, uma aresta de um subgrafo e' a mesma aresta no grafo original.

Cada subgrafo possui um nome. Um grafo pode pode possuir v�rios subgrafos. 
Cada subgrafo deve ter um nome distinto.
A opera��o createSubgraphDG permite a criacao de um novo subgrafo. Este novo 
subgrafo pode so' conter um subconjunto dos vertices do grafo original ou pode 
ser induzido a partir deste subconjunto. 
Novas arestas podem ser acrescentas ao subgrafo por meio da operacao 
includeEdgeSDG e retiradas por excludeEdgeSDG. Note que a aresta acrescentada 
deve existir no grafo original e que a aresta exclu�da do subgrafo NAO e' 
excluida do grafo original.
Existem tambem outras operacoes que possibilitam percorrer o subgrafo.

O modulo tambem oferece duas operacoes de percurso sobre o grafo: busca em largura (bfs) 
e busca em profundidade (dfs).
Estes percursos tem por parametros funcoes que sao invocadas quando arestas do grafo 
sao "descobertas" durante o percurso. 
Caso alguma dessas funcoes retornar TRUE, o percurso � interrompido.
*/


typedef void *Digraph;
typedef int Node;
typedef void *Edge;
typedef void *Info;

/*
  "e" e' a aresta "descoberta"/"percorrida"/"classificada". td e' o tempo da descoberta (quando pintado de cinza).
  tf e' tempo de finalizacao (quando pintado de preto).
 */
bool (*procEdge)(Digraph g, Edge e, int td, int tf, void *extra); 

bool (*dfsRestarted)(Digraph g, void *extra);


/*
    Cria um grafo orientado com, no maximo, "nVert" vertices.
    Os vertices devem ser posteriormente inseridos por meio
    da operacao addNode.
 */
Digraph createGraph(int nVert);


/*
    Retorna numero maximo de vertices que grafo g pode conter.
    (veja createGraph).
 */
int getMaxNodes(Digraph g);


/*
    Retorna numero total de vertices adicionados ao grafo gr.
    (veja addNode).
 */
int getTotalNodes(Digraph g);


/*
    Adiciona um novo v�rtice ao grafo "g" com o nome "nome".
    O n�mero de vertices adicionados nao pode ser superior o 
    numero maximo informado em createGraph.
    Retorna o n� criado.
 */
Node addNode(Digraph g, char *nome, Info info);


/*
    Retorna no' cujo de nome e' "nome". Retorna -1, caso o nao
    exista no com o nome especificado.
 */
Node getNode(Digraph g,  char *nome);


/*
    Retorna informacao associada ao no' node.
    node deve ser um no' existente no grafo.
 */
Info getNodeInfo(Digraph g, Node node);


/*
    Retorna nome associado ao no' node.
    node deve ser um no' existente no grafo.
 */
char *getNodeName(Digraph g, Node node);


/*
    Atribui ao no' "node" a informacao "info"
 */
void setNodeInfo(Digraph g, Node node, Info info);


/*
    Adiciona a aresta (from,to) ao grafo. Atribui
    a informacao info `a aresta.
 */
Edge addEdge(Digraph g, Node from, Node to, Info info);


/*
    Retorna a aresta (from,to). Se a aresta não existe,
    retorna NULL.
 */
Edge getEdge(Digraph g, Node from, Node to);


/*
   Retorna o no' de origem na aresta "e".
 */
Node getFromNode(Digraph g, Edge e);

  
/*
    Retorna o no' de destino da aresta "e".
 */  
Node getToNode(Digraph g, Edge e);


/*
    Retorna a informacao associada 'a aresta "e".
    A informacao deve ter sido anteriormente associada 'a
    aresta pela operacao setEdgeInfo.
 */
Info getEdgeInfo(Digraph g, Edge e);


/*
   Associa a informacao "info" 'a aresta "e".
 */
void setEdgeInfo(Digraph g, Edge e, Info info);


/*
    Dado g=(V,E) tal que "e" pertence a E,
    retira "e" de E (E = E - {e}).
 */
void removeEdge(Digraph g, Edge e);


/*
   Retorna verdadeiro se existe a aresta (from,to)
   no grafo g; falso, caso contrario.
 */
bool isAdjacent(Digraph g, Node from, Node to);


/* 
   Adiciona 'a lista "nosAdjacentes" os nos adjacentes ao no "node".
 */
void adjacentNodes(Digraph g, Node node, Lista nosAdjacentes);


/*
   Adiciona 'a lista "arestaAdjacentes" as arestas (x,y), tal que,
   x == node.
 */
void adjacentEdges(Digraph g, Node node, Lista arestasAdjacentes);


/*
   Insere na lista "nomesNodes" os nomes atribuidos aos nos do grafo.
 */
void  getNodeNames(Digraph g, Lista nomesNodes);


/*
   Insere na lista "arestas", as arestas (Edge) do grafo g.
 */
void getEdges(Digraph g, Lista arestas);


/*
   Faz percurso em profundidade sobre o grafo g, a partir do no' node, classificando 
   as arestas do grafo em aresta de arvore, aresta de avanco, de retorno e cruzada. 
   No momento da classificacao, a respectiva funcao e' invocada (caso nao seja NULL).
   "extra" e' um apontador que pode ser usado por qualquer uma das funcoes.
   A busca em profundidade, eventualmente, pode produzir uma floresta. Neste caso,
   a funcao newTree e' invocada sempre que o percurso for retomado.
 */  
bool dfs(Digraph g, Node node, procEdge treeEdge, procEdge forwardEdge, procEd returnEdge,
	 procEdge crossEdge, dfsRestarted newTree, void *extra);


/*
   Percorre o grafo g em largura, a partir do no' node. Invoca a funcao discoverNode (se != NULL)
   para a aresta (x,y) usada para "descobrir" o no' y.
   "extra" e' um apontador que pode ser usado por qualquer uma das funcoes.
 */
bool bfs(Digraph g, Node node, procEdge discoverNode, void *extra);


/*
   Destroi o grafo "g" e libera os recursos utilizados por g.
 */
void killDG(Digraph g);

/*
 **********************
 * SUB-GRAFOS
 **********************
/*
    Calcula o subgrafo composto  pelos vertices cujos nomes estao no vetor nomesVerts
(nVerts e' o tamanho deste vetor). Caso comAresta seja true calcula o subgrafo induzido pelos
vertices em nomesVers (i.e., tambem inclue algumas arestas).
Note que ss vertices e arestas do subgrafo sao "os mesmos" do grafo original. 
Isto e', qualquer alteracao feitas nas informacoes associadas aos
vertices e arestas de um tambem sao percebidas pelo outro.
 */
void  createSubgraphDG(Digraph g, char *nomeSubgrafo, char *nomesVerts[], int nVert,
		       bool comArestas);


/*
    Adiciona a aresta "e", existente no grafo g, ao subgrafo nomeSubgrafo.
 */
Edge includeEdgeSDG(Digraph g, char *nomeSubgrafo, Edge e);

/*
  Retorna verdadeiro se a aresta "e" pertence ao subgrafo "nomeSubgrafo" do grafo g; 
  falso, caso contrario.
 */
bool existsEdgeSDG(Digraph g, char *nomeSubgrafo, Edge e);

/*
  Retira a aresta "e" do subgrafo "nomeSubgrafo". Ou seja, desfaz a correspondente 
  operacao includeEdgeSg previamente executada. 
  Note que a aresta  "e" NAO e' removida do grafo g.
 */
void excludeEdgeSDG(Digraph g, char *nomeSubgrafo, Edge e);

/*
   Adiciona 'a lista "arestaAdjacentes" as arestas (x,y), tal que:
   x == node; x pertence ao subgrafo "nomeSubgrafo", (x,y) tambem e' aresta
   do subgrafo.
 */
void adjacentEdgesSDG(Digraph g, char *nomeSubgrafo, Node node, Lista arestasAdjacentes);

/*
   Adiciona 'a lista "lstNodes" (Lista<Node>) os n�s do subgrafo "nomeSubgrafo".
 */
void getAllNodesSDG(Digraph g, char *nomeSubgrafo,  Lista lstNodes);

/*
   Adiciona 'a lista "lstEdges" (Lista<Edge>) as arestas do subgrafo "nomeSubgrafo".
 */
void getAllEdgesSDG(Digraph g, char *nomeSubgrafo, Lista lstEdges);


#endif
