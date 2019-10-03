# HashedPasswordBruteForce
After downloading write in your terminal:<br><br>

<h3>To make a hash to test on it:</h3>
    <code>$ gcc -o hash hash.c -lcrypt</code> <br>
    <code>$ ./hash password</code>
<h4><em>Example:</em></h4>
    <code>$ ./hash hello</code> <br>
    <em>Result:</em> <br>
    <code>$ 50l5IR0THCAN6 </code> <br>


<h3>For the serial version:</h3>
    <code>$ gcc -o crack crack.c -lcrypt -lm</code> <br>
    <code>$ ./crack hashedpassword</code><br><br>

<h3>For the parallel version: <em>(not finished yet)</em></h3>
    <h4>Inside parallelVersion directory:</h4>
    <code>$ bash ./script </code><br>
    <code>$ ./parallel_crack hashedpassword threads_number</code><br>