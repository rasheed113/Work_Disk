#include "qr.h"
namespace work_disk::tools::bot53 {
Result encode(const EncodeRequest& r, Provider& p) { if(r.request_id.empty()||r.caller_context.empty()||r.envelope_type.empty()||r.version.empty()||r.payload.empty()) return {}; return p.encode(r); }
Result decode(const DecodeRequest& r, Provider& p) { if(r.request_id.empty()||r.caller_context.empty()||r.encoded.empty()) return {}; return p.decode(r); }
} // namespace work_disk::tools::bot53
