#pragma once

#include "WordTask.h"



class TaskManager {

public:
    TaskManager();
    virtual ~TaskManager() = default;

    bool init(const std::string& filePath);
    void setCurrentTaskNumberAsZero() const;

    size_t getTasksNumber() const;
    WordTask getTask(size_t taskNumber) const;
    WordTask getRandomTask() const;
    WordTask getNextTask() const;
    void addTask(const WordTask& task);

protected:
    bool readTasks(const std::string& filePath);


protected:
    std::vector<WordTask> _tasks;
    mutable size_t _currentTaskNumber;
};
