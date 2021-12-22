import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.util.Scanner; // Import the Scanner class to read text files
import java.util.Arrays;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;

public class main {

	public static void main(String[] x) throws IOException {

		

		try {
	        	FileWriter File2 = new FileWriter("dict4");	
			File myObj = new File("dict2");
			Scanner myReader = new Scanner(myObj);
			ArrayList<String> dictionary = new ArrayList<String>();
			while (myReader.hasNextLine()) {
				String data = myReader.nextLine();
				dictionary.add(data);
			}
			
			String [] dict = new String [dictionary.size()];
			dict = dictionary.toArray(dict);
			String temp;
			
			for(int i = 0 ; i < dict.length - 1; i++){
				
				int min = i;
				for(int j = i + 1 ; j < dict.length; j++){
					
					if(min > dict[j].length()){
						min = dict[j].length();
						temp = dict[j];
						dict[j] = dict[i];
						dict[i] = temp;	
						
					}

				}	
			
			}
			
			for (int i = 0; i < dict.length; i++){
				
				File2.write(dict[i]);
				File2.write('\n');
			}
			
			myReader.close();
		
		} catch (FileNotFoundException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
			}


	}


}
