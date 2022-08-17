#ifndef LOGDURATION_H_
#define LOGDURATION_H_
#include <iostream>
#include <chrono>

class LogDuration
{
private:
    const std::string id_;
    const std::chrono::steady_clock::time_point start_time_;

public:
    LogDuration(std::string id);
    ~LogDuration();
};

#endif