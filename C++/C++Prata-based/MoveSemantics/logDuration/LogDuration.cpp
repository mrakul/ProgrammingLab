#include "LogDuration.h"

//Use move semantics not to copy id and initialize start_time with the time of object creation
LogDuration::LogDuration(std::string id) : id_(std::move(id)), start_time_(std::chrono::steady_clock::now()) {}

//Track the time of execution
LogDuration::~LogDuration()
{
    const auto end_time = std::chrono::steady_clock::now();
    const auto dur = end_time - start_time_;
    std::cout << id_ << ": ";
    std::cout << "operation time"
        << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
        << " ms" << std::endl;
}