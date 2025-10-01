#include <iostream>

using namespace std;

bool ECIsIsomorphic(string s, string t) {
	int i=0;
	while(s[i] != '\0' && t[i] != '\0'){
		char l1 = s[i];
		char l2 = t[i];
		int j=0;
		while(s[j] != '\0' && t[j] != '\0'){
			if(l1 == s[j] && l2 != t[j]) { return false; }
			if(l1 != s[j] && l2 == t[j]) { return false; }

			j++;
		}

		i++;
	}
	return true;
}
