#ifndef _TCFUNCTION_H_
#define _TCFUNCTION_H_

#include <vector>
#include <queue>
#include "module_net.h"

bool Is_And(module* gate);
bool Is_Or(module* gate);
bool Is_Xor(module* gate);
bool Is_Nand(module* gate);
bool Is_Nor(module* gate);
bool Is_Xnor(module* gate);
int Calculate_Delay(vector<module*> modules);
void Setup_Candidate(vector<module*> modules);
void DP_Gates(module* front_g,module* back_g);

#endif /* _TCFUNCTION_H_ */
