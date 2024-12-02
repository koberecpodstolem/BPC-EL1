#pragma once

#define NICK_SIZE 50       // Maximální délka přezdívky
#define NAME_SIZE 50       // Maximální délka jména
#define SURNAME_SIZE 50    // Maximální délka příjmení
#define PHNUMBER_SIZE 20   // Maximální délka telefonního čísla
#define EMAIL_SIZE 100     // Maximální délka e-mailu

struct t_kontakt {
    char nick[NICK_SIZE];         // Přezdívka
    char name[NAME_SIZE];         // Jméno
    char surname[SURNAME_SIZE];   // Příjmení
    char phnumber[PHNUMBER_SIZE]; // Telefonní číslo
    char email[EMAIL_SIZE];       // E-mailová adresa
    struct t_kontakt* dalsi;      // Ukazatel na další kontakt v seznamu
};

void add(char* nick, char* name, char* surname, char* phnumber, char* email, struct t_kontakt** uk_prvni);
void del(char* nick, struct t_kontakt** uk_prvni);