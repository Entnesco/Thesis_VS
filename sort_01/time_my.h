/*
Biblioteka time_my.h zawiera klase o nazwie Time składającej się z metod służących do pomiaru czasu w programie
*/

#include <chrono>
#include <unistd.h>

class Time{

    std::chrono::time_point<std::chrono::system_clock> start, end;

    public:

    void startTimer()
    {
        start = chrono::system_clock::now();
    }

    long long stopGetNanoseconds()
    {
        end = chrono::system_clock::now();  
        return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }

    long long stopGetMicroseconds()
    {
        end = chrono::system_clock::now();  
        return chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    long long stopGetMiliseconds()
    {
        end = chrono::system_clock::now();  
        return chrono::duration_cast<chrono::milliseconds>(end - start).count();
    }

    long long stopGetSeconds()
    {
        end = chrono::system_clock::now();
        return chrono::duration_cast<chrono::seconds>(end - start).count();
    }
};