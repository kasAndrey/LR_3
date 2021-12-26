#ifndef _MY_ITERATOR_ 

#define _MY_ITERATOR_

class Iterator
{
public:
	virtual void next() = 0;
	virtual bool has_next() const = 0;
	virtual int get_value() const = 0;
};

#endif // ! _MY_ITERATOR_