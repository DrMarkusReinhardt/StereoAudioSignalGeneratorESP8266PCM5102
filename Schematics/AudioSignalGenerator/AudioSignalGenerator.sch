EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Dual Channel Audio Sine Signal Generator"
Date "2021-02-06"
Rev "0.1"
Comp "HoMeR"
Comment1 "Dr. Markus Reinhardt"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 601EBB44
P 2450 3650
F 0 "J1" H 2558 3831 50  0000 C CNN
F 1 "Conn_01x02_Male" H 2558 3740 50  0000 C CNN
F 2 "" H 2450 3650 50  0001 C CNN
F 3 "~" H 2450 3650 50  0001 C CNN
	1    2450 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 601EBF63
P 3800 3550
F 0 "#PWR01" H 3800 3400 50  0001 C CNN
F 1 "+5V" H 3815 3723 50  0000 C CNN
F 2 "" H 3800 3550 50  0001 C CNN
F 3 "" H 3800 3550 50  0001 C CNN
	1    3800 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 601EC43C
P 3800 3850
F 0 "#PWR02" H 3800 3600 50  0001 C CNN
F 1 "GND" H 3805 3677 50  0000 C CNN
F 2 "" H 3800 3850 50  0001 C CNN
F 3 "" H 3800 3850 50  0001 C CNN
	1    3800 3850
	1    0    0    -1  
$EndComp
$Comp
L nodemcu:NodeMCU_0.9 XA1
U 1 1 601ECC88
P 5050 3750
F 0 "XA1" H 5050 4675 50  0000 C CNN
F 1 "NodeMCU_0.9" H 5050 4584 50  0000 C CNN
F 2 "" H 5300 3750 50  0000 C CNN
F 3 "" H 5300 3750 50  0000 C CNN
	1    5050 3750
	1    0    0    -1  
$EndComp
Text Notes 750  1400 0    315  ~ 63
Dual Channel Audio Sine Signal Generator
$Comp
L OLED_1DOT3:OLED_1DOT3 U1
U 1 1 601F4A30
P 7800 3100
F 0 "U1" H 8278 3146 50  0000 L CNN
F 1 "OLED_1DOT3" H 8278 3055 50  0000 L CNN
F 2 "MODULE" H 7800 3100 50  0001 C CNN
F 3 "DOCUMENTATION" H 7800 3100 50  0001 C CNN
	1    7800 3100
	1    0    0    -1  
$EndComp
$Comp
L PCM5102_MODULE:PCM5102_MODULE U2
U 1 1 601F5253
P 7800 4300
F 0 "U2" H 7800 4915 50  0000 C CNN
F 1 "PCM5102_MODULE" H 7800 4824 50  0000 C CNN
F 2 "MODULE" H 7800 4300 50  0001 C CNN
F 3 "DOCUMENTATION" H 7800 4300 50  0001 C CNN
	1    7800 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 3650 3800 3550
Wire Wire Line
	3800 3750 3800 3850
Wire Wire Line
	3800 3750 4150 3750
Wire Wire Line
	4150 3750 4150 4350
Wire Wire Line
	4150 4350 4600 4350
Connection ~ 3800 3750
Wire Wire Line
	4600 4450 4300 4450
Wire Wire Line
	4300 4450 4300 3650
Wire Wire Line
	4300 3650 3800 3650
Connection ~ 3800 3650
Wire Wire Line
	5500 4350 7050 4350
Wire Wire Line
	7050 4450 5950 4450
Wire Wire Line
	5950 4450 5950 4700
Wire Wire Line
	5950 4700 4150 4700
Wire Wire Line
	4150 4700 4150 4350
Connection ~ 4150 4350
Wire Wire Line
	4300 4450 4300 4550
Connection ~ 4300 4450
Wire Wire Line
	4300 4550 6050 4550
Wire Wire Line
	6050 4550 6050 2950
Wire Wire Line
	6050 2950 7050 2950
Connection ~ 6050 4550
Wire Wire Line
	6050 4550 7050 4550
Wire Wire Line
	5950 4450 5950 3050
Wire Wire Line
	5950 3050 7050 3050
Connection ~ 5950 4450
Wire Wire Line
	5500 3250 7050 3250
Wire Wire Line
	5500 3150 7050 3150
Wire Wire Line
	5500 4050 7050 4050
Wire Wire Line
	5500 4150 7050 4150
Wire Wire Line
	5500 3450 6150 3450
Wire Wire Line
	6150 3450 6150 4250
Wire Wire Line
	6150 4250 7050 4250
Text Notes 700  2000 0    197  ~ 0
NodeMCU V0.9 Module with PCM5102 Module and 1.3" OLED Display
Text Notes 6450 3400 0    79   ~ 0
I2C Interface
Text Notes 6450 3950 0    79   ~ 0
I2S Interface
$Comp
L Switch:SW_SPST SW1
U 1 1 6021EC58
P 3250 3650
F 0 "SW1" H 3250 3885 50  0000 C CNN
F 1 "SW_SPST" H 3250 3794 50  0000 C CNN
F 2 "" H 3250 3650 50  0001 C CNN
F 3 "~" H 3250 3650 50  0001 C CNN
	1    3250 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 3750 3800 3750
Wire Wire Line
	2650 3650 3050 3650
Wire Wire Line
	3450 3650 3800 3650
$Comp
L Switch:SW_SPST SW2
U 1 1 60221C7B
P 3300 4250
F 0 "SW2" H 3300 4485 50  0000 C CNN
F 1 "SW_SPST" H 3300 4394 50  0000 C CNN
F 2 "" H 3300 4250 50  0001 C CNN
F 3 "~" H 3300 4250 50  0001 C CNN
	1    3300 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 602220C7
P 2950 4300
F 0 "#PWR03" H 2950 4050 50  0001 C CNN
F 1 "GND" H 2955 4127 50  0000 C CNN
F 2 "" H 2950 4300 50  0001 C CNN
F 3 "" H 2950 4300 50  0001 C CNN
	1    2950 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 4250 2950 4250
Wire Wire Line
	2950 4250 2950 4300
Wire Wire Line
	3500 4250 4600 4250
$EndSCHEMATC