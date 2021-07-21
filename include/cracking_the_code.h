#include <string>
#include <forward_list>
#include <vector>
#include <stack>
#include <optional>
#include <bitset>
#include <set>

[[nodiscard]] bool isUniqueWithSet(const std::string & str);
[[nodiscard]] bool isUniqueNoExtraDS(const std::string & str);

[[nodiscard]] bool isPermurationMap(const std::string & str1,const std::string & str2);

[[nodiscard]] std::size_t countChar(const char* str,std::size_t n, char c);
void UrlifyFromStart(char* str,std::size_t n);
void UrlifyFromEnd(char* str,std::size_t n);

[[nodiscard]] bool isPermutationOfPalindromeMapApperences(const std::string & str);
[[nodiscard]] bool isPermutationOfPalindromeSet(const std::string & str);
[[nodiscard]] bool isPermutationOfPalindromeSetEarlyExit(const std::string & str);

[[nodiscard]] bool isOneChangeAway(const std::string & str1,const std::string & str2);


[[nodiscard]] std::string compressString(const std::string &str);

[[nodiscard]] bool isRotationOneSubstring(const std::string & str1,const std::string & str2);

void rotateMatrix90Deg(std::vector<std::vector<int>> & matrix);

[[nodiscard]] bool isListUnique(const std::forward_list<int> & list);
void removeDuplicatesFromListWithSet(std::forward_list<int> & list);
void removeDuplicatesFromListNoExtraDS(std::forward_list<int> &list);
[[nodiscard]] int kToLastElementRecursive(const std::forward_list<int> & list, int kElement);
[[nodiscard]] int kToLastElementIterative(const std::forward_list<int> & list, int kElement);
void deleteNodeFromMiddleOfList(std::forward_list<int> & list,std::forward_list<int>::iterator & node);
void partitionListAroundValue(std::forward_list<int> & list,int x);
[[nodiscard]] std::forward_list<int> sumListsValues(const std::forward_list<int> & list1,const std::forward_list<int> & list2);
[[nodiscard]] bool isListPalindrome(const std::forward_list<int> & list);
[[nodiscard]] std::forward_list<int>::const_iterator areListsIntersecting(const std::forward_list<int> & list1,const std::forward_list<int> & list2);
[[nodiscard]] std::forward_list<int>::const_iterator isListLooping(const std::forward_list<int> & list);

void sortStackWithAnother(std::stack<int> &unsortedStack);

class StackWithMin
{
    public:
    int top() const;
    void pop();
    void push(int v);
    int min() const;
    static StackWithMin Create(std::initializer_list<int> values);
    private:
    std::stack<int> values_stack;
    std::stack<int> min_values_stack;
};
class SelfRegulatingStack
{
    public:
    int CountStacks() const;
    int top() const;
    void pop();
    void push(int v);
    static SelfRegulatingStack Create(std::size_t stackMaxSize,std::initializer_list<int> values);
    private:
    std::size_t StackMaxSize{5};
    std::stack<std::stack<int>> stack_of_stacks;
};



class MyQueue
{
public:
int dequeInt();
void enqueueInt(int value);
private:
std::stack<int> sT;
std::stack<int> sF;
bool stacktoUse;
void MoveFromStackToStack(std::stack<int> & emptyStack,std::stack<int> & fullStack);

};

class AnimalSheleter
{
public:
enum class AnimalType
{
    CAT,
    DOG
};
struct Animal{
    std::string name;
    AnimalType type;
};

std::optional<Animal> DequeDog();
std::optional<Animal> DequeCat();
std::optional<Animal> DequeAny();
void Enque(Animal && animal);
private:
std::forward_list<std::pair<unsigned int,Animal>> dogs;
std::forward_list<std::pair<unsigned int,Animal>> cats;

};

int bitsToflip(int a, int b);



int HeavyBottle20(int k);
bool BetterOneThrow(double prob);
std::bitset<128> flipLockers();

[[nodiscard]] std::size_t trippleStepsRec(std::size_t floors);
[[nodiscard]] std::size_t trippleSteps(std::size_t floors);

void printPowerSet(std::set<int> & s);