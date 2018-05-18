Final project for ADS-S18
Barnes-Hut nlogn n-body simulation.
This method changes computational time from n^2 to n logn.

To Run:

In the source folder run:

	make gen

	./gen

this will prompt you first for the number of objects and second for the square dimensional range of the objects. Choose a number of objects up to 1000 objects for a reasonable runtime and a zone between 100 and 1080. This will output n bodies to random x,y positions with random mass into a textfile called output.txt.

Next, run:

	make

	./quadtreedriver < output.txt > ../output/_filename_.txt

where you replace _filename_ with the desired destination filename.

This may or may not give feedback while running. TBD

Next, feed this output into the graphics program in the readin folder by running. First edit the ofstream line in proto-draw.cpp to the filepath you want (or leave it as is for a predtermined calculation). Then run:

	make proto-draw
	
	./proto-draw


Click the play button to begin, and the reset button to restart the graphical output.

By:

Spencer Eanes

Jacob Cabbage

Jason Dickmeyer
