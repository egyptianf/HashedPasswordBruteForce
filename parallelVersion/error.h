extern int error(){
    fprintf(stderr, "Usage: ./crack hash number_of_threads\n");
    return 1;
}