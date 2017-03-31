#ifndef __CORE_CSingleton_
#define __CORE_CSingleton_

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

#endif