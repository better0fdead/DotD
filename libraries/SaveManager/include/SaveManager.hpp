#pragma once


class SaveManager:
{
    public:
        SaveManager();
        ~SaveManager();
        int getTopScore(std::string name);
        void saveScore(int score, std::string name);
} 