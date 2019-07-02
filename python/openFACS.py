import json
import os
import socket

def sendAUS(aus, speed):
	j = {
		'AU1': aus[0],
		'AU2': aus[1],
		'AU4': aus[2],
		'AU5': aus[3],
		'AU6': aus[4],
		'AU7': aus[5],
		'AU9': aus[6],
		'AU10': aus[7],
		'AU12': aus[8],
		'AU14': aus[9],
		'AU15': aus[10],
		'AU17': aus[11],
		'AU20': aus[12],
		'AU23': aus[13],
		'AU25': aus[14],
		'AU26': aus[15],
		'AU28': aus[16],
		'AU45': aus[17],
		'Speed': speed,
	}

	UDP_IP_ADDRESS = "127.0.0.1"
	UDP_PORT_NO = 5000
	Message = str.encode(json.dumps(j))

	clientSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	clientSock.sendto(Message, (UDP_IP_ADDRESS, UDP_PORT_NO))
	return;