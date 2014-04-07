#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <math.h>
#include <limits.h>
using namespace std;

class NodeonRNT
{
	private:
		unsigned long long int Position, P, Q;

		//Level은 tree의 레벨이 몇번째 인지 저장하는 변수. ith는 그 레벨에서 왼쪽에서 몇번째인지 저장하는 변수
		int Level;

		vector<unsigned long long int> Positions;
		vector<unsigned long long int> NodeDepths;
		vector<char> NodesSide;

		unsigned long long int UpperLevelPosition( unsigned long long int position )
		{
			return ceil( position / 2 );
		}
		//상위 노드의 P,Q값을 넣고, 오른쪽 가지인지 왼쪽 가지인지 알려주면 다음 P,Q 값을 리턴하는 함수
		tuple<unsigned long long int, unsigned long long int>LowerPQ( unsigned long long int P, unsigned long long int Q, char side )
		{
			if( side == 'L' )
				return make_tuple( P, P+Q );
			if( side == 'R' )
				return make_tuple( P+Q, Q );
		}

		//위의 노드의 position으로 나눈 값이 2이면 왼쪽, 2가 아니면 오른쪽
		char LeftorRight( unsigned long long int uppernodedepth, unsigned long long int node )
		{
			if( node % uppernodedepth == 0 )
				return 'L';
			else
				return 'R';
		}

		//임의의 노드의 깊이를 받으면, 상위 노드의 깊이를 계산해주는 함수
		unsigned long long int UpperNodeDepth( unsigned long long int depth )
		{
			//위의 노드의 깊이가 i라고 하면, 그 다음 노드의 깊이는 2i-1이거나, 2i이다. 따라서 상위방향은 2로 나누어주면 됨.
			if( depth % 2 == 0 )
				return depth / 2;
			else
				return (depth+1) / 2;
		}

		//왼쪽 숫자가 크면, 바로 위 노드의 오른쪽으로 분할된 노드일 것이고, 오른쪽 숫자가 크면, 바로 위 노드의 왼쪽으로 분할된 노드일 것
		char WhichBranch( unsigned long long int left, unsigned long long int right )
		{
			if ( left > right )
				return 'R';
			else
				return 'L';
		}

		//바로 위의 노드를 찾아내는 함수. tie ( upper_p, upper_q )와 같은 방식으로 값을 리턴한다.
		tuple<int, int>UpperStage( int p, int q )
		{
			if( p > q )
				return make_tuple( p - q, q );
			if( p < q )
				return make_tuple( p, q - p );
			if( p == q )
				return make_tuple( p, q );
		}

		//position을 받아서, 그 레벨에서 몇번째 자리인지 리턴하는 함수. 그 레벨에 해당하는 지 확인하는 게 좋겠지.
		unsigned long long int Depth( int level, unsigned long long int position  )
		{
			return position - pow( 2, level - 1 ) + 1;
		}

		//position을 넣으면 몇번째 레벨에 해당하는 지 리턴
		int WhatLevel( unsigned long long int position )
		{
			int MaxLevel = 64;

			for( int i=1; i < MaxLevel+1; i++ )
			{
				if( position < pow( 2, i ) )
				{
					return i;
				}
			}

			return 0;
		}

	public:
		void InputPnQ( unsigned long long int p, unsigned long long int q )
		{
			P = p;
			Q = q;
			Position = 0;
		}

		//Position을 받으면 해당 노드가 몇번째 레벨의 몇번째 자리에 위치해했는지 계산한다.
		void InputPosition( unsigned long long int position )
		{
			Position = position;
			cout << "Position: " << Position << " ";
			Level = this->WhatLevel( Position );
			cout << "Level: " << Level << endl;

			Positions.push_back( position );
			for( int i=0; Positions[i] > 1; i++ )
			{
				Positions.push_back( UpperLevelPosition( Positions[i] ) );
			}

			int temp = Positions.size();

			for( int i=0; i<temp-1; i++)
			{
				NodesSide.push_back( this->LeftorRight( Positions[i+1], Positions[i] )  );
				cout << i << "th position: " << Positions[i] << "'s side is " << NodesSide[i] << endl;
			}
		}
};

int main( int argc, char** argv )
{
	int CaseNum, WhichCase;
	unsigned long long int Position, P, Q;
	NodeonRNT	nodes;

	ifstream myfile;

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
				nodes.InputPosition( Position );
			}
			if( WhichCase == 2 )
			{
				myfile >> P >> Q;
				//nodes[i].InputPnQ( P, Q );
			}

			if( WhichCase == 1 )
			{
				//cout << "This case is find P and Q by " << Position << endl;
			}
			if( WhichCase == 2 )
			{
				//cout << "This case is find Position by P: " << P << ", Q: " << Q << endl;
				//int upper_p, upper_q;

				//cout << "Upper Case is " << upper_p << ", " << upper_q << endl;
			}
		}
	}

	//delete[] nodes;
	myfile.close();
}
