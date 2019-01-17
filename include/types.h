#ifndef types_h
#define types_h

enum simplex {VERTEX, TRIANGLE};
enum direction {FUTURE, PAST, SAME};
enum moveType {TWOFOUR, FOURTWO, TWOTWO};

class Vertex;
class Triangle;

template <class T>
using adjList = std::deque<T>;

#endif
