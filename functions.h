#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <iostream>
#include <sys/time.h>
#include <iomanip>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <functional>
#include <map>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <cmath>

std::string inttostr(int i);
int strtoint(std::string str);
void strerase(std::string &mainstr, std::string cutdstr);
std::string strcut(std::string mainstr, std::string cutdstr);


#endif /* _FUNCTIONS_H_ */
