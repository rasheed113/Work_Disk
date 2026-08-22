#include "http-transport-infrastructure.h"

namespace work_disk::transport {

void HttpRouteDispatcher::post(std::string path, RouteHandler handler) {
    postRoutes_[std::move(path)] = std::move(handler);
}

HttpResponse HttpRouteDispatcher::dispatch(const HttpRequest& request) const {
    if (request.method != "POST") {
        return {405, "application/json", R"({"state":"ERROR","error":{"code":"METHOD_NOT_ALLOWED"}})"};
    }

    const auto it = postRoutes_.find(request.path);
    if (it == postRoutes_.end()) {
        return {404, "application/json", R"({"state":"ERROR","error":{"code":"ROUTE_NOT_FOUND"}})"};
    }

    return it->second(request);
}

} // namespace work_disk::transport
