package com.fico.rulesetmanager;

import com.blazesoft.repository.file.NdFileRepositoryConnection;
import com.blazesoft.repository.naming.NdLocation;
import com.blazesoft.repository.naming.NdLocationFactory;
import com.blazesoft.security.bc.util.Arrays;
import com.blazesoft.template.engine.NdInstantiation;
import com.blazesoft.template.engine.NdInstantiationElement;
import com.blazesoft.template.repository.NdPromDirectory;
import com.blazesoft.template.repository.NdRomMutableDirectory;
import com.blazesoft.template.repository.NdPromItem;
import com.blazesoft.template.repository.NdPromItemContent;
import com.blazesoft.template.repository.NdPromItemFactory;
import com.blazesoft.template.repository.NdPromProject;
import com.blazesoft.template.repository.NdPromProjectFactory;
import com.blazesoft.template.repository.NdRomConnectionContext;
import com.blazesoft.template.repository.NdRomConnectionManager;
import com.blazesoft.template.repository.NdRomDirectory;
import com.blazesoft.template.repository.NdRomEntry;
import com.blazesoft.template.repository.NdRomException;
import com.blazesoft.template.repository.NdRomFactory;
import com.blazesoft.template.repository.NdRomProject;
import com.blazesoft.template.repository.NdRomSchemaConstants;
import com.blazesoft.template.repository.NdRomSchemaElement;
import com.blazesoft.template.repository.NdRomSchemaManager;
import com.blazesoft.template.repository.objects.NdPromTextContentFactory;
import com.blazesoft.template.repository.objects.rules.NdPromSrlConstructContentFactory;
import com.blazesoft.template.repository.objects.rules.NdPromSrlGenericTypeContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlParameterContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRule;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRuleBodyTextContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRuleContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRuleset;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRulesetContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRulesetItem;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRulesetItemContent;

import tools.Utils;

public class RulesetManager implements NdRomSchemaConstants {

	// Representa o caminho para o repositório, se tem ou nao versionamento, credentials etc.
	private NdFileRepositoryConnection repoConn;
	// Faz a conexão com o repositório acontecer.
	private NdRomConnectionManager connManager;
	// Carrega o contexto da conexão com o repositório, para começar a tirar as estruturas e navegar por elas.
	private NdRomConnectionContext connContext;
	// romRoot nesse caso será o Raiz do Repositório.
	private NdRomDirectory romRoot;
	// Voce precisa de um Rom project
	private NdRomProject romProject;
	// Voce precisa de um project(PROM)
	private NdPromProject project;
	// Serve para armazenar a localização de algum elemento (diretório/projeto/ruleset/etc)
	private NdLocation projectLocation;
	// Serve para permitir salvar um elemento em um projeto, somente PromItem tem o método save, por exemplo salvar o
	// projeto, carrega ele em um PromItem.
	private NdPromItem rulesetPromItem;
	// Permite acessar um ruleset no formato CONTENT, ou seja isso é WRITABLE, o mode STRING não é writable, o modo STRING
	// correspondem as mesmas classes sem o Content no final.
	private NdPromSrlRulesetContent ruleset;

	// CONECTA NO REPOSITORIO ( STRING PATH ) : BOOLEAN TRUE IF SUCCESS
	//
	public boolean conectaRepositorio(String path) throws NdRomException {
		repoConn = new NdFileRepositoryConnection();
		repoConn.setRepositoryFolder(path);
		connManager = NdRomFactory.newRepositoryConnectionManager(repoConn);
		try {
			connManager.connect();
			connContext = connManager.getConnectionContext();
			romRoot = connContext.getRoot();
			Utils.print("Conectado no repositório com sucesso!");
			return true;
		} catch (Exception e) {
			Utils.print("(X) Falha ao conectar no repositório.");
			e.printStackTrace();
			return false;
		}
	}

