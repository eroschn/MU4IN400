#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

#include "HashMap.h"

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("/tmp/WarAndPeace.txt");

  HashMap<string, int> words_map {50000};
	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;

    int *value = words_map.get(word);

    if (value != nullptr) {
      words_map.put(word, (*value) + 1);
    } else {
      words_map.put(word, 1);
    }

	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();

  cout << "Parsing took "
            << duration_cast<milliseconds>(end - start).count()
            << "ms.\n";

  cout << "Found a total of " << nombre_lu << " words." << endl;

  cout << "war_occurences=" << *words_map.get("war") << endl;
  cout << "peace_occurences=" << *words_map.get("peace") << endl;
  cout << "toto_occurences=" << *words_map.get("toto") << endl;

  std::vector<pair<string, int>> vectory_copy {
    std::begin(words_map.buckets),
    std::end(words_map.buckets)
  };

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

  return 0;
}


