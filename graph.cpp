#include "graph.h"
#include <iostream>
using namespace std;

void createGraph(Graph &G){
    start(G) = NULL;
};

adrNode newNode(infotype x){
    adrNode P = new elmNode;
    info(P) = x;
    next(P) = NULL;
    firstEdge(P) = NULL;
    return P;
};
adrEdge newEdge(infotype x){
    adrEdge P = new elmEdge;
    info(P) = x;
    next(P) = NULL;
    return P;
};

void addNode(Graph &G,adrNode P){
    adrNode Q = start(G);
    if (Q == NULL){
        // run when graph is empty
        start(G) = P;
    }else {
        // insert Last on graph List
        while(next(Q) != NULL){
            Q = next(Q);
        }
        next(Q) = P;
    }
};
void addEdge(Graph &G,infotype x, infotype y){
    adrNode pG = start(G);
    if (isConnected(G,x,y)){
        // run when node x and y is already connected
        cout << x << " and " << y << " is already connected" << endl;
    }else {
        // find the node that will be connect
        adrNode nodeX = findNode(G,x);
        adrNode nodeY = findNode(G,y);

        // create new edge based on finded node
        adrEdge edgeX = newEdge(info(nodeX));
        adrEdge edgeY = newEdge(info(nodeY));

        if (nodeX == nodeY){
            if (firstEdge(nodeX) == NULL){
                firstEdge(nodeX) = edgeY;
            }else {
                next(edgeY) = firstEdge(nodeX);
                firstEdge(nodeX) = edgeY;
            }
        }else {
                // add the edge Y to node X
            if (firstEdge(nodeX) == NULL){
                firstEdge(nodeX) = edgeY;
            }else {
                next(edgeY) = firstEdge(nodeX);
                firstEdge(nodeX) = edgeY;
            }
                // add the edge X to node Y
            if (firstEdge(nodeY) == NULL){
                firstEdge(nodeY) = edgeX;
            }else {
                next(edgeX) = firstEdge(nodeY);
                firstEdge(nodeY) = edgeX;
            }
        }
    }
};

adrNode findNode(Graph G,infotype x){
    if (start(G) == NULL){
        cout << "Graph Kosong" << endl;
    }else {
        adrNode P = start(G);
        while(P != NULL && info(P) != x){
            P = next(P);
        }
        return P;
    }
    return NULL;
};

