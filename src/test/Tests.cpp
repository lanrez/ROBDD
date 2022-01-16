//
// Created by tobias on 21.11.16.
//

#include "Tests.h"

void ROBDDTest::SetUp() {
  x = new ClassProject::Manager();
  a = new ClassProject::BDD_ID (x->createVar("a"));
  b = new ClassProject::BDD_ID (x->createVar("b"));
  c = new ClassProject::BDD_ID (x->createVar("c"));
  d = new ClassProject::BDD_ID (x->createVar("d"));
}

void ROBDDTest::TearDown() {
  x->~Manager();
  //delete a;

}

TEST_F(ROBDDTest, constructorTest){
  ClassProject::BDD_ID y = x->True();
  ASSERT_EQ(y,2);
  y = x->False();
  ASSERT_EQ(y,1);
}

TEST_F(ROBDDTest, constantTest){
  ASSERT_TRUE(x->isConstant(x->True()));
  ASSERT_TRUE(x->isConstant(x->False()));
  ASSERT_FALSE(x->isConstant(*a));
  ASSERT_FALSE(x->isConstant(*c));
  ASSERT_FALSE(x->isConstant(x->or2(*c,*d)));
}

TEST_F(ROBDDTest, createvarTest){
  ASSERT_TRUE(x->isVariable(*a));
  ASSERT_TRUE(x->isVariable(*b));
  ASSERT_TRUE(x->isVariable(*c));
  ASSERT_TRUE(x->isVariable(*d));
  ASSERT_FALSE(x->isVariable(x->True()));
  ASSERT_FALSE(x->isVariable(x->False()));
  ASSERT_FALSE(x->isVariable(x->and2(*a,*b)));
}

TEST_F(ROBDDTest, and2Test){
  auto r = x->and2(*a,*b);
  ASSERT_EQ(x->topVar(r),*a);
  ASSERT_EQ(x->coFactorTrue(r),*b);
  ASSERT_EQ(x->coFactorFalse(r),1);
}

TEST_F(ROBDDTest, or2Test){
  auto r = x->or2(*a,*b);
  ASSERT_EQ(x->topVar(r),*a);
  ASSERT_EQ(x->coFactorTrue(r),2);
  ASSERT_EQ(x->coFactorFalse(r),*b);
}

TEST_F(ROBDDTest, cofactorTest){
  auto r = x->or2(*a,x->and2(*b,*c));
  auto rTrue = x->coFactorTrue(r,*c);
  auto rFalse = x->coFactorFalse(r,*c);
  ASSERT_EQ(x->topVar(rTrue),*a);
  ASSERT_EQ(x->coFactorTrue(rTrue),2);
  ASSERT_EQ(x->coFactorFalse(rTrue),*b);
  ASSERT_EQ(x->topVar(rFalse),*a);
  ASSERT_EQ(x->coFactorTrue(rFalse),2);
  ASSERT_EQ(x->coFactorFalse(rFalse),1);
}