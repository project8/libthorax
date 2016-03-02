/*
 * thorax_cpp_test.cc
 *
 *  Created on: Oct 30, 2013
 *      Author: nsoblath
 */


#include "thorax_time.hh"

#include <iostream>

using namespace std;
using namespace thorax;

int main()
{
    cout << "The current time is (UTC): " << get_absolute_time_string() << endl;

    return 0;
}
