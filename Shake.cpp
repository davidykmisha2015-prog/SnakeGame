#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "menu.h"

struct Point { int x, y; };

int main() {
    srand(time(0));
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    int score = 0;
    int speed = 100000; // Початкова швидкість
    std::vector<Point> snake = {{10, 10}, {9, 10}, {8, 10}};
    Point food = {15, 10};
    int dir_x = 1, dir_y = 0;

    // Ініціалізація перед циклом
    bool is_super = false;
    food = {15, 10};

    showMenu();

    while (true) {
        int ch = getch();
        if (ch == KEY_LEFT && dir_x != 1) { dir_x = -1; dir_y = 0; }
        else if (ch == KEY_RIGHT && dir_x != -1) { dir_x = 1; dir_y = 0; }
        else if (ch == KEY_UP && dir_y != 1) { dir_x = 0; dir_y = -1; }
        else if (ch == KEY_DOWN && dir_y != -1) { dir_x = 0; dir_y = 1; }
        else if (ch == 27) break; // ESC

        Point new_head = {snake[0].x + dir_x, snake[0].y + dir_y};

        // Перевірка зіткнення зі стінами
        if (new_head.x < 0 || new_head.x >= COLS || new_head.y < 0 || new_head.y >= LINES) break;

        snake.insert(snake.begin(), new_head);

        // Логіка їжі та пришвидшення
        if (new_head.x == food.x && new_head.y == food.y) {
            score += (is_super ? 50 : 10);
            if (speed > 30000) speed -= (is_super ? 15000 : 5000);
            
            // Нова їжа
            food = {rand() % COLS, rand() % LINES};
            is_super = (rand() % 5 == 0); // 20% шанс на супер-їжу
        } else {
            snake.pop_back();
        }

        // Малювання
        clear();
        mvprintw(0, 0, "Score: %d", score);
        mvaddch(food.y, food.x, is_super ? '@' : '*');
        for (auto p : snake) mvaddch(p.y, p.x, '#');
        
        refresh();
        usleep(speed);
    }
    int bestScore = loadHighScore();
if (score > bestScore) {
    saveHighScore(score);
    mvprintw(LINES/2, COLS/2 - 10, "NEW RECORD: %d!", score);
} else {
    mvprintw(LINES/2, COLS/2 - 10, "Score: %d (Best: %d)", score, bestScore);
}
refresh();
getch(); // Чекаємо на натискання перед виходом
endwin();

    endwin();
    return 0;
}
