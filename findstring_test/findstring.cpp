#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;
void fix_REGX_format(std::string& str)
{
    std::size_t found = 0;

    while(std::string::npos != (found = str.find("\\\\", found)))
    {
        str.replace(found, 2, "\\");
        found+=1;
    }

    found = 0;
    while(std::string::npos != (found = str.find("\\\"", found)))
    {
        str.replace(found, 2, "\"");
        found+=1;
    }

}

int main()
{
    size_t found = 0;
    string s1 ("DLINK'300\\\\");

    cout <<"before: " <<  s1 << endl;

    fix_REGX_format(s1);

    cout <<"after: " <<  s1 << endl;


        return 0;
}
