# ECEN5803-Project-1-Flowmeter   
This Project has a 4 part objective: 
1. Module-1 : Write a function to compute the square root of a number in Assembly.
2. Module-2 : Integrate FRDM-KL25Z's onboard I2C accelerometer and touch sensor.   
3. Module-3 : Setup UART Console for for the KL25Z.
4. Module-4 : Capture frequency and temperature from the ADC and compute the flow rate (gallons/min)

## Block Diagram of the System
<br>Block Diagram of Vortex Flowmeter:</br>  
   ![block_diagram](Block%20Diagram/Flowmeter%20Solution%20Block%20Diagram.jpg)

## Simulink result for the given requirements
<br>Simulink Result:</br>
   ![block_diagram](Module-4/Simulink/simulink%20result.jpg)

## Lab Setup
<br>Picture 1</br>
   ![block_diagram](Lab%20Setup/lab_1.jpg)
 
 
<br>Picture 2</br>
   ![block_diagram](Lab%20Setup/lab_2.jpg) 
   
## Test Results
<br>Module 1</br>
	![block_diagram](Module-1/test%20results/Input_1.jpg)
	![block_diagram](Module-1/test%20results/output_1.png)
	
<br>Module 2</br>
<br>Accelerometer</br>
	[![Watch the video](https://i.imgur.com/vKb2F1B.png)](https://github.com/sankalp123321/ECEN5803-Project-1-Flowmeter/blob/main/Module-2/test%20results/Accelerometer%20Working.mp4)
	
<br>Touch Sensor</br>
	[![Watch the video](https://i.imgur.com/vKb2F1B.png)](https://github.com/sankalp123321/ECEN5803-Project-1-Flowmeter/blob/main/Module-2/test%20results/Touch%20Sensor%20working.mp4)
	
<br>Module 3</br>
	![block_diagram](Module-3/test%20results/uart%20debug%20monitor.jpg)
	
<br>Module 4</br>
	![block_diagram](Module-4/test%20results/uart%20monitor.jpg)

Also a Dhrystone benchmarking has to be performed on this microcontroller to calculate the speed of the microcontroller.    

## Authors  
1. Sankalp Agrawal - saag2511@colorado.edu   
2. Ayush Gupta - aygu7370@colorado.edu
