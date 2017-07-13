#!/usr/bin/env python3.4

import telepot
import subprocess
import csv
import datetime

#token do bot
bot = telepot.Bot("389133150:AAFqZmu_2WMCHRBpUlv2DyFeCW2Hn6CEwQc")
global_resposta = ""

def rec(msg):
	chat = msg['chat']
	idChat = chat['id']
	mensagemTxt = msg['text']
	#arrumar essa funcao, erro devido a chamada do rec com o parametro fake
	print(datetime.datetime.fromtimestamp(
        int(msg['date'])).strftime('%H:%M:%S %d-%m') + "|" +
msg['from']['first_name']+ "| " + msg['text'])
	#print(mensagemTxt)
	if (mensagemTxt == '/petr4' or mensagemTxt == '/vale5' or mensagemTxt ==
'/usim5' or mensagemTxt == '/csna3'  or mensagemTxt == '/goau4'  or mensagemTxt
== '/ggbr4'  or mensagemTxt == '/jbss3' and mensagemTxt != '/all') :
		with open("/root/workspace/bolsa-systems/blueMoney/csv/all"+msg['text']+'.csv', "r") as f:
			read_data = f.read()
			f.closed
		csv_reader = csv.reader(read_data)
		csv_data = list(csv_reader)
		#print (csv_data)
		bot.sendMessage(idChat, msg['text'] + " -> R$ " + csv_data[6][0]
+ " (" + csv_data[10][0] + ")" )
	if (mensagemTxt == '/all') :
		#gambiarra para chamar a funcao fazer enviar a mensagem, cuidado o msg é montado o json ali o.
		rec({'text':'/vale5','chat':msg['chat'],'from':msg['from'],'date':msg['date']})
		rec({'text':'/petr4','chat':msg['chat'],'from':msg['from'],'date':msg['date']})
		rec({'text':'/ggbr4','chat':msg['chat'],'from':msg['from'],'date':msg['date']})
		rec({'text':'/goau4','chat':msg['chat'],'from':msg['from'],'date':msg['date']})
		rec({'text':'/usim5','chat':msg['chat'],'from':msg['from'],'date':msg['date']})
		rec({'text':'/csna3','chat':msg['chat'],'from':msg['from'],'date':msg['date']})
		rec({'text':'/jbss3','chat':msg['chat'],'from':msg['from'],'date':msg['date']})
		#rec({'text':'/petr4','chat':{'id':msg['chat']['id']}})
		#rec({'text':'/ggbr4','chat':{'id':msg['chat']['id']}})
		#rec({'text':'/goau4','chat':{'id':msg['chat']['id']}})
		#rec({'text':'/usim5','chat':{'id':msg['chat']['id']}})
		#rec({'text':'/csna3','chat':{'id':msg['chat']['id']}})
		#rec({'text':'/jbss3','chat':{'id':msg['chat']['id']}})
		bot.sendMessage(idChat, "denovo? /all" )

	#if (mensagemTxt.index('sushi') == 0):
	if ( "sushi" in mensagemTxt):
		chat = msg['chat']
		idChat = chat['id']
		bot.sendMessage(idChat, "### Sushi também é muito bom se beijado antes de comer #### ")

	if ( mensagemTxt == '/mining'):
		bot.sendMessage(idChat, "### Start mining, wait ... ")
		shellcmd = ('/root/workspace/bolsa-systems/blueMoney/dataMining/mining.sh')
		global_resposta = subprocess.check_output(shellcmd, stderr=subprocess.STDOUT)
		print(global_resposta)
		bot.sendMessage(idChat, "Finished with success!\nhttp://bluemoney.antidrone.com.br/mesa.html para acessar realtime. Para consultar a resposta digite /res")

	if ( mensagemTxt == '/iron'):
		with open("/root/workspace/bolsa-systems/blueMoney/csv/all/iron-fe62.csv", "r") as f:
			read_data = f.read()
			f.closed
		csv_reader = csv.reader(read_data)
		csv_data = list(csv_reader)
		#print (csv_data)
		bot.sendMessage(idChat, msg['text'] + " -> $ " + csv_data[6][0])
	
	if ( mensagemTxt == '/brent'):
		with open("/root/workspace/bolsa-systems/blueMoney/csv/all/iron-fe62.csv", "r") as f:
			read_data = f.read()
			f.closed
		csv_reader = csv.reader(read_data)
		csv_data = list(csv_reader)
		#print (csv_data)
		bot.sendMessage(idChat, msg['text'] + " -> $ " + csv_data[6][0])


	if ( mensagemTxt == '/res'):
		chat = msg['chat']
		idChat = chat['id']
		with open("/tmp/out", "r") as f:
			read_data = f.read()
			f.closed
		bot.sendMessage(idChat, read_data)

	if (mensagemTxt == 'help' or mensagemTxt == '/help' or mensagemTxt =='Help' or mensagemTxt == '/Help' or  mensagemTxt == 'HELP' or mensagemTxt == '/HELP' or mensagemTxt == 'H' or mensagemTxt == 'h' ):
		chat = msg['chat']
		idChat = chat['id']
		bot.sendMessage(idChat, "### Help  #### ")
		bot.sendMessage(idChat, " Oi eu sou o Money Busters Bot! Estou \
aqui para ajuda-lo, use algum comando para executar uma ação. \n\n/all - Listar\
todas as ações \n/vale5 - Listar açoes da Vale\n/ticker_da_ação - exemplo\
/csna3, /petr4, /ggbr4, /jbss3\n/iron\n/brent\n/commodities\n\nUma dica cuide \
de sua alimentação")




#colocar o bot para ficar lendo
bot.message_loop(rec)
while True:
	#sleep 4
	pass
