//
// Created by tobias on 21.11.16.
//

#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"

class ROBDDTest : public ::testing::Test
{
protected:
    //virtual void start();
    //virtual void stop();

    virtual void SetUp();
    virtual void TearDown();

    ClassProject::Manager *x;
    ClassProject::BDD_ID *a;
    ClassProject::BDD_ID *b;
    ClassProject::BDD_ID *c;
    ClassProject::BDD_ID *d;


};
#endif VDS_PROJECT_TESTS_H

