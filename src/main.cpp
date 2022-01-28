/*=============================================================================
    Written by Carolina P. Nogueira (2016)
=============================================================================*/


#include <iostream>
#include <string>
#include "Manager.h"


int main(int argc, char* argv[])
{
  //std::cout << "Nothing implemented, yet" << std::endl;

  ClassProject::Manager x = ClassProject::Manager();
  ClassProject::BDD_ID y;
  std::set<ClassProject::BDD_ID> nodes, vars;

  auto a = x.createVar("a");
  auto b = x.createVar("b");
  auto c = x.createVar("c");
  auto d = x.createVar("d");

  auto aob = x.or2(a,b);

  auto cnd = x.and2(c,d);
  auto e = x.and2(aob,cnd);

  auto t1 = x.and2(c,d);
  auto t2 = x.and2(a,b);
  auto t3 = x.or2(t2, cnd);
  auto f = x.or2 (x.and2(a,b), x.and2(c,d));

  auto g = x.neg(3);
  auto h = x.neg(4);

  auto i = x.neg(2);
  auto j = x.neg(1);


  auto k = x.neg(x.neg(a));

  auto z = x.isVariable(a);

  auto l = x.or2(a,a);
  auto m = x.and2(b, b);

  auto bnc = x.and2(b,c);
  auto aobnc = x.or2(a,bnc);
  //y = x.coFactorTrue(aobnc,c);

  y = x.neg(x.False());

  std::cout << "y is " << y << std::endl;

  x.printR_table();

  x.findNodes(e, nodes);
  x.findVars(e, vars);

  for (auto x: nodes){
    std::cout << x << " ";
  }

}
