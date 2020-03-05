#include "logger.h"



Logger::Logger():mThreadStarted(false),mExit(false)
{
    //Start background thread
    mThread=std::thread{&Logger::processEntries, this};
    //Wait until background thread starts its processing loop.
    std::unique_lock<std::mutex>lock(mMutexStarted);
    mCondVarStarted.wait(lock,[&](){return mThreadStarted==true;});
}
Logger::~Logger()
{
    //Gracefully shut down the thread by setting mExit
    //to true notifying the thread.
    mExit=true;
    //Notify condition variable to wake up thread.
    mCondVar.notify_all();
    //Wait until thread is shut down.
    mThread.join();
}
void Logger::log(const std::string& entry)
{
    //Lock mutex and add entry to the queue.
    std::unique_lock<std::mutex>lock(mMutex);
    mQueue.push(entry);
    //Notify condition variable to wake up thread.
    mCondVar.notify_all();
}
void Logger::processEntries()
{
    //Open log file
    std::ofstream ofs("log.txt");
    if(ofs.fail())
    {
        std::cerr<<"Failed to open logfile."<<std::endl;
        return;
    }
    //Start processing loop.
    std::unique_lock<std::mutex>lock(mMutex);
    //Notify listeners that thread is starting processing loop.
    mThreadStarted=true;
    mCondVarStarted.notify_all();
    while(true){
        //Wait for a notification.
        mCondVar.wait(lock);
        //Condition variable is notified,so something is in queue
        //and/or we need to shut down this thread.
        lock.unlock();
        while(true)
        {
            lock.lock();
            if(mQueue.empty())
            {
                break;
            }else{
                ofs<<mQueue.front()<<std::endl;
                mQueue.pop();
            }
            lock.unlock();
        }
        if(mExit)
            break;
    }
}
