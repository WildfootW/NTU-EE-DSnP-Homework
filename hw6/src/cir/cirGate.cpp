/****************************************************************************
  FileName     [ cirGate.cpp ]
  PackageName  [ cir ]
  Synopsis     [ Define class CirAigGate member functions ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2008-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdarg.h>
#include <cassert>
#include "cirGate.h"
#include "cirMgr.h"
#include "util.h"

using namespace std;

extern CirMgr *cirMgr;

unsigned int CirGate::visited_ref = 0;
/**************************************/
/*   class CirGate member functions   */
/**************************************/
void
CirGate::print_net_dfs(unsigned int& print_line_no) const
{
    if(is_visited())
        return;
    set_visited();

    for(const related_gate& e:_i_gate_list)
    {
        e.get_gate()->print_net_dfs(print_line_no);
    }
    print_net(print_line_no);
}
void
CirGate::reportGate() const
{
    stringstream ss;
    ss << getTypeStr() << "(" << getId() << ")";
    if(!symbolic_name.empty())
        ss << "\"" << symbolic_name << "\"";
    ss << ", line " << getLineNo();

    unsigned int times = ss.str().size() + 4;
    times = max(times, (unsigned int)50);

    cout << string(times, '=') << endl;
    cout << "= "  << left << setw(times - 4) << ss.str() << " =" << endl;
    cout << string(times, '=') << endl;
}

void
CirGate::reportFanin(int level) const
{
   assert (level >= 0);
}

void
CirGate::reportFanout(int level) const
{
   assert (level >= 0);
}

void
CirGate::update_inputs_output_list(const related_gate& myself) const
{
    for(const related_gate& e:_i_gate_list)
    {
        //if(e.get_gate()->gate_type() == UNDEF_GATE)
        //    continue;
        e.get_gate()->add_output_gate(myself);
    }
}

//void
//CirGate::set_floating()
//{
//    floating = true;
//    for(related_gate& e:_o_gate_list)
//    {
//        if(e.get_gate()->is_floating() == false)
//            e.get_gate()->set_floating();
//    }
//}
bool
CirGate::have_floating_fanin() const
{
    for(const related_gate& e:_i_gate_list)
    {
        if(e.get_gate()->is_floating())
            return true;
    }
    return false;
}

