#include "PlayScene.h"

#include <fstream>
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "constants.h"
#include "MenuScene.h"



USING_NS_CC;



bool PlayScene::init() {

    if (!Scene::init()) {
        return false;
    }

    AppDelegate::createBackground(this);
    createMenu();
    createLabels();

    _taskManager.init(tasksFile);

    setInitialState();
    
    setKeyboardListener();
    endDelay();
    return true;
}

void PlayScene::update(float elapsedTime) {

    auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
    auto taskLabelBox = _taskLabel->getBoundingBox();
    auto top = taskLabelBox.origin.y + taskLabelBox.size.height;

    if (top < visibleOrigin.x) {

        _checkedAnswers.push_back({_currentTask, false});
        reduceLives();
        updateLabels();

        if (_isRun) {
            updateTask(0);
        }
    }
}

void PlayScene::setInitialState() {

    setScore(0);
    setLives(initialLives);
    loadMaxScore(scoreFile);

    updateLabels();

    updateTask(0);

    _isRun = true;
}

void PlayScene::setKeyboardListener() {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void PlayScene::createMenu() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto menuItem = MenuItemImage::create(
        menuButtonImage, menuButtonImage,
        CC_CALLBACK_1(PlayScene::menuMenuCallback, this)
    );
    menuItem->setPosition(origin + menuItem->getContentSize() / 2);
    menuItem->setTag(Buttons::Menu);

    auto exitItem = MenuItemImage::create(
        exitButtonImage, exitButtonImage,
        CC_CALLBACK_1(PlayScene::menuExitCallback, this)
    );
    exitItem->setPosition(
        origin + Vec2(visibleSize.width - exitItem->getContentSize().width / 2,
                      exitItem->getContentSize().height / 2)
    );
    exitItem->setTag(Buttons::Exit);

    auto replayItem = MenuItemImage::create(
        replayButtonImage, replayButtonImage,
        CC_CALLBACK_1(PlayScene::menuReplayCallback, this)
    );
    Vec2 centerPosition = origin + visibleSize / 2;
    replayItem->setPosition(
        centerPosition.x, centerPosition.y - 50 - replayItem->getContentSize().height / 2
    );
    replayItem->setTag(Buttons::Replay);
    replayItem->setVisible(false);

    _menu = Menu::create(menuItem, exitItem, replayItem, nullptr);
    _menu->setPosition(Vec2::ZERO);
    this->addChild(_menu, 1);
}

void PlayScene::createLabels() {

    _scoreLabel = createLabel("", fontFile, fontSize, Color4B::YELLOW);
    _maxScoreLabel = createLabel("", fontFile, fontSize, Color4B::YELLOW);
    _livesLabel = createLabel("", fontFile, fontSize, Color4B::YELLOW);

    _taskLabel = createLabel("", fontFile, fontSize, Color4B::BLUE);

    _gameOverLabel = createLabel("", fontFile, 2 * fontSize, Color4B::RED);
    _gameOverLabel->setVisible(false);
}

Label* PlayScene::createLabel(const std::string& text,
                              const std::string& fontFilePath,
                              float fontSize,
                              const Color4B& color,
                              cocos2d::Vec2 position) {

    auto label = Label::createWithTTF(text, fontFilePath, fontSize);
    label->setTextColor(color);
    label->setPosition(position);
    this->addChild(label, 1);
    return label;
}

void PlayScene::updateLabels() {
    updateLabelsText();
    updateLabelsPositions();
}

void PlayScene::updateLabelsText() {
    _scoreLabel->setString("Score: " + std::to_string(_score));
    _maxScoreLabel->setString("Max score: " + std::to_string(_maxScore));
    _livesLabel->setString("Lives: " + std::to_string(_lives));
    _gameOverLabel->setString(((_lives > 0) ? "Win!" : "Loss."));
}

void PlayScene::updateLabelsPositions() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto halfScoreLabelSize = _scoreLabel->getContentSize() / 2;
    _scoreLabel->setPosition(
        origin + Vec2(halfScoreLabelSize.width + sideMargin,
                      visibleSize.height - halfScoreLabelSize.height - topMargin)
    );

    auto halfMaxScoreLabelSize = _maxScoreLabel->getContentSize() / 2;
    _maxScoreLabel->setPosition(
        origin + Vec2(visibleSize.width / 2,
                      visibleSize.height - halfMaxScoreLabelSize.height - topMargin)
    );

    auto halfLivesLabelSize = _livesLabel->getContentSize() / 2;
    _livesLabel->setPosition(
        origin + visibleSize - halfLivesLabelSize - Vec2(sideMargin, topMargin)
    );

    _gameOverLabel->setPosition(origin + visibleSize / 2);
}

void PlayScene::updateTask(float elapsedTime) {
    endDelay();

    _currentTask = _taskManager.getNextTask(); // getRandomTask();
    _taskLabel->setString(_currentTask.getTask());
    initTaskLabelAction();
}

