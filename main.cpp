#include "alcs.h"
#include <algorithm>
#include <random>


using namespace std;

std::default_random_engine generator;

int RandomInt(int left, int right)
{
    std::uniform_int_distribution<int> distribution(left, right);
    return distribution(generator);
}

bool CompareVectors(std::vector < std::vector <int> > &first, std::vector < std::vector <int> > &second)
{
    if (first.size() != second.size())
        return false;
    for (size_t i = 0; i < first.size(); ++i)
    {
        if (first[i].size() != second[i].size())
            return false;
        for (size_t j = 0; j < first[i].size(); ++j)
            if (first[i][j] != second[i][j])
                return false;
    }
    return true;
}

void WriteVector(std::vector < std::vector <int> > &tmp)
{
    for (size_t i = 0; i < tmp.size(); ++i)
    {
        for (size_t j = 0; j < tmp[i].size(); ++j)
            std::cout << tmp[i][j] << ' ';
        std::cout << std::endl;
    }
}

std::string GenerateString(size_t size)
{
    std::string result = "";
    for (size_t i = 1; i < size; i++)
    {
        char new_char = 'a' + (char)(RandomInt(0, 25));
        result += new_char;
    }
    return result;
}

bool TestingWithCurrentLength(size_t first_length, size_t second_length, unsigned int number_of_tests)
{
    bool ok = true;
    for (unsigned int i = 0; i < number_of_tests; ++i)
    {
        std::string first = GenerateString(first_length);
        std::string second = GenerateString(second_length);

        std::vector < std::vector <int> > result_of_fast_algorithm;
        std::vector < std::vector <int> > result_of_slow_algorithm;

        FastLCS(first, second, result_of_fast_algorithm);
        SlowLCS(first, second, result_of_slow_algorithm);

        if (!CompareVectors(result_of_fast_algorithm, result_of_slow_algorithm))
            ok = false;
    }
    return ok;
}

bool Testing(unsigned int number_of_tests)
{
    bool ok = true;
    for (unsigned int i = 0; i <= number_of_tests; ++i)
    {
        size_t first_length = (size_t)RandomInt(0, i), second_length = (size_t)RandomInt(0, i);
        unsigned int number_of_tests_with_current_length = (unsigned int)RandomInt(10, 30);
        if (!TestingWithCurrentLength(first_length, second_length, number_of_tests_with_current_length))
            ok = false;
    }
    if (ok)
        cout << ":))\n";
    else
        cout << ":((\n";
    return ok;
}

int main()
{
    unsigned int number_of_tests;
    cin >> number_of_tests;
    Testing(number_of_tests);
    system("pause");
    return 0;
}
