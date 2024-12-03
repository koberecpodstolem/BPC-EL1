#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include "kontaktyDB.h"

int last_id = 1;

void add(char* nick, char* name, char* surname, char* phnumber, char* email, struct t_kontakt** uk_prvni) { 
    struct t_kontakt* novyKontakt; 
    struct t_kontakt* aktKontakt;  

    // alokace dynamické paměti
    novyKontakt = (struct t_kontakt*)malloc(sizeof(struct t_kontakt));
    if (novyKontakt == NULL) {
        printf("Chyba alokace paměti!\n");
        return;
    }
    
    // naplnění struktury
    novyKontakt->id = last_id++;
    strcpy_s(novyKontakt->nick, NICK_SIZE, nick);
    strcpy_s(novyKontakt->name, NAME_SIZE, name);
    strcpy_s(novyKontakt->surname, SURNAME_SIZE, surname);
    strcpy_s(novyKontakt->phnumber, PHNUMBER_SIZE, phnumber);
    strcpy_s(novyKontakt->email, EMAIL_SIZE, email);
    novyKontakt->dalsi = NULL;

    if (*uk_prvni == NULL) { 
        *uk_prvni = novyKontakt;
        return;
    }

    // vložíme na začátek, pokud není žádný kontakt předchozí
    aktKontakt = *uk_prvni;
    while (aktKontakt) { 
        if (aktKontakt->dalsi == NULL) { 
            aktKontakt->dalsi = novyKontakt; // přidání na konec seznamu
            return;
        }
        aktKontakt = aktKontakt->dalsi; 
    }
}

void del(int id, struct t_kontakt** uk_prvni) {
    struct t_kontakt* aktKontakt;

    // Pokud je kontakt ke smazání na začátku seznamu
    while (*uk_prvni && (*uk_prvni)->id == id) {
        struct t_kontakt* novyPrvni = (*uk_prvni)->dalsi;
        free(*uk_prvni);  // Uvolnění paměti
        *uk_prvni = novyPrvni;  
    }

    // Mazání druhého a dalších kontaktů v seznamu
    aktKontakt = *uk_prvni;
    while (aktKontakt && aktKontakt->dalsi) { // Procházení seznamu
        if (aktKontakt->dalsi->id == id) { // Kontakt ke smazání
            struct t_kontakt* novyDalsi = aktKontakt->dalsi->dalsi;
            free(aktKontakt->dalsi);  
            aktKontakt->dalsi = novyDalsi; 
            return;
        }
        aktKontakt = aktKontakt->dalsi; 
    }
}
