#include "../include/cracking_the_code.h"
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <cstring>
#include <optional>
#include <iterator>
#include <vector>
#include <stack>
#include <utility>
#include <ctime>
#include <chrono>
#include <thread>
#pragma region Chapter 1 - Arrays and String

/**
 * @brief 
 * put each elemnt into the hashSet, check the insertion operator to see if there was already something there
 * @param str 
 * @return true 
 * @return false 
 */
[[nodiscard]] bool isUniqueWithSet(const std::string &str)
{
    std::set<char> charSet;
    for (const auto &c : str)
    {
        auto insertion = charSet.insert(c);
        if (!insertion.second)
        {
            return false;
        }
    }
    return true;
}
/**
 * @brief 
 * iterate over the string, without changing it, and check if the character appears in any location forward.
 * this probably O(N^2)
 * @param str 
 * @return true 
 * @return false 
 */
[[nodiscard]] bool isUniqueNoExtraDS(const std::string &str)
{
    auto len{str.length()};
    for (auto i = 0; i < len - 1; ++i)
    {
        if (str.find_first_of(str[i], i + 1) != std::string::npos)
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief 
 * count elements in iterable
 * maybe we can template this
 * @param str 
 * @return std::map<char,std::size_t> 
 */
std::map<char, std::size_t> countAppearances(const std::string &str)
{
    std::map<char, std::size_t> apperances;
    for (const auto &c : str)
    {
        apperances[c] += 1;
    }
    return apperances;
}

/**
 * @brief 
 * check lengths for early exit
 * count appearnces for each character, store in a map, then compare maps
 * @param str1 
 * @param str2 
 * @return true 
 * @return false 
 */
[[nodiscard]] bool isPermurationMap(const std::string &str1, const std::string &str2)
{
    if (str1.length() != str2.length())
    {
        return false;
    }
    const auto appreances1{countAppearances(str1)};
    const auto appreances2{countAppearances(str2)};
    return appreances1 == appreances2;
}

/**
 * @brief 
 * utility to count chars in char arary
 * @param str 
 * @param n 
 * @param c 
 * @return std::size_t 
 */
[[nodiscard]] std::size_t countChar(const char *str, std::size_t n, char c)
{
    std::size_t count{0};
    for (auto i = 0; i < n; ++i)
    {
        if (str[i] == c)
        {
            ++count;
        }
    }

    return count;
}

/**
 * @brief utility function
 * put '%20' in location.
 * 
 * @param location 
 */
static void fillUrlSpace(char *location)
{
    *location = '%';
    *(location + 1) = '2';
    *(location + 2) = '0';
}
/**
 * @brief 
 * turn all spaces into %20, in place. assume space is sufficent
 * this is the less efficent form, we have lots of copying
 * @param str 
 */
void UrlifyFromStart(char *str, std::size_t n)
{
    [[maybe_unused]] auto totalCopies{0};
    while (char *first_space = strchr(str, ' '))
    {
        auto n_chars_to_copy = n - (first_space - str);
        memmove(first_space + 3, first_space + 1, n_chars_to_copy);
        fillUrlSpace(first_space);

        totalCopies += n_chars_to_copy;
    }
    totalCopies *= 1;
}

/**
 * @brief 
 * turn all spaces into %20, in place. assume space is sufficent
 * this is the more efficent form, we try to be a little smarter about copying
 * instead of copying the rest of the string each time,we only copy the parts of the string we need to.
 * we copy from the end, and we put each part of the string in the correct place
 * 
 * @param str 
 */
void UrlifyFromEnd(char *str, std::size_t n)
{
    auto calculated_size = n;
    auto totalCopies{0};
    auto iterations{0};
    auto copyLocation{str + n};
    while (!*--copyLocation)
        ;

    auto copyOffset{str + n - copyLocation + 1};
    while (char *last_space = strrchr(str, ' '))
    {
        auto offset = last_space - str;
        auto n_chars_to_copy = calculated_size - offset;

        //calculated_size= calculated_size-offset;

        memmove(last_space + 3 + copyOffset, last_space + 1, n_chars_to_copy - totalCopies);
        *last_space = 'x'; //placholder
        fillUrlSpace(last_space + copyOffset);

        totalCopies += n_chars_to_copy;
    }
    //totalCopies*=1;
}

[[nodiscard]] bool isPermutationOfPalindromeMapApperences(const std::string &str)
{
    const auto appreances{countAppearances(str)};
    auto oddAppereances = std::count_if(std::begin(appreances), std::end(appreances), [](const auto &p)
                                        { return p.second % 2 == 1; });
    return oddAppereances <= 1;
}

[[nodiscard]] bool isPermutationOfPalindromeSet(const std::string &str)
{
    std::set<char> chars;
    for (const auto &c : str)
    {
        auto it = std::find(std::begin(chars), std::end(chars), c);
        if (it != std::end(chars))
        {
            chars.erase(it);
        }
        else
        {
            chars.emplace(c);
        }
    }
    return (chars.size() <= 1);
}

/**
 * @brief 
 * less space usage for non palindromes, but might be higher runtime (depending on how str.length() is implmented)
 * if at any time we decide there is no chance to find a palindrome, we quit
 * @param str 
 * @return true 
 * @return false 
 */
[[nodiscard]] bool isPermutationOfPalindromeSetEarlyExit(const std::string &str)
{
    std::size_t possibilies = str.length();
    std::size_t number_of_uniques{0};
    std::set<char> chars;
    for (const auto &c : str)
    {

        auto it = std::find(std::begin(chars), std::end(chars), c);
        if (it != std::end(chars))
        {
            chars.erase(it);
            --number_of_uniques;
        }
        else
        {
            chars.emplace(c);
            ++number_of_uniques;
        }
        if (number_of_uniques > possibilies--)
        {
            return false;
        }
    }
    return (chars.size() <= 1);
}
/**
 * @brief 
 * early exit if the differnce in length is too high.
 * iterate over the strings,if a char is unmatched, increment the differnces count
 * if the differnces count is more than 1, exit
 * if one of the string is longer than the other, take the shorter string one position back at the first differnec
 * @param str1 
 * @param str2 
 * @return true 
 * @return false 
 */
[[nodiscard]] bool isOneChangeAway(const std::string &str1, const std::string &str2)
{
    auto len1{str1.length()};
    auto len2{str2.length()};

    if ((len1 > len2 + 1) || (len2 > len1 + 1))
    {
        return false;
    }
    auto diffs{0};
    auto i1{0};
    auto i2{0};
    while ((i1 < len1) && (i2 < len2))
    {
        if (str1[i1++] != str2[i2++])
        {
            if (++diffs > 1)
            {
                return false;
            }
            if (len1 > len2)
            {
                --i2;
            }
            else if (len2 > len1)
            {
                --i1;
            }
        }
    }
    return true;
}

std::optional<std::string> CompressStringIfNeeded(const std::string &str)
{
    auto len = str.length();
    auto pos = 0;
    std::string compressed;
    auto nlen{0};
    while (pos < len)
    {
        auto c{str[pos]};
        auto l = str.find_first_not_of(c, pos);
        auto cnt = (l == std::string::npos ? len : l) - pos;
        compressed.append(1, c).append(std::to_string(cnt));
        pos += cnt;
        nlen += cnt + 1;
        if (nlen > len)
            return {};
    }

    return compressed;
}

[[nodiscard]] std::string compressString(const std::string &str)
{
    auto st = CompressStringIfNeeded(str);
    return (st.value_or(str));
}

[[nodiscard]] static bool isRotationOneSubstringImpl(const std::string &str1, const std::string &str2)
{
    std::string expandedString{str1 + str1};
    return (expandedString.find(str2) != std::string::npos);
}

[[nodiscard]] bool isRotationOneSubstring(const std::string &str1, const std::string &str2)
{
    //we can check the lengths and just do one comparision instead
    return ((str1.length() == str2.length()) && isRotationOneSubstringImpl(str1, str2));
}

[[nodiscard]] std::pair<unsigned int, unsigned int> GetNextLocation(const std::size_t N, std::pair<unsigned int, unsigned int> current)
{
    return std::make_pair(current.second, N - current.first - 1);
}
/**
 * @brief 
 * rotate matrix N by N by 90 degrees.
 * we start in the outer rows, and then move to the inner sqaures
 * like rubix cube...
 * @param matrix 
 */
void rotateMatrix90Deg(std::vector<std::vector<int>> &matrix)
{
    const auto N = matrix.size();
    const auto SquareSize = N;
    auto row = 0u;
    while (row < N / 2)
    {
        for (auto col = row; col < N - row - 1; ++col)
        {
            auto startLocation = std::make_pair(row, col);
            auto current = startLocation;
            auto next = GetNextLocation(N, current);
            while (next != startLocation)
            {
                std::swap(matrix.at(startLocation.first)[startLocation.second], matrix.at(next.first)[next.second]);
                current = next;
                next = GetNextLocation(N, current);
            }
        }
        row++;
    }
}

#pragma endregion

#pragma region Chapter 2 - Linked Lists

[[nodiscard]] std::size_t listLength(const std::forward_list<int> &list)
{
    std::size_t len{0};
    auto node = std::begin(list);
    while (node != std::end(list))
    {
        ++len;
        ++node;
    }
    return len;
}

/**
 * @brief 
 * helper function to determine uniqueness
 * @param list 
 * @return true 
 * @return false 
 */
[[nodiscard]] bool isListUnique(const std::forward_list<int> &list)
{
    std::set<int> uniques;
    for (const auto &node : list)
    {
        auto insertion = uniques.insert(node);
        if (!insertion.second)
        {
            return false;
        }
    }
    return true;
}

void removeDuplicatesFromListWithSet(std::forward_list<int> &list)
{
    if (list.empty())
    {
        return;
    }
    auto node{std::begin(list)};
    std::set<int> uniques;
    uniques.insert(*node);

    while (node != std::end(list) && std::next(node) != std::end(list))
    {
        auto insertion = uniques.insert(*std::next(node));
        if (!insertion.second)
        {
            list.erase_after(node);
        }
        std::advance(node, 1);
    }
}

void removeDuplicatesFromListNoExtraDS(std::forward_list<int> &list)
{
    if (list.empty())
    {
        return;
    }
}
[[nodiscard]] std::pair<std::size_t, int> kToLastElementRecursiveImpl(const std::forward_list<int>::const_iterator &it, const std::forward_list<int>::const_iterator &end_it, int kElement)
{
    if (std::next(it) == end_it)
    {
        return {1, *it};
    }

    auto r = kToLastElementRecursiveImpl(std::next(it), end_it, kElement);
    if (r.first == kElement)
    {
        return r;
    }
    else
    {
        return {r.first + 1, *it};
    }
}

[[nodiscard]] int kToLastElementRecursive(const std::forward_list<int> &list, int kElement)
{
    auto pair = kToLastElementRecursiveImpl(std::begin(list), std::end(list), kElement);
    return pair.second;
}

[[nodiscard]] int kToLastElementIterative(const std::forward_list<int> &list, int kElement)
{

    std::vector<int> v(kElement);
    auto node = std::begin(list);
    int elementNum{0};
    while (node != std::end(list))
    {
        v[(elementNum++) % kElement] = *node;
        std::advance(node, 1);
    }
    auto index = (elementNum - kElement) % kElement;
    return v[index];
}
void deleteNodeFromMiddleOfList(std::forward_list<int> &list, std::forward_list<int>::iterator &node)
{
    auto nextNode = node;
    *node = *(++nextNode);
    list.erase_after(node);
}

void partitionListAroundValue(std::forward_list<int> &list, int x)
{
    std::forward_list<int> above;
    std::forward_list<int> below;
    while (!list.empty())
    {
        auto node = std::begin(list);
        int value = *node;
        if (value <= x)
        {
            below.push_front(value);
        }
        else
        {
            above.push_front(value);
        }
        list.pop_front();
    }

    above.splice_after(above.before_begin(), below);
    list = std::move(above);
    //list.splice_after(std::begin(list),below);
}

[[nodiscard]] int sumListValue(const std::forward_list<int> &list)
{
    int sum{0};
    int power{1};
    auto node = std::begin(list);
    while (node != std::end(list))
    {
        sum += (*node) * power;
        power *= 10;
        ++node;
    }
    return sum;
}
[[nodiscard]] std::forward_list<int> sumListsValues(const std::forward_list<int> &list1, const std::forward_list<int> &list2)
{
    int sum1{sumListValue(list1)};
    int sum2{sumListValue(list2)};
    int summed = sum1 + sum2;
    std::forward_list<int> result;
    auto it = result.before_begin();
    while (summed != 0)
    {
        auto value = summed % 10;
        it = result.insert_after(it, value);
        summed = (summed - value) / 10;
    }
    return result;
}

[[nodiscard]] bool isListPalindrome(const std::forward_list<int> &list)
{
    auto len = listLength(list);
    if (len == 0)
    {
        return true;
    }
    auto mid = std::begin(list);
    std::advance(mid, len / 2);
    std::stack<int> stk;
    while (mid != std::end(list))
    {
        stk.push(*mid);
        mid++;
    }
    auto node = std::begin(list);
    while (!stk.empty())
    {
        if (*node != stk.top())
        {
            return false;
        }
        stk.pop();
        ++node;
    }
    return true;
}

[[nodiscard]] std::forward_list<int>::const_iterator areListsIntersecting(const std::forward_list<int> &list1, const std::forward_list<int> &list2)
{

    auto len1 = listLength(list1);
    auto len2 = listLength(list2);
    auto node1 = std::begin(list1);
    auto node2 = std::begin(list2);
    if (len1 > len2)
    {
        std::advance(node1, len1 - len2);
    }
    else if (len2 > len1)
    {
        std::advance(node2, len2 - len1);
    }
    //we just need to check one of them...
    while (node1 != node2 && node1 != std::end(list1))
    {
        ++node1;
        ++node2;
    }
    return node1;
}
[[nodiscard]] std::forward_list<int>::const_iterator isListLooping(const std::forward_list<int> &list);

#pragma endregion

#pragma region Chapter 3 - stacks and queues

int StackWithMin::top() const
{
    return values_stack.top();
}
void StackWithMin::pop()
{
    values_stack.pop();
    min_values_stack.pop();
}
void StackWithMin::push(int v)
{
    values_stack.push(v);
    if (min_values_stack.empty() || v < min())
    {
        min_values_stack.push(v);
    }
    else
    {
        min_values_stack.push(min());
    }
}
int StackWithMin::min() const
{
    return min_values_stack.top();
}
StackWithMin StackWithMin::Create(std::initializer_list<int> values)
{
    StackWithMin s;
    for (auto v : values)
    {
        s.push(v);
    }
    return s;
}

int SelfRegulatingStack::CountStacks() const
{
    return stack_of_stacks.size();
}

int SelfRegulatingStack::top() const
{
    return stack_of_stacks.top().top();
}
void SelfRegulatingStack::pop()
{
    if (stack_of_stacks.empty())
        return;
    if (stack_of_stacks.top().empty())
    {
        stack_of_stacks.pop();
        pop();
    }
    else
    {
        stack_of_stacks.top().pop();
        if (stack_of_stacks.top().empty())
        {
            stack_of_stacks.pop();
        }
    }
}

void SelfRegulatingStack::push(int v)
{
    if (stack_of_stacks.empty() || stack_of_stacks.top().size() >= StackMaxSize)
    {
        stack_of_stacks.push({});
    }
    stack_of_stacks.top().push(v);
}

SelfRegulatingStack SelfRegulatingStack::Create(std::size_t size, std::initializer_list<int> values)
{
    SelfRegulatingStack s;
    s.StackMaxSize = size;
    for (auto v : values)
    {
        s.push(v);
    }
    return s;
}

void sortStackWithAnother(std::stack<int> &unsortedStack)
{
    if (unsortedStack.empty() || unsortedStack.size() == 1)
        return;
    auto max = unsortedStack.top();
    unsortedStack.pop();
    std::stack<int> otherStack;
    while (!unsortedStack.empty())
    {
        auto topElem = unsortedStack.top();
        unsortedStack.pop();
        if (max > topElem)
        {
            std::swap(topElem, max);
        }
        otherStack.push(topElem);
    }
}

std::optional<AnimalSheleter::Animal> AnimalSheleter::DequeDog()
{
    if (dogs.empty())
    {
        return {};
    }
    auto firstDog = dogs.front();
    dogs.pop_front();
    return firstDog.second;
}
std::optional<AnimalSheleter::Animal> AnimalSheleter::DequeCat()
{
    if (cats.empty())
    {
        return {};
    }
    auto firstCat = cats.front();
    cats.pop_front();
    return firstCat.second;
}
std::optional<AnimalSheleter::Animal> AnimalSheleter::DequeAny()
{
    if (dogs.empty())
    {
        //a bit of cheating becuase dequeCat checks itself for emptiess.
        return (DequeCat());
    }

    if (cats.empty())
    {
        return (DequeDog());
    }
    if (cats.front().first < dogs.front().first)
    {
        return (DequeCat());
    }
    else
    {
        return (DequeDog());
    }
}
auto GetLastValid(const std::forward_list<std::pair<unsigned int,AnimalSheleter::Animal>> & pets)
{
    auto slow= pets.before_begin();
    if (slow == std::end(pets))
    {
        return slow;
    }
    auto fast= pets.before_begin();
    ++fast;
    while(fast != std::end(pets))
    {
        ++fast;
        ++slow;
    }
    return slow;
}
void AnimalSheleter::Enque(AnimalSheleter::Animal &&animal)
{
        using namespace std::chrono_literals;

    std::this_thread::sleep_for(1000ms);
    std::time_t result = std::time(nullptr);
    if (animal.type == AnimalSheleter::AnimalType::CAT)
    {
        cats.insert_after(GetLastValid(cats),std::make_pair(result, animal));
    }
    else if (animal.type == AnimalSheleter::AnimalType::DOG)
    {
        dogs.insert_after(GetLastValid(dogs),std::make_pair(result, animal));
        
    }
}

int MyQueue::dequeInt()
{
    return -1;
    // if (!st.Empty())

    // return 0;

    // stacktoUse = !stacktoUse;
}

void MyQueue::enqueueInt(int value)
{
    // if (sT.empty())
    // {
    //     sT.push(value);
    // }
    // else if(sF.empty())
    // {
    //     sF.push(value);
    // }
    // else if (sT.size() > sF.size())
    // {
    //     sT.push(value);
    // }
    // else if (sF.size() > sT.size())
    // {
    //     sF.push(value);
    // }
    // else if(stacktoUse)
    // {
    //     sT.push(value)
    // }
    // else
    // {
    //     sF.push(value);
    // }
}

void MyQueue::MoveFromStackToStack(std::stack<int> & emptyStack,std::stack<int> & fullStack)
{
    while(fullStack.size()>1)
    {
        auto v = fullStack.top();
        emptyStack.push(v);
        fullStack.pop();
    }
}
#pragma endregion





#pragma region Chapter 5 - bitManipulations

unsigned int countSetBits(unsigned int n) 
{ 
  unsigned int count = 0; 
  while (n) 
  { 
    count += n & 1; 
    n >>= 1; 
  } 
  return count; 
} 

int bitsToflip(int a, int b)
{

    return countSetBits(a^b);
}

#pragma endregion