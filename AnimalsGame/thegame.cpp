#include "thegame.h"

TheGame::TheGame(): m_dataTree {std::make_unique<AnimalsTree>()}
{
    init();
}

void TheGame::init()
{
    auto head = std::make_shared<AnimalsTreeNode>(NodeType::Question, "Это млекопитающее?");
    auto leftCh = std::make_shared<AnimalsTreeNode>(NodeType::Question, "Оно лает?");
    auto rigthCh = std::make_shared<AnimalsTreeNode>(NodeType::Question, "Оно покрыто чешуей?");
    head->setLeftChild(leftCh);
    head->setRightChild(rigthCh);
    leftCh->addLeftChild(NodeType::Answer, "Собака");
    auto giraffeQ = leftCh->addRightChild(NodeType::Question, "Оно с длинной шеей?");
    giraffeQ->addLeftChild(NodeType::Answer, "Жираф");
    auto waterQ = rigthCh->addLeftChild(NodeType::Question, "Оно дышит в воде?");
    rigthCh->addRightChild(NodeType::Answer, "Птица");
    waterQ->addLeftChild(NodeType::Answer, "Рыба");
    waterQ->addRightChild(NodeType::Answer, "Змея");

    m_dataTree->setHead(head);

    auto check = m_dataTree->serialize();

    AnimalsTree test;
    test.deserialize(check);
}
