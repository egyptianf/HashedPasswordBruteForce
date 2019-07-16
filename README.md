# HashedPasswordBruteForce
After downloading write in your terminal:<br><br>

<h3>For the serial version:</h3><br>
    gcc -o crack crack.c -lcrypt -lm <br>
    ./crack hashedpassword<br><br>

<h3>For the parallel version:</h3><br>
    <h4>inside parallelVersion directory:</h4>
    gcc -c *.c<br>
    ar rcs libmystuff.a *.o<br>
    gcc -o parallel_crack *.c libmystuff.a -lcrypt -lm -g -Wall -fopenmp <br>
    ./parallel_crack hashedpassword threads_number<br>