# LRRP - Liteweight Request Response Protocol

This library is a http alternative that can be used either for interprocess comunication or client-server interraction

## How to build

```bash
    git clone git@github.com:lucky-rydar/lrrp.git
    cd lrrp
    mkdir build
    cd build
    cmake .. && make
```

## Integrate with cmake

To integrate this library with your cmake project add to your cmake file the following lines 

```cmake
    add_subdirectory(path/to/lib/root/dir)
    include_directories(path/to/lib/root/dir/include)
    target_link_libraries(<your tarket> lrrp)
```

To get more examples see examples

## Example of usage

The following code is copied from examples.

In the client it is getting two numbers from argv, creates request, sends it to server and prints the result got from response.
```c++
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

```

On the serverside it is just needed a handler for requested route (in this case it is 'sum'). Then it is needed to run the server, it will proceed all the requests.

```c++
    #include "lrrp.h"

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

```
