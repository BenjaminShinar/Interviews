#include <iostream>
#include <string>

#include "../include/cracking_the_code.h"

void isUnique()
{
    auto combinedUniqueFoo =[](const std::string & str)
    {
    std::cout<<std::boolalpha;
    std::cout<<str << " is unique with set? " << isUniqueWithSet(str) <<'\n';
    std::cout<<str << " is unique without set? " << isUniqueNoExtraDS(str) <<'\n';
    std::cout<<std::noboolalpha;
    };
    combinedUniqueFoo("uniqe!");
    combinedUniqueFoo("not unique!");

}

void isPermutation()
{
    //can we do this in a better way?
    //I don't want to sort the strings 
    auto combinedPermuteFoo =[](const std::string & str1,const std::string & str2)
    {
    std::cout<<std::boolalpha;
    std::cout<<str1 << " is premutation of " << str2<< "? " << isPermurationMap(str1,str2) <<'\n';
    std::cout<<std::noboolalpha;
    };
    combinedPermuteFoo("abb","bab");
    combinedPermuteFoo("abb","baba");
    combinedPermuteFoo("abcb","baba");

}

void UrlifyStrings()
{
    auto urlifyStringFoo =[](char* str,std::size_t n)
    {
    
    std::cout<<std::boolalpha;
    std::cout<< "original form :" <<str;
    Urlify(str,n);
    std::cout<< "modified form : " << str;
    std::cout<<std::noboolalpha <<'\n';
    };
    urlifyStringFoo("Mr John Smith\0\0\0",17);//needs to explicitly specify the size
}
int main()
{
    //isUnique();
    //isPermutation();
    UrlifyStrings();
}