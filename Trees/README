Antemir Andreea-Catalina - 314CA


Structurile folosite sunt urmatoarele:

-o structura pentru un nod de arbore binar care este reprezentat de un
nume si o frecventa, dar care contine si pointeri la cei doi copii ai sai

-o structura pentru un heap care contine un vector de pointeri de tip node_t,
numarul de elemente din vector, capacitatea maxima a vectorului, dimensiunea
fiecarui element din vector si o functie de comparatie


Functii utilizate in cod:

-compare_node - aceasta functie compara doua noduri de tip node_t folosind qsort
              - mai intai sorteaza crescator dupa frecvente, iar daca
              frecventele sunt egale, sorteaza lexicografic in functie de nume

-create_heap - functia se ocupa cu creearea unui heap, alocand memorie initial
             pentru intreaga structura, iar apoi pentru vector
             -seteaza pointerul la functia de comparatie, dimensiunea
             elementelor si capacitatea
             -initializeaza numarul de elemente din heap cu 0

-create_node - se ocupa cu crearea unui nod de arbore, alocand memorie mai intai
             pentru intreaga structura, apoi pentru numele satelitilor
             -initializeaza frecventa si copiaza numele in structura si seteaza
             poiterii left si right la NULL

-free_node - elibereaza memoria unui subarbore in mod recursiv
           - mai intai se elibereaza pentru numele fiecarui nod, iar apoi
           functia se apeleaza pentru ramurile left si right
           - la final se elibereaza memoria intregii structuri

-free_heap - elibereaza memoria ocupara de heap
           - mai inati elibereaza memoria pentru vectorul heapului si apoi cea
           ocupara de heap in sine

-heapify_min - functia porneste de la pozitia pos si calculeaza indexurile
             ambilor fii
             - determina cel mai mic element dintre parinte si copii folosind
             functia de comparare
             - daca minimul nu se afla pe pozitia curenta, face swap cu copilul
             respectiv
             - apoi se apeleaza recursiv pentru noua pozitie pentru a continua
             ajustarea
             - executia se incheie cand min_heapul isi pastreaza proprietatea

-insert - aceasta functie insereaza un poiter pentru noul nod pe ultima pozitie
        libera din heap (heap->size)
        - incredemnteaza heap->size intrucat se adauga un nou element
        - dupa ce adauga noul nod ii compara valoarea cu cea a parintelui sau
        - daca acesta este mai mic decat parintele face swap intre ele ca sa se
        pastreze proprietatea min_heapului

-heap_top - funtia returneaza radacina heapului
          - fiind un min_heap, radacina are cea mai mic valoarea deci aceasta
          functie returneaza minimul din heap

-delete - face schimb intre ultimul element si primul, pentru a elimina cea mai
        mica valoare din heap
        - decrementeaza heap->size, intrucat se micsoreaza numarul de elemente
        - se apeleaza heapify_min pentru a se reveni la structura unui min_heap
        proprietate care a fost alterata odata cu punerea pe prima pozitie a
        ultimului element (cea mai mare valoare)

-print_tree - functia aloca memorie pentru un buffer (coada) elements_tree de
            dimensiune 2*n-1, dimensiunea unui arbore binar complet cu n frunze
            - in acest buffer vor fi puse toate elementele 
            - apoi pune radacina in buffer si repeta: scoate nodul curent, il
            afiseaza in format "freq-nume”, iar copiii existenti ii pune la
            sfarsit

-built_tree - citeste n noduri de forma "freq-nume" si retine n in n_out daca
            este necesar la celalte functii in care aceasta functie este apelata
            (parametru folosit la alocarea unor vectori de tip coada temporari)
            - creeaza folosind toate aceste noduri un min_heap
            - dupa, cat timp in heap raman minim 2 noduri, extrage cele mai mici
            2 valori din heap, le creeaza parintele (frcventa parintelui este
            suma frecventelor celor doua noduri extrase, iar numele sau este
            format prin concatenarea numelor celor doua noduri)
            - adauga parintele in heap
            - ultimul nod ramas reprezinta radacina arborelui care ne trebuie
            ulterior in rezolvarea cerintelor, motiv pentru care il returneaza

-process_c1 - construieste arborele cerut cu built_tree
            - afiseaza arborele in fisierul de iesire folosindu se de print_tree
            - elibereaza memoria alocata pentr nodul in care retine radacina
            arborelui creat in built_tree

-process_c2 - functia construieste arborele cu ajutorul lui built_tree
            - citeste numarul de codificari si codificarile in sine
            - pentru fiecare codificare, parcurge arborele de la radacina
            inaintand stanga sau dreapta in functie de valoarea respectiva
            (0 - stanga, 1 - dreapta)
            - daca nu au fost parcursi toti bitii din codificares curenta, dar
            am inaintat pana am dat de o frunza, ne intoarcem la radacina pentru
            a parcurge arborele pana cand toate mutarile cerute de bitii din
            codificare au fost realizate
            - la final se elibereaza memoria alocata pentru nodul in care retine
            radacina arborelui creat in built_tree

-find_leaf - verifica, printr o parcurgere in latime (folosind un buffer alocat
           dinamic), daca subarborele cu radacina node contine o frunza care are
           acelasi nume cu cel pe care dorim sa l gasim
           - astfel, adauga in buffer fiecare nod curent in buffer pana cand il
           gaseste pe cel dorit
           - cand il gaseste elibereaza bufferul si returneaza 1, iar daca au
           fost parcurse toate nodurile, insa nu s a gasit cel dorit, returneaza
           0, inainte de asta eliberand memoria bufferului

-process_c3 - functia construieste arborele cu ajutorul lui built_tree
            - pentru fiecare frunza care trebuie codificata, functie coboara de
            la radacina la fiecare frunza folosind find_leaf
            - daca leaf returneaza 1 in cazul nodului curent, iar acesta are cel
            putin un copil, inaintam in directia respectiva, si adaugam bitul in
            sirul de codificari
            - mai exact, daca inaintam la stanga, adaugam 0 daca inaintam la
            dreapta adaugam 1
            - la final adauga terminatorul de sir si elibereaza memoria nodului
            in care a retinut radacina arborelui create in buit_tree

-process_c4 - construieste arborele cerut cu built_tree
            - coboara in arbore, in stanga sau drepta daca subarborele ar carui
            radacina este nodul curent contine toate frunzele cerute
            - acest lucru il stabilim prin faptul ca numele nodului curent ar
            trebui sa contina toate numele elementelor din aubarborele "lui"
            - daca acesta nu contine toate frunzele necesare, ne oprim, si
            eliberam memoria nodului in care am retinut radacina arborelui
            returnat de built_tree

-close_files - inchide fisierele de intrare si/sau de ierire

-main - verifica numarul de argumente din linia de comanda intrucat acestea
      trebuie sa fie in numar de 4
      - in fucntie de ce parametru primeste pe pozitia 1 (c1, c2, c3, c4), se
      apeleaza functia corespunzatoare cerintei
      - la final se inchid fisierele de intrare si iesire


Rezultatul checkerului:
-toate testele sunt verificate cu VALGRIND
-checkerul imi ofera 95 de puncte fara README

======================================
Scor total: 95.00 puncte din 115.
(Teste rulate: 84)
======================================
