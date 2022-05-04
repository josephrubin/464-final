#include <iostream>
#include <vector>
#include "rtos.h"
#include "md5.h"

// md5 from: http://www.zedwood.com/article/cpp-md5-function

int main() {
    rtos os {std::vector<int>{500, 1000, 3000}};
    os.start(40);
    return 0;
}
