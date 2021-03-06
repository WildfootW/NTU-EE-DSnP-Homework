/****************************************************************************
  FileName     [ cirMgr.h ]
  PackageName  [ cir ]
  Synopsis     [ Define circuit manager ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2008-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef CIR_MGR_H
#define CIR_MGR_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#include "cirDef.h"

extern CirMgr *cirMgr;

class CirMgr
{
public:
    CirMgr();
    ~CirMgr();

    string comments;

    // Access functions
    // return '0' if "gid" corresponds to an undefined gate.
    CirGate* getGate(unsigned gid) const;

    // for CIRRead
    bool readCircuit(const string&);

    // for CIRWrite
    void writeAag(ostream&) const;

    // for CIRPrint
    void printSummary() const;
    void printNetlist() const;
    void printPIs() const;
    void printPOs() const;
    void printFloatGates() const;

    // about optimization
    void sweep();
    void optimize();

    // about simulation
    void randomSim();
    void fileSim(ifstream&);
    void setSimLog(ofstream *logFile) { _simLog = logFile; }

    // about fraig
    void strash();
    void printFEC() const;
    void fraig();

    void printFECPairs() const;
    void writeGate(ostream&, CirGate*) const;

private:
    GateList _gate_list;
    unsigned int _header_M;
    unsigned int _header_I;
    unsigned int _header_L;
    unsigned int _header_O;
    unsigned int _header_A;

    IdList _pi_list;
    IdList _po_list;
    //IdList _latch_list;

    ofstream* _simLog;

    // Help function for readCircuit()
    bool read_symbol_parser(string input, CirGate*& target, string& symbolic_name) const;
    bool read_interger_parser(string input, vector<int>& tokens, unsigned int number_num) const;
    bool read_header_parser(const string& input, vector<int>& tokens) const;
    bool read_gate_parser(const string& input, vector<int>& tokens, GateType type) const;
    void read_set_header(const vector<int>& tokens);
    void read_set_gate(const vector<int>& tokens, GateType type, unsigned int lno);
    void read_init_add_gate(GateType type, unsigned int lno, const vector<int>& tokens);

    // static function
    static inline unsigned int literal_to_variable(int literal_id, bool& inverted);
    static inline unsigned int literal_to_variable(int literal_id);
};

#endif // CIR_MGR_H
