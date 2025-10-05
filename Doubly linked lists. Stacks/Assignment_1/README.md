/*Antemir Andreea-Catalina 314CA*/

Structurile folosite sunt urmatoarele:
-structura "page" data in enuntul temei pe care nu am modificat o
-structura "tab" data in enunt pe care de asemenea nu am modificat o
-structura "browser" pentru care nu am schimbat campurile date in enunt
-o structura pentru o lista dublu inlantuita pentru tab uri
-o structura pentru o lista simplu inlantuita folosita pentru stive
-o  structura pentru nodurile listei dublu inlantuite
-o structura pentru nodurile listei simple inlantuite
-o structura pentru stiva

Functii
-create_node_stack - creeaza nodul pentru stiva alocand memorie pentru acesta
                   - daca alocarea a functionat, se initializeaza campurile
                    structurii corespunzator: campul data primeste data primita
                    drept parametru, iar campul next este initializat cu NULL
-create_node_dlist - creeaza nodul pentru lista dublu inlantuita
                   - se aloca memorie pentru acesta, iar daca alocarea a
                   functionat, se initializeaza campurile structurii astfel:
                   data cu parametrul data, next si prev cu NULL
-push - functie folosita pentru adaugarea unui nod in stiva, creandu-se un nou
      nod si, de asemenea legaturile dintre acesta si ultimul nod adaugat in
      stiva
      - astfel, dimensiunea listei creste cu 1 si capul listei este
      reinitializat cu nodul proaspat adaugat
-pop - asemanatoare functiei push, doar ca in acest caz, ultimul nod din stiva
     este eliminat
     - se elibereaza memoria alocata nodului eliminat
-empty - verifica daca lista e goala prin compararea dimensiunii cu 0
       - astfel, daca size ul este 0, lista este goala si se returneaza 1
       - in schimb, se returneaza 0
-clear - elibereaza intreaba memorie alocata pentru nodurile stivei,
       lasand stiva complet goala
       - se reinitializeaza capul stivei cu NULL si dimensiunea cu 0
-free_browser - elibeeaza memoria pentru intregul browser, inclusiv pagina
              curenta, descrierea paginii curente, stivele backward si forward,
              sentinela, fiecare tab si intregul browser
-free_page - elibereaza memoria alocata pentru fiecare pagina si pentru
           descrierea fiecarei pagini
-free_pages - elibereaza memoria alocata pentru vectorul de pagini si pentru
            fiecare descrierele din acest vector
-create_default_page - aloca memorie pentru pagina default a fiecarui tab
                     deschis in browser
                     - se initializeaza id ul, url ul si descrierea cu cele
                     date in enuntul temei
-create_tab - se aloca memrie pentru un tab
            - daca alocarea a functionat, se initializeaza fiecare camp din
            structura
            - se creeaza pagina curenta
            - se aloca memorie pentru fiecare stiva si lista din stiva si se
            initializeaza campurile stivei
-create_browser - se aloca memorie pentru intregul browser
                - daca alocarea a mers, se aloca memorie pentru sentinela
                listei dublu inlantuita, se creeaza legaturile listei si se 
                initializeaza campurile listei
                - se creeaza tab ul cu id 0 si se fac legaturile intre acesta
                si sentunela
-new_tab - se creeaza tab ul cu id ul reprezentativ si se fac legaturile
         dinttre acesta si celelalte noduri din lista
-close - daca se incearca sa se inchida tab ul cu id 0 se afiseaza mesajul
       de eroare
       - in schimb, cand ajungem la tabul curent, stergem legaturile acestuia
       cu celelalte taburi din lista si eliberam memoria tabului repectiv dupa
       ce reinitializam tabul curent cu cel aflat in stanga tab ului tinta
-open - verificam daca id ul dat se afla in lista de taburi
      - daca nu se afla, atunci ok isi pastreaza valoarea 0 si se afiseaza
      mesajul de eroare
      - daca id ul s a gasit, atunci setam tab ul curent drept cel cu id ul
      specificat si ok devine 1
-next - se seteaza tab ul curent drept cel ce urmeaza dupa acesta
      - daca acesta este de fapt sentinela, atunci tab ul curent devine tab ul
      cu id 0
-prev - se seteaza tab ul curent drept cel precedent acestuia
      - daca  acesta este de fapt sentinela, atunci tab ul curent devine
      ultimul tab din lista
-page - daca pagina cu id ul specificat exista in vectorul de pagini, ok devine
      1 si se retine pozitia pe care s a gasit id ul
      - se seteaza drept pagina curenta pagina cu id ul respectiv, vechea
      pagina curenta devine capul stivei backward, iar stiva forward se goleste
-print - se afiseaza id urile tuturor tab urilor incepand cu cel curent
       - dupa asta, se afiseaza descrierea tab ului curent
-backward - daca stiva backward este goala se afiseaza mesajul de eroare
          - in cazul contrar, pagina curenta se pune in stiva forward, se
          scoate din stiva backward ultima pagina si se seteaza drept pagina
          curenta
-forward - daca stiva forward este goala se afiseaza mesajul de eroare
         - in cazul contrar, pagina curenta se pune in stiva backward, se
         scoate din stiva forward ultima pagina si se seteaza drept pagina
         curenta
-print_stack_forward - folosesc aceasta functie ca sa afisez recursiv
                     stiva forward incepand cu primul element adaugat in stiva
-print_stack_backward - folosesc aceasta functie ca sa afisez recursiv stiva
                      backward incepand cu ultimul element adaugat in stiva
-print_history - se cauta tab ul cu id ul specificat
               - daca id ul a fost gasit, se afiseaza url urile fiecarei pagini
               din tab imcepand cu prima pagina adaugata in stiva forward, apoi
               cel al paginii curente, si apoi, cele din stiva backward,
               incepand cu ultima pagina adaugata in stiva
               - in caz contrat se afiseaza mesajul de eroare
-close_files - inchide fisierele de intrare si/sau de ierire
-verify_command - proceseaza fiecare comanda si apeleaza fnctia reprezentativa
                fiecarei comenzi
-main - in functia princiala creez vectorul de pagini citind fiecare pagina
      din fisier, cea default ocupand pozitia 0
      - cream browserul
      -citim fiecare comanda si apelam verify_command ca sa procesam fiecare
      comanda

FEEDBACK CHECKER

-= TEMA 1 SDA =-
Total: 100/100
Valgrind: 20/20