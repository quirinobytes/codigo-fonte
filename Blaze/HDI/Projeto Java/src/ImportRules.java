
import tools.Utils;

import com.blazesoft.repository.base.NdWorkspaceConnection;
import com.blazesoft.repository.file.NdFileRepositoryConnection;
import com.blazesoft.repository.naming.NdLocation;
import com.blazesoft.repository.naming.NdLocationFactory;
import com.blazesoft.template.engine.NdInstantiation;
import com.blazesoft.template.engine.NdInstantiationElement;
import com.blazesoft.template.metaphor.NdMetaphorSupport;
import com.blazesoft.template.repository.NdPromDirectory;
import com.blazesoft.template.repository.NdPromEntry;
import com.blazesoft.template.repository.NdPromItem;
import com.blazesoft.template.repository.NdPromItemContent;
import com.blazesoft.template.repository.NdPromItemFactory;
import com.blazesoft.template.repository.NdPromProject;
import com.blazesoft.template.repository.NdPromProjectFactory;
import com.blazesoft.template.repository.NdRomConnectionContext;
import com.blazesoft.template.repository.NdRomConnectionException;
import com.blazesoft.template.repository.NdRomConnectionManager;
import com.blazesoft.template.repository.NdRomDirectory;
import com.blazesoft.template.repository.NdRomEntry;
import com.blazesoft.template.repository.NdRomException;
import com.blazesoft.template.repository.NdRomFactory;
import com.blazesoft.template.repository.NdRomItem;
import com.blazesoft.template.repository.NdRomMutableDirectory;
import com.blazesoft.template.repository.NdRomProject;
import com.blazesoft.template.repository.NdRomSchemaConstants;
import com.blazesoft.template.repository.NdRomSchemaElement;
import com.blazesoft.template.repository.NdRomSchemaManager;
import com.blazesoft.template.repository.events.NdPromObjectModifiedEvent;
import com.blazesoft.template.repository.objects.NdPromEntityNode;
import com.blazesoft.template.repository.objects.NdPromTextContentFactory;
import com.blazesoft.template.repository.objects.flow.NdPromFlowConstructContentFactory;
import com.blazesoft.template.repository.objects.flow.NdPromFlowFlowContent;
import com.blazesoft.template.repository.objects.flow.NdPromFlowRuleflowContent;
import com.blazesoft.template.repository.objects.flow.NdPromFlowTaskContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlArrayContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlBodyTextContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlCall;
import com.blazesoft.template.repository.objects.rules.NdPromSrlCollectionTextContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlConstraintTextContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlConstructContentFactory;
import com.blazesoft.template.repository.objects.rules.NdPromSrlDo;
import com.blazesoft.template.repository.objects.rules.NdPromSrlFunctionContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlGenericTypeContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlObjectModelVisitor;
import com.blazesoft.template.repository.objects.rules.NdPromSrlParameterContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlPatternContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRule;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRuleBodyTextContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRuleContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRuleset;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRulesetContent;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRulesetItem;
import com.blazesoft.template.repository.objects.rules.NdPromSrlStatement;
 

public class ImportRules implements NdRomSchemaConstants {
 
	private String repositorioPath;
	private Integer rulePosition;
	private NdFileRepositoryConnection con;
	private NdRomConnectionManager conManager;

	// VOce precisa de um Rom project
	private NdRomProject romProject;
	private NdRomDirectory romDirectory;

	// Voce precisa de um project(PROM)
	private NdPromProject project;
	
	//targetDirectory é onde recebe o Diretório do projeto.
	private NdPromDirectory targetDirectory;
	
	//voce precisa de um NdLocation loc para receber o caminho do projeto, usaremos para criar o Ruleset "subscricao".
	private NdLocation loc;
	private NdLocation subscricaoLoc;
	
	private NdPromSrlRulesetContent ruleset;
	private NdPromSrlRuleset ruleset2;
	private NdPromItem rulesetItem;
	private NdRomDirectory romRoot;
	NdLocation projectLocation;
	NdPromItem rulesetPromItem;
	
	public ImportRules() {
		rulePosition = 0;
	}

