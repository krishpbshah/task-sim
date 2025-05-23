#include "myheader.hpp"
#include <iostream>
using namespace std;

int main()
{
    CPU core;
    std::string cmd;
    int N, P_ID, C_ID;

    while (std::cin >> cmd)
    {
        if (cmd == "ON")
        {
            std::cin >> N;
            core.ON(N);
        }
        else if (cmd == "SPAWN")
        {
            std::cin >> P_ID;
            core.SPAWN(P_ID);
        }
        else if (cmd == "RUN")
        {
            std::cin >> C_ID;
            core.RUN(C_ID);
        }
        else if (cmd == "SLEEP")
        {
            std::cin >> C_ID;
            core.SLEEP(C_ID);
        }
        else if (cmd == "SHUTDOWN")
        {

            core.SHUTDOWN();
        }
        else if (cmd == "SIZE")
        {
            std::cin >> C_ID;
            core.SIZE(C_ID);
        }
        else if (cmd == "CAPACITY")
        {
            std::cin >> C_ID;
            core.CAPACITY(C_ID);
        }
        else if (cmd == "EXIT")
        {
            break;
        }
    }
}