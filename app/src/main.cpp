#include "FileLogger.h"
#include <iostream>
#include <string>



int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <log_file> [default_level]\nПример: " << argv[0] << " log.txt WARN\n";
        return 1;
    }

    std::string filename = argv[1];
    ALogger::Priority priority = argv[2];

    FileLogger fileLog(filename, priority);



    return 0;
}