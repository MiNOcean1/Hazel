#pragma once

#include<iostream>
#include<memory>
#include<utility>
#include<algorithm>
#include<functional>

#include<string>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>

#include "Hazel/Log.h"

//如果我们的平台是Windows就包含这个头文件
#ifdef HZ_PLATFORM_WINDOWS
    #include<Windows.h>
#endif  
