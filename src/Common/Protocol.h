#include "stdafx.h"
#include "Command.h"

#ifndef PROTOCOL_H
#define PROTOCOL_H

#define PROTOCOL_HEADER "cgi4lcd"
#define PROTOCOL_DELIMITER "|"
#define PROTOCOL_EXPECTED_SIZE 7

using namespace std;

class Protocol {

public:

    static Command parse(const string &data);
    static string build(const Command &cmd);

};

#endif // PROTOCOL_H
