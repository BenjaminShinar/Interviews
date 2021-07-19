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

    void rotateMatrixTest()
    {
        using v_int = std::vector<std::vector<int>>;
        auto foo = [](v_int &&m, const v_int &e)
        {
            std::cout << std::boolalpha;
            rotateMatrix90Deg(m);
            std::cout << "is matrix rotated properly: " << (e == m);
            std::cout << std::noboolalpha << '\n';
        };
        foo(std::move(v_int{{1}}), {{1}});
        foo(std::move(v_int{{1, 2}, {3, 4}}), {{3, 1}, {4, 2}});
        foo(std::move(v_int{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}), {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}});
        foo(std::move(v_int{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}),
            {{13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11, 7, 3}, {16, 12, 8, 4}});
        foo(std::move(v_int{{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}}),
            {{15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}});

        foo(std::move(v_int{{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}}),
            {{21, 16, 11, 6, 1}, {22, 17, 12, 7, 2}, {23, 18, 13, 8, 3}, {24, 19, 14, 9, 4}, {25, 20, 15, 10, 5}});
    }
}
#pragma endregion

#pragma region Chapter 2 - Linked Lists

namespace linkedLists
{
    using sll = std::forward_list<int>;

    std::ostream &operator<<(std::ostream &os, sll const &l)
    {
        for (int e : l)
            os << e << ' ';
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
            auto recursiveK{kToLastElementRecursive(list, k)};
            auto iterativeK{kToLastElementIterative(list, k)};
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
        foo({1, 7, 7, 7, 3, 2, 4}, 3, 3);
        foo({1, 7, 7, 7, 3, 2, 4}, 4, 7);
    }

    void deleteMiddleNode()
    {
        auto foo = [](const sll &list1, int indexToRemove, const sll &list2)
        {
            sll copy{list1};
            auto node = std::begin(copy);
            std::advance(node, indexToRemove);
            deleteNodeFromMiddleOfList(copy, node);
            std::cout << std::boolalpha;
            std::cout << "lists are equal? " << (copy == list2);
            std::cout << std::noboolalpha << '\n';
        };
        foo({1, 3, 2, 4}, 1, {1, 2, 4});
        foo({1, 7, 5, 6, 3, 2, 4}, 3, {1, 7, 5, 3, 2, 4});
    }
    void partitionAroundValue()
    {
        auto foo = [](const sll &list1, int partitionValue)
        {
            sll copy{list1};
            partitionListAroundValue(copy, partitionValue);
            std::cout << std::boolalpha;
            std::cout << copy;
            std::cout << std::noboolalpha << '\n';
        };
        foo({1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 4, 0}, 2);
        foo({7, 7, 7, 7, 1, 1, 1, 3}, 3);
    }
    void sumListsOfDigits()
    {
        auto foo = [](const sll &list1, const sll &list2, const sll &expected)
        {
            auto sum{sumListsValues(list1, list2)};
            std::cout << std::boolalpha;
            std::cout << "sum of " << list1 << " and " << list2 << " is " << sum << " as expected?: " << (sum == expected);
            std::cout << std::noboolalpha << '\n';
        };
        foo({7, 1, 6}, {5, 9, 2}, {2, 1, 9});
        foo({8, 9, 9}, {1}, {9, 9, 9});
        foo({9, 9}, {1, 0, 0}, {0, 0, 1});
    }
    void isPalindromeLinkedList()
    {
        auto foo = [](const sll &list1)
        {
            std::cout << std::boolalpha;
            std::cout << list1 << " is a palindrome? :" << isListPalindrome(list1);
            std::cout << std::noboolalpha << '\n';
        };
        foo({});
        foo({1});
        foo({3, 3});
        foo({1, 2, 1});
        foo({5, 4, 4, 5});
        foo({1, 2, 3});
        foo({7, 5, 2, 7});
    }
    void isintersectionLL()
    {
    }
    void findLoopStart()
    {
    }
}
#pragma endregion

#pragma region Chapter 3 - Stacks and queues
namespace stacksAndQueues
{

    void TestMinStack()
    {

        auto foo = [](StackWithMin &&stack, int min1, int min2)
        {
            std::cout << std::boolalpha;
            std::cout << "first min " << stack.min() << " is correct: " << (stack.min() == min1) << '\n';
            stack.pop();
            std::cout << "second min " << stack.min() << " is correct: " << (stack.min() == min2);
            std::cout << std::noboolalpha << '\n';
        };
        foo(std::move(StackWithMin::Create({5, 6, 7, 4, 9, 8, 3})), 3, 4);
        foo(std::move(StackWithMin::Create({1, 5, 6, 7, 4, 9, 8, 3})), 1, 1);
    }

