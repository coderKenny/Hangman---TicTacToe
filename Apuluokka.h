
#pragma once

#include "CommonHederi.h"


class Apuluokka
{
public:
	Apuluokka(void);
	~Apuluokka(void);

	void PiirraAloitusRuutu(void);
	void PiirraHirttoKuva(void);
	void pause();
	void ArvoLuku(int* luku);
	int GetRandomNumber(int nLow, int nHigh);
	void KysySanaa(int);

	void DrawError(int);

	void gotoxy ( int column, int line );

	void AloitaPeli(void);
	void PiirraAloitusRuutuXO(void);
	void KysyPelaajat(void);
	void PeliVuoro(int vuoro,string pelaaja);
	void PiirraPuhdasKentta();

	void PiirraTietty(char merkki, string mihin);
	void PiirraMerkki(int sarake,int rivi, char merkki);

	void AloitaPeliCyclit();

	void AllokoiTilaTaulukolle(void);

	void TarkistaVoittoehto(int);

	void PalaaValitsemaanRuutu();
	bool samaValittu;
	int merkattu;
	bool peliOnVoitettu;
	bool peliPaattyiTasan;

	string pelaaja1;
	string pelaaja2;

	int pelaajanVuoro;

	int** osumaTaulukko;

};

