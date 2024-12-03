#include <stdio.h>
#include <ctype.h>     
#include <stdlib.h>
#include "kontakty.h"
#include "kontaktyDB.h"

struct t_kontakt* prvni = NULL; // globalni ukazatel na prvni kontakt

void Save2File()
{
    FILE* file = fopen("../../../../kontakty.txt", "w"); // Otevreme soubor pro zapis
    if (file == NULL)
    {
        printf("Err.\n");
        return;
    }

    struct t_kontakt* aktKontakt = prvni;
    while (aktKontakt)
    {
        // Zapise kontakt do souboru
        fprintf(file, "%s %s %s %s %s\n",
            aktKontakt->nick, aktKontakt->name, aktKontakt->surname,
            aktKontakt->phnumber, aktKontakt->email);
        aktKontakt = aktKontakt->dalsi;
    }

    fclose(file); // Zavreme soubor
    printf("Contacts saved\n");
}

// Funkce pro nacteni seznamu ze souboru
void LoadFromFile()
{
    FILE* file = fopen("../../../../kontakty.txt", "r"); // Otevreme soubor pro cteni
    if (file == NULL)
    {
        printf("Err loading file\n");
        return;
    }

    char nick[NICK_SIZE], name[NAME_SIZE], surname[SURNAME_SIZE];
    char phnumber[PHNUMBER_SIZE], email[EMAIL_SIZE];

    while (fscanf(file, "%s %s %s %s %s", nick, name, surname, phnumber, email) == 5)
    {
        // Pridame kontakt do seznamu
        add(nick, name, surname, phnumber, email, &prvni);
    }

    fclose(file); // Zavreme soubor
    printf("Loaded.\n");
}

void OnAdd()
{
    char my_nick[NICK_SIZE];
    char my_name[NAME_SIZE];
    char my_surname[SURNAME_SIZE];
    char my_phnumber[PHNUMBER_SIZE];
    char my_email[EMAIL_SIZE];

    // Ziskani udaju o kontaktu
    printf("\nPrezdivka: ");
    scanf_s("%s", my_nick, NICK_SIZE);
    while (getchar() != '\n');

    printf("\nJmeno: ");
    scanf_s("%s", my_name, NAME_SIZE);
    while (getchar() != '\n');

    printf("\nPrijmeni : ");
    scanf_s("%s", my_surname, SURNAME_SIZE);
    while (getchar() != '\n');

    printf("\nTelefonni cislo : ");
    scanf_s("%s", my_phnumber, PHNUMBER_SIZE);
    while (getchar() != '\n');

    printf("\nE-mail : ");
    scanf_s("%s", my_email, EMAIL_SIZE);
    while (getchar() != '\n');

    add(my_nick, my_name, my_surname, my_phnumber, my_email, &prvni); // Volame pridavaci funkci
}

void OnDel() {
    int my_id;

    // Získání ID kontaktu, který chceme odstranit
    printf("\nZadejte ID kontaktu k odstraneni: ");
    scanf_s("%d", &my_id);  // Načteme ID kontaktu
    while (getchar() != '\n');  // Odstraníme přebytečné znaky

    // Volání funkce pro odstranění kontaktu podle ID
    del(my_id, &prvni);
}

void detail()
{
    int id;

    printf("\nID: ");
    scanf_s("%d", &id);
    while (getchar() != '\n');
 
    struct t_kontakt* aktKontakt = prvni;
    printf("\n\n");
    while (aktKontakt)
    {
        if (aktKontakt->id == id) 
        {
            printf("ID: %d\n", aktKontakt->id);
            printf("Prezdivka: %s\n", aktKontakt->nick);
            printf("Jmeno: %s\n", aktKontakt->name);
            printf("Prijmeni: %s\n", aktKontakt->surname);
            printf("Telefon: %s\n", aktKontakt->phnumber);
            printf("E-mail: %s\n", aktKontakt->email);
            getchar();
            return; // Kontakt byl nalezen, ukončíme funkci
        }
        aktKontakt = aktKontakt->dalsi; // Posun na další kontakt
    }
    
    printf("Kontakt nenalezen.\n");
    getchar();
}

void ShowContacts() {
    struct t_kontakt* aktKontakt = prvni; // ukazatel na aktualni kontakt
    printf("\n\n");
    while (aktKontakt) // prochazeni seznamu
    {
        printf("(%d) %s %s\n",
            aktKontakt->id,               // Zobrazení ID
            aktKontakt->name,
            aktKontakt->surname);
        aktKontakt = aktKontakt->dalsi; // posun na dalsi kontakt
    }
    getchar();
}

int main()
{
    LoadFromFile();
    char cmd;

    do
    {
        system("cls");
        printf("A: Pridat     ");
        printf("D: Smazat     ");
        printf("P: Tisk     ");
        printf("C: Detail kontaktu     ");
        printf("Q: Ulozit a konec\n\n");

        cmd = tolower(getchar());
        while (getchar() != '\n');

        switch (cmd)
        {
        case 'a':
            OnAdd();
            break;
        case 'd':
            OnDel();         
            break;
        case 'p':
            ShowContacts();
            break;
        case 'c':
            detail();
            break;
        }
    } while (cmd != 'q');

    Save2File();
    return 0;
}