	// Configurar o caminho do projeto, é necessário ter um projeto para se tirar de um projectLocation um romProject, que
	// será tirado o Factory
	public void setProjectPath(String[] projectStaticPath) {
		String r = "";
		for (int c = 0; c < projectStaticPath.length; c++) {
			r += "/" + projectStaticPath[c];
		}
		Utils.print("   ________________________");
		Utils.print("► |   setProject PATH(" + r + ") |");
		Utils.print("   ------------------------");
		// this parameter is something like new String[]{"Pasta","ProjetoBlaze Folder","ProjetoBlaze"}
		// String[] projectStaticPath = new String[] {"Pasta","ProjetoBlaze Folder","ProjetoBlaze"};
		Utils.print(NdLocationFactory.createLocation(projectStaticPath, true).getClass().toString());
		projectLocation = NdLocationFactory.createLocation(projectStaticPath, true);
	}

	// Funcao para criar um ruleset do zero, somente passar o nome e o local(targetDirectory)
	public void createRuleset(String rulesetName, String targetDirectory) throws NdRomException {
		Utils.print("   ________________________");
		Utils.print("► |   creating Ruleset(" + rulesetName + ") |");
		Utils.print("   ------------------------");
		romProject = (NdRomProject) romRoot.lookupEntry(projectLocation);
		NdPromProjectFactory projectFactory = connContext.getProjectFactory();
		project = projectFactory.createProject(romProject);
		NdLocation loc = NdLocationFactory.createLocation("ProjetoBlaze Folder");
		NdPromDirectory targetLoc = (NdPromDirectory) project.lookupEntry(loc);

		ruleset = NdPromSrlConstructContentFactory.newSrlRulesetContent(project);
		ruleset.setNameContent(NdPromTextContentFactory.newTextContent(rulesetName));

		NdRomSchemaManager schemaManager;
		schemaManager = project.getRomConnectionContext().getSchemaManager();

		NdRomSchemaElement schemaElement = schemaManager.lookupSchemaElement(TYPE_SRL_RULESET, SUB_TYPE_NONE, CONTENT_TYPE_FIXED, TARGET_SRL);
		NdPromItemFactory rulesetFactory = schemaElement.getItemFactory();
		rulesetPromItem = rulesetFactory.newItem((NdPromItemContent) ruleset, project);
		targetLoc.addItem(rulesetPromItem);
		// rulesetPromItem.save();
		// project.save();
	}

	// Funcao para setar uma Ruleset que será utilizada mais frente, ou para listar, adicionar ou trocar elementos.
	public boolean setRuleset(String[] rulesetPath_RelativeFromRoot) throws NdRomException {
		Utils.print("   ________________________");
		Utils.print("► |   setting Ruluset PATH(" + rulesetPath_RelativeFromRoot + ")  |");
		Utils.print("   ------------------------");
		try {
			romProject = (NdRomProject) romRoot.lookupEntry(projectLocation);
			NdPromProjectFactory projectFatory = connContext.getProjectFactory();
			project = projectFatory.createProject(romProject);
			NdLocation rulesetLocation = NdLocationFactory.createLocation(rulesetPath_RelativeFromRoot, false);
			rulesetPromItem = (NdPromItem) project.lookupEntry(rulesetLocation);
			if (rulesetPromItem != null) {
				// Utils.print("CLASSE=> "+ rulesetPromItem.getItemContent().getClass());
				ruleset = (NdPromSrlRulesetContent) rulesetPromItem.getItemContent();
				Utils.print("Conectado no ruleset com sucesso!");
				return true;
			} else {
				Utils.print("(X) Falha ao conectar no ruleset.");
				return false;
			}
		} catch (Exception e) {
			Utils.print("(X) Falha ao conectar no ruleset.");
			e.printStackTrace();
			return false;
		}
	}

