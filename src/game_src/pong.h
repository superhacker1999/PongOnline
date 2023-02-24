#ifndef SRC_PONG_PONG_H_
#define SRC_PONG_PONG_H_

#include "../helpers/matrix.h"
#include "../helpers/other.h"

#include <memory>
#include <utility>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <mutex>


enum EDirection : int {
    leftup,
    leftdown,
    rightup,
    rightdown
};

struct GoalScore {
    GoalScore() : player1(0), player2(0) {;}
    int player1;
    int player2;
};

struct Position {
    Position() {}
    Position(int x_, int y_) : x(x_), y(y_) {;}
    Position(const Position& other) : x(other.x), y(other.y) {;}
    bool operator==(const Position& other) { return x == other.x && y == other.y; }
    int x;
    int y;
};


static constexpr char symHorizontal = '-';
static constexpr char symVertical = '|';
static constexpr char symEmpty = ' ';
static constexpr char symBall = '@';
static constexpr char symPlatform = '*';

static constexpr int defTimeout = 100;
static constexpr int maxScore = 10;
static constexpr std::pair<int, int> fieldSize(20, 100);
static const Position player1DefPlatformPosition = Position(2, 10);
static const Position player2DefPlatformPosition = Position(97, 10);


static const std::string player1WinMessage =
"\t\t\t╔═══╦╗─╔══╦╗╔╦═══╦═══╗\n\
\t\t\t║╔═╗║║─║╔╗║║║║╔══╣╔═╗║\n\
\t\t\t║╚═╝║║─║╚╝║╚╝║╚══╣╚═╝║\n\
\t\t\t║╔══╣║─║╔╗╠═╗║╔══╣╔╗╔╝\n\
\t\t\t║║──║╚═╣║║║╔╝║╚══╣║║║\n\
\t\t\t╚╝──╚══╩╝╚╝╚═╩═══╩╝╚╝\n\
\t\t\t─╔╗──╔╗╔╗╔╦══╦╗─╔╦══╗\n\
\t\t\t╔╝║──║║║║║╠╗╔╣╚═╝║╔═╝\n\
\t\t\t╚╗║──║║║║║║║║║╔╗─║╚═╗\n\
\t\t\t─║║──║║║║║║║║║║╚╗╠═╗║\n\
\t\t\t─║║──║╚╝╚╝╠╝╚╣║─║╠═╝║\n\
\t\t\t─╚╝──╚═╝╚═╩══╩╝─╚╩══╝\n";

static const std::string player2WinMessage = 
"\t\t\t╔═══╦╗─╔══╦╗╔╦═══╦═══╗\n\
\t\t\t║╔═╗║║─║╔╗║║║║╔══╣╔═╗║\n\
\t\t\t║╚═╝║║─║╚╝║╚╝║╚══╣╚═╝║\n\
\t\t\t║╔══╣║─║╔╗╠═╗║╔══╣╔╗╔╝\n\
\t\t\t║║──║╚═╣║║║╔╝║╚══╣║║║\n\
\t\t\t╚╝──╚══╩╝╚╝╚═╩═══╩╝╚╝\n\
\t\t\t╔══╗──╔╗╔╗╔╦══╦╗─╔╦══╗\n\
\t\t\t╚═╗║──║║║║║╠╗╔╣╚═╝║╔═╝\n\
\t\t\t╔═╝║──║║║║║║║║║╔╗─║╚═╗\n\
\t\t\t║╔═╝──║║║║║║║║║║╚╗╠═╗║\n\
\t\t\t║╚═╗──║╚╝╚╝╠╝╚╣║─║╠═╝║\n\
\t\t\t╚══╝──╚═╝╚═╩══╩╝─╚╩══╝\n";



class Pong {
    public:
        Pong();
        ~Pong() = default;

        void gameStart();
        void processKeys();

    private:
        void initGameField_(std::pair<int, int> fieldSize);
        void updateBallPosition_();
        void createPlatforms_();
        void checkCollision_();
        void checkGoal_();
        void setBallToStartPosition_();
        void showScore_();
        void updatePlatformPosition_();
        void setPlatformToPosition_(const Position& pos1, const Position& pos2);
        bool doesSomeoneWon_();
        void movePlatformSafe_(Position& pos, char direction);


    private:
        s21::Matrix<char> m_gameField;
        GoalScore m_goalScore;
        int m_ballDirection = leftdown;
        Position m_ballPosition;
        Position m_ballStartPosition;
        // defines the x and y of center of platform
        Position m_player1PlatformPos;
        Position m_player2PlatformPos;
        std::mutex m_mutex;

};

#endif  // SRC_PONG_PONG_H_