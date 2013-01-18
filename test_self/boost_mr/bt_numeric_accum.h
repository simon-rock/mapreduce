// numeric_accum.cpp
// compile with: /EHsc
#include <vector>
#include <numeric>
#include <functional>
#include <iostream>

int test_numeric_accum( ) 
{
	using namespace std;

	vector <int> v1, v2( 20 );
	vector <int>::iterator Iter1, Iter2;

	int i;
	for ( i = 1 ; i < 21 ; i++ )
	{
		v1.push_back( i );
	}

	cout << "The original vector v1 is:\n ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")." << endl;

	// The first member function for the accumulated sum
	int total;
	total = accumulate ( v1.begin ( ) , v1.end ( ) , 0 );

	cout << "The sum of the integers from 1 to 20 is: " 
		<< total << "." << endl;

	// Constructing a vector of partial sums
	int j = 0, partotal;
	for ( Iter1 = v1.begin( ) + 1; Iter1 != v1.end( ) ; Iter1++ )
	{
		partotal = accumulate ( v1.begin ( ) , Iter1 , 0 );
		v2 [ j ] = partotal;
		j++;
	}
	/* // msvc error , gcc ok
	for ( Iter1 = v1.begin( ) + 1; Iter1 != v1.end( ) + 1 ; Iter1++ )
	{
		partotal = accumulate ( v1.begin ( ) , Iter1 , 0 );
		v2 [ j ] = partotal;
		j++;
	}
*/
	cout << "The vector of partial sums is:\n ( " ;
	for ( Iter2 = v2.begin( ) ; Iter2 != v2.end( ) ; Iter2++ )
		cout << *Iter2 << " ";
	cout << ")." << endl << endl;

	// The second member function for the accumulated product
	vector <int> v3, v4( 10 );
	vector <int>::iterator Iter3, Iter4;

	int s;
	for ( s = 1 ; s < 11 ; s++ )
	{
		v3.push_back( s );
	}

	cout << "The original vector v3 is:\n ( " ;
	for ( Iter3 = v3.begin( ) ; Iter3 != v3.end( ) ; Iter3++ )
		cout << *Iter3 << " ";
	cout << ")." << endl;

	int ptotal;
	ptotal = accumulate ( v3.begin ( ) , v3.end ( ) , 1 , multiplies<int>( ) );

	cout << "The product of the integers from 1 to 10 is: " 
		<< ptotal << "." << endl;

	// Constructing a vector of partial products
	int k = 0, ppartotal;
	for ( Iter3 = v3.begin( ) + 1; Iter3 != v3.end( ) ; Iter3++ ) {
		ppartotal = accumulate ( v3.begin ( ) , Iter3 , 1 , multiplies<int>( ) );    // Çó»ý
		v4 [ k ] = ppartotal;
		k++;
	}
	/*
	for ( Iter3 = v3.begin( ) + 1; Iter3 != v3.end( ) + 1 ; Iter3++ ) {
		ppartotal = accumulate ( v3.begin ( ) , Iter3 , 1 , multiplies<int>( ) );
		v4 [ k ] = ppartotal;
		k++;
	}
	*/

	cout << "The vector of partial products is:\n ( " ;
	for ( Iter4 = v4.begin( ) ; Iter4 != v4.end( ) ; Iter4++ )
		cout << *Iter4 << " ";
	cout << ")." << endl;

	return 0;
}