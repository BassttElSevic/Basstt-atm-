#pragma once
#include "database.h"
#include <string>
#include <iostream>

class quit {
private:
    std::string CardNumber;
    
public:
    quit(const std::string& cardNumber);
    
    // 保存数据并退出系统
    void saveAndExit();
    
    // 确认退出
    bool confirmExit();
};