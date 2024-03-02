// NECULAU SANDA-ELENA GRUPA 313 CB
#include "tema1.h"

Tlista Aloc_cel_lista_simpla (char caracter[20]) {
        Tlista aux = (Tlista) malloc(sizeof(Tcelula));
        if(!aux) {
                return 0;
        }
        strcpy(aux->info,caracter);
        aux->urm = NULL;
        return aux;
}


Tlista2 Alocare_celula_lista2(char caracter) {
   Tlista2 aux = (Tlista2) malloc(sizeof(Tcelula2));
   if(!aux) { 
        return 0;
   } else {
        aux->info = caracter;
        aux->urm = NULL;
        aux->pre = NULL;
   }
   return aux;
}

Tlista2 Init_lista_dubla (){

        Tlista2 aux = (Tlista2) malloc(sizeof(Tcelula2));
        if(!aux) { 
                return 0;
        }
        aux->info = '0';
        aux->urm = NULL;
        aux->pre = NULL;
        return aux;
}

Tlista2 Initiere_lista_banda () {
        /*santinela + caracterul "#" */
        const char c = '#';
        Tlista2 aux2;
        Tlista2 aux = (Tlista2) malloc(sizeof(Tcelula2));
        if(!aux) { 
                return 0;
        }
        aux->info = 'S' ;
        aux2 = Alocare_celula_lista2(c);
        aux->pre = NULL;
        aux->urm = aux2;
        aux2->pre = aux;
        aux2->urm = NULL;

        return aux;
}


void Afisare_lista_dublu(Tlista2 L, FILE *out) {
    Tlista2 t = L;    

    printf("Lista: ");
    while (t != NULL) {         /* parcurgere lista */
        fprintf(out,"%c", t->info);   
        t = t->urm;
    }
    fputs("\n", out);
}


Tband init(Tlista2 L) {
        Tband aux;
        aux = (Tband)malloc(sizeof(Tbanda));
        if(!aux) {
                return 0;
        }
        aux->l = L;
        aux->crt = L->urm;
        return aux;
}

void SHOW(Tband B, FILE *out) {
        Tband t = B;

        t->l=t->l->urm;
        while(t->l != NULL) {
                if(t->l == t->crt)
                { 
                        fprintf(out, "|%c|", t->l->info);
                } else {
                        fprintf(out, "%c", t->l->info);
                }
                t->l = t->l->urm;
        }
        fputs("\n", out);
}

void ACTUALIZARE_BANDA(Tlista2 L, Tband *B){

        (*B)->l= L;

}

TCoada *Initiere_coada () {
        TCoada *cd = (TCoada *)malloc(sizeof(TCoada));
        if(!cd) {
                return 0;
        } 
        cd->inc = cd->sf = NULL;
        return cd;
}

int Introducere_ele_coada (TCoada *c, char comanda[20]) {
        Tlista aux;

        /*alocare celula*/ 
        aux = (Tlista) malloc(sizeof(Tcelula));
        if(!aux){
                return 0;
        }

        strcpy(aux->info, comanda);
        aux->urm = NULL;

        if(c->sf != NULL) {
                c->sf->urm = aux; /*adaugam elementul intr-o coada nevida*/
        } else {
                c->inc = aux;  /*adaugam elementul intr-o coada vida*/
        }
        c->sf = aux;
        return 1;
}

int EXTRAGERE_COADA(TCoada *c, char *instruct) {

        Tlista aux ;
        if(c->inc == NULL && c->sf == NULL) { // coada este vida
                return 0;
        } else {
                if(c->inc == c->sf) {   // coada are o singura instructiune
                        strcpy(instruct, c->inc->info); // copiaza in instruct instructiunea pe care trebuie sa o faca
                        aux = c->inc;
                        c->inc = NULL;
                        c->sf = NULL;
                        free(aux);
                } else {
                        strcpy(instruct, c->inc->info);
                        aux = c->inc;
                        c->inc = c->inc->urm;
                        free(aux);  
                }
                return 1;
        }        

}

