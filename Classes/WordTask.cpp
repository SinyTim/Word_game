#include "WordTask.h"



USING_NS_CC;



bool WordTask::init(const std::string& task, const std::string& answer, char key) {
    return (
        setTask(task) && setAnswer(answer) && setKey(key)
    );
}

bool WordTask::isCorrectKey(EventKeyboard::KeyCode keyCode) const {
    return (_key == WordTask::keyCodeToChar(keyCode));
}

std::string WordTask::getTask() const {
    return _task;
}

std::string WordTask::getAnswer() const {
    return _answer;
}

char WordTask::getKey() const {
    return _key;
}

bool WordTask::setTask(const std::string& task) {

    if (task.empty()) {
        return false;
    }

    _task = task;
    return true;
}

bool WordTask::setAnswer(const std::string& answer) {

    if (answer.empty()) {
        return false;
    }

    _answer = answer;
    return true;
}

bool WordTask::setKey(char key) {

    if (!WordTask::isLetter(key)) {
        return false;
    }

    _key = key;
    return true;
}

char WordTask::keyCodeToChar(EventKeyboard::KeyCode keyCode) {
    const int offset = (int)EventKeyboard::KeyCode::KEY_A - 'a';
    return ((int)keyCode - offset);
}

bool WordTask::isLetter(char ch) {
    return (
        (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')
    );
}
