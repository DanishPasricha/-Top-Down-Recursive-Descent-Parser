📘 Top-Down Recursive Descent Parser

> A C++ implementation of a top-down recursive descent parser — designed to lex, parse, and analyze input according to a predefined grammar.

---

## 🧠 What Is This?

This project is a complete **lexer and parser framework** using the **recursive descent parsing technique**, typically used for analyzing programming language syntax or DSLs (Domain-Specific Languages). The parser is manually implemented and showcases classical compiler construction techniques.

---

## 📂 File Structure

```
Top-down-recursive-descent-parser/
├── inputbuf.cc           # Handles input buffering
├── inputbuf.h
├── lexer.cc              # Tokenizer (lexical analyzer)
├── lexer.h
├── parser.h              # Recursive descent parser logic
├── new.cc                # Likely the entry point (main function)
├── metadata.yml          # Metadata for project documentation or CI
├── README.md             # Project documentation
└── .gitattributes        # Git settings
```

---

## ⚙️ Features

* ✅ Implements a recursive descent parser in pure C++
* 📚 Separates lexical analysis (`lexer`) and parsing logic
* 🧪 Input buffer abstraction to handle character streams efficiently
* 🔍 Well-structured modular header/source file organization
* 🛠️ Simple to extend with new grammar rules

---

## 🏁 How to Compile and Run

### 🔧 Compile

```bash
g++ inputbuf.cc lexer.cc new.cc -o parser
```

### ▶️ Run

```bash
./parser < input.txt
```

Make sure `input.txt` contains the code or input you'd like to parse.

---

## 📘 Understanding the Components

| File           | Purpose                                              |
| -------------- | ---------------------------------------------------- |
| `inputbuf.*`   | Handles character-by-character input buffering       |
| `lexer.*`      | Tokenizes the input stream into a series of tokens   |
| `parser.h`     | Contains the grammar rules and parsing functions     |
| `new.cc`       | Likely the `main()` function and program entry point |
| `metadata.yml` | CI or documentation metadata (optional use)          |

---

## 🧪 Sample Input (example)

```plaintext
x = a + b * (c + d)
```

The parser processes this input and either:

* Outputs the parsed representation, or
* Reports syntax errors based on grammar violations

---

## 🧰 Prerequisites

* C++11 or later
* Linux/macOS or WSL on Windows
* A basic understanding of parsing and compiler theory is helpful
