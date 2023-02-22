#!/usr/bin/env node
var xpath = require('xpath')
var dom   = require('xmldom').DOMParser
var fs = require('fs')

//var xml = fs.readFileSync('1863313287/self.xml', 'utf8').toString()
const args = process.argv.slice(2)
var xml = fs.readFileSync(args[0], 'utf8').toString()
var doc = new dom().parseFromString(xml)
var nodes = doc.firstChild

var document = doc.getElementsByTagName('document')
var name = document[0].getElementsByTagName('name')
var fullpath = document[0].getElementsByTagName('fullPath')
var id = document[0].getElementsByTagName('lcAttachmentId')
nome = name[0].childNodes
path = fullpath[0].childNodes
filename = id[0].childNodes
var string = nome[0].nodeValue
if (string.includes('DELETED')){
console.log(nome[0].nodeValue)
}
else{
//console.log(nome[0].nodeValue)
//console.log(path[0].nodeValue)
//console.log(filename[0].nodeValue)

//criar o diretório caso não exista.
if (!fs.existsSync("c:" + '\\' + path[0].nodeValue)){
fs.mkdirSync( "c:" + '\\' + path[0].nodeValue,{ recursive: true });
}

var real = args[0].match(/\d{1,}/)

//console.log("REAL=> copy " + __dirname +"\\"+ real[0] + "\\" + filename[0].nodeValue +"\\" + filename[0].nodeValue + ".pdf  PARA  " + __dirname + "\\" +path[0].nodeValue + "\\" + nome[0].nodeValue + ".pdf"  )
fs.copyFile("D:\\workspace\\data\\documents\\"+ real[0] + "\\" + filename[0].nodeValue +"\\" + filename[0].nodeValue + ".pdf" , "c:\\" + path[0].nodeValue+ "\\" + nome[0].nodeValue + ".pdf" , (err) => {
if (err) throw err;
//console.log("Copiado " + __dirname +"\\"+ real[0] + "\\" + filename[0].nodeValue +"\\" + filename[0].nodeValue + ".pdf  PARA  " + __dirname + "\\" +path[0].nodeValue + "\\" + nome[0].nodeValue + ".pdf");
});
}
