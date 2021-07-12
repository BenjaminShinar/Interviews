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
    //maybe a different templated interface...
    virtual std::size_t firstDraw(const T &gb) = 0;
    virtual std::size_t nextDraw(const T &gb) = 0;
};

template <typename T>
struct IGame
{

    [[nodiscard]] virtual bool isDone() const = 0;
    virtual void playTurn(Player<T> &currentPlayer) = 0;
    virtual void printGame() const = 0;
};

template <typename T>
struct Card
{
    T identifier;
    bool matched{false};
};

class ScoreBoard
{
public:
    void addScore(const std::map<std::string, int> &roundScores, std::size_t round)
    {
        for (const auto &entry : roundScores)
        {
            m_scores[entry.first][round] += entry.second;
        }
    }
    void printScores() const
    {
        for (const auto &entry : m_scores)
        {
            std::cout << "Player: " << entry.first;
            auto total{0};
            for (const auto &match : entry.second)
            {
                std::cout << " {" << match.first << " : " << match.second << "} ";
                total += match.second;
            }

            std::cout << "{total : " << total << "}" << '\n';
        }
    }

private:
    std::map<std::string, std::map<std::size_t, int>> m_scores;
};
/**
 * @brief 
 * memory game that can do any number of series / pairs
 * @tparam N number of series
 * @tparam Q number of card in each series
 */
template <std::size_t N, std::size_t Q = 2, std::enable_if_t<(N > 1) && (Q > 1), bool> = true>
class GameBoard : public IGame<GameBoard<N, Q>>
{
    static constexpr std::size_t Size{N * Q};
    //not being random at all!
    //std::random_device rd;
    std::map<std::string, int> m_scores;
    std::array<Card<int>, N * Q> m_cards;
    std::size_t matches{0};

    //mutable so that randomCard() can be const
    mutable std::mt19937 m_genenerator;
    mutable std::uniform_int_distribution<> distrib;
    /*******/

    void flipCards(const std::set<std::size_t> &cardsIndices, bool matched)
    {
        for (const auto &id : cardsIndices)
        {
            m_cards.at(id).matched = matched;
        }
    }

    std::size_t UpdateScoreAndCards(const std::string &playerName, const std::set<std::size_t> &cardsIndices)
    {

        flipCards(cardsIndices, true);
        ++matches;
        m_scores[playerName] += Q;
        return Q;
    }

    /**
 * @brief this is the serious function
 * it should use the visitor design pattern or something
 * maybe strategy
 * @param currentPlayer 
 */
    void drawConsecutively(Player<GameBoard<N, Q>> &currentPlayer)
    {
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

    void resetBoard()
    {
        m_scores.clear();
        matches = 0;
        //flip cards to unmatchedState
        std::for_each(std::begin(m_cards), std::end(m_cards), [](auto &c)
                      { c.matched = false; });
        //shuffle
        std::shuffle(std::begin(m_cards), std::end(m_cards), m_genenerator);
    }

public:
    explicit GameBoard() : m_genenerator({static_cast<long unsigned int>(time(0))}), distrib(0, Size - 1)
    {
        std::generate(std::begin(m_cards), std::end(m_cards), [i = 0]() mutable
                      { return Card<int>{static_cast<int>(i++ / Q)}; });
        reset();
    }

    //TODO: this needs to be inaccesble for anybody except Game
    void reset()
    {
        resetBoard();
    }

#pragma region IGame
    [[nodiscard]] bool isDone() const override
    {
        return matches == N;
    }
    void playTurn(Player<GameBoard<N, Q>> &currentPlayer) override
    {
        drawConsecutively(currentPlayer);
    }
  /**
     * @brief print the cards
     * un matched cards are printed as ?
     * requires std::to_string()
     * we need the ? character to be similar to the Type.
     */
    void printGame() const override
    {
        for (const auto &card : m_cards)
        {
            std::cout << (card.matched ? std::to_string(card.identifier) : "?");
        }
        std::cout << '\n';
    }

#pragma endregion

    [[nodiscard]] std::optional<int> checkCardStatus(std::size_t index)
    {
        if (isValid(index))
        {
            return {m_cards.at(index).identifer};
        }
        return {};
    }

    const std::map<std::string, int> &getScores() const
    {
        return m_scores;
    }

    [[nodiscard]] bool isValid(std::size_t id) const
    {
        return (id < Size && !m_cards.at(id).matched);
    }

    [[nodiscard]] std::size_t randomCard() const
    {
        return distrib(m_genenerator);
    }

    [[nodiscard]] std::size_t Matches() const
    {
        return matches;
    }
};

template <typename T>
class Game : public IGame<T>
{
private:
    T m_game_board;
    ScoreBoard m_score_board;
    std::size_t m_current_round{1};

public:
#pragma region IGame

    void playTurn(Player<T> &player) override
    {
        if (isDone())
        {
            return;
        }
        m_game_board.playTurn(player);
        if (isDone())
        {
            m_score_board.addScore(m_game_board.getScores(), m_current_round);
        }
    }
    [[nodiscard]] bool isDone() const override
    {
        return m_game_board.isDone();
    }
  
    void printGame() const override
    {
        m_game_board.printGame();
    }
#pragma endregion

    void reset()
    {
        m_game_board.reset();
        ++m_current_round;
    }

    void printScore() const
    {
        m_score_board.printScores();
    }
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
    needs to implment


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
    Game<GB_T> game;
    RandomPlayer<GB_T> player_1("ryu");
    RandomPlayer<GB_T> player_2("ken");
    CheckOncePlayer<GB_T> player_3("dan");
    CheckNTimesPlayer<GB_T, 2> player_4("Guile");
    CheckNTimesPlayer<GB_T, 3> player_5("Sakura");
    SeriesSearchingPlayer<GB_T, 3> player_6("Chun-li");
    for (auto round = 0; round < 5; ++round)
    {
        for (auto i = 0; i < 10000 && !game.isDone(); ++i)
        {
            game.playTurn(player_1);
            game.playTurn(player_2);
            game.playTurn(player_3);
            game.playTurn(player_4);
            game.playTurn(player_5);
            game.playTurn(player_6);
        }
        game.reset();
    }
    game.printScore();
}