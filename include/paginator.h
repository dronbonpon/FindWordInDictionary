#pragma once

#include <vector>

// Выспомогательный класс диапазона итераторов
template <typename Iterator>
class IteratorRange {
public:
    IteratorRange( Iterator begin, Iterator end )
        : first( begin )
        , last( end )
        , size_( std::distance(first, last) )
    {
    }

    Iterator begin() const 
    {
        return first;
    }

    Iterator end() const 
    {
        return last;
    }

    size_t size() const 
    {
        return size_;
    }

private:
    Iterator first, last;
    size_t size_;
};

// Класс, который позволяет разбивать контейнер на страницы
template <typename Iterator>
class Paginator 
{
private:
    std::vector<IteratorRange<Iterator>> pages;

public:
    Paginator() = default;

    Paginator( Iterator begin, Iterator end, size_t page_size ) 
    {
        for ( size_t left = std::distance(begin, end); left > 0; ) 
        {
            size_t current_page_size = std::min( page_size, left );
            Iterator current_page_end = std::next( begin, current_page_size );
            pages.push_back( {begin, current_page_end} );

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const 
    {
        return pages.begin();
    }

    auto end() const 
    {
        return pages.end();
    }

    size_t size() const 
    {
        return pages.size();
    }
};

// Вспомогательная функция, создающая экземпляр класса Paginator
template <typename C>
auto Paginate( C& c, size_t page_size )
{
    return Paginator( begin( c ), end( c ), page_size );
}
