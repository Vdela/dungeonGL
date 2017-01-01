//
// Created by Vincent on 01/01/2017.
//

#ifndef IMACGL_INTERFACE_H
#define IMACGL_INTERFACE_H

#include <cstdint>

class Interface {
public:
    static Interface& getInstance();

    static const uint32_t gameWidth = 800;
    static const uint32_t gameHeight = 800;
private:
    static Interface * instance;
    Interface();
};


#endif //IMACGL_INTERFACE_H
