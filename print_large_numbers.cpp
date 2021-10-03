#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>


//print 1 to 10^10E20
namespace bigNumbers
{

constexpr static std::size_t MAX_DIG = 100;
constexpr static std::size_t WIDTH = 2;

template<std::size_t N>
struct BigNumbersPrinter
{   

    BigNumbersPrinter<N-1> inner;
    
    void print(const std::string & str)
    {   
        for (auto cnt =0; cnt <MAX_DIG; ++cnt)
        {
            std::stringstream ss;
            ss << str <<std::setw(WIDTH) << std::setfill('0');
            ss << std::to_string(cnt);
            inner.print(ss.str());
        }
    }

};

template<>
struct BigNumbersPrinter<0>
{   
    void print(const std::string & str)
    {   
        for (auto cnt =0; cnt <MAX_DIG; ++cnt)
        {
        std::stringstream ss;
        ss << str <<std::setw(WIDTH) << std::setfill('0');
        ss << std::to_string(cnt);
        std::cout << ss.str() <<'\n';
        }
    }
};
template<std::size_t N>
class BigNumbersPrinterWrapper
{   
    BigNumbersPrinter<N> inner;
    public:
    void start()
    {
        std::string empty;
        inner.print(empty);
    }
};




}


int main()
{

    bigNumbers::BigNumbersPrinterWrapper<1> bnp{};
    bnp.start();

    // const auto max = 100;
    
    // for (auto a1 = 0; a1<max;++a1)
    // {
    //     //don't pad with zero.
    //     const auto s1 = std::to_string(a1);
    //     for (auto a2 = 0; a2<max;++a2)
    //     {
    //         //pad with zero
    //         std::cout<<s1<<a2 <<'\n';
    //     }
        
    // }

 //   std::cout<<i<<'\n';
}