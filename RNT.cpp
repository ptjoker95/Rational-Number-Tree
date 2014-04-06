#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <math.h>
#include <limits.h>
using namespace std;

tuple<int, int>UpperStage( int p, int q )
{
	if( p > q )
		return make_tuple( p - q, q );
	if( p < q )
		return make_tuple( p, q - p );
	if( p == q )
		return make_tuple( p, q );
}

char WhichBranch( int left, int right )
{
	if ( left > right )
		return 'R';
	else
		return 'L';
}

int WhatLevel( unsigned long long int position )
{
	int level, MaxLevel = 64;

	for( int i=1; i < MaxLevel; i++ )
	{
		if( position <= pow( 2, i ) - 1 )
		{
			return i;
		}
	}
}

class NodeonRNT
{
	private:
		unsigned long long int Position, P, Q;
	public:
		void InputPnQ( long long int p, long long int q )
		{
			P = p;
			Q = q;
			Position = 0;
		}
		void InputPosition( long long int position )
		{
			Position = position;
		}
};

int main( int argc, char** argv )
{
	int CaseNum, WhichCase;
	unsigned long long int Position, P, Q;
	//NodeonRNT	*nodes;

	ifstream myfile;

	cout << "Position: " << Position << endl;

	myfile.open( argv[1] );

	if( myfile.is_open() )
	{
		myfile >> CaseNum;	
		//nodes = new NodeonRNT[ CaseNum ];

		for( int i=0; i<CaseNum; i++ )
		{
			myfile >> WhichCase;
			
			if( WhichCase == 1 )
			{
				myfile >> Position;
				//nodes[i].InputPosition( Position );
				cout << "This Position's Level is: " << WhatLevel( Position ) << endl;
			}
			if( WhichCase == 2 )
			{
				myfile >> P >> Q;
				//nodes[i].InputPnQ( P, Q );
			}

			if( WhichCase == 1 )
			{
				cout << "This case is find P and Q by" << Position << endl;
			}
			if( WhichCase == 2 )
			{
				//cout << "This case is find Position by P: " << P << ", Q: " << Q << endl;
				int upper_p, upper_q;
				tie ( upper_p, upper_q ) = UpperStage( P, Q );
				
				cout << "Upper Case is " << upper_p << ", " << upper_q << endl;
			}
		}
	}

	//delete[] nodes;
	myfile.close();
}
