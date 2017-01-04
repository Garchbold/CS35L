George Archbold	
CS35L
Lab 8

In the homework part of lab 8, I had trouble implementing the multithreading functionality of the main.c file. It was pretty obvious after looking at main.c, how it could benefit from multithreading but the actual implementation was more difficult. The main function accepted the nthreads value from argc, but initally it returned an error if nthreads was greater than one. So I removed that chunk of code in order to allow for more threads. I then made an array of threads to hold all of the inputted nthreads that would later be created.

Then I removed all of the coded that handled the graphics and made that into its own function. I also created three global color variables since there was now another function other than main that needed to access these colors.
I passed this function into the pthread_create function which was in a for loop that creates a thread for each entry in pthreads and assigns them a unique thread ID. 

Each function call starts new thread and I incremented the pixel start point an incrementation inside the graphic function. So if there are four threads, the first thread will start at the first pixel and process every fourth pixel, then the second thread will start at the second pixel and process every fourth pixel from there and so on. By the end of the threads they will al be working independently to finish processing all the pixels. They are all joined together and printed out at the end.


Threads:	Times:
1			51.729s
2			26.011s
4			13.640s
8			7.317s

After looking at the output in make-log.txt I observed that the program was nthreads times faster based on the number of threads.