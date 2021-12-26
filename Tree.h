#ifndef  _MY_TREE_

#define _MY_TREE_

#include "DftIterator.h"
#include "BftIterator.h"
#include "Queue.h"

#include <iostream>

class Tree
{
public:
	Tree();
	Tree(const Tree& other);
	~Tree();
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

Tree::Tree() :_root(nullptr) {

}

Tree::Tree(const Tree& other) : _root(nullptr) {
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

/*
Tree::node* Tree::_get_parent_of_searching(Tree::node* parent, int value) {
	if (value < parent->value)
		if (parent->left != nullptr)
			if (parent->left->value == value)
				return parent;
			else
				_get_parent_of_searching(parent->left);
		else
			return nullptr;
	else
		//if (value > parent->value)
		if (parent->right != nullptr)
			if (parent->right->value == value)
				return parent;
			else
				_get_parent_of_searching(parent->right);
		else
			return nullptr;
}
*/

node* Tree::_extract_new_child(Queue<node*>& children) {
	node* extracted = children.pop();

	if (extracted != nullptr) {
		children.push(extracted->left);
		children.push(extracted->right);
	}

	return extracted;
}

//Tree::Tree(const Tree& other) : _root(nullptr) {
//	if (other._root != nullptr) {
//		BreadthIterator iterator = other.create_bft_iterator();
//
//		_root = new node(iterator.get_value()); //pushing first in root
//		iterator.next();
//
//		for (iterator; iterator.has_next(); iterator.next())
//			_insert_in_non_empty(_root, iterator.get_value());
//	}
//}

void Tree::_bind_queuing_parent_with_new_childrens(Queue<node*>& created_parents, Queue<node*>& children_to_copy) {
	node* temp_parent = created_parents.pop();


	node* left_child = _extract_new_child(children_to_copy);
	node* right_child = _extract_new_child(children_to_copy);



	if (left_child != nullptr)
	{
		node* copy_for_left_child = new node(left_child->value);
		temp_parent->left = copy_for_left_child;

		created_parents.push(copy_for_left_child);
	}
	else
		temp_parent->left = nullptr;

	if (right_child != nullptr)
	{
		node* copy_for_right_child = new node(right_child->value);
		temp_parent->right = copy_for_right_child;

		created_parents.push(copy_for_right_child);
	}
	else
		temp_parent->right = nullptr;
}

/*
void Tree::_insert(node* root, int value) {
	if (root == nullptr)
		return new node(value);
	if (value < root->value)
		root->left = _insert(root->left, value);
	if (value > root->value)
		root->right = _insert(root->right, value);
	return root;
}
*/

/*
void Tree::_insert(node*& reference_to_root, int value) {
	node** address_of_temp = &reference_to_root; //saving address of temp element to change refference which pointed to it
	while (true) {
		if (*address_of_temp == nullptr) {			//if element by address is absent, put new element by this address
			*address_of_temp = new node(value);		//inserting go to only empty leafs
			return;
		}
		if ((*address_of_temp)->value == value)		//if value exist in tree -> out
			return;
		if (value < (*address_of_temp)->value)		//if inserting value should be in left part
			address_of_temp = &((*address_of_temp)->left); //copy address of variable, which contains address of left branch
		else
			address_of_temp = &((*address_of_temp)->right);	//same with right
	}
}
*/

Tree::~Tree() {
	_delete(_root);
}

bool Tree::contains(int value) const {
	return _contains(_root, value);
}

void  Tree::insert(int value) {
	if (_root == nullptr)
		_root = new node(value);
	else
		_insert_in_non_empty(_root, value);
}

void Tree::remove(int value) {
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

/*
node* Tree::_insert_in_non_empty(node* root, int value) {
	if (root == nullptr)
		return new node(value);
	node* temp = root;
	while (true) {
		if (value == temp->value)	//if value is already pushed
			break;
		if (value < temp->value)			//if value should be in left branch
			if (temp->left == nullptr) {	//if left branch doesn't exist then add new node
				temp->left = new node(value);
				break;
			}
			else
				temp = temp->left;			//if left branch exists then move down
		else								//if value should be in right branch
			if (temp->right == nullptr) {	//if right branch doesn't exist then add new node
				temp->right = new node(value);
				break;
			}
			else
				temp = temp->right;			//if right branch exists then move down
	}
	return root; //return old root
}
*/

node* Tree::_remove_and_get_replacement(node* element) {
	if (element->left == nullptr && element->right == nullptr)
		return _remove_with_0_children(element);
	else
		if (element->left == nullptr || element->right == nullptr)
			return _remove_with_1_children(element);
		else
			return _remove_with_2_children(element);
}

node* Tree::_remove_with_2_children(node* element) {
	node* left_child = element->left;
	node* right_child = element->right;


	if (right_child->left == nullptr)
		right_child->left = left_child;
	else
		_get_left_leaf(right_child)->left = left_child;

	delete element;

	return right_child;
}

node* Tree::_remove_with_1_children(node* element) {
	node* left_child = element->left;
	node* right_child = element->left;

	delete element;



	if (right_child == nullptr)
		return left_child;


	return right_child;
}

node* Tree::_remove_with_0_children(node* element) {
	delete element;

	return nullptr;
}

node* Tree::_get_left_leaf(node* root) {
	node* temp = root;

	while (temp->left != nullptr)
		temp = temp->left;

	return temp;
}
node* Tree::_get_parent_of_searching(node* parent, int value) {
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


DepthIterator Tree::create_dft_iterator() const {
	return DepthIterator(_root);
}


BreadthIterator Tree::create_bft_iterator() const {
	return BreadthIterator(_root);
}


bool Tree::_contains(node* root, int value) {
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


void Tree::_insert_in_non_empty(node* root, int value) {
	node* temp = root;

	while (true) {
		if (value == temp->value)
			break;

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


void Tree::_delete(node* root) {
	if (root == nullptr)
		return;

	_delete(root->left);
	_delete(root->right);

	delete root;
}
#endif // ! _MY_TREE_