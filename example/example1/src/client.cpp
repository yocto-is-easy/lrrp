#include <iostream>

#include "lrrp.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc != 3) {
        cout << "Usage: " << argv[0] << " <arg1> <arg2>" << endl;
        return 1;
    }

    lrrp::client c("127.0.0.1", 8080);
    lrrp::request req = lrrp::request_builder("sum")
            .set_param("a", stoi(string(argv[1])))
            .set_param("b", stoi(string(argv[2])))
            .build();

    lrrp::response res = c.send(req);
    std::cout << res.get_payload()["sum"] << std::endl;
}
