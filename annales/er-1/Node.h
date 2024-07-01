//
// Created by Eros Chan on 06/11/2023.
//

#pragma once

#include <string>
#include <ostream>

using std::string;

class Node {

  string value;
  Node *left;
  Node *right;

public:

  Node(const string & value) : value(value), left(nullptr), right(nullptr) {}

  /**
   * Essaie d'insérer la string s
   * @param s   string à insérer
   * @returns   true si l'insertion a eu lieu
   *            false sinon
   */
  bool insert(const string & s) {
    // Le noeud courant porte déjà la string
    if (value == s) {
      return false;
    }

    // Sous-arbre gauche
    else if (value < s) {

      // Si le sous-arbre gauche est un arbre vide
      if (left == nullptr) {

        // On créé un nouveau noeud qui contient le mot
        left = new Node(s);
        return true;
      }

      // Sinon, on réalise notre récursion sur le sous-arbre gauche
      else {
        return left->insert(s);
      }
    }

    // Sous-arbre droit
    else if (value > s) {

      // Si le sous-arbre droit est un arbre vide
      if (right == nullptr) {

        // On créé un nouveay noeud qui contient le mot
        right = new Node(s);
        return true;
      }

      // Sinon, on réalise notre récursion sur le sous-arbre droit
      else {
        return right->insert(s);
      }
    }
  }

  // Constructeur par copie
  Node(const Node & other) {
    value = other.value;
    if (other.left) left = new Node(*other.left);
    else left = nullptr;
    if (other.right) right = new Node(*other.right);
    else right = nullptr;
  }

  // Un destructeur
  ~Node() {
    delete left;
    delete right;
  }

  friend std::ostream & operator<<(std::ostream & os, const Node & node) {
    if (node.left) os << *node.left;
    os << node.value << std::endl;
    if (node.right) os << *node.right;
  }

};