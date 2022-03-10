# Tema3-Image-Processing
Ultima temă de la PCLP (Programarea Calculatoarelor și Limbaje de Programare), Anul I, Semestrul I, punctaj maxim

# Introducere
Procesarea de imagini se refera la aplicarea unor algoritmi specifici pe continutul unei imagini pentru a obtine anumite efecte (blur, sharpening, etc.) sau rezultate (face detection/recognition, etc.). In aceasta tema vom lucra cu unul dintre cele mai simple formate de imagini si anume formatul BMP.

O imagine BMP are următoarea structură:

un File Header care are următoarele câmpuri:

signature – 2 octeți - literele 'B' și 'M' în ASCII;

file size – 4 octeți – dimensiunea întregului fișier;

reserved – 4 octeți – nefolosit;

offset – 4 octeți – offsetul de la începutul fișierului până la începutului bitmap-ului, adica al matricii de pixeli.

un Info Header care poate avea structuri diferite, însă noi vom lucra cu cel care se numește BITMAPINFOHEADER. Are următoarele câmpuri:

size – 4 octeți – dimensiunea Info Header-ului, care are o valoare fixă, 40;
width – 4 octeți – lățimea matricii de pixeli (numărul de coloane);
height – 4 octeți – înălțimea matricii de pixeli (numărul de rânduri);
planes – 2 octeți – setat la valoarea fixă 1;
bit count – 2 octeți – numărul de biți per pixel. În cazul nostru va avea mereu valoarea 24, adică reprezentăm fiecare pixel pe 3 octeți, adică cele 3 canale, RGB;
compression – 4 octeți – tipul de compresie. Acest câmp va fi 0;
image size – 4 octeți – se referă la dimensiunea matricii de pixeli, inclusiv padding-ul adăugat (vedeți mai jos);
x pixels per meter – 4 octeți – se referă la rezoluția de printare. Pentru a simplifica puțin tema, veți seta acest câmp pe 0. Nu o să printăm imaginile.
y pixels per meter – la fel ca mai sus;

colors used – numărul de culori din paleta de culori. Aceasta este o secțiune care va lipsi din imaginile noastre BMP, deoarece ea se află în general imediat după Info Header însă doar pentru imaginile care au câmpul bit count mai mic sau egal cu 8. Prin urmare, câmpul va fi setat pe 0;

colors important – numărul de culori importante. Va fi, de asemenea, setat pe 0, ceea ce înseamnă că toate culorile sunt importante.

BitMap-ul, care este matricea de pixeli și care ocupă cea mai mare parte din fișier. Trei lucruri trebuiesc menționate despre aceasta:
pixelii propriu-ziși se află într-o matrice de dimensiune height x width, însă ea poate avea o dimensiune mai mare de atât din cauza paddingului. Acest padding este adăugat la sfârșitul fiecărei linii astfel încat fiecare linie să înceapă de la o adresă (offset față de începutul fișierului) multiplu de 4. Mare atenție la citire, pentru că acest padding trebuie ignorat (fseek). De asemenea, la scriere va trebui să puneți explicit valoarea 0 pe toți octeții de padding.
este răsturnată, ceea ce înseamnă că prima linie în matrice conține de fapt pixelii din extremitatea de jos a imaginii. Vedeți exemplul de mai jos;
canelele pentru fiecare pixel sunt în ordinea BGR (Blue Green Red).

# Task 0 - Interactive Console
Se va implementa un parser al liniei de comandă pentru a putea lucra interactiv cu transformările descrise în cerințele de mai jos și pentru a putea vedea la fiecare pas output-ul rezultat. Programul scris va citi în continuu de la standard input și va putea primi următoarele comenzi.

save <path>
edit <path>
insert <path> y x
set draw_color R G B
set line_width x
draw line y1 x1 y2 x2
draw rectangle y1 x1 width height
draw triangle y1 x1 y2 x2 y3 x3
fill y x
quit

# Task 1 - Basic Commands
Pentru acest task vom implementa primele doua operatii de baza necesare unui editor de imagini:

edit <path> - Incarcă imaginea în memoria aplicației pentru a fi editată
save <path> - Salveaza/suprascrie imaginea din edit mode in calea path.
quit - dezaloca memoria si inchide programul
  
