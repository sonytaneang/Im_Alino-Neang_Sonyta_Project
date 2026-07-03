#include <stdlib.h>

#ifndef CLEAR_H
#define CLEAR_H

void clearScreen(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseAndClear() {
    printf("\nPress Enter to Continue.");
    getchar(); // Clears any leftover '\n' from scanf
    getchar(); // Waits for the actual Enter keypress
    clearScreen();
}

#endif