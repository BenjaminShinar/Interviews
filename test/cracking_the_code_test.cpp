#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <iterator>
#include "../include/cracking_the_code.h"

#pragma region Chapter 1 - Arrays and String
namespace arraysAndString
{
    void isUnique()
    {
        auto combinedUniqueFoo = [](const std::string &str)
        {
            std::cout << std::boolalpha;
            std::cout << str << " is unique with set? " << isUniqueWithSet(str) << '\n';
            std::cout << str << " is unique without set? " << isUniqueNoExtraDS(str) << '\n';
            std::cout << std::noboolalpha;
        };
        combinedUniqueFoo("uniqe!");
        combinedUniqueFoo("not unique!");
    }

    void isPermutation()
    {
        //can we do this in a better way?
        //I don't want to sort the strings
        auto combinedPermuteFoo = [](const std::string &str1, const std::string &str2)
        {
            std::cout << std::boolalpha;
            std::cout << str1 << " is premutation of " << str2 << "? " << isPermurationMap(str1, str2) << '\n';
            std::cout << std::noboolalpha;
        };
        combinedPermuteFoo("abb", "bab");
        combinedPermuteFoo("abb", "baba");
        combinedPermuteFoo("abcb", "baba");
    }

    void UrlifyStrings()
    {
        auto urlifyStringFoo = [](const std::string &str)
        {
            auto n = str.length();
            n += (2 * countChar(str.c_str(), n, ' '));
            auto makeCharArray = [](const std::string s, std::size_t n)
            {
                auto char_array = std::make_unique<char[]>(n);
                memcpy(char_array.get(), s.c_str(), n);
                return char_array;
            };
            auto char_array_from_start = makeCharArray(str, n);
            auto char_array_from_end = makeCharArray(str, n);

            std::cout << "original form : " << str << '\n';
            UrlifyFromStart(char_array_from_start.get(), n);
            std::cout << "modified form from start : " << char_array_from_start.get() << '\n';
            //UrlifyFromEnd(char_array_from_end.get(),n);
            //std::cout<<"modified form from end : " << char_array_from_end.get() <<'\n';
            std::cout << '\n';
            char_array_from_start.release();
            char_array_from_end.release();
        };
        urlifyStringFoo("a b");
        urlifyStringFoo("Mr John Smith Goes to");
        urlifyStringFoo("Mr John Smith");
        urlifyStringFoo("john");
        urlifyStringFoo(" Mr ");
        urlifyStringFoo("double  spaces");
        urlifyStringFoo("doNothing");
        urlifyStringFoo(" ");
        urlifyStringFoo("");
    }

    void isPermutationOfPalindrome()
    {
        //can we do this in a better way?
        //I don't want to sort the strings
        auto combinedPermutePalindromeFoo = [](const std::string &str)
        {
            std::cout << std::boolalpha;
            std::cout << str << " is premutation of palindrome.";
            std::cout << " {mapping apperences? : " << isPermutationOfPalindromeMapApperences(str) << "}";
            std::cout << " {with set? : " << isPermutationOfPalindromeSet(str) << "}";
            std::cout << " {with set early exit? : " << isPermutationOfPalindromeSetEarlyExit(str) << "}";

            std::cout << std::noboolalpha << '\n';
        };
        combinedPermutePalindromeFoo("abc");
        combinedPermutePalindromeFoo("ax xa");
        combinedPermutePalindromeFoo("xaxa");
        combinedPermutePalindromeFoo("abcb");
    }

    void isOneEditAway()
    {
        //can we do this in a better way?
        //I don't want to sort the strings
        auto combinedOneChangeAwayFoo = [](const std::string &str1, const std::string &str2)
        {
            std::cout << std::boolalpha;
            std::cout << str1 << " is one change away of " << str2 << "? " << isOneChangeAway(str1, str2) && isOneChangeAway(str2, str1);
            std::cout << std::noboolalpha << '\n';
        };
        combinedOneChangeAwayFoo("pale", "ple");
        combinedOneChangeAwayFoo("pale", "pales");
        combinedOneChangeAwayFoo("pale", "bale");
        combinedOneChangeAwayFoo("pale", "bake");
        combinedOneChangeAwayFoo("pxle", "baxle");
        combinedOneChangeAwayFoo("pale", "palell");
    }

    void isCompressedDecompressedString()
    {
        //can we do this in a better way?
        //I don't want to sort the strings
        auto combinedcompressDecompressFoo = [](const std::string &str1, const std::string &str2)
        {
            const auto cmprse = compressString(str1);
            std::cout << std::boolalpha;
            std::cout << str1 << " compression to " << cmprse << " ok? :" << (str2 == cmprse);
            std::cout << std::noboolalpha << '\n';
        };
        combinedcompressDecompressFoo("aaaa", "a4");
        combinedcompressDecompressFoo("aabcccccaaa", "a2b1c5a3");
        combinedcompressDecompressFoo("compressed", "compressed");
    }

