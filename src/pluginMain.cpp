//
// Created by Alex.
//

#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>

#include "shapeInverter.h"
#include "shapeInverterCommand.h"


MStatus initializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin fnPlugin(obj, "Alex Widener", "0.1", "Any");

    status = fnPlugin.registerNode("shapeInverter",
                                   shapeInverter::typeId,
                                   shapeInverter::creator,
                                   shapeInverter::initialize,
                                   MPxNode::kDeformerNode);

    status = fnPlugin.registerCommand("shapeInverterCommand",
                                      shapeInverterCommand::creator);

    CHECK_MSTATUS_AND_RETURN_IT(status);
    return status;
}


MStatus uninitializePlugin(MObject obj) {
    MStatus status;
    MFnPlugin fnPlugin(obj);
    status = fnPlugin.deregisterNode(shapeInverter::typeId);
    status = fnPlugin.deregisterCommand("shapeInverterCommand");
    CHECK_MSTATUS_AND_RETURN_IT(status);
    return status;
}