	public void conectaRepositorio(String path) throws NdRomException {
		repositorioPath = path;
		con = new NdFileRepositoryConnection();
		con.setRepositoryFolder(path);
		conManager = NdRomFactory.newRepositoryConnectionManager(con);
		conManager.connect();

		NdRomConnectionContext conContext = conManager.getConnectionContext();
		System.out.println("Nome do Repositório: " + conContext.toString());
		romRoot = conContext.getRoot();

		String[] localProject = new String[] {"Pasta","ProjetoBlaze Folder","ProjetoBlaze"};
		NdLocation projectLocation = NdLocationFactory.createLocation(localProject, true);
		romProject = (NdRomProject) romRoot.lookupEntry(projectLocation);
		NdPromProjectFactory projectFatory = conContext.getProjectFactory();

		project = projectFatory.createProject(romProject);
		loc = NdLocationFactory.createLocation("ProjetoBlaze Folder");
	}
	
	public void createRuleset() throws NdRomException {
		targetDirectory = (NdPromDirectory) project.lookupEntry(loc);
		
		ruleset = NdPromSrlConstructContentFactory.newSrlRulesetContent(project);	
		ruleset.setNameContent(NdPromTextContentFactory.newTextContent("subscricao"));
	}

	public void conecta2() throws NdRomException {
		
		con = new NdFileRepositoryConnection();
		con.setRepositoryFolder("C:\\WORKSPACE\\API\\Repositorio");
		conManager = NdRomFactory.newRepositoryConnectionManager(con);
		conManager.connect();
		NdRomConnectionContext conContext = conManager.getConnectionContext();
		System.out.println("Nome do Repositório: " + conContext.toString());
		romRoot = conContext.getRoot();
		
		//Preparando o project
		String[] localProject = new String[] {"Pasta","ProjetoBlaze Folder","ProjetoBlaze"};
		 projectLocation = NdLocationFactory.createLocation(localProject, true);
		romProject = (NdRomProject) romRoot.lookupEntry(projectLocation);
		NdPromProjectFactory projectFatory = conContext.getProjectFactory();
		project = projectFatory.createProject(romProject);
		loc = NdLocationFactory.createLocation("ProjetoBlaze Folder");
		
		//

		NdRomEntry[] allEntriesInRepository = romRoot.getEntries();		
		
		int c=0;
		
		for (c=0 ; c < allEntriesInRepository.length ; c++) {
			Utils.print(allEntriesInRepository[c].getDisplayName());
		}
		
		NdLocation rulesetLocation = NdLocationFactory.createLocation(new String[] {"ProjetoBlaze Folder","subscricao"}, false);
		rulesetPromItem = (NdPromItem)project.lookupEntry(rulesetLocation);
		
		if (rulesetPromItem == null ) Utils.print("é null");
		else Utils.print("ACHEIIIIII");
		
		NdPromSrlRuleset rulesetInterno = (NdPromSrlRuleset) rulesetPromItem.getItemContent();
		// rulesetInterno.insertSrlRulesetItemContentAt
		// rulesetInterno.get
		// rulesetPromItem.get
		ruleset = (NdPromSrlRulesetContent) rulesetPromItem.getItemContent();
		
		
		
//		for (NdPromSrlRulesetItem rulesetItem:  rulesetInterno.getSrlRulesetItems() ) {// obtem os iens (regras) do ruleset  em um array
//			
//			//ruleset = (NdPromSrlRulesetContent) rulesetItem.getContainingSrlRuleset().getItem();
//			Utils.print(rulesetItem.getContainingSrlRuleset().getItem().getDisplayName());
//			//Utils.print(rulesetItem.getContainingSrlRuleset().getItem().getContent().toString());
//			Utils.print(rulesetItem.getContainingSrlRuleset().getClass().toString());
//			//ruleset = (NdPromSrlRulesetContent) rulesetItem.getContainingSrlRuleset().getItem().; //NdPromSrlRulesetContent 
//		}
//		
		//Utils.print((String) rulesetInterno.generate());
				
	}
	
	
	public void connectRuleset() throws NdRomException,Exception{
		String[] subscricaoLocalProject = new String[] { "Pasta", "ProjetoBlaze Folder", "ProjetoBlaze"};
		//NdLocation subscLocation = NdLocationFactory.createLocation(subscricaoLocalProject, true);
		NdLocation subscLocation = NdLocationFactory.createLocation("./subscricao", false);
		Utils.print("LOCATION[0] => " + subscLocation.getComponent(0).toString());
		Utils.print("LOCATION[1] => " + subscLocation.getComponent(1).toString());
		
		//essa é a idéia que passou!!! troca o subscLocation pelo loc que vc vai ver q o CAST está fucionando para esse rulesetcontent
		//NdPromSrlRulesetContent ruleset = (NdPromSrlRulesetContent) project.lookupEntry(loc);
//		NdPromSrlRulesetContent ruleset = (NdPromSrlRulesetContent) project.lookupEntry(subscLocation);
		
		//a segunda ideia é
		NdPromItem promItem = (NdPromItem)(project.lookupEntry(subscLocation));
		Utils.print("kkkkkkkkkkkkkkkk");
		Utils.print(" " + promItem);
		//Utils.print("VAI => " + ( project.lookupEntry(subscLocation).toString()));
		
		NdPromItemContent content = promItem.getItemContent();
		NdInstantiationElement instantiationElt = null;

		if (content instanceof NdInstantiation) {
		   instantiationElt = (NdInstantiationElement)content;
		}
				
		String metaphorInstanceName = "subscricao";
		NdInstantiationElement instanceElt = instantiationElt.safeLookup(metaphorInstanceName);
		
		if (NdMetaphorSupport.isDecisionGraphInstance(instanceElt)) {

			   Utils.print("OIEEEEEEEEEEEE");

			}
		
		//Utils.print("RULESET => " + ruleset.toString().toString());
		
		//NdPromSrlRuleset ruleset = (NdPromSrlRuleset) item.getItemContent();
		//String name = ruleset.getName();
		//Utils.print("NAME=> "+ name);
		
		
		//NdRomProject subscRomProject = (NdRomProject)romRoot.lookupEntry(subscLocation);
//		//project.dispose(); 
		//NdRomConnectionContext conContext = conManager.getConnectionContext();
		//NdPromProjectFactory projectFactory = conContext.getProjectFactory();
		//NdPromProject subscProject = projectFactory.createProject(subscRomProject);
		//ruleset = (NdPromSrlRulesetContent) NdPromSrlConstructContentFactory.newSrlRulesetContent(subscProject);
//		ruleset.setNameContent(NdPromTextContentFactory.newTextContent("subscricao"));
		//ruleset.setNameContent(NdPromTextContentFactory.newTextContent("subscricao"));		
	}
	

