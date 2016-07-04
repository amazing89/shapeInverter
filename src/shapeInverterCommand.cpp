//
// Created by Alex on 7/4/16.
//

#include "shapeInverterCommand.h"
#include <maya/MGlobal.h>


void* shapeInverterCommand::creator()
{
    return new shapeInverterCommand;
}

MStatus shapeInverterCommand::doIt(const MArgList& argList)
{

    MGlobal::displayInfo("Hello");
    return MS::kSuccess;
}