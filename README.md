Final project for ADS-S18
Barnes-Hut nlogn n-body simulation.
This method changes computational time from n^2 to n logn.

To Run:

In the source folder run:

	make gen

	./gen

this will prompt you first for the number of objects and second for the square dimensional range of the objects. Choose a number of objects up to 1million (though this will take some time), and a range **specify the range later**. This will output n bodies to random x,y positions with random mass into a textfile called output.txt.

Next, run:

	make

	./quadtreedriver < output.txt > ../output/_filename_.txt

where you replace _filename_ with the desired destination filename.

This may or may not give feedback while running. TBD

Next, feed this output into the graphics program by running:

	make gui

	./gui < ../output/_filename_.txt

where you replace the filename that you entered.

Alternatively, you can skip the first two steps and gnereate graphics output from a pre-generated example such as 

	./gui < ../output/run1.txt

By:
Spencer Eanes
Jacob Cabbage
Jason Dickmeyer
