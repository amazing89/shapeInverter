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
#include <maya/MFnMesh.h>
#include <maya/MFnPointArrayData.h>
#include <maya/MItGeometry.h>
#include <maya/MFnData.h>

#include "cmath"


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
    MFnTypedAttribute       typedAttr;
    MFnMatrixAttribute      matrixAttr;
    MObject                 outputGeometry;

    if (API_VERSION < 201600) {
        outputGeometry = MPxDeformerNode::outputGeom;
    } else {
        outputGeometry = MPxGeometryFilter::outputGeom;
    }

    aCorrectiveGeo = typedAttr.create("correctiveMesh", "cm", MFnData::kMesh);
    addAttribute(aCorrectiveGeo);
    attributeAffects(aCorrectiveGeo, outputGeometry);

    aDeformedPoints = typedAttr.create("deformedPoints", "dp", MFnData::kPointArray);
    addAttribute(aDeformedPoints);

    aMatrix = matrixAttr.create("inversionMatrix", "im");
    matrixAttr.setArray(true);
    addAttribute(aMatrix);

    return MStatus::kSuccess;
}

MStatus shapeInverter::deform(MDataBlock& data, MItGeometry& iter, const MMatrix& localToWorldMatrix, unsigned int mIndex)
{
    // Get the corrective mesh
    MObject originalMesh;

    originalMesh = data.inputValue(aCorrectiveGeo).asMesh();
    if (originalMesh.isNull()) {
        return MS::kNotImplemented;
    }

    MFnMesh fnMesh(data.inputValue(originalMesh).asMesh());
    MPointArray correctivePoints;
    fnMesh.getPoints(correctivePoints);

    if (initialized == 0) {
        MArrayDataHandle hMatrix = data.inputArrayValue(aMatrix);
        int matrixCount = hMatrix.elementCount();
        if (matrixCount == 0) {
            // No data yet
            return MS::kNotImplemented;
        }
        for (int i = 0; i < matrixCount; i++) {
            hMatrix.jumpToElement(i);
            matrices.append(hMatrix.inputValue().asMatrix());
        }

        MObject originalDeformedPoints = data.inputValue(aDeformedPoints).data();
        MFnPointArrayData pointArrayData(originalDeformedPoints);
        pointArrayData.copyTo(deformedPoints);
        initialized = 1;
    }

    while (!iter.isDone()) {
        int index = iter.index();
        MVector delta = correctivePoints[index] - deformedPoints[index];
        if ((abs(delta.x) < 0.001) && (abs(delta.y) < 0.001) && (abs(delta.z) < 0.001)) {
            iter.next();
            continue;
        }
        MVector offset = delta * matrices[index];
        MPoint position = iter.position() + offset;
        iter.setPosition(position);
        iter.next();
    }

    return MS::kSuccess;
}
