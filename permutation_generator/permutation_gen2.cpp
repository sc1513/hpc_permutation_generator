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
                        //s.erase( std::remove( s.begin(), s.end(), '\n'), s.end() );
                        //if (!s.empty() and s[s.length()-1] == '\n')
                        //   s.erase( s.length()-1 );
                        s.clear();
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

        std::vector< std::vector<std::string> > thread_results;
        int nthreads = 1;

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
	
	//OpenMp Implementation
	//for(auto& it : wordDictionary){
	#pragma omp for
	for(int i = 0; i < wordDictionary.size(); ++i) {
                const auto& it = wordDictionary[i];
		match = true;
		dmap.clear();
		//std::cout << "blah: " << it << std::endl;
		for( auto& charIt : it){
			char myChar = charIt;
				
			it3 = lmap.find(myChar);
			if(it3 != lmap.end()){
				it4 = dmap.find(myChar);
				if(it4 != dmap.end()){
					dmap.at(myChar) = dmap[myChar] + 1;
					//std::cout<< dmap[myChar] << std::endl;
					//std::cout<< lmap[myChar] << std::endl; 
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
		//if(it.compare("cab") == 0) {
                // std::cout << "cab" << it << "\n";
                // for (auto k : dmap) printf("%c: %d\n", k.first, k.second);
                //}
		if(match){
		//std::cout << it << std::endl;
		//results.push_back(it);
		thread_results[thread_id].push_back(it);
		}

	}

        } // end parallel

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
	

	std::vector<char> testL = { 'h', 't', 'e'};
	checkLetterSet(testL);

	for(int i = 0 ; i < results.size() ; i++){
		std::cout << results[i] << std::endl;
	}	
		std::cout << results.size() << std::endl;
		
	

	return 1;
			                                                                                                
}

