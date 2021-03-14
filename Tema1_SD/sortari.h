//
// Created by Ionut on 3/11/2021.
//

#ifndef TEMA1_SD_SORTARI_H
#define TEMA1_SD_SORTARI_H
#include <vector>
using namespace std;

void bubblesort(vector <int> &v);
void countsort(vector <int> &v, int max);
void interclasare(vector <int> &v, int left, int right, int mij);
void mergesort(vector <int> &v, int left, int right);
int alege_pivot_1(vector <int>& v, int left, int right);
int alege_pivot_2(vector <int>& v, int left, int right);
int alege_pivot_3(vector <int>& v, int left, int right);
void quicksort(vector <int> &v, int left, int right);
void quicksort_median_of_three(vector <int> &v, int left, int right);
int element_max(const vector <int> &v);
void count_sort(vector <int> &v, long long place, int baza);
void count_sort_bit(vector <int> &v, int place, long long baza);
void radixsort_bit(vector <int> &v, int nr_biti);
void radixsort(vector <int> &v, int baza);
bool test_sort(vector <int> &v, vector <int> &cv);

#endif //TEMA1_SD_SORTARI_H
