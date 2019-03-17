#include <iostream>
#include <cstdlib>
#include <fstream>

class Product
{
public:

    Product(std::string newname = "NULL", int newprice = 0, int newtax = 0)
    {
        name = newname;
        netto = newprice;
        VAT = newtax;
    }

    int getnet() const
    {
        return netto;
    }

    int getVAT() const
    {
        return VAT;
    }

    std::string getname() const
    {
        return name;
    }

    void setnet(int new_netto)
    {
        netto = new_netto;
    }

    void setVAT(int new_VAT)
    {
        VAT = new_VAT;
    }

    void setname(std::string new_name)
    {
        name = new_name;
    }

private:

    int netto, VAT; // CENA PODANA JEST W GROSZACH
    std::string name;
};

void show_price(int newprice)
{
    std::cout << newprice / 100 << ",";
    if(newprice % 100 < 10)
        std::cout << 0;
    std::cout << newprice % 100;
}

class Cart
{
public:

    Cart()
    {
        for(int i = 0; i < getcart_capacity(); ++i)
        {
            tabc[i].setnet(0);
            tabc[i].setVAT(0);
            tabc[i].setname("NULL");
            qty[i] = 0;
        }
    }

    const int getcart_capacity() const
    {
        return cart_capacity;
    }

    const int getmaxqty() const
    {
        return maxqty;
    }

    Product gettabc(int i) const
    {
        return tabc[i];
    }

    int getqty(int i) const
    {
        return qty[i];
    }

    void settabc(int i, Product new_article = Product())
    {
        tabc[i].setnet(new_article.getnet());
        tabc[i].setVAT(new_article.getVAT());
        tabc[i].setname(new_article.getname());
    }

    void setqty(int newqty, int i)
    {
        qty[i] = newqty;
    }

    void orderly_tabc_and_qty()
    {
        bool blank = false;

        for(int i = 0; i < getcart_capacity() - 1; ++i)
        {
            if((gettabc(i)).getname() != "NULL" && blank == false)
            {
                settabc(i, gettabc(i));
                setqty(getqty(i), i);
            }

            if((gettabc(i)).getname() != "NULL" && blank == true)
            {
                settabc(i, gettabc(i + 1));
                setqty(getqty(i + 1), i);
            }

            if((gettabc(i)).getname() == "NULL" && blank == false)
            {
                settabc(i, gettabc(i + 1));
                setqty(getqty(i + 1), i);

                blank = true;
            }

            if((gettabc(i)).getname() == "NULL" && blank == true)
            {
                settabc(i);
                setqty(0, i);
            }
        }
    }

    void add_product(Product article, int newqty)
    {
        for(int i = 0; i < getcart_capacity(); ++i)
            if(article.getname() == tabc[i].getname())
            {
                if(getqty(i) + newqty > getmaxqty())
                    std::cout << "Nie zmiesci sie tyle w koszyku.\n";
                else
                {
                    setqty(getqty(i) + newqty, i);
                    std::cout << "Dodales do koszyka " << article.getname() << ", w ilosci: " << newqty << '\n';
                }

                return;
            }

        int NULL_indicator = -1;

        for(int i = 0; i < getcart_capacity(); ++i)
            if(tabc[i].getname() == "NULL")
            {
                NULL_indicator = i;
                break;
            }

        if(NULL_indicator < 0)
        {
            std::cout << "W koszyku jest juz 10 roznych produktow. Aby dodac kolejny usun przynajmniej jeden produkt z koszyka.\n";
            return;
        }

        if(newqty > getmaxqty())
            std::cout << "Nie zmiesci sie tyle w koszyku.\n";
        else
        {
            settabc(NULL_indicator, article);
            setqty(newqty, NULL_indicator);
            std::cout << "Dodales do koszyka " << article.getname() << ", w ilosci: " << newqty << '\n';
        }

    }

