
#pragma once

#include <vector>
#include <exception>
#include <iostream>
#include <list>

using namespace std;

class ListIterator;

enum class Iterators {
	STEP,
	VALUE,
	PREDICATE
};//++

class List
{
public:
	 list <int> vec;
	 list <int>::iterator back;
public:
	friend class ListIterator;
	ListIterator* createIterator(Iterators its, bool(*func)(int)) const;
	List(size_t aSize) {
		vec.resize(aSize);
		back = vec.begin();
	}

	virtual ~List() { }

	bool append(int a) {
		if (back == vec.end())
			return false;
		vec.emplace(back, a);
		back++;
		if (back == vec.end())
			return true;
		auto del = back;
		del++;
		vec.erase(back);
		back = --del;
		return true;
	}
		bool remove() {
		if (back == vec.begin())
			return false;
		list <int>::iterator it;
		it = back;
		it--;
		vec.erase(it);
		vec.resize(vec.size() + 1);
		return true;
	}

	ListIterator* createIterator(Iterators its, const int aStep) const;
	
};


class ListIterator {
protected:
	friend class List;
	const List* pList;
	list<int>::iterator place;
	virtual bool first() = 0;
    virtual bool next() = 0;
	virtual int currentItem()
	{
		return *(place);
	}
public:
	ListIterator(const List* aPList) : pList(aPList), place(pList->back)
	{
		if (pList->vec.size() == 0) {
			throw std::exception("It is empty!!!");
		}
		place--;
		/*if (pList->back == pList->vec.end())
			place--;*/
	}
	bool operator++()
	{
		return next();
	}
	int operator*()
	{
		return currentItem();
	}
	bool operator()()
	{
		return first();
	}
};

class ListIteratorStep : public ListIterator
{
private:
	int step;
public:
	friend class List;
	ListIteratorStep(const List* aPList, int aStep = 1) : ListIterator(aPList) {
		if (aStep < 0) {
			throw std::exception("invalid step!!!");
		}
		step = aStep - 1;
	}

	bool first() override {//changed
		place = pList->back;
		place--;
		//cout << *place << ' ';
		if (pList->back == pList->vec.end())
			place--;
		//cout << *place << ' ';
		auto i = 1;
		while (i <= step)
		{
			i++;
			if (place == pList->vec.begin())
				return false;
			place--;
			//cout << *place << ' ';
		}
		return true;
	}

	bool next() override//+
	{
		if (place == pList->vec.begin())
			return false;
		place--;
		auto i = 0;
		while (i < step)
		{
			i++;
			if (place == pList->vec.begin())
				return false;
			place--;
		}
		return true;
	}

};

class ListIteratorPredicate : public ListIterator
{
private:
  bool (*predicate)(int);
public:
  ListIteratorPredicate(const List* aPList, bool aPredicate(int)) : ListIterator(aPList) {
    predicate = aPredicate;
  }
  bool first() override//changed
  {
	  place = pList->back;
	  place--;
	  if (pList->back == pList->vec.end())
		  place--;
	  while (!predicate(*place))
	  {
		  if (place == pList->vec.begin())
			  return false;
		  place--;
	  }
	  return true;
  }
  bool next() override//+
  {
	  if (place == pList->vec.begin())
		  return false;
	  place--;
	  while (!predicate(*place))
	  {
		  if (place == pList->vec.begin())
			  return false;
		  place--;
	  }
	  return true;
  }
};

class ListIteratorValue : public ListIterator
{
private:
	int value;
	bool first() override//changed
	{
		place = pList->back;
		place--;
		if (pList->back == pList->vec.end())
			place--;
		while (*place != value)
		{
			if (place == pList->vec.begin())
				return false;
			place--;
		}
		return true;
	}
	bool next() override//+
	{
		if (place == pList->vec.begin())
			return false;
		place--;
		while (*place != value)
		{
			if (place == pList->vec.begin())
				return false;
			place--;
		}
		return true;
	}
public:
	ListIteratorValue(const List* aPList, int aValue) : ListIterator(aPList)
	{
		value = aValue;
	}
};



