<a name="_heading=h.gjdgxs"></a>OS2024 - Domaći 2

Simbolične veze i disk usage

Cilj domaćeg zadatka je izmeniti xv6 sistem tako da podržava simboličke veze. Simboličke veze se odnose na povezanu datoteku putem putanje. Kada se simbolička veza otvori, prati se veza do navedene datoteke. Završen domaći treba da sadrži sledeće funkcionalnosti:

- Sistemski poziv:
  - symlink(dest, link) - kreira simbolični link link koji pokazuje na dest
- Korisničke programe: 
  - sln - Symbolic Link (ln -s)
  - symlinkinfo
  - du (disk usage)
- Flag  O\_NOFOLLOW za open()
- Polje blocks u stat strukturi
- Ispis istog u izlazu ls-a


Od velike je važnosti da ova nova funkcionalnost ne naruši trenutni rad sistema. 

Nova funkcionalnost treba da bude integrisana sa postojećim sistemom na način koji ne remeti osnovne funkcije i performanse sistema.

Na materijalima postoji snimak koji demonstrira kako izgleda rad sistema sa urađenim zadatkom.

Kod koji treba koristiti kao polaznu tačku za domaći zadatak dobija se tako što prihvatite zadatak na Github Classroom-u u zavisnosti od grupe.


# Predaja i rokovi

Ukoliko prvi put slušate predmet, zadatak se predaje putem GitHub Classroom-a. 

Rok za izradu je:

- Ponedeljak, 8. april 23:59:59 za grupe koje slušaju OS vežbe ponedeljkom
- Utorak, 9. april 23:59:59 za grupe koje slušaju OS vežbe utorkom
- Sreda, 10. april 23:59:59 za grupe koje slušaju OS vežbe sredom
- Petak, 12.april 23:59:59 za grupu 201
- Rok za ponovce je rok poslednjeg (četvrtog) domaćeg zadatka

Neće se pregledati zadaci (tj. biće dodeljeno 0 poena) ako se desi bilo koje od:

- Kod se ne kompajluje.
- Kod nije uredno uvučen.
- Predaja se desi nakon navedenog roka.
- Ukoliko student nije u tačnoj Github učionici koja je definisana po roku predaje.

Rok je definisan po grupi kojoj student zvanično pripada. Studenti koju slušaju vežbe van svog termina i dalje moraju da poštuju termine na osnovu zvaničnog spiska.

Odbrana domaćih zadataka je obavezna. Termin za odbranu prvog domaćeg zadatka će biti naknadno poslat mejlom. Odbrane će se vršiti po grupama. Grupe će biti formirane i objavljene. Ako ste iz bilo kog razloga sprečeni da prisustvujete odbrani, obavezno to najavite što pre, kako bismo mogli da zakažemo vanredni termin za odbranu. 

Svrha odbrane je da se pokaže autentičnost zadatka. Ovo podrazumeva odgovaranje na pitanja u vezi načina izrade zadatka, ili izvršavanje neke izmene nad zadatkom na licu mesta. U slučaju da odbrana nije uspešna, zadatak se boduje sa -5 bodova umesto namenjenog broja bodova.



Link za Github korisnička imena: <https://forms.gle/GrQvNZFhPrR82DxM8> 



Napomena: 


Za studente koji predmet ne slušaju prvi put, zadatak se predaje putem mejla: <estojanovic@raf.rs>, <aarsenovic@raf.rs>, <dtisma@raf.rs> ili <vkovinic@raf.rs>. Obavezno izvršite komandu  `make clean` kako biste uklonili izvršni kod. 

Projekat imenovati na sledeći način: 

“os\_d2\_ime\_prezime\_ind” 

primer. “os\_d2\_student\_studentic\_rn0101”

Potom arhivirati ovaj direktorijum (.zip) i arhivu poslati kao attachment uz mejl ili kao link ka drajvu na kojem se nalazi arhiva.

U tekstu mejla obavezno navesti ime, prezime i broj indeksa. 

Subject mejla mora da bude u obliku: “[OS 2024] D2 ime\_prezime\_ind”. 

primer. “[OS 2024] D2 student\_studentic\_rn0101”

Naziv arhive mora da bude u obliku: “os\_d2\_ime\_prezime\_ind.zip”

primer. “os\_d2\_student\_studentic\_rn0101.zip”

Neće se pregledati zadaci (tj. biće dodeljeno 0 poena) ako se desi bilo koje od:

- Kod se ne kompajluje.
- Kod nije uredno uvučen.
- Predaja se desi nakon navedenog roka.
- Sadržaj mejla nije po navedenom obliku.
- Subject mejla nije po navedenom obliku.
- Naziv arhive nije po navedenom obliku.


# Github Classroom
Prvo, posetite link u zavisnosti od grupe kako biste pristupili GitHub Classroom-u za OS:

- 205 <https://classroom.github.com/a/xJzdcgjb> 
- 202 i 203 <https://classroom.github.com/a/dgHbPfoD>
- 204 i 206 <https://classroom.github.com/a/jc2SLbL6>
- 201 <https://classroom.github.com/a/UoNznjRd> 

Ponovci mogu da preuzmu kod sa bilo koje učionice. 

Ako nemate nalog na GitHub-u, morate ga napraviti. Ako već imate nalog, prijavite se na GitHub sa Vašim postojećim nalogom.

Nakon što prihvatite zadatak, GitHub će automatski kreirati repozitorijum za Vas sa odgovarajućim imenom i postavkama za zadatak. Ovaj repozitorijum možete koristiti na bilo koji način koji smatrate adekvatnim, uključujući force push i ostale konvencionalno shvaćene kao “opasne” operacije.

Da biste radili na zadatku, morate klonirati repozitorijum na svoj lokalni računar. To možete uraditi koristeći komandu git clone  u terminalu sa linkom do Vašeg repozitorijuma.

Ako dobijete grešku o autentikaciji, proverite da li ste autentikovani na GitHub za svrhe Git komandne linije. U priloženoj virtuelnoj mašini postoji uputstvo za autentikaciju u README.html fajlu.

Nakon što klonirate repozitorijum, možete početi da radite na zadatku lokalno na svom računaru.

Kada završite sa izmenama, odradite komandu  git add . da dodate sve izmene, a potom git commit -m "Opis izmena" da ih komitujete na lokalni repozitorijum.

Nakon dodavanja izmena komandom git add ., korisno je proveriti status repozitorijuma komandom git status kako biste bili sigurni da su sve izmene uspešno dodate.

Kada ste spremni da otpremite izmene na GitHub, koristite komandu git push da ih otpremite na GitHub.

Nakon što otpremite izmene, možete ih pregledati na GitHub-u da biste se uverili da su ispravne. 

Važno je da pratite uputstva i da se javite mejlom ako imate pitanja ili probleme, kako bismo mogli na vreme da ih uklonimo.
# <a name="_heading=h.1fob9te"></a>Izmena sistema datoteka
<a name="_heading=h.2et92p0"></a>Da bismo implementirali simboličke veze, potrebno je izvršiti sledeće izmene u sistemu datoteka:

<a name="_heading=h.wbv073mjare"></a><a name="_heading=h.zclho9pt8c7o"></a>**Dodavanje novog tipa datoteke**: U kernel/stat.h, dodajte novi tip datoteke T\_SYMLINK koji će predstavljati simboličke veze.

<a name="_heading=h.nx4g0exst1z7"></a><a name="_heading=h.q0fk76yrl0r9"></a>**Dodavanje novog flega**: U kernel/fcntl.h, dodajte novi flag O\_NOFOLLOW. Ovaj flag se koristi zajedno sa sistemskim pozivom open kako bi se sprečilo automatsko praćenje simboličkih veza prilikom otvaranja datoteke. Kada se open pozove sa O\_NOFOLLOW flagom, simbolička veza se otvara kao obična datoteka, bez praćenja do ciljne datoteke na koju veza upućuje.

<a name="_heading=h.20qg89djiaf1"></a><a name="_heading=h.78ichpb15x9u"></a>**Izmena sistema poziva open**: Modifikujte sistemski poziv open tako da može da prati simboličke veze. Ako je datoteka tipa T\_SYMLINK, sistem bi trebalo da prati putanju do ciljne datoteke i otvori je. Takođe, potrebno je sprečiti promene nad simboličkim linkovima koristeći write sistemski poziv, i sprečiti otvaranje za pisanje.

<a name="_heading=h.wo9jeeit3ssq"></a><a name="_heading=h.feaep0syxb4j"></a>**Detekcija ciklusa**: Kako biste sprečili beskonačno praćenje simboličkih veza koje formiraju ciklus, potrebno je implementirati mehanizam za detekciju ciklusa. Ovo se postiže rekurzivnim praćenjem simboličkih veza do trenutka kada se dostigne datoteka koja nije simbolička veza. Ako se tokom praćenja naiđe na simboličku vezu koja upućuje na prethodno posećenu vezu, formiran je ciklus. Da biste izbegli beskonačnu rekurziju, ograničite dubinu praćenja na određeni prag (na primer, 10). Ako se dostigne ovaj prag bez pronalaska krajnje datoteke, pretpostavlja se da postoji ciklus i treba vratiti odgovarajući kod greške. Ovaj pristup osigurava da se proces praćenja simboličkih veza završi u razumnom vremenskom okviru, čak i u prisustvu ciklusa.

<a name="_heading=h.794hah35m04m"></a><a name="_heading=h.3bjk8yexeu5b"></a>**Ponašanje drugih sistemskih poziva prema simboličkim vezama:**

