import json
import socket
from typing import List


class OpenFacsInterface(object):
    def __init__(self, udp_ip_address: str, udp_port: int) -> None:
        self._udp_address: str = udp_ip_address
        self._udp_port: int = udp_port

    def send_aus(self, au_list: List[float], speed: float) -> None:
        param_dict = {
            "AU1": au_list[0],
            "AU2": au_list[1],
            "AU4": au_list[2],
            "AU5": au_list[3],
            "AU6": au_list[4],
            "AU7": au_list[5],
            "AU9": au_list[6],
            "AU10": au_list[7],
            "AU12": au_list[8],
            "AU14": au_list[9],
            "AU15": au_list[10],
            "AU17": au_list[11],
            "AU20": au_list[12],
            "AU23": au_list[13],
            "AU25": au_list[14],
            "AU26": au_list[15],
            "AU28": au_list[16],
            "AU45": au_list[17],
            "Speed": speed,
        }

        message: bytes = str.encode(json.dumps(param_dict))

        client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        client_socket.sendto(message, (self._udp_address, self._udp_port))

    @property
    def udp_address(self) -> str:
        return self._udp_address

    @property
    def udp_port(self) -> int:
        return self._udp_port


def sendAUS(aus: List[float], speed: float) -> None:
    UDP_IP_ADDRESS = "127.0.0.1"
    UDP_PORT_NO = 5000

    open_facs_interface = OpenFacsInterface(
        udp_ip_address=UDP_IP_ADDRESS,
        udp_port=UDP_PORT_NO
    )

    open_facs_interface.send_aus(
        au_list=aus,
        speed=speed
    )
