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
#include <cctype>

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
                        std::string s(buffer);
                        s.clear(); //created a string variable in order to get rid of new line character. The character was causing issues with matching
                        for (int i = 0 ; i < strlen(buffer); ++i)
                          if (isalpha(buffer[i])) s += buffer[i];
			wordDictionary.push_back(s);						
				
	     
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

//Checks for two requirements
//1. All letters in a specific word are contained in the given set of letters.
//2. The letters in a specific word have less instances of each letter than the given set of letters.
void checkLetterSet(std::vector<char> Letters){

	//Set up letters to be checked in lmap
	std::map<char, int> lmap;
	std::map<char, int>::iterator it2;

	for (auto& it : Letters){
		it2 = lmap.find(it);
		if(it2 != lmap.end()){
			lmap.at(it) = lmap[it] + 1;
		} else {
			lmap.insert( std::pair<char, int>(it, 1) );
		}		
	}

	//Default number of threads 1, for serial case
        std::vector< std::vector<std::string> > thread_results;
        int nthreads = 1;

//Get number of threads for OpenMp
#ifdef _OPENMP
        #pragma omp parallel
        #pragma omp single
        {
           nthreads = omp_get_num_threads();
        }
#endif

        thread_results.resize( nthreads );

        #pragma omp parallel
        {
           int thread_id = 0;
#ifdef _OPENMP
           thread_id = omp_get_num_threads();
#endif
        printf("%d %d\n", nthreads, thread_id);
	
	//loops through wordDictionary which is a vecor of strings.
	//OpenMp Implementation on the outer loop
	#pragma omp for
	for(int i = 0; i < wordDictionary.size(); ++i) {
                const auto& it = wordDictionary[i];
		
		// initiate dmap and iterators, dmap keeps track of how many instances there are of each letter appearing in word of the dictionary.
        	std::map<char, int> dmap;
        	std::map<char, int>::iterator it3;
        	std::map<char, int>::iterator it4;
		// Checks requirement one and requirement two. Evaluates false if requirements are not met.
		bool match {true};
		dmap.clear();
		
		// Loops through each character in a word taken from the dictionary
		for( auto& charIt : it){
			char myChar = charIt;				
			it3 = lmap.find(myChar);

			// Evaluates requirement one, does the dictionary word contain a letter that I do not have in my letter set
			if(it3 != lmap.end()){
				it4 = dmap.find(myChar);
				
				//add to my dmap
				if(it4 != dmap.end()){
					dmap.at(myChar) = dmap[myChar] + 1;
				
					// Evaluate requirement two, does the dictionary word contain more instances of a given letter than i have in my letter set	 
					if((int)dmap.at(myChar) > (int)lmap.at(myChar)){
					match = false;

					}		
				} else {
					dmap.insert( std::pair<char, int>(myChar, 1 ) );

				}
			} else {
			match = false;

			} 
			
		}
		
		//if both requirements are true then add to an array of results.
		//This is done prevent multiple threads from accessing the same container.
		//Race conditions
		if(match){
			thread_results[thread_id].push_back(it);
		}

	}

        } // end parallel

	//Take results and put them into a final results array.
        for (int i = 0; i < nthreads; ++i)
            for (auto& j : thread_results[i])
                results.push_back( j );

	//test
	for (auto& it : lmap){
		std::cout << it.first << it.second << std::endl;
	}


}
	
	
int main(int argc, char * argv[]){
	std::cout<< "test" << std::endl;
	CreateDictionary();
	

	std::vector<char> testL = { 'h', 't', 'e', 't', 'e'};
	checkLetterSet(testL);

	for(int i = 0 ; i < results.size() ; i++){
		std::cout << results[i] << std::endl;
	}	
		std::cout << results.size() << std::endl;
		
	

	return 1;
			                                                                                                
}

