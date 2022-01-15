#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{

}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> &&edge)
{
    _childEdges.push_back(std::move(edge));
}


void GraphNode::MoveChatbotHere(ChatBot &&chatbot)
//Argument being rvalue reference is the reason why my output is not calling the move constructor
//only move assigment operator
//However efficienty is bigger in this way
{
    _chatBot = std::move(chatbot);
    _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(std::move(_chatBot));
}


GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{

    return _childEdges[index].get();

}