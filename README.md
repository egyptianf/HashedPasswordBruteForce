# HashedPasswordBruteForce
After downloading write in your terminal:<br><br>

<h3>For the serial version:</h3><br>
    <code>$ gcc -o crack crack.c -lcrypt -lm</code> <br>
    <code>$ ./crack hashedpassword</code><br><br>

<h3>For the parallel version:</h3><br>
    <h4>inside parallelVersion directory:</h4>
    <code>$ gcc -c *.c</code><br>
    <code>$ ar rcs libmystuff.a *.o</code><br>
    <code>$ gcc -o parallel_crack *.c libmystuff.a -lcrypt -lm -g -Wall -fopenmp </code><br>
    <code>$ ./parallel_crack hashedpassword threads_number</code><br>