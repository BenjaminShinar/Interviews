#include "../include/cracking_the_code.h"
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <cstring>
/**
 * @brief 
 * put each elemnt into the hashSet, check the insertion operator to see if there was already something there
 * @param str 
 * @return true 
 * @return false 
 */
[[nodiscard]] bool isUniqueWithSet(const std::string & str)
{
    std::set<char> charSet;
    for (const auto &c:str)
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
[[nodiscard]] bool isUniqueNoExtraDS(const std::string & str)
{
    auto len{str.length()};
    for (auto i =0; i<len-1;++i)
    {
        if (str.find_first_of(str[i],i+1) != std::string::npos)
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
std::map<char,std::size_t> countAppearances(const std::string & str)
{
    std::map<char,std::size_t> apperances;
    for (const auto & c : str)
    {
        apperances[c] +=1;
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
[[nodiscard]] bool isPermurationMap(const std::string & str1,const std::string & str2)
{
    if (str1.length() != str2.length())
    {
        return false;
    }
    const auto appreances1{countAppearances(str1)};
    const auto appreances2{countAppearances(str2)};
    return appreances1 == appreances2;
}

[[nodiscard]] std::size_t countChar(const char* str,std::size_t n, char c)
{
    std::size_t count{0};
    for (auto i=0;i<n;++i)
    {
        if (str[i]==c)
        {
            ++count;
        }
    }

    return count;
}
/**
 * @brief 
 * turn all spaces into %20, in place. assume space is sufficent
 * @param str 
 */
void Urlify(char* str,std::size_t n)
{
    const auto space{' '};
    auto countSpaces = countChar(str,n,space);
//    auto to{n};

    
}