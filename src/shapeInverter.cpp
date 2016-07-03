//
// Created by Alex.
//

#include "shapeInverter.h"
#include <maya/MGlobal.h>
#include <maya/MPxDeformerNode.h>
#include <maya/MPxGeometryFilter.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnData.h>

/*
 * As of right now, I'm only writing this to work for 2016 and above, therefore, I'll have to use the outputGeom
 * from MPxGeometryFilter and not from MPxDeformer node. I'll work on that later.
 */


int API_VERSION = MGlobal::apiVersion();


MTypeId shapeInverter::typeId(0x80008);

MObject     shapeInverter::aCorrectiveGeo;
MObject     shapeInverter::aDeformedPoints;
MObject     shapeInverter::aMatrix;


shapeInverter::shapeInverter()
{
    initialized = 0;
    elementCount = 0;
}


void* shapeInverter::creator()
{
    return new shapeInverter();
}


MStatus shapeInverter::initialize()
{
    MFnNumericAttribute     numAttr;
    MFnTypedAttribute       typedAttr;
    MFnMatrixAttribute      matrixAttr;
    MPxGeometryFilter       outputGeometry;

    /* Set up for 2015 once this is working */

    aCorrectiveGeo = typedAttr.create("correctiveMesh", "cm", MFnData::kMesh);
    addAttribute(aCorrectiveGeo);

    aDeformedPoints = typedAttr.create("deformedPoints", "dp", MFnData::kPointArray);
    addAttribute(aDeformedPoints);

    aMatrix = matrixAttr.create("inversionMatrix", "im");
    matrixAttr.setArray(true);

    addAttribute(aMatrix);

    return MStatus::kSuccess;
}

MStatus shapeInverter::deform(MDataBlock& data, MItGeometry& iter, const MMatrix& localToWorldMatrix, unsigned int mIndex)
{

    return MS::kSuccess;
}
