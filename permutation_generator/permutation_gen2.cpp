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
#include <cstring>

//#include <aligned_allocator.h>
//#ifdef _OPENMP
//#include <omp.h>
//#endif

//serial code  	     

std::vector<std::string> wordDictionary;
std::vector<std::string> results;
std::vector<std::vector<std::string>> checkLetterSet(std::vector<char> Letters);
void consolidateResults(std::vector< std::vector<std::string> > thread_results);
int threads;




void help(const char* prg) {
   if (prg) fprintf(stderr,"%s:\n", prg);
   fprintf(stderr,"\t--help | -h       : Print help message.\n");
   fprintf(stderr,"\t--nparticles | -n : # of particles (5).\n");
   fprintf(stderr,"\t--nsteps | -s     : # of steps to take (10).\n");
 
}


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

void runTests(int n, int num_steps){
//seed random input for tests
	printf("Benchmark for Scramble Word Search \n");
	printf("Amount of Letters: %d \n", n);
	printf("Number of Tests: %d \n", num_steps);
	
   	/* Run the step several times. */
   	TimerType t_start = getTimeStamp();
   	double t_checkLetterSet = 0;
	double t_consolidateResults = 0;
   	double t_cls = 0;
	double t_cr = 0;
	std::vector< std::vector<std::string> > threadsR;
	int wordsFoundPerTest = 0;      	
	
	std::vector<std::vector<char>> testWords;
	testWords.reserve(num_steps);
	std::vector<std::string> displayWords;

      	for (int i = 0; i < num_steps; i++)
      	{
         	std::vector<char> tWord;
         	for (int k = 0; k < n; k++){
			//Assign random set of characters (lower case)
			char c = (char)(rand() % 26 + 97);
			tWord.push_back(c);
		} 
		testWords.push_back(tWord);
		std::string s(tWord.begin(), tWord.end());
		displayWords.push_back(s);
            	tWord.clear();	
      	}
   	
	
	printf("Letters | Words Found | Search Time | Concatonate Time \n");
	for (int i = 0; i < num_steps; i++){

		/* 1. get time elapsed to find words from dictionary */
      		TimerType t0 = getTimeStamp();
      		threadsR = checkLetterSet(testWords[i]);
      		TimerType t1 = getTimeStamp();

		/* 2. get time elasped to concatonate results from multiple threads */
		TimerType t2 = getTimeStamp();
		consolidateResults(threadsR);
		TimerType t3 = getTimeStamp();

		/*3. Calculate time for both metrics */
      		t_checkLetterSet += getElapsedTime(t0,t1);
		t_consolidateResults += getElapsedTime(t2,t3);
		
		//find time and words per trial
		wordsFoundPerTest = results.size() - wordsFoundPerTest;
		t_cls = t_checkLetterSet - t_cls;
		t_cr = t_consolidateResults - t_cr;
		std::cout << displayWords[i] << " ";
		printf("| %d | %f (ms) | %f (ms) \n", wordsFoundPerTest, t_cls*1000.0, t_cr*1000.0);
		//printf("Average time = %f (ms) per step with %d elements %.2f KB over %d steps %f %f %f\n", t_calc*1000.0/num_steps, n, nkbytes, num_steps, t_accel*1000/num_steps, t_update*1000/num_steps, t_search*1000/num_steps);
		
		wordsFoundPerTest = results.size();
		t_cls = t_checkLetterSet;
		t_cr = t_consolidateResults;

	}	

	printf("AVG Number of words found: %1ld, AVG time to find words %f (ms), AVG time to concatonate words %f (ms), Number of thread(s) used %d, # of Letters in data set %d. # of words tested %d.\n", results.size()/num_steps, t_checkLetterSet*1000.0/num_steps, t_consolidateResults*1000.0/num_steps, threads, n, num_steps);
	
	for(int i = 0; i < results.size(); i++){
		std::cout << results[i] << " ";
	}


}



//Checks for two requirements
//1. All letters in a specific word are contained in the given set of letters.
//2. The letters in a specific word have less instances of each letter than the given set of letters.
std::vector< std::vector<std::string> > checkLetterSet(std::vector<char> Letters){

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
        //printf("%d %d\n", nthreads, thread_id);
	
	//loops through wordDictionary which is a vecor of strings.
	//OpenMp Implementation on the outer loop
	//Serial Runs on one Thread, #pragma omp for optimization, #pragma omp for schedul(dynamic) for load balancing.
	#pragma omp for schedule(dynamic)
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
					continue;
					}		
				} else {
					dmap.insert( std::pair<char, int>(myChar, 1 ) );

				}
			} else {
			match = false;
			continue;
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
        //for (int i = 0; i < nthreads; ++i)
        //    for (auto& j : thread_results[i])
        //        results.push_back( j );
	threads = nthreads;
	//std::cout << "test";	
	return thread_results; 
}

void consolidateResults(std::vector< std::vector<std::string> > thread_results){

	//Take results and put them into a final results array.
	for (int i = 0; i < thread_results.size(); ++i)
            for (auto& j : thread_results[i])
                results.push_back( j );


	std::sort(results.begin(), results.end());

}

	
	
int main(int argc, char * argv[]){
	
	int n = 5;

  	int num_steps = 10;

	for (int i = 1; i < argc; ++i)
  	{
#define check_index(i,str) \
   	if ((i) >= argc) \
      	{ fprintf(stderr,"Missing 2nd argument for %s\n", str); help(argv[0]); return 1; }

      	if ( strcmp(argv[i],"-h") == 0 || strcmp(argv[i],"--help") == 0)
      	{
         	help(argv[0]);
         	return 0;
      	}
      	else if (strcmp(argv[i],"--nparticles") == 0 || strcmp(argv[i],"-n") == 0)
      	{
         	check_index(i+1,"--nparticles|-n");
         	i++;
         	if (not(isdigit(*argv[i])))
            	{ fprintf(stderr,"Invalid value for option \"--particles\" %s\n", argv[i]); help(argv[0]); return 1; }
         	n = atoi( argv[i] );
      	}
      	else if (strcmp(argv[i],"--nsteps") == 0 || strcmp(argv[i],"-s") == 0)
      	{
         	check_index(i+1,"--nsteps|-s");
         	i++;
         	if (not(isdigit(*argv[i])))
            	{ fprintf(stderr,"Invalid value for option \"--nsteps\" %s\n", argv[i]); help(argv[0]); return 1; }
         	num_steps = atoi( argv[i] );
      	}
      	else
      	{
         	fprintf(stderr,"Unknown option %s\n", argv[i]);
         	help(argv[0]);
         	return 1;
      	}
   	}
	//create dictionary to reference data
	CreateDictionary();
	
	//letter set to reference against the dictionary
	//std::vector<char> testL = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	runTests(n, num_steps);		

	return 1;
			                                                                                                
}

