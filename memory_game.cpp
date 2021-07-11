#include <iostream>
#include <array>
#include <cmath>
#include <optional>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <deque>
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
struct Player
{

    const std::string Name;

    explicit Player(const std::string &name) : Name(name){

                                               };
    //these should be injected somehow
    virtual std::size_t firstDraw(const T &gb) = 0;
    virtual std::size_t nextDraw(const T &gb) = 0;
};

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
    std::map<std::string, std::size_t> m_scores;
    std::array<Card<int>, N * Q> m_cards;
    std::size_t matches{0};

    //mutable so that randomCard() can be const
    mutable std::mt19937 m_genenerator;
    mutable std::uniform_int_distribution<> distrib;

    std::size_t UpdateScoreAndCards(const std::string &playerName, const std::set<std::size_t> &cardsIndices)
    {
        for (const auto &id : cardsIndices)
        {
            m_cards.at(id).matched = true;
        }

        ++matches;
        m_scores[playerName] += Q;
        return Q;
    }

public:
    explicit GameBoard() : m_genenerator({static_cast<long unsigned int>(time(0))}), distrib(0, Size - 1)
    {
        std::generate(std::begin(m_cards), std::end(m_cards), [i = 0]() mutable
                      { return Card<int>{static_cast<int>(i++ / Q)}; });

        //shuffle
        std::shuffle(std::begin(m_cards), std::end(m_cards), m_genenerator);
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
        return distrib(m_genenerator);
    }

    [[nodiscard]] std::size_t Matches() const
    {
        return matches;
    }
    [[nodiscard]] bool isDone() const
    {
        return matches == Size;
    }
    [[nodiscard]] std::optional<int> checkCardStatus(std::size_t index)
    {
        if (isValid(index))
        {
            return {m_cards.at(index).identifer};
        }
        return {};
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
    void printScores() const
    {
        for (const auto &p : m_scores)
        {
            std::cout << p.first << " : " << p.second << " points!" << '\n';
        }
    }

    /**
 * @brief this is the serious function
 * it should use the visitor design pattern or something
 * maybe strategy
 * @param id1 
 * @return int 
 */

    void drawConsecutively(Player<GameBoard<N, Q>> &currentPlayer)
    {
        if (isDone())
        {
            return;
        }
        auto firstCard = currentPlayer.firstDraw(*this);
        if (!isValid(firstCard))
        {
            return;
        }

        std::set<std::size_t> indices;
        indices.emplace(firstCard);
        const auto series = m_cards.at(firstCard).identifier;

        while (indices.size() < Q)
        {
            const auto nextCard = currentPlayer.nextDraw(*this);
            if (!isValid(nextCard))
            {
                return;
            }

            if (indices.find(nextCard) == std::end(indices) && m_cards.at(nextCard).identifier == series)
            {
                indices.emplace(nextCard);
            }
            else
            {
                //no match
                return;
            }
        }
        UpdateScoreAndCards(currentPlayer.Name, indices);
    }
};

class Game
{
    //maybe we want to play many Games with the same players, so score should be here?
    //that way we can shuffle the board as many times as we need,
    //maybe this should take the logic of turns and handling the players
};

template <typename T>
struct RandomPlayer : public Player<T>
{

    explicit RandomPlayer(const std::string &name) : Player<T>(name)
    {
    }
    std::size_t firstDraw(const T &gb) override
    {
        return gb.randomCard();
    }

    std::size_t nextDraw(const T &gb) override
    {
        return gb.randomCard();
    }
};

template <typename T>
struct CheckOncePlayer : public Player<T>
{

    explicit CheckOncePlayer(const std::string &name) : Player<T>(name)
    {
    }

    std::size_t firstDraw(const T &gb) override
    {
        return drawUnmatchedCard(gb);
    }

    std::size_t nextDraw(const T &gb) override
    {
        return drawUnmatchedCard(gb);
    }

private:
    std::size_t drawUnmatchedCard(const T &gb)
    {
        auto id = gb.randomCard();
        if (!gb.isValid(id))
        {
            id = gb.randomCard();
        }

        return id;
    }
};

template <typename T, std::size_t N>
struct CheckNTimesPlayer : public Player<T>
{

    explicit CheckNTimesPlayer(const std::string &name) : Player<T>(name)
    {
    }

    std::size_t firstDraw(const T &gb) override
    {
        return drawUnmatchedCard(gb);
    }

    std::size_t nextDraw(const T &gb) override
    {
        return drawUnmatchedCard(gb);
    }

private:
    std::size_t drawUnmatchedCard(const T &gb)
    {
        auto tries = N;
        auto id = gb.randomCard();
        while (tries > 0 && !gb.isValid(id))
        {
            id = gb.randomCard();
            --tries;
        }

        return id;
    }
};

template <typename T, std::size_t N>
struct SeriesSearchingPlayer : public Player<T>
{
    /*
    first (if nothing at queue) check randomly
    if reched second stage last decidsion inside queue.



    */
private:
    std::size_t last_Request{0};
    std::size_t current_iteration{0};
    std::vector<std::size_t> knownSeries;

public:
    explicit SeriesSearchingPlayer(const std::string &name) : Player<T>(name)
    {
    }
    std::size_t firstDraw(const T &gb) override
    {
        return drawUnmatchedCard(gb);
    }

    std::size_t nextDraw(const T &gb) override
    {
        
        return drawUnmatchedCard(gb);

    }

private:
    std::size_t drawUnmatchedCard(const T &gb)
    {
        auto tries = N;
        auto id = gb.randomCard();
        while (tries > 0 && !gb.isValid(id))
        {
            id = gb.randomCard();
            --tries;
        }
        return id;
    }
};

int main()
{
    using GB_T = GameBoard<10, 4>;
    GB_T gb;
    RandomPlayer<GB_T> player_1("ryu");
    RandomPlayer<GB_T> player_2("ken");
    CheckOncePlayer<GB_T> player_3("dan");
    CheckNTimesPlayer<GB_T, 2> player_4("Guile");
    CheckNTimesPlayer<GB_T, 3> player_5("Sakura");
    SeriesSearchingPlayer<GB_T, 3> player_6("Chun-li");

    //auto score{0};
    for (auto i = 0; i < 10000 && !gb.isDone(); ++i)
    {
        gb.drawConsecutively(player_1);
        gb.drawConsecutively(player_2);
        gb.drawConsecutively(player_3);
        gb.drawConsecutively(player_4);
        gb.drawConsecutively(player_5);
        gb.drawConsecutively(player_6);
    }

    gb.printBoard();
    gb.printScores();
    std::cout << "matches " << gb.Matches() << '\n';
}