// function untuk menghapus node dari List Graph
void deleteNode(Graph &G, adrNode P){
    adrNode Q = start(G);
    if (Q != NULL){
        if (P == start(G)){                         // pengecekan jika P berapa diawal graph, jika iya deleteFirst Node
            start(G) = next(P);
            next(P) = NULL;
            deleteNodeConnection(G,P);              // penghapusan semua edge yang berhubungan dengan adrNode P
        }else if (next(P) == NULL) {                // pengecekan jika P berapa diakhir graph, jika iya deleteLast
            while ( next(next(Q)) != NULL){
                Q = next(Q);
            }
            next(Q) = NULL;
            deleteNodeConnection(G,P);              // penghapusan semua edge yang berhubungan dengan adrNode P
        }else {
            while(next(Q) != NULL && next(Q) != P){ // pengambilan elemen sebelum elemen terakhir, sehingga cover link
                Q = next(Q);
            }
            if (Q != NULL){
                next(Q) = next(P);
                next(P) = NULL;
                deleteNodeConnection(G,P);          // penghapusan semua edge yang berhubungan dengan adrNode P
            }
        }
    }
};
// function untuk menghapus connection dengan menggunakan binary search,
void deleteNodeConnection(Graph &G, adrNode P){
    adrNode Q = start(G);
    adrEdge R;
    while (Q != NULL){                     // looping untuk melakukan pencarian pada list childnya
        R = firstEdge(Q);
        while(R != NULL){                  // looping untuk melakukan pengecekan info R dan info P
            if (info(R) == info(P)){
                deleteEdge(G,Q,info(P));    // memanggil deleteEdge untuk menghapus edge pada list edge dari node P
            }
            R = next(R);
        }
        Q = next(Q);
    }
};
// menghapus edge dari list edge pada node P,
void deleteEdge(Graph &G, adrNode P,infotype x){
    adrEdge edgeX,tempEdge;
    if (firstEdge(P) != NULL){                                  // pengecekan jika edge tidak kosong
        if (info(firstEdge(P)) == x){                           // pengecekan jika edge berada di firstEdge, jika iya maka deleteFirst edge
            edgeX = firstEdge(P);
            firstEdge(P) = next(edgeX);
            next(edgeX) = NULL;
        }else {
            edgeX = firstEdge(P);
            while (next(edgeX) != NULL && info(next(edgeX)) != x){ // looping untuk menunjuk ke elemen sebelum x, untuk melakukan deleteAfter dan deleteLast
                edgeX = next(edgeX);
            }
            tempEdge = next(edgeX);
            next(edgeX) = NULL;
        }
    }
};
bool isConnected(Graph G, infotype x, infotype y){
    adrNode P = start(G);
    adrEdge Q;
    // search the node
    while (P != NULL){
        Q = firstEdge(P);
        if (info(P) == x){
            // search the edge
            while (Q != NULL){
                if (info(Q) == y){
                    // if edge Y found on Node X
                    return true;
                }
                Q = next(Q);
            }
        }
        P = next(P);
    }
    return false;
};
void printGraph(Graph G){
    adrNode P = start(G);
    adrEdge Q;
    while (P != NULL){
        PrintEdgeOfNode(G,P);
        P = next(P);
    }
};
void PrintEdgeOfNode(Graph G,adrNode P){
    adrEdge edgeP = firstEdge(P);
    cout << "Kota " << info(P) << ": ";
    if (edgeP != NULL) {
        while (edgeP != NULL){
            cout << info(edgeP);
            if (next(edgeP) != NULL){
                cout << " - ";
            }
            edgeP = next(edgeP);
        }
    }
    cout << endl;
}
int countNodeDegree(adrNode P){
    adrEdge Q = firstEdge(P);
    int countDegree = 0;
    while (Q != NULL){
        countDegree++;
        Q = next(Q);
    }
    return countDegree;
}
void printMostConnection(Graph G){
    adrNode P = start(G);
    int degree = countNodeDegree(P);
    adrNode mostP = P;
    int mostDegree = degree;
    while (P != NULL) {
        degree = countNodeDegree(P);
        if (degree > mostDegree) {
            mostDegree = degree;
            mostP = P;
        }
        P = next(P);
    }
    P = start(G);
    adrEdge Q = firstEdge(mostP);
    while (Q != NULL) {
        cout << info(Q);
        if (next(Q) != NULL) {
            cout << " - ";
        }
        Q = next(Q);
    }
    cout << endl;
};
void printCities(Graph G) {
    adrNode P = start(G);
    int i = 0;
    cout << "=================================================" << endl;
    while (P != NULL){
        i++;
        cout << info(P) << " ";
        if (i % 5 == 0 && next(P) != NULL) {
            cout << endl;
        }
        P = next(P);
    }
    cout <<endl<<"=================================================" << endl;
}

