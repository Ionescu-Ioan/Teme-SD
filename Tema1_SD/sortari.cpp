#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "sortari.h"

using namespace std;


void bubblesort(vector <int> &v)
{
    bool gata = false;
    while(!gata)
    {
        gata=true;
        for(int i=0; i<v.size()-1; ++i)
            if(v[i] > v[i+1])
            {
                int aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                gata=false;
            }
    }
}


void countsort(vector <int> &v, int max)
{
    vector <int> c(max+1, 0);
    for(int i=0; i<v.size(); ++i)
        ++c[v[i]];

    int j=0;
    for(int i=0; i<=max; ++i)
        while(c[i]>0)
        {
            v[j]=i;
            --c[i];
            ++j;
        }
}


void interclasare(vector <int> &v, int left, int right, int mij)
{
    int i = left, j = mij + 1, k = 0;
    vector<int> t(right - left + 1);
    while (i <= mij && j <= right)
    {
        if (v[i] < v[j])
        {
            t[k++] = v[i++];
        }
        else
            {
            t[k++] = v[j++];
            }
    }
    while(i<=mij)
    {
            t[k++] = v[i++];
    }
    while(j<=mij)
    {
            t[k++] = v[j++];
    }
    for(i=0; i<k; ++i)
        v[left+i]=t[i];
}

void mergesort(vector <int> &v, int left, int right)
{
    if(left == right)
        return;
    int mij = (left + right)/2;
    mergesort(v, left, mij);
    mergesort(v, mij+1, right);
    interclasare(v, left, right, mij);

}

int alege_pivot_1(vector <int>& v, int left, int right) ///primul element
{
    int direction=0;
    while(left < right)
    {
        if(v[left] > v[right])
        {
            int aux = v[left];
            v[left] = v[right];
            v[right] = aux;
            direction = 1-direction;
        }
        left+=direction;
        right-=1-direction;
    }
    return left;
}

int alege_pivot_2(vector <int>& v, int left, int right) ///random
{
    int direction = 0;
    int p = rand()%(right - left) + left;

    swap(v[left], v[p]);

    while(left < right)
    {
        if(v[left] > v[right])
        {
            int aux = v[left];
            v[left] = v[right];
            v[right] = aux;
            direction = 1-direction;
        }
        left+=direction;
        right-=1-direction;
    }
    return left;
}

int alege_pivot_3(vector <int>& v, int left, int right) //mediana din 3
{
    int x=v[left], y=v[(right-left)/2+left], z=v[right-1];
    if (y>x && y<z || y>z && y<x )
    {x = y;
    }
    else if (z>x && z<y || z>y && z<x )
    {x = z;
    }

    left--;

    while (true)
    {
        do
        {right--;
        }while (v[right] > x);

        do
        {left++;
        }while (v[left] < x);

        if  (left < right)
        {
            swap(v[left],v[right]);
        }
        else return right+1;
    }
}

void quicksort(vector <int> &v, int left, int right)
{
    if(left < right)
    {
        int piv = alege_pivot_2(v, left, right);
        quicksort(v, left, piv-1);
        quicksort(v, piv+1, right);
    }
}


void quicksort_median_of_three(vector <int> &v, int left, int right)
{
    if(right - left < 2) return;

    int piv = alege_pivot_3(v, left, right);
    quicksort_median_of_three(v, left, piv);
    quicksort_median_of_three(v, piv, right);
}

int element_max(const vector <int> &v)
{
    int m = v[0];
    for(int i=1; i<v.size(); ++i)
        m = max(v[i], m);

    return m;
}

void count_sort(vector <int> &v, long long place, int baza)
{
    vector <int> count(baza);
    vector <int> out(v.size());

    for(int i=0; i<v.size(); ++i)
        ++count[v[i]/place%baza];

    for(int i=1; i<baza; ++i)
        count[i] += count[i-1];

    for(int i=v.size()-1; i>=0; --i)
    {
        out[count[v[i] / place % baza] - 1] = v[i];
        count[v[i] / place % baza]--;
    }

    for(int i=0; i<out.size(); ++i)
        v[i] = out[i];
}

void count_sort_bit(vector <int> &v, int place, long long baza)
{
    vector <int> count(baza + 1);
    vector <int> out(v.size());

    for(int i=0; i<v.size(); ++i)
    {
        int cif = ((v[i]>>place)&baza);
        ++count[cif];
    }

    for(int i = 1; i <= baza; ++i)
        count[i] += count[i-1];

    for(int i=v.size()-1; i >= 0; --i)
    {
        int cif = ((v[i]>>place)&baza);
        out[count[cif] - 1] = v[i];
        count[cif]--;
    }

    for(int i=0; i<out.size(); ++i)
        v[i] = out[i];
}


void radixsort_bit(vector <int> &v, int nr_biti)
{
    long long baza=(1ll << nr_biti)-1; /// cifra maxima care se poate reprezenta in acea baza
    int m = element_max(v);
    for(int place=0; m/(1ll << place)>0; place+=nr_biti)
        count_sort_bit(v, place, baza);
}

void radixsort(vector <int> &v, int baza)
{
    int m = element_max(v);
    for(long long place=1; m/place>0; place*=baza)
        count_sort(v, place, baza);
}

bool test_sort(vector <int> &v, vector <int> &cv)
{
    std::sort(cv.begin(), cv.end());
    for(int i=0; i<v.size(); ++i)
        if(v[i] != cv[i])
            return false;
  
    return true;
}
