#include <stdio.h>
#include <math.h>

void print_menu();
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
int modulus(int a, int b);
double power(double a, double b);
double square_root(double a);
double logarithm(double a);

int main() {

    int choice;
    double first, second, result;

    do {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        if (choice == 7) {
            printf("Merci d'avoir utilisé la calculatrice !\n");
            break;
        }

        if (choice >= 1 && choice <= 6) {
            printf("\nVeuillez entrer le premier nombre : ");
            scanf("%lf", &first);
            printf("\nVeuillez entrer le second nombre : ");
            scanf("%lf", &second);
        } else if (choice == 8 || choice == 9) {
            printf("\nVeuillez entrer le nombre : ");
            scanf("%lf", &first);
        }

        switch (choice) {
            case 1:
                result = add(first, second);
                printf("\nRésultat : %.2f\n", result);
                break;
            case 2:
                result = subtract(first, second);
                printf("\nRésultat : %.2f\n", result);
                break;
            case 3:
                result = multiply(first, second);
                printf("\nRésultat : %.2f\n", result);
                break;
            case 4:
                if (second == 0) {
                    printf("\nErreur : division par zéro !\n");
                } else {
                    result = divide(first, second);
                    printf("\nRésultat : %.2f\n", result);
                }
                break;
            case 5:
                if ((int)second == 0) {
                    printf("\nErreur : division par zéro !\n");
                } else {
                    printf("\nRésultat : %d\n", modulus((int)first, (int)second));
                }
                break;
            case 6:
                result = power(first, second);
                printf("\nRésultat : %.2f\n", result);
                break;
            case 8:
                if (first < 0) {
                    printf("\nErreur : racine carrée d'un nombre négatif !\n");
                } else {
                    result = square_root(first);
                    printf("\nRésultat : %.2f\n", result);
                }
                break;
            case 9:
                if (first <= 0) {
                    printf("\nErreur : logarithme d'un nombre négatif ou nul !\n");
                } else {
                    result = logarithm(first);
                    printf("\nRésultat : %.2f\n", result);
                }
                break;
            default:
                printf("\nChoix invalide, veuillez réessayer.\n");
                break;
        }
    } while (1);

    return 0;
}

void print_menu() {
    printf("\n=== Calculatrice simple ===\n");
    printf("1. Addition\n");
    printf("2. Soustraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulo\n");
    printf("6. Puissance\n");
    printf("7. Quitter\n");
    printf("8. Racine carrée\n");
    printf("9. Logarithme (base e)\n");
    printf("Veuillez entrer votre choix : ");
}

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) { return a / b; }
int modulus(int a, int b) { return a % b; }
double power(double a, double b) { return pow(a, b); }
double square_root(double a) { return sqrt(a); }
double logarithm(double a) { return log(a); }