#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm> // std::min
#include <cmath> // std::log, etc.
#include <string>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <unordered_set>
#include <bits/stdc++.h>
#include <map>
#include <utility>

//serial code converted from java implementati
// 	     

std::vector<std::string> wordDictionary;
std::vector<std::string> results;


//sets up dictionary
void CreateDictionary() {
		
	const int B = 40;
				                 
	FILE * file;
     	char buffer[B];
	int i= 0;

	file = fopen("../dictionary2.txt", "r");

	if (file == NULL) perror ("Error opening file");   
	else{		        
		while( ! feof (file) ){
			
	    		if( fgets (buffer , 40 , file) == NULL ) 
				break;	
				
				wordDictionary.push_back(buffer);						
				
	     
		}
		fclose(file);
	}
	
	//test
	for(int i = 0; i < 50; i++){    
               		
		std::cout << wordDictionary.at(i);
                                        
	}

}

void runTests(int numOfLetters, int numOfWords){
//seed random input for tests





}

void checkLetterSet(std::vector<char> Letters){

	std::map<char, int> lmap;
	std::map<char, int> dmap;	
	std::map<char, int>::iterator it2;
	std::map<char, int>::iterator it3;
	std::map<char, int>::iterator it4;
	bool match {true};

	for (auto& it : Letters){
		it2 = lmap.find(it);
		if(it2 != lmap.end()){
			lmap.at(it) = lmap[it] + 1;
		} else {
			lmap.insert( std::pair<char, int>(it, 1) );
		}		
	}
	
	//OpenMp Implementation
	for(auto& it : wordDictionary){
		match = true;
		dmap.clear();

		for( auto& charIt : it){
			it3 = lmap.find(charIt);
			if(it3 != lmap.end()){
				it4 = dmap.find(charIt);
				if(it4 != dmap.end()){
					dmap.at(charIt) = dmap[charIt] + 1;
					if((int)dmap.at(charIt) > (int)lmap.at(charIt)){
					match = false;
					}		
				} else {
					dmap.insert( std::pair<char, int>(charIt, 1 ) );
				}
			} else {
			//match = false;
			} 
		}
		int d = (int) dmap.at(charIt);
		int l = (int) lmap.at(charIt);
		if(l > d){
		std::cout << it << std::endl;
		results.push_back(it);
		}

	}
	//test
	for (auto& it : lmap){
		std::cout << it.first << it.second << std::endl;
	}


}
	
	
int main(int argc, char * argv[]){
	std::cout<< "test" << std::endl;
	CreateDictionary();
	

	std::vector<char> testL = { 'a', 'b', 'c', 'd', 'e'};
	checkLetterSet(testL);

	for(int i = 0 ; i < results.size() ; i++){
		//std::cout << "test";
		std::cout << results.at(i) << std::endl;
		
	}

	return 1;
			                                                                                                
}

