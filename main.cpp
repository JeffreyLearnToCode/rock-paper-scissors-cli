#include <array>
#include <random>
#include <iostream>

constexpr std::array<std::string_view, 3> hands = {"Paper", "Rock", "Scissor"};

std::string_view robotDecision() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, hands.size()-1);
    const int randomNumber = distrib(gen);

    std::cout << randomNumber << std::endl;
    return hands[randomNumber];
}

int main() {
    return 0;
}