//program function
void showMenu() {
    clearScreen();
    cout << "================= MENU =================" << endl;
    cout << "1. Menambahkan Kota" << endl;
    cout << "2. Menambahkan Hubungan Antar Kota" << endl;
    cout << "3. Menampilkan Jalur Dari/ke Kota X" << endl;
    cout << "4. Menampilkan Kota yang memiliki jalur terbanyak" << endl;
    cout << "5. Menampilkan Semua Kota" << endl;
    cout << "6. Menampilkan Graph" << endl;
    cout << "7. Menghapus Kota" << endl;
    cout << "0. exit" << endl;
    cout << "========================================" << endl;
}
int chooseMenu() {
    showMenu();
    int choosenMenu = 0;
    cout << "Pilih Menu: ";cin >> choosenMenu;
    return choosenMenu;
}
bool goBackToMenu() {
    char backMenu;
    cout << "Kembali ke manu?<y/n>: ";cin >> backMenu;
    if (backMenu == 'y' || backMenu == 'Y') {
        return true;
    }else {
        return false;
    }
}
void clearScreen(){
    if (system("CLS")) system("clear");
};
void insertManualNode(Graph &G) {
    addNode(G,newNode("Brebes"));
    addNode(G,newNode("Tegal"));
    addNode(G,newNode("Pemalang"));
    addNode(G,newNode("Pekalongan"));
    addNode(G,newNode("Kendal"));
    addNode(G,newNode("Semarang"));
    addNode(G,newNode("Demak"));
    addNode(G,newNode("Kudus"));
    addNode(G,newNode("Rembang"));
    addNode(G,newNode("Slawi"));
    addNode(G,newNode("Purwokerto"));
    addNode(G,newNode("Cilacap"));
    addNode(G,newNode("Kroya"));
    addNode(G,newNode("Kebumen"));
    addNode(G,newNode("Purbalingga"));
    addNode(G,newNode("Banjarnegara"));
    addNode(G,newNode("Purworejo"));
    addNode(G,newNode("Wonosobo"));
    addNode(G,newNode("Magelang"));
    addNode(G,newNode("Boyolali"));
    addNode(G,newNode("Klaten"));
    addNode(G,newNode("Salatiga"));
    addNode(G,newNode("Temanggung"));
    addNode(G,newNode("Solo"));
    addNode(G,newNode("Purwodadi"));
    addNode(G,newNode("Blora"));
    addNode(G,newNode("Sragen"));
    addNode(G,newNode("Sukoharjo"));
    addNode(G,newNode("Wonogiri"));
    addEdge(G,"Brebes","Tegal");
    addEdge(G,"Brebes","Slawi");
    addEdge(G,"Tegal","Slawi");
    addEdge(G,"Tegal","Pemalang");
    addEdge(G,"Pemalang","Pekalongan");
    addEdge(G,"Pemalang","Purbalingga");
    addEdge(G,"Slawi","Purwokerto");
    addEdge(G,"Purwokerto","Cilacap");
    addEdge(G,"Cilacap","Kroya");
    addEdge(G,"Kroya","Kebumen");
    addEdge(G,"Purwokerto","Kroya");
    addEdge(G,"Purwokerto","Kebumen");
    addEdge(G,"Purwokerto","Purbalingga");
    addEdge(G,"Purbalingga","Banjarnegara");
    addEdge(G,"Banjarnegara","Wonosobo");
    addEdge(G,"Wonosobo","Magelang");
    addEdge(G,"Wonosobo","Temanggung");
    addEdge(G,"Kebumen","Purworejo");
    addEdge(G,"Purworejo","Magelang");
    addEdge(G,"Magelang","Temanggung");
    addEdge(G,"Magelang","Boyolali");
    addEdge(G,"Boyolali","Klaten");
    addEdge(G,"Boyolali","Salatiga");
    addEdge(G,"Temanggung","Salatiga");
    addEdge(G,"Temanggung","Kendal");
    addEdge(G,"Pekalongan","Kendal");
    addEdge(G,"Kendal","Semarang");
    addEdge(G,"Salatiga","Semarang");
    addEdge(G,"Demak","Semarang");
    addEdge(G,"Demak","Kudus");
    addEdge(G,"Purwodadi","Kudus");
    addEdge(G,"Demak","Purwodadi");
    addEdge(G,"Rembang","Kudus");
    addEdge(G,"Rembang","Blora");
    addEdge(G,"Purwodadi","Blora");
    addEdge(G,"Purwodadi","Solo");
    addEdge(G,"Boyolali","Solo");
    addEdge(G,"Sragen","Solo");
    addEdge(G,"Sragen","Blora");
    addEdge(G,"Sukoharjo","Solo");
    addEdge(G,"Wonogiri","Sukoharjo");
}
