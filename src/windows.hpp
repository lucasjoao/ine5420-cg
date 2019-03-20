#ifndef OBJETO_WINDOWS
#define OBJETO_WINDOWS

#include <string>

class Windows {

    public:

        Windows(double minX, double minY, double maxX, double maxY) : _minX(minX), _minY(minY),
        _maxX(maxX), _maxY(maxY) {}


        void movimentar(double x) {
            _minX += x;
            _minY += x;
            _maxX += x;
            _maxY += x;
        }

        void zoom(double x) {
            _minX -= x;
            _minY -= x;
            _maxX += x;
            _maxY += x;
        }

    private:

        double _minX;
        double _minY;
        double _maxX;
        double _maxY;

};

#endif