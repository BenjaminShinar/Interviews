#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>
#include <string>
#include <set>
#include <functional>
#include <random>
#include <ctime>
/*
    memory game
    match 2 cards to win points.
    try to do a design first
    maybe build on one lone coder engine
    https://youtu.be/DDV_2cWT94U

    see if we can use a visitor design pattern for the players

*/

template <typename T>
struct Card
{
    T identifier;
    bool matched{false};
};

/**
 * @brief 
 * memory game that can do any number of series / pairs
 * @tparam N number of series
 * @tparam Q number of card in each series
 */
template <std::size_t N, std::size_t Q = 2, std::enable_if_t<(N > 1) && (Q > 1), bool> = true>
class GameBoard
{
    static constexpr std::size_t Size{N * Q};
    //not being random at all!
    //std::random_device rd;
    
    std::array<Card<int>, N * Q> m_cards;
    std::size_t matches{0};

    //mutable so that randomCard() can be const
    mutable std::mt19937 m_genenerator;
    mutable std::uniform_int_distribution<> distrib;


public:
    explicit GameBoard():m_genenerator({static_cast<long unsigned int>(time(0))}),distrib(0,Size-1)
    {
        std::generate(std::begin(m_cards), std::end(m_cards), [i = 0]() mutable
                      { return Card<int>{static_cast<int>(i++ / Q)}; });

        //shuffle
       std::shuffle(std::begin(m_cards),std::end(m_cards),m_genenerator);
    }


    [[nodiscard]] bool isValid(std::size_t id) const
    {
        return (id < Size && !m_cards.at(id).matched);
    }

    [[nodiscard]] std::size_t randomCard() const
    {
        // auto x = distrib(m_genenerator);
        // if (x > Size)
        // {
        //     std::cout << x <<" too large!\n";
        // }
        return  distrib(m_genenerator);
    }

    [[nodiscard]] std::size_t Matches() const
    {
        return matches;
    }
    [[nodiscard]] bool isDone() const
    {
        return matches == Size;
    }
    /**
     * @brief print the cards
     * un matched cards are printed as ?
     * requires std::to_string()
     * we need the ? character to be similar to the Type.
     */
    void printBoard() const
    {
        for (const auto &card : m_cards)
        {
            std::cout << (card.matched ? std::to_string(card.identifier) : "?");
        }
        std::cout << '\n';
    }

/**
 * @brief this is the serious function
 * it should use the visitor design pattern or something
 * 
 * @param id1 
 * @return int 
 */
    int drawConsecutively(std::size_t id1)
    {
        if(!isValid(id1))
        {
            return 0;
        }

        std::set<std::size_t> indices;
        indices.emplace(id1);
        const auto series = m_cards.at(id1).identifier;

        while (indices.size() < Q)
        {
            const auto id = randomCard();
            if(!isValid(id))
            {
                return 0;
            }
  
            if (indices.find(id) == std::end(indices) && m_cards.at(id).identifier == series)
            {
                indices.emplace(id);
            }
            else
            {
                //no match
                return 0;
            }
        }
        for (const auto &id : indices)
        {
            m_cards.at(id).matched = true;
        }

        ++matches;
        return Q;
    }
};

class Game
{
    //maybe this should take the logic of turns and handling the players
};

struct Player
{
    const std::string Name;
    //these should be injected somehow
    std::size_t firstDraw();
    std::size_t NextDraw();
};

int main()
{
    GameBoard<10, 4> gb;
    auto score{0};
    for (auto i = 0; i < 100000 && !gb.isDone(); ++i)
    {
        score += gb.drawConsecutively(gb.randomCard());
    }
    gb.printBoard();

    std::cout << "matches " << gb.Matches() << " score " << score << '\n';
}