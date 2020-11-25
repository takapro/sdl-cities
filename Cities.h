#pragma once

struct City {
    static constexpr int NUM_CITIES = 151;
    static City cities[NUM_CITIES];

    const char* name;
    const char* country;
    float latitude;
    float longitude;
};
