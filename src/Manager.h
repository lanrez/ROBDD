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
/**
 * Hashing function for array[3]
 */
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
       * Creates a variable and adds its ID to the unique table
       * @param label name of variable
       * @return ID of variable
       */
      BDD_ID createVar(const std::string &label) override;

      /**
       * Returns the terminal true node
       * @return ID of true node
       */
      const BDD_ID &True() override;

      /**
       * Returns the terminal false node
       * @return ID of false node
       */
      const BDD_ID &False() override;

      /**
       * Checks if ID is terminal
       * @param f input ID
       * @return true if f is a terminal node
       */
      bool isConstant(const BDD_ID f) override;

      /**
       * Checks if ID is a variable
       * @param x input ID
       * @return true if x is a variable
       */
      bool isVariable(const BDD_ID x) override;

      /**
       * Returns the top varible of ID
       * @param f input ID
       * @return returns the top variable of f
       */
      BDD_ID topVar(const BDD_ID f) override;

      /**
       * Performs the ite operation
       * @param i input if
       * @param t input then
       * @param e input else
       * @return The ID of ite(i,t,e)
       */
      BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) override;

      /**
       * Returns the ID of a function when variable is set as true
       * @param f input function
       * @param x input variable
       * @return returns the ID when variable x is set as true in function f
       */
      BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x) override;

      /**
       * Returns the ID of a function when variable is set as false
       * @param f input function
       * @param x input variable
       * @return returns the ID when variable x is set as false in function f
       */
      BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x) override;

      /**
       * Returns the ID of function when the top variable is true
       * @param f input function
       * @return returns the ID when the top variable is set as true in function f
       */
      BDD_ID coFactorTrue(const BDD_ID f) override;

      /**
       * Returns the ID of function when the top variable is false
       * @param f input function
       * @return returns the ID when the top variable is set as false in function f
       */
      BDD_ID coFactorFalse(const BDD_ID f) override;

      /**
       * Performs the AND operation
       * @param a input a
       * @param b input b
       * @return returns the ID of (a AND b)
       */
      BDD_ID and2(const BDD_ID a, const BDD_ID b) override;

      /**
       * Performs the OR operation
       * @param a input a
       * @param b input b
       * @return returns the ID of (a OR b)
       */
      BDD_ID or2(const BDD_ID a, const BDD_ID b) override;

      /**
       * Performs the XOR operation
       * @param a input a
       * @param b input b
       * @return returns the ID of (a XOR b)
       */
      BDD_ID xor2(const BDD_ID a, const BDD_ID b) override;

      /**
       * Performs the NOT operation
       * @param a input a
       * @return returns the ID of NOT(a)
       */
      BDD_ID neg(const BDD_ID a) override;

      /**
       * Performs the NAND operation
       * @param a input a
       * @param b input b
       * @return returns the ID of NOT(a AND b)
       */
      BDD_ID nand2(const BDD_ID a, const BDD_ID b) override;

      /**
       * Performs the NOR operation
       * @param a input a
       * @param b input b
       * @return returns the ID of NOT(a OR b)
       */
      BDD_ID nor2(const BDD_ID a, const BDD_ID b) override;

      /**
       * Return the name of the top variable of ID
       * @param root input ID
       * @return returns name of the top varible of root
       */
      std::string getTopVarName(const BDD_ID &root) override;

      /**
       * Return all IDs that can be accessed from a root node
       * @param root input root note
       * @param nodes_of_root set to contain all nodes accessible from root node
       */
      void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

      /**
       * Return all top variables that can be accessed from a root node
       * @param root input root node
       * @param vars_of_root set to contain all top variables from the node
       */
      void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

      /**
       * Return the size of the unique table
       */
      size_t uniqueTableSize() override;

      /**
       * Displays the unique table
       */
      void printR_table();

      private:

    /**
     * Hash table as the Unique table
     * Key: Unique ID nodes
     * Values: Top, Low and High ID for the key
     */
    std::unordered_map<BDD_ID, std::array<BDD_ID,3>> u_table;
    /**
     * Hash table as Variable table
     * Key: Unique ID nodes
     * Values: Variable names of the ID nodes
     */
    std::unordered_map<BDD_ID, std::string> var_str;
    /**
     * Hash table as the Computed table
     * Key: ID nodes
     * Values: {i,t,e} triple that results in ID
     */
      std::unordered_map<std::array<BDD_ID,3>, BDD_ID, ArrayHasher> c_table;
      //std::unordered_map<BDD_ID, std::array<BDD_ID,3>> c_table;
      std::unordered_map<std::array<BDD_ID,3>, BDD_ID, ArrayHasher> u_t2;


    };

}
#endif

// Local Variables:
// mode: c++
// End:
