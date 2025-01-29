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
