//
// Created by Alex.
//

#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>

#include "shapeInverter.h"


MStatus initializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin fnPlugin(obj, "Alex Widener", "0.1", "Any");

    status = fnPlugin.registerNode("shapeInverter",
                                   shapeInverter::typeId,
                                   shapeInverter::creator,
                                   shapeInverter::initialize,
                                   MPxNode::kDeformerNode);

    return status;
}


MStatus uninitializePlugin(MObject obj) {
    MStatus status;
    MFnPlugin fnPlugin(obj);
    status = fnPlugin.deregisterNode(shapeInverter::typeId);
    return status;
}
