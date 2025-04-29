#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <string>
#include <cstdlib>

using namespace std;

using Kolumna = queue<string>;

class Player
{
public:
    bool drugi_strzal;
    bool gra_trwa;
    int kolumna;
};

void wypisz(vector<Kolumna> &plansza, int k, int b, Player &gracz, std::ostream& os = std::cout)
{
    for (int i = 0; i < k; i++)
    {
        if (i == k-1)
            os << "----";
        else
            os << "------";
    }
    os << '\n';
    for (int row = 0; row < 9; row++)
    {
        if (row == 8)
        {
            for (int i = 0; i < k; i++)
            {
                if (i == gracz.kolumna)
                    os << "=[]= ";
                else
                    os << "      ";
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
                    os << "      ";
                else
                    os << temp.front() << "  ";
            }
        }
            os << '\n';
    }
    for (int i = 0; i < k; i++)
    {
        if (i == k - 1)
            os << "----";
        else
            os << "------";
    }

}

void strzal(vector<Kolumna>& plansza, int cel, Player &gracz, std::ostream& os = std::cout) {
    if (plansza[cel].empty())
    {
        os << "Brak bloczkow w tej kolumnie!" << endl;
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

void check_win(vector<Kolumna>& plansza, int k, Player &gracz)
{
    for (int i = 0; i < k; i++)
    {
        if (plansza[i].size() == 8)
            gracz.gra_trwa = false;
    }
}