    void remove_product()
    {
        int choice = 0;

        std::cout << "\nW koszyku znajduja sie produkty wypisane ponizej:\n";
        for(int i = 0; i < getcart_capacity(); ++i)
            if(tabc[i].getname() != "NULL")
                std::cout << i + 1 << " - " << tabc[i].getname() << '\n';

        std::cout << "\nWybierz produkt, ktory chcesz usunac z koszyka: ";
        std::cin >> choice;

        if(choice < 1 || choice > getcart_capacity())
        {
            std::cout << "\nWprowadziles liczbe spoza zakresu! Wybierz jeszcze raz.\n";
            remove_product();
        }

        std::cout << "\nUsunales z koszyka: " << tabc[choice - 1].getname() << '\n';

        settabc(choice - 1);
        setqty(0, choice - 1);
        orderly_tabc_and_qty();
    }

    void show_cart() const
    {
        int amount = 0;

        std::cout << "\nZawartosc koszyka:\n";
        for(int i = 0; i < getcart_capacity(); ++i)
            if(tabc[i].getname() != "NULL")
            {
                std::cout << i + 1 << " - " << tabc[i].getname() << " - " << getqty(i) << " szt.\n";

                amount += getqty(i) * (tabc[i].getnet() * (100 + tabc[i].getVAT()) / 100);
            }

        std::cout << "\nLaczna kwota produktow w koszyku wynosi: ";
        show_price(amount);
        std::cout <<" PLN\n";

        char x = 'n';
        std::cout << "\nJesli chcesz zapisac stan koszyka do pliku tekstowego, wpisz \"t\" i zatwierdz: ";
        std::cin >> x;

        if(x == 't')
        {
            std::string file_name;

            std::cout << "Podaj nazwe pliku do zapisu stanu koszyka: ";
            std::cin >> file_name;
            file_name += ".txt";

            std::ofstream cart_save_file(file_name.c_str());

            for(int i = 0; i < getcart_capacity(); ++i)
                if(tabc[i].getname() != "NULL")
                {
                    cart_save_file << tabc[i].getname() << '\n';
                    cart_save_file << tabc[i].getnet() << '\n';
                    cart_save_file << tabc[i].getVAT() << '\n';
                    cart_save_file << getqty(i) << '\n';
                }
        }
    }

    void load_cart()
    {
        std::string file_name;
        std::string load_data;

        std::cout << "\nPodaj nazwe pliku do odczytu stanu koszyka: ";
        std::cin >> file_name;
        file_name += ".txt";

        std::ifstream cart_load_file(file_name.c_str());

        if(cart_load_file.good() == false)
        {
            std::cout << "\nPlik zapisu o podanej nazwie nie istnieje.\n";
            return;
        }

        for(int i = 0; i < getcart_capacity(); ++i)
        {
            settabc(i);
            setqty(0, i);
        }

        int line_no = 1;
        int product_no = 0;

        while(getline(cart_load_file, load_data))
        {
            static std::string temp_name = "NULL";
            static int temp_netto = 0;
            static int temp_VAT = 0;

            if(line_no == 1)
                temp_name = load_data;
            if(line_no == 2)
                temp_netto = atoi(load_data.c_str());
            if(line_no == 3)
            {
                temp_VAT = atoi(load_data.c_str());
                Product temp_product(temp_name, temp_netto, temp_VAT);
                settabc(product_no, temp_product);
            }
            if(line_no == 4)
            {
                setqty(atoi(load_data.c_str()), product_no);
                product_no++;
            }

            if(line_no == 4)
                line_no = 1;
            else line_no++;
        }
    }

private:

    Product tabc[10];
    int qty[10];
    static const int cart_capacity = 10;
    static const int maxqty = 24;
};

class Shop
{
public:

    Shop(Product* tab)
    {
        for(int i = 0; i < getproduct_qty(); ++i)
            tabs[i] = tab[i];
    }

    const int getproduct_qty() const
    {
        return product_qty;
    }

    Product gettabs(int i) const
    {
        return tabs[i];
    }

    void show_articles() const
    {
        std::cout << "\nDostepne produkty:\n";

        for(int i = 0; i < getproduct_qty(); ++i)
        {
            std::cout << tabs[i].getname() << " - ";
            show_price(tabs[i].getnet() * (100 + tabs[i].getVAT()) / 100);
            std::cout << " PLN\n";
        }

        char x = '1';
        std::cout << "\nAby wrocic do menu glownego wybierz ZERO: ";
        std::cin >> x;
        if(x == '0')
            return;
        else show_articles();
    }

