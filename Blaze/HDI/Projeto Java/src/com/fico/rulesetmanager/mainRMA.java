package com.fico.rulesetmanager;

import com.blazesoft.rma.NdRMAException;
import com.blazesoft.rma.NdRmaProject;
import com.blazesoft.template.repository.NdRomException;

import tools.Utils;

public class mainRMA {

	public NdRmaProject rmaProject;
	public static RmaManager rma;
		
	/**
	 * @param debug
	 * @desc  Usada para definir o mode VERBOSE de execuçao, VERBOSE=true ou VERBOSE=false
	 */
	
	public static boolean debug = true;
	public static int intPrintAddRegras = 100;
	public static int intPrintProjetoSalvo = 300;

	public static void main(String[] args) throws NdRomException, NdRMAException {
		
		// 0 -> Verbose off
		// 1 -> Verbose on
		if (debug) { rma = new RmaManager(DEBUG.YES); debug = true; }
		else { rma = new RmaManager(DEBUG.NO); debug = false; }

		if (rma.conectaRepositorio("C:\\WORKSPACE\\API\\Repositorio")) {
			
			rma.setProjectPath("/Pasta/ProjetoBlaze Folder/ProjetoBlaze");
			rma.setInstanceName("vertzon");
			//rma.listRules();
			
//			String foundPath = rma.findSegment("rule1");
//			if (foundPath != null) 	rma.setNodeValue(foundPath + ".name", "rule2");
//			if (foundPath != null) 	rma.setNodeValue(foundPath + ".comment", "Loren Yplum Doren loren" );
//			if (foundPath != null) 	rma.setNodeValue(foundPath + ".ruleAction","{ print('rafael'); }");
//			if (foundPath != null) 	rma.setNodeValue(foundPath + ".ruleCondition","( parameter is equal to true )");

			addMultiplasRules(5);
						
			rma.save();
			rma.disconnect();
		} else {
			Utils.print("Erro ao conectar no repositorio");
		}
	}
	
	public static void addMultiplasRules(int qtde) throws NdRMAException {
		System.out.print("Iniciando da adição de mais "+qtde+" rules\n\n • Aguarde :P \n");
		String ruleName, comment, condition, action;
		for (int c=1;c!=qtde;c++) {
			
			//Mostra parcial de 100 em 100
			if (c%intPrintAddRegras==0) {
				System.out.println("\n\t -> Mais 100 regras adicionadas\n\t -> Total adicionado: "+c+" regras\n");
				rma.save();
			}
			if (c%intPrintProjetoSalvo==0) {
				System.out.println("\n\t -> Projeto Salvo "+c+" regras\n");
				rma.projectSave();
			}
			
			ruleName = "rule"+c;
			comment = "Rule"+ c+ "´s comment goes here.";
			condition = "( parameter is equal to true )";
			action = "{  i = 0;  while (i < 1000) do  { i += 1; print(\"Nova:  Rule "+c+" - \" + i);  }  }";					
			rma.addRule(ruleName,action,condition,comment);	
			if(!debug) System.out.print(".");
		}
		if (! debug) System.out.print("-> Done");
		System.out.println("\n\n   ✔ Finalizei a adicão de mais "+qtde+" rules\n");
		System.out.println("\t  \\Ω/  ");
		System.out.println("\t  σ╫    ");
		System.out.println("\t   ╩    \n\n");
	}
}
