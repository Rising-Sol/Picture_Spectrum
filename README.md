# README #

This is a README for writing the PictureSpectrum program.

### What is this repository for? ###

This file is here to orgaize the structure of the PictureSpectrum program
and plan out how to build the program.

### Goal of the program ###

The PictureSpectrum program is intended to take a user uploaded JPEG photo
and rearrange the pixels of that photo into a color spectrum. Pixels will 
be arranged in the Y dimension by luminosity. In the X dimension pixels are
sorted by color values. Total red will be on the very left, gradient into 
green, and then blue. 

Sorting will be done using Radix sort and quicksort. The UI should give the 
user the option of which method to sort the picture.

The user interface will be created in SFML. It should be simple, containing
a button to allow the user to upload a picture, and two buttons to allow the
user to choose whether to sort the picture using Radix or Quick sort. After 
displaying the picture, have a button to return to the main page. 

### Information Resources ###

information on how colors are represented in code.
https://www.rapidtables.com/web/color/RGB_Color.html

SFML resource on manipulating images
https://www.sfml-dev.org/documentation/2.0/classsf_1_1Image.php

information on creating a GUI with SFML
https://www.binpress.com/tutorial/creating-a-city-building-game-with-sfml-part-8-gui-system/130

SFML tutorial page
https://www.sfml-dev.org/tutorials/2.1/

for a visualization of how Radix sort works.
https://www.cs.usfca.edu/~galles/visualization/RadixSort.html

Quick sort visualization
https://www.hackerearth.com/practice/algorithms/sorting/quick-sort/visualize/

### process ###

The two main components of this program will be:
creating a user interface -
	accepting a user input JPEG and returning the sorted picture spectrum to the 
	user.
	
Sorting the accepted picture - 
	using Radix sort and Quick sort to arrange the pixels into color
	coded order. 
	
### Who do I talk to? ###

Kaine Schultz
Schultz.kaine.ix@gmail.com
