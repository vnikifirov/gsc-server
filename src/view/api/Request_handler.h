#pragma once

#include "../../common/paths.h"
#include "resources.h"
#include "../../model/auth/User.h"
#include "../../Session.h"

#include <Wt/Http/Request.h>
#include <Wt/Http/Response.h>

#include <memory>
#include <string>

namespace api {

struct Credentials
{
    std::string username;
    std::string password;
};

class Request_handler
{
public:
    Request_handler(Db_session&, Wt::Http::Request const&, Wt::Http::Response&);

    dbo::ptr<User> authenticate() const;
    std::unique_ptr<resources::Resource> parse_uri() const;

    static void check_password_strength(Credentials const& cred);

private:
    dbo::ptr<User> authenticate_by_cookie_() const;
    dbo::ptr<User> authenticate_by_password_() const;

    void create_cookie_(Wt::Auth::User const&) const;
    void set_cookie_(std::string const& value, int ttl_seconds) const;

    Db_session& session_;
    Wt::Http::Request const& request_;
    Wt::Http::Response& response_;
    std::string path_info_;
    std::string method_;
};

} // end namespace api
