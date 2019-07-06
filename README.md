# HashedPasswordBruteForce
After downloading write in your terminal:<br><br>

<h3>For the serial version:</h3><br>
    -gcc -o crack crack.c -lcrypt -lm <br>
    -./crack hashedpassword<br><br>

<h3>For the parallel version:</h3><br>
    -gcc -o parallel_crack parallel_crack.c -lcrypt -lm -g -Wall -fopenmp <br>
    -./parallel_crack hashedpassword threads_number<br>