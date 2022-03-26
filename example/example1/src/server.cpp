#include "client.h"
#include "handler_base.h"
#include "request.h"
#include "response.h"

using namespace std;

class sum_handler : public lrrp::handler_base {
public:
    virtual lrrp::response handle(const lrrp::request& req) override {
        int a = req.get_param<int>("a");
        int b = req.get_param<int>("b");
        int sum = a + b;

        printf("asked to sum %d and %d\n", a, b);

        return lrrp::response_builder().set_payload(json({{"sum", sum}})).build();
    }
};

int main() {
    lrrp::server s(8080);
    s.add_handler("sum", std::make_unique<sum_handler>());

    s.run();
}
