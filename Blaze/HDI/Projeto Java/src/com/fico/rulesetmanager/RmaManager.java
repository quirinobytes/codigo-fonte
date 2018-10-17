package com.fico.rulesetmanager;

import com.blazesoft.repository.file.NdFileRepositoryConnection;
import com.blazesoft.rma.NdRMAException;
import com.blazesoft.rma.NdRmaEditableFile;
import com.blazesoft.rma.NdRmaFile;
import com.blazesoft.rma.NdRmaFileContent;
import com.blazesoft.rma.NdRmaInstance;
import com.blazesoft.rma.NdRmaProject;
import com.blazesoft.rma.NdRmaRepository;
import com.blazesoft.rma.NdRmaRepositoryFactory;
import com.blazesoft.template.introspector.NdAbstractInstanceListNode;
import com.blazesoft.template.introspector.NdAbstractInstanceNode;
import com.blazesoft.template.introspector.NdInstanceElementNode;
import com.blazesoft.template.repository.NdRomException;
import com.blazesoft.template.repository.objects.rules.NdPromSrlRulesetContent;

import tools.Utils;

/**
 * @author RafaelQuirino
 *
 */
/**
 * @author RafaelQuirino
 *
 */
public class RmaManager extends NdRMAException {

	private static final long serialVersionUID = 1L;
	public NdRmaRepository rmaRepository;
	public NdRmaProject rmaProject;
	public NdRmaInstance rmaInstance;
	public NdRmaFile rmaFile;
	public NdPromSrlRulesetContent ruleset;
	public Utils u;
	public boolean debug = false;

	@SuppressWarnings("static-access")
	public RmaManager(DEBUG debug) {
		this.u = new Utils();
		if (debug == DEBUG.YES) {
			u.debug = true;
		}
		else {
			u.debug = false;
		}
	}

	// Retorna true se sucesso, passar o caminho do Repositório como parametro C://WORKSPACE//PROJETO//REPOSITORIO
	public boolean conectaRepositorio(String path) throws NdRomException, NdRMAException {
		// int chars = "conectaRepositorio".length() + path.length();
		// u.setPontos( chars);
		u.startBanner("conectaRepositorio", path);
		NdFileRepositoryConnection connection = new NdFileRepositoryConnection();
		// connection.setUser("Template Developer"); // needed only in versioned repositories
		connection.setRepositoryFolder(path);
		rmaRepository = NdRmaRepositoryFactory.connectToRepository(connection);

		// se diferente de null é pq achou o repositorio.
		if (rmaRepository == null) {
			u.errorBanner();
			return false;
		} else {
			Utils.print("(OK) Conectado ao repositorio com sucesso. [ " + rmaRepository.getRepositoryConnection().getRepositoryName() + " ]");
			Utils.print("(OK) Path do [ " + rmaRepository.getRepositoryConnection().getRepositoryName() + " ] => " + connection.getRepositoryFolder());
			u.endBanner();
			return true;
		}

	}

	/**
	 * @param projectPath
	 *            - String com o Caminho no File system, relativo a partir da raiz do repositório do projeto exemplo:
	 *            "/Pasta/ProjetoBlaze Folder/ProjetoBlaze"
	 * @throws NdRMAException
	 */
	public void setProjectPath(String projectPath) throws NdRMAException {
		u.startBanner("setProjectPath", projectPath);
		try {
			rmaProject = rmaRepository.openProject(projectPath);

		} catch (Exception e) {
			Utils.print("Erro ao tentar setar o PROJECT PATH: " + projectPath + " \nError Message: " + e.getMessage());
		}
		u.endBanner();

	}

	public NdRmaInstance obtainInstanceByDisplayName(String instanceName) throws NdRMAException {
		NdRmaInstance instance = null;
		NdRmaInstance[] rmaInstances = rmaProject.getAllInstances(false);
		for (int i = 0; i < rmaInstances.length; i++) {
			rmaFile = ((NdRmaFileContent) rmaInstances[i]).getFile();
			if (rmaFile.getDisplayName().equals(instanceName)) {
				instance = rmaInstances[i];
				break;
			}
		}
		return instance;
	}

