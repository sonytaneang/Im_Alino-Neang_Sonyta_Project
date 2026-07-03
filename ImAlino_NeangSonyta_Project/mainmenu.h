#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#ifndef MAINMENU_H
#define MAINMENU_H

/* ---------- Box Drawing Helper ---------- */

/* Prints a neat Unicode box around a title and a list of option strings.
   Matches the reference style:
       ╔══════════════════════════════════════╗
       ║              TITLE HERE              ║
       ╠══════════════════════════════════════╣
       ║ 1. Option One                        ║
       ║ 2. Option Two                        ║
       ╚══════════════════════════════════════╝

   Usage:
       const char *opts[] = {"1. Foo", "2. Bar", "3. Exit"};
       print_boxed_menu("My Menu", opts, 3);
*/
void print_boxed_menu(const char *title, const char *options[], int count){
    int width = (int)strlen(title);
    int i;

    for(i = 0; i < count; i++){
        int len = (int)strlen(options[i]);
        if(len > width) width = len;
    }

    width += 2; /* 1 space padding on each side */

    /* Top border */
    printf("\n\xE2\x95\x94");
    for(i = 0; i < width; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x97\n");

    /* Title line (centered) */
    {
        int pad_total = width - (int)strlen(title);
        int pad_left = pad_total / 2;
        int pad_right = pad_total - pad_left;
        printf("\xE2\x95\x91");
        for(i = 0; i < pad_left; i++) printf(" ");
        printf("%s", title);
        for(i = 0; i < pad_right; i++) printf(" ");
        printf("\xE2\x95\x91\n");
    }

    /* Separator */
    printf("\xE2\x95\xA0");
    for(i = 0; i < width; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\xA3\n");

    /* Options */
    for(i = 0; i < count; i++){
        int pad_right = width - 1 - (int)strlen(options[i]);
        printf("\xE2\x95\x91 %s", options[i]);
        for(int j = 0; j < pad_right; j++) printf(" ");
        printf("\xE2\x95\x91\n");
    }

    /* Bottom border */
    printf("\xE2\x95\x9A");
    for(i = 0; i < width; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x9D\n");
}

/* ---------- Menus ---------- */

int read_menu_choice(){
    int choice;
    if (scanf("%d", &choice) != 1){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return -1;  
    }
    return choice;
}

int User_Menu(){
    const char *options[] = {
        "1. Guest",
        "2. Staff",
        "3. Exit"
    };
    print_boxed_menu("Welcome To Zoo-per Wildlife Sanctuary", options, 3);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Staff_Menu(){

    const char *options[] = {
        "1. Animal Management System",
        "2. Staff Management System",
        "3. Exit"
    };
    print_boxed_menu("Staff Menu", options, 3);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Animal_Management_Menu(){
    
    const char *options[] = {
        "1. View Animals List",
        "2. Search Animal",
        "3. Add Animal",
        "4. Update Animal",
        "5. Delete Animal",
        "6. Exit"
    };
    print_boxed_menu("Animal Management", options, 6);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Animal_Search_Menu(){
    
    const char *options[] = {
        "1. Search by ID",
        "2. Search by Species",
        "3. Search by Class",
        "4. Search by Food Category",
        "5. Search by Natural Habitat",
        "6. Search by Habitat Zone",
        "7. Exit"
    };
    print_boxed_menu("Search Animal", options, 7);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Update_Animal_Menu(){
  
    const char *options[] = {
        "1. General Information",
        "2. Health Information",
        "3. Feeding Information",
        "4. Exit"
    };
    print_boxed_menu("Update Animal Information", options, 4);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Update_General_Information_Menu(){
    
    const char *options[] = {
        "1. Update Name",
        "2. Update ID",
        "3. Update Sex",
        "4. Update Age",
        "5. Update Species",
        "6. Update Natural Habitat",
        "7. Update Zone",
        "8. Update Origin",
        "9. Update Food Category",
        "10. Update Class",
        "11. Exit"
    };
    print_boxed_menu("Update General Information", options, 11);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Update_Health_Information_Menu(){
    
    const char *options[] = {
        "1. Update Height",
        "2. Update Weight",
        "3. Update Health Condition",
        "4. Update Breeding Status",
        "5. Update Checkup Date",
        "6. Update Next Checkup Date",
        "7. Exit"
    };
    print_boxed_menu("Update Health Information", options, 7);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Update_Feeding_Information_Menu(){
    
    const char *options[] = {
        "1. Update Feeding Status",
        "2. Update Last Feeding Time",
        "3. Update Next Feeding Time",
        "4. Exit"
    };
    print_boxed_menu("Update Feeding Information", options, 4);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Staff_Management_Menu(){
    
    const char *options[] = {
        "1. View Staff List",
        "2. Search Staff",
        "3. Add Staff",
        "4. Update Staff",
        "5. Delete Staff",
        "6. View Salary",
        "7. View Activity Log",
        "8. Exit"
    };
    print_boxed_menu("Staff Management", options, 8);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Search_Staff_Menu(){
    
    const char *options[] = {
        "1. Search by ID",
        "2. Search by Name",
        "3. Search by Position",
        "4. Exit"
    };
    print_boxed_menu("Search Staff", options, 4);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Update_Staff_Menu(){
    
    const char *options[] = {
        "1. Check in/out Time/Date",
        "2. Personal Information",
        "3. Salary Information",
        "4. Exit"
    };
    print_boxed_menu("Update Staff Information", options, 4);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Update_Date_Time_Menu(){
    
    const char *options[] = {
        "1. Check-in",
        "2. Check-out",
        "3. Exit"
    };
    print_boxed_menu("Update Check-in/out Time/Date", options, 3);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}
int Update_Personal_Information_Menu(){
    
    const char *options[] = {
        "1. Update Name",
        "2. Update ID",
        "3. Update Age",
        "4. Update Gender",
        "5. Update Position",
        "6. Exit"
    };
    print_boxed_menu("Update Staff's Personal Information", options, 6);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Update_Salary_Information(){
    
    const char *options[] = {
        "1. Update Salary",
        "2. Update Salary Status",
        "3. Exit"
    };
    print_boxed_menu("Update Staff's Salary Information", options, 3);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

int Guest_Menu(){
    
    const char *options[] = {
        "1. View Animals",
        "2. Search Animal",
        "3. Exit"
    };
    print_boxed_menu("Guest Menu", options, 3);

    printf("Enter Your Choice : ");
    return read_menu_choice();
}

#endif
