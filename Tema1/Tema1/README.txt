Oprea Olivia 333CA Tema1

----------Informatii----------
Pentru informatii suplimentare pentru fiecare functie din tema exista comentariu
deasupra fiecareia cu ceea ce doreste sa implementeze in caz de ratez ceva aici +
explicatii suplimentare.

----------Tema1Obj2D----------
Aici am functiile care ma ajuta sa imi creez: dreptunghiul, triunghiul, steaua,
arcul, baloanele, cercul, liniile.

----------Tema1Transform2D----------
Aici am functiile de translate, scale si rotate facute conform laboratoarelor.

----------Tema1----------
***Tema1() -> initializez variabilele

***Init() -> imi creez obiectele pe care le voi folosii pentru realizarea jocului.
Imi creez sageata = triunghi + dreptunghi, arcul, balonul rosu si galben = balon +
triunghi + sfoara (linie), steaua, bara de putere si de scor = dreptunghi, cercurile
pentru viata, arcasul = cerc + linii (maini si picioare si corp)

***FrameStart() -> imi schimb fundalul in functie de ce tinta am nimerit. Daca nimeresc
un balon rosu sau o stea avem o culoare deschisa, iar daca nimeresc balonul galben sau 
steluta pe arcas fundalul se schimba la o culoare inchisa.

***Update() -> 
- Imi pun in scena arcasul si partile corpului la locul lor si ma asigur ca 
mainile se misca o data cu arcul si de asemenea arcasul merge pe axa OY.
- Imi pun in scena arcul care se poate rotii dupa mouse si deplasa pe axa OY.
- Imi pun in scena sageata care se misca dupa arc.
- O data ce am pus in scena baloanele (dupa ce le-am construit ca sa arate a balon)
verific coliziunea dintre sageata si baloane si cresc si scad scorul in functie de
culoarea balonului. Baloanele se pot deplasa pe OY si apar la baza scenei si dispar
o data ce ies din scena pentru a reaparea random din nou la baza scenei. De asemenea,
o data lovite acestea scaleaza de la 1 la 0 urmand sa reapara la baza scenei.
- Am creat steaua din 2 triunghiuri si imaginea lor in oglinda ca sa arate ca o stea.
Tot aici verific coliziunea cu sageata sau cu aracasul. Daca am lovit arcasul o sa
imi scada din viata, iar la 3 vieti pierdute jocul se inchide. De asemenea o stea
lovita v-a scala de la 1 la 0. Daca steau loveste varful sagetii si cand aceasta e 
inca in arc o sa o ia ca coliziune arc-steluta si nu imi fura din viata.
- Am creat power bar si scor bar pe aceelasi principiu. Un dreptunghi incadrator si
un dreptunghi care scaleaza pe OY. Cel de la scor bar scaleaza cu scorul, iar cel de
la power bar scaleaza cu puterea cu care am tinut apasat mouse-ul.
- Cercurile de viata scaleaza de la 1 la 0 o data ce le pierd.
- Tot in aceasta functie resetez coordonatele sagetii si scalarile obiectelor ca sa
reapara cand vreau sa trag o noua sageata. Daca mai am o viata o sa imi apara un cerc
de viata ca sa pot sa imi cresc viata. Daca scorul trece de 1000 jocul se termina.

***OnImputUpdate() ->
- Am setarea coordonatelor arcului pentru a se putea deplasa pe OY.
- Coordonatele balonului pentru a se deplasa pe OY si pentru a reveni random
pe OX atunci cand iese din scena.
- Coordonatele stelutei pentru a se putea rotii in jurul centrului si pentru a aparea
random pe OY si a se deplasa pe axa OX.
- De asemenea updatez si pozitile cercurilor de viata.
- Cel mai important am functia de cat de mult am tinut mouse-ul apasat si val maxima.

***OnMouseMove() -> aici este calculata rotatia cu care se misca arcul dupa mouse.

***OnMouseBtnRelase() -> aici setez ca am dat drumul la mouse.

----------Bonus----------
- am pus un arcas in scena
- am pus alt obiect in plus in scena (acea viata bonus pentru a o creste)
- nush daca se pune ca imi scaleaza obiectele tinta :)