#ifndef TEST_H
#define TEST_H
#include<sstream>
#include"logger.h"
//测试函数

void logSomeMessages(int id,Logger &logger)
{
    for(int i=0;i<10;++i)
    {
        std::stringstream ss;
        ss<<"Log entry"<<i<<"from thread"<<id;
        logger.log(ss.str());
    }
}
#endif // TEST_H
