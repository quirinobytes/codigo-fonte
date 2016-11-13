import java.io.*;
public class Tictactoe
{
	public static Integer[][] array = new Integer[3][3];

	
	
    public static void  main(String args[]) throws IOException
    {
	String a = new String();
	
    float number;
	array[0][0] = -8;
	array[0][1] = -8;
	array[0][2] = -8;
	array[1][0] = -8;
	array[1][1] = -8;
	array[1][2] = -8;
	array[2][0] = -8;
	array[2][1] = -8;
	array[2][2] = -8;
	
    System.out.println("Play1 ( 1 ) choose you position: (A1 - A2 - A3 - B1 - B2 - B3 - C1 - C2 - C3 [where: letter=lines number=column])");
	try
	{
		InputStreamReader in=new InputStreamReader(System.in);
		BufferedReader br=new BufferedReader(in);
	 a=" ";

	while( (char)a.charAt(0) != 'q'  ){		
			 a=br.readLine();
			 if (a.equals("A1")) {
				 array[0][0] = 1;
			 }
			 else
				 if (a.equals("A2") ){
				 array[0][1] = 1;
			 }
			 else
				 if (a.equals("A3") ){
				 array[0][2] = 1;
			 }
			 else
				 if (a.equals("B1") ){
				 array[1][0] = 1;
			 }
			 else
				 if (a.equals("B2") ){
				 array[1][1] = 1;
			 }
			 else
				 if (a.equals("B3") ){
				 array[1][2] = 1;
			 }
			 else
				 if (a.equals("C1") ){
				 array[2][0] = 1;
			 }
			 else
				 if (a.equals("C2") ){
				 array[2][1] = 1;
			 }
			 else
				 if (a.equals("C3") ){
				 array[2][2] = 1;
			 }
			 
		 
		 
		 System.out.println("Play2 ( O ) choose you position: (A1 - A2 - A3 - B1 - B2 - B3 - C1 - C2 - C3 [where: letter=lines number=column])");
		 a=br.readLine();
		 		 
		 if (a.equals("A1")) {
				 array[0][0] = 0;
			 }
			 else
				 if (a.equals("A2") ){
				 array[0][1] = 0;
			 }
			 else
				 if (a.equals("A3") ){
				 array[0][2] = 0;
			 }
			 else
				 if (a.equals("B1") ){
				 array[1][0] = 0;
			 }
			 else
				 if (a.equals("B2") ){
				 array[1][1] = 0;
			 }
			 else
				 if (a.equals("B3") ){
				 array[1][2] = 0;
			 }
			 else
				 if (a.equals("C1") ){
				 array[2][0] = 0;
			 }
			 else
				 if (a.equals("C2") ){
				 array[2][1] = 0;
			 }
			 else
				 if (a.equals("C3") ){
				 array[2][2] = 0;
			 }
		 
			escreve();
			hasWins();
		
		}
		
	}
	catch(Exception e){}

    }
	
	
	public static void escreve(){
		
		int c;
		for (c=0;c<3;c++){
				System.out.println(" "+array[c][0] + " | " + array[c][1] + " | " + array[c][2]);
				System.out.println("_________");
			
		}
		
	}
	public static void hasWins(){
		boolean p1=false,p2=false;
		
		if ((array[0][0] == 1 ) && (array[0][1] == 1 )  && (array[0][2] == 1 ) ) {
			p1=true;
		}
		else
		if ((array[1][0] == 1 ) && (array[1][1] == 1 )  && (array[1][2] == 1 ) ) {
			p1=true;
		}
		else
		if ((array[2][0] == 1 ) && (array[2][1] == 1 )  && (array[2][2] == 1 ) ) {
			p1=true;
		}
		if ((array[0][0] == 1 ) && (array[1][0] == 1 )  && (array[2][0] == 1 ) ) {
			p1=true;
		}
		else
		if ((array[0][1] == 1 ) && (array[1][1] == 1 )  && (array[2][1] == 1 ) ) {
			p1=true;
		}
		else
		if ((array[0][2] == 1 ) && (array[1][2] == 1 )  && (array[2][2] == 1 ) ) {
			p1=true;
		}
		if ((array[0][0] == 1 ) && (array[1][1] == 1 )  && (array[2][2] == 1 ) ) {
			p1=true;
		}
		if ((array[0][2] == 1 ) && (array[1][1] == 1 )  && (array[2][0] == 1 ) ) {
			p1=true;
		}
	

	
	
		if ((array[0][0] == 0 ) && (array[0][1] == 0 )  && (array[0][2] == 0 ) ) {
			p2=true;
		}
		else
		if ((array[1][0] == 0 ) && (array[1][1] == 0 )  && (array[1][2] == 0 ) ) {
			p2=true;
		}
		else
		if ((array[2][0] == 0 ) && (array[2][1] == 0 )  && (array[2][2] == 0 ) ) {
			p2=true;
		}
		if ((array[0][0] == 0 ) && (array[1][0] == 0 )  && (array[2][0] == 0 ) ) {
			p2=true;
		}
		else
		if ((array[0][1] == 0 ) && (array[1][1] == 0 )  && (array[2][1] == 0 ) ) {
			p2=true;
		}
		else
		if ((array[0][2] == 0 ) && (array[1][2] == 0 )  && (array[2][2] == 0 ) ) {
			p2=true;
		}
		if ((array[0][0] == 0 ) && (array[1][1] == 0 )  && (array[2][2] == 0 ) ) {
			p2=true;
		}
		if ((array[0][2] == 0 ) && (array[1][1] == 0 )  && (array[2][0] == 0 ) ) {
			p2=true;
		}
	


	
		if (p1 && p2){
			System.out.println("Empate !");
			array[0][0] = -8;
			array[0][1] = -8;
			array[0][2] = -8;
			array[1][0] = -8;
			array[1][1] = -8;
			array[1][2] = -8;
			array[2][0] = -8;
			array[2][1] = -8;
			array[2][2] = -8;
			System.out.println("Try Again...");
			escreve();
		}
		else
			if (p1) { 
					System.out.println("Player 1 WINS!");
					System.out.println("Play again or type q<ENTER> twice to quit.");
			}	
		else
			if (p2) {
					System.out.println("Player 2 WINS!");
					System.out.println("Play again or type q<ENTER> twice to quit.");
			}
			
		
		
	}
}







