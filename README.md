# Shop
Zadanie z kursu C/C++ (ALX/Warszawa/kwiecień-czerwiec 2018)

3 Sklep
Dla przypomnienia: to jest zadanie „otwarte” – wymyslenie rozsadnego zestawu klas oraz potrzebnych metod
jest czescia cwiczenia. W przypadku róznych watpliwosci (takze technicznych, np. jak zrobic interaktywny
program), najlepiej pisac na Slacku.

Zaprojektuj i zaprogramuj system samoobsługowej sprzedazy w sklepie. W sklepie znajduja sie produkty, które
moga byc kupowane przez klientów.

Klient moze poprosic sklep o liste produktów – w takim przypadku stosowna informacja powinna zostac
wypisana na ekran. Wewnetrznie w sklepie, kazdy produkt ma pewne cechy go opisujace. Sa to: nazwa,
cena netto i stawka VAT. Przy wypisywaniu asortymentu sklepu powinna zostac wyswietlona tylko cena brutto
za dany produkt. Dla uproszczenia przyjmujemy, ze sklep posiada nieskonczony zapas kazdego posiadanego
produktu.

Klienci maja koszyk, w którym przechowuja produkty, które chca zakupic. W koszyku moze znajdowac sie
co najwyzej 10 róznych produktów, a kazdy z nich moze znajdowac sie w liczbie do 24 jednostek. Klienci
powinni miec mozliwosc wyjmowania produktów z koszyka. W dowolnym momencie klient moze poprosic
o podsumowanie kosztu produktów w koszyku.

Gdy klient decyduje sie zapłacic, jego koszyk zostaje oprózniony, a na ekran wyswietlone jest podsumowanie
zakupów (elektroniczny paragon): lista zamówionych produktów oraz ich liczba, cena netto, cena brutto
(z informacja o stawce VAT), podsumowanie kosztu. Nie zajmujemy sie tutaj kwestia płatnosci za zakupy
ani przekazaniem ich klientowi.

3.1 Gwiazdka
Zadbaj, aby Twój program był interaktywny, tzn. na starcie programu wyswietl (tekstowo) jakie polecenia
ma do dyspozycji uzytkownik. W trakcie działania, program powinien odczytywac i wykonywac polecenia
od uzytkownika. Nie trzeba sie bardzo przejmowac kontrola błedów, tzn. mozna przyjac, ze uzytkownik czyta
instrukcje ze zrozumieniem i bezbłednie wpisuje polecenia.

3.2 Gwiazdka
Dodaj mozliwosc zapisywania biezacego stanu koszyka do pliku o wskazanej nazwie.

3.3 Dwie gwiazdki
Dodaj mozliwosc wczytania z pliku wczesniej zapisanego tamze stanu koszyka. Moze sie to przydac w sytuacji,
gdy klient dokonuje wyboru produktów, ale musi przerwac zakupy przed wybraniem wszystkich potrzebnych
produktów. Dzieki tej funkcjonalnosci klient moze zapisac koszyk i w dogodnym dla siebie momencie odczytac go
z pliku i kontynuowac zakupy.
