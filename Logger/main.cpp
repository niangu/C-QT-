#include <QCoreApplication>
#include"logger.h"
#include"test.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Logger logger;
    std::vector<std::thread>threads;
    //Create a few threads all working with the same Logger instance.
    for(int i=0;i<10;++i)
    {
        threads.push_back(std::thread{logSomeMessages, i, std::ref(logger)});
    }
    //Wait for all threads to finish
    for(auto& t:threads)
    {
        t.join();
    }

    return a.exec();
}
