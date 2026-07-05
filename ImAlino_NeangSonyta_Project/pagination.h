#ifndef PAGINATION_H
#define PAGINATION_H

#include <stdio.h>
#include "clear.h"

#define PAGE_SIZE 7   // how many records per page - change as you like

/*
   Generic pagination wrapper.

   total_items   : how many records you have (e.g. *current_staff)
   print_item(i) : a function pointer that prints ONE record at index i
                   (you write this per data type - see examples below)

   Controls after each page:
     [N] Next page
     [P] Previous page
     [Q] Quit / stop viewing
*/
void Paginate(int total_items, void (*print_item)(int)) {
    if (total_items <= 0) {
        printf("(No records to display.)\n");
        return;
    }

    int total_pages = (total_items + PAGE_SIZE - 1) / PAGE_SIZE;
    int current_page = 0; // 0-indexed
    int need_to_print = 1; // only print the page when something actually changed

    while (1) {
        if (need_to_print) {
            clearScreen();
            printf("\n--------------------------------------------------\n");
            printf("Page %d of %d\n", current_page + 1, total_pages);
            printf("--------------------------------------------------\n");

            int start = current_page * PAGE_SIZE;
            int end = start + PAGE_SIZE;
            if (end > total_items) {
                end = total_items;
            }

            for (int i = start; i < end; i++) {
                print_item(i);
            }

            printf("--------------------------------------------------\n");
        }

        printf("[N] Next  [P] Previous  [Q] Quit or See Total : ");

        char choice;
        scanf(" %c", &choice);

        if (choice == 'n' || choice == 'N') {
            if (current_page < total_pages - 1) {
                current_page++;
                need_to_print = 1;
            } else {
                printf("Already on the last page.\n");
                need_to_print = 0;
            }
        }
        else if (choice == 'p' || choice == 'P') {
            if (current_page > 0) {
                current_page--;
                need_to_print = 1;
            } else {
                printf("Already on the first page.\n");
                need_to_print = 0;
            }
        }
        else if (choice == 'q' || choice == 'Q') {
            break;
        }
        else {
            printf("Invalid choice.\n");
            need_to_print = 0;
        }
    }
}

#endif
