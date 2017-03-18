var crawlerJS = require('crawler-js');

var crawler = {

	interval: 1000,
	getSample: 'http://science.gsfc.nasa.gov/sed/index.cfm?fuseAction=people.staffList&navOrgCode=600&nav_about_us&PageNum=1',
	get:'http://science.gsfc.nasa.gov/sed/index.cfm?fuseAction=people.staffList&navOrgCode=600&nav_about_us&PageNum=[numbers:1:10000:1]',
	preview: 3,
	extractors: [
		{
		selector: '#border-spacing tr',
		elements: "data.nome = $(this).children('td').eq(0).children('a').text(); 
		           data.filial = $(this).children('td').eq(3).text();
				   data.telefone = $(this).children('td').eq(4).text();",
		mongoCollection: 'nasa',
		csv: {name:'funcionarios-nasa.csv'}
		}
	] 

}

var config = {
	mongoDB: 'TDC'
	mongoDBhost: 'localhost' 
	mongoDBPort: '27017'
}