#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <cstring>


using namespace std;

class A
{
public:
	int a;

	A()
	{
		a = 0;
		cout << "A Construct " << a << endl;
	}

	~A()
	{
		cout << "~A Destruct " << a << endl;
	}

};

class Str
{
public:
	char *buff;

	Str(): buff(new char[16])
	{
		cout << "Str Construct " << endl;
	}
	~Str()
	{
		cout << "Str Destruct " << endl;
	}

	Str(const Str &Other)
	{
		cout << "Str Copy Construct" << endl;
		buff = new char[16];
		memcpy(buff, Other.buff, 16);
	}

	Str(Str &&Other)
	{
		cout << "Str Move Construct" << endl;
		memcpy(buff, Other.buff, 16);
	}

	Str& operator =(const Str &Other)
	{
		cout << "Str Copy Equal" << endl;
		buff = new char[16];
		memcpy(buff, Other.buff, 16);
		return *this;
	}

	Str& operator =(Str &&Other)
	{
		cout << "Str Move Equal" << endl;
		memcpy(buff, Other.buff, 16);
		return *this;
	}
};

class B
{
public:
	Str bs;
	B(const Str& InStr) : bs(InStr)
	{
		cout << "B Copy Construct" << endl;
	}

	B(Str&& InStr) : bs(InStr)
	{
		cout << "B move construct" << endl;
	}
};



class A GetA()
{
	A x;
	return x;
}

class A& GetARef()
{
	A x;
	return x;
}

class Str GetStr()
{
	Str ss;
	return ss;
}

class Str& GetStrRef()
{
	Str ss;
	return ss;
}

int main()
{
	//const A& m = GetA();

	//const A& k = GetA();
	//A n = GetARef();

	Str s1 = GetStr();
	cout << "---" << endl;

	//Str s2 = GetStrRef();
	B b(s1);
    return 0;
}


