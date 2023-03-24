#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>

/// @brief uniform distributed random even number generator
class EvenRandom
{
public:
    /// @brief seed 설정
    EvenRandom();

    /// @brief 랜덤 짝수 리턴
    /// @return random even number
    int next();

    /// @brief low와 high 사이의 랜덤 짝수 리턴
    /// @param low minimum value
    /// @param high maximum value
    /// @return [low, high] 사이의 랜덤 짝수
    int nextInRange(const int low, const int high);

private:
    std::random_device random_device;
    std::mt19937 mt_engine;
    std::uniform_int_distribution<int> uniform_distributor;
};

EvenRandom::EvenRandom()
    : mt_engine(random_device())
{
    // 최대 분포를 RAND_MAX의 절반으로 설정 (결과값에 * 2를 하기 위함)
    uniform_distributor.param(std::uniform_int_distribution<int>::param_type(0, RAND_MAX / 2));
}

int EvenRandom::next()
{
    return uniform_distributor(mt_engine) * 2;
}

int EvenRandom::nextInRange(const int low, const int high) 
{
    std::uniform_int_distribution<int> ranged_distributor(low / 2, high / 2);
    return ranged_distributor(mt_engine) * 2;
}

int main()
{
    EvenRandom r;
    std::cout << "-- 0에서 " << RAND_MAX << "까지의 랜덤 짝수 정수 10 개--" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        int n = r.next(); // 0에서 RAND_MAX(32767) 사이의 랜덤한 정수 cout << n << ' ';
        std::cout << n << ' ';
    }
    std::cout << std::endl
              << std::endl
              << "-- 2에서 "
              << "10 까지의 랜덤 짝수 정수 10 개 --" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        int n = r.nextInRange(2, 10); // 2에서 10 사이의 랜덤한 정수 cout << n << ' ';
        std::cout << n << ' ';
    }
    std::cout << std::endl;
}