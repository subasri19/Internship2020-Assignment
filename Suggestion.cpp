#include<bits/stdc++.h> 
using namespace std; 


// declarations
const int size = 100;
int c=1;
std::map<char, int> charIndex;
std::map<string, int> frequency;
std::multiset< pair<int, string> > solution;


//structure for the trie
struct TrieNode { 
	struct TrieNode *children[size]; 
	bool isWordEnd; 
}; 


// creating the trie node
struct TrieNode *getNode(void) { 
	struct TrieNode *pNode = new TrieNode; 
	pNode->isWordEnd = false; 

	for (int i = 0; i < size; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 


// inserting the characters of teh string into the trie
map<char, int> insert(struct TrieNode *root, string key){
	struct TrieNode *p = root; 
	map<char, int>:: iterator itr;
	int index;

	for (int level = 0; level < key.length(); level++) {
		//checking if the character is already present in the tree 
		if((charIndex.find(key[level]))==charIndex.end()){
			charIndex.insert({key[level],c});
			index=c;
			c++;	 
		}
		else{
			index=charIndex.find(key[level])->second;
		}
		if (!p->children[index]) 
			p->children[index] = getNode(); 
		p = p->children[index]; 
	} 
	p->isWordEnd = true; 
	return charIndex;
} 


// returns 0 if the node has a child
bool isLastNode(struct TrieNode* root) { 
	for (int i = 0; i < size; i++) 
		if (root->children[i]) 
			return 0; 
	return 1; 
} 


// recursive function to store the suggestions in the solution multiset
void suggestionsRec(struct TrieNode* root, string query){
	map<char,int> :: iterator it;
	char temp; 

	if (root->isWordEnd)
		solution.insert(make_pair(frequency[query],query));

	if (isLastNode(root)) 
		return; 

	for (int i = 0; i < size; i++) { 
		if (root->children[i]) { 
			for(it=charIndex.begin(); it!=charIndex.end(); it++){
				if(it->second==i){
					temp=it->first;
					break;
				}
			}

			query.push_back(temp); 

			suggestionsRec(root->children[i], query); 
			query.pop_back(); 
		} 
	} 
} 


// stores teh suggestions for the given query in the solution multiset
int autoSuggestions(TrieNode* root, string query){
	struct TrieNode* p = root; 
	int level; 
	int n = query.length(); 
	for (level = 0; level < n; level++){ 
		int index = charIndex.find(query[level])->second; 

		if (!p->children[index]) 
			return 0; 

		p = p->children[index]; 
	} 

	bool isWord = (p->isWordEnd == true); 

	bool isLast = isLastNode(p); 

	if (isWord && isLast){ 
		solution.insert(make_pair(frequency[query],query));
		return -1; 
	} 

	if (!isLast) { 
		string prefix = query; 
		suggestionsRec(p, prefix); 
		return 1; 
	} 
} 

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

int main(){ 
	struct TrieNode* root = getNode();
	string line, input;
	int test_cases;
	fstream file;
	

	// accessing the word_frequency file and storing the strings and their corresponding frequency in the map
	string filename="word_frequency.txt";
	file.open(filename.c_str()); 
	while (std::getline(file, line)){
        vector<string> row_values;
        split(line, '\t', row_values);
        frequency.insert({row_values[0],stoi(row_values[1])});
        
        //inserting the string into the trie
        charIndex=insert(root,row_values[0]);
    }
	
	cout<<"Number of test cases : ";
	cin>>test_cases;

	while(test_cases--){
		cout<<"Input string : ";
		cin>>input;

		int ans = autoSuggestions(root, input ); 

		// prints the solution set
		for (auto itr = solution.rbegin(); itr != solution.rend(); ++itr) 
	        cout << itr->second<<'\t'<< itr->first<<endl; 

	    solution.clear();

		if (ans == 0) 
			cout << "No string found with this prefix\n"; 
	}

	return 0; 
} 
