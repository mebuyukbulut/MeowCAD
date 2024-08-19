#pragma once
class ETime{
    double 
        delta_time{},
        last_time{}, 
        current_time{};
public:
    void update();
    double get_delta_time();
};

