#pragma once
#include <memory>

namespace core
{
    template <typename T>
    class CSingleton
    {
    public:
        static T& GetInstance()
        {
            static T    instance;
            return instance;
        }
    protected:
        CSingleton() {}
    };
}
