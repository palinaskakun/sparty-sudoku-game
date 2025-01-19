/**
 * @file ContainerFinder.cpp
 * @author audre
 *
 * Visitor class that finds a container
 */

#include "../pch.h"
#include "ContainerFinder.h"

using namespace std;

/**
 * Visits container
 * @param container Object we are looking for
 */
void ContainerFinder::VisitContainer(Container *container)
{
    mContainer = container;
}

/**
 * Finds Xray
 * @param xray Object we are looking for
 */
void ContainerFinder::VisitXray(ItemXray *xray)
{
    mXray = xray;
}



