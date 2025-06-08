#include <ncurses.h>
#include <stdio.h>

#define Y 25
#define X 80
#define MIN_SPEED 100
#define MAX_SPEED 1000

void input_matrix(int **matrix);

void update_matrix(int **current, int **next);

int count_neighbors(int **current, int i, int j);

int decision(int neighbors, int condition);

void replace(int **next, int **current);

int check(int **current, int **next);

int change_speed(char control_button, int *flag, int time_ms);

int count(int **matrix);

int main() {
    int current[Y][X], next[Y][X];
    int *prtCurrent[Y], *prtNext[Y];

    for (int i = 0; i < Y; ++i) prtCurrent[i] = current[i];
    for (int i = 0; i < Y; ++i) prtNext[i] = next[i];

    int time_ms = 500;
    int stop = 0;
    input_matrix(prtCurrent);
    if (freopen("/dev/tty", "r", stdin)) initscr();
    nodelay(stdscr, true);

    while (stop != 1) {
        char control_button = getch();

        if (count(prtCurrent) == 0) {
            stop = 1;
        }

        time_ms = change_speed(control_button, &stop, time_ms);

        timeout(time_ms);
        clear();
        update_matrix(prtCurrent, prtNext);
        box(stdscr, 0, 0);
        mvprintw(1, X + 2, "CONTROLS:");
        mvprintw(2, X + 2, "z - decrease speed");
        mvprintw(3, X + 2, "a - increase speed");
        mvprintw(4, X + 2, "Space bar- exit");
        noecho();
        curs_set(0);
        refresh();
        if (check(prtCurrent, prtNext) == Y * X) {
            stop = 1;
        }
        replace(prtNext, prtCurrent);
    }
    endwin();
    return 0;
}

void input_matrix(int **matrix) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                matrix[i][j] = 0;
            }
        }
    }
}

void update_matrix(int **current, int **next) {
    for (int i = 0; i < Y; i++) {
        move(i, 0);
        for (int j = 0; j < X; j++) {
            next[i][j] = decision(count_neighbors(current, i, j), current[i][j]);
            if (next[i][j] == 1)
                printw("O");
            else
                printw("-");
        }
        printw("\n");
    }
}

int count_neighbors(int **current, int i, int j) {
    int sum = 0;

    int i_minus = i - 1, j_minus = j - 1, i_plus = i + 1, j_plus = j + 1;

    if (i_minus < 0) i_minus = Y - 1;
    if (j_minus < 0) j_minus = X - 1;
    if (i_plus > Y - 1) i_plus = i_plus % Y;
    if (j_plus > X - 1) j_plus = j_plus % X;

    sum += current[i_minus][j_minus];
    sum += current[i_minus][j];
    sum += current[i_minus][j_plus];
    sum += current[i][j_plus];
    sum += current[i_plus][j_plus];
    sum += current[i_plus][j];
    sum += current[i_plus][j_minus];
    sum += current[i][j_minus];

    return sum;
}

int decision(int neighbors, int condition) {
    int next_gen = -1;
    if ((neighbors == 2 || neighbors == 3) && condition == 1) {
        next_gen = 1;
    } else if (neighbors == 3 && condition == 0) {
        next_gen = 1;
    } else {
        next_gen = 0;
    }
    return next_gen;
}

void replace(int **next, int **current) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            current[i][j] = next[i][j];
        }
    }
}

int check(int **current, int **next) {
    int ans = 0;
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            if (current[i][j] == next[i][j]) ans++;
        }
    }
    return ans;
}

int change_speed(char control_button, int *flag, int time_ms) {
    if (control_button == 'z' || control_button == 'Z') {
        time_ms = (time_ms >= MAX_SPEED) ? MAX_SPEED : time_ms + 100;
    } else if (control_button == 'a' || control_button == 'A') {
        time_ms = (time_ms <= MIN_SPEED) ? MIN_SPEED : time_ms - 100;
    } else if (control_button == ' ') {
        *flag = 1;
    }

    return time_ms;
}

int count(int **matrix) {
    int sum = 0;
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}