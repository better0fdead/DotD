#pragma once

#include <SFML/Graphics.hpp>


class State {
public:
    State() {};

    virtual ~State() {};


    virtual void init() = 0;

    virtual void update() = 0; //Updates the Components of the State
    virtual void draw() = 0; //Draws the Components of the State
    virtual void processStuff() = 0;//Process The Components in the State
    virtual void updateKeyBinds() = 0; //All Key Binds Of State go in here

    // virtual void checkForQuit(); //Predefined Quit Key
    virtual void pause() {};

    virtual void start() {};

//    void setQuit(bool newQuit);
//
//    bool getQuit() const; // determines if State should end Goes in Update Function in GAME
//
//    void setHolderScore(int newScore);
//
//    int getHolderScore() const;
//
//    //Allows the States the Option to switch to a diffent State depending on their definitions
//    virtual bool switchState();

private:
//    bool quit;  // determines if the State Should Quit Initially False
    // int holderScore; // transfer score from GameState to LostState

};
