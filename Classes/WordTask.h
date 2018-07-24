#pragma once

#include "cocos2d.h"



class WordTask {

public:
    WordTask() = default;
    virtual ~WordTask() = default;

    bool init(const std::string& task, const std::string& answer, char key);
    bool isCorrectKey(cocos2d::EventKeyboard::KeyCode keyCode) const;

    std::string getTask() const;
    std::string getAnswer() const;
    char getKey() const;
    bool setTask(const std::string& task);
    bool setAnswer(const std::string& answer);
    bool setKey(char key);

    static char keyCodeToChar(cocos2d::EventKeyboard::KeyCode keyCode);
    static bool isLetter(char ch);


protected:
    std::string _task;
    std::string _answer;
    char _key;
};
