#pragma once

#include "task_t.hpp"


class taskManager
{
    private:
    task_t Tasks[];
    bool solveTask(int taskNum);
    void sendBuff(int buffNum);
    public:
    taskManager();
	~taskManager();
    void process_task(int taskNum);
}
