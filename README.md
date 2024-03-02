# Magic-Tape

1. Prezentare operațiilor posibile
Există mai multe operații care pot fi executate. Acestea sunt împărțite în următoarele categorii: UPDATE, QUERY, UNDO / REDO, EXECUTE. În continuare, vom prezenta fiecare categorie în parte, specificând pentru fiecare ce particularități prezintă și care sunt operațiile incluse.

2.1. Operații de tip UPDATE

Operațiile de tip UPDATE permit deplasarea cu o poziție pe banda (stânga/dreapta), de- plasarea pana la în anumit caracter (stânga/dreapta). În cazul operațiilor de deplasare, se poate modifica numai poziția degetului, fără a modifica conținutul benzii. De asemenea, în cadrul acestor operații există posibilitatea de a modifica conținutul benzii, prin suprascrierea caracterului din poziția degetului (fără a se modifica poziția degetului). O altă operație posibilă constă în posibilitatea de a insera un caracter în stânga, respectiv dreapta poziției degetului caz în care se va realiza și deplasarea acestuia.
    Observaţie
Este important de remarcat faptul că aceste operații nu sunt executate direct. Atunci când întâlnim o astfel de comandă doar o adaugăm într-o coadă.
Operaţiile posibile de tip UPDATE sunt:
• Deplasare deget cu o poziție la stânga / dreapta: "MOVE_LEFT" sau "MOVE_RIGHT". Dacă ne aflăm la prima poziție și întâlnim operația "MOVE_LEFT" nu se întâmplă nimic, dar dacă ne aflăm la ultima poziție și întâlnim "MOVE_RIGHT" mutăm degetul cu o poziție mai la dreapta, iar în celula respectivă scriem caracterul #
Deplasare dreapta / stânga până la primul caracter egal cu un anumit simbol: "MOVE_LEFT_CHAR <C>", "MOVE_RIGHT_CHAR <C>", unde <C> este un caracter. Căutarea începe de la poziția curentă a degetului.
- În cazul operației "MOVE_LEFT_CHAR <C>" dacă se ajunge în marginea din stânga a benzii și nu s-a găsit caracterul căutat, se va afișa ERROR iar poziția degetului nu se modifică.
- În cazul operației "MOVE_RIGHT_CHAR <C>" - dacă se ajunge la limita din dreapta a benzii care conține caractere și nu s-a găsit caracterul căutat, se inserează # la final și poziția degetului va fi pe #-ul inserat.
• Actualizarea caracterului curent: "WRITE <C>"
• Inserare caracter în stânga/dreapta poziției degetului (implică inserare și deplasarea degetului pe noua poziție inserată): "INSERT_LEFT <C>", "INSERT_RIGHT <C>". Dacă degetul se află pe prima poziție, nu se poate insera la stânga - se afișează mesajul ERROR, banda ramâne nemodificată și poziția degetului rămâne nemișcată.

2.2 Operații de tip QUERY

Operațiile de tip QUERY permit afișarea caracterului curent (din poziția curentă a degetului), respectiv afișarea conținutului benzii, cu marcarea poziției curente pe banda.
    Observaţie
Aceste operații sunt executate direct atunci când sunt întâlnite.
• Determinare caracter din poziția degetului: "SHOW_CURRENT"
• Afișare conținut bandă: "SHOW". Caracterul pe care se află degetul va fi pus între |. De exemplu, abc dle semnifică faptul că degetul se află pe caracterul d.

2.3 Operații de tip UNDO / REDO

    Important
Pentru fiecare din operațiile UNDO / REDO se va folosi câte o stivă / comandă care va fi implementată pornind de la o listă.
Operațiile de tip UNDO / REDO permit anularea ultimei operații aplicate, respectiv refacerea ultimei operații aplicate.
    Observaţie
Aceste operații sunt executate direct atunci când sunt întâlnite și ele nu modifică în vreun fel conținutul benzii. Cu alte cuvinte, acestea vor modifica doar poziția degetului. De aceea, este suficient să reținem în stivele pentru cele două operații doar un pointer la poziția curentă.
Dacă este executată comanda MOVE_RIGHT și în urma execuției se adăugă simbolul # la finalul benzii, atunci când vom apela comanda UNDO vom schimba doar poziția degetului, fără a elimina simbolul inserat la final.

  Se garantează că operațiile de UNDO și de REDO se vor da doar pentru operațiile de "MOVE_LEFT", "MOVE_RIGHT", nu vor fi pentru operații de "WRITE <C>" și "INSERT_LEFT <C>", "INSERT_RIGHT <C>" - nu trebuie făcute verificări suplimentare pentru a verifica acest lucru (se garantează că operațiile de UNDO și de REDO nu vor modifica banda).
    
    Observaţie
• Atunci când executăm operația UNDO, extragem pointerul reținut în vârful stivei pentru UNDO, adăugăm pointerul la poziția curentă a degetului în vârful stivei pentru REDO, după care modificăm poziția degetului astfel încât să indice către pointerul extras din stiva pentru UNDO.
• Atunci când executăm operația REDO, extragem pointerul reținut în vârful stivei pentru REDO, adăugăm pointerul la poziția curentă a degetului în vârful stivei pentru UNDO, după care modificăm poziția degetului astfel încât să indice către pointerul extras din stiva pentru REDO.
După o operație de WRITE stivele de UNDO / REDO e util să fie golite, pentru că se garantează că nu se vor da operații de UNDO / REDO peste cele de WRITE.

2.4 Operația EXECUTE

    Important
Pentru comanda EXECUTE se va folosi o coadă implementată pornind de la o listă.
Pentru a face lucrurile mai interesante, operațiile de tip UPDATE nu se vor executa pe măsură ce se citesc. Ele se vor adăuga într-o coadă, iar în cadrul testelor, în lista cu query- uri vor fi intercalate comenzi de tip EXECUTE. O comandă EXECUTE va lua prima operație de UPDATE disponibilă din coadă și o va executa. Până nu se dă EXECUTE, banda rămâne în starea originală ("#").
    Observaţie
Dacă operația curentă care urmează să fie executată este una dintre MOVE_LEFT, MOVE_RIGHT, se va reține pointerul la nodul curent din listă, se va încerca aplicarea operației, iar dacă aceasta este realizată cu suc- ces, atunci pointerul reținut anterior este adăugat în stiva pentru UNDO.


    IMPORTANT
  
  •  Pentru a evidenția simbolul marcat de deget, la afișare, acesta va fi precedat și succedat de caracterul | (bară verticală). Spre exemplu vom avea următoarea afișare: !b|2|9a#
  •  Banda are inițial un singur caracter pe ea, caracterul #, dar are proprietatea că se poate extinde la dreapta oricât de mult (la stânga nu se poate extinde).
          
    Observatie
•  Caracterele # și nu se vor folosi niciodată în testele efectuate. Caracterul # este folosit doar pentru a indica o poziție alocată din banda, iar caracterul "|" este utilizat pentru a marca, în afișare, simbolul pe care este poziționat degetul.
