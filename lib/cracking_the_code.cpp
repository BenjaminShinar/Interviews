#include "../include/cracking_the_code.h"
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <cstring>
#include <optional>
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