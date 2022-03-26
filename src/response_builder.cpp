#include "response.h"

lrrp::response_builder::response_builder() {
    res_ = response();
}

lrrp::response_builder& lrrp::response_builder::set_payload(const json& payload) {
    res_.set_payload(payload);
    return *this;
}

lrrp::response_builder& lrrp::response_builder::set_status(const status_type& status) {
    res_.set_status(status);
    return *this;
}

lrrp::response lrrp::response_builder::build() {
    return res_;
}
