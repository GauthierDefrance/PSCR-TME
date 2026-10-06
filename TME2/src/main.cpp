#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>
#include <algorithm>
#include <vector>
#include "FreqMap.h"

// helper to clean a token (keep original comments near the logic)
static std::string cleanWord(const std::string& raw) {
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	static const std::regex re( R"([^a-zA-Z])");
	// élimine la ponctuation et les caractères spéciaux
	std::string w = std::regex_replace(raw, re, "");
	// passe en lowercase
	std::transform(w.begin(), w.end(), w.begin(), ::tolower);
	return w;
}

#include <unordered_map> // Ne pas oublier cet include

// Recherche ultra-rapide avec unordered_map
static int searchWordFreq(const std::string& word, const std::unordered_map<std::string, int>& wordCounts) {
	auto it = wordCounts.find(word);
	if (it != wordCounts.end()) {
		return it->second;
	}
	return 0;
}

static int searchWordFreq(const std::string& word, const std::vector<WordCount>& pairs) {
	for (const auto& p : pairs) {
		if (p.first == word) return p.second;
	}
	return 0;
}

static void sortAndPrintTop(const std::vector<WordCount>& pairs, int n) {
	auto sorted = pairs;  // copie, on ne modifie pas l'original
	std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;  // ici le compteur est en .second
	});

	std::cout << "The ten most commons words" << std::endl;
	int limit = std::min(n, static_cast<int>(sorted.size()));
	for (int i = 0; i < limit; i++) {
		std::cout << sorted[i].first << " : " << sorted[i].second << std::endl;
	}
}

// Tri et affichage (on copie dans un vecteur temporaire pour trier par valeur)
static void sortAndPrintTop(const std::unordered_map<std::string, int>& wordCounts, int n)
{
	// Copie de la map vers un vecteur de paires (fréquence, mot)
	std::vector<std::pair<int, std::string>> vec;
	vec.reserve(wordCounts.size());
	for (const auto& [word, count] : wordCounts) {
		vec.emplace_back(count, word);
	}

	// Tri par ordre décroissant de la fréquence
	std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
		return a.first > b.first;
	});

	std::cout << "The ten most commons words" << std::endl;

	int limit = std::min(n, static_cast<int>(vec.size()));
	for (int i = 0; i < limit; i++)
	{
		std::cout << vec[i].second << " : " << vec[i].first << std::endl;
	}
}


static bool alreadySeen(const std::string& word, const std::vector<std::string>& words) {
	for (const auto& w : words) {
		if (word == w) return true;
	}
	return false;
}

static bool alreadySeenAndIncrement(const std::string& word, std::vector<std::pair<int, std::string>>& words) {
	for (auto& w : words) {
		if (word == w.second)
		{
			w.first++;
			return true;
		}
	}
	return false;
}


static void sortAndPrintTop(const std::vector<std::pair<int, std::string>> &words, int n)
{
	auto sortedWords = words;

	// 2. On trie la copie
	std::sort(sortedWords.begin(), sortedWords.end(), [](const auto& a, const auto& b) {
		return a.first > b.first; // Plus grand en premier
	});

	std::cout << "The ten most commons words" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << sortedWords[i].second << " : " << sortedWords[i].first << std::endl;
	}
}


static int searchWordFreq(const std::string& word, const std::vector<std::pair<int, std::string>>& words)
{
	for (auto& w : words) {
		if (word == w.second)
		{
			return w.first;
		}
	}
	return 0;
}


