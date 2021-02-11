Oprea Olivia Maria-Magdalena 333CA

----------Tema2.cpp & Tema2.h----------

Am furat sfera si box-ul din primitivele date de voi :)
Pentru inceput mi-am setat o linie de 3 platforme initiale.
Acestea au x = -2 0 sau 2, y este constant, iar z este random (nu pentru primele platforme).
De aceea tin minte mereu cel mai mare z pentru a stii care este cea mai lunga platforma de la 
care voi incepe sa generez urmatorul rand de platforme, asa evitand sa se intercaleze intre ele.
Am 2 tipuri de shadere (ambele luate initial din laborator apoi modificate): unul pentru sfera
ce contine si deformarea acesteia cu zgomot si unul pentru placi si orice alt obiect folosit.
RenderMesh si RenderSimpleMesh sunt luate de asemenea din laborator, dar pe ultima am modificat-o
pentru a primi ca parametru si o culoare ca sa pot colora placile si celelalte obiecte cum vreau eu.

Pentru sfera initial are un shader normal, iar daca pica pe verde primeste shader-ul care contine si
functia de noise ca sa se deformeze.
Imi generez un anumit numar de platforme si cu acestea voi lucra tot jocul. O data ce platformele nu se
mai vad in camera acestea se repozitioneaza in fata de tot pentru a genera o harta continua. Culoarea
platformelor este facuta random printr-o functie a mea myRandomColor care genereaza culori random ca mai
apoi sa le pot da placilor. De asemenea placile sunt generate si acestea random tot cu o functie a mea
addPlatforme.
Pentru coliziuni am verificat daca bila se afla pe platforma si daca da am aplicat avantajele si dezavantajele
pentru fiecare placa si am schimbat culoarea lor in mov.

Combustibilul si bara de viteze sunt create in aceelasi mod. Combustibilul scade in timp, iar bara de viteze ne
arata ce viteza avem.
Am luat si o idee de la o colega care mi-a placut foarte mult. Atunci cand am picat pe placa portocalie care ma 
blocheaza la o anumita viteza fundalul meu devine si el foarte colorat. Acesta este format dintr-o sfera foarte mare
trimisa foarte in spate dar arata prea frumos.

SRERA SE DEFORMEAZA NUMAI PE VERDE CA NUMAI VERDE ESTE POWER UP SI TU(LABORANTUL) AI ZIS CA ASA E :) pentru asigurare.

Am facut si bonnusul cu viata si pierd viata pe platforma gri si castig viata pe cea turcoaz, dar pierd viata pe cand
nu mai am combustibil.

----------Tema2_Transform3D.h----------

Contine functile de translate, scale si rotate pentru un obiect 3D.
Luat din laboratoare :)

----------Tema2_Camera.h----------

Contine functile pentru a genera camera in care se desfasoara jocul, pozitionarea ei,
updatarea si sincer si alte functii pe care nu le-am folosit, dar nu le-am mai sters.
Luat din laboratoare.

----------Tema2_Platforma.h----------

In aceasta functie am get-eri si set-eri pentru placile mele si de asemenea setarea
starii initiale a unei placi pentru a imi usura generarea lor cu ajutorul unui vector

----------BONUS----------
- am facut vieti si platforme si chestii
- sare mingea destul de real (zic eu) nush daca se pune
