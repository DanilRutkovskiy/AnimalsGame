#include "thegame.h"
#include "dbmanager.h"
#include "fstream"

TheGame::TheGame(): m_dataTree {std::make_unique<AnimalsTree>()}
{
    init();
}

NodeType TheGame::currentState(std::string &str)
{
    auto curNode = m_dataTree->getCurrentNode();
    if(curNode != nullptr){
        str = curNode->data();
        return curNode->type();
    }
    else{
        str = "";
        return NodeType::Null;
    }
}

void TheGame::init()
{
    auto dbmanager = DBManager::instance();

    if(dbmanager == nullptr){
        assert(0);
        return;
    }

    std::string tree_data = dbmanager->getTreeData();
    if(tree_data != ""){
        //Сделать проверку на корректность
        m_dataTree->deserialize(tree_data);

        return;
    }

    std::ifstream file{"treeData.txt"};
    if(file.is_open()){
        std::getline(file, tree_data);
        if(tree_data != ""){
            m_dataTree->deserialize(tree_data);
        }
    }
    else{
        std::ofstream{"treeData.txt"};
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

void TheGame::addNewQuestion(const std::string &question, const std::string &ans)
{
    auto curr = m_dataTree->getCurrentNode();
    if(curr != nullptr){
        std::shared_ptr<AnimalsTreeNode> temp = make_shared<AnimalsTreeNode>(NodeType::Answer, curr->data());
        curr->setData(question);
        curr->setType(NodeType::Question);
        curr->addLeftChild(NodeType::Answer, ans);
        curr->setRightChild(temp);
    }
    else{
        assert(0);
    }
}

void TheGame::newGame()
{
    m_dataTree->resetHeadAsCurrentNode();
}

void TheGame::saveProgress()
{
    auto dbmanager = DBManager::instance();
    if(dbmanager){
        dbmanager->saveTreeData(m_dataTree->serialize());
    }
    else{
        assert(0);
    }

    std::ofstream file{"treeData.txt"};

    if(file.is_open()){
        file << m_dataTree->serialize();
        file.close();
    }
    else{
        assert(0);
    }
}
