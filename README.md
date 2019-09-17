# Digital Timer
 
Include your responses to the bold questions below. Include snippets of code that explain what you did. Deliverables are due next Tuesday. Post your lab reports as README.md pages on your GitHub, and post a link to that on your main class hub page.

## Part A. Solder your LCD panel

![LCD picture](https://github.com/ronykrell/IDD-Fa19-Lab2/blob/master/soldered.JPG "LCD")


## Part B. Writing to the LCD
 
**a. What voltage level do you need to power your display?**

5V (w/potentiometer)

**b. What voltage level do you need to power the display backlight?**

3.3V
   
**c. What was one mistake you made when wiring up the display? How did you fix it?**

Not wiring together the ground + power between the two halves of the right siderail. Fixed by connecting top & bottom ground + power siderail lines.


**d. What line of code do you need to change to make it flash your name instead of "Hello World"?**

  lcd.print("hello, world!"); =>   lcd.print("Rony Krell");
 
**e. Include a copy of your Lowly Multimeter code in your lab write-up.**

[Code for Lowly Multimeter](https://github.com/ronykrell/IDD-Fa19-Lab2/blob/master/LowlyVoltmeter.ino)


## Part C. Using a time-based digital sensor


[Rotary Encoder Video](https://youtu.be/SlvDI3g2yI4)


## Part D. Make your Arduino sing!

**a. How would you change the code to make the song play twice as fast?**

Divide the duration by 2:

int noteDuration = 1000 / noteDurationLose[thisNote];
  
   =>

int noteDuration = 1000 / noteDurationLose[thisNote] / 2;
 
**b. What song is playing?**

The start wars theme song


## Part E. Make your own timer

**a. Make a short video showing how your timer works, and what happens when time is up!**

The timer is part of a game where the player stops the lights by pressing a button. To win, stop the light when the middle LED is lit. 
Set the timer to start, and get the middle LED before time runs out!


[Demo](https://youtu.be/2L-5r6BSOIg)

[LED Closeup](https://youtu.be/kWZPegpry50)

**b. Post a link to the completed lab report your class hub GitHub repo.**
