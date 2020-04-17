# Paddle-Monitor

The Paddle monitor allows you to see and record a huge ammount of data from any paddle machine.

The Paddle monitor is based around the amazing Teensy 3.6. I am using this because of the larger number of programable pins, the ability to add interupts to all the pins and the sheer speed of the arm processor

a modified Adafruit HX8357 has been used with a higher SPI clock speed to improve the refresh time from 360ms to 190 for a full screen update which is a great improvement. I would like to write a custom library which used an external frame buffer on a ram chip to reduce the refresh time further. 

though a touch screen is used a encoder is used to interface with it because i found it to be easier to use then the touch screen which is not accurate enough  and difficult to use for smaller buttons. but future version will have an encorperated option to activate the touch screen 

the DATALOG.TXT file that the device creates can be read as follows:
angularVelocity, time in Microsecconds

these are the only two recorded bits of data because these are the only bit of data that are required to fully recreate all information that you can get on the paddle monitor. a HR feild will be added when I encorperate them into the code. to get the information recoreded out of the data use the code in the variables.ino which is able to read all the data from these two variables.
the time needs to be turned into milliseconds 


the session file can be written to directly with the formating
effor,length,name,beginOrEnd,unit
no spaces!
effort is weather the effort is a go or stop 1 or 0 respectivly
length can be an integer in the respective unit, total length at the beginning and end
name is the name of the effort, it only needs to be named at the beggining and end of the effort max length 16
beginOrEnd can only be 1 if its the starting or ending line and is used for identification otherwise it must be 0
unit 1 for seconds 0 for distance in metres

example:

1,3160,56 minuite pyramid,1,1

0,120,nul,0,1

1,30,nul,0,1

0,30,nul,0,1

...

0,120,nul,0,1

0,3160,56 minuite pyramid,1,1



beginning is identified with a 1 as the effort and 1 as the beginOrEnd
end id identified with a 0 as the effort and 1 as the beginOrEnd
it is for this reason that the beginOrEnd must be 0 unless its the beginning or end line


How the code works

the variables page can mostly be explained by
http://eodg.atm.ox.ac.uk/user/dudhia/rowing/physics/ergometer.html
which is great paper which explains everything very simply

the drag factor k is set to 3.67 which is the value I calculated with a paddle machine.
the speed factor is set to the recomended 2.8 which I have found to be a bit off so may be changed in the future
the speed is an estimation and does not account for weight which is a majour factor in speed while paddeling as it effect acceleration
f=ma <-- see

millis() is the most common way of finding time with an arduino but with the speed of rotation this would result is very few preset powers which results in inaccurate readings at higher powers.
of 
2778, 2533, 2316, 2123, 1951 ect.

to fix this micros are used which though having the same problem it is 1000 times smaller which is outside of what I would call resonable bounds as k is writen to less significant figures

a min time between full flywheel rotation is set to 31426 microsecconds which results in a w value of roughly 200 and a power of 3000w which I believe is above 99% of users maxium power outputs as I can only peak at 1.6kW

to combat the micros rollover which is a reasonably common occurance a function micros64 was made. this gets the micros value in a 64bit integer and works by counting the number of times that it rolls over. the micros64 function is therefor called in the loop every time which ensures that the rollover is found. it does not need to be this often but it is the most reliable repeating loop which will always catch the rollover and it is critical that it is caught before the w is called.


Graphs works by mapping an array of data onto a simple graph with the tft.drawLine function which makes it really quite simple. to reduce flicker the previous lines are writen over with the same code but the colour white, this reduces the time required to update the graph and I have been able to run it at over 30FPS, but I have set the value at 10 because it is not needed and can clog up the processing and would also result in reading things faster then the Angular velocity(w) is updated.

the graphs are set in there own function seperate to the menu to reduce clutter and it has been designed so that I can add more graphs in the future for other data sets and functions.


Menu.ino is the most on of the most important functions
the concept of its function is simple
the Refresh function is called with every loop cycle, this function detects any button presses and sets the approprite variables and calls the needed functions. if a change in screen or data is required the refresh function is called

refresh requires a boolean as a perameter, HIGH forces it to do a full update of the screen which takes roughly 190ms (very slow) and this clogs up the processor for to long so is only done when the screen changes. otherwise it is set to low

when it is set to low and refresh is called two main things are updated:
- any variables displayed are wiped and updated
- and selection boxes are updated

betterGraphics.ino
this is just a page i have added to reduce clutter in the menu tab, it allow me to draw thich lines as the normal lines are only 1px which is to thin.
and draw custom icons such as the Arrow() icon which draws an arrow for selections

Sessions.ino is not yet finished but possibly the harded to make
the sessionsREAD(byte findSession)
works by opening the SESSIONS.TXT file on the sd card
reading on line into a buffer string
splitting the string at every comma
setting the strings to their apropriate variable types
repeating.

the findSession takes an byte and if passed a byte with values other then 255 will attempt to find that session counting up from zero
so to find the 10 session in the file it will need to be set to 9. When you enter this it will set the variables RunningSessionLine which is used by the sessionRUN() function.

sessionRUN()
reads the file to find the needed session, takes the same value as above
clears the variables. a for loop is needed to clear the data acumulating variables StrokeRate, it is set to 10 loops but can be set to down to 4

once it has done this the setup is complete and every other time it is called it will run the main code
this reads the file utill it finds the RunningSessionLine, it will then store that line and allow the menu to run threw it
once the length has run out it will then read the file again and find RunningSessionLine+1 which is incremented at the end of the reading before. once it finds this line it sets the new values

this can be better optimised to not read the entire file and break the while(dataFile.available()){}

and end session function needs to be added which turns off the session once done and goes to the pause screen. but with the play button deactivated.

Timer is very simple and can be understood by the reader.

this is not the final version of this code as can be seen by the need for optimisation and the missing stop session feature, race feature and bluetooth which was been uncoperative last time I tried.






