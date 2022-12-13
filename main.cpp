#include <iostream>
#include <omp.h>

int main() {
    //omp_set_num_threads(8);
    #pragma omp parallel default(none)
    {
        int nthreads = omp_get_num_threads(); //contador de hilos
        int thread_id = omp_get_thread_num(); //ID del hilo actual
        if(thread_id==0){
            std::printf("Tengo %d procesadores\n", omp_get_num_procs());
            std::printf("Tengo %d hilos\n", nthreads);
        }
        //std::printf("Hello OPM\n");
        std::printf("El ID del hilo actual es %d\n",thread_id);
    }
    return 0;
}
