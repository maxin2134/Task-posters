#include <iostream>
#include <vector>
#include <stack>
/*
  * Program jest przykładowym rozwiązania zadania ze strony szkopuł.edu.pl o nazwie Plakatowanie
  * Z analizy zadania wynika, że głównym czynnikiem odpowiadającym za ilość wymaganych plakatów do oklejenia
  * północnej ściany budynków jest ich wysokość dlatego podczas wczytywania danych budynków (szerokość i wysokosć)
  * do struktury danych typu vector jest wczytywana tylko wysokość budynków i na tej podstawie jest obliczana
  * minimalna liczba plakatów.
  *
  * Algorytm liczenia plakatów:
  *
  * 1. Jeżeli stos nie jest pusty i budynek na wierzchu stosu jest większy od budynku aktualnie sprawdzanego (vector),
       zdejmij budynek z wierzchu stosu
  * 2. Jeżeli stos jest pusty lub sprawdzany budynek (vector) jest większy od budynku na wierzchu stosu
  *    dodaj budynek do stosu i zwiększ liczbę plakatów o jeden
  *
  * Algorytm pomija zdarzenie kiedy sprawdzane budynki są takiej samej wielkości ponieważ nic nie zmienia w liczbie
  * wykorzystywanych plakatów.
*/


/*
  *  zmienne globalne
  *  buildingsCount - ilość wczytanych budynków
  *  postersUsed - ilość wykorzystanych plakatów do oklejenia północnej ściany budynków
  *  heightOfBuildings - struktura danych do przechowywania wysokości budynków
*/
unsigned buildingsCount = 0, postersUsed = 0;
std::vector<unsigned> heightOfBuildings;

// funkcja odpowiadająca za zliczanie wykorzystywanych plakatów
void computePostersUsed()
{
    //utowrzenie stosu
    std::stack<unsigned> heightsProcessed;

    // pętla wykorzystywana do przejścia przez całą strukturę danych w której przechowujemy wysokości budynków
    for (unsigned i = 0; i < heightOfBuildings.size(); ++i)
    {
        // Pętla odpowiedzialna za sprawdzanie czy stos nie jest pusty i czy budynek na wierzchu stosu jest większy
        // od obecnie sprawdzanego budynku. Jeżeli warunek zostaje spełniony, budynek ze stosu zostaje zdjęty.
        while (!heightsProcessed.empty() && heightsProcessed.top() > heightOfBuildings[i])
        {
            heightsProcessed.pop();
        }

        // Warunek sprawdzający czy stos jest pusty lub sprawdzany budynek jest wyższy od budynku znajdującego się
        // na wierzchu stosu. Jeżeli którykolwiek z tych warunków zostanie spełniony następuję dodanie na stos
        // obecnie sprawdzanego budynku oraz zwiększenie liczby plakatów o 1
        if (heightsProcessed.empty() || heightsProcessed.top() < heightOfBuildings[i])
        {
            heightsProcessed.push(heightOfBuildings[i]);
            ++postersUsed;
        }
    }
}

int main()
{
    // wyłączenie synchronizacji danych bufera danych wyjścia/wejścia, aby przyśpieszyć działanie programu
    std::ios_base::sync_with_stdio(0);

    // wczytanie ilości budynków podawanej przez użytkownika
    std::cin >> buildingsCount;

    // utowrzenie vektora (zarezerwowanie pamięci) o wielkości podanej przez użytkownika 
    heightOfBuildings.reserve(buildingsCount);

    // pętla wczytująca dane
    for (int i = 0; i < buildingsCount; i++)
    {
        // utworzenie zmiennych pomocniczych 
        unsigned height = 0;
        unsigned width = 0;

        // wczytywanie ze standardowego wejścia szerokości i wysokości
        std::cin >> width >> height;

        // dodanie na sam koniec do vektora podanej wysokości
        heightOfBuildings.push_back(height);
    }

    // wywołanie funkcji odpowiedzialnej za liczenie minimalnej liczby plakatów
    computePostersUsed();

    // wypisaniu na standardowe wyjście obliczonej minimalnej liczby plakatów
    std::cout << postersUsed << std::endl;

    return 0;
}