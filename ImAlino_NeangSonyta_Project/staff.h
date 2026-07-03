#ifndef STAFF_H
#define STAFF_H
#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#include "mainmenu.h"
#include "struct.h"
#include "animal.h"
#include "activity_log.h"
#include"clear.h"
#include "pagination.h"


void Print_Staff_Function(Staff_Info staff[], int index){
    int width = 40;
    printf("\n\xE2\x95\x94");
    for(int i = 0; i < width; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x97\n");
    printf("    Name : %s\n", staff[index].name);
    printf("    ID : %s\n", staff[index].id);
    printf("    Position : %s\n", staff[index].position);
    printf("\xE2\x95\x9A");
    for(int i = 0; i < width; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x9D\n");
}

Staff_Info* paginate_staff_ptr = NULL;

int paginate_match_indices[max_staff];   // holds the real staff[] indices that matched

void Print_Staff_Match_For_Paginate(int i) {
    // i here is 0,1,2... (the "page index"), NOT the real staff index
    int real_index = paginate_match_indices[i];
    Print_Staff_Function(paginate_staff_ptr, real_index);
}

void Print_Staff_For_Paginate(int i) {
    Print_Staff_Function(paginate_staff_ptr, i);   // <-- calling the function above
}

void Print_Salary_Function(Staff_Info staff[], int index){
    int width = 40;
    printf("\n\xE2\x95\x94");
    for(int i = 0; i < width; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x97\n");
    printf("    Name : %s\n", staff[index].name);
    printf("    ID : %s\n", staff[index].id);
    printf("    Position : %s\n", staff[index].position);
    printf("    Salary : %d\n", staff[index].salary);
    printf("    Salary Status : %s\n", staff[index].salary_status);
    printf("\xE2\x95\x9A");
    for(int i = 0; i < width; i++) printf("\xE2\x95\x90");
    printf("\xE2\x95\x9D\n");
}

void View_Salary_For_Paginate(int i) {
    Print_Salary_Function(paginate_staff_ptr, i);
}

//Does the same thing as save animal
void Save_Staff(Staff_Info staff[], int* current_staff) {
    FILE* fp = fopen("staffs.txt", "w");
    if (fp == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    for (int i = 0; i < *current_staff; i++) {
        fprintf(fp, "%s, %s, %s, %d, %c, %s, %d:%d:%d, %d/%d/%d, %d:%d:%d, %d/%d/%d, %d, %s\n",
            staff[i].name,
            staff[i].id,
            staff[i].password,
            staff[i].age,
            staff[i].gender,
            staff[i].position,
            staff[i].check_in_time.hour,
            staff[i].check_in_time.min,
            staff[i].check_in_time.sec,
            staff[i].check_in_date.day,
            staff[i].check_in_date.month,
            staff[i].check_in_date.year,
            staff[i].check_out_time.hour,
            staff[i].check_out_time.min,
            staff[i].check_out_time.sec,
            staff[i].check_out_date.day,
            staff[i].check_out_date.month,
            staff[i].check_out_date.year,
            staff[i].salary,
            staff[i].salary_status);
    }

    fclose(fp);
    printf("Staff data saved.\n");
}

void Load_Staff(Staff_Info staff[], int* current_staff) {
    FILE* fp = fopen("staffs.txt", "r");
    if (fp == NULL) {
        printf("No saved staff data found.\n");
        return;
    }

    int i = 0;

    while (i < max_staff &&
        fscanf(fp, " %29[^,], %9[^,], %9[^,], %d, %c, %9[^,], %d:%d:%d, %d/%d/%d, %d:%d:%d, %d/%d/%d, %d, %9s\n",
            staff[i].name,
            staff[i].id,
            staff[i].password,
            &staff[i].age,
            &staff[i].gender,
            staff[i].position,
            &staff[i].check_in_time.hour,
            &staff[i].check_in_time.min,
            &staff[i].check_in_time.sec,
            &staff[i].check_in_date.day,
            &staff[i].check_in_date.month,
            &staff[i].check_in_date.year,
            &staff[i].check_out_time.hour,
            &staff[i].check_out_time.min,
            &staff[i].check_out_time.sec,
            &staff[i].check_out_date.day,
            &staff[i].check_out_date.month,
            &staff[i].check_out_date.year,
            &staff[i].salary,
            staff[i].salary_status) == 20) {
        i++;
    }
    *current_staff = i;
    printf("Load %d staffs data\n", *current_staff);

    fclose(fp);
}

// Add Staff to staff list
void Add_Staff(Staff_Info staff[], int* current_staff, int compare_position, char* logged_in_name, char* logged_in_id){
    bool isduplicate;
    if(*current_staff == max_staff){
        printf("Staff is at Max Capacity!\n");
        return;
    }
    if (compare_position == 0){
        printf("\n===== Adding New Staff =====\n");
        printf("Enter Name : ");
        scanf(" %29[^\n]", staff[*current_staff].name);
        printf("\n");

        do {
            printf("Enter ID : ");
            scanf("%9s", staff[*current_staff].id);
            isduplicate = false;
            printf("\n");

            for (int i = 0; i < *current_staff; i++){
                if (strcmp(staff[*current_staff].id, staff[i].id) == 0){
                    printf("ID already exists. Please enter a different ID.\n");
                    isduplicate = true;
                    break;
                }
            }
        }while (isduplicate);

        printf("Enter Password : ");
        scanf("%9s", staff[*current_staff].password);
        printf("\n");

        printf("Enter Age : ");
        scanf("%d", &staff[*current_staff].age);
        printf("\n");

        printf("Enter Gender (F/M) : ");
        scanf(" %c", &staff[*current_staff].gender);
        printf("\n");

        printf("Enter Position : ");
        scanf(" %9[^\n]", staff[*current_staff].position);
        printf("\n");

        printf("Enter Check-in Time (HH:MM:SS) : ");
        scanf("%d:%d:%d", &staff[*current_staff].check_in_time.hour,
                            &staff[*current_staff].check_in_time.min,
                            &staff[*current_staff].check_in_time.sec);
        printf("\n");

        printf("Enter Check-in Date (DD/MM/YY) : ");
        scanf("%d/%d/%d", &staff[*current_staff].check_in_date.day,
                            &staff[*current_staff].check_in_date.month,
                            &staff[*current_staff].check_in_date.year);
        printf("\n");

        printf("Enter Check-Out Time (HH:MM:SS) : ");
        scanf("%d:%d:%d", &staff[*current_staff].check_out_time.hour,
                            &staff[*current_staff].check_out_time.min,
                            &staff[*current_staff].check_out_time.sec);
        printf("\n");

        printf("Enter Check-Out Date (DD/MM/YY) : ");
        scanf("%d/%d/%d", &staff[*current_staff].check_out_date.day,
                            &staff[*current_staff].check_out_date.month,
                            &staff[*current_staff].check_out_date.year);
        printf("\n");    

        printf("Enter Staff's Salary : ");
        scanf("%d", &staff[*current_staff].salary);
        printf("\n");

        printf("Enter Staff's Salary Status : ");
        scanf("%9s", staff[*current_staff].salary_status);
        printf("\n");

        printf("Staff Added Successfully!\n");
        (*current_staff)++;
        Save_Staff(staff, current_staff);
        Activity_Log(logged_in_name, logged_in_id, "Added Staff", staff[*current_staff - 1].id);
    }
    else {
        printf("Authorized Access Only!\n");
        return;
    }
}

//Search staff by full name and partial name
void Search_Staff_By_Name(Staff_Info staff[], int* current_staff){
    char search_name[30];
    bool found = false;
    printf("\n===== Search Staff by Name =====\n");
    printf("Enter Name: ");
    scanf(" %29[^\n]", search_name);

    int match_count = 0;

    for(int i = 0; i < *current_staff; i++){
        if(strstr(staff[i].name, search_name) != NULL){
            found = true;
            paginate_match_indices[match_count] = i;   // remember the REAL index
            match_count++;
            printf("\n");
        }
    }
    paginate_staff_ptr = staff;
    Paginate(match_count, Print_Staff_Match_For_Paginate);

    if(!found){
        printf("No Staff Found.\n");
    }
}

// Use int to return the index in staff list, when staff is found it returns the found index
// and it can be used in delete staff and update staff function

int Search_ID(Staff_Info staff[], int* current_staff, char search_id[]){
    int found_index = -1;
    for (int i = 0; i < *current_staff; i++){
        if(strcmp(search_id, staff[i].id) == 0){
            found_index = i;
            break;
        }
    }
    if(found_index == -1){
        printf("No Staffs Found.\n");
    }
    return found_index;
}
void Search_Staff_By_ID(Staff_Info staff[], int* current_staff, int compare_position){
    char search_id[10];
    char answer;
    printf("\n===== Search Staff by ID =====\n");
    printf("Enter Search ID : ");
    scanf("%9s",search_id);
    printf("\n");

    printf("Search ID is : %s", search_id);
    printf("\n");

    int index = Search_ID(staff, current_staff, search_id);

    if (index == -1){
        return;
    }
    int width = 30;
    printf("Staff Found!\n");
    printf("Do you want to print the Staff's Information? (Y/N): ");
    scanf(" %c", &answer);
    if (answer == 'Y' || answer == 'y'){
        printf("\n\xE2\x95\x94");
        for(int i = 0; i < width; i++) printf("\xE2\x95\x90");
        printf("\xE2\x95\x97\n");
        printf("    ID : %s\n",staff[index].id);
        printf("    Name : %s \n",staff[index].name);
        printf("    Age : %d\n",staff[index].age);
        printf("    Gender : %c\n",staff[index].gender);
        printf("    Position : %s\n",staff[index].position);
        printf("    Check-in Time : %d:%d:%d\n", staff[index].check_in_time.hour, staff[index].check_in_time.min, staff[index].check_in_time.sec);
        printf("    Check-in Date : %d/%d/%d\n", staff[index].check_in_date.day, staff[index].check_in_date.month, staff[index].check_in_date.year);
        printf("    Check-out Time : %d:%d:%d\n", staff[index].check_out_time.hour, staff[index].check_out_time.min, staff[index].check_out_time.sec);
        printf("    Check-out Date : %d/%d/%d\n", staff[index].check_out_date.day, staff[index].check_out_date.month, staff[index].check_out_date.year);
        if (compare_position == 0){
            printf("    Password : %s\n", staff[index].password);
            printf("    Salary : %d\n", staff[index].salary);
            printf("    Salary Status : %s\n", staff[index].salary_status);
            printf("\xE2\x95\x9A");
            for(int i = 0; i < width; i++) printf("\xE2\x95\x90");
            printf("\xE2\x95\x9D\n");
        }else {
            printf("\xE2\x95\x9A");
            for(int i = 0; i < width; i++) printf("\xE2\x95\x90");
            printf("\xE2\x95\x9D\n");
        }
    }
}


void Search_Staff_By_Position (Staff_Info staff[], int* current_staff){
    char search_position[10];
    bool found = false;
    printf("\n===== Search Staff by Position =====\n");
    printf("Enter Search Position : ");
    scanf("%9s", search_position);
    
    printf("Search Position is : %s", search_position);
    printf("\n");

    int match_count = 0;

    for (int i = 0; i < *current_staff; i++){
        if(strcmp(search_position, staff[i].position) == 0){
            found = true;
            paginate_match_indices[match_count] = i;   // remember the REAL index
            match_count++;
        }
    }
    if (!found){
        printf("No Staff Found At This Position!\n");
    }
    paginate_staff_ptr = staff;
    Paginate(match_count, Print_Staff_Match_For_Paginate);
}

void Search_Staff(Staff_Info staff[], int* current_staff, int compare_position){
    int running = 1;
    while (running == 1){
        int staff_search_choice = Search_Staff_Menu();
        clearScreen();
        switch(staff_search_choice){
            case 1 :
                clearScreen();  
                Search_Staff_By_ID(staff, current_staff, compare_position);
                pauseAndClear();
                break;
            case 2 :
                clearScreen();
                Search_Staff_By_Name(staff, current_staff);
                clearScreen();
                break;
            case 3 :
                clearScreen(); 
                Search_Staff_By_Position(staff, current_staff);
                clearScreen();
                break;
            case 4 :
                printf("Exited The System Successfully!\n");
                running = 0;
                break;
            default :
                printf("Invalid Choice.\n");
                break;
        }
    }
}

//Use found_index in search staff function to move one element to next the next until the last index
//of the function, to ensure that no index in staff list is empty
void Delete_Staff(Staff_Info staff[], int* current_staff, int compare_position, char* logged_in_name, char* logged_in_id){
    //Password will need to be set in main function 
    if(compare_position == 0){
        printf("\n===== Delete Staff =====\n");
        char delete_id[10];
        char answer;
        printf("Enter ID : ");
        scanf("%9s", delete_id);

        printf("Are you sure you want to delete this Staff with ID %s? (Y/N) : ", delete_id);
        scanf(" %c", &answer);

        if (answer == 'Y' || answer == 'y'){
            int index = Search_ID(staff, current_staff, delete_id);
            if (index == -1){
                return;
            }
            for (int i = index; i < *current_staff - 1; i++){
                staff[i] = staff[i+1];
            }
            (*current_staff)--;
            printf("Staff Deleted Successfully!\n");
            Save_Staff(staff, current_staff);
            Activity_Log(logged_in_name, logged_in_id, "Deleted Staff", delete_id);
        }else {
            return;
        }
    }else {
        printf("Authorized Access Only!\n");
        return;
    }
}

//Use found_index to update staff info
void Update_Staff(Staff_Info staff[], int* current_staff, int compare_position, char* logged_in_name, char* logged_in_id){
    char search_id[10];
    printf("\n===== Updating Staff =====\n");
    printf("Enter Search ID : ");
    scanf("%9s",search_id);
    printf("\n");

    printf("Search ID is : %s", search_id);
    printf("\n");

    int index = Search_ID(staff, current_staff, search_id);

    if (index == -1){
    return;
    }

    int running = 1;
    while (running == 1){
        int staff_update_choice = Update_Staff_Menu();
        clearScreen();

        switch (staff_update_choice){
            case 1 :
                int running1 = 1;
                while (running1 == 1){
                    int update_time_date_choice = Update_Date_Time_Menu();
                    clearScreen();
                    printf("\n===== Updating Staff's Check-in/out Time/Date =====\n");
                        switch (update_time_date_choice){
                            case 1 : 
                                printf("Enter Update Time (HH:MM:SS): ");
                                scanf("%d:%d:%d", &staff[index].check_in_time.hour,
                                                    &staff[index].check_in_time.min,
                                                    &staff[index].check_in_time.sec);
                                printf("\n");

                                printf("Enter Update Date (DD/MM/YY) : ");
                                scanf("%d/%d/%d", &staff[index].check_in_date.day,
                                                    &staff[index].check_in_date.month,
                                                    &staff[index].check_in_date.year);
                                printf("Update Successfully\n");
                                Save_Staff(staff, current_staff);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Staff's Check in", staff[index].id);
                                break;
                            case 2 : 
                                printf("Enter Update Time (HH:MM:SS) : ");
                                scanf("%d:%d:%d", &staff[index].check_out_time.hour,
                                                    &staff[index].check_out_time.min,
                                                    &staff[index].check_out_time.sec);
                                printf("\n");

                                printf("Enter Update Date (DD/MM/YY) : ");
                                scanf("%d/%d/%d", &staff[index].check_out_date.day,
                                                    &staff[index].check_out_date.month,
                                                    &staff[index].check_out_date.year);
                                printf("\n");
                                printf("Update Successfully\n");
                                Save_Staff(staff, current_staff);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Staff's Check Out", staff[index].id);
                                break;
                            case 3 :
                                clearScreen();
                                printf("Exited The System Successfully\n");
                                running1 = 0;
                                break;
                            default:
                                clearScreen();
                                printf("Invalid Choice.\n");
                                break;
                        }
                    }
            break;
            case 2 :
                if (compare_position == 0){
                    int running2 = 1;
                    while (running2 == 1){
                        int update_info_choice = Update_Personal_Information_Menu();
                        clearScreen();
                        printf("\n===== Updating Staff's Personal Information =====\n");
                        switch(update_info_choice){
                            case 1 :
                                printf("Enter New Name : ");
                                scanf(" %29[^\n]", staff[index].name);
                                printf("\nUpdate Successfully\n");
                                Save_Staff(staff, current_staff);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Staff's Name", staff[index].id);
                                break;
                            case 2 :
                                printf("Enter New ID : ");
                                char new_id[10];
                                bool isduplicate;
                                do {
                                    scanf("%9s", new_id);
                                    isduplicate = false;
                                    for (int i = 0; i < *current_staff; i++){
                                        if (i != index && strcmp(new_id, staff[i].id) == 0){
                                            printf("ID already exists. Please enter a different ID : ");
                                            isduplicate = true;
                                            break;
                                        }
                                    }
                                } while (isduplicate);
                                strcpy(staff[index].id, new_id);
                                printf("\nUpdate Successfully\n");
                                Save_Staff(staff, current_staff);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Staff's ID", staff[index].id);
                                break;
                            case 3 :
                                printf("Enter New Age : ");
                                scanf("%d", &staff[index].age);
                                printf("\nUpdate Successfully\n");
                                Save_Staff(staff, current_staff);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Staff's Age", staff[index].id);
                                break;
                            case 4 :
                                printf("Enter New Gender : ");
                                scanf(" %c", &staff[index].gender);
                                printf("\nUpdate Successfully\n");
                                Save_Staff(staff, current_staff);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Staff's Gender", staff[index].id);
                                break;
                            case 5 :
                                printf("Enter Position : ");
                                scanf("%9s", staff[index].position);
                                printf("\nUpdate Successfully\n");
                                Save_Staff(staff, current_staff);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Staff's Position", staff[index].id);
                                break;
                            case 6 :
                                clearScreen();
                                printf("Exited The System Successfully!\n");
                                running2 = 0;
                                break;
                            default :
                                clearScreen();
                                printf("Invalid Choice.\n");
                                break;
                        }
                    }
                }else {
                    printf("Authorized Access Only!\n");
                    break;
                }
            break;
            case 3 :
                if (compare_position == 0){
                    int running3 = 1;
                    while (running3 == 1){
                        int update_salary_info = Update_Salary_Information();
                        clearScreen();
                        printf("\n===== Updating Staff's Salary Information =====\n");
                        switch (update_salary_info){
                            case 1 :
                                printf("Enter New Salary : ");
                                scanf("%d", &staff[index].salary);
                                printf("Update Successfully\n");
                                Save_Staff(staff, current_staff);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Staff's Salary", staff[index].id);                            
                                break;
                            case 2 :
                                printf("Enter New Salary Status : ");
                                scanf("%9s", staff[index].salary_status);
                                printf("Update Successfully\n");
                                Save_Staff(staff, current_staff);
                                Activity_Log(logged_in_name, logged_in_id, "Updated Staff's Salary Status", staff[index].id);
                                break;
                            case 3 :
                                clearScreen(); 
                                printf("Exited The System Successfully!\n");
                                running3 = 0;
                                break;
                            default :
                                clearScreen(); 
                                printf("Invalid Choice.\n");
                                break;
                        }
                    }
                }else {
                    printf("Authorized Access Only!\n");
                    break;
                }
            break;
            case 4 : 
                printf("Exited The System Successfully!\n");
                running = 0;
                break;
            default : 
                printf("Invalid Choice.\n");
                break;
        }
    }
}

void Print_All_Staff(Staff_Info staff[], int* current_staff){
    paginate_staff_ptr = staff;
    Paginate(*current_staff, Print_Staff_For_Paginate);
}


void View_Salary(Staff_Info staff[], int* current_staff, int compare_position){
    if (compare_position == 0){
        paginate_staff_ptr = staff;
        Paginate(*current_staff, View_Salary_For_Paginate);
    }else {
        printf("\nAuthorized Access Only\n");
        return;
    }
}

void Staff_Management(Staff_Info staff[], int* current_staff, int compare_position, char* logged_in_name, char* logged_in_id){
    int running = 1;
    while (running == 1){
        int staff_management_choice = Staff_Management_Menu();
        clearScreen();
        switch(staff_management_choice){
            case 1 :
                clearScreen();
                Print_All_Staff(staff, current_staff);
                clearScreen();
                break;
            case 2 :
                clearScreen();
                Search_Staff(staff, current_staff, compare_position);                
                break;
            case 3 :
                clearScreen();
                Add_Staff(staff, current_staff, compare_position, logged_in_name, logged_in_id);
                pauseAndClear();
                break;
            case 4 :
                clearScreen();
                Update_Staff(staff, current_staff, compare_position, logged_in_name, logged_in_id);
                break;
            case 5 :
                clearScreen();
                Delete_Staff(staff, current_staff, compare_position, logged_in_name, logged_in_id);
                pauseAndClear();
                break;
            case 6 :
                clearScreen();
                View_Salary(staff, current_staff, compare_position);
                if (compare_position == 0){
                    clearScreen();
                }else {
                    pauseAndClear();
                }
                break;
            case 7 :
                clearScreen();
                View_Activity_Log(compare_position);
                clearScreen();
                break;
            case 8 :
                printf("Exited The System Successfully!\n");
                running = 0;
                break;
            default :
                printf("Invalid Choice.\n");
                break;
        }
    }
}

void Staff_Log_In(Staff_Info staff[], int* current_staff, Animal_Info animal[], int* current_animal_count){
    char log_in_id[10];
    char log_in_password[10];
    int index;
    bool is_logged_in = false;

    printf("\n===== Staff Log In =====\n");

    while(1){
        printf("Enter Your ID : ");
        scanf("%9s", log_in_id);

        index = Search_ID(staff, current_staff, log_in_id);

        if(index != -1){
            break;
        }

        int try_choice;
        printf("Enter again? (1/0): ");
        scanf("%d", &try_choice);

        if(try_choice == 0){
            return;
        }
    }

    int chance = 3;
    printf("Enter Your Password : ");
    scanf("%9s", log_in_password);
    
    char logged_in_name[30];
    char logged_in_id[10];
    strcpy(logged_in_name, staff[index].name);
    strcpy(logged_in_id, staff[index].id);

    int compare_position = strcmp("Manager", staff[index].position);
    do {
        if(strcmp(log_in_password, staff[index].password) == 0){
            is_logged_in = true;
            printf("You are logged in as a %s", staff[index].position);
            int running = 1;
            while (running == 1){
                int staff_menu_choie = Staff_Menu();
                clearScreen();
                switch (staff_menu_choie){
                case 1:
                    clearScreen();
                    Animal_Management(animal, current_animal_count, logged_in_name, logged_in_id);
                    break;
                case 2 :
                    clearScreen();
                    Staff_Management(staff, current_staff, compare_position, logged_in_name, logged_in_id);
                    break;
                case 3 : 
                    printf("Exited The System Successfully!\n");
                    running = 0;
                    break;
                default:
                    printf("Invalid Choice!\n");
                    break;
                }
            }
            break;
        }
        chance--;
        if (chance > 0){
            clearScreen();
            printf("Incorrect password. %d attempt(s) remaining.\n", chance);
            printf("Enter Your Password Again : ");
            scanf("%9s", log_in_password);
        }
    } while(chance > 0);
    if (!is_logged_in){
        printf("Too many failed attempts. Access denied.\n");
        pauseAndClear();
        return;
    }
}


#endif