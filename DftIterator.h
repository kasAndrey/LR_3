
#ifndef _MY_DEPTH_ITERATOR_ 

#define _MY_DEPTH_ITERATOR_

#include "Iterator.h"
#include "node.h"
#include "Stack.h"

class DepthIterator : public Iterator {
public:
	DepthIterator(node* root);

	virtual void next() override;
	virtual bool has_next() const override;
	virtual int get_value() const override;

private:
	Stack<node*> _stack;

	void put_left_branch_to_stack(node* root);
};

DepthIterator::DepthIterator(node* root) {
	put_left_branch_to_stack(root);
}

void DepthIterator::put_left_branch_to_stack(node* root) {
	node* temp = root;
	while (temp != nullptr) {
		_stack.push(temp);
		temp = temp->left;
	}
}

void DepthIterator::next() {
	node* popped = _stack.pop();

	put_left_branch_to_stack(popped->right);
}

bool DepthIterator::has_next() const {
	return !_stack.is_empty();
}

int DepthIterator::get_value() const {
	return _stack.top()->value;
}

#endif	//! _MY_DEPTH_ITERATOR_