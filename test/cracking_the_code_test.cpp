#include <iostream>
#include <string>
#include <memory>
#include <cstring>
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
    auto urlifyStringFoo =[](const std::string & str)
    {
    auto n = str.length();
    n += (2*countChar(str.c_str(),n,' '));
    auto makeCharArray = [](const std::string s,std::size_t n)
    {
    auto char_array = std::make_unique<char[]>(n);
    memcpy(char_array.get(),s.c_str(),n);
    return char_array;
    };
    auto char_array_from_start = makeCharArray(str,n);
    auto char_array_from_end = makeCharArray(str,n);

    std::cout<< "original form : " <<str <<'\n';
    UrlifyFromStart(char_array_from_start.get(),n);
    std::cout<<"modified form from start : " << char_array_from_start.get() <<'\n';
    //UrlifyFromEnd(char_array_from_end.get(),n);
    //std::cout<<"modified form from end : " << char_array_from_end.get() <<'\n';
    std::cout <<'\n';
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
    auto combinedPermutePalindromeFoo =[](const std::string & str)
    {
    std::cout<<std::boolalpha;
    std::cout<<str << " is premutation of palindrome.";
    std::cout<<" {mapping apperences? : " << isPermutationOfPalindromeMapApperences(str) <<"}";
    std::cout<<" {with set? : " << isPermutationOfPalindromeSet(str) <<"}";
    std::cout<<" {with set early exit? : " << isPermutationOfPalindromeSetEarlyExit(str) <<"}";

    std::cout<<std::noboolalpha << '\n';
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
    auto combinedOneChangeAwayFoo =[](const std::string & str1,const std::string & str2)
    {
    std::cout<<std::boolalpha;
    std::cout<<str1 << " is one change away of " << str2<< "? " << isOneChangeAway(str1,str2) &&  isOneChangeAway(str2,str1);
    std::cout<<std::noboolalpha << '\n';
    };
    combinedOneChangeAwayFoo("pale","ple");
    combinedOneChangeAwayFoo("pale","pales");
    combinedOneChangeAwayFoo("pale","bale");
    combinedOneChangeAwayFoo("pale","bake");
    combinedOneChangeAwayFoo("pxle","baxle");
    combinedOneChangeAwayFoo("pale","palell");
}

void isCompressedDecompressedString()
{
    //can we do this in a better way?
    //I don't want to sort the strings 
    auto combinedcompressDecompressFoo =[](const std::string & str1,const std::string & str2)
    {
    const auto cmprse= compressString(str1);
    std::cout<<std::boolalpha;
    std::cout<<str1 << " compression to " << cmprse << " ok? :" <<(str2==cmprse);
    std::cout<<std::noboolalpha << '\n';
    };
    combinedcompressDecompressFoo("aaaa","a4");
    combinedcompressDecompressFoo("aabcccccaaa","a2b1c5a3");
    combinedcompressDecompressFoo("compressed","compressed");
}
int main()
{
    //isUnique();
    //isPermutation();
    //UrlifyStrings();
    //isPermutationOfPalindrome();
    //isOneEditAway();
    isCompressedDecompressedString();
}