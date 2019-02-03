/**** simple spell checker ****/

#include <bits/stdc++.h>

struct ToLower{
    char operator()(char c){
		return std::tolower(c); 
	}
};

// calculate Levenshtein distance between s1 and s2
int d(std::string s1, std::string s2)
{
	int m = int(s1.size()), n = int(s2.size());
	int dp[20][20] = {};
	for(int i = 0; i != m + 1; i++){
		for(int j = 0; j != n + 1; j++){
			dp[i][j] = i + j;
			// insertion
			if(i > 0)	dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + 1);
			// deletion
			if(j > 0)	dp[i][j] = std::min(dp[i][j], dp[i][j - 1] + 1);
			// replacement
			if(i > 0 && j > 0){
				dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1] + 1 * (s1[i - 1] != s2[j - 1]));
			}
			// swap
			if(i > 1 && j > 1){
				if(s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]){
					dp[i][j] = dp[i - 2][j - 2] + 1;
				}
			}
		}
	}
	return dp[m][n];
}

// return int(log_5(n))
int logpoor5(int n){
	int l = 0;
	if(n > 5)        l = 1;
	if(n > 25)       l = 2;
	if(n > 125)      l = 3;
	if(n > 625)      l = 4;
	if(n > 3125)     l = 5;
	if(n > 15625)    l = 6;
	if(n > 78125)    l = 7;
	if(n > 390625)   l = 8;
	if(n > 1953125)  l = 9;
	if(n > 9765625)  l = 10;
	return l;
}

int main(void)
{
	// read dictionary data
	// "en_full.txt" is from https://github.com/hermitdave/FrequencyWords/blob/master/content/2016/en/en_full.txt
	// words are recorded in the form of "(word) (frequency)"
	std::map<std::string, int> dict;
	std::ifstream words("en_full.txt");
	std::string str;
	std::vector<std::string> data;
	while(getline(words, str)){
		int pos = str.find(' ');
		dict[str.substr(0, pos)] = logpoor5(std::atoi(str.substr(pos + 1).c_str()));
	}
	
	// find words with correct spelling
	while(true){
		int score = -100, score_tmp = -100, d_tmp = 0;
		auto itr_max = dict.begin();
		std::cin >> str;
		std::transform(str.begin(), str.end(), str.begin(), ToLower());
		for (auto itr = dict.begin(); itr != dict.end(); itr++){
			// variable score_tmp means
			// p((correct spelling) | (wrong spelling))
			d_tmp = d(str, itr->first);
			score_tmp = 2 * itr->second - 7 * d_tmp;
			if(score_tmp > score && itr->second != 0){
				itr_max = itr;
				score = score_tmp;
			}
		}
		
		std::cout << itr_max->first << " ";
	}
	return 0;
}
