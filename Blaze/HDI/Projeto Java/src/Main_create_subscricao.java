import com.blazesoft.template.repository.NdRomException;

public class Main_create_subscricao {
	
	public static String XMLReal = ""
			+ "<REGRA ID='16594' COD_VAR='8' NOME_VAR='CodPrdOperac' FATOR_CALCULO='0,032' DATA_VIG=01012001:10102020>"
			+ "	<CONDITION ID='350068'>"
			+ "				<ID_VAR>8</ID_VAR>"
			+ "				<OPERADOR>IN</OPERADOR>"
			+ "				<VALOR>331,334,431,831</VALOR>"
			+ "	</CONDITION>"
			+ "	<CONDITION ID='350069'>"
			+ "				<ID_VAR>33</ID_VAR>"
			+ "				<OPERADOR>=</OPERADOR>"
			+ "				<VALOR>14</VALOR>"
			+ "	</CONDITION>"					
			+ "</REGRA> ";
	
	public static String regra1 = "if ( ((cotacao.CodPrdOperac = 331) or (cotacao.CodPrdOperac = 334) or (cotacao.CodPrdOperac = 431) or (cotacao.CodPrdOperac = 831 )) and \r\n" + 
			"     (cotacao.CodCategTarifa = 14) and (cotacao.CodPrdOperac = 1) and (cotacao.CodPrdOperac = 4  ) and  ( VARIAVEK >= 301 and VARIALVE <= 1000))  \r\n" + 
			"   	then\r\n" + 
			"     FatorCalculo = 0,032;";

	public static String regra2 = "if ((cotacao.CodVeiculo = 14 ) and\r\n" + 
			"     ((cotacao.CodPrdVeiculo = 1 OR cotacao.CodPrdVeiculo = 4  ) and\r\n" + 
			"     FatorCalculo = 0,062;";

	public static void main(String[] args) throws Exception {
		ImportRules conversor = new ImportRules();
		try {
			if (true) {
			conversor.conectaRepositorio("C:\\WORKSPACE\\API\\Repositorio");
			//conversor.conecta2();
			conversor.createRuleset();
			//conversor.connectRuleset();
			//conversor.createRulesetInputParameter("xmlInput","XML");
			//conversor.createRulesetInputParameter("xmlInput","Parametro2");
			conversor.addRule("RuleID 3500068", regra1);
			conversor.addRule("rule1", regra2);
			conversor.addRule("RuleID 3500070", regra1);
			conversor.save();
			}
			else
			{
				conversor.conecta2();
				//conversor.createRulesetInputParameter("xmlInput","XML");
				//conversor.createRulesetInputParameter("xmlInput","Parametro2");
				conversor.addRule("RuleID 3500068", regra1);
				//conversor.addRule("rule1", regra2);
				//conversor.addRule("RuleID 3500070", regra1);
				conversor.save2();
			}
			//conversor.printXML();
			
		}
		
		catch (NdRomException e) {
			e.printStackTrace();
		}
		System.out.println("END");
	}
}
