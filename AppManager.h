#pragma once
#include "DataRepository.h"

class AppManager
{
    DataRepository data_;

    void login();
    
public:
    AppManager();
    ~AppManager();

    void run();
};
