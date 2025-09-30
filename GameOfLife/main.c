#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

#define DEAD 0
#define ALIVE 1


HANDLE hConsole;

WORD saved_attributes;

void clear_screen() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hConsole, coord);
}

void print_matrix(char *m, const int ml, const int mc) {
    clear_screen(); 
    for (int i = 0; i < mc + 2; i++)
        printf("--");
    printf("\n");

    for (int i = 0; i < ml; i++) {
        printf("| ");
        for (int j = 0; j < mc; j++) {
            if (*(m + i * mc + j)) {
                
                SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                printf("  ");
                
                SetConsoleTextAttribute(hConsole, saved_attributes);
            } else {
                printf("  ");
            }
        }
        printf(" |\n");
    }

    for (int i = 0; i < mc + 2; i++)
        printf("--");
    printf("\n");
}

int alter(char *m, const int ml, const int mc, const int ipos, const int jpos) {
    int nb = 0;
    int i, j;
    for (i = ipos - 1; i <= ipos + 1; i++) {
        if (i >= 0 && i < ml) {
            for (j = jpos - 1; j <= jpos + 1; j++) {
                if (j >= 0 && j < mc) {
                    if (i != ipos || j != jpos) {
                        if (*(m + i * mc + j)) {
                            nb++;
                        }
                    }
                }
            }
        }
    }

    if (*(m + ipos * mc + jpos)) {
        return (nb == 2 || nb == 3);
    } else {
        return (nb == 3);
    }
}

void update_matrix(char *m, char *bis, const int ml, const int mc) {
    for (int i = 0; i < ml; i++) {
        for (int j = 0; j < mc; j++) {
            *(bis + i * mc + j) = alter(m, ml, mc, i, j);
        }
    }
    for (int i = 0; i < ml; i++)
        for (int j = 0; j < mc; j++)
            *(m + i * mc + j) = *(bis + i * mc + j);
}

void update_matrix2(char *m, char *bis, const int ml, const int mc) {
    int i, j, k, l;
    for (i = 0; i < ml; i++) {
        for (j = 0; j < mc; j++) {
            if (*(m + i * mc + j)) {
                *(bis + i * mc + j) = alter(m, ml, mc, i, j);
                for (k = i - 1; k <= i + 1; k++) {
                    for (l = j - 1; l <= j + 1; l++) {
                        if (k != i || l != j) {
                            if (k >= 0 && k < ml) {
                                if (l >= 0 && l < mc) {
                                    if (!*(m + k * mc + l))
                                        *(bis + k * mc + l) = alter(m, ml, mc, k, l);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < ml; i++)
        for (int j = 0; j < mc; j++)
            *(m + i * mc + j) = *(bis + i * mc + j);
}

void set_matrix(char *m, const int mml, const int mmc, int ybeg, int xbeg, char *s, const int ml, const int mc) {
    for (int i = ybeg; i < ybeg + ml; i++) {
        for (int j = xbeg; j < xbeg + mc; j++) {
            *(m + i * mmc + j) = *(s + (i - ybeg) * mc + (j - xbeg));
        }
    }
}


BOOL WINAPI ConsoleHandler(DWORD dwCtrlType) {
    if (dwCtrlType == CTRL_C_EVENT) {
        fprintf(stderr, "\nInterruption par Ctrl+C, arret du programme.\n");
        
        SetConsoleTextAttribute(hConsole, saved_attributes);
        exit(0);
    }
    return FALSE; 
}

int main(void) {
    
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
        fprintf(stderr, "ERREUR: Impossible de configurer le gestionnaire d'evenements.\n");
        return 1;
    }

    #define ml 40
    #define mc 110
    char matrix[ml][mc] = {DEAD};
    char bis[ml][mc] = {DEAD};

    char planneur[3][3] = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1},
    };
    char set[9][36] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };
    char set2[9][18] = {
        {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
		{0,1,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1},
		{0,1,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };

    set_matrix(&matrix[0][0], ml, mc, 15, 15, &planneur[0][0], 3, 3);
    set_matrix(&matrix[0][0], ml, mc, 0, 0, &set[0][0], 9, 36);
    set_matrix(&matrix[0][0], ml, mc, 25, mc - 20, &set2[0][0], 9, 18);

    while (1) {
        print_matrix(&matrix[0][0], ml, mc);

        #ifdef U2
        update_matrix2(&matrix[0][0], &bis[0][0], ml, mc);
        #else
        update_matrix(&matrix[0][0], &bis[0][0], ml, mc);
        #endif

        Sleep(33);
    }

    return 0;
}