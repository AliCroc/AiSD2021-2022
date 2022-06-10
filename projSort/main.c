#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#include "algorytmy.h"

#define RANGE_VALUE_TOP 100
#define RANGE_VALUE_BOTTOM -100
#define POSSIBLE_NUMBERS_TOTAL 201  //ilość liczb w przedziale <-100, 100>
#define MAX_ARRAY_LENGTH 20000

FILE *file_dane;  //globalna zmienna z pointerem do pliku
char file_name[5] = "dane";

void generate_arrays(int size);
int start_menu(int size);
void sort_menu(int size, int array[]);

int getArray(int size, int tab[], int wanted_arr_nr);
void copyArray(int size, int original_array[], int array_copy[]);
void add_array_to_file(int* array, int size);
void add_message_to_file(char *message);

void clear();

int main(int argc, char* argv[])
{
    int size;
    file_dane = fopen(file_name, "w");  //do zapisu
    if(file_dane == NULL) {
        printf("Wystapil blad przy kreacji pliku!");
        exit(1);
    }
    
    printf("Podaj ile elementow ma mieć lista do przesortowania\nMaksymalna dlugosc listy do przesortowania: %d\n\n", MAX_ARRAY_LENGTH);
    scanf("%d", &size);
    if(size > MAX_ARRAY_LENGTH) {
        printf("\nPodana dlugosc listy przekracza limit %d!", MAX_ARRAY_LENGTH);
        fclose(file_dane);
        exit(1);
    }
    srand(time(NULL));
    generate_arrays(size); //generowanie i zapisaywanie tablic do pliku "dane"
    fclose(file_dane);
    // (void)getch(); //debug
    start_menu(size);
    // printf("wyszlismy z start_menu"); //debug
    fclose(file_dane);
    return 0;
}

int start_menu(int size) {
    int selected_array[size];
    int *pointer_selected = selected_array;
    int selected_option = 0, flag;
    clear();

    while(selected_option != '4') {
        flag = 0;
        printf("Wybierz ktory test chcesz wykonac z opcji ponizej:\n");
        printf("1) Test 1 - dane generowane losowo\n");
        printf("2) Test 2 - dane posortowane w kolejnosci odwrotnej (malejaco)\n");
        printf("3) Test 3 - posortowanych wlasciwie (rosnaco)\n");
        printf("4) Wyjdz z programu\n\n");
        selected_option = getche();
        switch(selected_option) {
            case '1':
                getArray(size, pointer_selected, 0);
                flag = 1;
                break;
            case '2':
                getArray(size, pointer_selected, 1);
                flag = 1;
                break;
            case '3':
                getArray(size, pointer_selected, 2);
                flag = 1;
                break;
            case '4':
                printf("\n\nOpuszczanie programu...\n");
                break;
        }

        if(flag == 1) {
            sort_menu(size, pointer_selected);
            clear();
        }
    }
}

void sort_menu(int size, int array[]) {
    int selected_opt = 0, *arr_pointer, exit_flag;
    int temp_array[size];
    clear();
    while(selected_opt != '7') {
        exit_flag = 0;
        copyArray(size, array, temp_array);
        arr_pointer = temp_array;
        printf("Wybierz ktory algorytm sortowania chcesz przetestowac:\n");
        printf("1) Przez wstawianie (insert sort)\n");
        printf("2) Przez selekcje (selection sort)\n");
        printf("3) Babelkowe (bubble sort)\n");
        printf("4) Quicksort\n");
        printf("5) Sortowanie Shella (shell sort)\n");
        printf("6) Sortowanie przez kopcowanie (heap sort)\n");
        printf("7) Powrot do poprzedniego menu\n\n");
        selected_opt = getche();
        clock_t time_start = clock();
        switch(selected_opt) {
            case '1':
                insert_sort(arr_pointer, size);
                break;
            case '2':
                selection_sort(arr_pointer, size);
                break;
            case '3':
                bubble_sort(arr_pointer, size);
                break;
            case '4':
                quick_sort(arr_pointer, 0, size - 1);
                break;
            case '5':
                shell_sort(arr_pointer, size);
                break;
            case '6':
                heap_sort(arr_pointer, size);
                break;
            case '7':
                exit_flag = 1;
                printf("\n\nWracanie do poprzedniego menu...");
                break;
            default:
                exit_flag = 2;
                continue;
                break;
            }
        clock_t time_end = clock();
        if (exit_flag == 0) {
            printf("\nCzas wykonania wybranego algorytmu trwal %lf\n", ((double)(time_end - time_start)) / CLOCKS_PER_SEC); //dziala na unix, nie dziala na windows
            printf("\nWygenerowana tablica przed sortowaniem:\t");
            for(int index = 0; index < size; index++)
                printf("%d, ", array[index]);
            printf("\nPosortowana tablica:\t");
            for(int index = 0; index < size; index++)
                printf("%d, ", temp_array[index]);
        }
        else if (exit_flag == 1) break;

        printf("\n\nWcisnij dowolny klawisz, aby kontynuowac...\n\n");
        //(void)getch() to uniwersalny sposob na zatrzymanie akcji programu bez martwienia sie o środowisko
        //programistyczne użytkownika, klikniety dowolny klawisz kontynuuje prace programu
        (void)getch();
    }
}

