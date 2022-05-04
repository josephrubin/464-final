#include <iostream>
#include <vector>
#include "rtos.h"
#include "md5.h"

// md5 from: http://www.zedwood.com/article/cpp-md5-function

int main() {
    std::cout << "md5 of 'grape': " << md5("grape") << std::endl;
    std::cout << "Hello, World!" << std::endl;
    rtos os {std::vector<int>{500, 600, 1200, 60}};
    os.start(5);
    std::cout << "All done" << std::endl;
    return 0;
}
