#include "lrrp.h"
#include <thread>

using namespace std;

class echo_handler : public lrrp::handler_base {
public:
    virtual lrrp::response handle(const lrrp::request& req) override {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return lrrp::response_builder().set_payload({{"data", req.jsonify()["data"]}}).build();
    }
};

int main() {
    lrrp::server s(8080);
    s.add_handler("echo", std::make_unique<echo_handler>());

    s.run();
}
