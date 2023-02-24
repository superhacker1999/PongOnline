#ifndef SRC_HELPERS_OTHER_OTHER_H_
#define SRC_HELPERS_OTHER_OTHER_H_

#include <math.h>
#include <termios.h>
#include <unistd.h>

class Helper {
    public:
        static double GenerateRandomNumber(double min, double max) {
            double random = (double)rand() / RAND_MAX;
            return min + random * (max - min);
        }

        static int GenerateRandomNumber(int min, int max) {
            int random = rand() / RAND_MAX;
            return min + random * (max - min);
        }

        static int getch() {
            struct termios oldt, newt;
            int ch;
            tcgetattr( STDIN_FILENO, &oldt );
            newt = oldt;
            newt.c_lflag &= ~( ICANON | ECHO );
            tcsetattr( STDIN_FILENO, TCSANOW, &newt );
            ch = getchar();
            tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
            return ch;
        }
};


#endif  // SRC_HELPERS_OTHER_OTHER_H_