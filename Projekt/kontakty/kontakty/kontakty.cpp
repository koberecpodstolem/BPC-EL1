#include <stdio.h>
#include <ctype.h>     
#include <stdlib.h>
#include "kontakty.h"
#include "kontaktyDB.h"

struct t_kontakt* prvni = NULL; 

//####################################################################################################

void Save2File()
{
    FILE* file = fopen("../../../../kontakty.txt", "w"); 
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

    fclose(file); 
    printf("Contacts saved\n");
}

//####################################################################################################

void LoadFromFile()
{
    FILE* file = fopen("../../../../kontakty.txt", "r"); 
    if (file == NULL)
    {
        printf("Err loading file\n");
        return;
    }

    char nick[NICK_SIZE], name[NAME_SIZE], surname[SURNAME_SIZE];
    char phnumber[PHNUMBER_SIZE], email[EMAIL_SIZE];

    while (fscanf(file, "%s %s %s %s %s", nick, name, surname, phnumber, email) == 5)
    {
        
        add(nick, name, surname, phnumber, email, &prvni);
    }

    fclose(file); 
    printf("Loaded.\n");
}
//####################################################################################################

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

//####################################################################################################

void OnDel() {
    int my_id;

    // Získání ID kontaktu, který chceme odstranit
    printf("\nZadejte ID kontaktu k odstraneni: ");
    scanf_s("%d", &my_id);  // Načteme ID kontaktu
    while (getchar() != '\n');  // Odstraníme přebytečné znaky

    // Volání funkce pro odstranění kontaktu podle ID
    del(my_id, &prvni);
}

//####################################################################################################

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
            return; 

        }
        aktKontakt = aktKontakt->dalsi; // Posun na další kontakt
    }
    
    printf("Kontakt nenalezen.\n");
    getchar();
}

//####################################################################################################

void ShowContacts() {
    struct t_kontakt* aktKontakt = prvni; 
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

//####################################################################################################

void FindBySurname() {
    char hledane_prijmeni[SURNAME_SIZE];

    printf("\nZadejte prijmeni pro vyhledani: ");
    scanf_s("%s", hledane_prijmeni, SURNAME_SIZE);
    while (getchar() != '\n');  // Odstranění přebytečných znaků

    struct t_kontakt* aktKontakt = prvni;
    bool nalezeno = 0;

    printf("\nVyhledane kontakty:\n");
    while (aktKontakt) {
        if (strcmp(aktKontakt->surname, hledane_prijmeni) == 0) {  // Porovnání příjmení
            printf("ID: %d\n", aktKontakt->id);
            printf("Prezdivka: %s\n", aktKontakt->nick);
            printf("Jmeno: %s\n", aktKontakt->name);
            printf("Prijmeni: %s\n", aktKontakt->surname);
            printf("Telefon: %s\n", aktKontakt->phnumber);
            printf("E-mail: %s\n\n", aktKontakt->email);
            nalezeno = 1;
        }
        aktKontakt = aktKontakt->dalsi;
    }

    if (!nalezeno) {
        printf("Zadne kontakty s timto prijmenim nebyly nalezeny.\n");
    }
    getchar();  
}

//####################################################################################################

int main()
{
    LoadFromFile();
    char cmd;

    do
    {
        system("cls");
        printf("A: Novy     ");
        printf("D: Smazat     ");
        printf("P: Zobrazit vse     ");
        printf("C: Otevrit kontakt     ");
        printf("H: Hledat prijmeni     ");
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
        case 'h':
            FindBySurname();
            break;
        }
    } while (cmd != 'q');

    Save2File();
    return 0;
}
