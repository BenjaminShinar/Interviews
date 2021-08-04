#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <numeric>

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
        for (auto i = 0; i < seatings.length(); i+=2)
        {
            int row = std::stoi(seatings.substr(i+1,1)); 
            //std::cout << "seat person in row " << row << " to seat " << seatings[i] << '\n';
            rows_of_seats[row-1].seatPerson(seatings[i]);
        }
    }
    std::size_t possibleFamiliesToSeat() const
    {
        return std::accumulate(std::begin(rows_of_seats), std::end(rows_of_seats), 0, [](std::size_t acc, const Row &r)
                                                    { return acc + r.possibleFamiliesToSeat(); });;
    }

private:
    std::vector<Row> rows_of_seats;
};
void TestPlanes()
{
    auto TestSeatings = [](std::size_t rows, const std::string &seatings, std::size_t expected)
    {
        std::cout << std::boolalpha;
        Plane plane{rows, seatings};
        const auto families = plane.possibleFamiliesToSeat();
        std::cout << "the plane can has seatings " <<seatings << " can fit additional " << families << " families. as excepted? " << (families == expected);
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
        TestSeatings(1, "A1", 2);
        TestSeatings(1, "B1", 1);
        TestSeatings(1, "C1", 1);
        TestSeatings(1, "D1", 1);
        TestSeatings(1, "E1", 1);
        TestSeatings(1, "F1", 1);
        TestSeatings(1, "G1", 1);
        TestSeatings(1, "H1", 1);
        TestSeatings(1, "J1", 1);
        TestSeatings(1, "K1", 2);
    }

    {
        //two passengers in row
        TestSeatings(1, "A1K1", 2); // no effect
        TestSeatings(1, "A1B1", 1); // middle is empty
        TestSeatings(1, "B1E1", 1); // right is empty
        TestSeatings(1, "F1G1", 1); // left is empty
        TestSeatings(1, "B1F1", 0); // neither is empty
    }
    {
        //multiple rows
        TestSeatings(3, "A1K1A2D2C3F3", 6-0-1-2);
    }
}
int main()
{
    TestPlanes();
}