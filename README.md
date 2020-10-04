# Door Jam
Project for the 2020 Invention Studio Fall Hackathon

## Team Members
* Aaron Rieck
* Russell Newton

## Project Description
The project is a smart door opener that can be opened with the push of a button from the internet, preventing a user from ever being locked out. To open their door, the user must navigate to the door opener website and create an account. They will receive an email that their account is awaiting confirmation before it can used. After their account is confirmed by the administrator as the resident of the room they have indicated, it will be added to the database of registered accounts. The user can then log in to a cookie-authenticated page where they can press a button and open a door. The button sends an API request that runs a function on a Particle Photon which sends a signal to a TI Launchpad board. When the TI board receives the signal, it powers a stepper motor. This motor rotates a piece that turns the door handle to a predetermined amount of steps, holding the handle down for several seconds before moving back. This leaves ample time for a user on the other side of the door to push and enter. Unfortunately, the stepper motor we used does not produce enough torque to turn the door handle. A gear box or more powerful stepper motor could fix this problem.

## Hardware Used
* TI Launchpad (MSP-EXP432P401R)
* Particle Photon
* 28BYJ-48 stepper motor
* ULN2003 stepper motor driver

## Software Used
* C++
* Node.js
* MongoDB
* HTML
* CSS
* BootStrap
* Handlebars
* Code Composer Studio
* Particle Web IDE

## Creation Process:
The first step in the process was creating a web server that could be securely logged into that sends the API request to the Particle Photon. After this, we tested executing functions on the Photon from the internet. Next, we added functionality to the web server such as a user database and confirmation emails. We also wrote the code to drive the stepper motor from the TI Launchpad. To do this, we created [several helper methods](https://github.com/aaronr31/Hack/blob/30b4737a093ea4d3df2872cff1db1eb8a5e0e21f/Hack_LaunchPadCode/Utils.h#L22-L117) and a helper class to make reading from and writing to the pin registers simple. We then worked on driving the TI board from the Photon. The problem we encountered was that the TI board was reading high from the Photon when it should not be. To fix this, we designed an emitter follower circuit using an NPN transistor to ground the input pin of the TI when the Photon is not outputting high, as well as buffering the Photon’s input into the TI. Originally, we also wanted to use a piezo speaker to play a tune from “Take On Me” by a-ha, but we experienced a similar problem where the Photon was reading high, and we weren’t able to fix it the same way, so we left it out of the final product. The 3D-printed parts are not very complicated and were printed without any problems.

## Extension:
Not only would this device be useful for a college dorm, it could be useful for a hotel room, where the door mechanisms are fairly similar. This could be a useful tool for people who have trouble turning handles themselves.

## Submission Video:
[Youtube Link](https://youtu.be/_pt8qd4V0B4)  ||  [Dropbox Link](https://www.dropbox.com/s/93h6g1784k9o52x/Door_Opener.mov)

The submission video shoes the process of creating a new user, getting approval, and logging in. It shows how when the button on the success page is pressed, the command is sent to the Photon, which instructs the Launchpad to start turning the handle. The video shows how the stepper motor isn't strong enough to turn the handle, although it can be seen trying.

## Images of Hardware
Parts Out of the Box | Parts in the Box and on the Door
---------------------|---------------------------------
![PartsOutOfBox](/Photos/PartsOutOfBox.jpg) | ![PartsInBoxOnDoor](/Photos/PartsInBoxOnDoor.jpg)

## Images of Website
Sign-In Page | Sign-Up Page
-------------|-------------
![SignIn](/Photos/Invalid_Password.png) | ![SignUp](/Photos/SignUp.png)
Success Page | No Bypassing Log In!
![Success](/Photos/YoureIn.png) | ![NoBypassing](/Photos/NoBypassing.png)

## Resources:
* [Arduino Stepper Library](https://github.com/arduino-libraries/Stepper)
* [TI Launchpad Lab 6 - GPIO](https://www.ti.com/lit/ml/swrp157/swrp157.pdf?ts=1601837017966)
* [TI Launchpad Lab 9 - SysTick](https://www.ti.com/lit/ml/swrp157/swrp157.pdf?ts=1601837017966)
