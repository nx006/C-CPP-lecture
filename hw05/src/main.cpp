#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>

class Player
{
public:
    explicit Player(std::string name = "") : name{name} {}
    void setName(const std::string name) { this->name = name; }
    const std::string &getName() const { return name; }
    void getEnterKey() const
    { // <Enter> 키가 입력되면 리턴
        char buf[100];
        std::cin.getline(buf, 99); // wait <Enter> key
    }

private:
    std::string name;
};

class GamblingGame
{ // 갬블링 게임 전체를 다루는 클래스
private:
    Player p[2];           // 2 명의 선수
    int num[3];            // 랜덤하게 생성된 3 개의 수를 저장하는 배열
    bool matchAll() const; // num[] 배열의 수가 모두 일치하면 true 리턴
public:
    GamblingGame(); // num[i] = 0 setting 및 랜덤 seed 값 생성
    void run();     //
};

GamblingGame::GamblingGame()
{
    // seed the random
    srand(static_cast<unsigned int>(time(nullptr)));

    for (auto &number : num)
    {
        number = rand() % 2;
    }

    constexpr auto playerCount = 2;
    std::array<std::string, playerCount> playerNames;

    std::cout << "***** 갬블링 게임을 시작합니다. *****" << std::endl;
    std::cout << "첫번째 선수 이름>>";
    std::cin >> playerNames[0];
    std::cout << "두번째 선수 이름>>";
    std::cin >> playerNames[1];

    std::cin.ignore();

    for (std::size_t index = 0; index < playerCount; index++)
    {
        p[index].setName(playerNames[index]);
    }
}

void GamblingGame::run()
{
    constexpr auto playerCount = 2;

    auto gameTurnCount = 0;
    while (true)
    {
        const auto index = gameTurnCount++ % playerCount;
        const auto &currentPlayer = p[index];
        std::cout << currentPlayer.getName() << ':';
        currentPlayer.getEnterKey();

        std::cout << '\t';
        // winning
        if (matchAll())
        {
            std::cout << currentPlayer.getName() << "님 승리!!" << std::endl;
            break;
        }
        else
        { // losing
            std::cout << "아쉽군요!" << std::endl;
        }
    }
}
bool GamblingGame::matchAll() const
{
    auto result = true;
    constexpr auto diceSize = 3;
    std::array<int, diceSize> dices;
    for (auto i = 0; i < diceSize; i++)
    {
        dices[i] = rand() % 2;
        if (dices[i] != num[i])
        {
            result = false;
        }
    }

    for (const auto &dice : dices)
    {
        std::cout << dice << '\t';
    }

    return result;
}

int main()
{
    GamblingGame game;
    game.run();

    return 0;
}
