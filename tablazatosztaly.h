#pragma once
#ifndef TABLAZATOSZTALY_H
#define TABLAZATOSZTALY_H

class tablazatOsztaly {
private:
	std::vector<std::vector<std::string>> tabla;
	std::vector<int> oszlopHosszok;
	int oszlopTeljesMeret;
public:
	tablazatOsztaly();
	int sorokSzama();
	int oszlopokSzama();
	std::string cellaErtek(int i, int j);
	void tablaKiir();
	void sorMeret(int meret);
	void oszlopMeret(int meret);
	void sorTorles(int hely);
	void oszlopTorles(int hely);
	void cellaBeallit(int sor, int oszlop, std::string tartalom);
	void sorBeszur(int hely, int db);
	void oszlopBeszur(int hely, int db);
};

#endif // !TABLAZATOSZTALY_H

