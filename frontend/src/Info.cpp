//
// Created by robcholz on 11/27/23.
//
#include "ssa/Info.hpp"


Info::Info(){

}

Info& Info::getInstance() {
    static Info info;
    return info;
}
