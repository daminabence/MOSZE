#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tablazatosztaly.h"

using namespace std;

int main() {
    tablazatOsztaly tablazat;
    tablazat.tablaKiir();
    bool kilepes = false;
    string bevitel[5], beviteliMezo;
    int i = 0;
    while (!kilepes) {
        cout << "\nParancs: "; getline(cin, beviteliMezo);
        string tartalom = beviteliMezo; int space_db = 0, ii = 0; char betu;
        for (char betu : beviteliMezo) {
            if (betu == ' ') space_db++;
        }
        if (space_db > 4) {
            space_db = 0;
            while (space_db < 5) {
                betu = beviteliMezo[ii];
                if (betu == ' ') space_db++;
                if (space_db >= 5) beviteliMezo.erase(ii, 200);
                ii++;
            }
        }
        i = 0;
        for (int i = 0; i < 5; i++) {
            bevitel[i] = "";
        }
        for (char betu : beviteliMezo) {
            if (betu != ' ') {
                bevitel[i] += betu;
            }
            else {
                i++;
            }
        }
        if (bevitel[0] == "edit" and bevitel[1] != "") {
            string mezo = bevitel[1];
            int oszlop = mezo[0] - 96;
            mezo.erase(0, 1);
            int sor = stoi(mezo);
            int spaceDb = 0;
            char betu;
            while (spaceDb < 2) {
                betu = tartalom[0];
                if (betu == ' ') spaceDb++;
                tartalom.erase(0, 1);
            }
            if (sor > 0 and sor < tablazat.sorokSzama() and oszlop > 0 and oszlop < tablazat.oszlopokSzama()) {
                tablazat.cellaBeallit(sor, oszlop, tartalom);
            }
            else { cout << "Ilyen cella nem letezik" << endl; }
        }
        else if (bevitel[0] == "add" and bevitel[1] != "" and bevitel[2] != "" and bevitel[3] == "" and bevitel[4] == "") {
            int db = stoi(bevitel[1]);
            if (bevitel[2] == "rows") {
                tablazat.sorMeret(tablazat.sorokSzama() + db);
                tablazat.oszlopMeret(tablazat.oszlopokSzama());
            }
            else if (bevitel[2] == "cols") {
                tablazat.oszlopMeret(tablazat.oszlopokSzama() + db);
            }
            else { cout << "Ilyen parancs nem letezik" << endl; }
        }
        else if (bevitel[0] == "delete" and bevitel[1] != "" and bevitel[2] == "" and bevitel[3] == "" and bevitel[4] == "") {
            string mezoNev = bevitel[1];
            int hely;
            if (isdigit(mezoNev[0])) {
                hely = stoi(mezoNev) + 1;
                if (hely <= tablazat.sorokSzama() and tablazat.sorokSzama() > 2) {
                    tablazat.sorTorles(hely);
                }
                else {
                    cout << "Ez az sor nem torolheto" << endl;
                }
            }
            else if (isalpha(mezoNev[0])) {
                char kar = tolower(mezoNev[0]);
                hely = kar - 'a' + 1;
                if (hely < tablazat.oszlopokSzama() and tablazat.oszlopokSzama() > 2) {
                    tablazat.oszlopTorles(hely);
                }
                else {
                    cout << "Ez az oszlop nem torolheto" << endl;
                }
            }
        }
        else if (bevitel[0] == "insert" and bevitel[1] != "" and bevitel[2] != "" and bevitel[3] != "" and bevitel[4] != "") {
            if (isdigit(bevitel[1][0])) {
                int hely;
                char kar = bevitel[4][0];
                kar = tolower(kar);
                if (isalpha(kar)) {
                    hely = bevitel[4][0] - 96;
                }
                else if (isdigit(kar)) {
                    hely = stoi(bevitel[4]);
                }
                int db = stoi(bevitel[1]);
                if (bevitel[2] == "rows") {
                    if (bevitel[3] == "after") {
                        tablazat.sorBeszur(hely + 1, db);
                    }
                    else if (bevitel[3] == "before") {
                        tablazat.sorBeszur(hely, db);
                    }
                    else { cout << "Ilyen parancs nem letezik" << endl; }
                }
                if (bevitel[2] == "cols") {
                    if (bevitel[3] == "after") {
                        tablazat.oszlopBeszur(hely + 1, db);
                    }
                    else if (bevitel[3] == "before") {
                        tablazat.oszlopBeszur(hely, db);
                    }
                    else { cout << "Ilyen parancs nem letezik" << endl; }
                }
            }
        }
        else if (bevitel[0] == "exit" and bevitel[1] == "" and bevitel[2] == "" and bevitel[3] == "" and bevitel[4] == "") {
            kilepes = true;
        }
        else if ((bevitel[0].substr(bevitel[0].size() - 4)) == ".csv") {
            char elvalasztoChar = ';';
            if (bevitel[1] == "-sep") {
                elvalasztoChar = bevitel[2][0];
            }
            fstream tablaFajl;
            tablaFajl.open(bevitel[0], ios::in);
            if (!tablaFajl) {
                 cout << "A fajl nem letezik";
            }
            else {
                 string sor,elem;
                 tablazat.sorMeret(1);
                 tablazat.oszlopMeret(1);
                 int sorMeret=1, oszlopMeret=1, temp=1, i=1, j=1;
                 while (getline(tablaFajl, sor)) {
                     stringstream ss(sor);
                     while (getline(ss, elem, elvalasztoChar)) {
                         temp++;
                     }
                     if (temp > oszlopMeret) oszlopMeret = temp;
                     temp = 0;
                     sorMeret++;
                 } 
                 tablazat.sorMeret(sorMeret);
                 tablazat.oszlopMeret(oszlopMeret);
                 tablaFajl.close();
                 tablaFajl.open(bevitel[0], ios::in);
                 while (getline(tablaFajl, sor)) {
                     stringstream ss(sor);
                     while (getline(ss, elem, elvalasztoChar)) {
                         tablazat.cellaBeallit(i, j, elem);
                         j++;
                     }
                     j = 1;
                     i++;
                 }
            }
            tablaFajl.close();
        }
        else if (bevitel[0] == "save" and (bevitel[1].substr(bevitel[1].size() - 4)) == ".csv") {
            string fajlNev = bevitel[1];
            char elvalasztoChar = ';';
            if (bevitel[2] == "-sep") {
                elvalasztoChar = bevitel[3][0];
            }
            ofstream TablaKiir;
            TablaKiir.open(fajlNev);
            int i = 1,  j = 1;
            for (i = 1; i < tablazat.oszlopokSzama(); i++) {
                for (j = 1; j < tablazat.sorokSzama(); j++) {
                    TablaKiir << tablazat.cellaErtek(i, j) << elvalasztoChar;
                }
                TablaKiir << endl;
            }
            TablaKiir.close();
        }
        else {
            cout << "Ilyen parancs nem letezik\n";
        }
        cout << endl;
        tablazat.tablaKiir();
    }
    return 0;
}
