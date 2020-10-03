EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Hackathon:TI_MSP430 U2
U 1 1 5F7AD382
P 5650 4100
F 0 "U2" H 5650 3627 50  0000 C CNN
F 1 "TI_MSP430" H 5650 3536 50  0000 C CNN
F 2 "" H 5500 4250 50  0001 C CNN
F 3 "" H 5500 4250 50  0001 C CNN
	1    5650 4100
	1    0    0    -1  
$EndComp
$Comp
L Motor:Stepper_Motor_bipolar M1
U 1 1 5F7ADB00
P 8000 4150
F 0 "M1" H 8188 4274 50  0000 L CNN
F 1 "Stepper_Motor_bipolar" H 8188 4183 50  0000 L CNN
F 2 "" H 8010 4140 50  0001 C CNN
F 3 "http://www.infineon.com/dgdl/Application-Note-TLE8110EE_driving_UniPolarStepperMotor_V1.1.pdf?fileId=db3a30431be39b97011be5d0aa0a00b0" H 8010 4140 50  0001 C CNN
	1    8000 4150
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J1
U 1 1 5F7B0E32
P 5800 2300
F 0 "J1" H 5857 2767 50  0000 C CNN
F 1 "USB_B_Micro" H 5857 2676 50  0000 C CNN
F 2 "" H 5950 2250 50  0001 C CNN
F 3 "~" H 5950 2250 50  0001 C CNN
	1    5800 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5F7B460B
P 5800 2700
F 0 "#PWR03" H 5800 2450 50  0001 C CNN
F 1 "GND" H 5805 2527 50  0000 C CNN
F 2 "" H 5800 2700 50  0001 C CNN
F 3 "" H 5800 2700 50  0001 C CNN
	1    5800 2700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 5F7B4B92
P 6100 2300
F 0 "#PWR04" H 6100 2150 50  0001 C CNN
F 1 "+5V" V 6115 2428 50  0000 L CNN
F 2 "" H 6100 2300 50  0001 C CNN
F 3 "" H 6100 2300 50  0001 C CNN
	1    6100 2300
	0    1    1    0   
$EndComp
Text Label 6100 2100 0    50   ~ 0
Vusb
Text Label 3000 2350 1    50   ~ 0
Vusb
Text Label 5650 3600 0    50   ~ 0
Vusb
$Comp
L Transistor_BJT:2N3904 Q1
U 1 1 5F7B8C62
P 4250 3600
F 0 "Q1" H 4440 3646 50  0000 L CNN
F 1 "2N3904" H 4440 3555 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4450 3525 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 4250 3600 50  0001 L CNN
	1    4250 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 3600 4050 3600
Wire Wire Line
	4350 3800 4350 4100
Wire Wire Line
	4350 4100 5050 4100
Wire Wire Line
	4350 4100 4350 4300
Connection ~ 4350 4100
$Comp
L power:GND #PWR02
U 1 1 5F7BB2C7
P 4350 4750
F 0 "#PWR02" H 4350 4500 50  0001 C CNN
F 1 "GND" H 4355 4577 50  0000 C CNN
F 2 "" H 4350 4750 50  0001 C CNN
F 3 "" H 4350 4750 50  0001 C CNN
	1    4350 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5F7BB6AD
P 2400 2700
F 0 "#PWR01" H 2400 2450 50  0001 C CNN
F 1 "GND" V 2405 2572 50  0000 R CNN
F 2 "" H 2400 2700 50  0001 C CNN
F 3 "" H 2400 2700 50  0001 C CNN
	1    2400 2700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5F7BBAA5
P 7050 4650
F 0 "#PWR05" H 7050 4400 50  0001 C CNN
F 1 "GND" H 7055 4477 50  0000 C CNN
F 2 "" H 7050 4650 50  0001 C CNN
F 3 "" H 7050 4650 50  0001 C CNN
	1    7050 4650
	1    0    0    -1  
$EndComp
Text Label 2400 2550 2    50   ~ 0
Vcc
Text Label 7450 3650 0    50   ~ 0
Vcc
Wire Wire Line
	4350 3400 4350 2500
Text Label 4350 2500 1    50   ~ 0
Vcc
$Comp
L Device:R R1
U 1 1 5F7BD4CF
P 4350 4450
F 0 "R1" H 4420 4496 50  0000 L CNN
F 1 "330" H 4420 4405 50  0000 L CNN
F 2 "" V 4280 4450 50  0001 C CNN
F 3 "~" H 4350 4450 50  0001 C CNN
	1    4350 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 4600 4350 4750
Wire Wire Line
	6250 3800 6250 3850
Wire Wire Line
	6250 3850 6650 3850
Wire Wire Line
	6250 4000 6250 3950
Wire Wire Line
	6250 3950 6650 3950
Wire Wire Line
	6250 4200 6250 4050
Wire Wire Line
	6250 4050 6650 4050
Wire Wire Line
	6250 4400 6300 4400
Wire Wire Line
	6300 4400 6300 4150
Wire Wire Line
	6300 4150 6650 4150
Wire Wire Line
	7450 3850 7500 3850
Wire Wire Line
	7500 3850 7500 3700
Wire Wire Line
	7500 3700 8100 3700
Wire Wire Line
	8100 3700 8100 3850
Wire Wire Line
	7450 3950 7800 3950
Wire Wire Line
	7800 3950 7800 3850
Wire Wire Line
	7800 3850 7900 3850
Wire Wire Line
	7450 4050 7700 4050
Wire Wire Line
	7450 4150 7600 4150
Wire Wire Line
	7600 4150 7600 4250
Wire Wire Line
	7600 4250 7700 4250
$Comp
L Hackathon:Particle_Photon U1
U 1 1 5F7ACE6F
P 3000 3400
F 0 "U1" H 3000 2427 50  0000 C CNN
F 1 "Particle_Photon" H 3000 2336 50  0000 C CNN
F 2 "" H 3000 3400 50  0001 C CNN
F 3 "" H 3000 3400 50  0001 C CNN
	1    3000 3400
	1    0    0    -1  
$EndComp
NoConn ~ 2400 2850
NoConn ~ 2400 3000
NoConn ~ 2400 3150
NoConn ~ 2400 3300
NoConn ~ 2400 3450
NoConn ~ 2400 3600
NoConn ~ 2400 3750
NoConn ~ 2400 3900
NoConn ~ 2400 4050
NoConn ~ 2400 4200
NoConn ~ 3600 2550
NoConn ~ 3600 2700
NoConn ~ 3600 2850
NoConn ~ 3600 3000
NoConn ~ 3600 3150
NoConn ~ 3600 3300
NoConn ~ 3600 3450
NoConn ~ 3600 3750
NoConn ~ 3600 3900
NoConn ~ 3600 4050
NoConn ~ 3600 4200
NoConn ~ 6100 2500
NoConn ~ 6100 2400
NoConn ~ 5650 2700
$Comp
L Transistor_Array:ULN2003A U3
U 1 1 5F7AE4E3
P 7050 4050
F 0 "U3" H 7050 4717 50  0000 C CNN
F 1 "ULN2003A" H 7050 4626 50  0000 C CNN
F 2 "" H 7100 3500 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2003a.pdf" H 7150 3850 50  0001 C CNN
	1    7050 4050
	1    0    0    -1  
$EndComp
NoConn ~ 6650 4250
NoConn ~ 6650 4350
NoConn ~ 6650 4450
NoConn ~ 7450 4450
NoConn ~ 7450 4350
NoConn ~ 7450 4250
$EndSCHEMATC
