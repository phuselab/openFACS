import random
from typing import Tuple, List

import PySimpleGUI as sg

from omegaconf import DictConfig

import openFACS


PROTOTYPICAL_EXPRESSIONS_NORMALIZED: dict = {
    "anger": [0.0, 0.0, 1.0, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.6, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    "contempt": [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0],
    "disgust": [0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.4, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    "fear": [0.6, 0.0, 0.6, 0.0, 0.0, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.6, 0.6, 0.6, 0.6, 0.0, 0.0],
    "happiness": [0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0],
    "neutral": [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    "sadness": [1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    "shock": [0.6, 0.6, 0.4, 0.8, 0.0, 0.4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.0, 0.0, 0.4, 0.0, 0.0],
    "surprise": [0.6, 0.6, 0.0, 0.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.6, 0.0, 0.0]
}

NUMBER_OF_ACTION_UNITS: int = 18


class OpenFacsControllerGUI(object):
    def __init__(self, open_facs_interface: openFACS.OpenFacsInterface, slider_maxval: float) -> None:
        self._open_facs_interface: openFACS.OpenFacsInterface = open_facs_interface
        self._slider_maxval: float = slider_maxval

        self._window = sg.Window(
            title="OpenFACS Controller",
            layout=self._get_layout(slider_maxval),
            resizable=True
        )

    @staticmethod
    def _get_layout(slider_maxval: float) -> List:
        layout = [
            [sg.Combo(
                list(PROTOTYPICAL_EXPRESSIONS_NORMALIZED.keys()),
                size=(40, 4),
                enable_events=True,
                key="dropdown")
            ],

            [sg.Text("Speed", size=(10, 1)),
             sg.InputText(default_text="1.0", key="speed_input", enable_events=True, size=(5, 1))
             ],

            [sg.Text("AU 1: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU1"
             ),
             sg.Text("inner brow raiser", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 2: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU2"
             ),
             sg.Text("outer brow raiser", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 4: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU4"
             ), sg.Text("brow lowerer", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 5: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU5"
             ), sg.Text("upper lid raiser", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 6: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU6"
             ), sg.Text("cheek raiser", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 7: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU7"
             ), sg.Text("lid tightener", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 9: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU9"
             ), sg.Text("nose wrinklener", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 10: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU10"
             ), sg.Text("upper lip raiser", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 12: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU12"
             ), sg.Text("lip corner puller", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 14: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU14"
             ), sg.Text("dimpler", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 15: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU15"
             ), sg.Text("lip corner depressor", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 17: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU17"
             ), sg.Text("chin raiser", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 20: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU20"
             ), sg.Text("lip stretcher", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 23: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU23"
             ), sg.Text("lip tightener", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 25: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU25"
             ), sg.Text("lips part", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 26: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU26"
             ), sg.Text("jaw drop", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 28: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU28"
             ), sg.Text("lip suck", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text("AU 45: ", size=(6, 1), font=("Helvetica", 12), justification="c"),
             sg.Slider(
                 range=(0, slider_maxval),
                 default_value=0,
                 resolution=0.1,
                 size=(20, 15),
                 orientation="horizontal",
                 font=("Helvetica", 12),
                 enable_events=True,
                 key="SAU45"
             ), sg.Text("blink", size=(10, 2), font=("Helvetica", 9), justification="c")],

            [sg.Text(size=(50, 1), key="error_box")],
            [sg.Text(size=(50, 1), key="output")],

            [sg.Checkbox("Enable interactive mode:", default=False, key="interactive")],
            [sg.Button("Send"), sg.Button("Reset"), sg.Button("Random"), sg.Button("Quit")]
        ]

        return layout

    @staticmethod
    def read_slider_values(values) -> List[float]:
        au1 = values["SAU1"]
        au2 = values["SAU2"]
        au4 = values["SAU4"]
        au5 = values["SAU5"]
        au6 = values["SAU6"]
        au7 = values["SAU7"]
        au9 = values["SAU9"]
        au10 = values["SAU10"]
        au12 = values["SAU12"]
        au14 = values["SAU14"]
        au15 = values["SAU15"]
        au17 = values["SAU17"]
        au20 = values["SAU20"]
        au23 = values["SAU23"]
        au25 = values["SAU25"]
        au26 = values["SAU26"]
        au28 = values["SAU28"]
        au45 = values["SAU45"]

        return [au1, au2, au4, au5, au6, au7, au9, au10, au12, au14, au15, au17, au20, au23, au25, au26, au28, au45]

    def read_speed(self, values) -> float:
        speed_in = values["speed_input"]

        try:
            speed = float(speed_in)
        except ValueError:
            self._window["error_box"].update(f"Inserted speed value is not valid! Using 1.0")
            print(f"WARNING: Inserted speed value is not valid! Using 1.0")

            speed_in = "1.0"
            self._window["speed_input"].update(speed_in)
            speed = float(speed_in)

        return speed

    def set_slider_values(self, au_list: List[float]) -> None:
        self._window["SAU1"].update(au_list[0])
        self._window["SAU2"].update(au_list[1])
        self._window["SAU4"].update(au_list[2])
        self._window["SAU5"].update(au_list[3])
        self._window["SAU6"].update(au_list[4])
        self._window["SAU7"].update(au_list[5])
        self._window["SAU9"].update(au_list[6])
        self._window["SAU10"].update(au_list[7])
        self._window["SAU12"].update(au_list[8])
        self._window["SAU14"].update(au_list[9])
        self._window["SAU15"].update(au_list[10])
        self._window["SAU17"].update(au_list[11])
        self._window["SAU20"].update(au_list[12])
        self._window["SAU23"].update(au_list[13])
        self._window["SAU25"].update(au_list[14])
        self._window["SAU26"].update(au_list[15])
        self._window["SAU28"].update(au_list[16])
        self._window["SAU45"].update(au_list[17])

    def set_speed(self, speed_value: float) -> None:
        self._window["speed_input"].update(str(speed_value))

    def reset(self) -> Tuple[List[float], float]:
        aus = [0.0] * NUMBER_OF_ACTION_UNITS
        speed = 1.0

        self.set_speed(speed_value=speed)
        self.set_slider_values(au_list=aus)

        return aus, speed

    def generate_random_aus(self) -> List[float]:
        """
        Generates from a lognormal(0, 1).
        """
        random_au_values = [
            random.lognormvariate(0, 1) for _ in range(NUMBER_OF_ACTION_UNITS)
        ]
        # Adjust to the maximum value of the slider.
        random_au_values = [
            min(rv, self._slider_maxval) for rv in random_au_values
        ]

        self.set_slider_values(au_list=random_au_values)

        return random_au_values

    def run(self) -> None:
        # Display and interact with the Window using an Event Loop
        while True:
            event, values = self._window.read()

            # Empty all text previously written
            self._window["output"].update("")
            self._window["error_box"].update("")

            # See if user wants to quit or window was closed
            if event == sg.WINDOW_CLOSED or event == "Quit":
                aus, speed = self.reset()
                self._window["output"].update("Successfully reset all values")
                self._open_facs_interface.send_aus(au_list=aus, speed=speed)

                break

            elif event == "Send":
                aus = self.read_slider_values(values)
                speed = self.read_speed(values)

                self._open_facs_interface.send_aus(au_list=aus, speed=speed)
                self._window["output"].update("Message sent successfully!")

            elif event == "Reset":
                aus, speed = self.reset()
                self._window["output"].update("Successfully reset all values")
                self._open_facs_interface.send_aus(au_list=aus, speed=speed)

            elif event == "Random":
                aus = self.generate_random_aus()
                speed = self.read_speed(values)

                self._open_facs_interface.send_aus(au_list=aus, speed=speed)
                self._window["output"].update("Successfully generated random values")

            # If any of the sliders are moved and the interactive mode is enabled
            elif event in [
                "SAU1", "SAU2", "SAU4", "SAU5", "SAU6", "SAU7", "SAU9",
                "SAU10", "SAU12", "SAU14", "SAU15", "SAU17",
                "SAU20", "SAU23", "SAU25", "SAU26", "SAU28",
                "SAU45"
            ] and values["interactive"] is True:
                aus = self.read_slider_values(values)
                speed = self.read_speed(values)

                self._open_facs_interface.send_aus(au_list=aus, speed=speed)

            elif event == "dropdown":
                dropdown_value: str = values["dropdown"]
                normalized_aus: List[float] = PROTOTYPICAL_EXPRESSIONS_NORMALIZED[dropdown_value]
                aus: List[float] = [
                    au * self._slider_maxval for au in normalized_aus
                ]
                speed: float = self.read_speed(values)

                self.set_slider_values(au_list=aus)
                self._open_facs_interface.send_aus(au_list=aus, speed=speed)
                self._window["output"].update("Message sent successfully!")

        # Finish up by removing from the screen
        self._window.close()


def main() -> None:
    UDP_IP_ADDRESS = "127.0.0.1"
    UDP_PORT_NO = 5000
    SLIDER_MAXVAL = 5

    open_facs_interface = openFACS.OpenFacsInterface(
        udp_ip_address=UDP_IP_ADDRESS,
        udp_port=UDP_PORT_NO
    )

    open_facs_controller = OpenFacsControllerGUI(
        open_facs_interface=open_facs_interface,
        slider_maxval=SLIDER_MAXVAL
    )
    open_facs_controller.run()


if __name__ == "__main__":
    main()
