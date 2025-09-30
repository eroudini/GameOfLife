
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int random, guess; 
    int no_of_guess = 0;

    printf("Welcome to the world of guessing Numbers!\n");
    printf("I have selected a number between 1 and 100. Try to guess it!\n");

    srand((unsigned int)time(NULL));
    random = rand() % 100 + 1;

    do {
        printf("\nPlease enter your guess: ");
        if (scanf("%d", &guess) != 1) {
            printf("Invalid input. Please enter a number.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        no_of_guess++;
        if (guess < random) {
            printf("Try a higher number!\n");
        } else if (guess > random) {
            printf("Try a lower number!\n");
        }
    } while (guess != random);

    printf("\nCongratulations! You have successfully guessed the number %d in %d attempts.\n", random, no_of_guess);

    return 0;
}