void PlayScene::initTaskLabelAction() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    _taskLabel->stopAllActions();
    _taskLabel->setScale(1);

    auto halfTaskLabelSize = _taskLabel->getContentSize() / 2;
    _taskLabel->setPosition(
        origin + Vec2(visibleSize.width / 2, 
                      visibleSize.height - halfTaskLabelSize.height - 50)
    );

    Vec2 taskMoveTo = origin + Vec2(visibleSize.width / 2, -100);
    Vec2 taskScaleBy(3, 3);
    moveAndScaleNode(_taskLabel, taskMoveTo, taskScaleBy);
}

void PlayScene::moveAndScaleNode(Node* node,
                                 const Vec2& moveTo,
                                 const Vec2& scaleBy) {

    auto distance = node->getPosition().getDistance(moveTo);
    auto duration = distance / AppDelegate::getFallingSpeed();
    
    auto moveToAction = MoveTo::create(duration, moveTo);
    auto scaleByAction = ScaleBy::create(1, scaleBy.x, scaleBy.y);
    node->runAction(moveToAction);
    node->runAction(scaleByAction);
}

void PlayScene::showAnswer() {
    _taskLabel->stopAllActions();
    _taskLabel->setString(_currentTask.getAnswer());
}

void PlayScene::addScore(int scoreChange) {

    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    audioEngine->playEffect(correctSound.c_str());

    setScore(_score + scoreChange);
}

void PlayScene::setScore(int score) {

    _score = (score >= 0) ? score : 0;
    updateMaxScore();

    if (_score >= winScore) {
        _isRun = false;
        callFunctionWithDelay(schedule_selector(PlayScene::showEnd));
    }
}

void PlayScene::updateMaxScore() {
    _maxScore = MAX(_maxScore, _score);
}

void PlayScene::loadMaxScore(const std::string& filePath) {

    _maxScore = 0;

    std::ifstream fin;
    fin.open(filePath);

    if (fin.is_open()) {
        fin >> _maxScore;
    }

    fin.close();
}

void PlayScene::saveMaxScoreToFile(const std::string& filePath) {

    std::ofstream fout;
    fout.open(filePath);

    updateMaxScore();
    fout << _maxScore;

    fout.close();
}

void PlayScene::saveStatisticsToFile(const std::string& filePath) {

    if (_checkedAnswers.empty()) {
        return;
    }

    std::ofstream fout;
    fout.open(filePath, std::ios::app);

    for (const auto& checkedAnswerPair : _checkedAnswers) {
        fout << checkedAnswerPair.first.getTask() << " - " 
            << (checkedAnswerPair.second ? "correct" : "wrong") << "\n";
    }
    for (size_t i = 0; i < separatorLength; ++i) {
        fout << '-';
    }
    fout << '\n';

    fout.close();

    _checkedAnswers.clear();
}

void PlayScene::saveDataToFiles() {
    saveMaxScoreToFile(scoreFile);
    saveStatisticsToFile(statisticsFile);
}

void PlayScene::reduceLives() {

    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    audioEngine->playEffect(wrongSound.c_str());

    setLives(_lives - 1);
}

void PlayScene::setLives(int lives) {

    _lives = (lives >= 0) ? lives : 0;

    if (_lives == 0) {
        _isRun = false;
        callFunctionWithDelay(schedule_selector(PlayScene::showEnd));
    }
}

void PlayScene::showEnd(float elapsedTime) {
    _taskLabel->setVisible(false);
    _gameOverLabel->setVisible(true);
    _menu->getChildByTag(Buttons::Replay)->setVisible(true);
}

void PlayScene::callFunctionWithDelay(SEL_SCHEDULE selector) {
    _isKeyboardAvailable = false;
    this->unscheduleUpdate();
    scheduleOnce(selector, 1);
}

void PlayScene::endDelay() {
    _isKeyboardAvailable = true;
    this->scheduleUpdate();
}

void PlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    
    switch (keyCode) {

        default:
            if (!_isKeyboardAvailable 
                || !WordTask::isLetter(WordTask::keyCodeToChar(keyCode))) {
                break;
            }

            _checkedAnswers.push_back({_currentTask, _currentTask.isCorrectKey(keyCode)});

            if (_currentTask.isCorrectKey(keyCode)) {
                addScore(scoreChange);
            } else {
                reduceLives();
            }

            showAnswer();
            updateLabels();

            if (_isRun) {
                callFunctionWithDelay(schedule_selector(PlayScene::updateTask));
            }
            break;
    }
}

void PlayScene::menuMenuCallback(Ref* sender) {
    saveDataToFiles();
    Director::getInstance()->popScene();
}

void PlayScene::menuExitCallback(Ref* sender) {
    saveDataToFiles();
    Director::getInstance()->end();
}

void PlayScene::menuReplayCallback(Ref* sender) {
    saveDataToFiles();

    setInitialState();
    endDelay();

    _taskLabel->setVisible(true);
    _gameOverLabel->setVisible(false);
    _menu->getChildByTag(Buttons::Replay)->setVisible(false);
}
