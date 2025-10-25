#include <array>
#include <random>
#include <iostream>
#include <string_view>
#include <limits>

constexpr std::array<std::string_view, 3> hands = {"Paper", "Rock", "Scissor"};

enum GAMERESULT {
    WIN,
    LOSE,
    DRAW
};

constexpr int OFFSET = 1;

int robotDecision() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(OFFSET, hands.size());
    const int randomNumber = distrib(gen);

    return randomNumber;
}
void printChoose(const int &offset = 0) {
    for (int i = 0; i < hands.size(); i++) {
        std::cout << (i + offset) << ". " << hands[i] << std::endl;
    }
}

int userDecision(const int &low, const int &high) {
    for (;;) {

        if (int d; std::cin >> d &&
            d >=low && d <= high) return d;

        // Error Handling
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a validate choose between " << low << " and " << high << std::endl;
    }
}

GAMERESULT gameDecision(const int &user, const int &robot) {
    if (user == robot) return DRAW;

    if ((user == 1 && robot == 2)||
        (user == 2 && robot == 3)||
        (user == 3 && robot == 1)) {
        return WIN;
    }

    return LOSE;
}

int main() {
    std::cout << "Welcome to ROCK PAPER SCISSOR" << std::endl;
    printChoose(OFFSET);
    std::cout << "Pick a choose: ";
    const int userChoice = userDecision(OFFSET, hands.size());

    const int robotChoice = robotDecision();

    if (gameDecision(userChoice, robotChoice) == WIN) {
        std::cout << "You win!" << std::endl;
    }else if (gameDecision(userChoice, robotChoice) == DRAW) {
        std::cout << "You draw!" << std::endl;
    }else {
        std::cout << "You lose!" << std::endl;
    }
    std::cout << "Robot: " << hands[robotChoice - 1] << std::endl <<
            "User: " << hands[userChoice - 1] << std::endl;

    return 0;
}