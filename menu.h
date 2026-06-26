#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include "scores.h"

void showMenu() {
    int bestScore = loadHighScore();
    
    clear();
    // Відображення заголовка та рекорду
    mvprintw(LINES/2 - 2, COLS/2 - 5, "SNAKE GAME");
    
    if (bestScore > 0) {
        mvprintw(LINES/2, COLS/2 - 10, "Best Score: %d", bestScore);
    } else {
        mvprintw(LINES/2, COLS/2 - 10, "No record yet :3");
    }
    
    mvprintw(LINES/2 + 2, COLS/2 - 12, "Press ENTER to Start");
    refresh();

    // Блокуючий ввід (чекаємо ENTER)
    nodelay(stdscr, FALSE);
    int ch;
    while ((ch = getch()) != 10 && ch != KEY_ENTER) {
        // Чекаємо поки натиснуть Enter
    }
    nodelay(stdscr, TRUE); // Повертаємо назад для гри
}

#endif
