#include <cstdlib>
#include <cstring>

class N {

public:
	N(int n);

	char	*setAnnotation(char * str);

	int	operator+(N &o);
	int	operator-(N &o);

private:
	char	_str[100];
	int	_n;

};

N::N(int n) : _n(n) {}

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
	return (*n1 + *n2);
}
