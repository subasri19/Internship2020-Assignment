#include <bits/stdc++.h> 
using namespace std; 

fstream file; 
string filename, word, line, dummyLine;
string key="", character="";
vector<pair<string, string> > char_representation;
vector<pair<string, string> > word_frequency;
int itr1=0;

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

//storing the contents of the file in the vector
vector<pair<string, string> > read_file(string filename){
	vector<pair<string, string> > m;
	file.open(filename.c_str()); 
	getline(file, dummyLine);

	while (std::getline(file, line)){
        vector<string> row_values;
        split(line, '\t', row_values);
        
        // for (int i=0; i!=row_values.size(); i++)
        //     cout << row_values[i] << ',' ;
        // cout<<'\t';

        m.push_back(make_pair(row_values[1], row_values[0]));
    }
	file.close();
	return m;
}

void print_map(vector<pair<string, string> > m){
	for (itr1 = 0; itr1 != m.size(); ++itr1) { 
        cout << '\t' << m[itr1].first 
             << '\t' << m[itr1].second << '\n'; 
    } 
    cout << endl; 
}

int main() { 
	string s1, s2, s3;
	int found;
	
	string file1="character_mapping.txt";
	// string file1="sample.txt";
	string file2="word_corpus.txt";
	
	char_representation = read_file(file1);
	word_frequency = read_file(file2);
	

	for(int i=0 ; i != word_frequency.size(); i++){
		for(int j= 0; j != char_representation.size(); j++){
			s1=word_frequency[i].first;
			s2=char_representation[j].first;
			s3=char_representation[j].second;
			
			// cout<<s1<<" "<<s2<<" "<<s3<<endl;

			// Locating the substring to be replaced. Erasing and inserting the string.
			for(size_t pos = 0; ; pos += s3.length()) {
		        pos = s1.find( s2, pos);
		        if(pos == string::npos) 
		        	break;
		        s1.erase(pos, s2.length());
		        s1.insert(pos, s3);
		    }
		    if(s1!=word_frequency[i].first)
		    	word_frequency[i].first=s1;
		}		
	}

	// Writing the replaced contents to the output file "word_frequency.txt"
	ofstream myfile;
	myfile.open ("word_frequency.txt");

	for(int i=0 ; i != word_frequency.size(); i++){
	  	 myfile << word_frequency[i].first <<"\t"<<word_frequency[i].second<<endl;
	}
	myfile.close();

	return 0; 
} 
