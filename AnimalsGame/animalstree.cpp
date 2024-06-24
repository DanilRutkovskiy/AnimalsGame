#include "animalstree.h"



AnimalsTreeNode::~AnimalsTreeNode()
{
}

AnimalsTreeNode::AnimalsTreeNode(NodeType type, const std::string &data) :
    m_type{type}, m_data{data}, m_leftChild{nullptr}, m_rightChild{nullptr}
{

}

std::shared_ptr<AnimalsTreeNode> AnimalsTreeNode::addLeftChild(NodeType type, const std::string &data)
{
    m_leftChild = std::make_shared<AnimalsTreeNode>(type, data);

    return m_leftChild;
}

std::shared_ptr<AnimalsTreeNode> AnimalsTreeNode::addRightChild(NodeType type, const std::string &data)
{
    m_rightChild = std::make_shared<AnimalsTreeNode>(type, data);

    return m_rightChild;
}

void AnimalsTreeNode::setLeftChild(std::shared_ptr<AnimalsTreeNode> &left)
{
    m_leftChild = left;
}

void AnimalsTreeNode::setRightChild(std::shared_ptr<AnimalsTreeNode> &right)
{
    m_leftChild = right;
}

std::shared_ptr<AnimalsTreeNode> AnimalsTreeNode::leftChild()
{
    return m_leftChild;
}

std::shared_ptr<AnimalsTreeNode> AnimalsTreeNode::rightChild()
{
    return m_rightChild;
}

AnimalsTree::AnimalsTree(): m_head{nullptr}
{

}

void AnimalsTree::setHead(std::shared_ptr<AnimalsTreeNode>& head)
{
    m_head = head;
}
