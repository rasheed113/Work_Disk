#include "media_acquisition.h"
namespace work_disk::tools::bot52 {
namespace { bool valid(Source s) { switch (s) { case Source::Camera: case Source::Gallery: case Source::DevicePicker: return true; } return false; } }
Result execute(const Request& request, Provider& provider) {
  if (request.request_id.empty() || request.caller_context.empty() || !valid(request.source) || request.max_candidates == 0) return {};
  return provider.acquire(request);
}
} // namespace work_disk::tools::bot52
