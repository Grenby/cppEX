int* my_slightly_dumb_reallocation(int* source, unsigned int n_old, unsigned int n_new){
    int * newInt = new int[n_new];
    for (int i = 0; i <n_new; ++i) {
        if (i==n_old)break;
        newInt[i]=source[i];
    }
    delete [] source;
    return newInt;
}
