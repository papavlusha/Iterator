#include "List.h"
#include <iostream>
#include <time.h>
#include <windows.h>
#include <vector>

using namespace std;

bool func(int a) {
	return a <= 2;
}
unsigned counting(ListIterator* li) {
	unsigned cnt = 0;
	cout << "{ ";
	if (li->operator()()) {
		do {
			cnt++;
			cerr << li->operator *() << " ";
		} while (li->operator++());
	}
	cout << "}";
		cerr << endl << "amount:";
		return cnt;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand((unsigned)time(0));
	unsigned capacity, count;
	cout <<"Введите объем стека:";
	cin >> capacity;

	try {
		List list(capacity);
	}
	catch (std::exception t) {
		cerr << t.what();
		return 3;
	}
	List list(capacity);
	cout << "Введите кол-во элементов:";
	cin >> count;
	cout << "Введите шаг для итератора step:";
	int step;
	cin >> step;
	cout << "\nЗначение , которое будет использоваться для итератора VALUE = 4;\n";
	cout << "элементы стека:";
	for (unsigned i = 0; i < count; i++) {
		int x = rand() % 5;
		if (list.append(x))
			cout << x << " ";
	}
	cout << endl;
	ListIterator* litS3;
	try {
		 litS3 = list.createIterator(Iterators::STEP,step);
	}
	catch (exception t) {
		cerr << t.what();
		return 3;
	}
	ListIterator* litV4 = list.createIterator(Iterators::VALUE, 4);
	ListIterator* litPred = list.createIterator(Iterators::PREDICATE,func);
	cout << "Элементы удовлетворяющие 1-му итератору ";
	cout << counting((ListIteratorStep*)litS3)  << endl;
	cout << "Элементы удовлетворяющие 2-му итератору ";
	cout << counting((ListIteratorValue*)litV4)  << endl;
	cout << "Элементы удовлетворяющие 3-му итератору ";
	cout << counting((ListIteratorPredicate*)litPred) << endl;
}

