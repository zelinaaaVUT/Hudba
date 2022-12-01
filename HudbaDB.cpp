#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HudbaDB.h"

void add(char* interpret, int rok, char* nazev_alba, struct t_hudba** uk_prvni) // pridani auta
{
	struct t_hudba* noveAlbum; // ukazatel pro nove vkladane auto
	struct t_hudba* aktAlbum; // ukazatel na aktualni auto

	// alokace dynamicke promenne
	noveAlbum = (struct t_hudba*)malloc(sizeof(struct t_hudba));

	strcpy_s(noveAlbum->interpret, ZNACKA_SIZE, interpret); // naplneni struktury
	noveAlbum->rok = rok;
	strcpy_s(noveAlbum->nazev_alba, ZNACKA_SIZE, nazev_alba);
	noveAlbum->dalsi = NULL;

	if (*uk_prvni == NULL) // linearni seznam je prazdny
	{
		*uk_prvni = noveAlbum;
		return;
	}
	else if (strcmp(noveAlbum->nazev_alba,(*uk_prvni)->nazev_alba) < 0) // vlozime na zacatek else if (noveAlbum->rok < (*uk_prvni)->rok)
	{
		noveAlbum->dalsi = *uk_prvni;
		*uk_prvni = noveAlbum;
		return;
	}

	aktAlbum = *uk_prvni;
	while (aktAlbum) // prochazeni seznamu
	{
		if (aktAlbum->dalsi == NULL) // jsme na poslednim aute
		{
			aktAlbum->dalsi = noveAlbum; // pridavame na konec
			return;
		}
		else if (strcmp(noveAlbum->nazev_alba,aktAlbum->dalsi->nazev_alba) < 0)
		{
			noveAlbum->dalsi = aktAlbum->dalsi; // vlozime za aktAuto
			aktAlbum->dalsi = noveAlbum;
			return;
		}
		aktAlbum = aktAlbum->dalsi; // posun na dalsi auto
	}
}

void del(int rok, struct t_hudba** uk_prvni)
{
	struct t_hudba* aktAlbum;

	while (*uk_prvni && (*uk_prvni)->rok == rok)
	{
		struct t_hudba* newPrvni = (*uk_prvni)->dalsi;
		free(*uk_prvni);  // uvolneni auta z pameti
		*uk_prvni = newPrvni;
	}

	aktAlbum = *uk_prvni;
	while (aktAlbum && aktAlbum->dalsi) // prochazeni seznamu
	{
		if (aktAlbum->dalsi->rok == rok) // auto je ke smazani
		{
			struct t_hudba* newDalsi = aktAlbum->dalsi->dalsi;
			free(aktAlbum->dalsi);  // uvolneni auta z pameti
			aktAlbum->dalsi = newDalsi;
		}
		aktAlbum = aktAlbum->dalsi; // posun na dalsi auto
	}
}