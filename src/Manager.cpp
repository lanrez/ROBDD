//#include <cassert>

#include "Manager.h"


#define DEBUG 1

// Local Variables:
// mode: c++
// End:
using namespace ClassProject;

Manager::Manager() {
  u_table[1] = {False(), False(), False()};
  var_str[1] = "0";
  u_table[2] = {True(), True(), True()};
  var_str[2] = "1";
}

BDD_ID Manager::createVar(const std::string &label) {
  BDD_ID ID = u_table.size() + 1;
  u_table[ID] = {ID, False(), True()};
  var_str[ID] = label;
#if DEBUG
  std::cout << std::endl << "Create variable " + label + " with ID " << ID;
#endif
  return ID;
}

const BDD_ID &Manager::True() {
  const BDD_ID &ID = 2;
  return ID;
}

const BDD_ID &Manager::False() {
  const BDD_ID &ID = 1;
  return ID;
}

bool Manager::isConstant(const BDD_ID f) {
  if (f == True() || f == False())
    return true;
  else
    return false;
}

bool Manager::isVariable(const BDD_ID x) {
  if ((!isConstant(x)) && (var_str.find(x) != var_str.end()))
    return true;
  else
    return false;
}

BDD_ID Manager::topVar(const BDD_ID f) {
  return u_table[f][0];
}
//0todo
BDD_ID Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) {
  if(i == True())
    return t;
  else if(i == False())
    return e;
  else if(t == True() && e == False())
    return i;
  else if(t == e)
    return t;
  /*else if(t == False() && e == True())
    return neg(i);*/
  else {
    for(auto x: c_table){
      if (std::array<BDD_ID,3>{i,t,e} == x.second){
#if DEBUG
        std::cout << std::endl << "Computed found: " << c_table.size();
#endif
        return x.first;}
    }
    /*if (c_table.find(std::array<BDD_ID,3>{i,t,e}) != c_table.end()){
#if DEBUG
      std::cout << std::endl << "Computed found: " << c_table.size();
#endif
      return c_table[std::array<BDD_ID,3>{i,t,e}];}*/

    BDD_ID t_var = topVar(i);
    if (topVar(t) < t_var && isVariable(topVar(t)))
      t_var = topVar(t);
    if (topVar(e) < t_var && isVariable(topVar(e)))
      t_var = topVar(e);
    BDD_ID high = ite(coFactorTrue(i,t_var), coFactorTrue(t,t_var), coFactorTrue(e,t_var));
    BDD_ID low = ite(coFactorFalse(i,t_var), coFactorFalse(t,t_var), coFactorFalse(e,t_var));
    //BDD_ID eval = ite(t_var, high, low);
    if (high == low)
      return high;
    else{
      std::array<BDD_ID, 3> entry = {t_var, low, high};

      for(auto x: u_table) {
        //std::array<BDD_ID, 2> val = {x.second[1], x.second[2]};
        if(entry == x.second) {
          //if (entry == val)
          c_table[x.first] = std::array<BDD_ID,3>{i,t,e};
#if !DEBUG
          std::cout << std::endl << "Computed table size: " << c_table.size();
#endif
          return x.first;
        }
      }

      BDD_ID ID = u_table.size() + 1;
      c_table[ID] = std::array<BDD_ID,3>{i,t,e};
#if !DEBUG
      std::cout << std::endl << "Computed table size: " << c_table.size();
#endif
      u_table[ID] = entry;
      return ID;
    }

    //std::array<BDD_ID, 2> entry = {low, high};

  }
}

