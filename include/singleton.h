#pragma once

template<typename Instance>
class Singleton
{
public:
    static Instance& GetInstance()
    {
        static Instance instance;
        return instance;
    }

    Singleton( const Singleton& other ) = delete;
    Singleton& operator=( const Singleton& other ) = delete;

protected:
    Singleton() = default;
};