#include <array>
#include <random>
#include <iostream>
#include <string_view>
#include <limits>
#include <conio.h>

constexpr std::array<std::string_view, 3> hands = {"Rock", "Paper", "Scissor"};
constexpr std::array<std::string_view, 3> menuChoices = {"Scores", "Play Game", "Exit"};

enum GameResult {
    WIN,
    LOSE,
    DRAW
};

enum Choice {
    ROCK,
    PAPER,
    SCISSOR,
};

enum MainMenu {
    SCORE,
    GAME,
    EXIT
};

enum WaitKey {
    ENTER,
    ESC
};

constexpr int OFFSET = 1;

int robotDecision() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, hands.size()-1);
    const int randomNumber = distrib(gen);

    return randomNumber;
}

void printMainMenuChoose(const int offset = 0) {
    for (int i = 0; i < menuChoices.size(); i++) {
        std::cout << (i+offset) << ". " << menuChoices[i] << std::endl;
    }
}

void printHandChoose(const int offset = 0) {
    for (int i = 0; i < hands.size(); i++) {
        std::cout << (i + offset) << ". " << hands[i] << std::endl;
    }
}

int userDecision(const int low, const int high) {
    for (;;) {

        if (int d; std::cin >> d &&
            d >=low && d <= high) return d;

        // Error Handling
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a validate choose between " << low << " and " << high << ": ";
    }
}

WaitKey waitForExitKeyPress() {
    for (;;) {
        if (int key; _kbhit()) {
            key = _getch();

            if (key == 98) return ESC;
            if (key == '\n' || key == '\r') return ENTER;
        }
    }
}

GameResult gameDecision(const Choice user, const Choice robot) {
    if (user == robot) return DRAW;

    if ((user ==  PAPER && robot == ROCK)||
        (user == ROCK && robot == SCISSOR)||
        (user == SCISSOR && robot == PAPER)) {
        return WIN;
    }

    return LOSE;
}

int main() {
    std::cout << "Welcome to ROCK PAPER SCISSOR" << std::endl;
    int userScore = 0;
    int robotScore = 0;

    while (true) {
        printMainMenuChoose(OFFSET);
        std::cout << "Pick a choose: ";
        const auto mainMenuChoice = static_cast<MainMenu>(userDecision(OFFSET, menuChoices.size()) - OFFSET);

        if (mainMenuChoice == SCORE) {

            while (true) {
                std::cout << "Robot: " << robotScore << std::endl <<
                        "User: " << userScore << std::endl;

                std::cout << "Please click the ENTER to continue or ESC key to go back to the main menu: ";

                if (waitForExitKeyPress() == ENTER) break;
            }

        }else if (mainMenuChoice == GAME){
            do{
                printHandChoose(OFFSET);
                std::cout << "Pick a choose: ";
                const auto userChoice = static_cast<Choice>(userDecision(OFFSET, hands.size()) - OFFSET);

                const auto robotChoice = static_cast<Choice>(robotDecision());

                GameResult gameResult = gameDecision(userChoice, robotChoice);

                if (gameResult == WIN) {
                    userScore++;
                    std::cout << "You win!" << std::endl;
                }else if (gameResult == DRAW) {
                    std::cout << "You draw!" << std::endl;
                }else {
                    robotScore++;
                    std::cout << "You lose!" << std::endl;
                }
                std::cout << "Robot: " << hands[robotChoice] << std::endl <<
                        "User: " << hands[userChoice] << std::endl;

                std::cout << "\n\n" << "Please click the ENTER to continue or ESC key to go back to the main menu: ";

                if (waitForExitKeyPress() == ESC) break;

            }while (true);
        }else if (mainMenuChoice == EXIT) {
            std::cout << "Goodbye!" << std::endl;
            exit(1);
        }
    }

    return 0;
}