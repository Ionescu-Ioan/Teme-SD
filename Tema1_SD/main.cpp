#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "sortari.h"

using namespace std;


int T;

vector <string> metode_sortare = {"bubblesort", "countsort", "mergesort", "quicksort", "quicksort_median_of_three",  "radixsort", "radixsort_bit", "sort_stl"};

class Test
{
private:
    int nr_test;
    int N;
    int Max;
    double timp;
    string metoda_sortare;
    bool ok;

public:
    Test(int nr, int n, int max, double t, string metoda, bool _ok)
    {
        nr_test = nr;
        N = n;
        Max = max;
        timp = t;
        metoda_sortare = metoda;
        ok = _ok;
    }

    ~Test(){}
    void afisare()
    {
        cout << setw(8) << nr_test << setw(10) << N << setw(12) << Max << setw(14) << timp << setw(10) << ok << setw(30) << metoda_sortare << "\n";
    }

};

vector <Test> vt;

/*
void afisare_vector(vector <int> &v)
{
    for(int i=0; i<v.size(); ++i)
        cout<<v[i]<<" ";
    cout<<"\n";
}
 */


string int_to_string(int x)
{
    ostringstream os;   /// stream de iesire ce are ca buffer un string
    os << x;            ///trimit valoarea intreaga din x la stream-ul os
    return os.str();   ///returnez string-ul din stream-ul de iesire de mai sus(conversia lui x de la int la string)
}


void sortari()
{

    for(int m=0; m < metode_sortare.size(); ++m)
    {
        for(int t=1; t<=T; ++t)
        {
            vector <int> v;
            string fname = "test_" + int_to_string(t) + ".txt";
            ifstream fin(fname.c_str()); ///c_str() returneaza continutul lui fname in formatul clasic(sir de caractere ce se termina cu terminatorul null)

            int N, Max;
            fin >> N >> Max;
            if(N > 1000000)
            {
                cout << "Nu se poate sorta, deoarece vectorul construit ar avea o dimensiune prea mare\n";
            }
            else {
                v.resize(N);

                for (int i = 0; i < N; ++i)
                    fin >> v[i];

                long long timp_start = clock();

                switch (m) {
                    case 0:
                        bubblesort(v);
                        break;
                    case 1:
                        countsort(v, Max);
                        break;
                    case 2:
                        mergesort(v, 0, v.size() - 1);
                        break;
                    case 3:
                        quicksort(v, 0, v.size() - 1);
                        break;
                    case 4:
                        quicksort_median_of_three(v, 0, v.size());
                        break;
                    case 5:
                        radixsort(v, 32);
                        break;
                    case 6:
                        radixsort_bit(v, 5);
                        break;
                    case 7:
                        std::sort(v.begin(), v.end());
                        break;
                }

                long long timp_end = clock();
                bool rez_sort = test_sort(v);
                double timp_sortare = 1.0 * (timp_end - timp_start) / CLOCKS_PER_SEC;
                Test test(t, N, Max, timp_sortare, metode_sortare[m], rez_sort);
                vt.push_back(test);

                //afisare_vector(v);
            }
        }

    }

}


int random()
{
    long long r1 = rand(), r2 = rand();
    return (r1 * r2)%1000000007; ///e indicat sa lucram cu numere prime cand generam random
}


void build(vector <int> &v, int n, int max)
{
    v.resize(n,0);
    for(int i=0; i<n; ++i)
        v[i]=random()%max+1;
}


void generari() ///genereaza fisierele de test(fiecare fisier va afea continutul unui vector generat random)
{
    ifstream fin("teste.txt");
    fin >> T;
    for(int t=1; t<=T; ++t)
    {
        int N, Max;
        fin >> N >> Max;
        vector <int> v;

        string fname = "test_" + int_to_string(t) + ".txt";
        ofstream fout(fname.c_str());
        fout << N << " " << Max << "\n";

        if(N < 1000000)
        {
            build(v, N, Max);
            for (int i = 0; i < N; i++)
                fout << v[i] << " ";
        }
        else cout << "Vectorul are dimensiunea prea mare\n";
        fout.close();
    }
}

void afisare_rezultat()
{
    cout << "\n                            Studiul tehnicilor de sortare\n";
    cout << "--------------------------------------------------------------------------------------------------\n";
    cout << "Numar test      N         Max    Timp sortare    Rezultat             Metoda sortare\n";
    cout << "--------------------------------------------------------------------------------------------------\n";
    for(int i=0; i<vt.size(); ++i)
    {
        vt[i].afisare();
    }
}


int main()
{
    srand(time(0));
    ofstream fout("rezultate.txt");
    generari();
    sortari();
    cerr << "sfarsit sortari\n";
    afisare_rezultat();

return 0;
}