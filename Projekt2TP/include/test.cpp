#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <queue>
#include <vector>
#include "main.h"

int main() {
    // Stwarzanie planszy 5x5 i gracza
    vector<Kolumna> plansza(5);
    Player gracz;
    gracz.gra_trwa = true;
    gracz.drugi_strzal = false;
    gracz.kolumna = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            string blok = (j % 2 == 0) ? "#++#" : "####";
            plansza[i].push(blok);
        }
    }
    // Test 1 dla funkcji wypisz
    std::ostringstream oss;
    wypisz(plansza, 5, 5, gracz, oss);
    string output = 
    "----------------------------\n"
"#++#  #++#  #++#  #++#  #++#  \n"
"####  ####  ####  ####  ####  \n"
"#++#  #++#  #++#  #++#  #++#  \n"
"####  ####  ####  ####  ####  \n"
"#++#  #++#  #++#  #++#  #++#  \n"
"                              \n"
"                              \n"
"                              \n"
"=[]=                         \n"
"----------------------------";
    assert(oss.str() == output);
    cout << "Test 1 passed!" << "\n";
    // wyczyszczanie oss
    oss.str("");

    // Test 2 funkcji strzal
    strzal(plansza, 1, gracz);
    wypisz(plansza, 5, 5, gracz, oss);
    string output1 = 
    "----------------------------\n"
"#++#  #++#  #++#  #++#  #++#  \n"
"####  ####  ####  ####  ####  \n"
"#++#  #++#  #++#  #++#  #++#  \n"
"####  ####  ####  ####  ####  \n"
"#++#        #++#  #++#  #++#  \n"
"                              \n"
"                              \n"
"                              \n"
"=[]=                         \n"
"----------------------------";
    assert(oss.str() == output1);
    cout << "Test 2 passed!" << "\n";
    // wyczyszczanie oss
    oss.str("");

    // Test 3 atrybutu gra_trwa
    assert(gracz.gra_trwa == 1);
    cout << "Test 3 passed!" << "\n";

    // Test 4 atrybutu drugi_strzal
    assert(gracz.drugi_strzal == 1);
    cout << "Test 4 passed!" << "\n";

    // Test 5 funkcji dodaj. Na poczatku obliczamy ilosc znakow # w planszy
    wypisz(plansza, 5, 5, gracz, oss);
    int ile_linek = 0;
    for (size_t i = 0; i < oss.str().length(); i++)
        if (oss.str()[i] == '#') {
            ile_linek += 1;
        }
    oss.str("");
    
    // dodajemy nowa linke 
    // i porownujemy ilosc znakow # do ilosci jaka byla wczesniej
    // roznica moze wynosic minimalnie 10, 
    // jesli wszystkie dodane symboli byli #++# 
    // i maksymalnie 20, jesli wszystkie dodane symboli byli #### 
 
    dodaj(plansza, 5);
    wypisz(plansza, 5, 5, gracz, oss);
    int ile_linek_teraz = 0;
    for (size_t i = 0; i < oss.str().length(); i++)
        if (oss.str()[i] == '#') {
            ile_linek_teraz += 1;
        }
    assert(ile_linek_teraz - ile_linek >= 10 && ile_linek_teraz - ile_linek <= 20);
    cout << "Test 5 passed!" << "\n";
}