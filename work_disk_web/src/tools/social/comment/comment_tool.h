#pragma once
#include "comment_types.h"
namespace work_disk::tools::comment { class CommentProvider { public: virtual ~CommentProvider()=default; virtual bool submit(const CommentRequest&,std::string&)=0; }; class CommentTool { CommentProvider& p_; public: explicit CommentTool(CommentProvider& p):p_(p){} CommentResult submit(const CommentRequest&) const; }; }
