#ifndef THEGAME_H
#define THEGAME_H

#include <memory>

#include "animalstree.h"

class TheGame
{
public:
    TheGame();

    NodeType currentState(std::string& str);
    void answerYes();
    void answerNo();
    void addNewQuestion(const std::string& question, const std::string& ans);
    void newGame();
    void saveProgress();
private:
    void init();
private:
    std::unique_ptr<AnimalsTree> m_dataTree;
};

#endif // THEGAME_H
