#include <array>
#include <random>
#include <iostream>
#include <string_view>
#include <limits>

constexpr std::array<std::string_view, 3> hands = {"Rock", "Paper", "Scissor"};

enum GAMERESULT {
    WIN,
    LOSE,
    DRAW
};

enum CHOICE {
    ROCK,
    PAPER,
    SCISSOR,
};

constexpr int OFFSET = 1;

int robotDecision() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, hands.size()-1);
    const int randomNumber = distrib(gen);

    return randomNumber;
}
void printChoose(const int offset = 0) {
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

GAMERESULT gameDecision(const CHOICE user, const CHOICE robot) {
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
    printChoose(OFFSET);
    std::cout << "Pick a choose: ";
    const auto userChoice = static_cast<CHOICE>(userDecision(OFFSET, hands.size()) - OFFSET);

    const auto robotChoice = static_cast<CHOICE>(robotDecision());

    GAMERESULT gameResult = gameDecision(userChoice, robotChoice);

    if (gameResult == WIN) {
        std::cout << "You win!" << std::endl;
    }else if (gameResult == DRAW) {
        std::cout << "You draw!" << std::endl;
    }else {
        std::cout << "You lose!" << std::endl;
    }
    std::cout << "Robot: " << hands[robotChoice] << std::endl <<
            "User: " << hands[userChoice] << std::endl;

    return 0;
}