#pragma once

// Шаблон класса синглтон, который реализует паттерн CRTP
template<typename Instance>
class Singleton
{
public:

    // Получение единственного экземпляра синглтона
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