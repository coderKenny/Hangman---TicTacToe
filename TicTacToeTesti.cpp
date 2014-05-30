
#include "CommonHederi.h"
#include "Apuluokka.h"
#include "SanaKokoelma.h"


void main (void)
{
	Apuluokka* apuluokka = new Apuluokka();
	
	apuluokka->AllokoiTilaTaulukolle(); // Could have been placed in default/custom constructor too !
	apuluokka->AloitaPeli();

	if(apuluokka->pelaajanVuoro==1) // Eka vuoronvaihto
		apuluokka->pelaajanVuoro=2;
	else
		apuluokka->pelaajanVuoro=1;


	apuluokka->AloitaPeliCyclit(); // Hoitaa vuoronvaihdot tästä eteenpäin

	getchar();
	
	delete apuluokka;
}