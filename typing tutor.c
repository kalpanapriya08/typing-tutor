#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 20

// Function to generate a random word for typing practice
void generateRandomWord(char *word) {
    const char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    int length = rand() % (MAX_WORD_LENGTH - 3) + 3; // Random length between 3 and MAX_WORD_LENGTH
    for (int i = 0; i < length; ++i) {
        word[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    word[length] = '\0'; // Null-terminate the string
}

double getCurrentTime() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec / 1e9;
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    printf("Welcome to the Typing Tutor!\n");
    printf("Type the word and press Enter.\n");

    int correctWords = 0;
    int totalWords = 0;

    while (1) {
        char wordToType[MAX_WORD_LENGTH];
        generateRandomWord(wordToType);
        printf("Word: %s\n", wordToType);

        // Measure typing speed
        double startTime = getCurrentTime();

        // Get user input
        char userInput[MAX_WORD_LENGTH];
        scanf("%s", userInput);

        double endTime = getCurrentTime();

        // Calculate time taken
        double typingTime = endTime - startTime;

        // Check if the typed word is correct
        int len = strlen(wordToType);
        int accuracy = 0;

        for (int i = 0; i < len; ++i) {
            if (i < strlen(userInput) && wordToType[i] == userInput[i]) {
                accuracy++;
            }
        }

        double accuracyPercentage = (double)accuracy / len * 100;

        if (accuracyPercentage == 100.0) {
            printf("Correct! Accuracy: %.2f%%, Time: %.6f seconds\n", accuracyPercentage, typingTime);
            correctWords++;
        } else {
            printf("Incorrect. Try again. Accuracy: %.2f%%, Time: %.6f seconds\n", accuracyPercentage, typingTime);
        }

        totalWords++;

        // Ask if the user wants to continue
        printf("Do you want to continue? (y/n): ");
        char continueOption;
        scanf(" %c", &continueOption);

        if (continueOption != 'y' && continueOption != 'Y') {
            break;
        }
    }

    // Display overall performance
    printf("\nTyping tutor summary:\n");
    printf("Correct words: %d\n", correctWords);
    printf("Total words: %d\n", totalWords);
    printf("Accuracy: %.2f%%\n", (double)correctWords / totalWords * 100);

    return 0;
}