    void TestSelfRegulatingStack()
    {
        auto stack = SelfRegulatingStack::Create(2, {1, 2, 3, 4, 5, 6, 7});
        std::cout << std::boolalpha;
        std::cout << " stacks:" << stack.CountStacks() << " top " << stack.top();
        stack.pop();
        stack.pop();
        std::cout << " stacks:" << stack.CountStacks() << " top " << stack.top();
        std::cout << std::noboolalpha << '\n';
    }
    //     1. three stacks in one array?
    // 3. stack of plates: self regulating stacks
    //     - add 'pop at index'
    // 4. queue via stack

    void TestMyQueue()
    {
        MyQueue q;
        q.enqueueInt(1);
        q.enqueueInt(2);
        std::cout << "1 in : " << q.dequeInt() << '\n';
        std::cout << "2 in : " << q.dequeInt() << '\n';
    }
    // 5. sort stack (with other stack)

    void TestAnimalStructure()
    {
        AnimalSheleter aShelter;
        aShelter.Enque({"doggo1", AnimalSheleter::AnimalType::DOG});
        aShelter.Enque({"catto1", AnimalSheleter::AnimalType::CAT});
        aShelter.Enque({"catto2", AnimalSheleter::AnimalType::CAT});
        aShelter.Enque({"doggo2", AnimalSheleter::AnimalType::DOG});
        auto an1 = aShelter.DequeDog();
        std::cout << "1 animal: " << an1.value().name << '\n';
        auto an2 = aShelter.DequeCat();
        std::cout << "2 animal: " << an2.value().name << '\n';
        auto an3 = aShelter.DequeAny();
        std::cout << "3 animal: " << an3.value().name << '\n';
    }
}
#pragma endregion


#pragma region Chapter 5 - Bit Manipulation
namespace bitManip
{
void TestBitsToFlip()
{
    auto foo =[](int n1, int n2, int e)
    {
            std::cout << std::boolalpha;
            auto flipped = bitsToflip(n1,n2);
            std::cout << n1 << " to " << n2 << " required " << flipped << " flips, as expected? " << (e == flipped);
            std::cout << std::noboolalpha << '\n';
    };
    foo(29,15,2);
    foo(28,14,2);
    foo(0b1000,0b1101,2);
    foo(0b1010,0b1001,2);
    foo(0b1010,0b1011,1);
    foo(0b1010,0b1010,0);
}

}
#pragma endregion

#pragma region Chapter 6 - Math and Logic puzzles
namespace mathAndLogic
{
    void TestFindHeavyBottle()
    {
        auto foo =[](int K)
        {
            int matched = HeavyBottle20(K);
            std::cout << std::boolalpha;
            //auto flipped = bitsToflip(n1,n2);
            std::cout << "when " << K <<" bottle is heavier, we matched " << matched << " as expeted? " << (matched == K);
            std::cout << std::noboolalpha << '\n';
        };
        for (int i =1 ; i <= 20; ++i)
        {
            foo(i);
        }
    }

    void TestBetterOneThrow()
    {
        auto foo =[](double prob)
        {
            auto better  = BetterOneThrow(prob) ? "one Throw" : "three throws";
            std::cout << std::boolalpha;
            //auto flipped = bitsToflip(n1,n2);
            std::cout << "when probabilty is " << prob << " the higher chance is to take " << better;
            std::cout << std::noboolalpha << '\n';
        };
        for (auto p =0.45 ; p < 0.55; p+=0.01)
        {
            foo(p);
        }
    }

    void TestFlippedLockers()
    {
        auto lockers =flipLockers();
        for (auto i =0; i<100;++i)
        {
            if (lockers.test(i))
            {
                std::cout << "locker at index " << (i+1) << " is open" <<'\n';
            }
        }

    }
    void TestAll()
    {
        //TestFindHeavyBottle();
        //TestBetterOneThrow();
        TestFlippedLockers();
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
        //rotateMatrixTest();
    }

    {
        using namespace linkedLists;
        //removeDuplicateslinkedList();
        //kthtoLast();
        //deleteMiddleNode();
        //partitionAroundValue();
        //sumListsOfDigits();
        //isPalindromeLinkedList();
    }

    {
        using namespace stacksAndQueues;
        //TestMinStack();
        //TestSelfRegulatingStack();
        //TestAnimalStructure();
        //TestMyQueue();
    }

{
    using namespace bitManip;
    //TestBitsToFlip();

}

    mathAndLogic::TestAll();
    

    // std::vector<std::vector<int>> a{{1,2},{3,4}};
    // std::vector<std::vector<int>> b{{1,2},{3,4}};
    // std::vector<std::vector<int>> c{{1,1},{3,4}};
    // std::cout << "a ==b ? :" << (a==b) <<'\n';
    // std::cout << "a ==c ? :" << (a==c) <<'\n';
}