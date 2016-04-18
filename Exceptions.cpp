//
// Created by Gannon Faul on 3/31/16.
//

#include "Exceptions.h"

namespace Gaming {

    void GamingException::setName(std::string name) {
        __name = name;
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {
        __exp_width = expWidth;
        __exp_height = expHeight;
        __width = width;
        __height = height;
        setName("DimensionEx");
    }

    unsigned DimensionEx::getExpWidth() const {
        return __exp_width;
    }

    unsigned DimensionEx::getExpHeight() const {
        return __exp_height;
    }

    unsigned DimensionEx::getWidth() const {
        return __width;
    }

    unsigned DimensionEx::getHeight() const {
        return __height;
    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
        os << "minWidth: " << getExpWidth();
        os << " minHeight: " << getExpHeight() << std::endl;
        os << "width: " << getWidth();
        os << " height: " << getHeight() << std::endl;
    }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight,
                                                       unsigned width, unsigned height
    ) : DimensionEx(minWidth, minHeight, width, height) {
        setName("InsufficientDimensionEx");
    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const {
        os << "maxWidth: " << getExpWidth();
        os << " maxHeight: " << getExpHeight() << std::endl;
        os << "width: " << getWidth();
        os << " height: " << getHeight() << std::endl;
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight,
                                 unsigned width, unsigned height
    ) : DimensionEx(maxWidth, maxHeight, width, height){
        setName("OutOfBoundsEx");
    }

    void PositionEx::__print_args(std::ostream &os) const {
        os << "x: " << __x;
        os << " y: " << __y << std::endl;
    }

    PositionEx::PositionEx(unsigned x, unsigned y) {
        __x = x;
        __y = y;
        setName("PositionEx");
    }

    PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y) : PositionEx(x, y) {
        setName("PositionNonemptyEx");
    }

    PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y) : PositionEx(x, y) {
        setName("PositionEmptyEx");
    }

    void PosVectorEmptyEx::__print_args(std::ostream &os) const {
        os << getName() << std::endl;
    }

    PosVectorEmptyEx::PosVectorEmptyEx() {
        setName("PosVectorEmptyEx");
    }

    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        os << ex.__name << std::endl;
        ex.__print_args(os);
        return os;
    }

}