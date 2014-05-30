
#include "Apuluokka.h"
#include "SanaKokoelma.h"
#include <windows.h>  // Konsolihypyt

Apuluokka::Apuluokka(void) // Konstruktori
{
	samaValittu=false;
	merkattu=0;
	peliOnVoitettu=false;
	peliPaattyiTasan=false;
	osumaTaulukko=nullptr;
}


Apuluokka::~Apuluokka(void) // Destruktori
{
	if(osumaTaulukko!=nullptr)  // NULL with hangman, !NULL with ticTac
	{
		for(int i = 0; i < 3; ++i) // Tuhoa dynaaminen taulukko heapist‰
			delete[] osumaTaulukko[i];

		delete[] osumaTaulukko;

	}
}


void Apuluokka::AllokoiTilaTaulukolle(void)
{
	// Allokoi heapista tilan dynaamiselle, 2-ulotteiselle integer arraylle
	// Hederiss‰ : osumaTaulukko**

	osumaTaulukko = new int*[3];

	for(int i = 0; i < 3; ++i)
		osumaTaulukko[i] = new int[3];


	// OR -->

	//osumaTaulukko	 = new int* [3];
	//osumaTaulukko[0] = new int [3];
	//osumaTaulukko[1] = new int [3];
	//osumaTaulukko[2] = new int [3];

	
	// Alustus -->
	osumaTaulukko[0][0]=0;
	osumaTaulukko[0][1]=0;
	osumaTaulukko[0][2]=0;
	osumaTaulukko[1][0]=0;
	osumaTaulukko[1][1]=0;
	osumaTaulukko[1][2]=0;
	osumaTaulukko[2][0]=0;
	osumaTaulukko[2][1]=0;
	osumaTaulukko[2][2]=0;
}


void Apuluokka::PiirraAloitusRuutu(void) // Hirsipuun aloituskent‰n piirto
{
	pause();
	system("CLS");
	cout<<"\n\nArvaa kirjaimia : \n";
	int luku;
	ArvoLuku(&luku);
	KysySanaa(luku);
}


void Apuluokka::PiirraPuhdasKentta() // Ristinollan aloituskent‰n piirto
{
	system("CLS");
	gotoxy(3,3);
	cout<<"-------";
	gotoxy(3,4);
	cout<<"| | | |";
	gotoxy(3,5);
	cout<<"-------";
	gotoxy(3,6);
	cout<<"| | | |";
	gotoxy(3,7);
	cout<<"-------";
	gotoxy(3,8);
	cout<<"| | | |";
	gotoxy(3,9);
	cout<<"-------";
	gotoxy(1,11);
}


void Apuluokka::PiirraAloitusRuutuXO(void)  // Piirt‰‰ tyhj‰n kent‰n ja kysyy kumpi aloittaa
{
	PiirraPuhdasKentta();

	gotoxy(0,0);
	cout<<"Peli alkaa :";
	

	gotoxy(1,11);

	cout<<"Kumpi aloittaa ? (1= "<<pelaaja1<< " 2= "<<pelaaja2<<") " ;

	char pelaaja;

	do
	{
		cin>>pelaaja;
	}
	while(pelaaja ==1 || pelaaja ==2);



	if(pelaaja =='1')
	{
		cout<<"\n\nPelaaja : "<<pelaaja1<<" aloittaa (x) !";

			pause();
			pelaajanVuoro=1;
			PeliVuoro(1,pelaaja1);

	}

	else
	{
		cout<<"\n\nPelaaja : "<<pelaaja2<<" aloittaa (o) !";
		pelaajanVuoro=2;
		pause();

		PeliVuoro(1,pelaaja2);
	}

}


void Apuluokka::AloitaPeli(void) // Alkuohjeistus
{
	system("CLS");
	cout<< "Tama on ristinolla peli (kaksinpelina)\n\n\n";

	cout<<"Anna pelaajan1 nimi : ";
	getline(cin,pelaaja1);
	cout<<endl<<endl;
	cout<<"Anna pelaajan2 nimi : ";
	getline(cin,pelaaja2);
	PiirraAloitusRuutuXO();
}


void Apuluokka::PeliVuoro(int vuoro,string pelaaja)  // Eka pelivuoro
{

	PiirraPuhdasKentta();

	gotoxy(1,1);
	cout << "Pelaajan " <<pelaaja <<" vuoro";

	gotoxy(1,11);

	cout<<"Anna ruutu (a-c sarake), (1-3 ruutu) : "; 

	string mihin;
	char merkki;
	cin>> mihin;

	if(pelaaja==pelaaja1)
		merkki = 'x';
	else
		merkki = 'o';

	PiirraTietty(merkki,mihin);

}


