#include "graph.h"

#include <iostream>

using namespace std;
int main()
{
    Graph G;
    createGraph(G);
    adrNode P;
    infotype info1;
    infotype info;
    int totalDegree;
    int totalInput;

    insertManualNode(G);

    bool runProgram = true;
    while(runProgram) {
        int menu = chooseMenu();
        if (menu == 1){
            clearScreen();
            cout << "Menu 1 : Menambahkan Kota" << endl;
            cout << "=================================================" << endl;
            cout << "Jumlah kota: ";cin >> totalInput;
            for (int i = 0; i < totalInput; i++){
                cout << "Masukkan Nama Kota ke-"<< i+1<< ": ";cin >> info;
                addNode(G,newNode(info));
            }
            cout << "Kota berhasil ditambahkan" << endl;
        }else if (menu == 2){
            clearScreen();
            cout << "Menu 2 : Menambahkan Hubungan Antar Kota" << endl;
            cout << "=================================================" << endl;
            cout << "=> Kota yang tersedia: " << endl;
            printCities(G);
            cout << "Masukkan kota yang ingin dihubungkan: " << endl;
            cout << "Kota 1: ";cin >> info;
            cout << "Kota 2: ";cin >> info1;
            addEdge(G,info,info1);
            cout << "Kota-kota berhasil dihubungkan" << endl;
        }else if (menu == 3){
            clearScreen();
            cout << "Menu 3 : Menampilkan Hubungan Kota X" << endl;
            cout << "=================================================" << endl;
            printCities(G);
            cout << "Masukkan Kota yang ingin dicari hubungannya: ";cin >> info;
            P = findNode(G,info);
            if (P == NULL) {
                cout << "Kota tidak ditemukan"<<endl;
            }else {
                PrintEdgeOfNode(G,P);
            }
        }else if (menu == 4){
            clearScreen();
            cout << "Menu 4 : Menampilkan Kota yang memiliki hubungan terbanyak" << endl;
            cout << "=================================================" << endl;
            printMostConnection(G);
        }else if (menu == 5){
            clearScreen();
            cout << "Menu 5 : Menampilkan Seluruh Kota" << endl;
            cout << "=================================================" << endl;
            printCities(G);
        }else if (menu == 6){
            clearScreen();
            cout << "Menu 6 : Menampilkan Graph" << endl;
            cout << "=================================================" << endl;
            printGraph(G);
        }else if (menu == 7){
            clearScreen();
            cout << "Menu 7 : Menghapus Kota" << endl;
            cout << "=================================================" << endl;
            printCities(G);
            cout << "Masukkan kota yang ingin dihapus: ";cin >> info;   // Input user terhadap kota yang ingin dihapus
            P = findNode(G,info);                                       // Mencari Element Kota berdasarkan user input
            if (P == NULL) {
                cout << "Kota tidak ditemukan" << endl;                 // jika P tidak ditemukan, kode yang akan dieksekusi
            }else {
                deleteNode(G,P);                                        // menghapus node beserta hubungannya
                cout << "Kota dan hubungannya berhasil dihapus" << endl;
            }
        }else if (menu == 0){
            break;
        }else {
            continue;
        }
        cout << endl;
        runProgram = goBackToMenu();
    }

    return 0;
}

// https://1.bp.blogspot.com/-_tfdrvsqfuQ/U43MF70q2RI/AAAAAAAAADo/eLB0FN0ZsiY/s1600/1.png