	public void createRulesetInputParameter(String name,String type) {
		// Add 'xmlInput' parameter to ruleset
		NdPromSrlParameterContent parameter = NdPromSrlConstructContentFactory.newSrlParameterContent();
		parameter.setNameContent(NdPromTextContentFactory.newTextContent(name));
		NdPromSrlGenericTypeContent parameterType = NdPromSrlConstructContentFactory.newSrlGenericTypeContent(type);
		parameter.setSrlGenericTypeContent(parameterType);
		ruleset.insertSrlParameterContentAt(parameter, 0);
		Utils.print("Parâmetro: " + name + "(" +type+") criado com sucesso!");
	}
	
	public void addRule(String ruleName, String regraXML) throws NdRomException {
						
		// Create 'rule1' rule
		NdPromSrlRuleContent rule = NdPromSrlConstructContentFactory.newSrlRuleContent(project);
		Utils.print("rule criada");
		
		// set rule name
		rule.setNameContent(NdPromTextContentFactory.newTextContent(ruleName));

		NdPromSrlRuleBodyTextContent ruleBody = NdPromSrlConstructContentFactory.newSrlRuleBodyContent(regraXML);
		rule.setSrlRuleBodyContent(ruleBody);

		// A rule is a ruleset item (NdPromSrlRuleContent extends NdPromSrlRulesetItemContent)
		//Utils.print(ruleset.toString());
		ruleset.insertSrlRulesetItemContentAt(rule, 0);
		rulePosition++;

		// // Create 'boughtProducts' pattern
		// NdPromSrlPatternContent boughtPattern =
		// NdPromSrlConstructContentFactory.newSrlPatternContent(project);
		// boughtPattern.setNameContent(NdPromTextContentFactory.newTextContent("boughtProducts"));
		// NdPromSrlGenericTypeContent patternType =
		// NdPromSrlConstructContentFactory.newSrlGenericTypeContent("Product");
		// boughtPattern.setSrlGenericTypeContent(patternType);

		// // set collection
		// NdPromSrlCollectionTextContent collection =
		// NdPromSrlConstructContentFactory.newSrlCollectionContent("shopper.purchasedProducts");
		// boughtPattern.setSrlCollectionContent(collection);

		// A pattern is a ruleset item

		// (NdPromSrlPatternContent extends NdPromSrlRulesetItemContent)
		// ruleset.insertSrlRulesetItemContentAt(boughtPattern, 0);

		// // Create 'promoProducts' pattern
		// NdPromSrlPatternContent promoPattern =
		// NdPromSrlConstructContentFactory.newSrlPatternContent(project);
		// promoPattern.setNameContent(NdPromTextContentFactory.newTextContent("promoProducts"));

		// //set the type
		//
		// NdPromSrlGenericTypeContent patternType1 =
		// NdPromSrlConstructContentFactory.newSrlGenericTypeContent("Product");
		// promoPattern.setSrlGenericTypeContent(patternType1);

		// //set the constraint
		// NdPromSrlConstraintTextContent constraint =
		// NdPromSrlConstructContentFactory.newSrlConstraintContent("promotion = true");
		// promoPattern.setSrlConstraintContent(constraint);
		// ruleset.insertSrlRulesetItemContentAt(promoPattern, 1);

		// Create NdPromItem *rulesetItem* for the ruleset, add to a PROM directory and save.

	}
	
