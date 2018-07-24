#pragma once

#include <string>



static const   std::string   fontFile            = "fonts/Marker Felt.ttf";
static const   float         fontSize            = 30.0f;

static const   int           scoreChange         = 10;
static const   int           winScore            = 100;

static const   int           initialLives        = 3;

static const   std::string   tasksFile           = "data/tasks.txt";
static const   std::string   scoreFile           = "data/record.txt";
static const   std::string   statisticsFile      = "data/statistics.txt";

static const   std::string   backgroundImage     = "background.jpg";

static const   std::string   replayButtonImage   = "buttons/ReplayButton.png";
static const   std::string   menuButtonImage     = "buttons/MenuButton.png";
static const   std::string   exitButtonImage     = "buttons/ExitButton.png";

static const   std::string   backgroundMusic     = "audio/background.mp3";
static const   std::string   correctSound        = "audio/correct.wav";
static const   std::string   wrongSound          = "audio/wrong.wav";

static const   float         minFallingSpeed     = 50.0f;
static const   float         maxFallingSpeed     = 250.0f;

static const   float         menuPadding         = 30.0f;
static const   float         topMargin           = 10.0f;
static const   float         sideMargin          = 10.0f;

static const   int           separatorLength     = 30;


enum Buttons {
    Menu,
    Exit,
    Replay,
};
