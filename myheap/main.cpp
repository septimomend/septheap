// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "myheap.h"

using namespace septmem;

int main()
{
	// my_malloc test
	//
	cout << "my_malloc() test" << endl;
	long long* d = (long long*)my_malloc(sizeof(long long) * 6);
	cout << "First byte address of block allocated by my_malloc: " << d << endl;

	// my_realloc test
	//
	cout << "\nmy_realloc() test" << endl;
	int* c = (int*)my_malloc(sizeof(int) * 8);

	c[0] = 9;
	c[1] = 5;
	c[2] = 3;
	c[3] = 4;
	c[4] = 6;
	c[5] = 2;
	c[6] = 4;
	c[7] = 8;


	for (int i = 0; i < 10; ++i)
		cout << " " << c[i];
	cout << endl;

	c = (int*)my_realloc(c, sizeof(int)*2);

	for (int i = 0; i < 10; ++i)
		cout << " " << c[i];
	cout << endl;


	// my_free test
	//
	cout << "\nmy_free() test" << endl;
	my_free(d);	// ok
	my_free(c);	// ok
	my_free(d);	// already freed
	int v[12];
	my_free(v);	// didn't allocate by malloc or realloc

	// my_memcpy test
	//
	cout << "\nmy_memcpy() test" << endl;
	int a[5], b[10];

	for (int i = 0; i < 5; ++i)
		a[i] = 5;

	for (int i = 0; i < 5; ++i)
		cout << " " << a[i];
	cout << endl;

	my_memcpy(b, a, sizeof(a));

	for (int i = 0; i < sizeof(b)/sizeof(b[0]); ++i)
		cout << " " << b[i];
	cout << endl;

	// my_memmove test
	//
	cout << "\nmy_memmove() test" << endl;
	int* f = (int*)my_malloc(sizeof(int)*10);
	int* e = (int*)my_malloc(sizeof(int)*5);

	for (int i = 0; i < 10; ++i)
		f[i] = 5;

	for (int i = 0; i < 10; ++i)
		cout << " " << f[i];
	cout << endl;

	my_memmove(e, f, sizeof(int)*5);

	for (int i = 0; i < 5; ++i)
		cout << " " << e[i];
	cout << endl;

	// my_memset test
	//
	cout << "\nmy_memset() test" << endl;
	my_memset(f, 2, 5);
	for (int i = 0; i < 10; ++i)
		cout << " " << f[i];
	cout << endl;

	///////////////
	my_free(f);
	my_free(e);

	return 0;
}

