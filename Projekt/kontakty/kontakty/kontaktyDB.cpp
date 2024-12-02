#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kontaktyDB.h"

// Funkce pro přidání kontaktu do seznamu
void add(const char* nick, const char* name, const char* surname,
    const char* phnumber, const char* email, t_kontakt** uk_prvni)
{
    t_kontakt* novyKontakt;  // Ukazatel pro nový kontakt
    t_kontakt* aktKontakt;   // Ukazatel na aktuální kontakt

    // Alokace dynamické paměti pro nový kontakt
    novyKontakt = (t_kontakt*)malloc(sizeof(t_kontakt));

    // Naplnění struktury nového kontaktu
    strcpy_s(novyKontakt->nick, NICK_SIZE, nick);
    strcpy_s(novyKontakt->name, NAME_SIZE, name);
    strcpy_s(novyKontakt->surname, SURNAME_SIZE, surname);
    strcpy_s(novyKontakt->phnumber, PHNUMBER_SIZE, phnumber);
    strcpy_s(novyKontakt->email, EMAIL_SIZE, email);
    novyKontakt->dalsi = NULL;

    // Pokud je seznam prázdný, přidáme kontakt na začátek
    if (*uk_prvni == NULL)
    {
        *uk_prvni = novyKontakt;
        return;
    }

    // Vkládáme na začátek seznamu, pokud je novější přezdívka (nick)
    if (strcmp(novyKontakt->nick, (*uk_prvni)->nick) < 0)
    {
        novyKontakt->dalsi = *uk_prvni;
        *uk_prvni = novyKontakt;
        return;
    }

    // Procházení seznamu a přidání na správné místo (seřazeno podle přezdívky)
    aktKontakt = *uk_prvni;
    while (aktKontakt)
    {
        if (aktKontakt->dalsi == NULL) // Jsme na posledním kontaktu
        {
            aktKontakt->dalsi = novyKontakt; // Přidáváme na konec
            return;
        }
        else if (strcmp(novyKontakt->nick, aktKontakt->dalsi->nick) < 0)
        {
            novyKontakt->dalsi = aktKontakt->dalsi; // Vkládáme za aktuální kontakt
            aktKontakt->dalsi = novyKontakt;
            return;
        }
        aktKontakt = aktKontakt->dalsi; // Posun na další kontakt
    }
}

// Funkce pro smazání kontaktu ze seznamu podle přezdívky
void del(const char* nick, t_kontakt** uk_prvni)
{
    t_kontakt* aktKontakt;

    // Pokud je kontakt ke smazání na začátku seznamu
    while (*uk_prvni && strcmp((*uk_prvni)->nick, nick) == 0)
    {
        t_kontakt* novyPrvni = (*uk_prvni)->dalsi;
        free(*uk_prvni); // Uvolnění kontaktu z paměti
        *uk_prvni = novyPrvni;
    }

    // Mazání druhého a dalších kontaktů v seznamu
    aktKontakt = *uk_prvni;
    while (aktKontakt && aktKontakt->dalsi) // Procházení seznamu
    {
        if (strcmp(aktKontakt->dalsi->nick, nick) == 0) // Kontakt ke smazání
        {
            t_kontakt* novyDalsi = aktKontakt->dalsi->dalsi;
            free(aktKontakt->dalsi); // Uvolnění kontaktu z paměti
            aktKontakt->dalsi = novyDalsi;
            return;
        }
        aktKontakt = aktKontakt->dalsi; // Posun na další kontakt
    }
}
