#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <regex>
#include <iterator>
class Plane
{
    // row layout refernce
    // "{[0A][BC]}-{[DE][FG]}-{[HJ][K0]}"
    class Row
    {

    public:
        explicit Row() : blocks(~0) // make all bits set
        {
            blocks.reset(0); // first block doesn't fit two people;
            blocks.reset(5); // last block doesn't fit two people;
        }
        void seatPerson(char seatLetter)
        {
            //not checking for double sittings;
            auto block = convertSeatToBlock(seatLetter);
            // std::cout << "seat person in seat " << seatLetter << " to block " <<block <<'\n';
            blocks.reset(block); // this block now can't fit a family;
        }
        std::size_t possibleFamiliesToSeat() const
        {
            //this should count consecutive blocks of size 2;
            // in real life this wouldn't be hardcoded
            // maybe use some constants to check the entire bitset value against;
            if (testMidFamily()) //skip first block
            {
                if (blocks.test(1) && blocks.test(4)) // test sides
                {
                    return 2;
                }
                else
                {
                    return 1;
                }
            }
            if (testLeftFamily() || testRightFamily())
            {
                return 1;
            }
            return 0;
        }

    private:
        bool testLeftFamily() const
        {
            return blocks.test(1) && blocks.test(2);
        }
        bool testRightFamily() const
        {
            return blocks.test(3) && blocks.test(4);
        }
        bool testMidFamily() const
        {
            return blocks.test(2) && blocks.test(3);
        }
        std::bitset<6> blocks; // save memory by using a bitset to store blocks.
        static std::size_t convertSeatToBlock(char seatLetter)
        {
            if (seatLetter > 'I')
            {
                --seatLetter; // compenstate for lack of 'I' seat;
            }
            auto seatIndex = 1 + seatLetter - 'A'; //always skip the non existent sit at the first block;
            return (seatIndex / 2);
        }
    };

public:
    explicit Plane(std::size_t rows, const std::string &seatings) : rows_of_seats(rows)
    {
        //parse seatings into rows.
        //doesn't work with multi characters rows...
        const auto seatingPairs = parseSeatings(seatings);
        for (const auto &p : seatingPairs)
        {
            rows_of_seats[p.first - 1].seatPerson(p.second);
        }
    }
    std::size_t possibleFamiliesToSeat() const
    {
        return std::accumulate(std::begin(rows_of_seats), std::end(rows_of_seats), 0, [](std::size_t acc, const Row &r)
                               { return acc + r.possibleFamiliesToSeat(); });
        ;
    }

private:
    std::vector<Row> rows_of_seats;

    static std::vector<std::pair<std::size_t, char>> parseSeatings(const std::string &seatings)
    {

        std::vector<std::pair<std::size_t, char>> seats;
        if (!seatings.empty())
        {
            std::istringstream ss(seatings);
            while (ss)
            {
                std::string singleSeat;
                ss >> singleSeat;
                if (!singleSeat.empty())
                {
                const std::string matchSeats {"ABCDEFGHJK"};
                auto letterMatchIndex =singleSeat.find_first_of(matchSeats);
                if (letterMatchIndex == std::string::npos)
                {
                    letterMatchIndex = singleSeat.length()-1;
                }
                auto letterMatch =  singleSeat[letterMatchIndex];
                auto row = std::atoi(singleSeat.data());

                seats.push_back({row, letterMatch});
                }
            }
        }
        return seats;
    }
};
void TestPlanes()
{
    auto TestSeatings = [](std::size_t rows, const std::string &seatings, std::size_t expected)
    {
        std::cout << std::boolalpha;
        Plane plane{rows, seatings};
        const auto families = plane.possibleFamiliesToSeat();
        std::cout << "the plane can has seatings " << seatings << " can fit additional " << families << " families. as excepted? " << (families == expected);
        std::cout << std::noboolalpha << '\n';
    };
    //in the real world we would have something to generate the test cases.
    // "{[0A][BC]}-{[DE][FG]}-{[HJ][K0]}"

    {
        //no passengers
        TestSeatings(1, "", 2);
        TestSeatings(2, "", 4);
    }
    {
        //one passenger in row
        TestSeatings(1, "1A", 2);
        TestSeatings(1, "1B", 1);
        TestSeatings(1, "1C", 1);
        TestSeatings(1, "1D", 1);
        TestSeatings(1, "1E", 1);
        TestSeatings(1, "1F", 1);
        TestSeatings(1, "1G", 1);
        TestSeatings(1, "1H", 1);
        TestSeatings(1, "1J", 1);
        TestSeatings(1, "1K", 2);
    }

    {
        //two passengers in row
        TestSeatings(1, "1A 1K", 2); // no effect
        TestSeatings(1, "1A 1B", 1); // middle is empty
        TestSeatings(1, "1B 1E", 1); // right is empty
        TestSeatings(1, "1F 1G", 1); // left is empty
        TestSeatings(1, "1B 1F", 0); // neither is empty
    }
    {
        //multiple rows
        //TestSeatings(3, "1A 1K 2A 2D 3C 3F", 6 - 0 - 1 - 2);
    }
}

void TestRegex()
{
    auto testRegexRow = [](const std::string & row,const std::regex & pattern,std::size_t expected)
    {
        
        std::cout << std::boolalpha;
        auto familiesBegin = std::sregex_iterator(std::begin(row),std::end(row),pattern);
        auto familiesEnd = std::sregex_iterator();

        const auto matches = std::distance(familiesBegin,familiesEnd);
        std::cout << "the row " << row << " can fit additional " << matches << " families. as excepted? " << (matches == expected);
        std::cout << std::noboolalpha << '\n';
    };
    //"{[0A][BC]}-{[DE][FG]}-{[HJ][K0]}"
    
    auto familyOfFour = std::regex{"[a-zA-Z]{2}\\s?[a-zA-Z]{2}"};
    auto familyOfFourTogether = std::regex{"[a-zA-Z]{4}"};

    auto familyOfSix = std::regex{"[a-zA-Z]{3}\\s?[a-zA-Z]{3}"};

    testRegexRow("ABC DEFG HJK",familyOfFour,2);
    testRegexRow("AB0 DEFG 0JK",familyOfFour,1);
    testRegexRow("ABC DE0G 0JK",familyOfFour,1);
    testRegexRow("ABC D0FG HJK",familyOfFour,1);
    testRegexRow("AB0 D0FG 0JK",familyOfFour,0);

    testRegexRow("ABC DEFG HJK",familyOfFourTogether,1);
    testRegexRow("AB0 DEFG 0JK",familyOfFourTogether,1);
    testRegexRow("ABC DE0G 0JK",familyOfFourTogether,0);
    testRegexRow("ABC D0FG HJK",familyOfFourTogether,0);
    testRegexRow("AB0 D0FG 0JK",familyOfFourTogether,0);
    testRegexRow("ABCD DEFG HJK",familyOfFourTogether,2);
    testRegexRow("ABC DEFGHJKL",familyOfFourTogether,2);


    testRegexRow("ABC DEFG HJK",familyOfSix,1);
    testRegexRow("ABC DEFG 0JK",familyOfSix,1);
    testRegexRow("ABC 0EFG HJK",familyOfSix,1);
    testRegexRow("ABC D0FG HJK",familyOfSix,0);
    testRegexRow("AB0 D0FG 0JK",familyOfSix,0);
}
int main()
{
    //TestPlanes();
    TestRegex();
}