void Afisare_coada(TCoada *c, FILE *out)  // afisare elementele cozii 
{
        Tlista l;
        if(c->inc == NULL)  /* coada vida */
        {
                puts("Coada vida\n");
                return;
        } 
        fputs("Elementele cozii: ", out);
        for(l = c->inc; l != NULL; l = l->urm)
                fprintf(out, "%s ", l->info);
}


void Insert_ele_Lista_dubla(Tlista2 *L, char x)
{
       Tlista2 p = (*L)->urm;
       Tlista2 aux;
       while(p->urm != NULL) {
                p = p->urm; 
       }
       aux = Alocare_celula_lista2(x);
       p->urm = aux;
       aux->pre = p;
       aux->urm = NULL;
       
}

void WRITE(Tband *B, char x) {

           (*B)->crt->info = x;  // se schimba info de la adresa unde puncteaza degetul

}

void MOVE_LEFT(Tband *B, Tstiva *U) {
        Tlista2 aux = (*B)->l;
        ADAUGARE_ADRESA_STIVE(U,*B);
        if((*B)->crt->pre == aux) {
              EXTRAGERE_STIVA(U);  // nu se intampla nimic daca degetul se afla pe prima pozitie
        } else if((*B)->crt->pre != aux) {
                (*B)->crt = (*B)->crt->pre;
        }
}

void MOVE_RIGHT(Tband *B) {
        Tlista2 aux;
        if((*B)->crt->urm == NULL) {  // daca nu exista nu mai exista nicio celula dupa deget 
                aux = Alocare_celula_lista2('#');   // atunci se mai adauga o celula
                aux->pre = (*B)->crt;
                (*B)->crt->urm = aux;
                aux->urm = NULL;
                (*B)->crt = aux;
        } else {
                (*B)->crt = (*B)->crt->urm;   // daca exista celula dorita se muta degetul pe pozitia respectiva
        }
}

void MOVE_R_CHAR(Tband *B, char x) {
        int ok = 0;
        Tlista2 aux; 
        if((*B)->crt->info == x) {
                ok = 1;  // daca a gasit caracterul cautat pe pozitia curenta degetul  nu se schimba
                return;
        } 
        if(!ok) {
                while((*B)->crt->urm != NULL) {
                        if((*B)->crt->urm->info == x) {
                                ok = 1;
                                (*B)->crt = (*B)->crt->urm;
                                break;
                        }
                        (*B)->crt = (*B)->crt->urm;
                }
                if (!ok){
                        aux = Alocare_celula_lista2('#');  // alocam celula noua cu info "#" daca nu exista 
                        aux->pre = (*B)->crt;                // exista caracterul cautat de noi in spre dreapta
                        (*B)->crt->urm = aux;
                        (*B)->crt = (*B)->crt->urm;
                        aux->urm = NULL;
                }
               
        }
}

void MOVE_L_CHAR(Tband *B, char x, FILE *out) {

        int ok = 0;
        Tlista2 p, aux;
        p = (*B)->crt;

        if(p->info == x) {
                return;
                ok = 1;
        }
        if(ok == 0) {
                while(p != (*B)->l) {   // cat timp nu a ajuns la santinela
                        if(p->info == x) {
                                ok = 1;   // s-a gasit caracterul cautat 
                                (*B)->crt = p; // degetul primeste adresa lui p
                                break;
                        }
                        p = p->pre;
                }
                if(!ok) {
                        //revenire la pozitia initiala a degetului nu se modifica nimic
                        fputs("ERROR\n", out);
                }
        }
}

void INSERT_LEFT(Tband *B, char x, FILE *out) {

        Tlista2 aux ;
        Tlista2 p = (*B)->crt;
        if(p->pre == (*B)->l) {
                fputs("ERROR\n", out); // daca pozitia anterioara a degetului este santinela atunci
                return;         // nu se poate muta degetul si se afiseaza eroarea 
        } else {
                aux = Alocare_celula_lista2(x);
                aux->pre = (*B)->crt->pre;
                aux->urm = (*B)->crt;
                (*B)->crt->pre->urm = aux;
                (*B)->crt->pre = aux;
                (*B)->crt = aux;
        }
}