	// retorna o PATH do elemento caso encontre, ou retorna null.
	public String findSegment(String elementName) throws NdRMAException {
		u.startBanner("findSegment", elementName);
//		NdAbstractInstanceListNode instance = null;
//		String name;
		String basePath = null;
		String ruleName = null;
		int c = 0;
		// NdInstanceElementNode node = null;
		NdInstanceElementNode[] instanceElementNodes = rmaInstance.getInstanceElementNodes();
		Utils.print("Total nodes na instancia  => " + instanceElementNodes.length);

		for (NdInstanceElementNode node : rmaInstance.getInstanceElementNodes()) {
			// Utils.print("Oi");
			// name = ((NdAbstractInstanceNode) node).getName();
			if (node instanceof NdAbstractInstanceListNode) {
				// Utils.print("encontrei um NdAbstractInstanceListNode");
				// Utils.print("NODE PATH= " + ((NdAbstractInstanceNode)node).getPath() );
				// Utils.print("NODE NAME= " + ((NdAbstractInstanceListNode) node).getName());
				// Utils.print(((NdAbstractInstanceListNode) node).getListItemNode(0).getName());
				// Utils.print(((NdAbstractInstanceListNode) node).getListItemNode(1).getName());
				// Utils.print(((NdAbstractInstanceListNode) node).getListItemNode(2).getName());
				// Utils.print("NODE PATH(2)= " + ((NdAbstractInstanceListNode) node).getListItemNode(2).getPath());

				c = ((NdAbstractInstanceListNode) node).getCount();
				// Utils.print("Numero de Rules nessa instancia = " + c);

				for (int ii = c - 1; ii >= 0; ii--) {

					ruleName = ((NdAbstractInstanceListNode) node).getListItemNode(ii).getName();
					if (ruleName.equals(elementName)) {
						basePath = ((NdAbstractInstanceListNode) node).getListItemNode(ii).getPath();
						u.endBanner();
						return basePath;
					}
				}

				// u.endBanner();
				// return basePath;

				// for ( int ii = c; ii < c ; ii++) {
				// Utils.print("ii=" + ii);
				// ruleName = ((NdAbstractInstanceListNode) node).getListItemNode(ii).getName();
				// if (ruleName.equals(elementName)) {
				// Utils.print("KKKKKKKKKKKKKKKKKKK");
				// basePath = ((NdAbstractInstanceListNode)node).getListItemNode(ii).getPath();
				// return basePath;
				// }
				// }
			}
		}
		u.errorBanner();
		return null;
	}

	/**
	 * @param instanceName
	 *            - Necessário definir uma instancia antes chamar os demais métodos abaixo (mais sofisticados).
	 * @throws NdRMAException
	 */
	public void setInstanceName(String instanceName) throws NdRMAException {
		u.startBanner("setInstanceName", instanceName);
		rmaInstance = obtainInstanceByDisplayName(instanceName);
		if (rmaInstance == null) {
			Utils.print("(X) Erro ao tentar obter uma instância: " + instanceName);
			u.errorBanner();
		} else {
			Utils.print("- obtainInstanceByDisplayName(" + instanceName + ")\t =>  [ OK ]");
			Utils.print("- " + instanceName + ".getDisplayName()  \t\t =>  [ " + rmaInstance.getFile().getDisplayName() + " ]");
			Utils.print("- " + instanceName + ".getTemplate()    \t\t =>  [ " + rmaInstance.getTemplate().getDisplayName() + " ]");
			u.endBanner();
		}

	}

	/**
	 * @param ElementName
	 * @throws NdRMAException
	 */
	public void listRules() throws NdRMAException {
		u.startBanner("listRules");
		// NdAbstractInstanceListNode instance = null;
		// String name;
		// String path = null;
		// String basePath = null;
		// String ruleName = null;
		boolean acheiUm = false;
		int c;
		// NdInstanceElementNode node = null;
		NdInstanceElementNode[] instanceElementNodes = rmaInstance.getInstanceElementNodes();
		Utils.print("Actual Instance Name \t=> [ " + rmaInstance.getFile().getDisplayName() + " ]");
		Utils.print("Total de child Nodes \t=> [ " + instanceElementNodes.length + " ]\n");

		for (NdInstanceElementNode node : rmaInstance.getInstanceElementNodes()) {
			if (node instanceof NdAbstractInstanceListNode) {
				acheiUm = true;
				c = ((NdAbstractInstanceListNode) node).getCount();
				for (int ii = c - 1; ii >= 0; ii--) {
					Utils.print(((NdAbstractInstanceListNode) node).getListItemNode(ii).getName());
				}
				break;
			}

		}
		if (acheiUm)
			u.endBanner();
		else
			u.errorBanner();
	}