	public void save() throws NdRomException,Exception {
		// schemaManager is an NdRomSchemaManager
		NdRomSchemaManager schemaManager;
		schemaManager = project.getRomConnectionContext().getSchemaManager();

				NdRomSchemaElement schemaElement = schemaManager.lookupSchemaElement(TYPE_SRL_RULESET, SUB_TYPE_NONE, CONTENT_TYPE_FIXED, TARGET_SRL);
				NdPromItemFactory rulesetFactory = schemaElement.getItemFactory();
				rulesetItem = rulesetFactory.newItem((NdPromItemContent) ruleset, project);
				
		
		
		
		NdLocation location = NdLocationFactory.createLocation(new String[]{"Pasta", "ProjetoBlaze Folder"}, false);
		// targetDirectory is an NdPromDirectory
		//MOdificando para funcionar: PROM item must be jadded to a PROM directory before it can be saved.
		targetDirectory = (NdPromDirectory) project.lookupEntry(loc);				
		targetDirectory.addItem(rulesetItem);
		rulesetItem.save();
		
		// project is an NdPromProject
		project.save();
	}
	
	public void save2() throws NdRomException,Exception {

	rulesetPromItem.save();
	// project is an NdPromProject
	project.save();
	}
	
	public void exemplo() throws NdRomException {
		
		// Connect to a repository and create a project, add a folder to the project.
		NdFileRepositoryConnection connection = new NdFileRepositoryConnection();
		// Change the path to your repository as appropriate. The repository should exist.
		connection.setRepositoryFolder("C:\\WORKSPACE\\API\\Repositorio");
		// Connect to repository
		NdRomConnectionManager connectionMgr = NdRomFactory.newRepositoryConnectionManager(connection);
		connectionMgr.connect();
		NdRomConnectionContext conContext = connectionMgr.getConnectionContext();
		NdRomDirectory romRoot = conContext.getRoot();
		
		Utils.print("Conectado no repositório: ");
		
		NdLocation location = NdLocationFactory.createLocation(new String[]{"Pasta", "ProjetoBlaze Folder"}, false);
		NdRomDirectory promProjetoBlaze_Folder = (NdRomDirectory) romRoot.lookupEntry(location);
		
		Utils.print("promProjetoBlaze_Folder = ProjetoBlaze_Folder ");
		
		// Create a new directory, "Replicate PROM Project", under the "PROM API" directory
		location = NdLocationFactory.createLocation(new String[]{"Replicate PROM Project"}, false);
		NdRomDirectory	 topDirectory = ((NdRomMutableDirectory) promProjetoBlaze_Folder).createDirectory(location, true);
		((NdRomMutableDirectory) topDirectory).setDisplayName("Replicate PROM Project");
		
		// Each component of a location should be in a separate string in the string array.
		NdLocation projectLocation = NdLocationFactory.createLocation(new String[]{"Entity Creation"}, false);
		
		// The location used to create a directory must be a relative one and have a single component.
		NdRomDirectory entityCreationDirectory = ((NdRomMutableDirectory) topDirectory).createDirectory(projectLocation, true);
		((NdRomMutableDirectory) entityCreationDirectory).setDisplayName("Entity Creation");
		
		// Create a Prom project in the "Entity Creation" directory
		NdPromProjectFactory projectFactory = conContext.getProjectFactory();
		NdPromProject project = projectFactory.createProject(NdLocationFactory.createLocation(new String[]{"Pasta", "ProjetoBlaze Folder", "Replicate PROM Project", "Entity Creation"}, true));
		project.setDisplayName("Entity Creation");
		
		// Add directory to project
		NdPromDirectory projectDirectory = project.addDirectory(entityCreationDirectory.getLocation());
		
		// Create three directories and add to project.
				location = NdLocationFactory.createLocation(new String[]{"Cross-sell Rules"}, false);
				NdRomDirectory directory = ((NdRomMutableDirectory) topDirectory).createDirectory(location, true);
				((NdRomMutableDirectory) directory).setDisplayName("Cross-sell Rules");
				NdPromDirectory crossSellDirectory = project.addDirectory(directory.getLocation());
				
				location = NdLocationFactory.createLocation(new String[]{"Products"}, false);
				directory = ((NdRomMutableDirectory) topDirectory).createDirectory(location, true);
				((NdRomMutableDirectory) directory).setDisplayName("Products");
				NdPromDirectory productDirectory = project.addDirectory(directory.getLocation());
				
				location = NdLocationFactory.createLocation(new String[]{"Test"}, false);
				directory = ((NdRomMutableDirectory) topDirectory).createDirectory(location, true);
				((NdRomMutableDirectory) directory).setDisplayName("Test");
				NdPromDirectory testDirectory = project.addDirectory(directory.getLocation());

		
			NdPromProject subscricao = projectFactory.createProject(NdLocationFactory.createLocation(new String[]{"Pasta", "ProjetoBlaze Folder", "Replicate PROM Project", "Entity Creation"}, true));
			subscricao.setDisplayName("Entity Creation");
				
	}
	
