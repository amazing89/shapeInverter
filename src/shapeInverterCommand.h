//
// Created by Alex on 7/4/16.
//

#ifndef SHAPEINVERTERCOMMAND_H
#define SHAPEINVERTERCOMMAND_H

#include <maya/MPxCommand.h>
#include <maya/MArgList.h>


class shapeInverterCommand : public MPxCommand {
public:
    shapeInverterCommand() {};
    virtual MStatus doIt(const MArgList&);
    static void*    creator();
};


#endif
