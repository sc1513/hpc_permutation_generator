import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.util.Scanner; // Import the Scanner class to read text files
import java.util.Arrays;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;


public class main {

	public static void main(String[] x) throws IOException {

		try {
	        	FileWriter File2 = new FileWriter("dict3");	
			File myObj = new File("dict2");
			Scanner myReader = new Scanner(myObj);
			while (myReader.hasNextLine()) {
				String data = myReader.nextLine();
				data = data.toLowerCase();
				File2.write(data);
				File2.write('\n');
			}
			myReader.close();
		} catch (FileNotFoundException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
			}


	
				

	}





}