	public NdInstanceElementNode addSegment(String nodePath) throws NdRMAException {
		u.startBanner("nodePath", nodePath);
		NdInstanceElementNode node = null;
		NdInstanceElementNode instanceElementNode = rmaInstance.lookupInstanceElementNode(NdAbstractInstanceNode.INSTANCE_SECTION_INSTANTIATION, nodePath, false);
		if (instanceElementNode instanceof NdAbstractInstanceListNode) {
			NdAbstractInstanceListNode instanceListNode = (NdAbstractInstanceListNode) instanceElementNode;
			// This variation of addListInstance() is used when the
			// list node may only contain an instance of the same template.
			rmaInstance.addListInstance(instanceListNode);
			// Every time you perform a change to a NdInstanceElementNode
			// you need to fetch that node again.
			instanceListNode = (NdAbstractInstanceListNode) rmaInstance.lookupInstanceElementNode(NdAbstractInstanceNode.INSTANCE_SECTION_INSTANTIATION, nodePath, false);
			int count = instanceListNode.getCount();
			if (count > 0) {
				// Return the parent node of the new segment,
				// which is the last node in the node list.
				node = instanceListNode.getListItemNode(count - 1);
			} else {
				u.errorBanner();
				return null;
			}
		}
		u.endBanner();
		return node;
	}

	/**
	 * @param nodePath
	 * @param segmentName
	 * @throws NdRMAException
	 */
	public void removeSegment(String nodePath, String segmentName) throws NdRMAException {
		Utils.print("   ________________________");
		Utils.print("► |   removeSegment nodePath(" + nodePath + ", " + segmentName + ") |");
		Utils.print("   ------------------------");
		String name;
		NdInstanceElementNode node = null;
		NdInstanceElementNode instanceElementNode = rmaInstance.lookupInstanceElementNode(NdAbstractInstanceNode.INSTANCE_SECTION_INSTANTIATION, nodePath, false);
		if (instanceElementNode instanceof NdAbstractInstanceListNode) {
			int count = ((NdAbstractInstanceListNode) instanceElementNode).getCount();
			for (int ii = 0; ii < count; ii++) {
				node = ((NdAbstractInstanceListNode) instanceElementNode).getListItemNode(ii);
				name = ((NdAbstractInstanceNode) node).getName();
				if (name.equals(segmentName)) {
					rmaInstance.deleteListNode((NdAbstractInstanceNode) node);
					Utils.print("Item removed");
					break;
				}
			}
		}
		rmaProject.save();
		rmaProject.refresh();
	}

	protected void setNodeValue(String path, String value) throws NdRMAException {
		u.startBanner("setNodeValue", path + "," + value);
		// Utils.print("Entrei na setNodeValue\npath= " + path);
		// Utils.print("Vou alterar a rule = " + path + " -> " + value);
		NdInstanceElementNode valueNode = rmaInstance.lookupInstanceElementNode(NdAbstractInstanceNode.INSTANCE_SECTION_INSTANTIATION, path, false);
		rmaInstance.setNodeValue(valueNode, value);
		u.endBanner();
	}

	public void save() throws NdRMAException {
		((NdRmaEditableFile) rmaFile).save();
	}
	
	public void projectSave() throws NdRMAException {
		rmaProject.save();
	}
	
	

	public void disconnect() throws NdRMAException {
		u.statusFinal();
		rmaProject.save();
		rmaProject.refresh();
		rmaRepository.disconnect();
	}

	public void addRule(String ruleName, String action, String condition, String comment) throws NdRMAException {
		NdInstanceElementNode node = addSegment("newRules");
		String basePath = ((NdAbstractInstanceNode) node).getPath();
		if (node instanceof NdAbstractInstanceNode) {
			setNodeValue((basePath + ".name"), ruleName);
			setNodeValue((basePath + ".comment"), comment);
			setNodeValue((basePath + ".ruleCondition"), condition);
			setNodeValue((basePath + ".ruleAction"), action);
		}
	}
}
