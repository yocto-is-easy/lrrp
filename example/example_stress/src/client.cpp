#include <iostream>
#include <chrono>

#include "lrrp.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <amount of requests>" << endl;
        return 1;
    }
    int amount_of_requests = atoi(argv[1]);

    lrrp::client c("127.0.0.1", 8080);
    lrrp::request req = lrrp::request_builder("echo").set_param("data", "Hello, World!").build();

    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < amount_of_requests; i++) {
        c.send(req);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Average time: " << (double)duration.count() / amount_of_requests << " ms" << endl;
}
