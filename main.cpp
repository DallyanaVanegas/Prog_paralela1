#include <iostream>
#include <omp.h>
#include <chrono>

namespace ch = std::chrono;
#define numeroIteraciones 1000000000

double pi_serial(){
    double resp = 0;
    bool esIndicePar = true;
    for (long i = 0; i < numeroIteraciones; i++) {
        if(esIndicePar == true) {
            resp += 4.0/(2.0*i+1.0);
        }
        else {
            resp -= 4.0/(2.0*i+1.0);
        }
        esIndicePar = !esIndicePar;
    }
    return resp;
}

double pi_omp1(){
    int num_hilos= 0;

#pragma omp parallel
    {
        #pragma omp master //le pone en el hilo cero
        num_hilos = omp_get_num_threads();
    }
    std::printf("thread count: %d\n", num_hilos);

    double sumas_parciales[num_hilos];
#pragma omp parallel shared(sumas_parciales)
    {
        int id_hilo = omp_get_thread_num();
        for (long i = id_hilo ; i <= numeroIteraciones; i+=num_hilos) {
            if(i%2==0) {
                sumas_parciales[num_hilos] += 4.0/(2.0*i+1.0);
            }
            else {
                sumas_parciales[num_hilos] -= 4.0/(2.0*i+1.0);
            }
        }
    }
    double respuesta=0;
    for(int i=0; i< num_hilos; i++){
        respuesta = respuesta+ sumas_parciales[i];
    }
    return respuesta;
}
int main() {
    //omp_set_num_threads(8);
    /*#pragma omp parallel default(none)
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
    return 0;*/
    double pi1;
    auto start  = ch :: high_resolution_clock ::now();
    {
        pi1 = pi_omp1();
    }
    auto end  = ch :: high_resolution_clock ::now();
    ch::duration<double,std::milli> duracion = end-start;

    std::printf("Tiempo serial: %lf, pi=%lf\n", duracion.count()*1000, pi1);

    return 0;
}
