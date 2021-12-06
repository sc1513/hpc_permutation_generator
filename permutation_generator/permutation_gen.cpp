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
#include <bits/stdc++.h>

void findPermutations(std::string str, std::string ans);
std::string getAccumulated();
void addArray(std::string str, int n, int i);
void substringBuilder(std::vector<std::string> arrayString, int x);


int main(int argc, char * argv[]){

	return 1;

}

	//serial code converted from java implementation

	std::vector<char> LetterFromUser;

	int PermutationCounter = 0;

	std::string allcombos;
	
	std::string TestCombo;
		    
	std::vector<char> permutationsGenerated;
		        
	std::vector<std::string> permutationsChecked;
			    
	int j = 0;
			        
	int y = 1;
				    
	int lengthArray;
				        
	std::vector<std::string> TempArray;
			
	std::stringstream Build;

	void setChecked (std::vector<std::string> S){
									            								            
		permutationsChecked = S;
	 }
								        
	std::vector <std::string> getChecked (){
										        
		return permutationsChecked;
											    
	}
							     								    
	void setToZero(){ j = 0; y = 1; PermutationCounter = 0; lengthArray = 0;/*Collision = 0; rightIndex = 0;*/}
								    								        
	std::vector<char> getLetters(){ return LetterFromUser; }
								        									    
	std::string getPermutations() { return TestCombo;}
									  									        
	std::vector<char> getString() { return LetterFromUser;}
	
	int factorial(int n){

		if (n == 0){

			return 1;

		}
	
		return n*factorial(n-1);
						           
	}

	void getPermutationLength(int length){

		std::vector <char> permutationsGenerated;
		permutationsGenerated.reserve(length);

        }


	void findCombos(){
      
		std::cout << LetterFromUser.size() * factorial(LetterFromUser.size()) + factorial(LetterFromUser.size());	        
		getPermutationLength(LetterFromUser.size() * factorial(LetterFromUser.size()) + factorial(LetterFromUser.size()));	                
		std::string s(LetterFromUser.begin(), LetterFromUser.end());
		findPermutations(s,"");	                        
		TestCombo = getAccumulated();                   

	}

	std::string subString(std::string str, int n){
				    
		std::vector<std::string> TempArray;
				    
		int k = 0;
				    
		for (int i = 0; i < 1; i++) {
				    		                                            
			addArray(str,n,i);
				    				    
		}
				    				                                                            
		std::stringstream ans;
				    				                                                                    
		for(int i = 0 ; i < TempArray.size(); i++) {
				                                                                                
			if(TempArray.at(i).size() == 1) {

				break;
				                                                                                                            
			}
				                                                                                                                        
			ans << TempArray.at(i);
				                                                                                                                                
		}
					
		return ans.str();
				    
				                                                                                                                               
	}

	void addArray(std::string str, int n, int i){
		        
		for (int j = str.size() - y; j <= n - y; j++) {
				            
			TempArray.push_back(str.substr(i, j) + " ");
					                		    
			str.substr(i,j);
													
		}						
							
	}

	void clearTempArray(){
	        
		TempArray.clear();
			    
	}

	void findPermutations(std::string str, std::string ans){
     
		// If string is empty
			
       		if (str.size() == 0) {
			
			for(int k = 0; k < ans.size(); k++){
			
				permutationsGenerated[j] = ans.at(k);
				j = j + 1;
			}

			PermutationCounter++;
	
			permutationsGenerated[j] = ' ';
			
			j = j + 1;
			
		return;
			
		}
	
		std::vector<bool> alpha;
		alpha.reserve(26);
	        
		for (int i = 0; i < str.size(); i++) {
	
		
			char ch = str.at(i);

			std::string ros = str.substr(0, i) +

			str.substr(i + 1);

			if (!alpha[ch - 'a']){
			
				findPermutations(ros, ans + ch);

			}
			
			alpha[ch - 'a'] = true;								        
	
		}

	}

	void findAllSubstrings() {
					
		std::string S(permutationsGenerated.begin(), permutationsGenerated.end());
			
		Build << S;
			
		int a = S.find(" ") + 1;
			
		a *= PermutationCounter;

		std::string shortString = S.substr(0,a);
			
		//std::vector<std::string> arrayString = shortString.substr(0, shortString.find(" "));
		
		std::regex re(" ");
		std::sregex_token_iterator first{shortString.begin(), shortString.end(), re, -1}, last;//the '-1' is what makes the regex split (-1 := what was not matched)
		std::vector<std::string> arrayString{first, last};

		//for loop skips over repeating substrings, only grabbing unique strings from original list of permutations.
			
		for (int i = 1, x = 1; i < arrayString.at(i).size(); i++, x = factorial(i), y = i){
			
			substringBuilder(arrayString, x);
						
		}
		
	
		TestCombo = Build.str();
		
	}


	void substringBuilder(std::vector<std::string> arrayString, int x){
	        
		for (j = 1; j < arrayString.size(); j += x) {
			            
			Build << subString(arrayString.at(j), arrayString.at(0).size());
				                			
			//TODO create an array of strings instead of one long string				    
			//Substring function is returning to nothing.			
	    		// it needs to append to TestCombo, probably use a String Builder variable and append				
			// after that set the value equal to TestCombo

			clearTempArray();
										
		}
												                                                            
	}

	void clearStringBuilder(){
		        
		std::stringstream Build;
			    
	}

	void takeLetter(std::vector<char> characterArray){
		    
		LetterFromUser = characterArray;		  
			
    		clearStringBuilder();

		permutationsGenerated.reserve(LetterFromUser.size() * factorial(LetterFromUser.size()) + factorial(LetterFromUser.size()));

		lengthArray = permutationsGenerated.size();


	}

	std::vector<char> putLetter(){
		        
		return permutationsGenerated;

	}

	std::unordered_set <std::string> wordDictionary;
	     
	void CreateDictionary() {
		         	 		             	
   		if(wordDictionary.empty()) {
				                 
			     try {

				     File file = new File("C:\\Users\\Steven Carpenter\\eclipse-workspace\\ScrambleAlgorithm\\src\\scramble\\dictionary2.txt");				
				     Scanner sc = new Scanner(file);											           	 	
				     sc.useDelimiter("\n");
				     std::string line;

				     while ((line = sc.next()) != null) {

					     wordDictionary.insert(line);
					
				     }

			     } catch (IOException e) {

				     e.printStackTrace();
			     }

		     }

	     }


	void getPermutationLength(int length){

		permutationsGenerated.reserve(length);
	
	}
	
	std::string getAccumulated(){
		       
	       	return allCombos;
	
	}
