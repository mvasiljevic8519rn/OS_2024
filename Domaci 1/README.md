<a name="_heading=h.gjdgxs"></a>OS2024 - Domaći 1

Istorija unosa

Cilj domaćeg zadatka je izmeniti xv6 sistem tako da podržava istoriju unosa, omogućavajući korisnicima da pregledaju i ponovo koriste prethodno unete komande. Završen domaći treba da sadrži sledeće funkcionalnosti:

- Prikazivanje prethodno unetih komandi.
- Navigacija kroz istoriju unosa.
- Izbor i izvršavanje prethodno unetih komandi.

Od velike je važnosti da ova nova funkcionalnost ne naruši trenutni rad sistema. Pazite da odabir bilo koje prethodne komande, kao i njeno izvršavanje ne dovede do rušenja sistema.

Nova funkcionalnost treba da bude integrisana sa postojećim sistemom na način koji ne remeti osnovne funkcije i performanse sistema.

Na materijalima postoji snimak koji demonstrira kako izgleda rad sistema sa urađenim zadatkom.

Kod koji treba koristiti kao polaznu tačku za domaći zadatak dobija se tako što prihvatite zadatak na Github Classroom-u.


# Predaja i rokovi

Zadatak se predaje putem GitHub Classroom-a. 

Rok za izradu je:

- Ponedeljak, 25. mart 23:59:59 za grupe koje slušaju OS vežbe ponedeljkom
- Utorak, 26. mart 23:59:59 za grupe koje slušaju OS vežbe utorkom
- Sreda, 27. mart 23:59:59 za grupe koje slušaju OS vežbe sredom
- Petak, 29. mart 23:59:59 za grupe koje slušaju OS vežbe petkom
- Rok za ponovce je rok poslednjeg (četvrtog) domaćeg zadatka

Neće se pregledati zadaci (tj. biće dodeljeno 0 poena) ako se desi bilo koje od:

- Kod se ne kompajluje.
- Kod nije uredno uvučen.
- Predaja se desi nakon navedenog roka.

Rok je definisan po grupi kojoj student zvanično pripada. Studenti koju slušaju vežbe van svog termina i dalje moraju da poštuju termine na osnovu zvaničnog spiska.

Odbrana domaćih zadataka je obavezna. Termin za odbranu prvog domaćeg zadatka će biti naknadno poslat mejlom. Odbrane će se vršiti po grupama. Grupe će biti formirane i objavljene. Ako ste iz bilo kog razloga sprečeni da prisustvujete odbrani, obavezno to najavite što pre, kako bismo mogli da zakažemo vanredni termin za odbranu. 

Svrha odbrane je da se pokaže autentičnost zadatka. Ovo podrazumeva odgovaranje na pitanja u vezi načina izrade zadatka, ili izvršavanje neke izmene nad zadatkom na licu mesta. U slučaju da odbrana nije uspešna, zadatak se boduje sa -5 bodova umesto namenjenog broja bodova.



Napomena: 


Za studente koji predmet ne slušaju prvi put, zadatak se predaje putem mejla: <estojanovic@raf.rs>, <aarsenovic@raf.rs>, <dtisma@raf.rs> ili <vkovinic@raf.rs>. Obavezno izvršite komandu  `make clean` kako biste uklonili izvršni kod. 

Projekat imenovati na sledeći način: 

“os\_d1\_ime\_prezime\_ind” 

primer. “os\_d1\_student\_studentic\_rn0101”

Potom arhivirati ovaj direktorijum (.zip) i arhivu poslati kao attachment uz mejl ili kao link ka drajvu na kojem se nalazi arhiva.

U tekstu mejla obavezno navesti ime, prezime i broj indeksa. 

Subject mejla mora da bude u obliku: “[OS 2024] D1 ime\_prezime\_ind”. 

primer. “[OS 2024] D1 student\_studentic\_rn0101”

Naziv arhive mora da bude u obliku: “os\_d1\_ime\_prezime\_ind.zip”

primer. “os\_d1\_student\_studentic\_rn0101.zip”

Neće se pregledati zadaci (tj. biće dodeljeno 0 poena) ako se desi bilo koje od:

- Kod se ne kompajluje.
- Kod nije uredno uvučen.
- Predaja se desi nakon navedenog roka.
- Sadržaj mejla nije po navedenom obliku.
- Subject mejla nije po navedenom obliku.
- Naziv arhive nije po navedenom obliku.


# Github Classroom
Prvo, posetite link <https://classroom.github.com/a/iUiyMWYQ> kako biste pristupili GitHub Classroom-u za OS.

Ako nemate nalog na GitHub-u, morate ga napraviti. Ako već imate nalog, prijavite se na GitHub sa Vašim postojećim nalogom.

