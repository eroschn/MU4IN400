# PSCR

## TME-2 : Conteneurs, Map, Lib Standard

### 1.1. `std::vector`, `std::pair`

> **Question 1**
> 
> Exécutez le programme sur le fichier `WarAndPeace.txt` fourni. Combien y a-t-il de mots ?

Il y a **566193 mots** trouvés en $2811ms$.

> **Question 2**
> 
> Modifiez le programme pour compter le nombre de mots différents que contient le texte. Pour cela on propose dans un premier temps de stocker tous les mots rencontrés dans un vecteur, et de traverser ce vecteur à chaque nouveau mot rencontré pour vérifier s'il est nouveau ou pas. Exécutez le programme sur le fichier `WarAndPeace.txt` fourni. Combien y a-t-il de mots différents ?

On a le code suivant pour compter le nombre de mots différents que contient le texte :
```cpp
vector<string> words_vector;

// variable vérifiant l'appartenance dans le vecteur
bool exists = false;

for (const auto &i : words_vector) {
  if (i == word) {
    exists = true;
    break;
  }
}

// on vérifie que le mot n'a jamais été rencontré
if (!exists) {
  nombre_lu++;
  words_vector.push_back(word);
}
```

I y a **20333 mots** trouvés en $23003ms$.

> **Question 3**
> 
> Modifiez le programme pour qu'il calcule le nombre d'occurrences de chaque mot. Pour cela, on adaptera le code précédent pour utiliser un vecteur qui stocke des `pair<string, int>` au lieu de stocker juste des string. Afficher le nombre d'occurrences des mots "war", "peace" et
"toto".

On a le code suivant qui calcule le nombre d'occurences de chaque mot :
```cpp
vector <pair<string, int>> words_occurences;

// variable vérifiant l'appartenance dans le vecteur
bool exists = false;

for (auto &i : words_occurences) {
  if (i.first == word) {
    i.second++;
    exists = true;
    break;
  }
}

// on vérifie que le mot n'apparaît pas et on l'ajoute
if (!exists) {
  pair<string, int> p{word, 1};
  words_occurences.push_back(p);
};
nombre_lu++;

// ...

for (auto &p: words_occurences) {
  if (p.first == "war") cout << "war_occurences=" << p.scond << endl;
  else if (p.first == "peace") cout << "peace_occurences=" << p.scond << endl;
  else if (p.first == "toto") cout << "toto_occurences=" << p.scond << endl;
}
```

| **Mot** | **Occurences** |
|---------|----------------|
| "war"   | $298$          |
| "peace" | $114$          |
| "toto"  | $0$            |


> **Question 4**
> 
> Que penser de la complexité algorithmique de ce programme ? Quelles autres structures de données de la lib standard aurait-on pu utiliser ?

La complexité algorithmique laisse à désirer. En effet, on est contraint de parcourir tous les éléments du `vector<pair<string, int>>` pour :
- mettre à jour le nombre d'occurrence d'un mot : pour vérifier s'il n'est pas déjà dans le `vector<pair<string, int>>`
- chercher le nombre d'occurence d'un mot : on aimerait avoir une complexité constante
- de même, si on souhaite supprimer une `pair<string, int>`, on est obligé de parcourir tout le `vector<pair<string, int>>` : on préférait une complexité constante

Pour palier à ces problèmes, on aurait pu utiliser une table de hachage (HashMap).

### 1.2. Table de Hash

> **Question 5**
> 
> En suivant les indications du TD 2, implanter la classe générique `HashMap<K, V>`.

Cf. code source : `./HashMap.h`.

### 1.3. Mots les plus fréquents

> **Question 6**
> 
> Utiliser une table de hash `HashMap<string, int>` associant des entiers (le nombre d'occurrence) aux mots, et reprendre les questions où l'on calculait de nombre d'occurrences de mots avec cette nouvelle structure de donnée.

Dans la boucle `while`, on compte et on met à jour les mots de la manière suivante :
```cpp
// on récupère le nombre d'occurence de word
int *value = words_map.get(word);

// on vérifie si le mot existe déjà
if (value != nullptr) {
  // si true : on incrémente le compteur
  words_map.put(word, (*value) + 1);
} else {
  // si false : on insert le mot dans la table de hachage
  words_map.put(word, 1);
}
```

> **Question 7**
> 
> Après avoir chargé le livre, initialiser un `std::vector<pair<string, int>>`, par copie des entrées dans la table de hash. On pourra utiliser le contructeur par copie d'une range : `vector(InputIterator first, InputIterator last)`.

On initialise un `std::vector<pair<string, int>>` comme ceci :
```cpp
std::vector<pair<string, int>> vectory_copy {
    std::begin(words_map.buckets),
    std::end(words_map.buckets)
  };
```

> **Question 8**
> 
> Ensuite trier ce vecteur par nombre d'occurrences décroissantes à l'aide de `std::sort` et afficher les dix mots les plus fréquents. 
> 
> `std::sort` prend les itérateurs de début et fin de la zone à trier, et un prédicat binaire. Voir l'exemple
suivant.

Pour trier ce vecteur par nombre d'occurences décroissantes :
```cpp
std::sort(vectory_copy.begin(),
            vectory_copy.end(),
            [](const pair<string, int> & a, const pair<string, int> & b) {
    return a.second > b.second;
  });

  int cpt = 0;
  for (const auto & e : vectory_copy) {
    cout << cpt << ". " << e.first << " : " << e.second << endl;

    if (++cpt > 10) break;
  }
```


> **Question 9**
> 
> S'il vous reste du temps, remplacer les `forward_list` et `vector` utilisés par votre classe HashMap par vos propres implantations `List`, `Vector` comme discuté en TD. Ajouter les opérations nécessaires au fonctionnement de votre table de hash dans ces classes.

Facultatif.
