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

		//하위 노드의 position을 리턴하는 함수, 받은 노드에서 왼쪽이면 *2, 오른쪽이면 *2 + 1
		unsigned long long int LowerLevelPosition( unsigned long long int upperlevelposition, char side )
		{
			if( side == 'L' )
				return upperlevelposition * (unsigned long long int)2;
			if( side == 'R' )
				return upperlevelposition * (unsigned long long int)2 + (unsigned long long int)1;
		}

		//상위 노드의 position을 리턴하는 함수
		unsigned long long int UpperLevelPosition( unsigned long long int position )
		{
			return floor( position / (unsigned long long int)2 );
		}

		//상위 노드의 P,Q값을 넣고, 오른쪽 가지인지 왼쪽 가지인지 알려주면 다음 P,Q 값을 리턴하는 함수
		tuple<unsigned long long int, unsigned long long int>LowerPQ( unsigned long long int P, unsigned long long int Q, char side )
		{
			if( side == 'L' )
				return make_tuple( (unsigned long long int)P, (unsigned long long int)(P+Q) );
			if( side == 'R' )
				return make_tuple( (unsigned long long int)(P+Q), (unsigned long long int)Q );
		}

		//아래 노드를 2로 나눈 값이 위의 노드와 같으면 left, 다르면 R
		char LeftorRight( unsigned long long int uppernode, unsigned long long int lowernode )
		{
			if( uppernode * (unsigned long long int)2 != lowernode )
				return 'R';
			else
				return 'L';
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

		//P와 Q를 받으면, 위의 노드에서 어느 쪽으로 파생된 것인지 알려주고, 위의 노드의 P와 Q값을 리턴
		tuple<unsigned long long int, unsigned long long int, char>UpperStage( unsigned long long int p, unsigned long long int q )
		{
			if( p == 1 && q == 1 )
				return make_tuple( (unsigned long long int)1, (unsigned long long int)1, 'S' );
			if( p > q )
				return make_tuple( p - q, q, 'R' );
			if( p < q )
				return make_tuple( p, q - p, 'L' );
			if( p == q )
				return make_tuple( p, q, 's' );
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
		void OutputPosition()
		{
			cout << this->Position << endl;
		}

		void OutputPnQ()
		{
			cout << this->P << " " << this->Q << endl;
		}

		void InputPnQ( unsigned long long int p, unsigned long long int q )
		{
			this->P = p;
			this->Q = q;
			this->Position = (unsigned long long int)1;

			unsigned long long int tempP, tempQ;
			char side;

			tempP = p;
			tempQ = q;

			while( tempP > (unsigned long long int)1 || tempQ > (unsigned long long int)1)
			{
				tie( tempP, tempQ, side ) = this->UpperStage( tempP, tempQ );
				this->NodesSide.push_back( side );
			}

			int temp = this->NodesSide.size();

			for( int i=0; i<temp; i++ )
			{
				this->Position = this->LowerLevelPosition( this->Position, this->NodesSide[temp-1-i] );
			}
		}

		//Position을 받으면 해당 노드가 몇번째 레벨의 몇번째 자리에 위치해했는지 계산한다.
		void InputPosition( unsigned long long int position )
		{
			this->Position = position;
			this->Level = this->WhatLevel( Position );
			//cout << "Level: " << Level << endl;

			Positions.push_back( position );
			for( int i=0; Positions[i] > 1; i++ )
			{
				Positions.push_back( UpperLevelPosition( Positions[i] ) );
			}

			int temp = Positions.size();
			for( int i=0; i<temp-1; i++)
			{
				NodesSide.push_back( this->LeftorRight( Positions[i+1], Positions[i] )  );
			}

			P = (unsigned long long int)1;
			Q = (unsigned long long int)1;

			temp = NodesSide.size();
			for( int i = 0; i<temp; i++ )
			{
				tie( P, Q ) = this->LowerPQ( P, Q, NodesSide[temp - 1 - i]);
			}
		}
};

int main( int argc, char** argv )
{
	int CaseNum, WhichCase;
	unsigned long long int Position, P, Q;
	NodeonRNT	*nodes;

	ifstream myfile;

	myfile.open( argv[1] );

	if( myfile.is_open() )
	{
		myfile >> CaseNum;	
		nodes = new NodeonRNT[ CaseNum ];

		for( int i=0; i<CaseNum; i++ )
		{
			myfile >> WhichCase;
			
			if( WhichCase == 1 )
			{
				myfile >> Position;
				nodes[i].InputPosition( Position );
				cout << "Case #" << i+1 << ": ";
				nodes[i].OutputPnQ();
			}
			if( WhichCase == 2 )
			{
				myfile >> P >> Q;
				nodes[i].InputPnQ( P, Q );
				cout << "Case #" << i+1 << ": ";
				nodes[i].OutputPosition();
			}
		}
	}

	delete[] nodes;
	myfile.close();
}
