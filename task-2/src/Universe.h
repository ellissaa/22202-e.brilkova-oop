#ifndef UNIVERSE_H_INCLUDED
#define UNIVERSE_H_INCLUDED

#include <string>
#include <set>
#include <utility>

class Universe {
private:
    std::string m_name; // имя для той вселенной, с которой работаем
    std::set<int> m_birth_rule; // правило для рождения клеток
    std::set<int> m_survival_rule; // правило для выживания клеток
    int m_iteration_number;
    static int m_width;
    static int m_height;
    char* m_field;

    /// @brief заполняет поле
    /// @param coords координаты живых клеток
    void StartField(std::set<std::pair<int, int>> coords);

    int GetNumOfNeighbours(int x, int y);

public:
    static std::string default_name; // общее имя вселенной для всего класса
    static std::set<int> default_birth_rule;
    static std::set<int> default_survival_rule;

    /**
     * @brief Конструктор для вселенной.
     * @param name имя вселенной.
     * @param birth_rule количество клеток, необходимое для рождения данной клетки.
     * @param survival_rule количество клеток, необходимое для того, чтобы клетка не умерла.
     * @param coords множество координат клеток.
    */
    Universe(std::string name, std::set<int> birth_rule, std::set<int> survival_rule,
             std::set<std::pair<int, int>> coords);
    
    ~Universe();

    /// @brief следующее состояние вселенной
    void Tick();

    void PrintUniverse();

    std::string name();

    std::set<int> birth_rule();

    std::set<int> survival_rule();

    std::set<std::pair<int, int>> coords(); // множество координат живых клеток
};

#endif