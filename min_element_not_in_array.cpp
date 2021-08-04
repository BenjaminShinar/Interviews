#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <vector>
#include <list>

int MinElement(const std::vector<int> &vec)
{
    std::list<std::pair<int, int>> ranges{{0, 0}};
    for (auto element : vec)
    {
        std::cout << " checking element " << element <<'\n';
        if (element > 0)
        {
            for (auto it = std::begin(ranges); it != std::end(ranges); it = std::next(it))
            {

                if (element < it->first)
                {
                    if ((element) == it->first-1)
                    {
                        std::cout << " updating pair start for element " << element <<'\n';

                        it->first = element;
                    }
                    else
                    {
                        std::cout << " insert pair Before start for element " << element <<'\n';
                        ranges.insert(it, {element, element});
                    }
                    break;
                }

                if (element > it->first && element < it->second)
                {
                    //nothing to do here
                    break;
                }
                auto nextPair = std::next(it);

                if ((element+1) == it->second)
                {
                    
                    if (nextPair != std::end(ranges) && element == nextPair->first)
                    {
                        std::cout << " adding new pair for element " << element <<'\n';
                        it->second = nextPair->second;
                        ranges.erase(nextPair);

                    }
                    else
                    {
                        it->second = element;
                    }
                    break;
                }
                if (nextPair == std::end(ranges) || element <= nextPair->first)
                {
                    std::cout << " adding new last pair for element " << element <<'\n';

                    ranges.insert(nextPair, {element, element});
                    break;
                }
            }
        }
    }

    return ranges.front().second + 1;
}
void TestArrays()
{
    auto TestVector = [](const std::vector<int> &vec, std::size_t expected)
    {
        std::cout << std::boolalpha;
        auto firstNonPresentElement = MinElement(vec);
        std::cout << "first positive element missing is " << firstNonPresentElement << ". as expected? " << (firstNonPresentElement == expected);
        std::cout << std::noboolalpha << '\n';
    };
    //in the real world we would have something to generate the test cases.
    // "{[0A][BC]}-{[DE][FG]}-{[HJ][K0]}"

    {
        //no passengers
        //TestVector({-1, -4}, 1);
        //TestVector({1, 2}, 3);
        TestVector({2, 1}, 3);
    }
}
int main()
{
    TestArrays();
}