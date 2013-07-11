#include "TCfunctions.h"

using namespace std;

bool Is_And(module* gate){
    return ((*gate).nodeType=="and")||((*gate).nodeType=="not"&&(*(*gate).Inputs[0]).nodeType=="nand")||
    ((*gate).nodeType=="buf");
}
bool Is_Or(module* gate){
    return ((*gate).nodeType=="or")||((*gate).nodeType=="not"&&(*(*gate).Inputs[0]).nodeType=="nor")||
    ((*gate).nodeType=="buf");
}
bool Is_Xor(module* gate){
    return ((*gate).nodeType=="xor")||((*gate).nodeType=="not"&&(*(*gate).Inputs[0]).nodeType=="xnor")||
    ((*gate).nodeType=="buf");
}
bool Is_Nand(module* gate){
    return ((*gate).nodeType=="nand")||((*gate).nodeType=="not"&&(*(*gate).Inputs[0]).nodeType=="and")||
    ((*gate).nodeType=="buf");
}
bool Is_Nor(module* gate){
    return ((*gate).nodeType=="nor")||((*gate).nodeType=="not"&&(*(*gate).Inputs[0]).nodeType=="or")||
    ((*gate).nodeType=="buf");
}
bool Is_Xnor(module* gate){
    return ((*gate).nodeType=="xnor")||((*gate).nodeType=="not"&&(*(*gate).Inputs[0]).nodeType=="xor")||
    ((*gate).nodeType=="buf");
}
int Calculate_Delay(vector<module*> modules){
    int total_cost=0;
    for(int i=0;i<(int)modules.size();++i){
        if((*modules[i]).isVirtual)
            continue;
        if((*modules[i]).nodeType=="not")
            (*modules[i]).value=1;
        else if((*modules[i]).nodeType=="buf")
            (*modules[i]).value=0;
        else if((*modules[i]).nodeType=="xor"||(*modules[i]).nodeType=="xnor")
            (*modules[i]).value=6;
        else
            (*modules[i]).value=((int)(*modules[i]).Inputs.size()-1)*2;
        total_cost+=(*modules[i]).value;
    }
    return total_cost;
}
void Setup_Candidate(vector<module*> modules){
    vector<module*> leaves;
    queue<module*> q;
    for(int i=0;i<(int)modules.size();++i){
        if((*modules[i]).isVirtual){
            (*modules[i]).visit=true;
            continue;
        }
        if((*modules[i]).Inputs.size()==0){
            (*modules[i]).visit=true;
            leaves.push_back(modules[i]);
            continue;
        }
        for(int j=0;j<(int)(*modules[i]).Inputs.size();++j){
            if((*(*modules[i]).Inputs[j]).isVirtual || (int)(*(*modules[i]).Inputs[j]).Outputs.size()>1){
                (*modules[i]).visit=true;
                if((*modules[i]).nodeType!="buf")
                    leaves.push_back(modules[i]);
                else{
                    if(!(*(*modules[i]).Outputs[0]).isVirtual){
                        (*(*modules[i]).Outputs[0]).visit=1;
                        leaves.push_back((*modules[i]).Outputs[0]);
                    }
                }
                break;
            }
        }
    }
    //build each tree
    for(int i=0;i<(int)leaves.size();++i){
        for(int j=0;j<(int)(*leaves[i]).Outputs.size();++j){
            if(!(*(*leaves[i]).Outputs[j]).visit){
                (*(*leaves[i]).Outputs[j]).visit=true;
                q.push((*leaves[i]).Outputs[j]);
                DP_Gates(leaves[i],(*leaves[i]).Outputs[j]);
            }
        }
    }
    while(q.size()!=0){
        for(int i=0;i<(int)(*q.front()).Outputs.size();++i){
            if(!(*(*q.front()).Outputs[i]).visit && !(*(*q.front()).Outputs[i]).isVirtual){
                (*(*q.front()).Outputs[i]).visit=true;
                q.push((*q.front()).Outputs[i]);
                DP_Gates(q.front(),(*q.front()).Outputs[i]);
            }
        }
    }
    return;
}
void DP_Gates(module* front_g,module* back_g){

    return;
}
