#include "i18n_translation.h"
namespace work_disk::tools::bot54 {
Result execute(const Request& r, Provider& p) {
  if(r.request_id.empty()||r.caller_context.empty()||r.source_language.empty()||r.target_language.empty()||r.resource_key.empty()||r.source_text.empty()) return {};
  if(r.source_language == r.target_language) return {true,r.source_text};
  return p.translate(r);
}
} // namespace work_disk::tools::bot54
