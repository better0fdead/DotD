#pragma once


class SaveManager:
{
    public:
        SaveManager();
        ~SaveManager();
        int getTopScore(std::string name);
        bool saveScore(int score, std::string name);
};