/**
 *
 * Module:
 *  helloworldinc
 *
 * Description:
 *  Hello World but in C + a little extra
*/

// No iostream in C of course...
#include <stdio.h>

/* And we have no classes either so we can use a struct
class MyClass
{
public:
	MyClass();
	~MyClass();

private:

};
*/

// But unlike C++, C structs do not have functions in them.
struct Arguments
{
	int Count;
	char** ppArgs;
};

// In c++ I'd do something like this.
// static void PrintArgs( const Arguments& rArguments )
// But, in C references do not exist so we do this instead
static void PrintArgs( const struct Arguments* pArguments )
{
	for( int i = 0; i < pArguments->Count; ++i )
	{
		printf( "%s", pArguments->ppArgs[ i ] );
	}
}

int main( int count, char** ppArgs ) 
{
	struct Arguments arguments;
	memset( &arguments, 0, sizeof( struct Arguments ) );

	arguments.Count = count;
	// We'll just point to the same address, no need to copy for this.
	arguments.ppArgs = ppArgs;

	PrintArgs( &arguments );

	printf( "Hello World\n" );
}