BDD_ID Manager::coFactorTrue(const BDD_ID f, BDD_ID x) {
  if(isConstant(f))
    return f;
  else if (isConstant(x))
    return f;
  else if (topVar(f) == x)
    return coFactorTrue(f);
  else if (topVar(f) > x)
    return f;
  else {
    //return f; //todo
    BDD_ID T = coFactorTrue(coFactorTrue(f),x);
    BDD_ID E = coFactorTrue(coFactorFalse(f),x);
    return ite(topVar(f), T, E);
  }
}
//todo
BDD_ID Manager::coFactorFalse(const BDD_ID f, BDD_ID x) {
  if(isConstant(f))
    return f;
  else if (isConstant(x))
    return f;
  else if (topVar(f) == x)
    return coFactorFalse(f);
  else if (topVar(f) > x)
    return f;
  else {
    BDD_ID T = coFactorFalse(coFactorTrue(f),x);
    BDD_ID E = coFactorFalse(coFactorFalse(f),x);
    return ite(topVar(f), T, E);
  }
}

BDD_ID Manager::coFactorTrue(const BDD_ID f) {
  return u_table[f][2];
}

BDD_ID Manager::coFactorFalse(const BDD_ID f) {
  return u_table[f][1];
}

BDD_ID Manager::and2(const BDD_ID a, const BDD_ID b) {
#if DEBUG
  std::cout << std::endl << "and(" << a << "," << b << ")";
#endif
  return ite(a, b,1);
}

BDD_ID Manager::or2(const BDD_ID a, const BDD_ID b) {
#if DEBUG
  std::cout << std::endl << "or(" << a << "," << b << ")";
#endif
  return ite(a, 2, b);
}

BDD_ID Manager::xor2(const BDD_ID a, const BDD_ID b) {
#if DEBUG
  std::cout << std::endl << "xor(" << a << "," << b << ")";
#endif
  return ite(a, neg(b), b);
}
//todo
BDD_ID Manager::neg(const BDD_ID a) {
#if DEBUG
  std::cout << std::endl << "not(" << a << ")";
#endif
  return ite(a,False(),True());
  /*if (a == True())
    return False();
  else if (a == False())
    return True();
  else {
    BDD_ID t_var = topVar(a);
    BDD_ID high = coFactorFalse(a);
    BDD_ID low = coFactorTrue(a);

    std::array<BDD_ID,3> entry = {t_var, low, high};
    //std::array<BDD_ID, 2> entry = {low, high};

    for (auto x: r_table) {
      //std::array<BDD_ID, 2> val = {x.second[1], x.second[2]};
      if (entry == x.second)
        return x.first;
    }

    BDD_ID ID = r_table.size() + 1;
    r_table[ID] = entry;
    return ID;
  }*/
}

BDD_ID Manager::nand2(const BDD_ID a, const BDD_ID b) {
  return neg(and2(a, b));
}

BDD_ID Manager::nor2(const BDD_ID a, const BDD_ID b) {
  return neg(or2(a, b));
}

std::string Manager::getTopVarName(const BDD_ID &root) {
  BDD_ID t_var = topVar(root);
  return var_str[t_var];
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
  nodes_of_root.emplace(root);
  if(root > 2) {
    findNodes(coFactorTrue(root), nodes_of_root);
    findNodes(coFactorFalse(root), nodes_of_root);
  }

}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {
  std::set<BDD_ID> nodes;
  findNodes(root, nodes);
  for(auto x: nodes){
    vars_of_root.emplace(topVar(x));
  }
#if DEBUG
  printR_table();
#endif
}

size_t Manager::uniqueTableSize() {
  return u_table.size();
}

void Manager::printR_table() {
  std::cout << "BDD ID\tHigh\tLow\t\tTop Var" << std::endl;
  //std::cout << "BDD ID\tLabel\tHigh\tLow\tTop Var" << std::endl;
  for(auto x : u_table){
    std::cout << x.first << "\t\t" << x.second[2] << "\t\t" << x.second[1] << "\t\t" << x.second[0] << std::endl;
    //std::cout << x.first << "\t\t" << var_str[x.first] << "\t\t"<< x.second[2] << "\t\t" << x.second[1] << "\t\t" << x.second[0] << std::endl;
  }

  std::cout << "size_u: " << u_table.size() << std::endl;
  std::cout << "max_bucket_u: " << u_table.bucket_count() << std::endl;
  std::cout << "size_c: " << c_table.size() << std::endl;
  std::cout << "max_bucket_c: " << c_table.bucket_count() << std::endl;

}

