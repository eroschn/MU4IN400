//
// Created by Eros Chan on 01/10/2023.
//

#ifndef TME2_HASHMAP_H
#define TME2_HASHMAP_H

#include <ostream>
#include <vector>
#include <forward_list>

template <typename K, typename V>
class HashMap {

private:
  class Entry {
  public:
    const K key;
    V value;

    Entry(const K & k, const V & v) : key(k), value(v) {}
  };

public:
  std::vector<std::forward_list<Entry>> buckets;

  HashMap(size_t hashmap_size) {
    for (int i = 0; i < hashmap_size; i++) {
      std::forward_list<Entry> p{};
      buckets.push_back(p);
    }
  }

  /**
   * Rend l'adresse de la valeur associée à la clé
   * @param key clé
   * @return adresse de la clé si existante
   *         nullptr sinon
   */
  V* get(const K & key) {
    size_t h = std::hash<K>()(key);
    size_t target = h % buckets.size();

    for (Entry &e : buckets[target]) {
      if (e.key == key) {
        return &e.value;
      }
    }

    return nullptr;
  }

  /**
   * Ajoute l'association (key, value) dans la table de hachage
   * @param key clé
   * @param value valeur
   * @return true si mise à jour
   *         false si insertion
   */
  bool put(const K & key, const V & value) {
    size_t h = std::hash<K>()(key);
    size_t target = h % buckets.size();

    for (Entry &e : buckets[target]) {
      if (e.key == key) {
        // std::cout << "existe déjà, màj de " << e.value << " à " << value << std::endl;
        e.value = value;
        return true;
      }
    }

    Entry new_entry {key, value};
    buckets[target].push_front(new_entry);
    // std::cout << "n'existe pas, insertion de (" << key << ", " << value << ")" << std::endl;
    return false;
  }
};


#endif //TME2_HASHMAP_H
