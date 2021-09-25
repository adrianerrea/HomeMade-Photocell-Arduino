# HomeMade-Photocell-Arduino

## Description

**Warning!** This is not a ML project or something similar. I created this little project because I also like the hardware stuff and I thought it could have some utility anyway 😃

The idea of this arduino project is to simulate a photocell used in several locations like sports trials, presence detection and so on. My first idea was to have a prototipe as little as possible but working as I wanted. Then I would make it better from there.

I post the final schema for the connections I created with Fritzing Application (https://fritzing.org/) in the repository as well.


## Operation

The goal of the project is to be able to measure the time from two different moments triggered but the same action: something/someone crossing in front of the ultrasonic sensor. This way we can measure the time from two different intervals and show the time elapsed through the LCD display. As commented before, this project tries to replicate the behaviour of photocells but much more cheaper (and little less accuracy and reliable 😝). When you connect the Controller Board to the power (it can be a computer, a power bank, etc.) a beautiful melody arises from the kit (let's call it that way from now) letting you know that it is ready to rock!

As soon as somebody/something crosses ahead the kit, the time starts to count and the passive buzzer emmits a sound indicating the starting. Then, the LCD display shows the elapsed time as it happens and when somebody/something crosses ahead the kit again, a new sound is emmited by the buzzer indicating the end of the trial and the final time is shown on the LCD display. After some seconds (enough to check what is your total elapsed time), the kit is reset and the green led turns on indicating that it is ready for another trial.

## Modules used:

I bought an Arduino Starter Kit UNO R3 since I was pretty sure it would be more than enough for everything planned. However, I realised afterwards that visualizing the time instantly would make the project more usable. So, I had to buy an I2C adapter for the LCD display because at that time of the project, I was run out of available wires to make the connections 😅. So this adapter simplifies the connections in a great manner. Anyway, this is what I used:

+ UNO R3 Controller Board
+ Breadboard Expansion Board
+ Ultrasonic Sensor HC-SR04
+ LCD1602 Module
+ SODIAL(R) IIC I2C TWI SP (I2C Module for LCD Display)
+ Passive Buzzer
+ Green LED
+ Red LED
+ Resistor x2
+ Wires

## Code

The code is in the repository. Check it out to see all the details.

## Demo

In the repository you can watch a little demo of the kit working

## Conclusions and Improvements

I am quite happy with the result taking into account this is my first type of projects by my own (I made more of them at the university) so I can only improve from here! 😂
Some things I think is important to mention as they are clearly some points to improve:

+ The Ultrasonic Sensor is not so accurate and its precision is arguable. It only works in a closing range distance from 2 to 450 cm. I noticed some losts in the signals and I would not use it in a real life project. Besides this, it is affected by the sunlight and the reflectivity as I had never thought before. When taking the kit outdoors, the behaviour is unexpected and the first time I tried it outside I did not get what was going on. Later, I realised the ground was emmiting noisy signals to the Ultrasonic sensor and that was causing the chaos. I solved it by elevating the kit from the ground by 1 meter or so to avoid those rays reflected from the ground.
+  I packed all the kit into a box to protect it and even with that, the wires often get disconnected from the Board. I truly believe that Arduino stuff is only for indoors purposes 😔.

