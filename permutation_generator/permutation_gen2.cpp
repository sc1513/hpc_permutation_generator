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
#include <omp.h>

//#include <aligned_allocator.h>
//#ifdef _OPENMP
//#include <omp.h>
//#endif

//serial code  	     

std::vector<std::string> wordDictionary;
std::vector<std::string> results;
int checkLetterSet(std::vector<char> Letters);

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


}

void runTests(std::vector<char> Letters){
//seed random input for tests

   	/* Run the step several times. */
   	TimerType t_start = getTimeStamp();
   	double t_checkLetterSet = 0;
   	int threads;
      	
	/* 1. Compute the acceleration on each object. */
      	TimerType t0 = getTimeStamp();

      	threads = checkLetterSet(Letters);

      	TimerType t1 = getTimeStamp();

      	t_checkLetterSet += getElapsedTime(t0,t1);
	printf("Results: %d words found in %f (ms), # of thread(s) used %d, # of Letters in data set %d.\n", results.size(), t_checkLetterSet*1000.0, threads, Letters.size());
	//printf("Average time = %f (ms) per step with %d elements %.2f KB over %d steps %f %f %f\n", t_calc*1000.0/num_steps, n, nkbytes, num_steps, t_accel*1000/num_steps, t_update*1000/num_steps, t_search*1000/num_steps);
}



//Checks for two requirements
//1. All letters in a specific word are contained in the given set of letters.
//2. The letters in a specific word have less instances of each letter than the given set of letters.
int checkLetterSet(std::vector<char> Letters){

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
           thread_id = omp_get_thread_num();
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

	std::cout << "test";
	return nthreads;
}
	
	
int main(int argc, char * argv[]){
	
	//create dictionary to reference data
	CreateDictionary();
	
	//letter set to reference against the dictionary
	std::vector<char> testL = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	runTests(testL);		

	return 1;
			                                                                                                
}

