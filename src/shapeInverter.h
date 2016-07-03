//
// Created by Alex.
//

#ifndef SHAPEINVERTER_H
#define SHAPEINVERTER_H

#include <maya/MTypeId.h>
#include <maya/MPxDeformerNode.h>
#include <maya/MPointArray.h>
#include <maya/MIntArray.h>

using namespace std;

class shapeInverter : public MPxDeformerNode {

public:
    shapeInverter();
    static void*        creator();
    static MStatus      initialize();
    virtual MStatus     deform(MDataBlock& data, MItGeometry& iter, const MMatrix& localToWorldMatrix, unsigned int mIndex);


public:
    static MObject      aMatrix;
    static MObject      aCorrectiveGeo;
    static MObject      aDeformedPoints;
    static MTypeId      typeId;

private:
    bool                initialized;
    unsigned            elementCount;
    MPointArray         deformedPoints;
    MIntArray           bindArray;


};


#endif
