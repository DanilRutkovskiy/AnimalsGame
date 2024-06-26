#include "animalstree.h"
#include <cassert>

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
    m_rightChild = right;
}

void AnimalsTreeNode::setData(const std::string &new_data)
{
    m_data = new_data;
}

void AnimalsTreeNode::setType(NodeType new_type)
{
    m_type = new_type;
}

std::shared_ptr<AnimalsTreeNode> AnimalsTreeNode::leftChild()
{
    return m_leftChild;
}

std::shared_ptr<AnimalsTreeNode> AnimalsTreeNode::rightChild()
{
    return m_rightChild;
}

std::string AnimalsTreeNode::data()
{
    return m_data;
}

NodeType AnimalsTreeNode::type()
{
    return m_type;
}

AnimalsTree::AnimalsTree(): m_head{std::make_shared<AnimalsTreeNode>(NodeType::Null, "")}, m_current(nullptr)
{

}

void AnimalsTree::setHead(std::shared_ptr<AnimalsTreeNode>& head)
{
    m_head = head;
}

void AnimalsTree::resetHeadAsCurrentNode()
{
    m_current = m_head;
}

std::string AnimalsTree::serialize()
{
    return recSerialize(m_head);
}

void AnimalsTree::deserialize(const std::string &data)
{
    std::istringstream iss{data};
    m_head = recDeserialize(iss);
    m_current = m_head;
}

std::shared_ptr<AnimalsTreeNode> AnimalsTree::getCurrentNode()
{
    if(m_current != nullptr){
        return m_current;
    }
    else{
        assert(0);
        return nullptr;
    }
}

void AnimalsTree::goLeft()
{
    if(m_current != nullptr){
        if(m_current->leftChild() == nullptr){
            auto child = std::make_shared<AnimalsTreeNode>(NodeType::Null, "");
            m_current->setLeftChild(child);
        }
        m_current = m_current->leftChild();
    }
    else{
        assert(0);
    }
}

void AnimalsTree::goRight()
{
    if(m_current != nullptr){
        if(m_current->rightChild() == nullptr){
            auto child = std::make_shared<AnimalsTreeNode>(NodeType::Null, "");
            m_current->setRightChild(child);
        }
        m_current = m_current->rightChild();
    }
    else{
        assert(0);
    }
}

std::string AnimalsTree::recSerialize(const std::shared_ptr<AnimalsTreeNode> &node)
{
    if(node == nullptr){
        return "null null ";
    }

    std::stringstream ss;
    std::string temp = node->data();
    for(auto& ch : temp){
        if(ch == ' '){
            ch = '_';
        }
    }
    ss << temp << " ";
    ss << std::to_string(static_cast<int>(node->type())) << " ";
    ss << recSerialize(node->leftChild());
    ss << recSerialize(node->rightChild());

    return ss.str();
}

std::shared_ptr<AnimalsTreeNode> AnimalsTree::recDeserialize(std::istringstream& iss)
{
    std::string val;
    std::string type;

    std::shared_ptr<AnimalsTreeNode> left;
    std::shared_ptr<AnimalsTreeNode> right;

    iss >> val;
    for(auto& ch : val){
        if(ch == '_'){
            ch = ' ';
        }
    }
    iss >> type;
    if(val == "null" || type == "null"){
        return nullptr;
    }

    if(iss){
        left = recDeserialize(iss);
        right = recDeserialize(iss);
        auto ret = std::make_shared<AnimalsTreeNode>(static_cast<NodeType>(std::stoi(type)), val);
        ret->setRightChild(right);
        ret->setLeftChild(left);
        return ret;
    }

    return nullptr;
}
