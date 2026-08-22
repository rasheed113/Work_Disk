#ifndef WORK_DISK_HTTP_TRANSPORT_INFRASTRUCTURE_H
#define WORK_DISK_HTTP_TRANSPORT_INFRASTRUCTURE_H

#include <functional>
#include <string>
#include <unordered_map>

namespace work_disk::transport {

struct HttpRequest {
    std::string method;
    std::string path;
    std::string body;
};

struct HttpResponse {
    int statusCode;
    std::string contentType;
    std::string body;
};

using RouteHandler = std::function<HttpResponse(const HttpRequest&)>;

class HttpRouteDispatcher {
public:
    void post(std::string path, RouteHandler handler);
    HttpResponse dispatch(const HttpRequest& request) const;

private:
    std::unordered_map<std::string, RouteHandler> postRoutes_;
};

} // namespace work_disk::transport

#endif
