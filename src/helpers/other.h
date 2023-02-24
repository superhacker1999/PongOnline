#ifndef SRC_HELPERS_OTHER_OTHER_H_
#define SRC_HELPERS_OTHER_OTHER_H_

#include <math.h>


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
};


#endif  // SRC_HELPERS_OTHER_OTHER_H_