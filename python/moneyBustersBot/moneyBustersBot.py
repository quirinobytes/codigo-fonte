#!/usr/bin/env python3.4

import telepot
import subprocess

#token do bot
bot = telepot.Bot("389133150:AAFqZmu_2WMCHRBpUlv2DyFeCW2Hn6CEwQc")

def rec(msg):
	mensagemTxt = msg['text']
	print(mensagemTxt)
	if (mensagemTxt == '/petr4' or mensagemTxt == '/vale5' or mensagemTxt == '/usim5' or mensagemTxt == '/csna3'  or mensagemTxt == '/goau4'  or mensagemTxt == '/ggbr4'  or mensagemTxt == '/jbss3') :
		chat = msg['chat']
		idChat = chat['id']
		bot.sendMessage(idChat, "### INFO "+msg['text'])
		with open("/MoneyBustersBot"+msg['text']+'.csv', "r") as f:
			read_data = f.read()
			f.closed
		bot.sendMessage(idChat, read_data)
	if (mensagemTxt == '/all') :
		rec({'text':'/vale5','chat':{'id':msg['chat']['id']}})
		rec({'text':'/petr4','chat':{'id':msg['chat']['id']}})
		rec({'text':'/usim5','chat':{'id':msg['chat']['id']}})
		rec({'text':'/csna3','chat':{'id':msg['chat']['id']}})
		rec({'text':'/jbss3','chat':{'id':msg['chat']['id']}})
	if (mensagemTxt == 'help' or mensagemTxt == '/help' or mensagemTxt =='Help' or mensagemTxt == '/Help' or  mensagemTxt == 'HELP' or mensagemTxt == '/HELP' or mensagemTxt == 'h' ):
		chat = msg['chat']
		idChat = chat['id']
		bot.sendMessage(idChat, "### Help  #### ")
		bot.sendMessage(idChat, " Oi eu sou o Money Busters Bot! Estou aqui para ajuda-lo, use algum comando para executar uma ação. \n\n/all - Listar todas as ações \n/vale5 - Listar açoes da Vale\n/ticker_da_ação - exemplo /csna3, /petr4, /ggbr4, /jbss3.\nsushi - Uma dica de alimentação")
	#if (mensagemTxt.index('sushi') == 0):
	if ( "sushi" in mensagemTxt):
		chat = msg['chat']
		idChat = chat['id']
		bot.sendMessage(idChat, "### Sushi também é muito bom se beijado antes de comer #### ")
	if ( mensagemTxt == '/mining'):
		chat = msg['chat']
		idChat = chat['id']
		bot.sendMessage(idChat, "### Start mining, wait ... ")
		shellcmd = ('/root/workspace/bolsa-systems/blueMoney/dataMining/mining.sh 2>&1 > /tmp/out')
		res = subprocess.check_output(shellcmd, stderr=subprocess.STDOUT)
		print(res)
		bot.sendMessage(idChat, "### mining finished with sucess #### ")

#colocar o bot para ficar lendo
bot.message_loop(rec)
while True:
	#sleep 4
	pass
