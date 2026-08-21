#pragma once
#include "bookmark_types.h"
namespace work_disk::tools::bookmark { class BookmarkProvider { public: virtual ~BookmarkProvider()=default; virtual bool save(const BookmarkRequest&,std::string&)=0; }; class BookmarkTool { BookmarkProvider& p_; public: explicit BookmarkTool(BookmarkProvider& p):p_(p){} BookmarkResult save(const BookmarkRequest&) const; }; }
