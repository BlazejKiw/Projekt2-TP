#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <string>
#include <future>

using namespace std;

using Kolumna = queue<string>;

class Player
{
public:
    bool drugi_strzal;
    bool gra_trwa;
    int kolumna;
};

vector<Kolumna> stworz_plansze(int k, int b)
{
    vector<Kolumna> plansza(k);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < b; j++)
        {
            string blok = (rand() % 5 == 0) ? "#++#" : "####";
            plansza[i].push(blok);
        }
    }

    return plansza;
}

void wypisz(vector<Kolumna>& plansza, int k, int b, Player& gracz)
{
    for (int i = 0; i < k; i++)
    {
        if (i == k - 1)
            cout << "----";
        else
            cout << "------";
    }
    cout << '\n';
    for (int row = 0; row < 9; row++)
    {
        if (row == 8)
        {
            for (int i = 0; i < k; i++)
            {
                if (i == gracz.kolumna)
                    cout << "=[]= ";
                else
                    cout << "      ";
            }
        }
        else
        {
            for (int i = 0; i < k; i++)
            {
                queue<string> temp = plansza[i];
                for (int l = 0; l < row; l++)
                {
                    if (temp.empty())
                        break;
                    else
                        temp.pop();
                }
                if (temp.empty())
                    cout << "      ";
                else
                    cout << temp.front() << "  ";
            }
        }
        cout << '\n';
    }
    for (int i = 0; i < k; i++)
    {
        if (i == k - 1)
            cout << "----";
        else
            cout << "------";
    }

}

void strzal(vector<Kolumna>& plansza, int cel, Player& gracz) {
    if (plansza[cel].empty())
    {
        cout << "Brak bloczkow w tej kolumnie!" << endl;
        return;
    }

    queue<string> NowaKolumna;
    int size;
    size = plansza[cel].size();
    for (int i = 0; i < size - 1; ++i)
    {
        NowaKolumna.push(plansza[cel].front());
        plansza[cel].pop();
    }
    if (plansza[cel].empty() != true)
    {
        if (plansza[cel].front() == "#++#")
            gracz.drugi_strzal = true;
    }
    plansza[cel].pop();

    plansza[cel] = NowaKolumna;
}

void dodaj(vector<Kolumna>& plansza, int k)
{
    for (int i = 0; i < k; i++)
    {
        queue<string> temp;
        temp = plansza[i];
        while (plansza[i].empty() == false)
            plansza[i].pop();
        string blok = (rand() % 5 == 0) ? "#++#" : "####";
        plansza[i].push(blok);
        while (temp.empty() == false)
        {
            plansza[i].push(temp.front());
            temp.pop();
        }

    }
}

void check_win(vector<Kolumna>& plansza, int k, Player& gracz)
{
    for (int i = 0; i < k; i++)
    {
        if (plansza[i].size() == 8)
            gracz.gra_trwa = false;
    }
}

int main()
{
    //Zasady:
    //Maksymalna liczba wierszy to 8.
    srand(time(NULL));
    Player gracz;
    gracz.gra_trwa = true;
    gracz.drugi_strzal = false;
    gracz.kolumna = 0;
    int cel;
    int k;
    int b;
    int r;
    int n;
    int dodaj_runda;
    int turn = 0;


    cout << "Podaj liczbe kolumn: ";
    cin >> k;
    cout << "Podaj liczbe bloczkow na kolumne [0-8]: ";
    cin >> b;
    cout << "Co r+rnd ruchów do wszystkich kolumn dodawany jest jeden bloczek.Parametr rnd jest wartoscia losowa z przedzialu[0, n)" << '\n';
    cout << "Znajac ta zasade podaj parametr r: ";
    cin >> r;
    while (r < 1)
    {
        cin.clear();
        cin.ignore(numeric_limits< streamsize >::max(), '\n');
        cout << "Liczba nie moze byc mniejsza niz 1: ";
        cin >> r;
    }
    cout << "Podaj rowniez wartosc parametru n: ";
    cin >> n;
    while (n < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits< streamsize >::max(), '\n');
        cout << "Liczba nie jest z zakresu sprobuj jeszcze raz: ";
        cin >> n;
    }
    dodaj_runda = r + (rand() % n);
    while (b != 0 && b != 1 && b != 2 && b != 3 && b != 4 && b != 5 && b != 6 && b != 7 && b != 8)
    {
        cin.clear();
        cin.ignore(numeric_limits< streamsize >::max(), '\n');
        cout << "Liczba nie jest z zakresu sprobuj jeszcze raz: ";
        cin >> b;
    }

    //tworzenie planszy
    future<vector<Kolumna>> tworzenie_planszy = async(launch::async, stworz_plansze, k, b);

    cout << "!!!!Generowanie planszy!!!!" << '\n';

    vector<Kolumna> plansza = tworzenie_planszy.get();

    while (gracz.gra_trwa == true)
    {

        wypisz(plansza, k, b, gracz);
        cout << '\n' << '\n' << "Wybierz kolumnę w ktora chcesz strzelic: ";
        cin >> cel;
        cout << '\n';
        cel -= 1;
        gracz.kolumna = cel;
        while (cel > k - 1 || cel < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits< streamsize >::max(), '\n');
            cout << "Nie ma takiej kolumny sprobuj jeszcze raz: ";
            cin >> cel;
            cel -= 1;
        }
        strzal(plansza, cel, gracz);

        while (gracz.drugi_strzal == true)
        {
            wypisz(plansza, k, b, gracz);
            gracz.drugi_strzal = false;
            cout << '\n' << "!!!Masz bonusowy strzal!!!" << '\n';
            cout << '\n' << "Wybierz kolumnę w ktora chcesz strzelic: ";
            cin >> cel;
            cout << '\n';
            cel -= 1;
            gracz.kolumna = cel;
            while (cel > k - 1 || cel < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits< streamsize >::max(), '\n');
                cout << "Nie ma takiej kolumny sprobuj jeszcze raz: ";
                cin >> cel;
                cel -= 1;
            }
            strzal(plansza, cel, gracz);


        }
        if ((turn % dodaj_runda) == 0)
            dodaj(plansza, k);
        check_win(plansza, k, gracz);
        turn += 1;
    }
    wypisz(plansza, k, b, gracz);
    cout << '\n' << "!!!Koniec gry Przegrales!!!";
    return 0;
}