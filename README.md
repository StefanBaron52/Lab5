Lab5
====

Updated Lab 5 Game

The PreLab was accomplished in the lab notebook. The grade was given for the Pre-Lab in the Lab Notebook.
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


