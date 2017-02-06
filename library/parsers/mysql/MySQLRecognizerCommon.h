/*
 * Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#pragma once

#include "parsers-common.h"

namespace antlr4 {
  class RuleContext;
  class ParserRuleContext;

  namespace tree {
    class ParseTree;
  }

  namespace dfa {
    class Vocabulary;
  }
}

namespace parsers {

  class PARSERS_PUBLIC_TYPE MySQLLexer;

  // A class containing definitions and members used by both lexer and parser classes.
  class PARSERS_PUBLIC_TYPE MySQLRecognizerCommon {
  public:
    // SQL modes that control parsing behavior.
    enum SqlMode {
      NoMode             = 0,
      AnsiQuotes         = 1 << 0,
      HighNotPrecedence  = 1 << 1,
      PipesAsConcat      = 1 << 2,
      IgnoreSpace        = 1 << 3,
      NoBackslashEscapes = 1 << 4
    };


    // For parameterizing the parsing process.
    long serverVersion;
    SqlMode sqlMode; // A collection of flags indicating which of relevant SQL modes are active.

    // Returns true if the given mode (one of the enums above) is set.
    bool isSqlModeActive(size_t mode);
    void sqlModeFromString(std::string modes);

    static std::string dumpTree(antlr4::RuleContext *context, const antlr4::dfa::Vocabulary &vocabulary);
    static std::string sourceTextForContext(antlr4::ParserRuleContext *ctx, bool keepQuotes = false);
    static std::string sourceTextForRange(antlr4::Token *start, antlr4::Token *stop, bool keepQuotes = false);
    static std::string sourceTextForRange(antlr4::tree::ParseTree *start, antlr4::tree::ParseTree *stop, bool keepQuotes = false);

    static antlr4::tree::ParseTree* getPrevious(antlr4::tree::ParseTree *tree);
    static antlr4::tree::ParseTree* getNext(antlr4::tree::ParseTree *tree);
    static antlr4::tree::ParseTree* contextFromPosition(antlr4::tree::ParseTree *root, std::pair<size_t, size_t> position);
  };

  class SymbolTable;

  // Returns a symbol table for all predefined system functions in MySQL. The parameter version must be given as short
  // major * 100 + minor value (e.g. 506, 507, 800 etc.).
  PARSERS_PUBLIC_TYPE SymbolTable* functionSymbolsForVersion(size_t version);

}
