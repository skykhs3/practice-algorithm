#include <time.h>
#include <stdio.h>

const int LIMIT = 100000000; // Constants should be in uppercase

// Function to count the number of 1 bits using a loop
int getPopCountLoop(int num) {
    int count = 0;
    while (num) {
        if (num & 1) count++;
        num >>= 1;
    }
    return count;
}

// Function to count the number of 1 bits without using a loop
int getPopCountNotLoop(int num) {
    return (num >> 31 & 1)
         + (num >> 30 & 1)
         + (num >> 29 & 1)
         + (num >> 28 & 1)
         + (num >> 27 & 1)
         + (num >> 26 & 1)
         + (num >> 25 & 1)
         + (num >> 24 & 1)
         + (num >> 23 & 1)
         + (num >> 22 & 1)
         + (num >> 21 & 1)
         + (num >> 20 & 1)
         + (num >> 19 & 1)
         + (num >> 18 & 1)
         + (num >> 17 & 1)
         + (num >> 16 & 1)
         + (num >> 15 & 1)
         + (num >> 14 & 1)
         + (num >> 13 & 1)
         + (num >> 12 & 1)
         + (num >> 11 & 1)
         + (num >> 10 & 1)
         + (num >> 9 & 1)
         + (num >> 8 & 1)
         + (num >> 7 & 1)
         + (num >> 6 & 1)
         + (num >> 5 & 1)
         + (num >> 4 & 1)
         + (num >> 3 & 1)
         + (num >> 2 & 1)
         + (num >> 1 & 1)
         + (num >> 0 & 1);
}

int main() {
    int count1 = 0, count2 = 0, count3 = 0;
    clock_t start, finish;
    double duration;

    // Measure time using loop-based function
    start = clock();
    for (int i = 1; i <= LIMIT; i++) {
        count1 += getPopCountLoop(i);
    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%lf s <- Using Loop\n", duration);

    // Measure time using non-loop function
    start = clock();
    for (int i = 1; i <= LIMIT; i++) {
        count2 += getPopCountNotLoop(i);
    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%lf s <- Not Using Loop\n", duration);

    // Measure time using built-in function
    start = clock();
    for (int i = 1; i <= LIMIT; i++) {
        count3 += __builtin_popcount(i);
    }
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%lf s <- Built-in function\n", duration);

    // Print results
    printf("\n%d %d %d\n", count1, count2, count3);

    return 0;
}