void Apuluokka::PiirraMerkki(int rivi,int sarake, char merkki) // Piirt‰‰ ristinollan tietyn merkin jos sit‰ ei ole jo merkattu
{
	// x on 120, o on 111
	if(sarake==1&&rivi==1) // a1
	{
		if(osumaTaulukko[0][0]==0)
		{
			gotoxy(sarake+3,rivi+3); 
			putchar(merkki);
			osumaTaulukko[0][0]=(char)merkki; // Kirjoita merkki taulukkoon
			samaValittu=false;   // Resetoi samaValittu flagin
			merkattu++; // Inkrementoi merkattuja ruutuja muuttujaa
		}

		else
		{

			cout<<" Already hit";
			PalaaValitsemaanRuutu(); // Jo merkattu positio
			samaValittu=true;
		}
		
	}

	if(sarake==1&&rivi==2) // a2
	{
		if(osumaTaulukko[0][1]==0)
		{
			gotoxy(sarake+3,rivi+4);
			putchar(merkki);
			osumaTaulukko[0][1]=(char)merkki;
			samaValittu=false;
			merkattu++;
		}

		else
		{

			cout<<" Already hit";
			PalaaValitsemaanRuutu();
			samaValittu=true;
		}
	}

	if(sarake==1&&rivi==3) // a3
	{
		if(osumaTaulukko[0][2]==0)
		{
			gotoxy(sarake+3,rivi+5);
			putchar(merkki);
			osumaTaulukko[0][2]=(char)merkki;
			samaValittu=false;
			merkattu++;
		}

		else
		{

			cout<<" Already hit";
			PalaaValitsemaanRuutu();
			samaValittu=true;
		}
	}

	if(sarake==2&&rivi==1) // b1
	{
		if(osumaTaulukko[1][0]==0)
		{
			gotoxy(sarake+4,rivi+3);
			putchar(merkki);
			osumaTaulukko[1][0]=(char)merkki;
			samaValittu=false;
			merkattu++;
		}

		else
		{

			cout<<" Already hit";
			PalaaValitsemaanRuutu();
			samaValittu=true;
		}
	}

	if(sarake==2&&rivi==2) // b2
	{
		if(osumaTaulukko[1][1]==0)
		{
			gotoxy(sarake+4,rivi+4);
			putchar(merkki);
			osumaTaulukko[1][1]=(char)merkki;
			samaValittu=false;
			merkattu++;
		}

		else
		{

			cout<<" Already hit";
			PalaaValitsemaanRuutu();
			samaValittu=true;
		}
	}

	if(sarake==2&&rivi==3) // b3
	{
		if(osumaTaulukko[1][2]==0)
		{
			gotoxy(sarake+4,rivi+5);
			putchar(merkki);
			osumaTaulukko[1][2]=(char)merkki;
			samaValittu=false;
			merkattu++;
		}

		else
		{

			cout<<" Already hit";
			PalaaValitsemaanRuutu();
			samaValittu=true;
		}
	}

	if(sarake==3&&rivi==1) // c1
	{
		if(osumaTaulukko[2][0]==0)
		{
			gotoxy(sarake+5,rivi+3);
			putchar(merkki);
			osumaTaulukko[2][0]=(char)merkki;
			samaValittu=false;
			merkattu++;
		}

		else
		{

			cout<<" Already hit";
			PalaaValitsemaanRuutu();
			samaValittu=true;
		}
	}

	if(sarake==3&&rivi==2) // c2
	{
		if(osumaTaulukko[2][1]==0)
		{
			gotoxy(sarake+5,rivi+4);
			putchar(merkki);
			osumaTaulukko[2][1]=(char)merkki;
			samaValittu=false;
			merkattu++;
		}

		else
		{

			cout<<" Already hit";
			PalaaValitsemaanRuutu();
			samaValittu=true;
		}
	}

	if(sarake==3&&rivi==3) // c3
	{
		if(osumaTaulukko[2][2]==0)
		{
			gotoxy(sarake+5,rivi+5);
			putchar(merkki);
			osumaTaulukko[2][2]=(char)merkki;
			samaValittu=false;
			merkattu++;
		}

		else
		{
			cout<<" Already hit";
			PalaaValitsemaanRuutu();
			samaValittu=true;
		}
	}
	if(merkattu>4)
		TarkistaVoittoehto(merkattu);
}


