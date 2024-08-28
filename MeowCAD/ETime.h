#pragma once
class ETime {
    double
        delta_time{},
        last_time{},
        current_time{},
        elapsed_time{};
public:
    void update();
    double get_delta_time();
    double get_elapsed_time();
};