int main(int argc, char** argv) {
	using namespace std;
	using namespace std::chrono;

	// Allow filename as optional first argument, default to project-root/WarAndPeace.txt
	// Optional second argument is mode (e.g. "count" or "unique").
	string filename = "../WarAndPeace.txt";
	string mode = "freqmap";
	if (argc > 1) filename = argv[1];
	if (argc > 2) mode = argv[2];

	ifstream input(filename);
	if (!input.is_open()) {
		cerr << "Could not open '" << filename << "'. Please provide a readable text file as the first argument." << endl;
		cerr << "Usage: " << (argc>0?argv[0]:"countword") << " [path/to/textfile]" << endl;
		return 2;
	}
	cout << "Parsing " << filename << " (mode=" << mode << ")" << endl;

	auto start = steady_clock::now();

	// prochain mot lu
	string word;

	if (mode == "count") {
		size_t nombre_lu = 0;

		// default counting mode: count total words
		while (input >> word) {
			// élimine la ponctuation et les caractères spéciaux
			word = cleanWord(word);
			// un token sans aucune lettre (e.g. "--" ou "1812") devient vide : on l'ignore
			if (word.empty()) continue;

			// word est maintenant "tout propre"
			if (nombre_lu % 100 == 0)
			{
				// on affiche un mot "propre" sur 100
				cout << nombre_lu << ": "<< word << endl;
			}
			nombre_lu++;
		}
	input.close();
	cout << "Finished parsing." << endl;
	cout << "Found a total of " << nombre_lu << " words." << endl;

	} else if (mode == "unique") {
		// skeleton for unique mode
		// before the loop: declare a vector "seen"

		std::vector<string> uniqueWords;

		uniqueWords.reserve(25000);
		int i = 0;

		while (input >> word) {
			// élimine la ponctuation et les caractères spéciaux
			word = cleanWord(word);
			if (word.empty()) continue;

			// Skip if not new
			if (alreadySeen(word, uniqueWords)) continue;

			i++;
			uniqueWords.push_back(word);
			std::cout << word << ":" << i << std::endl;

		}
	input.close();
	cout << "Found " << uniqueWords.size() << " unique words." << endl;

	} else if (mode == "freq")
	{

		std::vector<std::pair<int, std::string>> uniqueWords;
		uniqueWords.reserve(25000);

		while (input >> word) {
			// élimine la ponctuation et les caractères spéciaux
			word = cleanWord(word);
			if (word.empty()) continue;

			// Skip if not new
			if (alreadySeenAndIncrement(word, uniqueWords)) continue;

			uniqueWords.emplace_back(1, word);
		}
		input.close();
		cout << "Found " << uniqueWords.size() << " unique words." << endl;

		cout << "Printing words and their frequency " << endl;

		cout << "war :" << searchWordFreq("war", uniqueWords) << endl;
		cout << "peace :" << searchWordFreq("peace", uniqueWords) << endl;
		cout << "toto :" << searchWordFreq("toto", uniqueWords) << endl;


		sortAndPrintTop(uniqueWords, 10);

		input.close();
	}


	else if (mode == "freqstd") {

		std::unordered_map<std::string, int> wordCounts;
		// Optionnel : réserver de l'espace pour éviter les rehachages fréquents
		wordCounts.reserve(25000);

		while (input >> word) {
			// Élimine la ponctuation et les caractères spéciaux
			word = cleanWord(word);
			if (word.empty()) continue;

			// Insère le mot s'il n'existe pas (valeur 0 par défaut) et l'incrémente
			wordCounts[word]++;
		}
		input.close();

		cout << "Found " << wordCounts.size() << " unique words." << endl;

		cout << "Printing words and their frequency " << endl;

		cout << "war :" << searchWordFreq("war", wordCounts) << endl;
		cout << "peace :" << searchWordFreq("peace", wordCounts) << endl;
		cout << "toto :" << searchWordFreq("toto", wordCounts) << endl;


		sortAndPrintTop(wordCounts, 10);



	}

	else if (mode == "freqmap") {
		FreqMap fm(25000);
		while (input >> word) {
			word = cleanWord(word);
			if (word.empty()) continue;
			fm.incrementFrequency(word);
		}
		auto pairs = fm.toKeyValuePairs();
		std::sort(pairs.begin(), pairs.end(),
				  [](const auto& a, const auto& b) { return a.second > b.second; });

		cout << "Found " << pairs.size() << " unique words." << endl;

		cout << "war :" << searchWordFreq("war", pairs) << endl;
		cout << "peace :" << searchWordFreq("peace", pairs) << endl;
		cout << "toto :" << searchWordFreq("toto", pairs) << endl;

		input.close();
	}



	else {
		// unknown mode: print usage and exit
		cerr << "Unknown mode '" << mode << "'. Supported modes: count, unique, freq" << endl;
		input.close();
		return 1;
	}

	// print a single total runtime for successful runs
	auto end = steady_clock::now();
	cout << "Total runtime (wall clock) : " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

	return 0;
}



