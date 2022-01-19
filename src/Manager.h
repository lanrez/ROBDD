// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Written by Markus Wedler 2014

#ifndef mwBDD_H
#define mwBDD_H

#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include "ManagerInterface.h"

namespace ClassProject {

  struct ArrayHasher{
    size_t operator() (const std::array<BDD_ID,3> &a) const{
      size_t h = 0;

      for(auto e: a){
        h ^= std::hash<BDD_ID>{}(e) + 0x9e3779b9 + (h << 6) + (h >> 2);
      }
      return h;
    }
  };

  class Manager :public ManagerInterface{
      public:
      Manager();

      ~Manager() = default;

      /**
       *
       * @param label
       * @return
       */
      BDD_ID createVar(const std::string &label) override;

      /**
       *
       * @return
       */
      const BDD_ID &True() override;

      /**
       *
       * @return
       */
      const BDD_ID &False() override;

      /**
       *
       * @param f
       * @return
       */
      bool isConstant(const BDD_ID f) override;

      /**
       *
       * @param x
       * @return
       */
      bool isVariable(const BDD_ID x) override;

      /**
       *
       * @param f
       * @return
       */
      BDD_ID topVar(const BDD_ID f) override;

      /**
       *
       * @param i
       * @param t
       * @param e
       * @return
       */
      BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) override;

      /**
       *
       * @param f
       * @param x
       * @return
       */
      BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x) override;

      /**
       *
       * @param f
       * @param x
       * @return
       */
      BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x) override;

      /**
       *
       * @param f
       * @return
       */
      BDD_ID coFactorTrue(const BDD_ID f) override;

      /**
       *
       * @param f
       * @return
       */
      BDD_ID coFactorFalse(const BDD_ID f) override;

      /**
       *
       * @param a
       * @param b
       * @return
       */
      BDD_ID and2(const BDD_ID a, const BDD_ID b) override;

      /**
       *
       * @param a
       * @param b
       * @return
       */
      BDD_ID or2(const BDD_ID a, const BDD_ID b) override;

      /**
       *
       * @param a
       * @param b
       * @return
       */
      BDD_ID xor2(const BDD_ID a, const BDD_ID b) override;

      /**
       *
       * @param a
       * @return
       */
      BDD_ID neg(const BDD_ID a) override;

      /**
       *
       * @param a
       * @param b
       * @return
       */
      BDD_ID nand2(const BDD_ID a, const BDD_ID b) override;

      /**
       *
       * @param a
       * @param b
       * @return
       */
      BDD_ID nor2(const BDD_ID a, const BDD_ID b) override;

      /**
       *
       * @param root
       * @return
       */
      std::string getTopVarName(const BDD_ID &root) override;

      /**
       *
       * @param root
       * @param nodes_of_root
       */
      void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

      /**
       *
       * @param root
       * @param vars_of_root
       */
      void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

      /**
       *
       * @return
       */
      size_t uniqueTableSize() override;

      void printR_table();

      private:

      std::unordered_map<BDD_ID, std::array<BDD_ID,3>> u_table;
      std::unordered_map<BDD_ID, std::string> var_str;
      std::unordered_map<std::array<BDD_ID,3>, BDD_ID, ArrayHasher> c_table;
      std::map<std::array<BDD_ID,3>, BDD_ID> c_table2;

    };

}
#endif

// Local Variables:
// mode: c++
// End:
