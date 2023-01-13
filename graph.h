#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#define info(P) (P)->info
#define next(P) (P)->next
#define start(P) (P).start
#define firstEdge(P) (P)->firstEdge

using namespace std;

typedef string infotype;

typedef struct elmEdge *adrEdge;
typedef struct elmNode *adrNode;

struct elmEdge {
    infotype info;
    adrEdge next;
};
struct elmNode{
    infotype info;
    adrNode next;
    adrEdge firstEdge;
};

struct Graph {
    adrNode start;
};

void createGraph(Graph &G);

adrEdge newEdge(infotype x);
adrNode newNode(infotype x);

void addNode(Graph &G, adrNode p);
void addEdge(Graph &G, infotype x, infotype y);

adrNode findNode(Graph G,infotype x);
bool isConnected(Graph G, infotype x, infotype y);
int countNodeDegree(adrNode P);

void deleteNode(Graph &G, adrNode P);                   // menghapus node
void deleteNodeConnection(Graph &G, adrNode P);         //menghapus hubungan kepada node yang akan kau hapu
void deleteEdge(Graph &G, adrNode P,infotype x);        // mengapus edge pada edge list

void printGraph(Graph G);
void PrintEdgeOfNode(Graph G,adrNode P);
void printMostConnection(Graph G);
void printCities(Graph G);

// progream function
void showMenu();
int chooseMenu();
bool goBackToMenu();
void clearScreen();
void insertManualNode(Graph &G);

#endif // GRAPH_H_INCLUDED
