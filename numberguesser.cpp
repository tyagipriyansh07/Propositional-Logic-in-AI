#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Logical functions
bool isEven(int number) {
    return number % 2 == 0;
}

bool isPrime(int number) {
    if (number <= 1)
        return false;
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0)
            return false;
    }
    return true;
}

bool isMultipleOfThree(int number) {
    return number % 3 == 0;
}

// AI Decision-Making based on propositional logic
void makeDecision(int secret, int attempts) {
    cout << "Hints:" << endl;

    if ((attempts % 3 == 1) && isEven(secret)) {
        cout << "- The secret number is even." << endl;
    } else if ((attempts % 3 == 1) && !isEven(secret)) {
        cout << "- The secret number is odd." << endl;
    }

    if ((attempts % 3 == 2) && isPrime(secret)) {
        cout << "- The secret number is prime." << endl;
    } else if ((attempts % 3 == 2) && !isPrime(secret)) {
        cout << "- The secret number is composite." << endl;
    }

    if ((attempts % 3 == 0) && isMultipleOfThree(secret)) {
        cout << "- The secret number is a multiple of three." << endl;
    } else if ((attempts % 3 == 0) && !isMultipleOfThree(secret)) {
        cout << "- The secret number is not a multiple of three." << endl;
    }
}

int main() {
    // Seed for random number generation
    srand(time(0));

    // Generate a random number between 1 and 100
    int secretNumber = rand() % 100 + 1;
    int guess;
    int attempts = 0;

    cout << "Welcome to the Number Guessing Game with Planning and Decision-Making!" << endl;

    do {
        cout << "Enter your guess (1-100): ";
        cin >> guess;
        attempts++;

        // AI Decision-Making based on propositional logic
        makeDecision(secretNumber, attempts);

        // Logic to guide the user based on the guess
        if (guess == secretNumber) {
            cout << "Congratulations! You guessed the correct number in " << attempts << " attempts." << endl;
        } else if (guess < secretNumber) {
            cout << "Too low! Try again." << endl;
        } else {
            cout << "Too high! Try again." << endl;
        }
    } while (guess != secretNumber);

    return 0;
}