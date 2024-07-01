//
// Created by Eros Chan on 06/11/2023.
//

#pragma once

#include <string>
#include <condition_variable>

using std::string;
using std::mutex;
using std::unique_lock;
using std::condition_variable;

class ResultatCalcul {

  string result;
  mutex m;
  condition_variable cond;
  bool define;
public:
  ResultatCalcul() : define(false) {}

  // Rend la valeur stockée dès qu'elle est disponible
  // Invocation bloque l'appelant si nécessaire jusqu'à ce que la valeur devienne disponible
  const string & getResult() const {
    unique_lock<mutex> lg(m);

    while (!define) {
      cond.wait(lg);
    }
    return result;
  }

  // Est vrai si et seulement si la valeur a déjà été affectée i.e. getResult n'est plus bloquant
  bool isSet() const {
    unique_lock<mutex> lg(m);
    return this->define == true;
  }

  // Permet de positionner la valeur stockée,
  // débloque les threads éventuellement bloqués sur getResult
  // On ne doit invoquer setResult qu'une seule fois sur une instance donnée de ResultatCalcul,
  // si on l'invoque de nouveau cela n'a aucun effet
  void setResult(const string & res) {
    unique_lock<mutex> lg(m);

    // On ne doit invoquer setResult qu'une seule fois sur une instance donnée, si on l'invoque de nouveau cela n'a aucun effet
    if (define) return;

    // Positionne la valeur stockée
    result = res;

    // A été positionné
    define = true;

    // Débloque les threads éventuellement bloqués sur getResult
    cond.notify_all();
  }

};
