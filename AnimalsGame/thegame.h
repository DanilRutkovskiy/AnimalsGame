#ifndef THEGAME_H
#define THEGAME_H

#include <memory>

#include "animalstree.h"

class TheGame
{
public:
    TheGame();

private:
    void init();

private:
    std::unique_ptr<AnimalsTree> m_dataTree;
};

#endif // THEGAME_H
