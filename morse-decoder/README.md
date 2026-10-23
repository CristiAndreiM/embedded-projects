Morse Decoder

Un proiect mic de Arduino: apăs un buton și programul îmi spune ce literă am scris în cod Morse.

L-am făcut ca să învăț arbori binari și template-uri în C++. Codurile Morse sunt ținute într-un arbore: punctul merge la stânga, liniuța la dreapta, iar litera stă în nodul în care ajungi. De exemplu .- înseamnă stânga, apoi dreapta, adică A.

Cum se folosește
apăsare scurtă = punct, apăsare lungă = liniuță (pragul e 300 ms)
după 1,5 secunde fără apăsări, litera se decodează
după 4 secunde, se afișează tot cuvântul
totul se vede în Serial Monitor, la 9600 baud
Montaj
buton pe pinul 2 (citește 1 când e apăsat, 0 când nu)
LED pe pinul 12 (la mine se aprinde pe LOW)
Fișiere
morse-decoder.ino - butonul, măsurarea timpului și afișarea
BinaryTree.h - arborele binar

Timpii (debounce, prag punct/liniuță, pauzele) sunt constante la începutul fișierului .ino, deci se pot regla după cum apasă fiecare.

Ce am învățat

Am pierdut destul timp pe un bug: logica butonului era inversată față de cum îl legasem. Am rezolvat afișând valoarea brută cu digitalRead în Serial Monitor.

De făcut
coduri citite de pe card SD
sens invers: text în Morse, cu LED sau buzzer
