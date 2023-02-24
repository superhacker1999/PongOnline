#include "pong.h"

Pong::Pong() {
    initGameField_(fieldSize);
}

void Pong::gameStart() {
    Position player1;
    Position player2;
    while (true) {
        if (doesSomeoneWon_()) {
            break;
        }
        auto new_poss = processKeys_();
        setPlatformToPosition_(player1, player2);
        updateBallPosition_();
        checkGoal_();
        checkCollision_();
        system("clear");
        showScore_();
        m_gameField.OutputMatrix(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(defTimeout));
    }
}

std::pair<Position, Position> Pong::processKeys_() {
    char key = getchar();
    Position player1 = m_player1PlatformPos;
    Position player2 = m_player2PlatformPos;
    if (key == 'A' || key == 'a') {
        player1.y--;
    } else if (key == 'z' || key == 'Z') {
        player1.y++;
    } else if (key == 'k' || key == 'K') {
        player2.y--;
    } else if (key == 'm' || key == 'M') {
        player2.y++;
    }
    return {player1, player2};
}

bool Pong::doesSomeoneWon_() {
    if (m_goalScore.player1 > maxScore) {
        system("clear");
        std::cout << player1WinMessage;
        return true;
    } else if (m_goalScore.player2 > maxScore) {
        system("clear");
        std::cout << player2WinMessage;
        return true;
    }
    return false;
}

void Pong::initGameField_(std::pair<int, int> fieldSize) {
    m_gameField = s21::Matrix<char>(fieldSize.first, fieldSize.second);
    for (int i = 0; i < m_gameField.GetRows(); ++i)
        for (int j = 0; j < m_gameField.GetCols(); ++j)
            if (i == 0 || i == m_gameField.GetRows() - 1)
                m_gameField(i, j) = symHorizontal;
            else if (j == 0 || j == m_gameField.GetCols() - 1)
                m_gameField(i, j) = symVertical;
            else
                m_gameField(i, j) = symEmpty;
    m_ballStartPosition = m_ballPosition = Position(m_gameField.GetRows() / 2,
                              m_gameField.GetCols() / 2);
    
    m_gameField(m_ballPosition.x, m_ballPosition.y) = symBall;
    createPlatforms_();
}

void Pong::createPlatforms_() {
    for (int i = -2; i < 3; ++i) {
        m_gameField(player1DefPlatformPosition.y + i,
            player1DefPlatformPosition.x) = symPlatform;
        m_gameField(player2DefPlatformPosition.y + i,
            player2DefPlatformPosition.x) = symPlatform;
    }
    m_player1PlatformPos = player1DefPlatformPosition;
    m_player2PlatformPos = player2DefPlatformPosition;
}

void Pong::updateBallPosition_() {
    m_gameField(m_ballPosition.x, m_ballPosition.y) = symEmpty;
    if (m_ballDirection == EDirection::leftdown) {
        m_ballPosition.x++;
        m_ballPosition.y--;
    } else if (m_ballDirection == EDirection::leftup) {
        m_ballPosition.x--;
        m_ballPosition.y--;
    } else if (m_ballDirection == EDirection::rightdown) {
        m_ballPosition.x++;
        m_ballPosition.y++;
    } else if (m_ballDirection == EDirection::rightup) {
        m_ballPosition.x--;
        m_ballPosition.y++;
    }
    m_gameField(m_ballPosition.x, m_ballPosition.y) = symBall;
}

void Pong::checkCollision_() {
    if (m_ballPosition.x == 1) {
        if (m_ballDirection == EDirection::leftup) {
            m_ballDirection = EDirection::leftdown;
        } else if (m_ballDirection == EDirection::rightup) {
            m_ballDirection = EDirection::rightdown;
        }
    } else if (m_ballPosition.x == m_gameField.GetRows() - 2) {
        if (m_ballDirection == EDirection::leftdown) {
            m_ballDirection = EDirection::leftup;
        } else if (m_ballDirection == EDirection::rightdown) {
            m_ballDirection = EDirection::rightup;
        }
    } else if (m_ballPosition.y == 4 &&
            m_ballPosition.x >= m_player1PlatformPos.x - 2 &&
            m_ballPosition.x <= m_player1PlatformPos.x + 2) {
        if (m_ballDirection == EDirection::leftdown) {
            m_ballDirection = EDirection::rightdown;
        } else if (m_ballDirection == EDirection::leftup) {
            m_ballDirection = EDirection::rightup;
        }
    } else if (m_ballPosition.y == 95 &&
            m_ballPosition.x >= m_player2PlatformPos.x - 2 &&
            m_ballPosition.x <= m_player2PlatformPos.x + 2) {
        if (m_ballDirection == EDirection::rightdown) {
            m_ballDirection = EDirection::leftdown;
        } else if (m_ballDirection == EDirection::rightup) {
            m_ballDirection = EDirection::leftup;
        }
    }
}

void Pong::setBallToStartPosition_() {
    m_gameField(m_ballPosition.x, m_ballPosition.y) = symEmpty;
    m_ballPosition = m_ballStartPosition;
    m_gameField(m_ballPosition.x, m_ballPosition.y) = symBall;
}

void Pong::setPlatformToPosition_(const Position& pos1, const Position& pos2) {
    for (int i = -2; i < 3; ++i) {
        m_gameField(m_player1PlatformPos.y + i,
            m_player1PlatformPos.x) = symEmpty;
        m_gameField(m_player2PlatformPos.y + i,
            m_player2PlatformPos.x) = symEmpty;
    }
    m_player1PlatformPos = pos1;
    m_player2PlatformPos = pos2;
    for (int i = -2; i < 3; ++i) {
        m_gameField(m_player1PlatformPos.y + i, m_player1PlatformPos.x) = symPlatform;
        m_gameField(m_player2PlatformPos.y + i, m_player2PlatformPos.x) = symPlatform;
    }
}

void Pong::checkGoal_() {
    if (m_ballPosition.y == 1) {
        m_goalScore.player2++;
        setBallToStartPosition_();
        setPlatformToPosition_(player1DefPlatformPosition, player2DefPlatformPosition);
    } else if (m_ballPosition.y == m_gameField.GetCols() - 2) {
        m_goalScore.player1++;
        setBallToStartPosition_();
        setPlatformToPosition_(player1DefPlatformPosition, player2DefPlatformPosition);
    }
}

void Pong::showScore_() {
    std::cout << "Player 1\t" << m_goalScore.player1 << "\t\t\t\t\t";
    std::cout << "Player 2\t" << m_goalScore.player2 << std::endl;
}
