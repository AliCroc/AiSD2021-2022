#include <stdio.h>
#include <stdlib.h>

#include "algorytmy.h"

int partition(int tab[], int l, int r);
void swap(int *a, int *b);
void heapify(int arr[], int n, int i);

//grupa metod I

void insert_sort(int *tab, int n)
{
    for (int i = 1; i < n; i++) {
        int key = tab[i], j = i - 1;
        while (key < tab[j] && j >= 0) {
            tab[j + 1] = tab[j];
            --j;
        }
        tab[j + 1] = key;
    }
}

void bubble_sort(int *tab, int n)
{
    int i, j, temp;
    for(i = 0 ; i < n - 1; i++)
    {
        for(j = 0 ; j < n-i-1; j++)
            if(tab[j] > tab[j+1])
                swap(&tab[j], &tab[j + 1]);
    }    
}

void selection_sort(int *tab, int n)
{
    int i, j, temp;
    for(i = 0; i < n; i++){
        for(j = i + 1; j < n; j++) {
            if(tab[i] > tab[j]) 
                swap(&tab[i], &tab[j]);
        }
    }
}

//grupa metod II

void quick_sort(int *arr, int l, int r) { //tu podajemy właściwą listę
    if (l < r) {
        int p = partition(arr, l, r);
        quick_sort(arr, l, p - 1);
        quick_sort(arr, p + 1, r);
  }
}

void shell_sort(int *arr, int n) {
    int i, j, m, temp;
    for (m = n / 2; m > 0; m /= 2) {
        for (j = m; j < n; j++) {
            for (i = j - m; i >= 0; i -= m) {
                if (arr[i + m] >= arr[i])
                    break;
                else 
                    swap(&arr[i], &arr[i + m]);
            }
        }
    }
}

void heap_sort(int *arr, int n) {
    int mockup_arr[n];
    for (int i = 0; i < n; i++)  //dla jak najbezpieczniejszej operacji duplikuję pointer array
        mockup_arr[i] = arr[i];
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(mockup_arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(&mockup_arr[0], &mockup_arr[i]);
        heapify(mockup_arr, i, 0);

    for (int i = 0; i < n; i++)  //przekazanie danych z mockup_arr do oryginalnej listy
         arr[i] = mockup_arr[i];
  }
}

///funkcje pomocnicze

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int *arr, int l, int r) {
    int p = arr[r], i = (l -1);
    for (int j = l; j < r; j++) {
    if (arr[j] <= p) {
        i++;
        swap(&arr[i], &arr[j]);
    }
  }
}

void heapify(int arr[], int n, int i) {
    int max_value = i;
    int l = 2 * i + 1; //lewa gałąź
    int r = 2 * i + 2; //prawa gałąź
    if (l < n && arr[l] > arr[max_value])
        max_value = l;
    if (r < n && arr[r] > arr[max_value])
        max_value = r;
    if (max_value != i) {
        swap(&arr[i], &arr[max_value]);
        heapify(arr, n, max_value);
    }
}

