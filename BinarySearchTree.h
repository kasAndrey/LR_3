#ifndef  _MY_TREE_

#define _MY_TREE_

#include "DftIterator.h"
#include "BftIterator.h"
#include "Queue.h"

#include <iostream>

class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& other);
	~BinarySearchTree();
	bool contains(int value) const; 
	void insert(int value); 
	void remove(int value); 
	DepthIterator create_dft_iterator() const; 
	BreadthIterator create_bft_iterator() const; 
private:
	node* _root;

	static node* _extract_new_child(Queue<node*>& queue_of_children);
	static void _bind_queuing_parent_with_new_childrens(Queue<node*>& created_parents, Queue<node*>& children_to_copy);

	static bool _contains(node* root, int value);
	
	static void _insert_in_non_empty(node* root, int value);
	
	static node* _get_parent_of_searching(node* reference_to_root, int value);

	static node* _remove_and_get_replacement(node* element);

	static node* _remove_with_2_children(node* element);
	static node* _remove_with_1_children(node* element);
	static node* _remove_with_0_children(node* element);

	static node* _get_left_leaf(node* root);

	static void _delete(node* root);
};


BinarySearchTree::BinarySearchTree() :_root(nullptr) {

}

node* BinarySearchTree::_extract_new_child(Queue<node*>& children) {
	node* extracted = children.pop();


	if (extracted != nullptr) {
		children.push(extracted->left);
		children.push(extracted->right);
	}

	return extracted;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) : _root(nullptr) {
	if (other._root != nullptr) {
		Queue<node*> created_parents;
		Queue<node*> children_to_copy;

		_root = new node(other._root->value);
		created_parents.push(_root);

		children_to_copy.push(other._root->left);
		children_to_copy.push(other._root->right);

		while (!children_to_copy.is_empty())
			_bind_queuing_parent_with_new_childrens(created_parents, children_to_copy);

	}
}

void BinarySearchTree::_bind_queuing_parent_with_new_childrens(Queue<node*>& created_parents, Queue<node*>& children_to_copy) {
	node* temp_parent = created_parents.pop();


	node* left_child = _extract_new_child(children_to_copy);
	node* right_child = _extract_new_child(children_to_copy);



	if (left_child != nullptr) {
		node* copy_for_left_child = new node(left_child->value);
		temp_parent->left = copy_for_left_child;

		created_parents.push(copy_for_left_child);
	}
	else
		temp_parent->left = nullptr;

	if (right_child != nullptr) {
		node* copy_for_right_child = new node(right_child->value);
		temp_parent->right = copy_for_right_child;

		created_parents.push(copy_for_right_child);
	}
	else
		temp_parent->right = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
	_delete(_root);
}

void BinarySearchTree::remove(int value) {
	if (_root == nullptr)
		return;

	if (_root->value == value) {
		_root = _remove_and_get_replacement(_root);
		return;
	}

	node* parent_of_removing = _get_parent_of_searching(_root, value);

	if (parent_of_removing == nullptr)
		return;

	if (parent_of_removing->left && parent_of_removing->left->value == value)
		parent_of_removing->left = _remove_and_get_replacement(parent_of_removing->left);
	else
		parent_of_removing->right = _remove_and_get_replacement(parent_of_removing->right);
}

bool BinarySearchTree::contains(int value) const {
	return _contains(_root, value);
}


void  BinarySearchTree::insert(int value) {
	if (_root == nullptr)
		_root = new node(value);
	else
		_insert_in_non_empty(_root, value);
}

node* BinarySearchTree::_remove_and_get_replacement(node* element) {
	if (element->left == nullptr && element->right == nullptr)
		return _remove_with_0_children(element);
	else
		if (element->left == nullptr || element->right == nullptr)
			return _remove_with_1_children(element);
		else
			return _remove_with_2_children(element);
}

node* BinarySearchTree::_remove_with_2_children(node* element) {
	node* left_child = element->left;
	node* right_child = element->right;



	if (right_child->left == nullptr)
		right_child->left = left_child;
	else
		_get_left_leaf(right_child)->left = left_child;

	delete element;

	return right_child;
}

node* BinarySearchTree::_remove_with_1_children(node* element) {
	node* left_child = element->left;
	node* right_child = element->left;

	delete element;



	if (right_child == nullptr)
		return left_child;


	return right_child;
}

node* BinarySearchTree::_remove_with_0_children(node* element) {
	delete element;

	return nullptr;
}

node* BinarySearchTree::_get_left_leaf(node* root) {
	node* temp = root;

	while (temp->left != nullptr)
		temp = temp->left;

	return temp;
}
node* BinarySearchTree::_get_parent_of_searching(node* parent, int value) {
	node* previous = parent;
	node* temp = (value < parent->value) ? parent->left : parent->right;

	while (temp != nullptr) {
		if (temp->value == value)
			return previous;

		previous = temp;
		temp = (value < temp->value) ? temp->left : temp->right;
	}

	return nullptr;
}

/*
bool BinarySearchTree::_contains(node* root, int value) {
	if (root == nullptr)
		return false;
	if (value == root->value)
		return true;
	if (value < root->value)
		return _contains(root->left, value);
	return _contains(root->right, value);
}
*/

DepthIterator BinarySearchTree::create_dft_iterator() const {
	return DepthIterator(_root);
}

BreadthIterator BinarySearchTree::create_bft_iterator() const {
	return BreadthIterator(_root);
}

bool BinarySearchTree::_contains(node* root, int value) {
	node* temp = root;

	while (temp != nullptr) {
		if (value == temp->value)
			return true;

		if (value < temp->value)
			temp = temp->left;
		else
			temp = temp->right;
	}

	return false;
}

void BinarySearchTree::_insert_in_non_empty(node* root, int value) {
	node* temp = root;

	while (value != temp->value) {
		if (value < temp->value)
			if (temp->left == nullptr) {
				temp->left = new node(value);
				break;
			}
			else
				temp = temp->left;
		else
			if (temp->right == nullptr) {
				temp->right = new node(value);
				break;
			}
			else
				temp = temp->right;
	}
}

void BinarySearchTree::_delete(node* root) {
	if (root == nullptr)
		return;

	_delete(root->left);
	_delete(root->right);

	delete root;
}

#endif // ! _MY_TREE_