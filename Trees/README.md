# Tema 2 – Arbori

```
Ana-Maria Simion, Andreea Dut,ulescu, Anca Bălut,oiu, Cătălin Rîpanu,
Alexandru Axenia, Mihai Nan
```
Data postării: 30.04.

## Deadline: 21.05.2025 ora 23:

## 1 Descriere

Agent,ia Spat,ială Românăs,i-a propus să dezvolte propria ret,ea de satelit,i pentru a observas,i
explora spat,iul. Ret,eaua de satelit,i trebuie realizată sub formă de arbore binar. Satelit,ii se
conectează între ei,s,i există un satelit rădăcină, aproape de atmosfera Pământului, care face
legătura cu tot,i ceilalt,i satelit,i.
Fiecare satelit ce va urma să fie în ret,ea are o frecvent,ă cu care raportează datele. Astfel,
pentru a facilita comunicarea, ne dorim ca satelit,ii care raportează mai des să fie mai aproape
de Pământ, iar satelit,ii care raportează mai rar să se afle la o distant,ă mai mare. Orice legătură
între doi satelit,i are o distant,ă constantă K. Pentru realizarea conexiunii satelit,ilor, se pot folosi
oricât,i satelit,i de legătură va fi necesar. Satelit,ii de legătură sunt menit,i să asigure comunicarea
între satelit,ii principali.
Pentru a asigura conexiunea între satelit,i, se adaugă satelit,i de legătură ori de câte ori este
necesar. Aces,ti satelit,i intermediari sunt responsabili pentru ment,inerea structurii arborelui
binar. Legarea satelit,ilor în ret,ea se face astfel:

1. Se identifică cei doi satelit,i cu cele mai mici frecvent,e de raportare.
2. Se introduce un satelit de legătură ca nod părinte pentru aces,ti doi satelit,i. Frecvent,a de
    raportare a satelitului de legătură este calculată ca suma frecvent,elor celor doi satelit,i
    copil. Numele acestuia este concatenarea dintre numele fiului stangs,i numele fiului drept.
3. Satelitul de legătură este apoi adăugat in Min-Heap, repetând procesul până când tot,i
    satelit,ii sunt legat,i într-un singur arbore binar.

```
Exemplul 1
```
### 4 - B4 7 - A7 7 - C7 12 - D12 16 - E



**1.1 Cerint,a 1**

Primim ca input o listă de satelit,i, fiecare caracterizat printr-un identificator unics,i o frecvent,ă
de raportare a datelor. Să se implementeze o funct,ie care construies,te arborele binar, astfel
încât să se respecte criteriul de organizare: satelit,ii cu frecvent,ă mai mare sunt mai aproape
de rădăcină, iar cei cu frecvent,ă mai mică sunt mai departe. Funct,ia va returna rădăcina
ret,elei de satelit,i. Pentru construirea acestei ret,ele de tip arbore se va folosi o structură de
Min-Heap pentru a extrage, la fiecare pas, satelit,ii cu cele mai mici valori de frecvent,ă de
raportare. Satelitul cu frecvent,a de raportare mai mică va fi fiul stâng al nodului de legătură.
Dacă ambii satelit,i au aceeas,i frecvent,ă de raportare, în partea stângă va fi plasat satelitul al
cărui nume apare primul în ordine alfabetică. Dacă există mai mult,i satelit,i cu aceeas,i frecvent,ă
de raportare, extragerea se va face în ordine alfabetică. Să se afis,eze arborele rezultat pe niveluri.
Informat,ia din nodurile de legătură reprezintă suma timpilor de raportare pentru satelit,ii din
cei 2 subarbori, iar numele este obt,inut prin concatenarea numelor celor 2 noduri copil.

**Format Input:**

Num ̆arul de satelit,i
Frecvent,a_de_raportare_1 Numele_satelitului_ 1
Frecvent,a_de_raportare_2 Numele_satelitului_ 2

## 

## 

## 

## 

Frecvent,a_de_raportare_N Numele_satelitului_N

**Restrict,ii pentru datele de intrare:** Frecvent,a de raportare este un număr întreg. Numele
unui satelit este un s,ir de cel mult 15 caractere.

