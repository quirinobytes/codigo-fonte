package tools;

public class Utils {
	
	public int pontos;
	public String endName;
	public String errorInFunction = "";
	public boolean errorFlag = false;
	public static boolean debug;
	
	//Método para facilitar o print
	public static void print(String str) {
		if (!debug) return;
		System.out.println(str);
	}
	
	public void setPontos(int num) {
		pontos = num;
	}
	public void setEndName(String name) {
		endName = name;
	}
	
	public void startBanner(String f_name, String param) {
		if (!debug) return;
		setPontos(f_name.length() + param.length());
		setEndName(f_name);
		int c;
		System.out.print("  ");
		for (c=0; c < f_name.length() + param.length() + 9 ; c++) {
			System.out.print("▄");
		}
		Utils.print("\n► █ " + f_name + " ('" + param + "') █  ");
		System.out.print("  ");
		for (c=0; c < f_name.length() + param.length() + 9 ; c++) {
			System.out.print("▀");
		}
		System.out.println("  ");
	}
	public void startBanner(String f_name) {
		if (!debug) return;
		setPontos(f_name.length());
		setEndName(f_name);
		int c;
		System.out.print("  ");
		for (c=0; c < f_name.length() + 9 ; c++) {
			System.out.print("▄");
		}
		Utils.print("\n► █  " + f_name + " ()  █  ");
		System.out.print("  ");
		for (c=0; c < f_name.length() + 9 ; c++) {
			System.out.print("▀");
		}
		System.out.println("  ");
	}
	
	private void print(int value) {
		if (!debug) return;
		Integer aux = new Integer(value);
		System.out.print(aux.toString());
	}
	
	
	public void endBanner() {
		if (!debug) return;
		//System.out.println("PONTOS ==>  " + pontos);
		String funcaoName = endName;
		int c;
		System.out.print("  ");
		for (c=0; c < pontos + 1 ; c++) {
			System.out.print(" ");
		}
		System.out.print("▄▄▄▄▄▄▄▄\n");
		System.out.print("◄ " + funcaoName );
		for (c=0;c< pontos - funcaoName.length() ;c++) {
			System.out.print(".");
		}	
		System.out.print(" █ DONE █\n");
		
		System.out.print("  ");
		for (c=0; c < pontos + 1; c++) {
			System.out.print(" ");
		}
		System.out.print("▀▀▀▀▀▀▀▀\n");
		endName = "";
	}

	public void errorBanner() {
		if (!debug) return;
		errorFlag = true;
		errorInFunction += endName;
		String funcaoName = endName;
		int c;
		System.out.print("");
		for (c=0; c < funcaoName.length() + pontos - 15 + endName.length(); c++) {
			System.out.print(" ");
		}
		System.out.print("▄▄▄▄▄▄▄▄▄\n");
		System.out.print("◄ " + funcaoName );
		for (c=0;c< pontos - funcaoName.length() - 4;c++) {
			System.out.print("X");
		}	
		System.out.print(" █ ERROR █\n");
		for (c=0; c < funcaoName.length() + pontos - 15 + endName.length() ; c++) {
			System.out.print(" ");
		}
		System.out.print("▀▀▀▀▀▀▀▀▀\n");
		
	}

	public void showPontos() {
		System.out.println(this.pontos);
		
	}
	
	public void statusFinal() {
		if (errorFlag){
			System.out.println("▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄");
			System.out.println("█ HOUVE ERRO DURANTE A EXECUCAO █");
			System.out.println("▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀");
		}
		else {
			System.out.println("▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄");
			System.out.println("█ FINALIZADO COM SUCESSO █");
			System.out.println("▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀");
		}
	}
}
