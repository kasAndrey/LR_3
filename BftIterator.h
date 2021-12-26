#ifndef _MY_BREADTH_ITERATOR_ 

#define _MY_BREADTH_ITERATOR_

#include "Iterator.h"
#include "node.h"
#include "Queue.h"

class BreadthIterator : public Iterator {
public:
	BreadthIterator(node* root);

	virtual void next() override;
	virtual bool has_next() const override;
	virtual int get_value() const override;
private:
	Queue<node*> _queue;

	void put_children_to_queue(node* root);
};

BreadthIterator::BreadthIterator(node* root) {
	if (root != nullptr)
		_queue.push(root);
}

void BreadthIterator::next() {
	node* popped = _queue.pop();

	put_children_to_queue(popped);
}

void BreadthIterator::put_children_to_queue(node* root) {
	if (root->left != nullptr)
		_queue.push(root->left);

	if (root->right != nullptr)
		_queue.push(root->right);
}

bool BreadthIterator::has_next() const {
	return !_queue.is_empty();
}

int BreadthIterator::get_value() const {
	return _queue.front()->value;
}

#endif	//! _MY_BREADTH_ITERATOR_