**Input:**

5
4 B

## 7 X

### 7 C

### 12 D

### 16 E

**Output:**

46-C7B4A7D12E
18-C7B4A7 28-D12E
7-C7 11-B4A7 12-D12 16-E
4-B4 7-A



**1.2 Cerint,a 2**

Agent,ia a recept,ionat un mesaj de la o sursă necunoscută, în codificare binară,s,is,i-au dat
seama că fiecare 0 reprezintă o mis,care la stânga în ret,eaua de satelit,i, iar fiecare valoare de
1 reprezintă o mis,care la dreapta. Astfel,s,i-au dat seama că trebuie să descifreze codificarea
pentru a determina în ce ordine să inspecteze informat,iile colectate de satelit,i. Primim ca input
o secvent,ă de valori 1 s,i 0 s,i trebuie să determinăm satelit,ii codificat,i în secvent,ă.
**Format Input:**

```
Num ̆arul de codific ̆ari
Codificarea
Codificarea
```
## 

## 

## 

## 

```
CodificareaN
Restrict,ii pentru datele de intrare:
```
```
Codificarea este un s,ir de cel mult 1000 caractere.
```
```
Input:
```
## 2 X

### 00010

### 1110011

## Output:

### C7 B

### E16 D12 A

```
Explicat,ie:
00|
11|10|
```
**1.3 Cerint,a 3**

```
Pentru a răspunde la mesaj, au distribuit diferite bucăt,i de informat,ie în anumit,i satelit,i, iar
codificarea trebuie trimisă în acelas,i fel în care a fost primită. Se va citi un număr N de satelit,i
s,i apoi numele acestora. Trebuie să se determine codificarea satelit,ilor în ordinea primită.
Input:
```
```
3
A
D
E
```
```
Output:
```
```
0111011
```
**1.4 Cerint,a 4**

```
Câteodată apar erori de comunicare între anumit,i satelit,is,i atunci trebuie să determinăm satelitul
părinte care face legătura între nodurile respective. Primim ca input o listă cu indicatorii unici
```

ai satelit,ilor care au erori de transmitere de dates,i trebuie să determinăm cel mai apropiat
satelit părinte comun pentru toate acele noduri, pentru a-l repara. Funct,ia trebuie să întoarcă
identificatorul unic al satelitului părinte.

**Format Input:**

Num ̆arul de satelit,i
Numele Satelitului 1
Numele Satelitului 2

Numele Satelitului N

**Input:**

3

## B

### A

### C

**Output:**

C7B4A

**1.5 Cerint,a 5**

Proiectul a fost un success,i agent,ia spat,ială a hotărât să extindăs,i mai mult ret,eaua principală
în următorul mod: Fiecare nod din ret,eaua principală, mai put,in radăcina, poate să fie legat
de nodul rădăcină al unui arbore multicăi. Nodurile din arborele principal stochează acum
s,i o legătură către rădăcina arborelui multicăi. Nodul din arborele multicăi cont,ine, la fel ca
celelalte noduri din arborele principal, o valoare pentru frecvent,a de raportares,i un nume.
Citirea arborelui multicăi se realizează pe nivel.

Să se implementeze o funct,ie care adaugă aceste noduri în ret,eaua principalăs,i o funct,ie care
determină distant,a între două noduri date (oricare dintre nodurile date pot fi din arborele
principal sau din arborele multicăi). Fiecare legătură dintre noduri reprezintă o unitate de
măsură. În figura 2 sunt exemplificate toate cazurile posibile: ambele noduri sunt din arborele
principal, un nod este din arborele principals,i celălalt este dintr-un arbore multicăi, ambele
noduri sunt într-un arbore multicăi sau cele două noduri sunt în arbori multicăi diferit,i. Distant,a
între nodurile albastre este 2. Distant,a între nodurile galbene este 4. Distant,a între nodurile
ros,ii este 11. Distant,a între nodurile verzi este 5.

**Format Input:**