	public void list() throws NdRomException {
		NdLocation rulesetLocation = NdLocationFactory.createLocation("ProjetoBlaze Folder/ProjetoBlaze");
		NdPromItem rulesetPromItem = (NdPromItem) project.lookupEntry(rulesetLocation);
		NdPromSrlRuleset ruleset = (NdPromSrlRuleset) rulesetPromItem.getItemContent();
		NdPromSrlRulesetItem[] rulesetItems = ruleset.getSrlRulesetItems();
		for (int i = 0; i < rulesetItems.length; i++) {
			if (rulesetItems[i] instanceof NdPromSrlRule) {
				String ruleName = ((NdPromSrlRule) rulesetItems[i]).getName();
				if (ruleName.equals("rule1")) {
					// The string-based NdPromSrlRulesetItem ruleset item is cast to
					// content-based interfaces are used exclusively.
					NdPromSrlRuleContent rule = (NdPromSrlRuleContent) rulesetItems[i];
					// replace rule text
					NdPromSrlRuleBodyTextContent ruleBody =
							NdPromSrlConstructContentFactory.newSrlRuleBodyContent("rule body replacement text");
					rule.setSrlRuleBodyContent(ruleBody);
					// print new rule text
					NdPromSrlRuleBodyTextContent ruleBodyTextContent =
							rule.getSrlRuleBodyContent();
					System.out.println("The replacement rule body text is" + ruleBodyTextContent.generate());
				}
			}
		}
	}
	
	public void printXML() {}

}