#ifndef MARKER_H
#define MARKER_H

#include <GL/glu.h>
#include <engine/physics/physical_single_body.h>

/**\brief A marker is a static object that marks a location.
It can be dragged around and displayed in different ways.

If should be used to place objects that should, themselves,
not be seen, like a spawner, unless for some crazy reason
 the spawner should look like stuff, like if there is a
 teleporter, that should be placed somewhere and thing-a-mabobs
 pop out of if, then that should be displayed.
*/


#include <engine/physics/physical_single_body.h>

class Marker : public PhysicalSingleBody {
private:
    static string geometry;
    double radius;

protected:
    virtual void OnSetSettings();
    virtual bool HandleMessage(NodeMessage message);

public:
    Marker();

    virtual void Draw();
    virtual void Update();
};

#endif // MARKER_H
