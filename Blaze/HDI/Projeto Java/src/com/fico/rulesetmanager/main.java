package com.fico.rulesetmanager;
import com.blazesoft.template.repository.NdRomException;

import tools.Utils;

public class main {
	
	public static String XMLReal = ""
			+ "33";
	
	public static String regra1 = "if ( ((cotacao.CodPrdOperac = 331) or (cotacao.CodPrdOperac = 334) or (cotacao.CodPrdOperac = 431) or (cotacao.CodPrdOperac = 831 )) and \r\n" + 
			"     (cotacao.CodCategTarifa = 14) and (cotacao.CodPrdOperac = 1) and (cotacao.CodPrdOperac = 4  ) and  ( VARIAVEK >= 301 and VARIALVE <= 1000))  \r\n" + 
			"   	then\r\n" + 
			"     FatorCalculo = 0.032;";

	public static String regra2 = "if ((cotacao.CodVeiculo = 14 ) and\r\n" + 
			"     ((cotacao.CodPrdVeiculo = 1 OR cotacao.CodPrdVeiculo = 4  ) and\r\n" + 
			"     FatorCalculo = 0.062;";

	public static void main(String[] args) throws Exception {
	
		String repositorioPath = "C:\\WORKSPACE\\API\\Repositorio";
		
		//rulesetName deve ser o caminho desde a Pasta do Projeto até o elemento.
		String [] rulesetName = {"ProjetoBlaze Folder", "subscricao"};
		String ruleName = "rule1";
		String ruleBodyText = "print(\"foda\");";
	
		RulesetManager HDI_ruleset = new RulesetManager();
		try {
			 if (HDI_ruleset.conectaRepositorio(repositorioPath)) {
				 //Como vamos trabalhar em um projeto, a primeira coisa a se fazer é setar o projeto.
				 HDI_ruleset.setProjectPath(new String[] {"Pasta","ProjetoBlaze Folder","ProjetoBlaze"});
				//HDI_ruleset.deleteDir("Projeder");

				 
				 if ( ! HDI_ruleset.isDirOnRoot("NovaPasta") ) {
					HDI_ruleset.createDirOnRoot("NovaPasta");	
				 }
				 HDI_ruleset.deleteDir("NovaPasta");	
				 
				 HDI_ruleset.createRuleset("subscricao", "ProjetoBlaze Folder");
				 HDI_ruleset.setRuleset(rulesetName);
				 
				 HDI_ruleset.addInputParameter("Rafael", "MachoPraCaralho");
				 HDI_ruleset.addRule("RuleID 3500068", regra1);
				 HDI_ruleset.addRule("rule1", regra2);
				 HDI_ruleset.addRule("RuleID 3500070", regra1);
				 HDI_ruleset.getItems("ProjetoBlaze Folder/subscricao");
				 HDI_ruleset.ruleBodyChange("ProjetoBlaze Folder/subscricao", ruleName, ruleBodyText);
				 HDI_ruleset.save();
			 }
			 else
			 {
				 Utils.print("Erro ao se conectar ao repositório, verifique o PATH= " + repositorioPath);
			 }
		}
		catch (NdRomException e) {
			e.printStackTrace();
		}
		
		//END
		Utils.print("(END) Execução finalizada.");
	}
}
