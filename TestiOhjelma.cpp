

#include "CommonHederi.h"
#include "Apuluokka.h"
#include "SanaKokoelma.h"


void main (void)
{
	Apuluokka* apuluokka = new Apuluokka();
	
	apuluokka->PiirraHirttoKuva(); // Piirtää uhkauksen 
	apuluokka->PiirraAloitusRuutu(); // Aloittaa pelin

	getchar();getchar();
	
	delete apuluokka;
}