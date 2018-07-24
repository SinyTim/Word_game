#include "TaskManager.h"

#include <fstream>



TaskManager::TaskManager() 
    : _currentTaskNumber(0) {
}

bool TaskManager::init(const std::string& filePath) {
    return readTasks(filePath);
}

void TaskManager::setCurrentTaskNumberAsZero() const {
    _currentTaskNumber = 0;
}

size_t TaskManager::getTasksNumber() const {
    return _tasks.size();
}

WordTask TaskManager::getTask(size_t taskNumber) const {

    if (taskNumber >= getTasksNumber()) {
        cocos2d::log("Error: Tim::TaskManager::getTask().");
        assert(taskNumber < getTasksNumber());
    }

    return _tasks[taskNumber];
}

WordTask TaskManager::getRandomTask() const {
    auto taskNumber = cocos2d::random<size_t>(0, getTasksNumber() - 1);
    return getTask(taskNumber);
}

WordTask TaskManager::getNextTask() const {

    WordTask task = getTask(_currentTaskNumber);

    ++_currentTaskNumber;
    if (_currentTaskNumber >= getTasksNumber()) {
        _currentTaskNumber = 0;
    }

    return task;
}

void TaskManager::addTask(const WordTask& task) {
    _tasks.push_back(task);
}

bool TaskManager::readTasks(const std::string& filePath) {

    std::ifstream fin;
    fin.open(filePath);

    if (!fin.is_open()) {
        cocos2d::log("Error: Tim::TaskManager::readTasks().");
        fin.close();
        return false;
    }

    std::string task;
    std::string answer;
    char key;
    WordTask wordTask;

    while (true) {

        fin >> task;
        fin >> answer;
        fin >> key;

        if (!fin) {
            break;
        }

        if (wordTask.init(task, answer, key)) {
            addTask(wordTask);
        } else {
            cocos2d::log("Warning: Tim::TaskManager::readTasks().");
        }
    }

    fin.close();
    return true;
}
