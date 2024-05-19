#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

// Define a structure to represent a destination with its characteristics
struct Destination {
    string name;
    int budget;
    bool sunny;
    bool hasCar;
    bool inMountains;
};

// Function to initialize a vector of destinations
vector<Destination> initializeDestinations() {
    return {
        {"Shimla", 5000, true, false, true},
        {"Goa", 8000, true, true, false},
        {"Manali", 6000, true, true, true},
        {"Ooty", 4000, true, false, false},
        {"Munnar", 4500, true, false, true},
        {"Jaipur", 5500, true, false, false},
        {"Rishikesh", 7000, true, false, true},
        {"Pondicherry", 7500, true, false, false},
        // Add more destinations with their characteristics
    };
}

// Function to get user input for budget and destination
void getUserInput(int& maxBudget, string& desiredDestination) {
    cout << "Enter your maximum budget: ";
    cin >> maxBudget;

    cout << "Enter your desired destination (Shimla, Goa, Manali, Ooty, Munnar, Jaipur, Rishikesh, Pondicherry, etc.): ";
    cin >> desiredDestination;
}

string findSuitableDestination(const vector<Destination>& destinations, int maxBudget, const string& desiredDestination, int& suggestedBudget) {
    for (const auto& destination : destinations) {
        if (destination.name == desiredDestination && destination.budget <= maxBudget &&
            (destination.sunny && !destination.inMountains || destination.hasCar)) {
            suggestedBudget = destination.budget;
            return destination.name;
        }
    }

    for (const auto& destination : destinations) {
        if (destination.name != desiredDestination && destination.budget <= maxBudget &&
            (destination.sunny && !destination.inMountains || destination.hasCar)) {
            suggestedBudget = destination.budget;
            return destination.name;
        }
    }

    // If the desired destination is not found, suggest any suitable destination within the budget
    for (const auto& destination : destinations) {
        if (destination.budget <= maxBudget && (destination.sunny && !destination.inMountains || destination.hasCar)) {
            suggestedBudget = destination.budget;
            return destination.name;
        }
    }

    return "No suitable destination found within the given budget and preferences.";
}

// Function to provide a reason for the suggestion
string provideReason(const Destination& suggestedDestination, const Destination& desiredDestination) {
    string reason = "Based on your preferences, ";

    if (suggestedDestination.sunny != desiredDestination.sunny) {
        reason += "the weather in " + suggestedDestination.name + " is more suitable. ";
    }

    if (suggestedDestination.hasCar != desiredDestination.hasCar) {
        reason += "Having a car in " + suggestedDestination.name + " is more convenient. ";
    }
    if (suggestedDestination.inMountains != desiredDestination.inMountains) {
        reason += "If you enjoy mountains, " + suggestedDestination.name + " is a great choice. ";
    }
    return reason;
}

int main() {
    // Seed for random number generation
    srand(time(0));

    cout << "Welcome to the Enhanced Trip Planning AI!" << endl;

    // Initialize destinations
    vector<Destination> destinations = initializeDestinations();

    // Get user input
    int maxBudget;
    string desiredDestination;
    getUserInput(maxBudget, desiredDestination);

    // Find a suitable destination
    int suggestedBudget = 0; // Variable to store the budget of the suggested destination
    string chosenDestination = findSuitableDestination(destinations, maxBudget, desiredDestination, suggestedBudget);

    // Display the chosen destination with a reason
    if (chosenDestination != "No suitable destination found within the given budget and preferences.") {
        Destination suggestedDestination;
        for (const auto& destination : destinations) {
            if (destination.name == chosenDestination) {
                suggestedDestination = destination;
                break;
            }
        }

        cout << "The AI suggests going to " << chosenDestination << ". ";
        cout << provideReason(suggestedDestination, destinations[0]); // Providing reason based on Shimla for simplicity

        // Check if the suggested destination is within or outside the budget
        if (suggestedBudget <= maxBudget) {
            cout<<endl;
            cout << "This destination is within your budget of " << maxBudget << ". ";
        } else {
            cout<<endl;
            cout << "This destination is outside your budget of " << maxBudget << ". ";
        }

        cout << "Enjoy your journey!" << endl;
    } else {
        cout << "Sorry, no suitable destination found within the given budget and preferences." << endl;
    }


    return 0;
}
