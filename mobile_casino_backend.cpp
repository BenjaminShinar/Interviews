#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
/*
a Company that makes mobile games. three tasks in codility;
1. find bug in program that gets the smallest element;
2. find largest possible square to make from two sticks - can we get 4 equal parts size;
3.


*/


int solutionBuggy(std::vector<int>& A) {
    int ans = 0;
    for (int i = 1; i < A.size(); i++) {
        if (ans > A[i]) {
            ans = A[i];
        }
    }
    return ans;
}

int solutionBetter(std::vector<int>& A) {
    int ans = A[0];
    for (int i = 1; i < A.size(); i++) {
        if (ans > A[i]) {
            ans = A[i];
        }
    }
    return ans;
}


void GetSmallest()
{
    // return smallest;
    auto Foo = [](const std::vector<int> & v)
    {
        std::vector<int> v2=v;
        std::cout << std::boolalpha;
        const auto bugged = solutionBuggy(v2);
        const auto better = solutionBetter(v2);
        std::cout << "bugged result is " << bugged << " correct results is " << better;
        std::cout << std::noboolalpha << '\n';
    };

    {
        Foo({-1,1,-2,2});
        Foo({3,3,2,2});
        //Foo();
    }
}


int StickSize(int A, int B)
{
    const auto largeStick = std::max(A,B);
    const auto smallStick = std::min(A,B);

    if  ((2*smallStick)>= largeStick)
    {
        return smallStick/2;
    }
    else if ((4*smallStick)  >= largeStick)
    {
        return std::min(largeStick/3,smallStick);
    }
    else
    {
        return largeStick/4;
    }
}

void GetShorestStick()
{
    // return smallest;
    auto Foo = [](int a, int b, int expected)
    {
        std::cout << std::boolalpha;
        const auto stickSize = StickSize(a,b);
        std::cout << "stick size is " << stickSize << " expected " << expected << " as expected? " << (stickSize == expected);
        std::cout << std::noboolalpha << '\n';
    };

    {
        Foo(10,21,7);
        Foo(13,11,5);
        Foo(2,1,0);
        Foo(1,8,2);
        Foo(0,0,0);
        Foo(8,8,4);
        Foo(8,7,3);
        Foo(18,7,6);
        Foo(18,5,5);
    }
}
int main()
{
    GetSmallest();
    GetShorestStick();
}