/*******************************************************************************
  Copyright (C) 2019 OLogN Technologies AG
*******************************************************************************/
//===--- RawPtrCastCheck.h - clang-tidy------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef NODECPP_CHECKER_NODECPP_RAWPTRCASTCHECK_H
#define NODECPP_CHECKER_NODECPP_RAWPTRCASTCHECK_H

#include "../ClangTidy.h"

namespace nodecpp {
namespace checker {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/nodecpp-raw-ptr-cast.html
class RawPtrCastCheck : public ClangTidyCheck {
public:
  RawPtrCastCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace checker
} // namespace nodecpp

#endif // NODECPP_CHECKER_NODECPP_RAWPTRCASTCHECK_H