Num ̆arul de arbori ce vor fi ad ̆augat,i
Nume nod din arborele principal de care se leag ̆a r ̆ad ̆acina arborelui
multic ̆ai
R ̆ad ̆acina arborelui multic ̆ai
Num ̆arul noduri p ̆arinte din arborelui multic ̆ai
Nod p ̆arinte
Num ̆arul noduri copil
Frecvent, ̆a_raportare_nod_copil Nume_nod_copil
Nod1 Nod

undeNod1s,iNod2sunt cele două noduri pentru care trebuie să determinăm distant,a.


## Input:

## 56 Y

## 89 X

               - 4 - B4 7 - A
                        - 11 - B4A
- 7 - C7 11 - B4A7 12 - D12 16 - E
            - 7 - C7 11 - B4A
                  - 18 - C7B4A
      - 12 - D12 16 - E16 18 - C7B4A
         - 12 - D12 16 - E
                     - 28 - D12E
   - 18 - C7B4A7 28 - D12E
- Figure 1: Arborele final pentru Exemplul
-
- B
- 12 Y
-
- Y
-
- 5 Y
- 63 Y
- 6 YU
- 1 Y
- Y
-
- 94 Y
- 144 Y
- YU
-
- 56 Y
- D
- 5 X
-
- X
-
- 36 X
- 7 X
- 92 X
- X
-
- 8 X
- 2 X
- 89 X
- Y6 X
- Output:


Figure 2: Exemplu de arbore pentru exercit

iul 5,


**2 Instruct,iuni pentru predarea temelor**

Temele trebuie să fie încărcate atât pe checker-ul automat, cât s,i pe Moodle, la sect,iunea
corespunzătoare. NU se acceptă teme trimise pe e-mail sau prin alt mijloc decât Moodle.

```
O rezolvare constă într-o arhivă de tip .zip care cont,ine toate fis,ierele sursă, alături de un
Makefile, care va fi folosit pentru compilare,s,i un fis,ier README, în care se vor preciza detaliile
implementării. Makefile-ul trebuie să cont,ină obligatoriu regulile builds,i clean. Regula build
trebuie să aibă ca efect compilarea surselor s,i crearea binarului tema2.
```
```
Programul vostru va primi, ca argumente în linia de comandă, numele fis,ierului de intrares,i al
celui de ies,ire, dar s,i o opt,iune, în felul următor:
./tema2 [-c1 |-c2 |-c3 |-c4 |-c5] [fis,ier_intrare] [fis,ier_ies,ire]
```
- c1 indică faptul că programul va rezolva cerint,a 1;
- c2 indică faptul că programul va rezolva cerint,a 2;
- c3 indică faptul că programul va rezolva cerint,a 3;
- c4 indică faptul că programul va rezolva cerint,a 4;
- c5 indică faptul că programul va rezolva cerint,a 5;
- fis,ier_intrare reprezintă numele fis,ierului de intrare;
- fis,ier_ies,ire reprezintă numele fis,ierului de ies,ire, în care se va scrie, în funct,ie de comanda
    primită, rezultatul execut,iei programului.

**3 Punctaj**

O temă cu toate cerint,ele de bază rezolvate corect valorează 100 de puncte. 95 de puncte se
vor acorda pentru testes,i 5 puncte pentru README. În urma corectării manuale, punctajul
acordat de checker-ul automat poate fi scăzut cu maxim 15 puncte pentru coding style. De
asemenea, cont,inutul fis,ierului README va fi verificat manual, iar punctajul obt,inut pentru
README poate fi diminuat. Punctajul pe teste este următorul:

```
Cerinta Punctaj
Cerint,a 1 30 puncte
Cerint,a 2 20 puncte
Cerint,a 3 20 puncte
Cerint,a 4 25 puncte
README 5 puncte
BONUS Cerint,a 5 20 puncte
```
```
Atent,ie!
```
```
Orice rezolvare care nu cont,ine structurile de date specificate NU este punctată.
Temele vor fi punctate doar pentru testele care sunt trecute pe vmchecker.
Nu lăsat,i warning-urile nerezolvate, deoarece vet,i fi depunctat,i.
Tema este individuală! Toate solut,iile trimise vor fi verificate, folosind
o unealtă pentru detectarea plagiatului.
```

