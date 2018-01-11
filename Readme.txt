**********************
COMP-2401 Assingment 1 

This program uses bit manipulation to  correct charaters that are simulated to be translated electronically. A error is forced in the transmit function and is corrected using the bitCorrect fuction. 


*********************
Compilation 
the bitManupulation.h function is used to easly do bit manupulation with the requried varibles. This has to be compiled with both the recieve fuction and the send program. 



**********************
Use 	
First run the Transmit program first by compiling it first. 

gcc –o tran transmit.c bit_manipulation.c


then run 
./transmit (what ever you set after the flag)

provide a string of text of your choosing and it will be outputed as a Short

e.g 
 
Please enter a message to transmit: how many errors does this have

zacchaeusleung@zacchaeusleung-VirtualBox:~/a2$ ./transmit

 Transmitted message (short integers):
3732 3308 3944 5380 3276 3080 3315 8088 1796 2136 4018 3890 3316 3858 3892 1300 7254 3836 3144 3868 3332 1876 3222 3258 3901 1280 3220 3085 3938 1112 


Then to get the errors corrected compile the recieve file

gcc –o reci recieve.c bit_manipulation.c


zacchaeusleung@zacchaeusleung-VirtualBox: ./reci

./receive
Please enter the transmitted message: 

3732 3308 3944 5380 3276 3080 3315 8088 1796 2136 4018 3890 3316 3858 3892 1300 7254 3836 3144 3868 3332 1876 3222 3258 3901 1280 3220 3085 3938 1112


 Transmitted Message:
xow�man�0Ezrnpr �eq`4hks hav%


 Corrected Transmitted Message:
how many errors does this have
















