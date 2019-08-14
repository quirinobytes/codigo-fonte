#!/usr/bin/env node

var fs = require('fs');
var AWS = require('aws-sdk');
var credentials = new AWS.SharedIniFileCredentials({profile: 'veloe-ppd'});
AWS.config.credentials = credentials;
var table = "ArMestrePedidoEntregaHistorico"
var docClient = new AWS.DynamoDB.DocumentClient()
var params = {
  TableName:table
};
var resultadoScan = [];

function updateItems(){
    for (i = 0; i < resultadoScan.length; i++) {
      if (resultadoScan[i].logradouro) {
        let numLogradouro = resultadoScan[i].numLogradouro
        let params = {
          TableName:table,
          Key:{
            "Id": resultadoScan[i].Id
          },
          UpdateExpression: "set logradouro.numLogradouro = :numLogradouro",
          ExpressionAttributeValues: {
            ":numLogradouro": numLogradouro.toString()
          },
          ReturnValues: "UPDATED_NEW"
        }
        docClient.update(params, function(err, data){
          if(err) {
            console.error("Unable to update item. Error JSON:", JSON.stringify(err, null, 2));
          } else {
            console.log("UpdateItem succeeded:", JSON.stringify(data, null, 2));
          }
        })
      }
    }
}

function scanDb() {
  var params = {
    TableName:table
  }
  console.log("Scanning table...");
  docClient.scan(params, onScan);
}

function onScan(err, data) {
  if (err) {
    console.error("Unable to scan the table. Error JSON:", JSON.stringify(err, null, 2));
  } else {
    console.log("Scan succeeded.");
    data.Items.forEach((data) => {
      if (data.logradouro){
        resultadoScan.push({"Id": data.Id, "numLogradouro": data.logradouro.numLogradouro})
        // console.log(data.Id)
        // console.log(data.logradouro.numLogradouro)
        // console.log('=================')
      }
    })
    if (typeof data.LastEvaluatedKey != "undefined") {
      console.log("Scanning for more...");
      console.log("Resultados: " + resultadoScan.length)
      params.ExclusiveStartKey = data.LastEvaluatedKey;
      docClient.scan(params, onScan);
    } else {
      updateItems()
    }
  }
}

scanDb()
