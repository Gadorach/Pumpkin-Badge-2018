# Pumpkin Badge 2018
A simple Halloween-themed LED badge for fun.
Runs on a PIC 12F1572, my 8-pin micro of choice.
Contains my adapted and working I2C library, based on code by Saeed.

Saeed's Blog Here: http://saeedsolutions.blogspot.com/2012/11/pic12f675-i2c-bit-banging-code-proteus.html

Also stole and adapted code for driving the PCA9685 LED Driver used in this project from TeraHz.

TeraHz Git Here: https://github.com/TeraHz/PCA9685

I would've made everything myself, but time was certainly not available for extensive messing about with code. Even with the adaptions, it took a logic analyzer and my Rigol to track down issues with the I2C library and fix my PCA9685 driver code.

Here's a link to my project page on MBChip, along with a simplified parts list.

MBChip Community: https://www.pcbway.com/project/shareproject/Pumpkin_Badge_V1.html

I plan to do more of these little fun boards in the future based on this chipset, so look forward to Christmas and Valentines boards next.

Note, a few glaring flaws exist on the V1 board that I intend to fix later, mainly that you can't both have the PCA9685 installed AND use the ICSP port simultaneously. That's my bad, and already have a fix, but need to finish reworking the board in a few other ways as well to make it a worthy V2. Just program the 12F1572 either before installing the PCA9685, or program the 12F1572 out of system before installing it.

Currently there's only 4 LED patterns, but it's fully programmable, so feel free to make your own!

Anyway, Enjoy!