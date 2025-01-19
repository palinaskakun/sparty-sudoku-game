/**
 * @file SpartyFinder.cpp
 * @author Team Syceus
 */

#include "../pch.h"
#include "SpartyFinder.h"

using namespace std;

/**
 * Visits object
 * @param sparty Object we are looking for
 */
void SpartyFinder::VisitSparty(Sparty *sparty)
{
    mSparty = sparty;
    //mSparty = std::shared_ptr<Sparty>(sparty);
}

/**
 * Visits object
 * @param xray Object we are looking for
 */
void SpartyFinder::VisitXray(ItemXray *xray)
{
    mXray = xray;
}



