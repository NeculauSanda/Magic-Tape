// NECULAU SANDA-ELENA GRUPA 313 CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*definire lista simpla*/
typedef struct celula{
    char info[20];
    struct celula *urm;
} Tcelula, *Tlista;


/* definirie lista dubla inlatuita cu santinela*/
typedef struct celula2 {
    char info;
    struct celula2 *urm, *pre;
}Tcelula2, *Tlista2;

/*definire banda*/
typedef struct banda {
   Tlista2 l;
   Tlista2 crt; 
} Tbanda, *Tband;

/*definire coada*/
typedef struct coada
{ 
  Tlista inc, sf;  
} TCoada;

/* definire stiva*/
typedef struct adresa{
    Tlista2 info;
    struct adresa *urm;
}Tadresa, *Tstiva;


Tlista Aloc_cel_lista_simpla (char caracter[20]);
Tlista2 Alocare_celula_lista2(char caracter);
Tlista2 Init_lista_dubla ();
Tlista2 Initiere_lista_banda ();
void Afisare_lista_dublu(Tlista2 L, FILE *out);
TCoada *Initiere_coada ();
int Introducere_ele_coada (TCoada *c, char comanda[20]);
int EXTRAGERE_COADA(TCoada *c, char *instruct);
Tband init(Tlista2 L);
void Afisare_coada(TCoada *c, FILE *out);
void Insert_ele_Lista_dubla(Tlista2 *L, char x);
void WRITE(Tband *B, char x);
void MOVE_R_CHAR(Tband *B, char x);
void MOVE_L_CHAR(Tband *B, char x, FILE *out);
void ACTUALIZARE_BANDA(Tlista2 L, Tband *B);
void SHOW(Tband B, FILE *out);
void SHOW_C(Tband B, FILE *out);
void MOVE_LEFT(Tband *B, Tstiva *U);
void MOVE_RIGHT(Tband *B);
void INSERT_LEFT(Tband *B, char x, FILE *out);
void INSERT_RIGHT(Tband *B, char x);
void ADAUGARE_ADRESA_STIVE(Tstiva *U, Tband B);
void Afisare_stiva(Tstiva U, FILE *out);
Tstiva Aloc_cel_lista_stiva ();
void EXTRAGERE_STIVA(Tstiva *U);
void UNDO(Tstiva *U, Tband *B, Tstiva *R);
void REDO(Tstiva *U, Tband *B, Tstiva *R);
void DISTRUGERE_STIVA(Tstiva *S);
void DISTRUGERE_LISTA(Tlista *L);
void DISTRUGERE_LISTA2(Tlista2 *B);
void DISTRUGERE_COADA(TCoada *C);