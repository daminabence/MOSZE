#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <numeric>
#include <iomanip>
#include "tablazatosztaly.h"

using namespace std;

tablazatOsztaly::tablazatOsztaly() {
    sorMeret(2);
    oszlopMeret(2);
    oszlopHosszok.resize(2);
    oszlopTeljesMeret = 0;
}

int tablazatOsztaly::sorokSzama() {
    return tabla.size();
}

int tablazatOsztaly::oszlopokSzama() {
    return tabla[0].size();
}

std::string tablazatOsztaly::cellaErtek(int i, int j) {
    return tabla[i][j];
}

void tablazatOsztaly::tablaKiir() {
    for (int i = 1; i < sorokSzama(); i++) {
        tabla[i][0] = to_string(i);
    }
    for (int j = 1; j < oszlopokSzama(); j++) {
        tabla[0][j] = (char(64 + j));
    }
    oszlopHosszok.resize(oszlopokSzama());
    int maxMeret = 1;
    for (int i = 0; i < oszlopokSzama(); i++) {
        maxMeret = 1;
        for (int j = 1; j < sorokSzama(); j++) {
            if (tabla[j][i].size() > maxMeret) maxMeret = tabla[j][i].size();
        }
        oszlopHosszok[i] = maxMeret;
    }
    oszlopTeljesMeret = accumulate(oszlopHosszok.begin(), oszlopHosszok.end(), 0);
    cout << endl << string(oszlopTeljesMeret + oszlopHosszok.size() + 1, '-') << endl;
    for (int i = 0; i < sorokSzama(); i++) {
        for (int j = 0; j < oszlopokSzama(); j++) {
            cout << "|" << left << setw(oszlopHosszok[j]) << tabla[i][j];

        }
        cout << "|" << endl << string(oszlopTeljesMeret + oszlopHosszok.size() + 1, '-') << endl;
    }
}

void tablazatOsztaly::sorMeret(int meret) {
    tabla.resize(meret);
}

void tablazatOsztaly::oszlopMeret(int meret) {
    for (int i = 0; i < sorokSzama(); i++) {
        tabla[i].resize(meret);
    }
}

void tablazatOsztaly::sorTorles(int hely) {
    hely--;
    for (int i = hely; i < tabla.size() - 1; i++) {
        for (int j = 0; j < tabla[0].size(); j++) {
            tabla[i][j] = tabla[i + 1][j];
        }
    }
    tabla.resize(sorokSzama() - 1);
}

void tablazatOsztaly::oszlopTorles(int hely) {
    for (int i = 0; i < tabla.size(); i++) {
        for (int j = hely; j < tabla[tabla.size() - 1].size() - 1; j++) {
            tabla[i][j] = tabla[i][j + 1];
        }
        tabla[i].resize(tabla[i].size() - 1);
    }
}

void tablazatOsztaly::cellaBeallit(int sor, int oszlop, std::string tartalom) {
    tabla[sor][oszlop] = tartalom;
}

void tablazatOsztaly::sorBeszur(int hely, int db) {
    vector<std::string> uresVektor;
    uresVektor.resize(tabla[0].size());
    auto elemHelye = tabla.begin() + hely;
    tabla.insert(elemHelye, db, uresVektor);
}

void tablazatOsztaly::oszlopBeszur(int hely, int db) {
    int meret = tabla[0].size() + db;
    for (int i = 0; i < tabla.size(); i++) {
        auto elemHelye = tabla[i].begin() + hely;
        tabla[i].insert(elemHelye, db, "");
    }
}