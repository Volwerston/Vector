#include <iostream>
#include <string>

#include "Vector.h"

using namespace std;

typedef Vector<string>::Iterator Iterator;

Vector<string> getVector()
{
	Vector<string> a;

	a.push_back("AC");
	a.push_back("CDA");
	a.push_back("AA");

	return a;
}

bool memoryLeak()
{
	_CrtMemState c1, c2, c3;

	_CrtMemCheckpoint(&c1);

	{
		Vector<int> a;

		a.push_back(1);
		a.push_back(2);
		a.push_back(3);

	}

	_CrtMemCheckpoint(&c2);

	return !_CrtMemDifference(&c3, &c1, &c2);
}

int main()
{
	if (!memoryLeak())
	{
		cout << "Memory leak failed" << endl;
	}
	else
	{
		cout << "Everything's OK:)" << endl;
	}

	Vector<string> vec;

	vec.push_back("DAVAY");
	vec.push_back("BEZ");
	vec.push_back("OBID");

	Vector<string> v({ "A", "B", "C", "D", "E" });

	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << endl;
	}

	string a = "FOO";
	string _v = "GSS";
	string s = "HAA";

	v = { a, _v, s };

	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << endl;
	}

	Vector<string> newOne;
	newOne = getVector();

	for (size_t i = 0; i < newOne.size(); ++i)
	{
		cout << newOne[i] << " ";
	}
	cout << endl;

	for (Iterator a = newOne.begin(); a != newOne.end(); ++a)
	{
		cout << "I " << *a << endl;
	}

	for (Iterator a = newOne.begin(); a != newOne.end(); ++a)
	{
		cout << "I " << *a << endl;
	}

	Iterator k = newOne.begin();
	++k;

	*k = "X";

	for (Iterator a = newOne.begin(); a != newOne.end(); ++a)
	{
		cout << "I " << *a << endl;
	}

	--k;
	*k = "Y";

	for (Iterator a = newOne.begin(); a != newOne.end(); ++a)
	{
		cout << "I " << *a << endl;
	}

	Iterator b = k;

	*b = "Z";

	for (Iterator a = newOne.begin(); a != newOne.end(); ++a)
	{
		cout << "I " << *a << endl;
	}

	Iterator t;

	t = b;

	++t;
	++t;

	*t = "O";


	for (Iterator a = newOne.begin(); a != newOne.end(); ++a)
	{
		cout << "I " << *a << endl;
	}

	string d = *t;

	cout << d << endl;

	system("pause");
	return 0;
}