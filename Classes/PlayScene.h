#pragma once

#include "cocos2d.h"
#include "TaskManager.h"



class PlayScene 
    : public cocos2d::Scene {

public:
    CREATE_FUNC(PlayScene);

protected:

    bool init() override;
    void update(float elapsedTime) override;

    void setInitialState();
    void setKeyboardListener();

    void createMenu();
    void createLabels();
    cocos2d::Label* createLabel(const std::string& text,
                                const std::string& fontFilePath,
                                float fontSize,
                                const cocos2d::Color4B& color,
                                cocos2d::Vec2 position = cocos2d::Vec2::ZERO);

    void updateLabels();
    void updateLabelsText();
    void updateLabelsPositions();

    void updateTask(float elapsedTime);
    void initTaskLabelAction();
    void moveAndScaleNode(cocos2d::Node* node,
                          const cocos2d::Vec2& moveTo,
                          const cocos2d::Vec2& scaleBy);
    void showAnswer();

    void addScore(int scoreChange);
    void setScore(int score);

    void updateMaxScore();
    void loadMaxScore(const std::string& filePath);
    void saveMaxScoreToFile(const std::string& filePath);
    void saveStatisticsToFile(const std::string& filePath);
    void saveDataToFiles();

    void reduceLives();
    void setLives(int lives);

    void showEnd(float elapsedTime);
    void callFunctionWithDelay(cocos2d::SEL_SCHEDULE selector);
    void endDelay();

    // Callbacks:
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, 
                      cocos2d::Event* event);
    void menuMenuCallback(cocos2d::Ref* sender);
    void menuExitCallback(cocos2d::Ref* sender);
    void menuReplayCallback(cocos2d::Ref* sender);


protected:

    bool _isRun;
    bool _isKeyboardAvailable;

    TaskManager _taskManager;
    WordTask _currentTask;

    int _score;
    int _maxScore;
    int _lives;

    std::vector<std::pair<WordTask, bool>> _checkedAnswers;

    cocos2d::Label* _taskLabel;
    cocos2d::Label* _scoreLabel;
    cocos2d::Label* _maxScoreLabel;
    cocos2d::Label* _livesLabel;
    cocos2d::Label* _gameOverLabel;

    cocos2d::Menu* _menu;
};
