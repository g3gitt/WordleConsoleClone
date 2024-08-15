#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<random>
#include<algorithm>
#include<cctype>

bool vector_contains_word(const std::vector<std::string>& vec, const std::string& word) {
	for (const auto& w : vec) {
		if (w == word) {
			return true;
		}
	}
	return false;
}
std::vector<int>fill_buckets(const std::string& word) {
	std::vector<int>buckets(26, 0);
	for (char c : word) {
		buckets[c - 'a']++;
	}
	return buckets;
}
int score_match(const std::string& word1, const std::string& word2, std::string& updated, std::string& letter) {
	const auto buckets1 = fill_buckets(word1);
	const auto buckets2 = fill_buckets(word2);
	int k = 0;
	int score = 0;
	for (int i = 0; i < 26; i++) {
		score += std::min(buckets1[i], buckets2[i]);
		if ((buckets2[i] == buckets1[i] && buckets2[i] == 1) || (buckets2[i] == 2 && buckets1[i] == 1) || (buckets2[i] == 1 && buckets1[i] == 2)) {
			char ch = i + 'a';
			letter[k++] = ch;

		}

	}
	for (int i = 0; i < 5; i++) {
		if (word1[i] == word2[i]) {
			score++;
			updated[i] = word1[i];
		}
	}
	return score;

}

int main() {
	std::vector<std::string>five_words;
	{
		//scope for the file to close after pushing the words into the vector
		std::ifstream five_word_file("sgb-words.txt");
		for (std::string line; std::getline(five_word_file, line);) {
			if (line.empty()) {
				continue;
			}
			five_words.push_back(line);
		}
	}
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int>dist(0, five_words.size() - 1);
	const std::string target = five_words[dist(rng)];


	while (true) {
		std::string letter = "-----";
		std::string updated = "_____";

		std::cout << "Guess a five letter word: ";
		std::string guess;
		std::getline(std::cin, guess);
		for (auto& c : guess) {
			c = std::tolower(c);
		}
		if (guess.size() != 5) {
			std::cout << "Five letter words only" << std::endl;
			continue;
		}
		if (!vector_contains_word(five_words, guess)) {
			std::cout << guess << "? That's Not a word" << std::endl;
			continue;
		}
		const int score = score_match(guess, target, updated, letter);
		if (score == 10) {
			std::cout << "Done.GOOD" << std::endl;
			break;
		}
		else {
			std::cout << "Your score is " << score << ", Guess: " << updated << " Jumbled: " << letter << std::endl;
			//WALTZ VIBEX CHUNK FJORD GYMPS
			continue;

		}

	}//while loop end


	std::cin.get();
	return 0;
}