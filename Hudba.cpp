// Auta.cpp : Defines the entry point for the application.
//

#include "Hudba.h"

#include <stdio.h>
#include <ctype.h>              // tolower
#include <stdlib.h>				// system

#include "HudbaDB.h"

struct t_hudba* prvni = NULL; // globalni ukazatel na prvni auto

void OnAdd()
{
	char my_name[ZNACKA_SIZE];
	char my_album[ZNACKA_SIZE];
	int my_year;

	printf("\nInterpret : ");         // dotazeme se na polozky
	scanf_s("%s", my_name, ZNACKA_SIZE);
	while (getchar() != '\n');
	printf("\nNazev alba : ");
	scanf_s("%s", my_album, ZNACKA_SIZE);
	while (getchar() != '\n');
	printf("\nRok : ");
	scanf_s("%d", &my_year);
	while (getchar() != '\n');
	add(my_name, my_year, my_album, &prvni);         // volame pridavaci funkci
}

void OnDel()
{
	int my_year;

	printf("\nRok : ");
	scanf_s("%d", &my_year);
	while (getchar() != '\n');
	del(my_year, &prvni);         // volame mazaci funkci
}

void ShowAlba()
{
	char pismeno[ZNACKA_SIZE];


	struct t_hudba* aktAlbum = prvni; // ukazatel na aktualni auto
	printf("\n\n");
	printf("Zadej od jakeho pismena chces vytisknout interprety: ");
	scanf_s("%c", &pismeno);
	while (getchar() != '\n');

	while (aktAlbum) // prochazeni seznamu aktAlbum
	{
		if (strcmp(aktAlbum->interpret, pismeno) > 0 || (aktAlbum->interpret)[0] == pismeno[0])
		{
			printf("%d: %s - %s\n", aktAlbum->rok, aktAlbum->interpret, aktAlbum->nazev_alba); // tisk radku
		}
		aktAlbum = aktAlbum->dalsi; // posun na dalsi auto
	}
	getchar();
}


int main()
{
	char  cmd;

	do
	{
		system("cls");		// smaze obrazovku
		printf("A: Pridat     ");
		printf("D: Smazat     ");
		printf("P: Tisk     ");
		printf("Q: Konec\n\n");

		cmd = tolower(getchar());
		while (getchar() != '\n');

		switch (cmd)
		{
		case 'a':
			OnAdd();					// volame pridani
			break;
		case 'd':
			OnDel();					// volame mazani
			break;
		case 'p':
			ShowAlba();
			break;
		}
	} while (cmd != 'q');     // koncime az pri Q
	return 0;
}