	// Funcao usada para adicionar uma "rule+body" dentro de um ruleset
	public void addRule(String ruleName, String ruleBody) throws NdRomException {
		Utils.print("   _________________");
		Utils.print("► |   Adding Rule   |");
		Utils.print("   -----------------");
		// Create 'rule1' rule
		NdPromSrlRuleContent rule = NdPromSrlConstructContentFactory.newSrlRuleContent(project);
		// set rule name
		rule.setNameContent(NdPromTextContentFactory.newTextContent(ruleName));
		NdPromSrlRuleBodyTextContent promRuleBody = NdPromSrlConstructContentFactory.newSrlRuleBodyContent(ruleBody);
		rule.setSrlRuleBodyContent(promRuleBody);
		// A rule is a ruleset item (NdPromSrlRuleContent extends NdPromSrlRulesetItemContent)
		ruleset.insertSrlRulesetItemContentAt(rule, 0);
		Utils.print("addRule(" + ruleName + ")     ->     Done");
		Utils.print("__________________________________________________\n");

	}

	// Função para adicionar parametros ao ruleset, somente para o name do Parametro e tipo, setRuleset(String) deve estar
	// configurada.
	public void addInputParameter(String name, String type) {
		Utils.print("   ___________________________");
		Utils.print("► |   Adding InputParameter   |");
		Utils.print("   ---------------------------");
		// Add 'xmlInput' parameter to ruleset
		NdPromSrlParameterContent parameter = NdPromSrlConstructContentFactory.newSrlParameterContent();
		parameter.setNameContent(NdPromTextContentFactory.newTextContent(name));
		NdPromSrlGenericTypeContent parameterType = NdPromSrlConstructContentFactory.newSrlGenericTypeContent(type);
		parameter.setSrlGenericTypeContent(parameterType);
		ruleset.insertSrlParameterContentAt(parameter, 0);
		Utils.print("Parâmetro: " + name + "(" + type + ") criado com sucesso!");
		Utils.print("__________________________________________________\n");
	}

	// Funcao para listar os itens(rules) de determinado ruleset já setado pela setRuleset(String).
	public void getItems(String location) throws NdRomException {
		Utils.print("   ________________________");
		Utils.print("► |   Listing Rule Items   |");
		Utils.print("   ------------------------");
		NdLocation rulesetLocation = NdLocationFactory.createLocation(location);
		NdPromItem rulesetPromItem = (NdPromItem) project.lookupEntry(rulesetLocation);
		NdPromSrlRuleset ruleset = (NdPromSrlRuleset) rulesetPromItem.getItemContent();
		NdPromSrlRulesetItem[] rulesetItems = ruleset.getSrlRulesetItems();

		for (int i = 0; i < rulesetItems.length; i++) {
			if (rulesetItems[i] instanceof NdPromSrlRule) {
				String ruleName = ((NdPromSrlRule) rulesetItems[i]).getName();
				Utils.print("Rulename: " + ruleName);
			}
		}
		Utils.print("__________________________________________________");
	}

	// Função para persistir as modificações caso haja, para o Storage
	public void save() throws NdRomException, Exception {
		// Qualquer NdPromItem tem a opção de save()
		rulesetPromItem.save();
		// project is an NdPromProject
		project.save();
	}

