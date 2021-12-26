#ifndef  _MY_NODE_

#define _MY_NODE_

struct node {
	node(int value);
	int value;
	node* left;
	node* right;
};

node::node(int value)
	: value(value), left(nullptr), right(nullptr) {

}
#endif // !_MY_NODE_