    void pay(Cart new_cart)
    {
        int pause_no = 0, amount = 0, total_amount = 0;

        std::cout << "\nPodsumowanie Twoich zakupow:\n\n";

        for(int i = 0; i < new_cart.getcart_capacity(); ++i)
        {
            if((new_cart.gettabc(i)).getname() != "NULL")
            {
                Product aux_var = new_cart.gettabc(i);
                amount = 0;
                amount = new_cart.getqty(i) * (aux_var.getnet() * (100 + aux_var.getVAT()) / 100);
                total_amount += new_cart.getqty(i) * (aux_var.getnet() * (100 + aux_var.getVAT()) / 100);

                std::cout << aux_var.getname() << " - " << new_cart.getqty(i) << " szt. - ";
                show_price(new_cart.getqty(i) * aux_var.getnet());
                std::cout << " PLN netto - ";
                show_price(amount);
                std::cout << " PLN brutto, w tym VAT ";
                std::cout << aux_var.getVAT() << "%\n";
            }
        }

        for(int i = 0; i < new_cart.getcart_capacity(); ++i)
        {
            new_cart.settabc(i);
            new_cart.setqty(0, i);
        }

        std::cout << "\nDo zaplaty: ";
        show_price(total_amount);
        std::cout << " PLN\n";
        std::cout << "\nNacisnij dowolny przycisk i zatwierdz, aby wyjsc z programu.";
        std::cin >> pause_no;
        exit(0);
    }

private:

    Product tabs[15];
    static const int product_qty = 15;
};

void Instruction(Shop new_shop, Cart new_cart)
{
    for(;;)
    {
        std::cout <<    "\nWitaj w sklepie. Wybierz dostepna z ponizszych opcji:\n"
                        "1 - lista dostepnych produktow\n"
                        "2 - dodaj produkt do koszyka\n"
                        "3 - usun produkt z koszyka\n"
                        "4 - pokaz stan koszyka\n"
                        "5 - zaladuj zapis stanu koszyka\n"
                        "6 - zaplac\n";

        char choice = '0';
        std::cin >> choice;

        if(choice == '1')
            new_shop.show_articles();
        if(choice == '2')
        {
            std::cout <<    "\nWybierz produkt, ktory chcesz kupic. Nastepnie zostaniesz poproszony o podanie ilosci."
                            " Pamietaj! Nie mozesz w koszyku miec wiecej niz 10 produktow, a te ktore sa w koszyku"
                            " nie moga byc w ilosci wiekszej niz 24.\n";

            for(int i = 0; i < new_shop.getproduct_qty(); ++i)
                std::cout << i + 1 << " - " << (new_shop.gettabs(i)).getname() << '\n';

            int what_to_buy = 0, pcs = 0;
            std::cin >> what_to_buy;
            std::cout << "Podaj ilosc: ";
            std::cin >> pcs;

            new_cart.add_product(new_shop.gettabs(what_to_buy - 1), pcs);
        }
        if(choice == '3')
            new_cart.remove_product();
        if(choice == '4')
            new_cart.show_cart();
        if(choice == '5')
            new_cart.load_cart();
        if(choice == '6')
            new_shop.pay(new_cart);
    }
}

int main()
{
    Product Pomidor("Pomidor", 95, 8), Ogorek("Ogorek", 500, 8), Marchewka("Marchewka", 150, 8), Cebula("Cebula", 50, 8), Rzodkiewka("Rzodkiewka", 200, 8);
    Product Banan("Banan", 2000, 23), Jablko("Jablko", 500, 23), Gruszka("Gruszka", 600, 23), Truskawka("Truskawka", 1500, 23), Pozeczka("Pozeczka", 450, 23);
    Product Papryka("Papryka", 900, 8), Pieczarka("Pieczarka", 350, 8), Agrest("Agrest", 1000, 23), Borowka("Borowka", 3000, 23), Reklamowka("Reklamowka", 20, 90);
    Product ShopTable[15] = {Pomidor, Ogorek, Marchewka, Cebula, Rzodkiewka, Banan, Jablko, Gruszka, Truskawka, Pozeczka, Papryka, Pieczarka, Agrest, Borowka, Reklamowka};

    Shop Warzywniak(ShopTable);
    Cart Koszyk;

    Instruction(Warzywniak, Koszyk);

    return 0;
}
