#include "game_src/pong.h"

int main() {
    Pong pong;
    std::thread processKeysThread(&Pong::processKeys, &pong);
    pong.gameStart();
    processKeysThread.detach();
}
