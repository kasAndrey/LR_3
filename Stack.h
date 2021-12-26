#ifndef _MY_STACK_

#define _MY_STACK_

#include <stdexcept>
using namespace std;
template <typename T>
class Stack
{
private:
	struct element;
public:
	Stack();
	Stack(const Stack& other);
	~Stack();

	Stack& operator=(const Stack& other);

	T pop();
	T top() const;
	void push(T value);
	bool is_empty() const;
private:
	element* _top;

	void _copy(const Stack& other);
	void _clear();
};

template <typename T>
struct Stack<T>::element {
	T value;
	element* next;
};
template <typename T>
Stack<T>::Stack() :_top(nullptr) {

}

template <typename T>
Stack<T>::Stack(const Stack& other) {
	if (other._top == nullptr)
		_top = nullptr;
	else
		_copy(other._top);
}

template <typename T>
void Stack<T>::_copy(const Stack& other) {
	_top = new element{ other._top->value, nullptr };

	element* last_added = _top;
	element* temp = other._top->next;

	while (temp != nullptr) {
		last_added->next = new element{ temp->value, nullptr };

		last_added = last_added->next;
		temp = temp->next;
	}
}

template <typename T>
Stack<T>::~Stack() {
	_clear();
}

template <typename T>
void Stack<T>::_clear() {
	while (_top != nullptr) {
		element* removing = _top;

		_top = _top->next;

		delete removing;
	}
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
	if (this != &other) {
		_clear();
		_copy(other);
	}

	return *this;
}

template <typename T>
T Stack<T>::pop() {
	if (_top == nullptr)
		throw ::runtime_error("Stack is empty.");

	T popping_value = _top->value;

	element* removing = _top;

	_top = _top->next;

	delete removing;

	return popping_value;
}

template <typename T>
T Stack<T>::top() const {
	if (_top == nullptr)
		throw ::runtime_error("Stack is empty.");

	return _top->value;
}

template <typename T>
void Stack<T>::push(T value) {
	_top = new element{ value, _top };
}

template <typename T>
bool Stack<T>::is_empty() const {
	return _top == nullptr;
}

#endif //! _MY_STACK_