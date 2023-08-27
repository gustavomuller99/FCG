#include <utils/bezier.h>

//FONTE - https://stackoverflow.com/questions/785097/how-do-i-implement-a-b%C3%A9zier-curve-in-c

float getPt(float n1 , float n2 , float perc) {
    float diff = n2 - n1;
    return n1 + ( diff * perc );
};

glm::vec2 getNextPt(float t, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4) {

    // The Green Lines
    float xa = getPt( p1.x , p2.x , t );
    float ya = getPt( p1.y , p2.y , t );
    float xb = getPt( p2.x , p3.x , t );
    float yb = getPt( p2.y,  p3.y , t );
    float xc = getPt( p3.x , p4.x , t );
    float yc = getPt( p3.y , p4.y , t );

    // The Blue Line
    float xm = getPt( xa , xb , t );
    float ym = getPt( ya , yb , t );
    float xn = getPt( xb , xc , t );
    float yn = getPt( yb , yc , t );

    // The Black Dot
    float x = getPt( xm , xn , t );
    float y = getPt( ym , yn , t );

    return glm::vec2(x, y);
};