<a name="_heading=h.e3ws7hlhfomn"></a>Važno je napomenuti da određeni sistemski pozivi, kao što su link i unlink, ne treba da prate simboličke veze do njihovih ciljnih datoteka ili direktorijuma. Umesto toga, ovi sistemski pozivi treba da deluju direktno na samoj simboličkoj vezi. Na primer, ako se sistemski poziv unlink primeni na simboličku vezu, treba da se obriše sama veza, a ne ciljna datoteka na koju veza upućuje. Slično, sistemski poziv link treba da kreira novu vezu na samoj simboličkoj vezi, a ne na njenom cilju. Ovaj pristup omogućava preciznu kontrolu i manipulaciju simboličkim vezama unutar sistema datoteka.

<a name="_heading=h.l5zln27pvhgf"></a><a name="_heading=h.5dfdf935mprs"></a>**Simboličke veze ka direktorijumima**: Za ovaj zadatak nije potrebno obraditi simboličke veze koje upućuju na direktorijume.

<a name="_heading=h.tix83r2p86c8"></a><a name="_heading=h.grnbvpb4l5ov"></a>**Brojanje fizičkih blokova vezanih za fajl**: U strukturu stat u fajlu kernel/stat.h potrebno je dodati polje uint blocks koje broji fizičke blokove vezane za fajl. Ovaj broj ne uključuje metapodatke. Na primer, fajl od 1000 bajtova je vezan za dva bloka jer je za njega alocirano dva bloka. Slično tome, fajl od 6145 je vezan za 14 blokova, jer zauzima 12 direktnih, jedan indirektan blok i blok indirekcije.
# <a name="_heading=h.8kfcakmxanwj"></a>Sistemski pozivi
Za potrebe domaćeg zadatka treba implementirati nove sistemske pozive: symlink

**int symlink(char \*target, char \*path);**

Ovaj sistemski poziv se koristi za kreiranje nove simboličke veze. Simbolička veza je posebna vrsta datoteke koja služi kao referenca ili prečica do druge datoteke ili direktorijuma. Simbolička veza može biti kreirana čak iako putanja koju predstavlja još uvek ne vodi do stvarne datoteke.

- Parametar **target** je putanja do ciljne datoteke ili direktorijuma na koju simbolička veza treba da upućuje.
- Parametar **path** je putanja gde treba kreirati simboličku vezu.

Povratna vrednost može biti jedna od sledećih:

- 0: Simbolička veza je uspešno kreirana.
- -1: Došlo je do greške prilikom kreiranja simboličke veze. Greška može biti uzrokovana nevalidnim putanjama, nedostatkom dozvola, nedovoljnim prostorom na disku, zauzetost putanje **path**, ili drugim sistemskim ograničenjima.







# Korisnički programi
Neophodno je implementirati korisničke programe:

**sln [target] [linkname]**

Korisnički program sln kreira simboličku vezu sa imenom linkname koja upućuje na ciljnu datoteku ili direktorijum target.

- **target**: Putanja do ciljne datoteke ili direktorijuma na koju simbolička veza treba da upućuje.
- **linkname**: Ime koje će biti dodeljeno simboličkoj vezi.

Moguće greške pri pokretanju ovog programa su:

- Navedena putanja za ciljnu datoteku ili direktorijum nije validna.
- Nije moguće kreirati simboličku vezu sa navedenim imenom.

Ovaj program omogućava korisnicima da lako kreiraju simboličke veze za datoteke i direktorijume unutar sistema.

**symlinkinfo [path]**

Korisnički program symlinkinfo prikazuje informacije o simboličkim vezama na određenoj putanji. Putanja je opciona, i ako se izostavi, podrazumeva se trenutni direktorijum (.). Za svaku pronađenu simboličku vezu koja upućuje na datoteku, program treba da ispiše ime veze i putanju na koju upućuje. 

Moguće greške pri pokretanju ovog programa su:

- Navedena putanja nije validna.
- Nema simboličkih veza koje upućuju na datoteke u navedenom direktorijumu.

Ovaj program bi korisnicima omogućio brz pregled simboličkih veza unutar direktorijuma i mogao bi biti koristan za proveru strukture simboličkih veza ili za dijagnostiku problema povezanih sa simboličkim vezama.

**du [path…]**

Program du ispisuje ukupno zauzeće kao i zauzeće individualnih fajlova za skup fajlova, rekurzivno za direktorijume. du uzima listu putanja, sabira broj blokova svakog fajla u toj putanji, i rekurzivno ponavlja taj postupak za sadržaj direktorijuma.

# Bodovanje
Zadatak se boduje na sledeći način:

- Izmena tako da se podrže simbolične veze i du	= 9 bodova 
- Sistemski pozivi					

○	symlink					= 5 bodova

- Korisnicki programi			

○	sln						= 1 bod

○	symlinkinfo					= 3 boda

○	du						= 2 boda

U slučaju da je neka od stavki implementirana parcijalno, biće dodeljeni parcijalni poeni (potrebno je demonstrirati da taj parcijalni deo zaista radi i ima efekta). 


