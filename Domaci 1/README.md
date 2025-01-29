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

