#include <stdlib.h>
#include <string.h>

class N {

public:
	N(int n);

	char	*setAnnotation(char * str);

	virtual int	operator+(N &o);
	virtual int	operator-(N &o);

private:
	char	_str[100];
	int	_n;

};

N::N(int n) : _n(n) {
	// the object has a vptr embedded in it. it is saved in its first 4 bytes
	// this->vptr = &N::operator+; -> this is done by the compiler
	// &N::operator+ = 0x08048848 = vtable for N + 8
	// _n = n;
}

char	*N::setAnnotation(char * str) {
	return ((char *)memcpy(_str, str, strlen(str)));
}

int	N::operator+(N &o) {
	return (_n + o._n);
}

int	N::operator-(N &o) {
	return (_n - o._n);
}

int main(int argc, char **argv)
{
	if (argc <= 1)
		exit(1);
	N *n1 = new N(5);
	N *n2 = new N(6);
	n1->setAnnotation(argv[1]);
	return (*n2 + *n1);
}
