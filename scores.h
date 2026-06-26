#ifndef SCORES_H
#define SCORES_H

#include <fstream>
#include <string>

// Функція для запису рекорду
void saveHighScore(int score) {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << score;
        file.close();
    }
}

// Функція для читання рекорду
int loadHighScore() {
    std::ifstream file("highscore.txt");
    int score = 0;
    if (file.is_open()) {
        file >> score;
        file.close();
    }
    return score;
}

#endif
