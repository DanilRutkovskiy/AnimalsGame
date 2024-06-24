#ifndef ANIMALSTREE_H
#define ANIMALSTREE_H

#include <string>
#include <memory>
enum class NodeType{
    Answer,
    Question,
};

class AnimalsTreeNode{
public:
    ~AnimalsTreeNode();
    AnimalsTreeNode(NodeType type = NodeType::Question, const std::string& data = "");
    std::shared_ptr<AnimalsTreeNode> addLeftChild(NodeType type, const std::string& data);
    std::shared_ptr<AnimalsTreeNode> addRightChild(NodeType type, const std::string& data);
    void setLeftChild(std::shared_ptr<AnimalsTreeNode>& left);
    void setRightChild(std::shared_ptr<AnimalsTreeNode>& right);
    std::shared_ptr<AnimalsTreeNode> leftChild();
    std::shared_ptr<AnimalsTreeNode> rightChild();

private:
    std::string m_data;
    NodeType m_type;

    std::shared_ptr<AnimalsTreeNode> m_leftChild;
    std::shared_ptr<AnimalsTreeNode> m_rightChild;
};

class AnimalsTree
{
public:
    AnimalsTree();
    void setHead(std::shared_ptr<AnimalsTreeNode>& head);

private:
    std::shared_ptr<AnimalsTreeNode> m_head;
};

#endif // ANIMALSTREE_H
