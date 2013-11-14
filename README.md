Lab5
====

Updated Lab 5 Game

The PreLab was accomplished in the lab notebook 05 November 2013. The grade was given for the Pre-Lab in the Lab Notebook.
Code was created using Code Composer on the Desktop in the ECE 382 LAB.
I ran into issues using Github on the desktop computer. Code Composer does not work on my school laptop
and neither does gitbash.

Lab 5 Pre-Lab
=============

Objective: In this lab, you’ll use your knowledge of interrupts and the Timer A subsystem to create a simple
game. To be successful you’ll have to use button and LCD.h drive either your own or open source, GITHUB


The Idea:
The Player of this game will be represented by an (*) asterix. By using push buttons we have to navigate 
he player across the screen avoiding mines (X) in the way. If the player does not move within 2 seconds, 
hey lose. Display “Game Over!” on the LCD for the first and second lines of the LCD. The objective of the game 
s the make it to the bottom right corner of the LCD screen. Display “You Won!” for winning the game. To achieve 
functionality, make obstacles. B functionality requires the use of interrupts. 

Required Functionality
======================

Objective: 
For required functionality, we need to implement the game as was stated before; however, we do 
not need to use interrupts. We may use the button library for assistance on good code. The two second between
move time must be handled bia an interrupt and the TIMER_A_subsystem. Debounce all button pushes. Use Github as 
is required.

First to start off:
1.) Clear the LCD
2.) Use code from Lab 4 or reference any other Github libraries for help on code
3.) Write Strings to the screen
4.) Poll buttons, can be taken from previous libraries on Github
5.) Get the game to display on the screen
6.) Scroll the player with strings and button pushes 
7.) Poll buttons with the delay in use to determine game over
...
...
...
8.) Make it to the end or take too long (Display a string)
9.) Display conclusion on screen
10.) Poll for reset/ Button pushes


My idea is that I should just be able to jump right into B-Functionality. There really is 
no point to doing just required functionality if B functionality just requires the use of interrupts. 
I am going to jump straight into getting B-Functionality

B Functionality
===============

Objective:
Your game must handle button presses via interrupts. Functionality will be identical to required (why I 
chose to go ahead and go straight for B Functionality). We can initially trigger a button on the falling edge,
then switch the trigger to rising edge to detect the release. 


The idea:
For the delay: we can use the old delay code, but we need to use interrupts this time.

Interrupts:
They are efficient, do not delay code too long with less clock cycles needed to be implemented. Interrupts
execute a pre defined subroutine based on an event, wake up the MSP430 from low-power mode, and interrupts 
have priority (referrence from Lesson 27 notes). 1.) Clear the interrupt flag. 2.) Turn on the local switch.
3.) Turn on global switch.

_enable_interrupt() - enables maskable interrupts

_disable_interrupt() - disables maskable interrupts 

Write an ISR:
include #pragma vector - loads address into interrupt vector table, clear interrupt flag, accomplish task

P1 Interrupt:
For buttons we want: 1 - high-to-low transition

The reason for high to low transition on the P1 interrupt is that we want to trigger on the high, rising edge since
we want to trigger right on the button push and not the release.

Good Code To Use:
Provided in Capt Branchflower's skeleton code for reference. I also reference C2C Tymchecko's and C2C Colin Busho's
code. I envy those guys because they are very good at writing clean code as well as they really do help a lot
in explaining code to me. 

Timer A:
Used to perform interval timing, used to put chip in low power state, waking up to take readings periodically. 

TAR - Timer A Register, IDx - Allows us to slow down frequency by dividing it, TASSELx bits - select clock signal
that Timer A counts off of. Count Mode - Specifies the way the timer counts.TACTL - controls most of the elements 
of TIMER A. 

Timer A can be used to poll the buttons, interrupt, move player, or display Game Over. This is sort of what I am
thinking about. This could be useful for this function. 

Final Part B Thoughts:
Use the interrupt feature, ISR's, Much of the same as required, but make changes to coding/syntax in regards
to delays and timers. 


Part B Lab Coding (Day 1 and Day 2)
===================================

To start off, I pulled up Capt Branchflower's skeleton code. This was very useful as it gave me a basis for
where I will start writing my code and keeping it organized. I quickly noticed that Capt Branchflower wrote his 
code with the intention of using Port 2, but I would rather use Port 1 to make wiring easier and it just makes more
sense to me on the protoboard. Little did I know that this idea I had of using Port 1 would go ahead and make my 
code have many errors in it.

My idea was after the skeleton code to go ahead and think about what I need to get done. I need to use buttons, 
set the clock speed to 1MHz, display on the LCD, as well as implement the game. I referenced Capt Branchflower's
buttons library and I also referenced C2C Colin Busho's clock library. They were both better than my own in syntax
and were very easy to see where I needed to make changes to my own code. 

After obtaining the buttons library and referencing Colin's clock library, I had everything I needed. My first 
action was getting the LCD to clear as well as writting string to the LCD. This was not so hard as LAB 4 sort of
dealt with the same thing. My next motion was to figure out how I was going to use the buttons to move the player 
across the screen. I had an idea. Since the top went from 0x80-0x87 and the botton from C0-C7, I decided that 
left and right could be easy to do. If less than seven, move right, if greater than 0, move left. This took some
thinking about, but in the end it all worked out. As far as up and down, I decided I would just set BIT6 for when 
we move up and then set it to 0 for down. This was simple. I started running into issues with how I was going to implemet the delays. I knew that I needed to use interrupts,
but how was I going to do that. I decided that in the main.c file, I would declare variables. An idea would be
set Game Over == 0 should we be reset, if not then keep Game Over == 1 to continue toggling the Game Over until
a button is pushed or the reset button is used. 

I decided that I would toggle all of the buttons to test if they were pushed in the interrupt. The reset button
was taken care of earlier. 

After writing the code I started running into many errors. I had many functions declaed implicitly. I forgot to 
declare some functions in the header file as well as before I used them in the main.c file. I also had errors with 
my port use. I still had in some areas Port 2 coded in where I needed Port 1. These contradictions just did not 
allow me to use the buttons at all. Once these items were fixed, I was able to get the game to display on the LCD, but
I was still running into issues. I had many warning about more functions being declared implicitly and sometimes it was
as simple as a capitalized letter or not having a semi-colon somewhere.

Capt Branchflower looked at my code and helped me to figure out some of my mistakes. After fixing of what seemed like 
20 minor syntax errors or missing semi-colons, I was able to get the game to work. The game was working sort of fast
so I decided to throw in a long delay after You Won and Game Over. This allows for proper time for the player to view
this conclusion screen.

In the end I achieved B Functionality with the help of a few of my class mates and Capt Branchflower. I really did not
have a great grasp on C programming during the assignments, but this lab helped me out alot with programming in C. 

B Functionality was achieved and signed off on 07 November 2013. 


Analysis
========