Nakon što prihvatite zadatak, GitHub će automatski kreirati repozitorijum za Vas sa odgovarajućim imenom i postavkama za zadatak.

Da biste radili na zadatku, morate klonirati repozitorijum na svoj lokalni računar. To možete uraditi koristeći komandu git clone  u terminalu sa linkom do Vašeg repozitorijuma.

Ako dobijete grešku o autentikaciji, proverite da li ste autentikovani na GitHub za svrhe Git komandne linije. U priloženoj virtuelnoj mašini postoji uputstvo za autentikaciju u README.html fajlu.

Nakon što klonirate repozitorijum, možete početi da radite na zadatku lokalno na svom računaru.

Kada završite sa izmenama, odradite komandu  git add . da dodate sve izmene, a potom git commit -m "Opis izmena" da ih komitujete na lokalni repozitorijum.

Nakon dodavanja izmena komandom git add ., korisno je proveriti status repozitorijuma komandom git status kako biste bili sigurni da su sve izmene uspešno dodate.

Kada ste spremni da otpremite izmene na GitHub, koristite komandu git push da ih otpremite na GitHub.

Nakon što otpremite izmene, možete ih pregledati na GitHub-u da biste se uverili da su ispravne. 

Važno je da pratite uputstva i da se javite mejlom ako imate pitanja ili probleme, kako bismo mogli na vreme da ih uklonimo.



# <a name="_heading=h.1fob9te"></a>Rad sa istorijom unosa
<a name="_heading=h.2et92p0"></a>Istorija unosa treba da sačuva poslednje **3** **izvršene komande** (komanda se računa kao izvršena kada se pritisne **ENTER** ili kada se samo izvršila jer je bafer bio pun, čak iako je komanda imala grešku ili nije bila uspešna, i dalje se smatra izvršenom i treba je sačuvati u istoriji unosa). 

<a name="_heading=h.vhhf3yw2xrv9"></a> 

<a name="_heading=h.v94l626ds0yv"></a>Kroz istoriju unosa se krećemo kombinacijom karaktera **SHIFT + ARROW\_UP** i **SHIFT + ARROW\_DOWN** (nijedna druga kombinacija sa ARROW\_UP i ARROW\_DOWN ne treba da radi prolazak kroz istoriju unosa). U istoriju unosa se ulazi kad kliknemo shift i  nagore. Ako pre ulaska u istoriju kliknemo shift i nadole, ništa se neće desiti. Kada se krećemo nagore, prikazuju se “dalje” (starije) komande, a kad se krećemo nadole prikazuju se “skorije” komande. Ako nastavimo da se krećemo nadole, izaći ćemo iz istorije unosa.

<a name="_heading=h.jn70ezc6rtm0"></a>Komande iz istorije se ispisuju zelenom bojom i obratite pažnju da **prazne komande** **ne čuvamo** u istoriji. Komande koje smo sačuvali u istoriji takođe treba da mogu da se izvrše nakon što ih odaberemo iz istorije.

<a name="_heading=h.ahveq091sxuh"></a><a name="_heading=h.vd6e0bdyv04o"></a>Na komandu iz istorije takođe možemo dodati još karaktera i oni će se ispisivati belom bojom. (slika 1)



|![](Aspose.Words.d829a16c-f039-48cf-83d5-ef47d5ecd223.001.png)|
| :-: |
|<a name="_heading=h.5b52x3by9qxw"></a><a name="_heading=h.qpgp0boqumjs"></a>*Slika 1 - Na komandu iz istorije možemo dodavati još karaktera* |

<a name="_heading=h.1sbmc9ntjhp5"></a><a name="_heading=h.4qet0p91304d"></a>Ako je korisnik kucao nešto pre ulaska u istoriju unosa, i zatim je listao kroz istoriju, kad je stigao do poslednje i komandom nadole izašao iz istorije, tekst koji je kucao pre ulaska u istoriju će biti obrisan. (ova funkcionalnost ne treba da utiče na samu istoriju unosa, već samo na tekst koji je korisnik kucao pre ulaska u istoriju - ne briše se istorija, već tekst iskucan pre ulaska u istoriju unosa, ukoliko ga je bilo) 


# <a name="_heading=h.8kfcakmxanwj"></a><a name="_heading=h.p7p0wz22te6p"></a>Bodovanje
Zadatak se boduje na sledeći način:

- Čuvanje, prikaz i listanje komandi                 = 7 bodova
- Pravilno ažuriranje istorije unosa           	 = 2 boda
- Komande mogu da se izvrše              	 = 6 bodova

U slučaju da je neka od stavki implementirana parcijalno, biće dodeljeni parcijalni poeni (potrebno je demonstrirati da taj parcijalni deo zaista radi).