# Task 2 - Overlap Images
Pentru acest task vom implementa următoarele doua operații:

insert <path> y x - Inserează imaginea (toata sau cropped) de la path peste cea din modul edit.
  
# Task 3 - Draw Lines
Pentru acest task vom implementa următoarele cinci operații:

set draw_color R G B - Va seta o culoare ce va fi folosită ori pentru a desena ori pentru a umple o zonă.
set line_width x - Va seta dimensiuni creionului cu care vom desena liniile.
draw line y1 x1 y2 x2
draw rectangle y1 x1 width height
draw triangle y1 x1 y2 x2 y3 x3
R G B au valori intre 0 și 255, valoarea default este 0 0 0
x are valori impare intre 1 si 255, valoarea default este 1

La desenarea cu un line_width diferit de 1, pixelul principal va fi incadrat intr-un patrat de latura x
Exemplu:



Pentru line_width = 3, pixelul principal este cel de culoare verde. La desenare, atat pixelul principal, cat si pixelii ce formeaza patratul(si interiorul lui) vor primi culoarea setata.

Pentru trasarea liniilor ce unesc doua puncte ce nu sunt paralele cu Ox sau Oy, se va folosi o functie de gradul I cu formula
(y - yA) / (yB - yA) = (x - xA) / (xB - xA).

Se stabileste pe ce axa se afla intervalul maxim (x max - x min) sau (y max - y min).

Se va parcurge de la minim la maxim intervalul de lungime maxima [x min, x max] sau [y min, y max] si pe baza formulei calculate PE INTREGI se afla a doua coordonata a punctului desenat.

Exemplu:
Pentru punctele (1, 1) si (2, 5), intervalul mai mare este cel de pe axa Oy.

Deci formula prin care vom afla x-ul corespunzator fiecarui y din intervalul [1, 5] este x = (y + 3) / 4.

y = 1 → x = 1

y = 2 → x = 1

y = 3 → x = 1

y = 4 → x = 1

y = 5 → x = 2

Pentru a evita erorile de rotunjire, punctele initiale primite ca parametru se vor desena indiferent de rezultatul functiei.

Daca intervalele sunt egale, atunci dreapta rezultata este de forma f(x) = x + C sau f(x) = -x + C, unde nu conteaza modul in care va fi desenata linia.
  
# Task 4 - Fill color
Pentru acest task vom implementa operația finală:

fill y x
În urma operației, pixelul de la pozitia (y, x) va fi suprascris cu pixeli setati prin comanda set draw_color R G B. Operația va fi repetată recursiv pentru toți vecinii acestuia (stânga, dreapta, sus, jos) care aveau aceeași culoare cu pixelul original din (y, x).

Dacă pixelul original avea tot culoarea (r, g, b), operația nu produce nici un efect.

Exemplu

Imaginea Originală:

(0, 0, 255) (10, 10, 10) (255, 0, 0)    (10, 10, 10)
(10, 10, 10) (0, 255, 0) (10, 10, 10)  (10, 10, 10)
(10, 10, 10) (10, 10, 10) (10, 10, 10) (10, 15, 10)
Instrucțiunea:

set draw_color 42 42 42
fill_color 1 2
În urma aplicării operației, toți vecinii accesibili din poziția (1, 2), având culoarea (10, 10, 10), au fost suprascriși cu un pixel de valoarea (42, 42, 42). Pixelul de pe poziția (0, 1) a rămas neschimbat.

Imaginea Obținută:

(0, 0, 255)  (10, 10, 10)  (255, 0, 0)  (42, 42, 42)
(42, 42, 42) (0, 255, 0)  (42, 42, 42) (42, 42, 42)
(42, 42, 42) (42, 42, 42) (42, 42, 42) (10, 15, 10)
  
# Task 5 - Clean Valgrind BONUS
Intrucat unul din scopurile principale ale acestei teme este alocarea dinamica a memoriei, pentru a rezolva acest task trebuie sa nu aveti nicio eroare sau leak de memorie la rularea utilitarului valgrind pe aceasta.

Utilitarul se va rula folosind urmatoarea comanda:

 valgrind --tool=memcheck --leak-check=full --error-exitcode=1 ./bmp < input_file 