void Apuluokka::TarkistaVoittoehto(int merkattuja) // Tarkistaa ristinollan voittoehdot
{

	// Voittoehto 1 
	// ristiin laskeva
	if(osumaTaulukko[0][0] == 120 && osumaTaulukko[1][1]== 120 && osumaTaulukko[2][2]== 120)
	{
		gotoxy(2,15);
		cout<< pelaaja1  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	if(osumaTaulukko[0][0] == 111 && osumaTaulukko[1][1]== 111 && osumaTaulukko[2][2]== 111)
	{
		gotoxy(2,15);
		cout<< pelaaja2  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	// Voittoehto 2 
	// ristiin nouseva
	if(osumaTaulukko[0][2] == 120 && osumaTaulukko[1][1]== 120 && osumaTaulukko[2][0]== 120)
	{
		gotoxy(2,15);
		cout<< pelaaja1  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	if(osumaTaulukko[0][2] == 111 && osumaTaulukko[1][1]== 111 && osumaTaulukko[2][0]== 111)
	{
		gotoxy(2,15);
		cout<< pelaaja2  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	// Voittoehto 3 
	// laaka keski
	if(osumaTaulukko[0][1] == 120 && osumaTaulukko[1][1]== 120 && osumaTaulukko[2][1]== 120)
	{
		gotoxy(2,15);
		cout<< pelaaja1  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	if(osumaTaulukko[0][1] == 111 && osumaTaulukko[1][1]== 111 && osumaTaulukko[2][1]== 111)
	{
		gotoxy(2,15);
		cout<< pelaaja2  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	// Voittoehto 4 
	// laaka yl‰
	if(osumaTaulukko[0][0] == 120 && osumaTaulukko[1][0]== 120 && osumaTaulukko[2][0]== 120)
	{
		gotoxy(2,15);
		cout<< pelaaja1  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	if(osumaTaulukko[0][0] == 111 && osumaTaulukko[1][0]== 111 && osumaTaulukko[2][0]== 111)
	{
		gotoxy(2,15);
		cout<< pelaaja2  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	// Voittoehto 5 
	// laaka ala
	if(osumaTaulukko[0][2] == 120 && osumaTaulukko[1][2]== 120 && osumaTaulukko[2][2]== 120)
	{
		gotoxy(2,15);
		cout<< pelaaja1  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	if(osumaTaulukko[0][2] == 111 && osumaTaulukko[1][2]== 111 && osumaTaulukko[2][2]== 111)
	{
		gotoxy(2,15);
		cout<< pelaaja2  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}



	// Voittoehto 6 
	if(osumaTaulukko[0][0] == 120 && osumaTaulukko[0][1]== 120 && osumaTaulukko[0][2]== 120)
	{
		gotoxy(2,15);
		cout<< pelaaja1  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	if(osumaTaulukko[0][0] == 111 && osumaTaulukko[0][1]== 111 && osumaTaulukko[0][2]== 111)
	{
		gotoxy(2,15);
		cout<< pelaaja2  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}


	// Voittoehto 7
	if(osumaTaulukko[1][0] == 120 && osumaTaulukko[1][1]== 120 && osumaTaulukko[1][2]== 120)
	{
		gotoxy(2,15);
		cout<< pelaaja1  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	if(osumaTaulukko[1][0] == 111 && osumaTaulukko[1][1]== 111 && osumaTaulukko[1][2]== 111)
	{
		gotoxy(2,15);
		cout<< pelaaja2  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}


	// Voittoehto 8
	if(osumaTaulukko[2][0] == 120 && osumaTaulukko[2][1]== 120 && osumaTaulukko[2][2]== 120)
	{
		gotoxy(2,15);
		cout<< pelaaja1  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	if(osumaTaulukko[2][0] == 111 && osumaTaulukko[2][1]== 111 && osumaTaulukko[2][2]== 111)
	{
		gotoxy(2,15);
		cout<< pelaaja2  <<" voitti pelin !!!\n"; 
		peliOnVoitettu=true;
		pause();
	}

	if (merkattuja ==9) // Tasapeli
	{
		
		gotoxy(2,15);
		cout<< "Tasapeli !!!\n";
		peliPaattyiTasan=true;
		pause();
	}

}


void Apuluokka::PalaaValitsemaanRuutu() // Palauta alkutila jotta voidaan valita joku toinen positio
{
		gotoxy(1,11);
		cout<<"															";
		gotoxy(1,11);
		cout<<"Anna ruutu (a-c sarake), (1-3 ruutu) : "; 
}


void Apuluokka::AloitaPeliCyclit() // Kutsutaan mainista hoitamaan pelin vuorotteluluupit
{
	//cout<<"DebugPoint";
	while(1)
	{
		if(pelaajanVuoro==1 && !peliOnVoitettu && !peliPaattyiTasan)
		{
			gotoxy(1,1);
			cout<<"															";
			gotoxy(1,1);
			cout << "Pelaajan " <<pelaaja1 <<" vuoro";
			
			gotoxy(1,11);
			cout<<"															";
			gotoxy(1,11);
			cout<<"Anna ruutu (a-c sarake), (1-3 ruutu) : "; 
		
			string mihin;
			char merkki;
			cin>> mihin;

			if(pelaajanVuoro==1)
				merkki = 'x';		// Pelaajan1 vuoro
			else
				merkki = 'o';		// Pelaajan2 vuoro

			PiirraTietty(merkki,mihin);

			if(!samaValittu) // Huomioi jos yritet‰‰n antaa jo varattu positio, vuoro ei vaihdu
				pelaajanVuoro=2;
		}
			
		if(pelaajanVuoro==2 && !peliOnVoitettu && !peliPaattyiTasan)
		{
			gotoxy(1,1);
			cout<<"															";
			gotoxy(1,1);
			cout << "Pelaajan " <<pelaaja2 <<" vuoro";

			gotoxy(1,11);
			cout<<"															";
			gotoxy(1,11);
			cout<<"Anna ruutu (a-c sarake), (1-3 ruutu) : "; 

			string mihin;
			char merkki;
			cin>> mihin;

			if(pelaajanVuoro==1)
				merkki = 'x';
			else
				merkki = 'o';

			PiirraTietty(merkki,mihin);

			if(!samaValittu)
				pelaajanVuoro=1;
		}

		if(peliOnVoitettu || peliPaattyiTasan )
			break;
	}
}


void Apuluokka::PiirraTietty(char merkki, string mihin) // Erottelee rivin, sarakkeen ja merkin
{
	string Stringinosa1=mihin.substr(0,1);
	string Stringinosa2=mihin.substr(1,1);

	int rivi=stoi(Stringinosa2);
	int sarake;

	if(Stringinosa1=="a" || Stringinosa1=="A")
		sarake=1;

	else if(Stringinosa1=="b" || Stringinosa1=="B")
		sarake=2;

	else if(Stringinosa1=="c" || Stringinosa1=="C")
		sarake=3;

	else
		cout<<"Error!";

	PiirraMerkki(rivi,sarake,merkki);
}


void Apuluokka::KysySanaa(int which) // Hangmanin p‰‰funktio, which valitsee sanan
{
	SanaKokoelma* kokoelma = new SanaKokoelma();
	string sana=kokoelma->sanavektori[which];
	char kirjain;
	int oikeita=0,arvauksia=0;
	bool gameWon=false;
	int sarake=16;
	string muodostettuSana;


	vector<char> myVector; // Vektori jo arvatuille kirjaimille



	std::size_t found; // String search palauttaa

	cin.clear(); // Putsaa input stream
	//cin.ignore(256,'\n');

	// Muodostetun sanan alustus alaviivoina
	for(unsigned int i=0;i<sana.length();i++)
		muodostettuSana.append("_");

	system("CLS");

	gotoxy(1,0);
	cout<< muodostettuSana;

	gotoxy(0,2);
	cout<<"Arvaa kirjain : ";

	cin>>kirjain;
	



	while(arvauksia != 7) // Kunnes Hirttosilmukka valmis
	{
		gotoxy(1,0);

		for(unsigned int i=0;i<sana.length();i++) // Etsi kirjainta
		{
			if(sana.at(i)==kirjain)
			{
				oikeita++;
			
				muodostettuSana.at(i)=kirjain; // Muodosta uusi viivoitus mukanaan oikein arvatut kirjaimet

				gotoxy(1,0);
				cout<< muodostettuSana; // Kirjoita uudelleen oikea kirjain mukana
				
			}
		}

		if(oikeita==0) // Kirjainta ei lˆytynyt
		{
			bool charFound=false;

			for each (char MyElement in myVector) // Kahdesta samasta v‰‰r‰st‰ ei rokoteta (haetaan vektorista jo annettua kirjainta)
			{
				if(MyElement==kirjain)
					charFound=true;
			}

			if(!charFound) // Kirjainta ei syˆtetty aikaisemmin, syˆtet‰‰n se vektoriin ja piirret‰‰n hirtt‰ "pidemm‰lle"
			{
				myVector.push_back(kirjain);
				DrawError(arvauksia+1);
				arvauksia++;
			}
		}

		oikeita=0; // Reset
		gotoxy(sarake+=2,2); // Palauttaa merkin kysynt‰‰n kursorin (kaksi merkki‰ jo annetun j‰lkeen)

		found = muodostettuSana.find("_");

		if(found >100) // Merkkijono t‰ytetty oikein koskei lˆytynyt en‰‰ alaviivoja
		{
			gameWon=true;	// Flag up
			break;			// Break from while
		}


		if(arvauksia != 7)
			cin>>kirjain;  // Kysy uudestaan kirjainta

	}

	if(!gameWon) // Hirress‰ roikutaan
	{
		gotoxy(3,20);
		cout<< "Game over !!!";
	}

	else // Breakin kautta
	{
		gotoxy(3,20);
		cout<< "Game won !!!";
	}

	delete kokoelma;
}


void Apuluokka::PiirraHirttoKuva(void) // Piirret‰‰n mahdollinen, uhkaava lopputulos
{
	system("CLS");

	cout << "This is a hangman game !\n\n";


	string rivi1="		+----+		\n";
	string rivi2="		|/   |		\n";
	string rivi3="		|    O		\n";
	string rivi4="		|   /|\\	\n";
	string rivi5="	        |   / \\	\n";
	string rivi6="	      +-+-+			\n";
	string rivi7="	      |   |			\n";

	cout << rivi1;
	cout << rivi2;
	cout << rivi3;
	cout << rivi4;
	cout << rivi5;
	cout << rivi6;
	cout << rivi7;
	
}


void Apuluokka::DrawError(int which) // Piirr‰ v‰‰rinarvattu puun jatko
{
	cout<<endl<<"\n\n\n\n\n\n";

	switch(which)
	{

		case 1:
		cout<<"	      +-+-+			\n";
		cout<<"	      |   |			\n";
		break;

		case 2:
		cout<<"		|/   		\n";
		cout<<"		|    		\n";
		cout<<"		|   	\n";
		cout<<"	        |   	\n";
		cout<<"	        |   		\n";
		cout<<"	      +-+-+			\n";
		cout<<"	      |   |			\n";
		break;

		case 3:
		cout<<"		+----+		\n";
		cout<<"		|/   		\n";
		cout<<"		|    		\n";
		cout<<"		|   	\n";
		cout<<"	        |   	\n";
		cout<<"	        |   		\n";
		cout<<"	      +-+-+			\n";
		cout<<"	      |   |			\n";
		break;

		case 4:
		cout<<"		+----+		\n";
		cout<<"		|/   |		\n";
		cout<<"		|    		\n";
		cout<<"		|   	\n";
		cout<<"	        |   	\n";
		cout<<"	        |   		\n";
		cout<<"	      +-+-+			\n";
		cout<<"	      |   |			\n";
		break;

		case 5:
		cout<<"		+----+		\n";
		cout<<"		|/   |		\n";
		cout<<"		|    O		\n";
		cout<<"		|   	\n";
		cout<<"	        |   	\n";
		cout<<"	        |   		\n";
		cout<<"	      +-+-+			\n";
		cout<<"	      |   |			\n";
		break;

		case 6:
		cout<<"		+----+		\n";
		cout<<"		|/   |		\n";
		cout<<"		|    O		\n";
		cout<<"		|   /|\\	\n";
		cout<<"	        |   	\n";
		cout<<"	        |   		\n";
		cout<<"	      +-+-+			\n";
		cout<<"	      |   |			\n";
		break;

		case 7 :
		cout<<"		+----+		\n";
		cout<<"		|/   |		\n";
		cout<<"		|    O		\n";
		cout<<"		|   /|\\	\n";
		cout<<"	        |   / \\	\n";
		cout<<"	        |   		\n";
		cout<<"	      +-+-+			\n";
		cout<<"	      |   |			\n";
		break;

	}

	gotoxy(0,0);	
}


void Apuluokka::pause() // System pause funktio
{
  cout << endl << "Press enter to continue...";
  getchar();
}


void Apuluokka::ArvoLuku(int* luku) // Haetaan satunnaisluku osa 1
{
	srand( time(0) ); // setting the seed value
	*luku=GetRandomNumber(1,10);
}


int Apuluokka::GetRandomNumber(int nLow, int nHigh) // Haetaan satunnaisluku osa 2
{
	return (rand() % (nHigh - nLow + 1)) + nLow;
}


void Apuluokka::gotoxy ( int column, int line )  // Liikutetaan kursoria konsolissa
{
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
}