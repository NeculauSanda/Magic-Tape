// NECULAU SANDA-ELENA GRUPA 313 CB
#include"tema1.h"

int main () {
       int dim = 0;
       Tlista2 B = NULL;  // lista dublu inlatuita unde se vor retine caracterele
       Tband Ba;  //banda 
       TCoada *Co;  // coada unde se vor retine instructiunile
       char instruct[20], instruct2[20]= {0};
       char caracter = '0';
       Tstiva U = NULL, R = NULL;  // declararea stivelor pt UNDO si REDO 


       /* DESCHIDERE FISIER*/ 
       FILE *in ;
       in = fopen("tema1.in", "rw");

       if(in == NULL) {
              fprintf(stderr, "Eroare, nu se poate deschide fisierul %s", "tema1.in");
              return 0;
       }

       /*CREARE FISIER OUTPUT*/
       FILE *out = fopen("tema1.out", "wt");

       if(!out) {
              fprintf(stderr, "Eroare, nu se poate deschide fisierul %s", "tema1.out");
              return 0;
       }

       //initiere coada
       Co = Initiere_coada();

       // initiere lista + banda
       B = Initiere_lista_banda();
       if(!B) return 1;
       Ba = init(B);

       // citire dimensiune
       fscanf(in, "%d", &dim);
       fgets(instruct, 20 , in);   //citim pana se termina randul 


       /*Citim comenzile, ce vor fi retinute in "instruct"*/
       while(fgets(instruct, 20 , in)){

              instruct[strcspn(instruct, "\n")] = 0; // eliminam new line de la sfarsitul fiecarui sir citit

              if(strcmp(instruct,"EXECUTE") == 0) {

                     EXTRAGERE_COADA(Co, instruct2);  // pt a elimina prima comanda din coada si a retine instructiunea

                     if(strcmp(instruct2,"MOVE_LEFT") == 0) {
                            
                            ACTUALIZARE_BANDA(B, &Ba);  //actualizam banda
                            MOVE_LEFT(&Ba, &U);

                     } else if(strcmp(instruct2,"MOVE_RIGHT") == 0) {

                            ACTUALIZARE_BANDA(B, &Ba);
                            ADAUGARE_ADRESA_STIVE(&U,Ba);
                            MOVE_RIGHT(&Ba);  

                     }  else if(strncmp(instruct2,"MOVE_LEFT_CHAR", 14) == 0) {

                             
                            caracter = instruct2[15];
                            MOVE_L_CHAR(&Ba, caracter, out);
                           

                     }  else if(strncmp(instruct2,"MOVE_RIGHT_CHAR", 15) == 0) {

                            caracter = instruct2[16];
                            MOVE_R_CHAR(&Ba, caracter);
                            ACTUALIZARE_BANDA(B, &Ba);  //actualizam banda

                     } else if(strncmp(instruct2, "INSERT_LEFT", 11) == 0) {

                            ACTUALIZARE_BANDA(B, &Ba);
                            caracter = instruct2[12];
                            INSERT_LEFT(&Ba, caracter, out);
                            DISTRUGERE_STIVA(&U);
                            DISTRUGERE_STIVA(&R);

                     }  else if(strncmp(instruct2, "INSERT_RIGHT", 12 ) == 0) {

                            caracter = instruct2[13];
                            INSERT_RIGHT(&Ba, caracter);
                            DISTRUGERE_STIVA(&U);
                            DISTRUGERE_STIVA(&R);

                     } else if(strncmp(instruct2, "WRITE", 5) == 0) {

                            caracter = instruct2[6];
                            WRITE(&Ba,caracter);
                            DISTRUGERE_STIVA(&U);
                            DISTRUGERE_STIVA(&R);

                     }

              } else if(strcmp (instruct, "SHOW") == 0) {
                     ACTUALIZARE_BANDA(B, &Ba);
                     SHOW(Ba, out);
              } else if(strcmp (instruct, "SHOW_CURRENT") == 0) {
                     SHOW_C(Ba, out);
              } else if(strcmp(instruct, "UNDO") == 0) {
                     UNDO(&U, &Ba,&R);
              } else if(strcmp(instruct,"REDO") == 0) {
                     REDO(&U, &Ba,&R);
              } else {
                     if(strcmp(instruct,"EXECUTE") != 0)
                     {
                            Introducere_ele_coada(Co, instruct);
                     }
              }
       }

       fclose(in);
       fclose(out);
       DISTRUGERE_LISTA2(&B);
       free(Ba);
       Ba = NULL;
       DISTRUGERE_COADA(Co);
       DISTRUGERE_STIVA(&R);
       DISTRUGERE_STIVA(&U);
       
       return 0;
}