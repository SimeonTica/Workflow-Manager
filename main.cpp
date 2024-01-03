#include <iostream>
#include "flow.hpp"

int main(){

    Flow *flow = new Flow();

    flow->execute();

    free(flow);
    return 0;
}