	// Função para trocar o Body "ruleBodyText" de uma rule "ruleName" dentro de uma "rulesetPath" específica.
	public void ruleBodyChange(String rulesetPath, String ruleName, String ruleBodyText) throws NdRomException {
		Utils.print("   ________________________");
		Utils.print("► |   changing Rule Body   |");
		Utils.print("   ------------------------");
		NdLocation rulesetLocation = NdLocationFactory.createLocation(rulesetPath);
		NdPromItem rulesetPromItem = (NdPromItem) project.lookupEntry(rulesetLocation);
		NdPromSrlRuleset ruleset = (NdPromSrlRuleset) rulesetPromItem.getItemContent();
		NdPromSrlRulesetItem[] rulesetItems = ruleset.getSrlRulesetItems();

		for (int i = 0; i < rulesetItems.length; i++) {
			if (rulesetItems[i] instanceof NdPromSrlRule) {
				String strRuleName = ((NdPromSrlRule) rulesetItems[i]).getName();
				if (strRuleName.equals(ruleName)) {
					// The string-based NdPromSrlRulesetItem ruleset item is cast to content-based interfaces are used exclusively.
					NdPromSrlRuleContent rule = (NdPromSrlRuleContent) rulesetItems[i];
					// replace rule text
					NdPromSrlRuleBodyTextContent ruleBody = NdPromSrlConstructContentFactory.newSrlRuleBodyContent(ruleBodyText);
					rule.setSrlRuleBodyContent(ruleBody);
					// print new rule text
					NdPromSrlRuleBodyTextContent ruleBodyTextContent = rule.getSrlRuleBodyContent();
					System.out.println("Rule body text changed => " + ruleBodyTextContent.generate());
				}
			}
		}
		rulesetPromItem.save();
		Utils.print("__________________________________________________");
	}

	// Funcao para criar um diretório na Raiz do repositório.
	public void createDirOnRoot(String dirName) throws NdRomException {
		Utils.print("   _____________________________________");
		Utils.print("► |   creating Dir On Root ("+ dirName + ")  |");
		Utils.print("   -------------------------------------");

		NdLocation location = NdLocationFactory.createLocation(new String[] { dirName }, false);
		NdRomEntry entry = romRoot.lookupEntry(location);

		if (entry == null) {
			Utils.print("Diretório não existe, criando ...");
			NdRomDirectory dirToBeCreate = ((NdRomMutableDirectory) romRoot).createDirectory(location, false);
			// NdPromDirectory projectDirectory = project.addDirectory(dirToBeCreate.getLocation());
			((NdRomMutableDirectory) dirToBeCreate).setDisplayName(dirName);
			Utils.print("(OK) Diretório *" + dirName + "* criado com sucesso!!!");
			// ((NdPromItem) entry).save();
			// project.save();
		}
	}

	public boolean isDirOnRoot(String dirName) throws NdRomException {
		Utils.print("   ________________________");
		Utils.print("► | isDirOnRoot(" + dirName + ") ? |");
		Utils.print("   ------------------------");

		NdLocation topDirectoryLocation = NdLocationFactory.createLocation(new String[] { dirName }, false);
		NdRomEntry entry = romRoot.lookupEntry(topDirectoryLocation);

		if (entry != null) {
			Utils.print("(OK) Yes, the Dir exists on Root_Repo");
			return true;
		} else {
			// Utils.print(entry.getClass().toString());
			Utils.print("(X) No, the Dir doesn´t exist on Root_Repo");
			return false;
		}

	}

	// Funcao para excluir um diretório.
	public void deleteDir(String dirName) throws NdRomException {
		Utils.print("   ________________________");
		Utils.print("► |   deleting Dir(" + dirName + ")  |");
		Utils.print("   ------------------------");

		NdLocation topDirectoryLocation = NdLocationFactory.createLocation(new String[] { dirName }, false);
		NdRomEntry promItem = romRoot.lookupEntry(topDirectoryLocation);
		if (promItem != null) {
			((NdRomMutableDirectory) romRoot).deleteEntry(dirName);
			Utils.print("(OK) Diretório *" + dirName + "* excluido com sucesso !!!");
			// NdPromDirectory projectDirectory = project.addDirectory(dirToBeCreate.getLocation());

			// AQUI PODEMOS TESTAR O TIPO DO promItem para na hora de fazer a operação nele fazer uma operação correta, pois qdo
			// deixo para executar as duas juntos exclue e cria, não sei pq mas nao rola.
			// ((NdPromItem) promItem).save();
			// project.save();
		} else {
			Utils.print("(X) Diretório não existe, impossível excluí-lo !!!");
		}

	}
}
