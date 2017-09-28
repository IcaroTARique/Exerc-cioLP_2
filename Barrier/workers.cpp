#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <atomic>
#include <chrono>

#define NUM_THREAD 5

using namespace std;
//using namespace std::chrono_literals;

int contador = 0;
int n = NUM_THREAD;
int cont = n;
std::atomic_flag lock = ATOMIC_FLAG_INIT;

// TRABALHADOR UM ***************************************
void worker_1 (int rec){
    int d = 0;
    while (lock.test_and_set()) {/*skip*/}
    cout << "\n\nINIT " << rec << endl;
    lock.clear();
    while (true) {

       while (lock.test_and_set()) {/*skip*/}
       cout << "Fazendo o while do trabalhador " << rec << endl;
       lock.clear();

        __atomic_fetch_add(&contador, 1, __ATOMIC_RELAXED );
        while (lock.test_and_set()) {/*skip*/}
        cout << "Contador em *************" << contador << endl;
        int c = 0;
        lock.clear();


        while (contador != n ){
            if (c < 2){
                while (lock.test_and_set()) {/*skip*/}
                cout << " # " << contador << "Threads chegaram na barreira" << endl;
                lock.clear();
                c++;
            }
        }

        chrono::seconds time(5); // Define tempo em segundos
        this_thread::sleep_for(time); // Faz o delay

        __atomic_fetch_sub(&contador, 1, __ATOMIC_RELAXED );

        while (lock.test_and_set()) {/*skip*/}
            cout << "!!!! PASSEI DA BAREIRA, SOU A THREAD !!!!"<< rec <<  endl;
        lock.clear();

        //while (lock.test_and_set()) {}
        //cout << "Contador contrário em ########" << cont << endl;
        //lock.clear();

        //while (cont != 0) {}
             //while (lock.test_and_set()) {/*skip*/}
            //chrono::seconds time(5); // Define tempo em segundos
            //this_thread::sleep_for(time); // Faz o delay

               //contador = cont;
               //cont = n;
            //cout << "Contador em *************" << contador << endl;
            //cout << "Contador contrário em ########" << cont << endl;
            //lock.clear();
    }
}

// TRABALHADOR DOIS *************************************
/*void worker_2 (){

    while (true) {
                while (lock.test_and_set()) { skip}
        cout << "Fazendo o while do trabalhador " << rec << endl;
        lock.clear();

    __atomic_fetch_add(&rodatnoc, -1, __ATOMIC_RELAXED );
    while (contador != n){}
    rodatnoc = n;
    }
}
*/
int main () {
    int index = 0;

    cout <<"#####################  Numero de Threads passados " << n << endl;
    cout <<"#####################  Contador setado em =" << contador << endl;
    //cout <<"#####################  Contador contrario em =" << rodatnoc << endl;

    thread objThread[n];

    for (int i = 1; i <= n ; i++){

        // PASSAR AS THREADS
        objThread[index ++] = thread(worker_1, i);
        //worker_1(i);
    }
// JOIN
    for (int i = 0; i < n; ++i){
        objThread[i].join();
    }

return 0;
}
