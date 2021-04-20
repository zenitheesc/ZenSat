

<h1 align="center" style="color:white; background-color:black">ZenSat</h1>
<h4 align="center">This is an Open Hardware and Software CubeSat developed by Zenith EESC-USP for the CubeDesign 2018.</h4>

<p align="center">
	<a href="http://zenith.eesc.usp.br/">
    <img src="https://img.shields.io/badge/Zenith-Embarcados-black?style=for-the-badge"/>
    </a>
    <a href="https://eesc.usp.br/">
    <img src="https://img.shields.io/badge/Linked%20to-EESC--USP-black?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/USPSat-AE1/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/zenitheesc/USPSat-AE1?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/USPSat-AE1/issues">
    <img src="https://img.shields.io/github/issues/zenitheesc/USPSat-AE1?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/USPSat-AE1/commits/main">
    <img src="https://img.shields.io/github/commit-activity/m/zenitheesc/USPSat-AE1?style=for-the-badge">
    </a>
    <a href="https://github.com/zenitheesc/USPSat-AE1/graphs/contributors">
    <img src="https://img.shields.io/github/contributors/zenitheesc/USPSat-AE1?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/USPSat-AE1/commits/main">
    <img src="https://img.shields.io/github/last-commit/zenitheesc/USPSat-AE1?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/USPSat-AE1/issues">
    <img src="https://img.shields.io/github/issues-raw/zenitheesc/USPSat-AE1?style=for-the-badge" />
    </a>
    <a href="https://github.com/zenitheesc/USPSat-AE1/pulls">
    <img src = "https://img.shields.io/github/issues-pr-raw/zenitheesc/USPSat-AE1?style=for-the-badge">
    </a>
</p>

Aiming to participate in the first CubeDesign in 2018, Zenith designed its first nanosatellite prototype, which was named ”ZenSat”. This project was a 2U CubeSat for imaging missions in the competition. It is worth mentioning that the focus of the project was not to validate a nanosatellite for flight but to enable a first contact between the group members and the development of a nanosatellite.

<p align = "center">
<img src="https://github.com/zenitheesc/ZenSat_1.0/blob/master/IMAGES/block-diagram.jpg?raw=true"/>
</p>

<a href="https://github.com/zenitheesc/ZenSat_1.0/tree/master/ADC%20-%20Attitude%20Determination%20and%20Control"><h2> ADC - Attitude Determination and Control </h2></a>
The entire stabilization and pointing system must be done necessary to fulfill the competition missions. For this, the reading is done necessary sensors, activating a reaction wheel, which, by means of the Law of Conservation of Angular Momentum, manages to act in the attitude of the satellite.

<p align = "center">
<img src="https://github.com/zenitheesc/ZenSat_1.0/blob/master/IMAGES/adc.PNG?raw=true"/>
</p>


<a href="https://github.com/zenitheesc/ZenSat_1.0/tree/master/COM%20-%20Command%20and%20Telemetry"><h2>COM - Command and Telemetry</h2></a>
It is responsible by the bidirectional telemetry in cubesat. This System has two LoRa radios, which communicate with the CTRL Subsystem

<p align = "center">
<img src="https://github.com/zenitheesc/ZenSat_1.0/blob/master/IMAGES/antena.PNG?raw=true"/>
</p>

<a href="https://github.com/zenitheesc/ZenSat_1.0/tree/master/COM%20-%20Command%20and%20Telemetry"><h2>CTRL - Control</h2></a>
The Control System is the main component of the project. This system is responsible for data analysis, decision making and controlling the others systems
<p align = "center">
<img src="https://github.com/zenitheesc/ZenSat_1.0/blob/master/IMAGES/diagrama%20Geral.PNG?raw=true"/>
</p>


<a href="https://github.com/zenitheesc/ZenSat_1.0/tree/master/PS%20-%20Power%20Supply"><h2>PS - Power Supply</h2></a>
Ensures the monitoring and control of EPS panel parameters,
that is, it performs the measurement of voltage and current levels at various points on the CubeSat;
monitors the temperature of the batteries and acts to keep it always positive, in addition to
carry out communication with other subsystems.
Also it performs conversions of battery voltage levels to the levels requested within the
hardware, making the necessary distribution, as well as controlling the loading of batteries through solar panels.

<p align = "center">
<img src="https://github.com/zenitheesc/ZenSat_1.0/blob/master/IMAGES/eps.PNG?raw=true"/>
</p>


<a href="https://github.com/zenitheesc/ZenSat_1.0/tree/master/STT%20-%20Structure"><h2> STT - Structure </h2></a>
Finally, we have the subsystem responsible for the physical integration of all
the subsystems described earlier. All manufacturing issues involving
the physical structure of ZenSat is the responsibility of the structures subsystem. The
determination of the materials used, the choice of manufacturing processes and display of all components, aiming at a satisfactory performance in the
vibration, are the main focuses of this subsystem

<p align = "center">
<img src="https://github.com/zenitheesc/ZenSat_1.0/blob/master/IMAGES/simula%C3%A7%C3%A3o.PNG?raw=true"/>
</p>


## Official Documentation

Check out the official documentation [here](https://github.com/zenitheesc/ZenSat_1.0/blob/master/ZenSat%20v.1.0.pdf).

<p align = "center">
<img src="https://github.com/zenitheesc/ZenSat_1.0/blob/master/IMAGES/render.png?raw=true" alt="drawing" width="800" align="center"/>
</p>


<p align="center">
    <a href="http://zenith.eesc.usp.br">
    <img src="https://img.shields.io/badge/Check%20out-Zenith's Oficial Website-black?style=for-the-badge" />
    </a> 
    <a href="https://www.facebook.com/zenitheesc">
    <img src="https://img.shields.io/badge/Like%20us%20on-facebook-blue?style=for-the-badge"/>
    </a> 
    <a href="https://www.instagram.com/zenith_eesc/">
    <img src="https://img.shields.io/badge/Follow%20us%20on-Instagram-red?style=for-the-badge"/>
    </a>

</p>
<p align = "center">
<a href="zenith.eesc@gmail.com">zenith.eesc@gmail.com</a>
</p>
