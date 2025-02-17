#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>


#define WIDTH		80
#define HEIGHT		25

#define MAX_COUNTER	21


void print_field(unsigned char ry1, unsigned char ry2, unsigned char bx, unsigned char by);


int
main(void)
{
	unsigned char ry1 = HEIGHT / 2, ry2 = HEIGHT / 2;
	unsigned char bx = WIDTH / 2, by = HEIGHT / 2 + 1;
	unsigned char counter_l = 0, counter_r = 0;
	signed char step_x = time(NULL) & 1 ? 1 : -1;
	signed char step_y = 0;
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	clear();
	print_field(ry1, ry2, bx, by);
	printw(" left - %d\t\t\t\t\t\t\t\trigth - %d\n", counter_l, counter_r);
	while (counter_l < MAX_COUNTER && counter_r < MAX_COUNTER) {
		refresh();
		switch (getch()) {
			case 'A':
			case 'a':
				ry1 -= ry1 > 1 ? 1 : 0;
				break;
			case 'Z':
			case 'z':
				ry1 += ry1 + 2 < HEIGHT ? 1 : 0;
				break;
			case 'K':
			case 'k':
				ry2 -= ry2 > 1 ? 1 : 0;
				break;
			case 'M':
			case 'm':
				ry2 += ry2 + 2 < HEIGHT ? 1 : 0;
				break;
		}
		bx += step_x;
		by += step_y;
		if ((bx == 2 && by >= ry1 && by <= ry1 + 2) || (bx == WIDTH - 1 && by >= ry2 && by <= ry2 + 2)) {
			step_x = -step_x;
			step_y = !step_y ? (time(NULL) & 1 ? 1 : -1) : step_y;
		} else if (!bx) {
			counter_r++;
			bx = 2;
			by = ry1 + 1;
			step_x = 1;
			step_y = 0;
		} else if (bx == WIDTH + 1) {
			counter_l++;
			bx = WIDTH - 1;
			by = ry2 + 1;
			step_x = -1;
			step_y = 0;
		} else if (step_y && (by == 1 || by == HEIGHT)) step_y = -step_y;
		clear();
		print_field(ry1, ry2, bx, by);
		printw(" left - %d\t\t\t\t\t\t\t\trigth - %d\n", counter_l, counter_r);
		usleep(80000);
	}
	clear();
	printw("\t\t\t\tTHE %s PLAYER WINS\n", counter_l > counter_r ? "LEFT" : "RIGHT");
	refresh();
	return 0;
}


void
print_field(unsigned char ry1, unsigned char ry2, unsigned char bx, unsigned char by)
{
	for (unsigned char x, y = 0; y != HEIGHT + 2; y++) {
		for (x = 0; x != WIDTH + 2; x++) {
			if (!x || x == WIDTH + 1) printw("|");
			else if (!y || y == HEIGHT + 1) printw("=");
			else if ((x == 1 && y >= ry1 && y <= ry1 + 2) ||\
					(x == WIDTH && y >= ry2 && y <= ry2 + 2)) printw("#");
			else if (x == bx && y == by) printw("o");
			else if (x == WIDTH / 2) printw("!");
			else printw(" ");
		}
		printw("\n");
	}
}