    void isSubstringRotation()
    {

        auto combinedIsSubstringRotationFoo = [](const std::string &str1, const std::string &str2)
        {
            std::cout << std::boolalpha;
            std::cout << str1 << " is a rotation of " << str2 << " ok? :" << isRotationOneSubstring(str1, str2);
            std::cout << std::noboolalpha << '\n';
        };
        combinedIsSubstringRotationFoo("aab", "baa");
        combinedIsSubstringRotationFoo("waterbottle", "erbottlewat");
        combinedIsSubstringRotationFoo("waterbottle", "water");
    }
}
#pragma endregion

#pragma region Chapter 2 - Linked Lists

namespace linkedLists
{
    using sll = std::forward_list<int>;

    std::ostream& operator<< (std::ostream& os, sll const& l) {
    for (int e : l) os << e << ' ';
    return os;
}
    void removeDuplicateslinkedList()
    {
        auto foo = [](const sll &list)
        {
            auto lcopy1{list};
            auto lcopy2{list};
            removeDuplicatesFromListWithSet(lcopy1);
            removeDuplicatesFromListNoExtraDS(lcopy2);
            std::cout << std::boolalpha;
            std::cout << "before: " << isListUnique(list);
            std::cout << " after {with set}: " << isListUnique(lcopy1);
            std::cout << " after {no extra DS}: " << isListUnique(lcopy2);
            std::cout << std::noboolalpha << '\n';
        };
        foo({});
        foo({1});
        foo({1, 1});
        foo({1, 2, 3});
        foo({1, 2, 2, 4});
    }
    void kthtoLast()
    {
        auto foo = [](const sll &list, std::size_t k, int expected)
        {
            auto recursiveK{kToLastElementRecursive(list,k)};
            auto iterativeK{kToLastElementIterative(list,k)};
            std::cout << std::boolalpha;
            std::cout << "element " << k << " is ";
            std::cout << " recursive " << recursiveK;
            std::cout << " as expected? : " << (recursiveK == expected);
            std::cout << " iterative " << iterativeK;
            std::cout << " as expected? : " << (iterativeK == expected);
            std::cout << std::noboolalpha << '\n';
        };

        foo({1, 3, 2, 4}, 1, 4);
        foo({1, 3, 2, 4}, 2, 2);
        foo({1, 3, 2, 4}, 3, 3);
        foo({1,7,7,7,3, 2, 4}, 3, 3);
        foo({1,7,7,7,3, 2, 4}, 4, 7);
    }

    void deleteMiddleNode()
    {
        auto foo = [](const sll &list1,int indexToRemove,const sll &list2)
        {
            sll copy{list1};
            auto node = std::begin(copy);
            std::advance(node,indexToRemove);
            deleteNodeFromMiddleOfList(copy,node);
            std::cout << std::boolalpha;
            std::cout << "lists are equal? " << (copy==list2);
            std::cout << std::noboolalpha << '\n';
        };
           foo({1, 3, 2, 4}, 1, {1, 2, 4});
           foo({1,7,5,6, 3, 2, 4}, 3, {1,7,5, 3, 2, 4});
           
    }
    void partitionAroundValue()
    {
        auto foo = [](const sll &list1,int partitionValue)
        {
            sll copy{list1};
            partitionListAroundValue(copy,partitionValue);
            std::cout << std::boolalpha;
            std::cout << copy;
            std::cout << std::noboolalpha << '\n';
        };
           foo({1, 3,1, 3,1, 3,1, 3,1, 3,1, 3,1, 3,1, 3,4,0}, 2);
           foo({7,7,7,7,1,1,1,3}, 3);
    }
    void sumListsOfDigits()
    {
            auto foo = [](const sll &list1,const sll &list2,const sll &expected)
        {
            auto sum{sumListsValues(list1,list2)};
            std::cout << std::boolalpha;
            std::cout << "sum of " << list1 << " and " << list2 << " is " << sum << " as expected?: "<< (sum==expected);
            std::cout << std::noboolalpha << '\n';
        };
        foo({7,1,6},{5,9,2},{2,1,9});
        foo({8,9,9},{1},{9,9,9});
        foo({9,9},{1,0,0},{0,0,1});

    }
    void isPalindromeLinkedList()
    {
    }
    void isintersectionLL()
    {
    }
    void findLoopStart()
    {
    }
}
#pragma endregion
int main()
{
    {
        using namespace arraysAndString;
        //isUnique();
        //isPermutation();
        //UrlifyStrings();
        //isPermutationOfPalindrome();
        //isOneEditAway();
        //isCompressedDecompressedString();
        //isSubstringRotation();
    }

    {
        using namespace linkedLists;
        //removeDuplicateslinkedList();
        //kthtoLast();
        //deleteMiddleNode();
        //partitionAroundValue();
        sumListsOfDigits();
    }
}