void INSERT_RIGHT(Tband *B, char x) {

        Tlista2 aux;
        aux = Alocare_celula_lista2(x);
        if((*B)->crt->urm != NULL) {  // daca urmatoarea celula dupa deget nu este nula
                
                aux->pre = (*B)->crt;
                aux->urm = (*B)->crt->urm;
                (*B)->crt->urm = aux;
                (*B)->crt = aux;
                (*B)->crt->urm->pre = aux;
        } else {
                aux->pre = (*B)->crt;
                aux->urm = NULL;
                (*B)->crt->urm = aux;
                (*B)->crt = aux;
        }
       
}

void SHOW_C(Tband B, FILE *out) {
        
        fprintf(out,"%c\n", B->crt->info);

}


Tstiva Aloc_cel_lista_stiva () {
        Tstiva aux = (Tstiva) malloc(sizeof(Tadresa));
        if(!aux) {
                return 0;
        }
        aux->urm = NULL;
        return aux;
}




void ADAUGARE_ADRESA_STIVE(Tstiva *U, Tband B) {

        Tstiva aux;
        aux = (Tstiva) malloc(sizeof(Tadresa));
        if(!aux) {
                printf("Alocare nereusita");
        }
        aux->info = B->crt; // primeste adresa ca valoare
        aux->urm = NULL;

        if((*U) == NULL) {    // daca stiva este vida
                (*U) = aux;
                (*U)->urm = NULL;
        } else {
                aux->urm = (*U);
                (*U) = aux;
        }
}

/*Extragere celula din stiva si eliminarea ei*/
void EXTRAGERE_STIVA(Tstiva *U) {

        Tstiva aux;
        aux = (*U);
        (*U) = (*U)->urm;
        free(aux); 
}

void UNDO(Tstiva *U, Tband *B, Tstiva *R) {
        Tstiva aux;
        aux = (*U);
        ADAUGARE_ADRESA_STIVE(R, (*B)); // adaug in R adresa degetului curent inainte de modificare
        (*B)->crt = (*U)->info;
        (*U) = (*U)->urm;  // eliminam prima celula din stiva
        free(aux);
} 

void REDO(Tstiva *U, Tband *B, Tstiva *R) {
        Tstiva aux;
        aux = (*R);
        ADAUGARE_ADRESA_STIVE(U, (*B));  // adaug in U adresa degetului curent nemodificat
        (*B)->crt = (*R)->info;
        (*R) = (*R)->urm;
        free(aux);
}

void DISTRUGERE_STIVA(Tstiva *S) {
        Tstiva p, aux;
        p = *S;
        while(p != NULL) {
                aux = p;
                p = p->urm;
                free(aux); 
        }
        *S = NULL;
}


/*distruge liste simple*/
void DISTRUGERE_LISTA(Tlista *L) {
        Tlista laux, aux;
        laux = *L;
        while(laux != NULL) {
                aux = laux;
                laux = laux->urm;
                free(aux); 
        }
}

/*distruge listele dublu inlatuite*/
void DISTRUGERE_LISTA2(Tlista2 *B) {
        Tlista2 baux = (*B)->urm, aux;
        while (baux != NULL) {         /* distrugere elementele listei */
                aux = baux;
                baux = baux->urm;
                free(aux);
        }
        free(*B);
        *B = NULL;
}


void DISTRUGERE_COADA(TCoada *C) {
        Tlista caux ;
        caux = C->inc;
        C->inc = NULL;
        C->sf = NULL;
        DISTRUGERE_LISTA(&caux);
        free(C);
        C = NULL;
}


void Afisare_stiva(Tstiva U, FILE *out) {
        fputs("Stiva: ", out);
        while (U != NULL) {                  
                fprintf(out, "%p ", U->info);   
                U = U->urm;
        }
        fputs("\n", out);
}
