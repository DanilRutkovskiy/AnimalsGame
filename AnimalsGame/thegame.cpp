#include "thegame.h"
#include "dbmanager.h"

TheGame::TheGame(): m_dataTree {std::make_unique<AnimalsTree>()}
{
    init();
}

void TheGame::init()
{
    auto dbmanager = DBManager::instance();

    if(dbmanager == nullptr){
        assert(0);
        return;
    }

    std::string tree_data = dbmanager->getTreeData();
    m_dataTree->deserialize(tree_data);
    //TODO что если tree_data не получена - надо сделать стандартную заглушку, в идеале - из файла
}

std::string TheGame::getQuestion()
{
    if(m_dataTree->getCurrentNode() != nullptr){
        return m_dataTree->getCurrentNode()->data();
    }
    else{
        return "";
    }
}

void TheGame::answerYes()
{
    m_dataTree->goLeft();
}

void TheGame::answerNo()
{
    m_dataTree->goRight();
}
