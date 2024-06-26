#ifndef ANIMALSTREE_H
#define ANIMALSTREE_H

#include <string>
#include <memory>
#include <sstream>
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
    std::shared_ptr<AnimalsTreeNode> leftChild();
    std::shared_ptr<AnimalsTreeNode> rightChild();
    void setLeftChild(std::shared_ptr<AnimalsTreeNode>& left);
    void setRightChild(std::shared_ptr<AnimalsTreeNode>& right);

    std::string data();
    NodeType type();

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

    std::string serialize();
    void deserialize(const std::string& data);

    std::shared_ptr<AnimalsTreeNode> getCurrentNode();
    void goLeft();
    void goRight();

private:
    std::string recSerialize(const std::shared_ptr<AnimalsTreeNode>& treeNode);
    std::shared_ptr<AnimalsTreeNode> recDeserialize(std::istringstream& ss);

private:
    std::shared_ptr<AnimalsTreeNode> m_head;
    std::shared_ptr<AnimalsTreeNode> m_current;
};

#endif // ANIMALSTREE_H