//////

int random(int min, int max) {
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void make_array_random(int size) {
    int array[size];

    for (int i = 0; i < size; ++i)
        array[i] = random(RANGE_VALUE_BOTTOM, RANGE_VALUE_TOP);
    add_array_to_file(array, size);
}

void make_array_decreasing(int size) {
    int array[size];
    int count_of_repeated_numbers, rest_of_number_repetitions, cell_value, i = 0, j = 0, flag = 1;
    int first_element = random(RANGE_VALUE_BOTTOM, RANGE_VALUE_TOP);  //the biggest value element
    count_of_repeated_numbers = size/(abs(RANGE_VALUE_BOTTOM) + first_element + 1);
    rest_of_number_repetitions = size % (abs(RANGE_VALUE_BOTTOM) + first_element + 1);
    cell_value = first_element;

    while(flag == 1) {
        for(j = 0; j <= count_of_repeated_numbers; j++) {
            if((i + j) < size) {
                array[i + j] = cell_value;
                if(rest_of_number_repetitions > 0) {
                    i++;
                    array[i + j] = cell_value;
                    rest_of_number_repetitions--;
                }
            }
            else { flag = 0; break; }
        }
        i = i + j;
        cell_value--;
    }
    add_array_to_file(array, size);
}

void make_array_sorted(int size) {
    int array[size];
    int count_of_repeated_numbers, i = 0, j = 0, cell_value, flag = 1, rest_of_number_repetitions; //
    int first_element = random(RANGE_VALUE_BOTTOM, RANGE_VALUE_TOP);  //the biggest value element
    count_of_repeated_numbers = size/(abs(RANGE_VALUE_BOTTOM) + first_element + 1);
    rest_of_number_repetitions = size % (abs(RANGE_VALUE_BOTTOM) + first_element + 1);
    cell_value = first_element;
    while(flag == 1) {
        for(j = 0; j <= count_of_repeated_numbers; j++) {
            if((i + j) < size) {
                array[i + j] = cell_value;
                if(rest_of_number_repetitions > 0) {
                    i++;
                    array[i + j] = cell_value;
                    rest_of_number_repetitions--;
                }
            }
            else { flag = 0; break; }
        }
        i = i + j;
        cell_value++;
    }
    add_array_to_file(array, size);
}


void generate_arrays(int size) {  //kolejność wywoływanych tu funkcji jest ważna dla poprawnego działania programu
    make_array_random(size);
    make_array_decreasing(size);
    make_array_sorted(size);
}

void add_array_to_file(int* array, int size) {
    for(int i = 0; i < size - 1; i++)
        fprintf(file_dane, "%d,", array[i]);
    fprintf(file_dane, "%d", array[size - 1]);
    fprintf(file_dane, "\n");
}

void add_message_to_file(char *message) {
    fprintf(file_dane, "\n");
    fprintf(file_dane, "%s\n", message);
}

int getArray(int size, int tab[], int wanted_arr_nr) { //ok
    file_dane = fopen(file_name, "r");  //do odczytu
    int flag = 1, i = 0, arr_nr = 0;
    char *token;
    char help_string[100001];
    while (fgets(help_string, sizeof(help_string), file_dane)) {
        if(arr_nr == wanted_arr_nr) {
            printf("%s", help_string); //debug
            token = strtok(help_string, ",");
            int i = 0;
            while(token != NULL) {
                printf("%s", help_string[i]);
                tab[i] = atoi(token);
                token = strtok(NULL, ",");
                i++;
            }
        }
        arr_nr++;
    }
    fclose(file_dane);
    return i;
}

void copyArray(int size, int original_array[], int array_copy[]) {
    for(int i = 0; i < size; i++)
        array_copy[i] = original_array[i];
}

void clear() {
    printf("\n\n\n\n\n\n\n\n\n\n\n");
}