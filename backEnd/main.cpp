

#include "Block.h"
	#include "Input.h"
	#include "Gate.h"
#include "Wire.h"

using namespace std;


int main()
{
	////////////////////////////////
    	// user changes the following 2:	
    	Input inputA(1);			
    	Input inputB(1);			
	////////////////////////////////

	Gate and_gate(0);
	Gate or_gate(1);

	Wire from_A0(&inputA);
	Wire from_A1(&inputA);
	Wire from_B0(&inputB);
	Wire from_B1(&inputB);

	and_gate.setIn0(&from_A0);
	and_gate.setIn1(&from_B0);

	or_gate.setIn0(&from_A1);
	or_gate.setIn1(&from_B1);

	Wire from_or(&or_gate);

	Wire from_and(&and_gate);

	// evaluate
	cout << "AND=" << from_and.getValue() << endl;
	cout << "OR=" << from_or.getValue() << endl;

	return 0;
}
