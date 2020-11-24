#pragma once
#include <vector>
#include <string>
#include <memory>
#include "rttr/type.h"

namespace studio
{

class Node;
using NodePtr = std::shared_ptr<Node>;

class Node
{
public:
	Node(const std::string &_name, rttr::type t) : name(_name), type(t){}

	void addChild(NodePtr node)
	{
		node->parent = this;
		children.push_back(node);
	}

	bool hasChild() const
	{
		return !children.empty();
	}

	size_t childCount() const
	{
		return children.size();
	}

	NodePtr at(int n)
	{
		return children[n];
	}

	NodePtr get(const std::string &childName)
	{
		for (auto c : children) { if (c->name == childName)return c; }
		return nullptr;
	}
	
	NodePtr operator[](int n)
	{
		return at(n);
	}

	std::string name;
	rttr::type type;
	std::vector<NodePtr> children;
	Node *parent{nullptr};

};

}