#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define max_animal 200
#define max_staff 50

#include "struct.h"
#include "mainmenu.h"  
#include "animal.h"     
#include "staff.h"
#include "activity_log.h" 
#include "clear.h"
   

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8); // included for printing specials character in output
    #endif
    Animal_Info animal[max_animal];
    int current_animal_count = 0;

    Staff_Info staff[max_staff];
    int current_staff = 0;

    Load_Animal_Data(animal, &current_animal_count);
    Load_Staff(staff, &current_staff);

    int running = 1;
    while (running == 1){
        clearScreen();
        int user_menu_choice = User_Menu();
        switch (user_menu_choice){
            case 1 :
                clearScreen(); 
                Guest(animal, &current_animal_count);
                break;
            case 2 :
                clearScreen(); 
                Staff_Log_In(staff, &current_staff, animal, &current_animal_count);
                break;
            case 3 :
                clearScreen();
                printf("Exited The System Successfully!\n");
                running = 0;
                break;
            default :
                printf("Invalid Choice.\n");
                break;
        }
    }
    return 0;
}