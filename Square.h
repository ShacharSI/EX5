
#include "Point.h"
#include "Searchable.h"
#include <queue>
#ifndef EX1TM_SQUARE_H
#define EX1TM_SQUARE_H

/**
 * a class that "implempents" the searchable interface
 * and represents a point on map that can be searched.
 */
class Square: public Searchable {

public:

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Searchable>(*this);
        ar &point;

    }
    void setBeforeBfs(std::list<Searchable*> l);
    Square(Point p1);
    Square (int x,int y);
    Square();
    ~Square();
    Point getPoint();
    void setStartVal();
    void setAll();
    void SetLeft(Square* s);
    void SetRight(Square* s);
    void SetUpper(Square* s);
    void SetBottom(Square* s);
    void setBfsVal(int a);
    void setBfsFather(Square* father);
    void setVisitR(bool b);
    void setVisitL(bool b);
    void setVisitU(bool b);
    void setVisitB(bool b);
    void setVisitFind(bool b);
    void setVisited(bool b);
    void setSon(int num);
    int getSon();


    bool getVisited();
    bool checkVal(Square* start,Square* des );
    queue<Square*> updateNeiboghr(std::queue<Square*> q);
    void createRout();
    int getBfsVal();

    Square* getBstFather();
    Square* getLeft();
    Square* getRight();
    Square* getBotoom();
    Square* getUpper();
    Square *leftSon;
    Square *rightSon;
    Square *upperSon;
    Square *bottomSon;

    list<Searchable*> createList();

    bool isVisitLeft() const;
    bool isVisitBottom() const;
    bool isVisitRIght() const;
    bool isVisitUp() const;

private:

    int numSon;
    Point point;
    int bfsVal;
    Square* bfsFather;
    bool visitLeft;
    bool visitBottom;
    bool visitRIght;
    bool visitUp;
    bool setAllVisted;
    bool visitToFind;
    bool bfsVisited;

};


#endif //EX1TM_SQUARE_H